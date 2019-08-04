#ifndef IMPLICITGEOMETRY_SPHERE_HPP
#define IMPLICITGEOMETRY_SPHERE_HPP

#include "AbsImplicitGeometry.hpp"

namespace implicit
{
    class Sphere : public AbsImplicitGeometry
    {
    public:
        Sphere( double x, double y, double z, double r );
    
        virtual bool inside( double x, double y, double z = 0.0 ) const override;
        virtual bool is2D() const override;
        
    private:
        double x_, y_, z_, r_;    
    };


}






#endif //IMPLICITGEOMETRY_SPHERE_HPP 
