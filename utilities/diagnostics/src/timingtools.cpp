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
#include "../inc/timingtools.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities {
namespace timingtools {

namespace {
thread_local std::chrono::high_resolution_clock::time_point lastTimePoint;
} // namespace

void tic( )
{
  FUNCTION_START;

  lastTimePoint = std::chrono::high_resolution_clock::now( );

  FUNCTION_END;
}

double toc( )
{
  FUNCTION_START;

  auto now = std::chrono::high_resolution_clock::now( );
  double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>( now - lastTimePoint ).count( );

  return elapsed_seconds;

  FUNCTION_END;
}

} // namespace timingtools
} // namespace utilities 
