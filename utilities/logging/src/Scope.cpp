/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/Scope.hpp"
#include "../inc/SilentScopeBehavior.hpp"
#include "../inc/LoopedScope.hpp"
#include "../inc/SectionResult.hpp"
#include "../inc/ProgressIndicator.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

#include <iostream> // remove this!!

namespace utilities
{

Scope::Scope( const std::string& name ) :
    BasicScope( name )
{
  FUNCTION_START;

  FUNCTION_END;
}

Scope::~Scope( )
{
  FUNCTION_START;

  close( );

  FUNCTION_END;
}

void Scope::close( )
{
  FUNCTION_START;

  closeSubscope( );

  // print loop summaries
  if( scopeWasClosed == false )
  {
    for ( SectionResultPtr result : myLoopResults )
    {
	  LoopedScope::printLoopResult( result );
	  result->elapsedTime = 0;
	  result->callCount = 0;
    }
  }

  // close the parent class scope (triggers Timer)
  BasicScope::close( );

  FUNCTION_END;
}

void Scope::subscope( const std::string& name )
{
  FUNCTION_START;

  closeSubscope( );

  mySubScope = std::make_shared<BasicScope>( name );

  FUNCTION_END;
}

void Scope::closeSubscope( )
{
  FUNCTION_START;

  if( mySubScope != nullptr )
  {
	  mySubScope->close( );
  }

  FUNCTION_END;
}

void Scope::silentSubscope( const std::string& name )
{
  FUNCTION_START;

  closeSubscope( );
  mySubScope = std::make_shared<BasicScope>( name, std::make_shared<SilentScopeBehavior>( ) );

  FUNCTION_END;
}

void Scope::loopSubscope( const std::string& name )
{
  FUNCTION_START;

  closeSubscope( );

  for ( SectionResultPtr result : myLoopResults )
  {
    if ( result->name == name )
    {
      mySubScope = std::make_shared<LoopedScope>( name, result );
      return;
    }
  }

  auto newResult = std::make_shared<SectionResult>( );
  newResult->name = name;

  mySubScope = std::make_shared<LoopedScope>( name, newResult );

  myLoopResults.push_back( newResult );

  FUNCTION_END;
}

void Scope::loopSubscope( const std::string& name,
                          double startCount,
                          double currentCount,
                          double expectedCount )
{
  FUNCTION_START;

//  loopSubscope( name );
//  ProgressIndicator::printProgress( name, startCount, currentCount, expectedCount );

  closeSubscope( );

  auto progressState = std::make_shared<LoopProgressState>( startCount, currentCount + 1, expectedCount + 1 );
  for ( SectionResultPtr result : myLoopResults )
  {
    if ( result->name == name )
    {
      mySubScope = std::make_shared<LoopedScope>( name, result, progressState );
      return;
    }
  }

  auto newResult = std::make_shared<SectionResult>( );
  newResult->name = name;


  mySubScope = std::make_shared<LoopedScope>( name, newResult, progressState );
//  std::cout << "new\n";

  myLoopResults.push_back( newResult );
  ProgressIndicator::printProgress( name, 0, 0, 10 );


  FUNCTION_END;
}

} // namespace utilities
