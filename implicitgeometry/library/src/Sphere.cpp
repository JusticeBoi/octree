#include "Sphere.hpp"
#include <cmath>


namespace implicit
{
    Sphere::Sphere(double x, double y, double z, double r ) : x_(x), y_(y), z_(z),r_(r){}


    bool Sphere::inside( double x, double y, double z ) const
    {
        double dx = x - x_;
        double dy = y - y_;
        double dz = z - z_;
    
        return r_ >= std::sqrt( dx * dx + dy * dy + dz * dz );
    }

    bool Sphere::is2D() const { return false;}


}
