#ifndef __INC_INTERSECTION_HPP__
#define __INC_INTERSECTION_HPP__
#include "AbsOperation.hpp"


namespace implicit
{

    class Intersection : public AbsOperation
    {
        public:
            Intersection(AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2);
            bool inside( double x, double y ,double z) const override ;
            //~Intersection() override; 
    };

}
#endif //__INC_INTERSECTION_HPP__
