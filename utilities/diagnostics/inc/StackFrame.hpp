/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef STACKFRAME_HPP_
#define STACKFRAME_HPP_

// --- Standard Includes ---
#include <string>
#include <iostream>

// --- Utilities Includes ---
#include "Location.hpp"

namespace utilities
{

class StackFrame final
{
  public:
    StackFrame( const size_t& relativeDepth,
                const std::string& function,
                const std::string& file,
                const int& line );

    StackFrame( const size_t& relativeDepth,
                const Location& location );

    StackFrame( const StackFrame& stackFrame );

    ~StackFrame( ) throw( );

    StackFrame& operator=( const StackFrame& stackFrame );

    int getAbsoluteDepth( const size_t& maxCallStackDepth ) const;

    const Location& getLocation( ) const;

  protected:
    size_t myRelativeDepth;
    
    Location myLocation;

  private:

};

std::ostream& operator<<( std::ostream& output, const StackFrame& stackFrame );

} // utilities

#endif // STACKFRAME_HPP_
