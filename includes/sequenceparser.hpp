#ifndef SEQUENCE_PARSER_HPP
#define SEQUENCE_PARSER_HPP

#include <string>
#include "residue.hpp"
// using namespace TemplateGraph;

namespace CondensedSequence
{
    class SequenceParser
    {
    public:
    //enum class Reordering_Approach {PRESERVE_USER_INPUT, LOWEST_INDEX, LONGEST_CHAIN};
        //////////////////////////////////////////////////////////
        //                       CONSTRUCTOR                    //
        //////////////////////////////////////////////////////////
        SequenceParser() {};
        SequenceParser(std::string sequence);
        //////////////////////////////////////////////////////////
        //                       ACCESSOR                       //
        //////////////////////////////////////////////////////////
        //inline Residue* GetCurrentParentResidue()  {return daddyNow_;}
        std::string Print();
        //////////////////////////////////////////////////////////
        //                       MUTATOR                        //
        //////////////////////////////////////////////////////////
       // inline void AddConnection(Residue* otherRes) {};
        //inline void SetCurrentParentResidue(Residue* parent) {daddyNow_ = parent;}

    private:
        //////////////////////////////////////////////////////////
        //                       ACCESSOR                       //
        //////////////////////////////////////////////////////////
        std::vector<Residue*> GetResidues();
        inline bool DerivativesExist() {return savedDerivatives_.size();}
        //////////////////////////////////////////////////////////
        //                       MUTATOR                        //
        //////////////////////////////////////////////////////////
        void SetInput(std::string sequence);
        std::vector<std::string> ExtractDerivatives();
        //////////////////////////////////////////////////////////
        //                       FUNCTIONS                      //
        //////////////////////////////////////////////////////////
        void TokenizeLabelledInput(std::string inString);
        bool ParseCondensedSequence(std::string inString);
        void RecurveParse(size_t &currentIndex, std::string sequence, Residue* parent);
        Residue* SaveResidue(const size_t windowStart, const size_t windowEnd, const std::string sequence, Residue* parent);
        inline void SaveDerivative(std::string derivative) {savedDerivatives_.push_back(derivative);}
        //////////////////////////////////////////////////////////
        //                 PRIVATE MEMBERS                      //
        //////////////////////////////////////////////////////////
    	std::string inputSequence_;
        std::vector<std::string> savedDerivatives_;
        size_t currentIndex_;
        size_t windowStart_;
        size_t windowEnd_;
        std::vector<std::shared_ptr<Residue>> residues_;
    };
}
#endif