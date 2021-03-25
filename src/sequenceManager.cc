#include "sequenceManager.hpp"

using CondensedSequence::SequenceManager;

void SequenceManager::reorderSequence()
{
	// Just doing the default by ascending link number for now.
	for (auto &residue : this->GetParsedResidues())
	{
		std::cout << "Links for " << residue->GetName() << ":\n";
		for (auto &neighbor : residue->GetChildren())
		{
			std::cout << neighbor->GetName() << ",";
		}
		std::cout << "\n";
	}
}