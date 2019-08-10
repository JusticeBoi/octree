/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef STRINGIFY_HPP_
#define STRINGIFY_HPP_

// --- Standard Includes ---
#include <string>
#include <sstream>
#include <limits>

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

template< typename T >
void formatString( std::string& string )
{
  // Do nothing implementation
}

template< >
void formatString< double >( std::string& string );

template< typename T >
const std::string stringify( const T& toStringify )
{
  FUNCTION_START;

    std::string stringified;

    std::ostringstream stringStream;

    stringStream.setf( std::ios_base::boolalpha |
                       std::ios_base::showpoint |
                       std::ios_base::scientific );

    stringStream.precision( static_cast< std::streamsize >
                            ( std::numeric_limits< double >::digits10 ) );

    stringStream << toStringify;

    stringified = stringStream.str( );

    formatString< T >( stringified );

    return stringified;

  FUNCTION_END;
}

}  // utilities

#endif // STRINGIFY_HPP_
