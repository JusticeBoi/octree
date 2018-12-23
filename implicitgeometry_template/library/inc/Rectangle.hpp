#ifndef __INC_RECTANGLE_HPP__
#define __INC_RECTANGLE_HPP__
#include "AbsImplicitGeometry.hpp"
namespace implicit
{

    class Rectangle : public AbsImplicitGeometry
    {
        public:
            Rectangle( double x1, double y1, double x2, double y2);
            bool inside( double x, double y ,double z) const override ;
        private:
            double x1_, y1_, x2_, y2_;
    
    };
}//implicit

#endif//__INC_RECTANGLE_HPP__
