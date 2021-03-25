
#include <iostream>
#include "condensedSequence.hpp"

int main ()
{	
    std::string sequence = "DManp[2S,3Me]a1-6DManpa1-6[DGlcpNAcb1-4][DNeu5Aca2-6DGalpb1-4DGlcpNAc[3S]b1-2DManpa1-3]DManpb1-4DGlcpNAc[6Me]b1-4DGlcpNAcb1-OH";
    std::cout << "ALKDJFLDAKJ\n";
    CondensedSequence::CondensedSequence arryPotter(sequence);
    std::cout << arryPotter.Print() << "\n";
    std::cout << "Visualize the graph here:\nhttps://dreampuf.github.io/GraphvizOnline/#digraph%20G%20%7B%0ABobie-%3ESteve%0A%7D\n";
    std::cout << "\n\n\nAbout to return.\n";
	return 0;
}

