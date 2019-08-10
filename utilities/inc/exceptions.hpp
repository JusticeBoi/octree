/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_EXCEPTIONS_HPP_
#define UTILITIES_EXCEPTIONS_HPP_

// --- Utilities Includes ---
#include "utilities/exceptions/inc/Exception.hpp"

// --- Boost Includes ---
#include <boost/current_function.hpp>

//-----------------------------------------------------------------------------
#define _FUNCTION BOOST_CURRENT_FUNCTION

#define _FILE __FILE__

#define _LINE __LINE__

#define _LOCATION _FUNCTION, _FILE, _LINE
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define THROW_LOCATION( message,\
                                function,\
                                file,\
                                line ) \
throw utilities::Exception( message,\
                                     function,\
                                     file,\
                                     line )

#define THROW( message ) \
throw utilities::Exception( message,\
                                     _LOCATION )
//-----------------------------------------------------------------------------

namespace utilities
{

// Forward declaration of helper functions. They are defined in Exceptions.cpp.
// We use them with external linkage to reduce compile dependencies.
void log_exception( );
void log_exception( utilities::Exception& exception );
void log_exception( const std::string& message );

} // utilities

#define TRY \
try\
{

#define CATCH \
}\
catch( utilities::Exception& exception )\
{\
  exception.addStackFrame( _LOCATION );\
  throw;\
}\
catch( std::exception& exception )\
{\
  THROW( exception.what( ) );\
}\
catch( ... )\
{\
  THROW( "unknown exception" );\
}

#define CATCH_AND_HANDLE \
}\
catch( utilities::Exception& exception )\
{\
  exception.addStackFrame( _LOCATION );\
  utilities::adhocpp_log_exception( exception );\
}\
catch( std::bad_exception& exception )\
{\
  utilities::adhocpp_log_exception( exception.what( ) );\
}\
catch( std::exception& exception )\
{\
  utilities::adhocpp_log_exception( exception.what( ) );\
}\
catch( ... )\
{\
  utilities::adhocpp_log_exception( );\
}

#define CATCH_HANDLE_AND_RETHROW \
}\
catch( utilities::Exception& exception )\
{\
  exception.addStackFrame( _LOCATION );\
  utilities::adhocpp_log_exception( exception );\
  throw;\
}\
catch( std::bad_exception& exception )\
{\
  utilities::adhocpp_log_exception( exception.what( ) );\
  throw;\
}\
catch( std::exception& exception )\
{\
  utilities::adhocpp_log_exception( exception.what( ) );\
  throw;\
}\
catch( ... )\
{\
  utilities::adhocpp_log_exception( );\
  throw;\
}

#define TRY_AND_HANDLE( expression ) \
TRY \
expression; \
CATCH_AND_HANDLE

#define TRY_HANDLE_AND_RETHROW( expression ) \
TRY \
expression; \
CATCH_HANDLE_AND_RETHROW

#endif // UTILITIES_EXCEPTIONS_HPP_
