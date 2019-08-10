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
//#include "utilities/packages/checks/inc/Check.hpp"
//
//namespace adhocpp
//{
//namespace utilities
//{
//
//BOOST_AUTO_TEST_SUITE ( CheckTest )
//
//struct CheckFixture
//{
//  double value1;
//  double value2;
//  size_t value3;
//  double tolerance1;
//  double tolerance2;  
//
//  CheckFixture( )
//  {
//    value1 = 0.9999999999999999;
//    value2 = 1.0000000000000001;
//    value3 = 1;
//    tolerance1 = 0.0000000000000001;
//    tolerance2 = 0.0000000000000002;
//  }
//};
//
//BOOST_AUTO_TEST_SUITE ( AdhocppCheckTest )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheck )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK( false ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK( true ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckEqualTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckEqual )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_EQUAL( value1, value2 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_EQUAL( value1, value1 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_EQUAL( 2, value3 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_EQUAL( 1, value3 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_EQUAL( value3, 2 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_EQUAL( value3, 1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckEqualTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckNearTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckNear )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_NEAR( value1, value2, tolerance1 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_NEAR( value1, value2, tolerance2 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckNearTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckNotEqualTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckNotEqual )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_NOT_EQUAL( value1, value1 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_NOT_EQUAL( value1, value2 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_NOT_EQUAL( 1, value3 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_NOT_EQUAL( 2, value3 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_NOT_EQUAL( value3, 1 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_NOT_EQUAL( value3, 2 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckNotEqualTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckNotNearTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckNotNear )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_NOT_NEAR( value1, value2, tolerance2 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_NOT_NEAR( value1, value2, tolerance1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckNotNearTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckGreaterTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckGreater )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_GREATER( value1, value2 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER( value2, value1 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_GREATER( 1, value3 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER( 2, value3 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_GREATER( value3, 1 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER( value3, 0 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckGreaterTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckGreaterEqualTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckGreaterEqual )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_GREATER_EQUAL( value1, value2 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER_EQUAL( value1, value1 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER_EQUAL( value2, value1 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_GREATER_EQUAL( 0, value3 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER_EQUAL( 1, value3 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_GREATER_EQUAL( value3, 2 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER_EQUAL( value3, 1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckGreaterEqualTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckGreaterNearTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckGreaterNear )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_GREATER_NEAR( value1, value2, tolerance1 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER_NEAR( value1, value2,
//                                                    tolerance2 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_GREATER_NEAR( value2, value1,
//                                                    tolerance1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckGreaterNearTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckLessTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckLess )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_LESS( value2, value1 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS( value1, value2 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_LESS( 1, value3 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS( 0, value3 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_LESS( value3, 1 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS( value3, 2 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckLessTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckLessEqualTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckLessEqual )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_LESS_EQUAL( value2, value1 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS_EQUAL( value1, value1 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS_EQUAL( value1, value2 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_LESS_EQUAL( 2, value3 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS_EQUAL( 1, value3 ) );
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_LESS_EQUAL( value3, 0 ));
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS_EQUAL( value3, 1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckLessEqualTest
//
//BOOST_FIXTURE_TEST_SUITE ( AdhocppCheckLessNearTest, CheckFixture )
//
//BOOST_AUTO_TEST_CASE ( AdhocppCheckLessNear )
//{
//  ADHOCPP_CHECK_THROW( ADHOCPP_CHECK_LESS_NEAR( value2, value1, tolerance1 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS_NEAR( value2, value1, tolerance2 ) );
//  ADHOCPP_CHECK_NO_THROW( ADHOCPP_CHECK_LESS_NEAR( value1, value2, tolerance1 ) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // AdhocppCheckLessNearTest
//
//BOOST_AUTO_TEST_SUITE_END() // CheckTest
//
//} // utilities
//} // adhocpp
