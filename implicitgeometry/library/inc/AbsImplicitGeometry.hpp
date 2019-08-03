#ifndef IMPLICITGEOMETRY_ABSIMPLICITGEOMETRY_HPP
#define IMPLICITGEOMETRY_ABSIMPLICITGEOMETRY_HPP

namespace implicit
{

class AbsImplicitGeometry
{
public:
    virtual ~AbsImplicitGeometry( );
    
    virtual bool inside( double x, double y, double z = 0.0 ) const = 0;
};

} // implicit

#endif
