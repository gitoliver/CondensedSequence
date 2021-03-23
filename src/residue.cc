#include "residue.hpp"

using CondensedSequence::Residue;

Residue::Residue(std::string residueString) 
: fullResidueString_ (residueString), node_ (this, residueString) {this->ParseResidueStringIntoComponents(residueString);}

Residue::Residue(std::string residueString, Residue* neighbor) 
: fullResidueString_ (residueString), node_ (this, residueString)
{
	this->ParseResidueStringIntoComponents(residueString);
	this->AddLinkage(neighbor);
}

void Residue::AddLinkage(Residue* otherRes) 
{
    //std::string label = this->GetName() + "->" + otherRes->GetName();
    //std::cout << "Adding Edge: " << label << std::endl;
    this->GetNode()->AddEdge(otherRes->GetNode(), this->GetName() + "->" + otherRes->GetName());
   // std::cout << "Is it getting destroyed now?\n";
}

void Residue::ParseResidueStringIntoComponents(std::string residueString)
{
	std::cout << "PARSING RESIDUE: " << residueString << std::endl;
	if (residueString.find('-') != std::string::npos)
    { // E.g. DManpNAca1-4. Isomer (D or L), residueName (ManNAc), ring type (f or p), configuration (a or b), linkage (1-4)
    	// Reading from front.
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
    	std::cout << "Blah " << residueString[0] << ".\n";
    	std::string linkage(1,residueString[0]);
    	this->SetLinkageLabel(linkage);
    	this->SetResidueName(residueString.substr(1)); // From position 1 to the end.
    }
    else
    { // A terminal
    	this->SetResidueName(residueString);
    }
    this->Print();
}

void Residue::Print()
{
	std::cout 	<< this->GetIsomer() << "_" 
				<< this->GetResidueName() << "_"
				<< this->GetRingType() << "_"
				<< this->GetSpecialModifier() << "_"
				<< this->GetConfiguration() << "_"
				<< this->GetLinkageLabel() << ".\n";
}