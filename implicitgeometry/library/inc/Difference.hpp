#ifndef IMPLICITGEOMETRY_DIFFERENCE_HPP
#define IMPLICITGEOMETRY_DIFFERENCE_HPP

#include "AbsOperation.hpp"

namespace implicit
{

class Difference: public AbsOperation
{
public:
    Difference(  AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2 );

    virtual bool inside( double x, double y, double z = 0.0 ) const override;
    virtual bool is2D() const override;
};

} // implicit

#endif
