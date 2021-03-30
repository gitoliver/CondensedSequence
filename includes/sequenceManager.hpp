#ifndef SEQUENCE_MANAGER_HPP
#define SEQUENCE_MANAGER_HPP

#include "sequenceParser.hpp"
#include "Graph.hpp"

using TemplateGraph::Graph;

namespace CondensedSequence
{
    class SequenceManager : public SequenceParser
    {
    public:
        //////////////////////////////////////////////////////////
        //                       CONSTRUCTOR                    //
        //////////////////////////////////////////////////////////
        SequenceManager(std::string inputSequence) : SequenceParser{inputSequence} {this->SetTerminal(this->FindTerminalResidue());}
        //////////////////////////////////////////////////////////
        //                       ACCESSOR                       //
        //////////////////////////////////////////////////////////
        inline ParsedResidue* GetTerminal() {return terminalResidue_;}
        //////////////////////////////////////////////////////////
        //                       MUTATOR                        //
        //////////////////////////////////////////////////////////
        inline void SetTerminal(ParsedResidue* terminal) {terminalResidue_ = terminal;}
        //////////////////////////////////////////////////////////
        //                       FUNCTIONS                      //
        //////////////////////////////////////////////////////////
        void ReorderSequence();
        void LabelSequence();
        void PrintLabelledSequence();
    private:
        //////////////////////////////////////////////////////////
        //                       ACCESSOR                       //
        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////
        //                       MUTATOR                        //
        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////
        //                       FUNCTIONS                      //
        //////////////////////////////////////////////////////////
        // inline void InitializeGraph() {graph_.SetRoot(this->GetTerminal()->GetNode());}
        //////////////////////////////////////////////////////////
        //                 PRIVATE MEMBERS                      //
        //////////////////////////////////////////////////////////
        ParsedResidue* terminalResidue_;
    };
}
#endif