#include "catch.hpp"
#include "Union.hpp"
#include "Difference.hpp"
#include "Intersection.hpp"
#include "Circle.hpp"

namespace implicit
{



// A mock is something we create for testing purposes that behaves like a real
// type but does testing for us. This way we can  inject testing code where 
// the final result doesn't tell us whether something happened or not. In our  
// case we use this to test whether memory was deallocated in AbsOperation.
class OperationDeallocationMock : public AbsImplicitGeometry
{
    AbsImplicitGeometry* geometry_;
    
    static unsigned int totalNumberOfObjects;
    
public:
    OperationDeallocationMock( AbsImplicitGeometry* geometry  ) :
        geometry_( geometry )
    {
        ++totalNumberOfObjects;
    }
    
    ~OperationDeallocationMock( )
    {
        delete geometry_;
        
        --totalNumberOfObjects;
    }
        
    virtual bool inside( double x, double y ) const
    {
        return geometry_->inside( x, y );
    }
    
    static bool operandsWereDeleted( )
    {
        return totalNumberOfObjects == 0;
    }
    
    static void reset( )
    {
        totalNumberOfObjects = 0;
    }
};

unsigned int OperationDeallocationMock::totalNumberOfObjects = 0;

TEST_CASE( "Union_test" )
{ 
    OperationDeallocationMock::reset( );
    
    // create new scope
    {
        OperationDeallocationMock* mockedCircle1 = new OperationDeallocationMock( new Circle( 0.0, 0.0, 1.0 ) );
        OperationDeallocationMock* mockedCircle2 = new OperationDeallocationMock( new Circle( 1.0, 0.0, 1.0 ) );
        
        Union u( mockedCircle1, mockedCircle2 );
        
        CHECK( !u.inside( 0.5,  1.0 ) );
        CHECK( !u.inside( 0.5, -1.0 ) );
        
        CHECK( !u.inside( -1.5, 0.0 ) );
        CHECK(  u.inside( -0.2, 0.0 ) );
        CHECK(  u.inside(  0.2, 0.0 ) );
        CHECK(  u.inside(  0.8, 0.0 ) );
        CHECK(  u.inside(  1.2, 0.0 ) );
        CHECK( !u.inside(  2.5, 0.0 ) );
    }
    
    // at this point Union went out of scope and should have deleted its members
    CHECK( OperationDeallocationMock::operandsWereDeleted( ) );
}

TEST_CASE( "Difference_test" )
{    
    OperationDeallocationMock::reset( );
    
    {
        OperationDeallocationMock* mockedCircle1 = new OperationDeallocationMock( new Circle( 0.0, 0.0, 1.0 ) );
        OperationDeallocationMock* mockedCircle2 = new OperationDeallocationMock( new Circle( 1.0, 0.0, 1.0 ) );
        
        Difference difference( mockedCircle1, mockedCircle2 );
        
        CHECK( !difference.inside( 0.5,  1.0 ) );
        CHECK( !difference.inside( 0.5, -1.0 ) );
        
        CHECK( !difference.inside( -1.5, 0.0 ) );
        CHECK(  difference.inside( -0.2, 0.0 ) );
        CHECK( !difference.inside(  0.2, 0.0 ) );
        CHECK( !difference.inside(  0.8, 0.0 ) );
        CHECK( !difference.inside(  1.2, 0.0 ) );
        CHECK( !difference.inside(  2.5, 0.0 ) );
    }
    
    CHECK( OperationDeallocationMock::operandsWereDeleted( ) );
}

TEST_CASE( "Intersection_test" )
{
    OperationDeallocationMock::reset( );
    
    {
        OperationDeallocationMock* mockedCircle1 = new OperationDeallocationMock( new Circle( 0.0, 0.0, 1.0 ) );
        OperationDeallocationMock* mockedCircle2 = new OperationDeallocationMock( new Circle( 1.0, 0.0, 1.0 ) );
        
        Intersection intersection( mockedCircle1, mockedCircle2 );
        
        CHECK( !intersection.inside( 0.5,  1.0 ) );
        CHECK( !intersection.inside( 0.5, -1.0 ) );
        
        CHECK( !intersection.inside( -1.5, 0.0 ) );
        CHECK( !intersection.inside( -0.2, 0.0 ) );
        CHECK(  intersection.inside(  0.2, 0.0 ) );
        CHECK(  intersection.inside(  0.8, 0.0 ) );
        CHECK( !intersection.inside(  1.2, 0.0 ) );
        CHECK( !intersection.inside(  2.5, 0.0 ) );
    }
    
    CHECK( OperationDeallocationMock::operandsWereDeleted( ) );
}



} // implicit
