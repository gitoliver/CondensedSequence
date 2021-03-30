#include <sstream>
#include "sequenceManager.hpp"

using CondensedSequence::SequenceManager;
using CondensedSequence::ParsedResidue;


void SequenceManager::ReorderSequence()
{
	// Just doing the default by ascending link number for now.
	for (auto &residue : this->GetParsedResidues())
	{
		std::cout << "Links for " << residue->GetName() << ":\n";
		residue->GetNode()->SortInEdgesBySourceTObjectComparator();
		for (auto &neighbor : residue->GetChildren())
		{
			std::cout << neighbor->GetLink() << ",";
		}
		std::cout << "\n";
	}
	return;
}

void SequenceManager::LabelSequence()
{
	std::stringstream ss;
	int linkIndex = 0; // Convention to start form 0 for linkages.
	int residueIndex = 1; // Convention to start from 1 for residues.
	auto startResidue = this->GetTerminal();
	for (auto &residue : this->GetParsedResiduesOrderedByConnectivity())
	{
		ss << residue->GetName() << "&Label=residue-" << residueIndex << ";";
		residue->GetNode()->AddLabel(ss.str());
		++residueIndex;
		ss.str( std::string() ); ss.clear();  // Must do both of these to clear the stream
		for (auto &linkage : residue->GetNode()->GetOutEdges())
		{
			ss << linkage->GetLabel() << "&Label=link-" << linkIndex << ";";
			linkage->AddLabel(ss.str());
			++linkIndex;
			ss.str( std::string() ); ss.clear(); // Must do both of these to clear the stream
		}
	}
	return;
}

void SequenceManager::PrintLabelledSequence()
{
	std::vector<std::string> labelsToPrint;
	auto glycamLabelSignature = "&Label=";
	for (auto &residue : this->GetParsedResidues())
	{
		if (residue->GetType() == ParsedResidue::Type::Terminal)
		{ // Terminal doesn't have linkage, so next for loop doesn't trigger for it.
			labelsToPrint.push_back(residue->GetNode()->FindLabelContaining(glycamLabelSignature));
		}
		for (auto &linkage : residue->GetNode()->GetOutEdges())
		{ 
			labelsToPrint.push_back(residue->GetNode()->FindLabelContaining(glycamLabelSignature) 
				                  + linkage->FindLabelContaining(glycamLabelSignature) );
		}
	}
	std::cout << "HERE" << std::endl;
	std::reverse(labelsToPrint.begin(), labelsToPrint.end()); // Reverse order, as it starts from terminal.
	for (auto &label : labelsToPrint)
		std::cout << label;
	std::cout << "\nGone" << std::endl;
	return;
}