#include "sequenceManager.hpp"

using CondensedSequence::SequenceManager;
using CondensedSequence::Residue;

void SequenceManager::reorderSequence()
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
}