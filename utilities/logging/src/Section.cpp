/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/Section.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

Section::Section( const std::string& name, double callTreeDepth ) :
    isActive ( true ),
    myName ( name ),
    myCallTreeDepth( callTreeDepth ),
    callCount( 1 ),
    cpuTimer( ),
    timeAtLastStart( 0 )
{
}

Section::~Section( )
{
}

SectionResultPtr Section::start( const std::string& name )
{
  FUNCTION_START;

  // search for active functions
  for( auto& section : myCallTree )
  {
    if( section->isActive )
    {
      return section->start( name );
    }
  } // end of foreach-loop

  auto result = std::make_shared<SectionResult>( );

  // search for inactive functions with the same name
  for( auto& section : myCallTree )
  {
    if( section->myName == name )
    {
      section->getCurrentState( *result );
      section->timeAtLastStart = result->elapsedTime;
      section->resume();
      return result;
    }
  } // end of foreach-loop

  // create new object
  auto section = std::make_shared<Section>( name, myCallTreeDepth + 1 );
  myCallTree.push_back( section );

  section->getCurrentState( *result );
  section->timeAtLastStart = result->elapsedTime;
  section->cpuTimer.start( );

  return result;

  FUNCTION_END;
}

void Section::resume()
{
  FUNCTION_START;

  isActive = true;
  ++callCount;
  cpuTimer.resume( );

  FUNCTION_END;
}

SectionResultPtr Section::end( )
{
  FUNCTION_START;

  // end all sub-sections
  for( auto& section : myCallTree )
  {
    if( section->isActive )
    {
      return section->end( );
    }
  } // end of foreach-loop

  // end *this
  cpuTimer.stop();
  isActive = false;

  auto result = std::make_shared<SectionResult>( );

  getCurrentState( *result );
  result->elapsedTime -= timeAtLastStart;

  return result;

  FUNCTION_END;
}

SectionResultPtr Section::getStateOfActiveSection( ) const
{
  FUNCTION_START;

  for( const auto& section : myCallTree )
  {
    if( section->isActive )
    {
      return section->getStateOfActiveSection( );
    }
  } // end of foreach-loop

  auto result = std::make_shared<SectionResult>( );

  getCurrentState( *result );
  result->elapsedTime -= timeAtLastStart;

  return result;

  FUNCTION_END;
}

void Section::finalize( std::vector<SectionResult>& resultVector ) const
{
  FUNCTION_START;

  SectionResult result;
  getCurrentState( result );

  resultVector.push_back( result );

  // finalize sub-sections
  for( const auto& section : myCallTree )
  {
    section->finalize( resultVector );
  } //foreach-loop

  FUNCTION_END;
}

void Section::finish( )
{
  FUNCTION_START;

  cpuTimer.stop();
  isActive = false;
  for( auto& section : myCallTree )
  {
    section->finish( );
  } //foreach-loop

  FUNCTION_END;
}
SectionResult& Section::getCurrentState( SectionResult& result ) const
{
  FUNCTION_START;

  // prepare time measurement
  boost::timer::nanosecond_type elapsedTime = cpuTimer.elapsed( ).wall;
  double seconds = static_cast<double> ( elapsedTime ) * 1e-9;

  result.name = myName;
  result.treeDepth = myCallTreeDepth;
  result.callCount = callCount;
  result.elapsedTime = seconds;

  return result;

  FUNCTION_END;
}

} // namespace utilities
