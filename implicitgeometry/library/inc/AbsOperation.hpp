#ifndef IMPLICITGEOMETRY_ABSOPERATION_HPP
#define IMPLICITGEOMETRY_ABSOPERATION_HPP

#include "AbsImplicitGeometry.hpp"

namespace implicit
{

class AbsOperation : public AbsImplicitGeometry
{
public:
    AbsOperation( AbsImplicitGeometry* operand1, AbsImplicitGeometry* operand2 );
    virtual ~AbsOperation( );

protected:
    AbsImplicitGeometry* operand1_;
    AbsImplicitGeometry* operand2_;
};

} // implicit

#endif
