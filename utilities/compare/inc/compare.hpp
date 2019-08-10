/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef COMPARE_HPP_
#define COMPARE_HPP_

// --- Standard Includes ---
#include <cmath>

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"
#include "tolerance.hpp"

namespace utilities
{

template< typename T >
bool compareEqual( const T& leftValue, const T& rightValue, const T& tolerance )
{
  FUNCTION_START;

    return ( std::abs( leftValue - rightValue ) <= std::abs( tolerance ) );

  FUNCTION_END;
}

template< typename T >
bool compareEqual( const T& leftValue, const T& rightValue )
{
  FUNCTION_START;

    return compareEqual( leftValue,
                         rightValue,
                         minimumTolerance< T >( ) );

  FUNCTION_END;
}

template< typename T >
bool compareNotEqual( const T& leftValue, const T& rightValue, const T& tolerance )
{
  FUNCTION_START;

  return !( std::abs( leftValue - rightValue ) <= std::abs( tolerance ) );

  FUNCTION_END;
}

template< typename T >
bool compareNotEqual( const T& leftValue, const T& rightValue )
{
  FUNCTION_START;

    return compareNotEqual( leftValue,
                         rightValue,
                         minimumTolerance< T >( ) );

  FUNCTION_END;
}


template< typename T >
bool compareGreater( const T& leftValue,
                     const T& rightValue,
                     const T& tolerance )
{
  FUNCTION_START;

    return ( ( leftValue > rightValue ) &&
             !compareEqual( leftValue, rightValue, tolerance ) );

  FUNCTION_END;
}

template< typename T >
bool compareGreater( const T& leftValue, const T& rightValue )
{
  FUNCTION_START;

    return compareGreater( leftValue,
                           rightValue,
                           minimumTolerance< T >( ) );

  FUNCTION_END;
}

template< typename T >
bool compareGreaterEqual( const T& leftValue,
                          const T& rightValue,
                          const T& tolerance )
{
  FUNCTION_START;

    return ( ( leftValue > rightValue ) ||
             compareEqual( leftValue, rightValue, tolerance ) );

  FUNCTION_END;
}

template< typename T >
bool compareGreaterEqual( const T& leftValue, const T& rightValue )
{
  FUNCTION_START;

    return compareGreaterEqual( leftValue,
                                rightValue,
                                minimumTolerance< T >( ) );

  FUNCTION_END;
}

template< typename T >
bool compareLess( const T& leftValue, const T& rightValue, const T& tolerance )
{
  FUNCTION_START;

    return ( ( leftValue < rightValue ) &&
             !compareEqual( leftValue, rightValue, tolerance ) );

  FUNCTION_END;
}

template< typename T >
bool compareLess( const T& leftValue, const T& rightValue )
{
  FUNCTION_START;

    return compareLess( leftValue,
                        rightValue,
                        minimumTolerance< T >( ) );

  FUNCTION_END;
}

template< typename T >
bool compareLessEqual( const T& leftValue,
                       const T& rightValue,
                       const T& tolerance )
{
  FUNCTION_START;

    return ( ( leftValue < rightValue ) ||
             compareEqual( leftValue, rightValue, tolerance ) );

  FUNCTION_END;
}

template< typename T >
bool compareLessEqual( const T& leftValue, const T& rightValue )
{
  FUNCTION_START;

    return compareLessEqual( leftValue,
                             rightValue,
                             minimumTolerance< T >( ) );

  FUNCTION_END;
}


}  // utilities

#endif // COMPARE_HPP_
