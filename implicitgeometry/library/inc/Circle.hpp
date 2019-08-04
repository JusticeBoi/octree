#ifndef IMPLICITGEOMETRY_CIRCLE_HPP
#define IMPLICITGEOMETRY_CIRCLE_HPP

#include "AbsImplicitGeometry.hpp"

namespace implicit
{

class Circle : public AbsImplicitGeometry
{
public:
    Circle( double x, double y, double r );

    virtual bool inside( double x, double y, double z = 0.0 ) const override;
    virtual bool is2D() const override;
    
private:
    double x_, y_;
    double r_;
};

} // implicit

#endif
