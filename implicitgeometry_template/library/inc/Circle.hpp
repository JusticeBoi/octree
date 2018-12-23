#ifndef __INC_CIRCLE_HPP__
#define __INC_CIRCLE_HPP__

#include "AbsImplicitGeometry.hpp"
#include <cmath>

namespace implicit
{

    class Circle : public AbsImplicitGeometry
    {
        public:
            Circle (double x, double y, double radius);
            bool inside( double x, double y ,double z) const override ;
        private:
            double x_, y_, radius_;
    
    };
}//implicit

#endif//__INC_CIRCLE_HPP__

