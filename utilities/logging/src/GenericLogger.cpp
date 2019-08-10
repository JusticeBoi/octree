/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/GenericLogger.hpp"
#include "../inc/Logger.hpp"
//#include "../impl/GenericLogger_impl.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

template<LogLevels logLevel>
GenericLogger<logLevel>::GenericLogger( )
{
}

template<LogLevels logLevel>
GenericLogger<logLevel>::~GenericLogger( )
{
}

template<LogLevels logLevel>
void GenericLogger<logLevel>::parseArgument( const std::string& arg )
{
  FUNCTION_START;

  size_t pos = arg.find( "\n" );
   if( pos != std::string::npos )
   {
     buffer << arg.substr( 0, pos );
     Logger::log( buffer, logLevel );
     buffer.str( "" );

     if( arg.size( ) > pos + 1 )
     {
       parseArgument( arg.substr( pos + 1 ) );
     }
   }
   else
   {
     buffer << arg;
   }

  FUNCTION_END;
}

void log( const std::string& message )
{
  FUNCTION_START;

  Logger::simpleLog( message );

  FUNCTION_END;
}

void log( const std::string& message,
          utilities::LogLevels logLevel )
{
  FUNCTION_START;

  Logger::simpleLog( message, logLevel );

  FUNCTION_END;
}

void logException( const std::string& message )
{
  FUNCTION_START;

  Logger::unconditionalLog( message );

  FUNCTION_END;
}

template class GenericLogger<LogLevels::ERROR>;
template class GenericLogger<LogLevels::WARNING>;
template class GenericLogger<LogLevels::INFO>;
template class GenericLogger<LogLevels::VERBOSE>;
template class GenericLogger<LogLevels::DEBUG>;

GenericLogger<LogLevels::ERROR> ErrorLogger;
GenericLogger<LogLevels::WARNING> WarningLogger;
GenericLogger<LogLevels::INFO> InfoLogger;
GenericLogger<LogLevels::VERBOSE> VerboseLogger;
GenericLogger<LogLevels::DEBUG> DebugLogger;

} // namespace utilities

