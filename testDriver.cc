
#include <iostream>
#include "sequenceManager.hpp"

int main ()
{	
    std::string sequence = "DTalp[2S,3Me]a1-6DManpa1-6[DAllpNAcb1-4][DNeu5Aca2-6DGalpb1-4DGlcp[3S]b1-2DAltpa1-3]DManpb1-4DGulpNAc[6Me]b1-4DGlcpNAcb1-OH";
    std::cout << "ALKDJFLDAKJ\n";
    CondensedSequence::SequenceManager arryPotter(sequence);
    std::cout << arryPotter.Print() << "\n";
    std::cout << "Visualize the graph here:\nhttps://dreampuf.github.io/GraphvizOnline/#digraph%20G%20%7B%0ABobie-%3ESteve%0A%7D\n";
    arryPotter.reorderSequence();
    std::cout << "\n\n\nAbout to return.\n";
	return 0;
}

