#include "catch.hpp"
#include "AbsImplicitGeometry.hpp"

namespace implicit
{

class AbsImplicitGeometryMock : public AbsImplicitGeometry
{
  	bool inside( double x, double y, double z ) const override
    {
  		return true;
    }
    bool is2D () const override { return true;};
};


TEST_CASE( "AbsImplicitGeometry_test" )
{
	// Test whether we can create an instance
	AbsImplicitGeometryMock geometry;

	// Check whether inside function is declared as const
	const AbsImplicitGeometry& geometryReference = geometry;

    CHECK( geometryReference.inside( 0.0, 0.0 ) == true );
}

} // implicit
