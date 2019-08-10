/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_LOGCONFIGURATION_HPP_
#define UTILITIES_LOGCONFIGURATION_HPP_

// --- Std Includes ---
#include <vector>
#include <string>

namespace utilities
{

// defines levels of importance for logging
enum class LogLevels
{
  ERROR, WARNING, INFO, VERBOSE, DEBUG
};

/*
 * LogConfiguration is the place where all relevant configurations concerning
 * logging and profiling can be found. It provides static variables that can
 * be modified for custom output behavior.
 * However keep in mind that changing the value of one static variable might
 * affect more testcases. To provide a comfortable solution to this problem
 * you can create a LogConfiguration object in your testcase which will
 * automatically call restoreDefaults() in its destructor.
 */
class LogConfiguration final
{
public:
  LogConfiguration( );
  ~LogConfiguration( );

  static utilities::LogLevels consoleLogLevel;      // log level for std::cout
  static utilities::LogLevels fileLogLevel;         // log level for logHistory

  static size_t indentation;                        // number of spaces in front of logs (for each nested scope)
  static size_t outputWidth;                        // the number of characters until the time stamp is printed
  static size_t highestScopeDepthPrinted;           // until what scope tree depth scope names are printed
  static bool deactiveScopeOutput;                  // No scoped output

  static bool deactivateLogger;                     // turns Logger completely off
  static bool silent;                               // kills console output
  static bool fancy;                                // for terminal: nice output
  static bool showTimingSummary;					// show profiling results after program exit
  static bool showProgressbar;						// show a progress bar for some loops
  static bool showLoopSummary;						// show duration and call count of some loops
  static std::vector<std::string> colorVector;      // maps logLevels and Scoped output to colors

  static bool catchSignals;                         // defines if signals should be caught
  static char summarySpaceCharacter;                // the character used for filling whitespace in the profiling summary
  static std::string fileName;                      // the file base name for log files

  static void restoreDefaults( ) noexcept;          // restores all default values and checks the terminal type
  static std::string getAdhoCppHeader( );           // returns the standard AdhoC++ output header

  static bool parseLogLevel( const std::string& logLevel, // converts string to LogLevels enum, returns false if logLevel
                             LogLevels &targetLogLevel ); // could not be resolved

private:
  explicit LogConfiguration( const LogConfiguration& );
  LogConfiguration& operator=( const LogConfiguration& );

};

} // namespace utilities 
#endif // UTILITIES_LOGCONFIGURATION_HPP_
