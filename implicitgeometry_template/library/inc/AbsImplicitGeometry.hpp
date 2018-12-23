#ifndef __INC_ABSIMPLICITGEOMETRY_HPP__
#define __INC_ABSIMPLICITGEOMETRY_HPP__

#include <iostream>
namespace implicit
{

    class AbsImplicitGeometry
    {
        
        public:
            virtual ~AbsImplicitGeometry();
            virtual bool inside(double x, double y,double z) const = 0;
    };
}//implicit

#endif //__INC_ABSIMPLICITGEOMETRY_HPP__
