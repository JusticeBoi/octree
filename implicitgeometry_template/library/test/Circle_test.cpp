#include "catch.hpp"
#include "Circle.hpp"

#include <cmath>

namespace implicit
{



TEST_CASE( "Circle_test" )
{
    Circle circle( 3.0, -2.0, 0.6 );

    double eps = 1e-8;

    CHECK(  circle.inside( 3.0, -2.0 ) );
    CHECK( !circle.inside( 0.0, 0.0 ) );
    
    // left 
    CHECK( !circle.inside( 2.4 - eps, -2.0 ) );
    CHECK(  circle.inside( 2.4 + eps, -2.0 ) );
    
    // right
    CHECK(  circle.inside( 3.6 - eps, -2.0 ) );
    CHECK( !circle.inside( 3.6 + eps, -2.0 ) );
    
    // bottom
    CHECK( !circle.inside( 3.0, -2.6 - eps ) );
    CHECK(  circle.inside( 3.0, -2.6 + eps ) );
    
    // top
    CHECK(  circle.inside( 3.0, -1.4 - eps ) );
    CHECK( !circle.inside( 3.0, -1.4 + eps ) );
    
    double delta = 0.6 / std::sqrt( 2.0 );
    eps /= std::sqrt( 2.0 );
    
    // top left
    CHECK( !circle.inside( 3.0 - delta - eps, -2.0 + delta + eps ) );
    CHECK(  circle.inside( 3.0 - delta + eps, -2.0 + delta - eps ) );

    // top right
    CHECK( !circle.inside( 3.0 + delta + eps, -2.0 + delta + eps ) );
    CHECK(  circle.inside( 3.0 + delta - eps, -2.0 + delta - eps ) );

    // bottom left
    CHECK( !circle.inside( 3.0 - delta - eps, -2.0 - delta - eps ) );
    CHECK(  circle.inside( 3.0 - delta + eps, -2.0 - delta + eps ) );
    
    // bottom left
    CHECK( !circle.inside( 3.0 + delta + eps, -2.0 - delta - eps ) );
    CHECK(  circle.inside( 3.0 + delta - eps, -2.0 - delta + eps ) );
}



} // implicit
