/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef CALLSTACK_HPP_
#define CALLSTACK_HPP_

// --- Standard Includes ---
#include <vector>
#include <iostream>

// --- Utilities Includes ---
#include "StackFrame.hpp"

namespace utilities
{

class CallStack final
{
  public:
    CallStack( );

    CallStack( const CallStack& callStack );

    ~CallStack( ) throw( );

    CallStack& operator=( const CallStack& callStack );

    size_t getDepth( ) const;

    void addStackFrame( const std::string& function,
                                const std::string& file,
                                const int& line );

    void addStackFrame( const Location& location );

    const StackFrame& getStackFrame( const size_t& index ) const;

  protected:
    std::vector< StackFrame > myEntries;

  private:

};

std::ostream& operator<<( std::ostream& output, const CallStack& callStack );

} // utilities

#endif // CALLSTACK_HPP_
