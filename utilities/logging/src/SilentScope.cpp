/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/SilentScope.hpp"
#include "../inc/SilentScopeBehavior.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

SilentScope::SilentScope( const std::string& name ) :
    BasicScope( name, std::make_shared<SilentScopeBehavior>( ) )
{
}

SilentScope::~SilentScope( )
{
  FUNCTION_START;

  close( );

  FUNCTION_END;
}

void SilentScope::subscope( const std::string& name )
{
  FUNCTION_START;

  closeSubscope( );

  mySubscope = std::make_shared<BasicScope>( name );

  FUNCTION_END;
}

void SilentScope::close( )
{
  FUNCTION_START;

  closeSubscope( );

  BasicScope::close( );

  FUNCTION_END;
}

void SilentScope::closeSubscope( )
{
  FUNCTION_START;

  if( mySubscope != nullptr )
  {
	  mySubscope->close( );
  }

  FUNCTION_END;
}

} // namespace utilities
