#ifndef SEQUENCE_RESIDUE_HPP
#define SEQUENCE_RESIDUE_HPP

#include <string>
#include <Node.hpp> // TemplateGraph
#include <Edge.hpp>

namespace CondensedSequence
{
	class Residue
	{
	public:
        //////////////////////////////////////////////////////////
        //                       CONSTRUCTOR                    //
        //////////////////////////////////////////////////////////
        Residue(std::string residueString) ;
        Residue(std::string residueString, Residue* neighbor);
        //~Residue() {std::cout << "Residue destroyed\n";}
        //////////////////////////////////////////////////////////
        //                       ACCESSOR                       //
        //////////////////////////////////////////////////////////
        inline std::string GetName() {return fullResidueString_;}
        inline TemplateGraph::Node<Residue>* GetNode() {return &node_;}
        void Print();
        inline char GetIsomer() {return isomer_;}
        inline std::string GetResidueName() {return residueName_;}
        inline char GetRingType() {return ringType_;}
        inline std::string GetSpecialModifier() {return specialModifier_;}
        inline char GetConfiguration() {return configuration_;}
        inline std::string GetLinkageLabel() {return linkageLabel_;}
        //////////////////////////////////////////////////////////
        //                       MUTATOR                        //
        //////////////////////////////////////////////////////////
    	void AddLinkage(Residue* otherRes);
	private:
        //////////////////////////////////////////////////////////
        //                       FUNCTIONS                      //
        //////////////////////////////////////////////////////////
        void ParseResidueStringIntoComponents(std::string residueString);
        //////////////////////////////////////////////////////////
        //                       MUTATORS                       //
        //////////////////////////////////////////////////////////
        //inline void SetFullResidueString(std::string inputString) {fullResidueString_ = inputString;}
        inline void SetIsomer(char isomer) {isomer_ = isomer;}
        inline void SetResidueName(std::string name) {residueName_ = name;}
        inline void SetRingType(char type) {ringType_ = type;}
        inline void SetSpecialModifier(std::string modifier) {specialModifier_ = modifier;}
        inline void SetConfiguration(char config) {configuration_ = config;}
        inline void SetLinkageLabel(std::string label) {linkageLabel_ = label;}
        //////////////////////////////////////////////////////////
        //                       ATTRRIBUTES                    //
        //////////////////////////////////////////////////////////
		std::string fullResidueString_;           // DManpNAca1-4.
		char isomer_;                      // D or L
        std::string residueName_;                 // Man, Neu, Ido etc
        char ringType_;                    // f or p
        std::string specialModifier_;             // NAc, Gc, A (IdoA)
    	char configuration_;               // a or b
        std::string linkageLabel_;                // 1-4, 2-6, 1- (when connected to OH)
        TemplateGraph::Node<Residue> node_;         
	};
}
#endif