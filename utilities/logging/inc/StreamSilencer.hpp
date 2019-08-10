/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2016, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_LIBRARIES_UTILITIES_PACKAGES_LOGGING_INC_STREAMSILENCER_HPP_
#define UTILITIES_LIBRARIES_UTILITIES_PACKAGES_LOGGING_INC_STREAMSILENCER_HPP_

#include <sstream>
#include <ostream>

namespace utilities {

class StreamSilencer
{
public:
  StreamSilencer( std::ostream& stream );

  ~StreamSilencer( );

  explicit StreamSilencer( const StreamSilencer& ) = delete;
  StreamSilencer& operator=( const StreamSilencer& ) = delete;

  const std::stringstream& getSuppressedContent( ) const;

private:
  std::ostream& myStream;
  std::stringstream myTempStream;
  std::streambuf *myOriginalStream;
};

} // namespace utilities 
#endif // UTILITIES_LIBRARIES_UTILITIES_PACKAGES_LOGGING_INC_STREAMSILENCER_HPP_
