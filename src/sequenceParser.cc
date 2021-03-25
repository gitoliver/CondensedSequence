#include <string>
#include <algorithm> // Reverse function.
//s#include "../../../GLYCAM_Dev_Env/V_2/Web_Programs/gems/gmml/includes/utils.hpp"
#include "sequenceParser.hpp"
#include <Graph.hpp> // For Print.

using CondensedSequence::SequenceParser;
using CondensedSequence::Residue;

SequenceParser::SequenceParser (std::string inputSequence)
{
	std::cout << "Yo\n";
	if (inputSequence.find(';') != std::string::npos)
	{
		std::cout << "Found labels in input\n";
		this->TokenizeLabelledInput(inputSequence);
	}
	else
	{
		std::cout << "Parsing unlabelled input sequence\n";
		this->ParseCondensedSequence(inputSequence);
	}
}

std::string SequenceParser::Print()
{
    TemplateGraph::Graph<Residue> sequenceGraph(this->GetParsedResidues().at(0)->GetNode());
    return sequenceGraph.Print();
}


std::vector<Residue*> SequenceParser::GetParsedResidues()
{
    std::vector<Residue*> rawResidues;
    for(auto &residue : residues_)
    {
        rawResidues.push_back(residue.get());
    }
    return rawResidues;
}

void SequenceParser::TokenizeLabelledInput(std::string inString)
{
	// char delimiter = ';';
	// std::vector<std::string> tokens = gmml::splitStringByDelimiter(inString, delimiter);
	// delimiter = '&';
	// for (auto &element : tokens)
	// {
	// 	std::vector<std::string> labelAndLabelee = gmml::splitStringByDelimiter(element, delimiter);
	// 	for (auto &subtoken : labelAndLabelee)
	// 	{
	// 		std::cout << " " << subtoken << " \n";
	// 	}
	// }
}

bool SequenceParser::ParseCondensedSequence(const std::string sequence)
{
    // Reading from the end of the string.
    std::cout << "About to parse " << sequence << "\n";
	size_t last_dash_index = sequence.find_last_of('-');
	std::string terminal_residue = sequence.substr((last_dash_index + 1)); // From last dash to end.
    std::cout << "Terminal is: " << terminal_residue << "\n";
    residues_.push_back(std::make_unique<Residue>(terminal_residue));
    auto terminal = residues_.back().get();
    //this->SetCurrentParentResidue(residues_.back());
    //std::cout << "And that was: " << this->GetCurrentParentResidue()->GetName() << std::endl;
    //std::cout << "And that was: " << terminal->GetName() << std::endl;
    size_t i = (last_dash_index + 1);        
    this->RecurveParse(i, sequence, terminal); 
    return true;
}

void SequenceParser::RecurveParse(size_t &i, const std::string sequence, Residue* parent)
{
    bool branchStart = true;
    size_t windowEnd = i;
    while (i > 0)
    {
        i--;
        if ( sequence[i] == '-' )
        {
            if (branchStart)
            {
                branchStart = false;
                std::cout << "branchStart is false\n";
            }
            else
            {
                parent = this->SaveResidue(i + 2, windowEnd, sequence, parent);
                windowEnd = i + 2; // Get to the right side of the number e.g. 1-4
            }
        }
        else if ( sequence[i] == '[' )
        {
            parent = this->SaveResidue(i + 1, windowEnd, sequence, parent);
            return;
        }
        else if ( sequence[i] == ']' )
        {
            if ((windowEnd - i) > 7) 
            {   // if not a derivative, save
                std::cout << "WE:" << windowEnd << " i:" << i << std::endl;
                parent = this->SaveResidue(i + 1, windowEnd, sequence, parent);
                this->RecurveParse(i, sequence, parent);
                windowEnd = i;
                branchStart = true; // reset this when you fall out a level
                std::cout << "branchStart is true again\n";
            }
            else // Derivative
            {   
                this->RecurveParse(i, sequence, parent);
            }
        }
        else if ( sequence[i] == ',' )
        {
            parent = this->SaveResidue(i + 1, windowEnd, sequence, parent);
            windowEnd = i;
        }
        else if ( i == 0)
        {
            parent = this->SaveResidue(i, windowEnd, sequence, parent);
        }
    }
    return; 
}

Residue* SequenceParser::SaveResidue(const size_t windowStart, const size_t windowEnd, const std::string sequence, Residue* parent)
{
    std::string residueString = sequence.substr(windowStart, (windowEnd - windowStart));
    //std::cout << "At start of save: " << residueString << std::endl;
    // Splice out anything within [ and ].
    if (residueString.find('[') != std::string::npos) 
    {
        size_t branch_start = residueString.find_first_of('[');
        size_t branch_finish = residueString.find_last_of(']') + 1;
        std::string firstPart = residueString.substr(0, branch_start);
        std::string lastPart = residueString.substr(branch_finish);
        residueString = firstPart + lastPart;
        //std::cout << firstPart << " + " << lastPart << std::endl;
    }
    if (residueString.find('-') != std::string::npos)
    {
        std::cout << "Saving " << residueString << " with parent " << parent->GetName() <<  std::endl;
        residues_.push_back(std::make_unique<Residue>(residueString, parent));
        auto newRes = residues_.back().get();
        if(this->DerivativesExist())
        {
            for(auto &derivative : this->ExtractDerivatives())
            {
                std::cout << "Saving " << derivative << " with parent " << newRes->GetName() <<  std::endl;
                residues_.push_back(std::make_unique<Residue>(derivative, newRes));
            }
        }
        return newRes;
    }
    else // A derivatve. The parent residue doesn't exist yet, so save it.
    {
        //std::cout << "Temporarily holding derivative: " << residueString << "\n";
        this->SaveDerivative(residueString);
        return parent;
    }
}

std::vector<std::string> SequenceParser::ExtractDerivatives()
{
    auto derivativesCopy = savedDerivatives_;
    savedDerivatives_.clear();
    return derivativesCopy;
}


