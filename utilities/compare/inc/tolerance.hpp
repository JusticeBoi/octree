/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef TOLERANCE_HPP_
#define TOLERANCE_HPP_

// --- Standard Includes ---
#include <limits>

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

template< typename T >
const T minimumTolerance( )
{
  FUNCTION_START;

    // Minimum tolerance supported by the machine, but a bit looser
    return std::numeric_limits< T >::epsilon( ) * 10e1;

  FUNCTION_END;
}

}  // utilities

#endif // TOLERANCE_HPP_
