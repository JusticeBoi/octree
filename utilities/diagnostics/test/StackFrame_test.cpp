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
//#include "utilities/packages/diagnostics/inc/StackFrame.hpp"
//
//namespace adhocpp
//{
//namespace utilities
//{
//
//BOOST_AUTO_TEST_SUITE ( StackFrameTest )
//
//BOOST_AUTO_TEST_SUITE ( constructorsTest )
//
//BOOST_AUTO_TEST_CASE ( overloadedConstructor1 )
//{
//  StackFrame stackFrame( 0,
//                         "function(arg1, arg2)",
//                         "/path/to/src/file.cpp",
//                         100 );
//
//  BOOST_CHECK( stackFrame.getAbsoluteDepth( 10 ) == 10 );
//
//  BOOST_CHECK( stackFrame.getLocation( ).getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( stackFrame.getLocation( ).getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( stackFrame.getLocation( ).getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_CASE ( overloadedConstructor2 )
//{
//  Location location( "function(arg1, arg2)", "/path/to/src/file.cpp", 100 );
//
//  StackFrame stackFrame( 0, location );
//
//  BOOST_CHECK( stackFrame.getAbsoluteDepth( 10 ) == 10 );
//
//  BOOST_CHECK( stackFrame.getLocation( ).getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( stackFrame.getLocation( ).getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( stackFrame.getLocation( ).getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_CASE ( copyConstructor )
//{
//  StackFrame stackFrame1( 0,
//                          "function(arg1, arg2)",
//                          "/path/to/src/file.cpp",
//                          100 );
//
//  StackFrame stackFrame2( stackFrame1 );
//
//  BOOST_CHECK( stackFrame2.getAbsoluteDepth( 10 ) == 10 );
//
//  BOOST_CHECK( stackFrame2.getLocation( ).getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( stackFrame2.getLocation( ).getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( stackFrame2.getLocation( ).getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // constructorsTest
//
//BOOST_AUTO_TEST_SUITE ( assignmentOperatorTest )
//
//BOOST_AUTO_TEST_CASE ( assignmentOperator )
//{
//  StackFrame stackFrame1( 0,
//                          "function(arg1, arg2)",
//                          "/path/to/src/file.cpp",
//                          100 );
//
//  StackFrame stackFrame2( 1, "unknown", "unknown", 0 );
//
//  stackFrame2 = stackFrame1;
//
//  BOOST_CHECK( stackFrame2.getAbsoluteDepth( 10 ) == 10 );
//
//  BOOST_CHECK( stackFrame2.getLocation( ).getFunction( ) == "function(...)" );
//
//  BOOST_CHECK( stackFrame2.getLocation( ).getFile( ) == "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( stackFrame2.getLocation( ).getLine( ) == 100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // assignmentOperatorTest
//
//BOOST_AUTO_TEST_SUITE ( getAbsoluteDepthTest )
//
//BOOST_AUTO_TEST_CASE ( getAbsoluteDepth )
//{
//  StackFrame stackFrame( 1,
//                         "function(arg1, arg2)",
//                         "/path/to/src/file.cpp",
//                         100 );
//
//  BOOST_CHECK( stackFrame.getAbsoluteDepth( 10 ) == 9 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // getAbsoluteDepthTest
//
//BOOST_AUTO_TEST_SUITE_END() // StackFrameTest
//
//} // utilities
//} // adhocpp
