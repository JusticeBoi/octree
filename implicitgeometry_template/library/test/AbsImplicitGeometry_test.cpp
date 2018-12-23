#include "catch.hpp"
#include "AbsImplicitGeometry.hpp"

namespace implicit
{



// Class for testing purposes. For more info check Operation_test.cpp
class AbsImplicitGeometryMock : public AbsImplicitGeometry
{
public:
    unsigned int* n_;

    AbsImplicitGeometryMock( unsigned int* numberOfDestructorCalls ) :
        n_( numberOfDestructorCalls )
    {

    }

    ~AbsImplicitGeometryMock( )
    {
        ++( *n_ );
    }

    virtual bool inside( double x, double y ) const
    {
          return true;
    }
};

TEST_CASE( "AbsImplicitGeometry_test" )
{
    unsigned int numberOfDestructorCalls = 0;

    // Test whether we can create an instance
    const AbsImplicitGeometry* geometry = new AbsImplicitGeometryMock( &numberOfDestructorCalls );

    // Test whether inside was declared as const
    CHECK( geometry->inside( 0.0, 0.0 ) == true );

    delete geometry;

    // Check whether destructor is declared virtual
    CHECK( numberOfDestructorCalls == 1 );
}



} // implicit
