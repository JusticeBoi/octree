#include "implicitgeometry.hpp"
#include <iostream>

int main( )
{
    implicit::Circle* circle1 = new implicit::Circle( 0.0, 0.0, 1.06 );
    implicit::Rectangle* rectangle1 = new implicit::Rectangle( -1.0, -1.0, 1.0, 1.0 );
        
    implicit::Intersection* intersection = new implicit::Intersection( circle1, rectangle1 ); 
    implicit::Rectangle* rectangle2 = new implicit::Rectangle( -0.1, -1.5, 0.1, 1.5 );
    
    implicit::Union* union1 = new implicit::Union( intersection, rectangle2 );
    
    implicit::Circle* circle2 = new implicit::Circle( 0.0, 0.0, 0.65 );

    implicit::Difference root( union1, circle2 );

    std::cout << "Point (0, 0): " << root.inside( 0.0, 0.0 ) << std::endl;
    std::cout << "Point (1, 0): " << root.inside( 0.0, 1.0 ) << std::endl;
    std::cout << "Point (1, 0): " << root.inside( 1.1, 0.0 ) << std::endl;
    // ... 
    // (to be used in the quad tree example)
    //delete union1;
    return 0;
}
