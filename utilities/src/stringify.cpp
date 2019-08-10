/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Utilities Includes ---
#include "../inc/stringify.hpp"
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

template< >
void formatString< double >( std::string& string )
{
  FUNCTION_START;

    // find e notation position
    std::size_t eNotation = string.find( "e" );

    // if e notation is found, remove preceding zeros
    if( eNotation != std::string::npos )
    {
      // start checking after the 'e'
      std::size_t eFirst = eNotation + 2;

      // skip zeros in e notation
      std::size_t eFirstNonZero = string.find_first_not_of( "0", eFirst );

      // if all digits are zero, keep last zero
      if( eFirstNonZero == std::string::npos )
        eFirstNonZero = string.size( ) - 1;

      // number of zeros to be deleted
      std::size_t eNumPrecedingZeros = eFirstNonZero - eFirst;

      // delete zeros after the 'e'
      string.erase( eFirst, eNumPrecedingZeros );
    }

    // find decimal point position
    std::size_t dPoint = string.find( "." );

    // if decimal point is found, remove trailing zeros
    if( dPoint != std::string::npos )
    {
      // last decimal digit
      std::size_t dLast;

      // if e notation exists, last decimal digit is the one preceding the 'e'
      if( eNotation != std::string::npos ) dLast = eNotation - 1;
      // else, last decimal digit is the last digit
      else dLast = string.size( ) - 1;

      // find last non-zero decimal digit
      std::size_t dLastNonZero = string.find_last_not_of( "0", dLast );

      // if last non-zero digit is the decimal point, remove it as well
      if( dLastNonZero == dPoint ) dLastNonZero--;

      // first trailing zero
      std::size_t dFirstTrailingZero = dLastNonZero + 1;

      // number of trailing zeros to be deleted
      std::size_t dNumTrailingZeros = dLast - dLastNonZero;

      // delete trailing zeros
      string.erase( dFirstTrailingZero, dNumTrailingZeros );
    }

    return;

  FUNCTION_END;
}


} // utilities
