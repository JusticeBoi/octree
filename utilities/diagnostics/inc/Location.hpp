/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef LOCATION_HPP_
#define LOCATION_HPP_

// --- Standard Includes ---
#include <string>
#include <iostream>

namespace utilities
{

class Location final
{
  public:
    Location( );

    Location( const std::string& function,
              const std::string& file,
              const int& line );

    Location( const Location& location );

    ~Location( ) throw( );

    Location& operator=( const Location& location );

    void set( const std::string& function,
                      const std::string& file,
                      const int& line);

    const std::string& getFunction( ) const;

    const std::string& getFile( ) const;

    const int& getLine( ) const;

  protected:    
    std::string myFunction;

    std::string myFile;

    int myLine;

  private:
    void stripFunction( );

    void stripFile( );
};

std::ostream& operator<<( std::ostream& output, const Location& location );

} // utilities

#endif // LOCATION_HPP_
