#ifndef __INC_DIFFERENCE_HPP__
#define __INC_DIFFERENCE_HPP__
#include "AbsOperation.hpp"

namespace implicit
{

    class Difference : public AbsOperation
    {
        public:
            Difference(AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2);
            bool inside( double x, double y ,double z) const override ;
            //~Difference() override; 
    };

}
#endif //__INC_DIFFERENCE_HPP__
