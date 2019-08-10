/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/Logger.hpp"
#include "../inc/Timer.hpp"
#include "../inc/TimeSpan.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- Std Includes ---
#include <iostream>
#include <fstream>
#include <initializer_list>

namespace utilities
{

void Logger::log( const std::stringstream& message,
                  LogLevels logLevel,
                  bool addTimeStamp )
{
  FUNCTION_START;

  Timer::checkpoint( );

  if ( ( LogConfiguration::deactivateLogger == true || LogConfiguration::silent ) && logLevel > LogLevels::WARNING ) return;

  SectionResultPtr result = Timer::instance( ).getStateOfActiveSection( );

  if ( result->treeDepth > LogConfiguration::highestScopeDepthPrinted && logLevel > LogLevels::WARNING )
  {
    return;
  }
  std::stringstream line;

  getWhiteSpaceIndendation( result, line );

  line << message.str( );
  if ( addTimeStamp ) wrapWordsAndAddTimeStamp( TimeSpan( result->elapsedTime ), line );

  line << "\n";

  logMessage( line, logLevel );

  FUNCTION_END;
}

void Logger::simpleLog( const std::string& message )
{
  FUNCTION_START;

  if ( LogConfiguration::deactivateLogger == true ) return;

  writeToFile( message );

  if ( LogConfiguration::silent == false ) {
#pragma omp critical( AdhocppLoggingCout )
    {
      std::cout << message;
    }
  }

  FUNCTION_END;
}

void Logger::simpleLog( const std::string& message,
                        utilities::LogLevels logLevel )
{
  FUNCTION_START;

  if ( LogConfiguration::deactivateLogger == true ) return;

  std::stringstream output;

  output << message;

  logMessage( output, logLevel );

  FUNCTION_END;
}

void Logger::logScopeStart( utilities::SectionResultPtr result )
{
  FUNCTION_START;

  if ( LogConfiguration::deactivateLogger == true || LogConfiguration::highestScopeDepthPrinted < result->treeDepth || LogConfiguration::deactiveScopeOutput == true
      || LogConfiguration::silent == true ) return;

  std::stringstream line;

  getScopedIndendation( result, line );

  if ( result->treeDepth > 0 && LogConfiguration::indentation > 0 )
  {
    line << "|" << std::string( LogConfiguration::indentation - 1, '-' ) << ">";
  }
  line << result->name << "\n";

  writeToFile( line.str( ) );
  coloredOutput( line.str( ), 5 );

  FUNCTION_END;
}
void Logger::logScopeEnd( utilities::SectionResultPtr result )
{
  FUNCTION_START;

  if ( LogConfiguration::deactivateLogger == true || LogConfiguration::highestScopeDepthPrinted < result->treeDepth || LogConfiguration::deactiveScopeOutput == true
      || LogConfiguration::silent == true ) return;

  std::stringstream line;

  getScopedIndendation( result, line );

  if ( result->treeDepth > 0 && LogConfiguration::indentation > 0 )
  {
    line << "|" << "<" << std::string( LogConfiguration::indentation - 1, '-' );
  }
  line << result->name;

  wrapWordsAndAddTimeStamp( TimeSpan( result->elapsedTime ), line );

  line << "\n";

  writeToFile( line.str( ) );
  coloredOutput( line.str( ), 6 );

  FUNCTION_END;
}

void Logger::getWhiteSpaceIndendation( utilities::SectionResultPtr result,
                                       std::stringstream &output )
{
  FUNCTION_START;

  size_t depth = ( (size_t) result->treeDepth < LogConfiguration::highestScopeDepthPrinted ) ? (size_t) result->treeDepth : LogConfiguration::highestScopeDepthPrinted;

  output << std::string( depth * ( LogConfiguration::indentation + 1 ), ' ' );

  FUNCTION_END;
}

void Logger::getScopedIndendation( utilities::SectionResultPtr result,
                                   std::stringstream &output )
{
  FUNCTION_START;

  for ( size_t i = 1; i < result->treeDepth && LogConfiguration::indentation != 0; ++i )
  {
    output << "." << std::string( LogConfiguration::indentation, ' ' );
  }

  FUNCTION_END;
}

void Logger::wrapWordsAndAddTimeStamp( const TimeSpan& timeSpan,
                                       std::stringstream &output )
{
  FUNCTION_START;

  std::string message = output.str( );
  output.str( "" );

  int remainingSpace;
  while ( 0 > ( remainingSpace = LogConfiguration::outputWidth - message.length( ) ) )
  {
    output << message.substr( 0, LogConfiguration::outputWidth ) << "\n";
    message = message.substr( LogConfiguration::outputWidth, message.length( ) );
  }
  output << message << std::string( remainingSpace, '.' ) << " " << timeSpan;

  FUNCTION_END;
}

void Logger::logMessage( const std::stringstream& output,
                         LogLevels logLevel )
{
  FUNCTION_START;

  if ( static_cast<int>( LogConfiguration::fileLogLevel ) >= static_cast<int>( logLevel ) )
  {
    writeToFile( output.str( ) );
  }
  if ( static_cast<int>( LogConfiguration::consoleLogLevel ) >= static_cast<int>( logLevel ) && LogConfiguration::silent == false )
  {
    coloredOutput( output.str( ), static_cast<int>( logLevel ) );
  }

  FUNCTION_END;
}

void Logger::writeToFile( const std::string& message )
{
  FUNCTION_START;

  if ( getOutputFileHandle( ).is_open( ) )
  {
    getOutputFileHandle( ) << std::unitbuf << message;
  }
  else
  {
#pragma omp critical( AdhocppLoggingCout )
    {
    std::cout << "opening file " << LogConfiguration::fileName << ".out failed...\n";
    }
  }

  FUNCTION_END;
}

void Logger::coloredOutput( const std::string& output,
                            int mode )
{
  FUNCTION_START;

#pragma omp critical( AdhocppLoggingCout )
  {
    if ( LogConfiguration::fancy == true && mode <= 6 && mode >= 0 )
    {
      std::cout << "\033[" << LogConfiguration::colorVector[mode] << "m" << output << "\033[0m";
    }
    else
    {
      std::cout << output;
    }
  }
  FUNCTION_END;
}

std::ofstream& Logger::getOutputFileHandle( )
{
  FUNCTION_START

  static std::ofstream outputFileHandle( LogConfiguration::fileName + ".out", std::fstream::out );

  return outputFileHandle;

FUNCTION_END
}

void Logger::unconditionalLog( const std::string& message )
{
FUNCTION_START

// for red color
LogLevels logLevel = LogLevels::ERROR;

// log without checks
coloredOutput( message, static_cast<int>( logLevel ) );

FUNCTION_END
}

} // namespace time
