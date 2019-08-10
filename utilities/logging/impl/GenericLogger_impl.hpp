/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_GENERICLOGGER_IMPL_HPP_
#define UTILITIES_GENERICLOGGER_IMPL_HPP_

#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

template<LogLevels logLevel>
template<typename T>
GenericLogger<logLevel>& GenericLogger<logLevel>::operator <<( const T& rhs )
{
  FUNCTION_START;

  std::stringstream sstream;
  sstream << rhs;

  parseArgument( sstream.str( ) );

  return *this;

  FUNCTION_END;
}

} // namespace utilities

#endif // UTILITIES_GENERICLOGGER_IMPL_HPP_
