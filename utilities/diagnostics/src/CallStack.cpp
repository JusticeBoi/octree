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
#include "../inc/CallStack.hpp"
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

CallStack::CallStack( )
{
}

CallStack::CallStack( const CallStack& callStack ) :
        myEntries( callStack.myEntries )
{
}

CallStack::~CallStack( ) throw ( )
{
}

CallStack& CallStack::operator=( const CallStack& callStack )
{
  FUNCTION_START;

    if ( this != &callStack )
    {
      myEntries = callStack.myEntries;
    }

    return *this;

  FUNCTION_END;
}

size_t CallStack::getDepth( ) const
{
  FUNCTION_START;

    return myEntries.size( );

  FUNCTION_END;
}

void CallStack::addStackFrame( const std::string& function,
                               const std::string& file,
                               const int& line )
{
  FUNCTION_START;

    myEntries.push_back( StackFrame( getDepth( ), function, file, line ) );

    return;

  FUNCTION_END;
}

void CallStack::addStackFrame( const Location& location )
{
  FUNCTION_START;

    StackFrame stackFrame( getDepth( ), location );

    myEntries.push_back( stackFrame );

    return;

  FUNCTION_END;
}

const StackFrame& CallStack::getStackFrame( const size_t& index ) const
{
  FUNCTION_START;

    return myEntries.at( index );

  FUNCTION_END;
}

std::ostream& operator<<( std::ostream& output,
                          const CallStack& callStack )
{
  FUNCTION_START;

    int maxDepth = callStack.getDepth( );

    for ( int i = 0; i < maxDepth; i++ )
    {
      output << "\t" << "["
          << callStack.getStackFrame( i ).getAbsoluteDepth( maxDepth ) << "/"
          << maxDepth << "]" << " " << callStack.getStackFrame( i );

      if ( i < ( maxDepth - 1 ) )
        output << std::endl;
    }

    return output;

  FUNCTION_END;
}

} // utilities
