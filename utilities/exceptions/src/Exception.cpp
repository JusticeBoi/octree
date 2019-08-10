/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Utilities Includes ---
#include "../inc/Exception.hpp"
#include "utilities/inc/diagnostics.hpp"
#include "utilities/inc/logging.hpp"
#include <iosfwd>
#include <cstring>

namespace utilities
{

void log_exception( )
{
  utilities::logException( "Exception caught\n"
      "Diagnostics:\n"
      "unknown exception\n" );
}

void log_exception( utilities::Exception& exception )
{
  std::stringstream sStream;
  sStream << "Exception caught\n" << "Diagnostics:\n" << exception << "\n\n" << exception.getCallStack( );

  utilities::logException( sStream.str( ) );
}

void log_exception( const std::string& message )
{
  std::stringstream sStream;
  sStream << "Exception caught\n"
      "Diagnostics:\n" << message << "\n";
  utilities::logException( sStream.str( ) );
}

struct Exception::ExceptionImplementation
{
  ExceptionImplementation( const std::string& message,
                           const Location& location ) :
          myMessage( message ),
          myLocation( location )
  {
  }

  std::string myMessage;

  Location myLocation;

  CallStack myCallStack;

  std::string myOutputString;

  const std::string& getOutputString()
  {
   std::stringstream output;
   output << "adhocpp::utilities::Exception" << "\n\n\t" << myLocation;

    if ( myMessage != "" )
    {
      output << "\n\t" << "Cause: " << myMessage << "\n";
    }

    output << "\n" << myCallStack << "\n";
   
    myOutputString = output.str( );
    return myOutputString;
  }
};

Exception::Exception( const std::string& message,
                      const std::string& function,
                      const std::string& file,
                      const int& line ) throw ( )
try :
        std::exception( ),
        myImplementation( new ExceptionImplementation( message, Location( function, file, line ) ) )
{
}
catch ( ... )
{
}

Exception::Exception( const std::string& message,
                      const Location& location ) throw ( )
try :
        std::exception( ),
        myImplementation( new ExceptionImplementation( message, location ) )

{
}
catch ( ... )
{
}

Exception::Exception( const Exception& object ) throw ( )
try :
        std::exception( object ),
        myImplementation( object.myImplementation )
{
}
catch ( ... )
{
}

Exception::~Exception( ) throw ( )
{
}

Exception& Exception::operator=( const Exception& object ) throw ( )
{
  if ( this != &object )
  {
    std::exception::operator=( object );

    myImplementation = object.myImplementation;
  }

  return *this;
}

const char* Exception::what( ) const noexcept
{
  try
  {
    return myImplementation->getOutputString().c_str();
  }
  catch ( ... )
  {
    return "";
  }
}

const std::string& Exception::getMessage( ) const throw ( )
{
  return myImplementation->myMessage;
}

const Location& Exception::getLocation( ) const throw ( )
{
  return myImplementation->myLocation;
}

CallStack& Exception::getCallStack( ) throw ( )
{
  return myImplementation->myCallStack;
}

const CallStack& Exception::getCallStack( ) const throw ( )
{
  return myImplementation->myCallStack;
}

void Exception::addStackFrame( const std::string& function,
                               const std::string& file,
                               const int& line )
{
  myImplementation->myCallStack.addStackFrame( function, file, line );
}

std::ostream& operator<<( std::ostream& output,
                          const Exception& exception ) throw ( )
{
  output << exception.what( ) << "\n\n\t" << exception.getLocation( );

if ( exception.getMessage( ) != "" )
  {
    output << "\n\t" << "Cause: " << exception.getMessage( ) << "\n";
  }

  output << std::endl << exception.getCallStack( ) << "\n";

  return output;
}

} // utilities
