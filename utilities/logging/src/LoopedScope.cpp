/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/LoopedScope.hpp"
#include "../inc/SilentScopeBehavior.hpp"
#include "../inc/Timer.hpp"
#include "../inc/Logger.hpp"
#include "../inc/TimeSpan.hpp"
#include "../inc/ProgressIndicator.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- Std Includes ---
#include <iomanip>
#include <iostream>

namespace utilities
{

LoopedScope::LoopedScope( const std::string& name, SectionResultPtr loopSummaryResult ) :
    BasicScope( name, std::make_shared<SilentScopeBehavior>( ) ),
    myResult( loopSummaryResult )
{
}

LoopedScope::LoopedScope( const std::string& name, SectionResultPtr loopSummaryResult,
		LoopProgressStatePtr progressState ) :
BasicScope( name, std::make_shared<SilentScopeBehavior>( ) ),
myResult( loopSummaryResult ),
myProgress( progressState )
{
}

LoopedScope::~LoopedScope( )
{
  FUNCTION_START;

  close( );

  FUNCTION_END;
}

void LoopedScope::close( )
{
  FUNCTION_START;

  // make sure that close() is called only once
  if( scopeWasClosed == false )
  {
    SectionResultPtr result = Timer::instance( ).end( );
    ++myResult->callCount;
    myResult->treeDepth = result->treeDepth - 1;
    myResult->elapsedTime += result->elapsedTime;

    if( myProgress != nullptr )
    {
      ProgressIndicator::printProgress( myName, myProgress->startCount,
    		  myProgress->currentCount, myProgress->expectedCount );
    }

    myBehavior->restore( );
    scopeWasClosed = true;

  }



  FUNCTION_END;
}

void LoopedScope::printLoopResult( SectionResultPtr result )
{
  FUNCTION_START;

  // ---------------- hard coded table field lengths --------------------

  int nameWidth = 45;		// length of the name field
  int timeSpanWidth = 20;   // length of the time spent field
  int countWidth = 6;		// length of the call count field

  // --------------------------------------------------------------------

  if( LogConfiguration::silent || LogConfiguration::deactivateLogger == true ||
		  LogConfiguration::showLoopSummary == false )
  {
    return;
  }

  // get left whitespace that depends on scope depth
  std::stringstream output;
  Logger::getWhiteSpaceIndendation( result, output );
  std::string whiteSpace = output.str( ) ;

  // prepare time span string
  output.str( "" );
  output << TimeSpan( result->elapsedTime );
  timeSpanWidth -= output.str( ).length( );
  if( timeSpanWidth < 0 )
  {
	  timeSpanWidth = 0;
  }
  std::string timeSpan( timeSpanWidth, ' ' );
  timeSpan += output.str( );

  // prepare name string
  nameWidth -= result->name.length( );
  if( nameWidth < 0 )
  {
	  nameWidth = 0;
  }
  std::string name = result->name + "':" + std::string( nameWidth, ' ' );

  // prepare count string
  output.str( "" );
  output << result->callCount;
  countWidth -= output.str( ).length( );
  if( countWidth < 0 )
  {
	  countWidth = 0;
  }
  std::string count = ", " + std::string( countWidth, ' ' ) + output.str( ) + " times";

  output.str( "" );
  output << whiteSpace << "  loop summary of '" << name << timeSpan << count;

  output << "\n";


  std::string colorStart = "";
  std::string colorEnd = "";

  if( LogConfiguration::fancy )
  {
	colorStart = std::string( "\033[" ) + LogConfiguration::colorVector[8] + std::string( "m" );
	colorEnd = "\033[0m";
  }
#pragma omp critical( AdhocppLoggingCout )
  {
    std::cout << colorStart << output.str( ) << colorEnd;
  }
  FUNCTION_END;
}

} // namespace utilities 
