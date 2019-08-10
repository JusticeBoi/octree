/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Unit Test Includes ---
//#include "utilities/inc/unittest.hpp"
//
//// --- Utilities Includes ---
//#include "utilities/packages/compare/inc/compare.hpp"
//
//namespace adhocpp
//{
//namespace utilities
//{
//
//BOOST_AUTO_TEST_SUITE ( CompareTest )
//
//struct CompareFixture
//{
//  double value1;
//  double value2;
//  double tolerance1;
//  double tolerance2;
//
//  CompareFixture( )
//  {
//    value1 = 0.9999999999999999;
//    value2 = 1.0000000000000001;
//    tolerance1 = 0.0000000000000001;
//    tolerance2 = 0.0000000000000002;
//  }
//};
//
//BOOST_AUTO_TEST_SUITE ( CompareTest )
//
//BOOST_AUTO_TEST_SUITE_END() // CompareTest
//
//BOOST_FIXTURE_TEST_SUITE ( CompareEqualTest, CompareFixture )
//
//BOOST_AUTO_TEST_CASE ( CompareEqual )
//{
//  BOOST_CHECK( !compareEqual( value1, value2, tolerance1 ) );
//  BOOST_CHECK( compareEqual( value1, value2, tolerance2 ) );
//  BOOST_CHECK( compareEqual( value1, value2 ) );
//  BOOST_CHECK( !compareEqual( value2, value1, tolerance1 ) );
//  BOOST_CHECK( compareEqual( value2, value1, tolerance2 ) );
//  BOOST_CHECK( compareEqual( value2, value1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // CompareEqualTest
//
//
//BOOST_FIXTURE_TEST_SUITE ( CompareGreaterTest, CompareFixture )
//
//BOOST_AUTO_TEST_CASE ( CompareGreater )
//{
//  BOOST_CHECK( !compareGreater( value1, value2, tolerance1 ) );
//  BOOST_CHECK( !compareGreater( value1, value2, tolerance2 ) );
//  BOOST_CHECK( !compareGreater( value1, value2 ) );
//  BOOST_CHECK( compareGreater( value2, value1, tolerance1 ) );
//  BOOST_CHECK( !compareGreater( value2, value1, tolerance2 ) );
//  BOOST_CHECK( !compareGreater( value2, value1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // CompareGreaterTest
//
//
//BOOST_FIXTURE_TEST_SUITE ( CompareGreaterEqualTest, CompareFixture )
//
//BOOST_AUTO_TEST_CASE ( CompareGreaterEqual )
//{
//  BOOST_CHECK( !compareGreaterEqual( value1, value2, tolerance1 ) );
//  BOOST_CHECK( compareGreaterEqual( value1, value2, tolerance2 ) );
//  BOOST_CHECK( compareGreaterEqual( value1, value2 ) );
//  BOOST_CHECK( compareGreaterEqual( value2, value1, tolerance1 ) );
//  BOOST_CHECK( compareGreaterEqual( value2, value1, tolerance2 ) );
//  BOOST_CHECK( compareGreaterEqual( value2, value1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // CompareGreaterEqualTest
//
//BOOST_FIXTURE_TEST_SUITE ( CompareLessTest, CompareFixture )
//
//BOOST_AUTO_TEST_CASE ( CompareLess )
//{
//  BOOST_CHECK( compareLess( value1, value2, tolerance1 ) );
//  BOOST_CHECK( !compareLess( value1, value2, tolerance2 ) );
//  BOOST_CHECK( !compareLess( value1, value2 ) );
//  BOOST_CHECK( !compareLess( value2, value1, tolerance1 ) );
//  BOOST_CHECK( !compareLess( value2, value1, tolerance2 ) );
//  BOOST_CHECK( !compareLess( value2, value1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // CompareLessTest
//
//BOOST_FIXTURE_TEST_SUITE ( CompareLessEqualTest, CompareFixture )
//
//BOOST_AUTO_TEST_CASE ( CompareLessEqual )
//{
//  BOOST_CHECK( compareLessEqual( value1, value2, tolerance1 ) );
//  BOOST_CHECK( compareLessEqual( value1, value2, tolerance2 ) );
//  BOOST_CHECK( compareLessEqual( value1, value2 ) );
//  BOOST_CHECK( !compareLessEqual( value2, value1, tolerance1 ) );
//  BOOST_CHECK( compareLessEqual( value2, value1, tolerance2 ) );
//  BOOST_CHECK( compareLessEqual( value2, value1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // CompareLessEqualTest
//
//BOOST_AUTO_TEST_SUITE_END() // CompareTest
//
//} // utilities
//} // adhocpp
