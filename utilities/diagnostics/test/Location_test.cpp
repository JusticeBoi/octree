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
//#include "utilities/packages/diagnostics/inc/Location.hpp"
//
//namespace adhocpp
//{
//namespace utilities
//{
//
//BOOST_AUTO_TEST_SUITE ( LocationTest )
//
//BOOST_AUTO_TEST_SUITE ( constructorsTest )
//
//BOOST_AUTO_TEST_CASE ( defaultConstructor )
//{
//  Location location;
//
//  BOOST_CHECK( location.getFunction( ) == "unknown" );
//
//  BOOST_CHECK( location.getFile( ) == "unknown" );
//
//  BOOST_CHECK( location.getLine( ) == 0 );
//}
//
//BOOST_AUTO_TEST_CASE ( overloadedConstructor )
//{
//  Location location( "function(arg1, arg2)", "/path/to/src/file.cpp", 100 );
//
//  BOOST_CHECK( location.getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( location.getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( location.getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_CASE ( copyConstructor )
//{
//  Location location1( "function(arg1, arg2)", "/path/to/src/file.cpp", 100 );
//
//  Location location2( location1 );
//
//  BOOST_CHECK( location2.getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( location2.getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( location2.getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // constructorsTest
//
//BOOST_AUTO_TEST_SUITE ( assignmentOperatorTest )
//
//BOOST_AUTO_TEST_CASE ( assignmentOperator )
//{
//  Location location1( "function(arg1, arg2)", "/path/to/src/file.cpp", 100 );
//
//  Location location2;
//
//  location2 = location1;
//
//  BOOST_CHECK( location2.getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( location2.getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( location2.getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // assignmentOperatorTest
//
//BOOST_AUTO_TEST_SUITE ( setTest )
//
//BOOST_AUTO_TEST_CASE ( set )
//{
//  Location location;
//
//  location.set( "function(arg1, arg2)", "/path/to/src/file.cpp", 100 );
//
//  BOOST_CHECK( location.getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( location.getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( location.getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // setTest
//
//BOOST_AUTO_TEST_SUITE_END() // LocationTest
//
//} // utilities
//} // adhocpp
