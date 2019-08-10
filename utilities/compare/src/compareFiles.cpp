/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#include "../inc/compareFiles.hpp"
#include "utilities/inc/functionessentials.hpp"
#include "utilities/checks/inc/Check.hpp"

#include <iosfwd>
#include <fstream>
#include <string>

namespace utilities {

bool compareContentOfFiles( const std::string& outputFileName,
                            const std::string& referenceFileName )
{
  FUNCTION_START;

  std::ifstream outputFile( outputFileName.c_str( ) );
  std::ifstream referenceFile( referenceFileName.c_str( ) );

// check that the file was created
  bool outputExists = static_cast<bool>( outputFile );
  bool referenceExists = static_cast<bool>( referenceFile );

  ADHOCPP_CHECK( outputExists );
  ADHOCPP_CHECK( referenceExists );

  std::string outputString;
  std::string referenceString;

  while ( not referenceFile.eof( ) )
  {
    std::getline( outputFile, outputString );
    std::getline( referenceFile, referenceString );

    if ( outputString != referenceString )
    {
      return false;
    }
  }

  return true;

  FUNCTION_END;
}

} // namespace utilities
