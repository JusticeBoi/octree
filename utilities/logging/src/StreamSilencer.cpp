/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2016, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Internal Includes ---
#include "../inc/StreamSilencer.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities {

StreamSilencer::StreamSilencer( std::ostream& stream ) :
        myStream( stream )
{
  myOriginalStream = stream.rdbuf( myTempStream.rdbuf( ) );
}

StreamSilencer::~StreamSilencer( )
{
  myStream.rdbuf( myOriginalStream );
}

const std::stringstream& StreamSilencer::getSuppressedContent( ) const
{
  return myTempStream;
}

} // namespace utilities
