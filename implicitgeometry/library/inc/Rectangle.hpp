#ifndef IMPLICITGEOMETRY_RECTANGLE_HPP
#define IMPLICITGEOMETRY_RECTANGLE_HPP

#include "AbsImplicitGeometry.hpp"

namespace implicit
{

class Rectangle : public AbsImplicitGeometry
{
public:
    Rectangle( double x1, double y1, double x2, double y2 );

    virtual bool inside( double x, double y, double z = 0.0 ) const;
    
private:
    double x1_, y1_, x2_, y2_;    
};

} // implicit

#endif
