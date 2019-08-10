/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/ProgressIndicator.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"
#include "../inc/Logger.hpp"
#include "../inc/Timer.hpp"

// --- Std Includes ---
#include <iostream>
#include <iomanip>
#include <sstream>

namespace utilities
{

ProgressIndicator::ProgressIndicator( const std::string& statement,
                                      size_t expectedCount ) :
    myStatement( statement ),
    myExpectedCount( expectedCount ),
    count( 0 ),
    hasFinished( false )
{
  std::stringstream sStream;
  Logger::getWhiteSpaceIndendation( Timer::instance( ).getStateOfActiveSection( ), sStream );
  indendation = sStream.str( );

  if( LogConfiguration::fancy )
  {
    colorStart = std::string( "\033[" ) + LogConfiguration::colorVector[7] + std::string( "m" );
    colorEnd = "\033[0m";
  }
  printStatement( );
}

ProgressIndicator::ProgressIndicator( const std::string& statement,
                                      size_t expectedCount,
                                      size_t startingValue ) :
        myStatement( statement ),
        myExpectedCount( expectedCount - startingValue ),
        count( 0 ),
        hasFinished( false )
{
}

ProgressIndicator::~ProgressIndicator( )
{
}

size_t ProgressIndicator::operator +=( size_t increment )
{
  FUNCTION_START;

  count += increment;
  printStatement( );

  return count;

  FUNCTION_END;
}

size_t ProgressIndicator::operator++( )
{
  FUNCTION_START;

  return operator +=( 1 );

  FUNCTION_END;
}

void ProgressIndicator::printStatement( )
{
  FUNCTION_START;

  hasFinished = printProgress( myStatement, 0, count, myExpectedCount );
//
//  if( LogConfiguration::silent || LogConfiguration::deactivateLogger == true
//      || LogConfiguration::fancy == false )
//  {
//    return;
//  }
//
//  if( myExpectedCount == 0 )
//  {
//    finished( );
//    return;
//  }
//  size_t progress = count * 100 / myExpectedCount;
//
//  if( progress >= 100 )
//  {
//    progress = 100;
//    finished( );
//    return;
//  }
//
//  std::cout << "\r" << indendation << colorStart << myStatement <<
//      std::setw( 3 ) << progress << "%" << colorEnd;
//
//  std::flush( std::cout );

  FUNCTION_END;
}

//void ProgressIndicator::finished( )
//{
//  FUNCTION_START;
//
//  if( hasFinished ) return;
//
//#pragma omp critical( AdhocppLoggingCout )
//  {
//  std::cout << "\r" << indendation << colorStart<< myStatement << "100%" <<
//      colorEnd << std::endl;
//  }
//  hasFinished = true;
//
//  FUNCTION_END;
//
//}

bool ProgressIndicator::printProgress( const std::string& statement,
                                       double startCount,
                                       double currentCount,
                                       double expectedCount )
{
  FUNCTION_START;

  // this is because the "normal" loop only runs from 0 to n-1!
  expectedCount--;

  // check a few things in which case no output should be generated
  if( LogConfiguration::silent || LogConfiguration::deactivateLogger == true ||
      LogConfiguration::fancy == false || LogConfiguration::showProgressbar == false )
  {
    return true;
  }

  std::stringstream sStream;

  // delete current line
  sStream << "\r";

  // initialize percentage
  int percentage = 100;

  // if input data is valid, set percentage
  if( startCount != expectedCount || currentCount != expectedCount )
  {
    percentage = ( currentCount - startCount ) * 100 / ( expectedCount - startCount  );
  }

  /*
   * Codes:
   *
   * hide cursor: "\33[?25l"
   * show cursor: "\33[?25h"
   * set output color: "\033[" + <color code> + "m"
   * reset color: "\033[0m"
   */

  // get right indentation according to current scope
  Logger::getWhiteSpaceIndendation( Timer::instance( ).getStateOfActiveSection( ), sStream );

  // deactivate cursor, set color, print statement, set right distance, print percentage, reset color
  sStream << "\33[?25l" << "\033[" << LogConfiguration::colorVector[7] << "m" << statement << " " <<std::setw( 3 ) <<
      percentage << "%\033[0m";

  bool done = false;
  if( percentage == 100 )
  {
    // show cursor again
    sStream << "\33[?25h\n";

    done = true;
  }

  // output and flush
#pragma omp critical( AdhocppLoggingCout )
  {
  std::cout << sStream.str( );
  std::flush( std::cout );
  }

  return done;

  FUNCTION_END;
}

} // namespace utilities
