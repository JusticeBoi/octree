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
#include "../inc/StackFrame.hpp"
#include "utilities/inc/checks.hpp"
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

StackFrame::StackFrame( const size_t& relativeDepth,
                        const std::string& function,
                        const std::string& file,
                        const int& line ) :
  myRelativeDepth( relativeDepth ),
  myLocation( function,
              file,
              line )
{
}

StackFrame::StackFrame( const size_t& relativeDepth,
                        const Location& location ) :
  myRelativeDepth( relativeDepth ),
  myLocation( location )
{
}

StackFrame::StackFrame( const StackFrame& stackFrame ) :
  myRelativeDepth( stackFrame.myRelativeDepth ),
  myLocation( stackFrame.myLocation )
{
}

StackFrame::~StackFrame( ) throw( )
{
}

StackFrame& StackFrame::operator=( const StackFrame& stackFrame )
{
  FUNCTION_START;

    if( this != &stackFrame )
    {
      myRelativeDepth = stackFrame.myRelativeDepth;

      myLocation = stackFrame.myLocation;
    }

    return *this;

  FUNCTION_END;
}


int StackFrame::getAbsoluteDepth( const size_t& maxCallStackDepth ) const
{
  FUNCTION_START;

    ADHOCPP_CHECK_GREATER_EQUAL_MSG_DBG(
      maxCallStackDepth,
      myRelativeDepth,
      "Maximum call stack depth can't be less than a stack frame's depth" );

    return ( maxCallStackDepth - myRelativeDepth );

  FUNCTION_END;
}

const Location& StackFrame::getLocation( ) const
{
  FUNCTION_START;

    return myLocation;

  FUNCTION_END;
}

std::ostream& operator<<( std::ostream& output, const StackFrame& stackFrame )
{
  FUNCTION_START;

    output << stackFrame.getLocation( );

    return output;

  FUNCTION_END;
}

} // utilities
