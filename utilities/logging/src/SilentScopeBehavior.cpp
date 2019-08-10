/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/SilentScopeBehavior.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"
#include "../inc/Logger.hpp"
#include "../inc/Timer.hpp"
#include "../inc/LogConfiguration.hpp"

namespace utilities
{

SilentScopeBehavior::SilentScopeBehavior( ) :
    cachedDepth( LogConfiguration::highestScopeDepthPrinted ),
    cachedConsoleLogLevel( LogConfiguration::consoleLogLevel )
{
  FUNCTION_START;

  size_t treeDepth = Timer::instance( ).getStateOfActiveSection( )->treeDepth;

  if( treeDepth < LogConfiguration::highestScopeDepthPrinted )
  {
    LogConfiguration::highestScopeDepthPrinted = treeDepth;
  }

  LogConfiguration::consoleLogLevel = LogLevels::ERROR;

  FUNCTION_END;
}

SilentScopeBehavior::~SilentScopeBehavior( )
{
//  FUNCTION_START;
//
//  FUNCTION_END;
}

void SilentScopeBehavior::restore( )
{
  FUNCTION_START;

  LogConfiguration::highestScopeDepthPrinted = cachedDepth;

  LogConfiguration::consoleLogLevel = cachedConsoleLogLevel;

  FUNCTION_END;
}

} // namespace utilities 
