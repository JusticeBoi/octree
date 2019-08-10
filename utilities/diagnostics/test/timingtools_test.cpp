/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Internal Includes ---
//#include "../inc/timingtools.hpp"
//
//// --- UnitTest Includes ---
//#include "utilities/inc/unittest.hpp"
//
//namespace adhocpp {
//namespace utilities {
//
//BOOST_AUTO_TEST_SUITE ( timingtoolsTest )
//
//double expensiveFunction( size_t maxI )
//{
//  double sum = 0.0;
//  for ( size_t i = 0; i < maxI; ++i )
//  {
//    sum += i;
//  } // end of i-loop
//
//  return sum;
//}
//
//BOOST_AUTO_TEST_CASE ( tictoc )
//{
//  double time1;
//  double time2;
//  double time3;
//
//  ADHOCPP_CHECK_NO_THROW( timingtools::tic( ) );
//
//  expensiveFunction( 1000000 );
//
//  ADHOCPP_CHECK_NO_THROW( time1 = timingtools::toc( ) );
//
//  expensiveFunction( 1000000 );
//
//  ADHOCPP_CHECK_NO_THROW( time2 = timingtools::toc( ) );
//
//  expensiveFunction( 1000000 );
//
//  ADHOCPP_CHECK_NO_THROW( time3 = timingtools::toc( ) );
//
//  BOOST_CHECK( time1 < time2 );
//  BOOST_CHECK( time2 < time3 );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // timingtoolsTest
//
//}// namespace utilities 
//}// namespace adhocpp
