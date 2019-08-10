/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/LogConfiguration.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"
//#include "adhocpp_config.hpp"

// --- Std Includes ---
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <time.h>

namespace utilities
{

LogLevels LogConfiguration::consoleLogLevel = LogLevels::INFO;
LogLevels LogConfiguration::fileLogLevel = LogLevels::DEBUG;

size_t LogConfiguration::indentation = 2;
size_t LogConfiguration::outputWidth = 120;
size_t LogConfiguration::highestScopeDepthPrinted = 100;
bool LogConfiguration::deactiveScopeOutput = false;

bool LogConfiguration::deactivateLogger = false;
bool LogConfiguration::silent = false;
bool LogConfiguration::fancy = false;
bool LogConfiguration::showTimingSummary = false;
bool LogConfiguration::showProgressbar = false;
bool LogConfiguration::showLoopSummary = false;

bool LogConfiguration::catchSignals = false;
char LogConfiguration::summarySpaceCharacter = ' ';
std::string LogConfiguration::fileName = "timer";

// vector of ansi color codes for console output
std::vector<std::string> LogConfiguration::colorVector =
{
  "38;5;196", // 0 ERROR        |
  "93",       // 1 WARNING      |
  "38;5;118", // 2 INFO         | LogLevels
  "38;5;118", // 3 VERBOSE      |
  "38;5;118", // 4 DEBUG        |

  "38;5;153", // 5 scope start  |
  "38;5;75",  // 6 scope end    | Scopes

  "38;5;172", // 7 progress bar |
  "38;5;193"  // 8 loop summary | Loop Information
};

LogConfiguration::LogConfiguration( )
{
  restoreDefaults();
}

LogConfiguration::~LogConfiguration( )
{
  // This cannot throw an exception as otherwise all tests that
  // use a LogConfiguration object to restore defaults would
  // have to declare a noexcept(false) destructor, which in turn
  // would require changing this in most of testcomponents

// FUNCTION_START;

  restoreDefaults( );

// FUNCTION_END;
}

void LogConfiguration::restoreDefaults( ) noexcept
{
  // This cannot throw an exception as otherwise all tests that
  // use a LogConfiguration object to restore defaults would
  // have to declare a noexcept(false) destructor, which in turn
  // would require changing this in most of testcomponents

//  FUNCTION_START;

  consoleLogLevel = LogLevels::INFO;
  fileLogLevel = LogLevels::DEBUG;

  indentation = 2;
  outputWidth = 120;
  highestScopeDepthPrinted = 100;

  deactivateLogger = false;

  showTimingSummary = false;
  showProgressbar = false;
  showLoopSummary = false;

  summarySpaceCharacter = ' ';
  fileName = "timer";

  std::stringstream stringStream;

  stringStream <<  std::getenv( "TERM" );

  bool isRegularTerminal = stringStream.str( ).find( "xterm" ) != std::string::npos;

  fancy = isRegularTerminal;
  catchSignals = false;;

  // if fancy, show cursor, in case progress bar did not reach 100%
  if( fancy )
  {
#pragma omp critical( AdhocppLoggingCout )
    {
      std::cout << "\33[?25h\n";
    }
  }

  LogConfiguration::colorVector =
  {
    "38;5;196", // 0 ERROR        |
    "93",       // 1 WARNING      |
    "38;5;118", // 2 INFO         | LogLevels
    "38;5;118", // 3 VERBOSE      |
    "38;5;118", // 4 DEBUG        |

    "38;5;153", // 5 scope start  |
    "38;5;75",  // 6 scope end    | Scopes

    "38;5;172", // 7 progress bar |
    "38;5;193"  // 8 loop summary | Loop Information
  };

//  FUNCTION_END;
}

std::string LogConfiguration::getAdhoCppHeader( )
{
  FUNCTION_START;

  std::stringstream header;

  header << "=========================================================================================================         \n"
            "                         ____       _                                                                             \n"
            "                        / __ |     | |                                                                            \n"
            "                       | |  | | ___| |_ _ __ ___  ___                                                             \n"
            "                       | |  | |/ __| __| '__/ _ |/ _ |                                                            \n"
            "                       | |__| | (__| |_| | |  __/  __|                                                            \n"
            "                        |____| |___|___|_|  |___||___|                                                            \n"
            "                                                                                                                  \n"
            "               Logging and implicitgeometry library by Chair of Computation in Engineerin, TU Muenchen.           \n"
            "               Rest is by Oguz Oztoprak.                                                                          \n" 
            "=========================================================================================================         \n\n";

  time_t rawtime;
  time ( &rawtime );


  return header.str( );

  FUNCTION_END;
}

bool LogConfiguration::parseLogLevel( const std::string& logLevel,
                                      LogLevels& targetLogLevel )
{
  FUNCTION_START;

  /*
   * helper function for comparing the input string with existing log levels
   * 1. check if size is equal
   * 2. compare letters after converting them to lower case
   */
  auto CaseInsensitiveComparison = [] ( const std::string& str1,
                                        const std::string& str2 )
  {
    if ( str1.size( ) != str2.size( ) )
    {
        return false;
    }
    for ( std::string::const_iterator c1 = str1.begin( ), c2 = str2.begin( ); c1 != str1.end( ); ++c1, ++c2 )
    {
        if ( tolower( *c1 ) != tolower( *c2 ) )
        {
            return false;
        }
    }
    return true;
  };

  // compare log levels
  if( CaseInsensitiveComparison( logLevel, "ERROR" ) )
  {
    targetLogLevel = LogLevels::ERROR;
  }
  else if( CaseInsensitiveComparison( logLevel, "WARNING" ) )
  {
    targetLogLevel = LogLevels::WARNING;
  }
  else if( CaseInsensitiveComparison( logLevel, "INFO" ) )
  {
    targetLogLevel = LogLevels::INFO;
  }
  else if( CaseInsensitiveComparison( logLevel, "VERBOSE" ) )
  {
    targetLogLevel = LogLevels::VERBOSE;
  }
  else if( CaseInsensitiveComparison( logLevel, "DEBUG" ) )
  {
    targetLogLevel = LogLevels::DEBUG;
  }
  else
  {
    targetLogLevel = LogLevels::ERROR;
    return false;
  }

  return true;

  FUNCTION_END;
}

} // namespace utilities 
