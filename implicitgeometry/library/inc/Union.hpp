#ifndef IMPLICITGEOMETRY_UNION_HPP
#define IMPLICITGEOMETRY_UNION_HPP

#include "AbsOperation.hpp"

namespace implicit
{

class Union : public AbsOperation
{
public:
    Union(  AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2 );

    virtual bool inside( double x, double y, double z = 0.0 ) const override;
    virtual bool is2D() const override;
};

} // implicit

#endif
