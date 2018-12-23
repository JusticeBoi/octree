#ifndef __INC_ABSOPERATION_HPP__
#define __INC_ABSOPERATION_HPP__
#include "AbsImplicitGeometry.hpp"

namespace implicit
{

    class AbsOperation: public AbsImplicitGeometry
    {
        public:
            AbsOperation(AbsImplicitGeometry* operand1, AbsImplicitGeometry *operand2 );
    
        protected:
            AbsImplicitGeometry* operand1_;
            AbsImplicitGeometry* operand2_;
    };
}
#endif//__INC_ABSOPERATION_HPP__
