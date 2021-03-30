#include "parsedResidue.hpp"

using CondensedSequence::ParsedResidue;

ParsedResidue::ParsedResidue(std::string residueString) 
: fullResidueString_ (residueString), node_ (this, residueString) {this->ParseResidueStringIntoComponents(residueString);}

ParsedResidue::ParsedResidue(std::string residueString, ParsedResidue* neighbor) 
: fullResidueString_ (residueString), node_ (this, residueString)
{
	this->ParseResidueStringIntoComponents(residueString);
	this->AddLinkage(neighbor);
}

void ParsedResidue::AddLinkage(ParsedResidue* otherRes) 
{
    //std::string label = this->GetName() + "->" + otherRes->GetName();
    //std::cout << "Adding Edge: " << label << std::endl;
    this->GetNode()->AddEdge(otherRes->GetNode(), this->GetConfiguration() + this->GetLinkageLabel());
   // std::cout << "Is it getting destroyed now?\n";
}

char ParsedResidue::GetLink()
{
    switch (this->GetType())
    {
        case (Type::Sugar):
            return this->GetLinkageLabel().back();
        case (Type::Derivative):
            return this->GetLinkageLabel().front();
        case (Type::Terminal):
            return '0';
        default:
            return '0';
    }
}

std::vector<ParsedResidue*> ParsedResidue::GetChildren()
{
    return this->GetNode()->GetIncomingNeighborObjects();
}

std::string ParsedResidue::GetName()
{
    return (this->GetIsomer() + this->GetResidueName() + this->GetRingType() + this->GetSpecialModifier());
}

void ParsedResidue::ParseResidueStringIntoComponents(std::string residueString)
{
	//std::cout << "PARSING RESIDUE: " << residueString << std::endl;
	if (residueString.find('-') != std::string::npos)
    { // E.g. DManpNAca1-4. Isomer (D or L), residueName (ManNAc), ring type (f or p), configuration (a or b), linkage (1-4)
    	// Reading from front.
        this->SetType(Type::Sugar);
    	this->SetIsomer(residueString[0]);
    	this->SetResidueName(residueString.substr(1, 3));
    	this->SetRingType(residueString[4]);
    	// Find the dash, read around it.
    	size_t dashPosition = residueString.find('-');
    	this->SetLinkageLabel(residueString.substr((dashPosition - 1), 3 ));
    	this->SetConfiguration(residueString[dashPosition - 2]);
    	// Find any special modifiers e.g. NAc, Gc, A in IdoA
    	size_t modifierLength = (dashPosition - 7);
    	if (modifierLength > 0)
    		this->SetSpecialModifier(residueString.substr(5, modifierLength));
    	else
    		this->SetSpecialModifier("");
    }
    else if (isdigit(residueString[0]))
    { // A derivative e.g. 3S, 6Me. Linkage followed by residue name. No configuration.
        this->SetType(Type::Derivative);
    	//std::cout << "Assumed derivative " << residueString[0] << ".\n";
    	std::string linkage(1,residueString[0]);
    	this->SetLinkageLabel(linkage);
    	this->SetResidueName(residueString.substr(1)); // From position 1 to the end.
    }
    else
    { // A terminal
        this->SetType(Type::Terminal);
    	this->SetResidueName(residueString);
    }
    //this->Print();
}

void ParsedResidue::Print()
{
	std::cout 	<< this->GetIsomer() << "_" 
				<< this->GetResidueName() << "_"
				<< this->GetRingType() << "_"
				<< this->GetSpecialModifier() << "_"
				<< this->GetConfiguration() << "_"
				<< this->GetLinkageLabel() << ".\n";
}