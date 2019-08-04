#ifndef IMPLICITGEOMETRY_INTERSECTION_HPP
#define IMPLICITGEOMETRY_INTERSECTION_HPP

#include "AbsOperation.hpp"

namespace implicit
{

class Intersection : public AbsOperation
{
public:
    Intersection(  AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2 );

    virtual bool inside( double x, double y, double z=0.0 ) const override;
    virtual bool is2D() const override;
};

} // implicit

#endif
