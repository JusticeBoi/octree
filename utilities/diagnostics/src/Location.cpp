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
#include "../inc/Location.hpp"
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

Location::Location( ) :
  myFunction( "unknown" ),
  myFile( "unknown" ),
  myLine( 0 )
{
}

Location::Location( const std::string& function,
                    const std::string& file,                        
                    const int& line ) :
  myFunction( function ),
  myFile( file ),
  myLine( line )
{
  FUNCTION_START;

    stripFunction( );

    stripFile( );

  FUNCTION_END;
}

Location::Location( const Location& location ) :
  myFunction( location.myFunction ),
  myFile( location.myFile ),  
  myLine( location.myLine )
{
}

Location::~Location( ) throw( )
{
}

Location& Location::operator=( const Location& location )
{
  FUNCTION_START;

    if( this != &location )
    {
      myFunction = location.myFunction;

      myFile = location.myFile;

      myLine = location.myLine;
    }

    return *this;

  FUNCTION_END;
}

void Location::set( const std::string& function,
                    const std::string& file,
                    const int& line)
{
  FUNCTION_START;

    myFunction = function;

    myFile = file;

    myLine = line;

    stripFunction( );

    stripFile( );

    return;

  FUNCTION_END;
}

const std::string& Location::getFunction( ) const
{
  FUNCTION_START;

    return myFunction;

  FUNCTION_END;
}

const std::string& Location::getFile( ) const
{
  FUNCTION_START;

    return myFile;

  FUNCTION_END;
}

const int& Location::getLine( ) const
{
  FUNCTION_START;

    return myLine;

  FUNCTION_END;
}

void Location::stripFunction( )
{
  FUNCTION_START;

    size_t start = myFunction.find_first_of( "(" );

    if( start != std::string::npos )
    {
      size_t end = std::string::npos;

      myFunction.erase( start, ( end - start ) );

      myFunction += "(...)";
    }

    return;

  FUNCTION_END;
}

void Location::stripFile( )
{
  FUNCTION_START;

//    size_t end = myFile.find_last_of( "/\\" );
//
//    if( end != std::string::npos )
//    {
//      size_t start = 0;
//
//      // include slash / backslash to the characters to be erased
//      end++;
//
//      myFile.erase( start, ( end - start ) );
//    }

    return;

  FUNCTION_END;
}

std::ostream& operator<<( std::ostream& output, const Location& location )
{
  FUNCTION_START;

    output << "Location: "
           << location.getFunction( )
           << " @ "
           << location.getFile( )
           << ":"
           << location.getLine( );

      return output;

  FUNCTION_END;
}

} // utilities
