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
//#include "utilities/packages/diagnostics/inc/CallStack.hpp"
//
//namespace adhocpp
//{
//namespace utilities
//{
//
//BOOST_AUTO_TEST_SUITE ( CallStackTest )
//
//BOOST_AUTO_TEST_SUITE ( constructorsTest )
//
//BOOST_AUTO_TEST_CASE ( defaultConstructor )
//{
//  CallStack callStack;
//
//  BOOST_CHECK( callStack.getDepth( ) == 0 );
//}
//
//BOOST_AUTO_TEST_CASE ( copyConstructor )
//{
//  CallStack callStack1;
//
//  callStack1.addStackFrame( "function(arg1, arg2)",
//                            "/path/to/src/file.cpp",
//                            100 );
//
//  CallStack callStack2( callStack1 );
//
//  BOOST_CHECK( callStack2.getDepth( ) == 1 );
//
//  BOOST_CHECK( callStack2.getStackFrame( 0 ).getLocation( ).getFunction( ) ==
//               "function(...)" );
//
//  BOOST_CHECK( callStack2.getStackFrame( 0 ).getLocation( ).getFile( ) ==
//               "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( callStack2.getStackFrame( 0 ).getLocation( ).getLine( ) ==
//               100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // constructorsTest
//
//BOOST_AUTO_TEST_SUITE ( assignmentOperatorTest )
//
//BOOST_AUTO_TEST_CASE ( assignmentOperator )
//{
//  CallStack callStack1;
//
//  callStack1.addStackFrame( "function(arg1, arg2)",
//                            "/path/to/src/file.cpp",
//                            100 );
//
//  CallStack callStack2;
//
//  callStack2 = callStack1;
//
//  BOOST_CHECK( callStack2.getDepth( ) == 1 );
//
//  BOOST_CHECK( callStack2.getStackFrame( 0 ).getLocation( ).getFunction( ) ==
//               "function(...)" );
//
//  BOOST_CHECK( callStack2.getStackFrame( 0 ).getLocation( ).getFile( ) ==
//               "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( callStack2.getStackFrame( 0 ).getLocation( ).getLine( ) ==
//               100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // assignmentOperatorTest
//
//BOOST_AUTO_TEST_SUITE ( addStackFrameTest )
//
//BOOST_AUTO_TEST_CASE ( addStackFrame1 )
//{
//  CallStack callStack;
//
//  callStack.addStackFrame( "function(arg1, arg2)",
//                            "/path/to/src/file.cpp",
//                            100 );
//
//  BOOST_CHECK( callStack.getDepth( ) == 1 );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getFunction( ) ==
//               "function(...)" );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getFile( ) ==
//               "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getLine( ) ==
//               100 );
//}
//
//BOOST_AUTO_TEST_CASE ( addStackFrame2 )
//{
//  Location location( "function(arg1, arg2)",
//                     "/path/to/src/file.cpp",
//                     100 );
//
//  CallStack callStack;
//
//  callStack.addStackFrame( location );
//
//  BOOST_CHECK( callStack.getDepth( ) == 1 );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getFunction( ) ==
//               "function(...)" );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getFile( ) ==
//               "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getLine( ) ==
//               100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // addStackFrameTest
//
//BOOST_AUTO_TEST_SUITE ( getStackFrameTest )
//
//BOOST_AUTO_TEST_CASE ( getStackFrame )
//{
//  CallStack callStack;
//
//  callStack.addStackFrame( "function(arg1, arg2)",
//                            "/path/to/src/file.cpp",
//                            100 );
//
//  BOOST_CHECK( callStack.getDepth( ) == 1 );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getFunction( ) ==
//               "function(...)" );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getFile( ) ==
//               "/path/to/src/file.cpp" );
//
//  BOOST_CHECK( callStack.getStackFrame( 0 ).getLocation( ).getLine( ) ==
//               100 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // getStackFrameTest
//
//BOOST_AUTO_TEST_SUITE_END() // CallStackTest
//
//} // utilities
//} // adhocpp
