/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef TIME_LOGGER_HPP_
#define TIME_LOGGER_HPP_

// --- Internal Includes ---
#include "SectionResult.hpp"
#include "LogConfiguration.hpp"
#include "utilities/inc/loggingTypes.hpp"

// --- Internal Includes ---
#include <string>
#include <vector>

namespace utilities
{

class Logger final
{
public:
  /* logs the message indented (depending on current tree depth) to :
   *
   * 1. console, if consoleLogLevel is higher or equal than the given
   *    logLevel. If enableColoredOutput is set, ansi color codes are added
   *
   * 2. logHistory, which is stored on filesystem later (initiated in Timer)
   */
  static void log( const std::stringstream& message,
                   LogLevels logLevel,
                   bool addTimeStamp = false );

  /*
   * logs the message to console and logHistory, no time stamp and no indentation
   * are added. However it respects silent and on
   */
  static void simpleLog( const std::string& message );
  static void simpleLog( const std::string& message, LogLevels logLevel );

  // log message independent of silent or whatever, mainly for exceptions
  static void unconditionalLog( const std::string& message );

  // ================================== only for Timer ==========================================
  static void logScopeStart( SectionResultPtr result );         // prints starting scope line
  static void logScopeEnd( SectionResultPtr result );           // prints ending scope line

  // adds white space to the output stream
  static void getWhiteSpaceIndendation( SectionResultPtr result, std::stringstream &output );

private:
  Logger( );
  ~Logger( );

  explicit Logger( const Logger& );
  Logger& operator=( const Logger& );

  // adds scope indicating space to output stream
  static void getScopedIndendation( SectionResultPtr result, std::stringstream &output );

  // wraps words of output stream and adds the time stamp
  static void wrapWordsAndAddTimeStamp( const TimeSpan& timeSpan, std::stringstream &output );

  // loggs given message conditionally depending on log levels
  static void logMessage( const std::stringstream& output, LogLevels logLevel );

  // manages colored output, mode: an integer corresponding to indices of colorMapping
  static void coloredOutput( const std::string& output, int mode );

  // get the ouput file handle described by LogConfiguration::fileName
  static std::ofstream& getOutputFileHandle( );

  // write to file using the internal file handle provided by getOutputFileHandle( )
  static void writeToFile( const std::string& message );
};

} // namespace time 
#endif // time_LOGGER_HPP_ 
