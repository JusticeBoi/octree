#include "catch.hpp"
#include "Rectangle.hpp"

namespace implicit
{

TEST_CASE( "Rectangle_test" )
{
    Rectangle rectangle( -6.5, 5.0, 1.2, 7.5 );
    
    CHECK(  rectangle.inside( 0.0, 7.0 ) );
    CHECK( !rectangle.inside( 0.0, 0.0 ) );
    
    double eps = 1e-8;

    // left side of left edge
    CHECK( !rectangle.inside( -6.5 - eps, 7.5 ) );
    CHECK( !rectangle.inside( -6.5 - eps, 6.5 ) );
    CHECK( !rectangle.inside( -6.5 - eps, 5.0 ) );
    
    // right side of left edge
    CHECK( !rectangle.inside( -6.5 + eps, 7.5 + eps ) );
    CHECK(  rectangle.inside( -6.5 + eps, 7.5 - eps ) );
    CHECK(  rectangle.inside( -6.5 + eps, 6.5 ) );
    CHECK(  rectangle.inside( -6.5 + eps, 5.0 + eps ) );
    CHECK( !rectangle.inside( -6.5 + eps, 5.0 - eps ) );
    
    // line through the middle
    CHECK( !rectangle.inside( -2.65, 7.5 + eps ) );
    CHECK(  rectangle.inside( -2.65, 7.5 - eps ) );
    CHECK(  rectangle.inside( -2.65, 6.5 ) );
    CHECK(  rectangle.inside( -2.65, 5.0 + eps ) );
    CHECK( !rectangle.inside( -2.65, 5.0 - eps ) );
        
    // left side of right edge
    CHECK( !rectangle.inside( 1.2 - eps, 7.5 + eps ) );
    CHECK(  rectangle.inside( 1.2 - eps, 7.5 - eps ) );
    CHECK(  rectangle.inside( 1.2 - eps, 6.5 ) );
    CHECK(  rectangle.inside( 1.2 - eps, 5.0 + eps ) );
    CHECK( !rectangle.inside( 1.2 - eps, 5.0 - eps ) );
        
    // right side of right edge
    CHECK( !rectangle.inside( 1.2 + eps, 7.5 ) );
    CHECK( !rectangle.inside( 1.2 + eps, 6.5 ) );
    CHECK( !rectangle.inside( 1.2 + eps, 5.0 ) );    
}

} // implicit
