/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/BasicScope.hpp"
#include "../inc/Timer.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

BasicScope::BasicScope( const std::string& name, ScopeBehaviorPtr scopeBehavior ) :
    myBehavior( scopeBehavior ),
    myName( name ),
    scopeWasClosed( false )
{
  FUNCTION_START;

  Timer::instance( ).start( name );

  FUNCTION_END;
}

BasicScope::~BasicScope( ) noexcept(false)
{
  FUNCTION_START;

  close( );

  FUNCTION_END;
}


void BasicScope::close( )
{
  FUNCTION_START;

  // make sure that close() is called only once
  if( scopeWasClosed == false )
  {
    Timer::instance( ).end( );
    myBehavior->restore( );
    scopeWasClosed = true;
  }

  FUNCTION_END;
}

} // namespace utilities 
