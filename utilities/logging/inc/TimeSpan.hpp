/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_TIMESPAN_HPP_
#define UTILITIES_TIMESPAN_HPP_

// --- Std Includes ---
#include <ostream>

namespace utilities
{

class TimeSpan final
{
public:
  TimeSpan( );
  TimeSpan( double seconds );

  ~TimeSpan( );

  friend std::ostream& operator <<( std::ostream& os, const TimeSpan& timeSpan );

  double myDuration;
private:
  explicit TimeSpan( const TimeSpan& );
  TimeSpan& operator=( const TimeSpan& );

};

} // namespace utilities
#endif // UTILITIES_TIMESPAN_HPP_
