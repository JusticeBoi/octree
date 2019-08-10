/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/TimeSpan.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- Std Includes ---
#include <iomanip>

namespace utilities
{

TimeSpan::TimeSpan( ) :
    myDuration( 0.0 )
{
}

TimeSpan::TimeSpan( double seconds ) :
    myDuration( seconds )
{
}

TimeSpan::~TimeSpan( )
{
}

std::ostream& operator <<( std::ostream& os, const TimeSpan& timeSpan )
{
  double duration = timeSpan.myDuration;
  size_t milliSecondDigits = 2;

  size_t numberOfUnits = 5;
  std::string timeUnits[] = { "d ", "h ", "min ", "s ", "ms" };
  double multiplier[] = { 86400, 3600, 60, 1, 0.001 };

  int value;
  bool first = true;
  for( size_t unit = 0; unit < numberOfUnits - 1; ++unit)
  {
    if( 0 < ( value = duration / multiplier[unit] ) )
    {
      if( first == false )
      {
        os << std::setfill('0') << std::setw(2);
      }
      else
      {
        first = false;
      }
      os << value << timeUnits[unit];
      duration -= value * multiplier[unit];
    }
  }
  if( first == false )
  {
    os << std::setfill( '0' ) << std::setw( 4 + milliSecondDigits );
  }
  os << std::fixed << std::setprecision( milliSecondDigits ) << duration /
      multiplier[numberOfUnits - 1] << timeUnits[numberOfUnits - 1];

  return os << "";
}

} // namespace utilities
