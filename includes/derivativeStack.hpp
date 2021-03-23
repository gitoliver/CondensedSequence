#ifndef DERIVATIVE_STACK_HPP
#define DERIVATIVE_STACK_HPP

#include <string>
#include <vector>

namespace CondensedSequence
{
	class DerivativeStack
	{
	public:
        //////////////////////////////////////////////////////////
        //                       CONSTRUCTOR                    //
        //////////////////////////////////////////////////////////
        DerivativeStack(std::string residueString);
        //////////////////////////////////////////////////////////
        //                       ACCESSOR                       //
        //////////////////////////////////////////////////////////
        inline bool Exists() {return residues_.empty();}
        //////////////////////////////////////////////////////////
        //                       MUTATOR                        //
        //////////////////////////////////////////////////////////
    	inline void SaveDerivative(std::string derivative) {derivatives_.push_back(derivative);}
        inline std::vector<std::string> Extract() 
        {
            auto derivativesCopy = derivatives_;
            derivatives_.clear();
            return derivativesCopy;
        }
	private:
        //////////////////////////////////////////////////////////
        //                       ATTRRIBUTES                    //
        //////////////////////////////////////////////////////////
		std::vector<std::string> derivatives_;
	};
}
#endif