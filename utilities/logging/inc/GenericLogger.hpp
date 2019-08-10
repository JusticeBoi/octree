/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_GENERICLOGGER_HPP_
#define UTILITIES_GENERICLOGGER_HPP_

// --- Internal Includes ---
#include "utilities/inc/loggingTypes.hpp"
#include "SectionResult.hpp"
#include "LogConfiguration.hpp"

// --- Std Includes ---
#include <string>
#include <sstream>


namespace utilities
{

/*
 * Generic Logger is the Interface for logging information to the
 * console (and files). It works pretty much the same way as cout,
 * except that you need to end your log statement with "\n". This
 * will flush the buffer and send its content to utilities::Logger.
 * The template parameter of GenericLogger specifies the LogLevel.
 * LogLevels for files and console can be changed in
 * utilities::LogConfiguration.
 */
template<LogLevels logLevel>
class GenericLogger final
{
public:
  GenericLogger( );
  ~GenericLogger( );

  // parses a new argument for \n
  void parseArgument( const std::string& arg );

  // enables logging via shift operator
  template<typename T>
  GenericLogger& operator <<( const T& rhs );
private:
  explicit GenericLogger( const GenericLogger& logger );
  GenericLogger& operator =( const GenericLogger& logger );

  // stores logged content until a \n is found
  std::stringstream buffer;
};

// extern template instantiation
extern template class GenericLogger<LogLevels::ERROR>;
extern template class GenericLogger<LogLevels::WARNING>;
extern template class GenericLogger<LogLevels::INFO>;
extern template class GenericLogger<LogLevels::VERBOSE>;
extern template class GenericLogger<LogLevels::DEBUG>;

// extern GenericLogger declarations for each LogLevel
extern GenericLogger<LogLevels::ERROR> ErrorLogger;
extern GenericLogger<LogLevels::WARNING> WarningLogger;
extern GenericLogger<LogLevels::INFO> InfoLogger;
extern GenericLogger<LogLevels::VERBOSE> VerboseLogger;
extern GenericLogger<LogLevels::DEBUG> DebugLogger;

// sends simple log statements without scoped indentation
void log( const std::string& message );
void log( const std::string& message, utilities::LogLevels logLevel );
void logException( const std::string& message );

} // namespace utilities

#include "../impl/GenericLogger_impl.hpp"

#endif // UTILITIES_GENERICLOGGER_HPP_
