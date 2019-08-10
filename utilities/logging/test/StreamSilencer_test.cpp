/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2016, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Internal Includes ---
//#include "../inc/StreamSilencer.hpp"
//
//// --- UnitTest Includes ---
//#include "utilities/inc/unittest.hpp"
//
//namespace adhocpp {
//namespace utilities {
//
//BOOST_AUTO_TEST_SUITE ( StreamSilencerTest )
//
//BOOST_AUTO_TEST_CASE ( testStreamSilencer )
//{
//  std::string text = "Hi there! How are you! You should not be able to read this, actually";
//  std::string suppressed;
//
//  {
//    StreamSilencer silencer( std::cout );
//
//    std::cout << text << std::endl;
//
//    suppressed = silencer.getSuppressedContent( ).str( );
//  }
//
//  BOOST_CHECK_EQUAL( text, suppressed.substr(0,text.size()) );
//}
//
//BOOST_AUTO_TEST_SUITE_END() // StreamSilencerTest
//
//}// namespace utilities 
//}// namespace adhocpp
