/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef TIME_TIMER_HPP_
#define TIME_TIMER_HPP_

// --- Internal Includes ---
#include "utilities/inc/loggingTypes.hpp"
#include "SectionResult.hpp"

// --- Std Includes ---
#include <ostream>
#include <sstream>

namespace utilities
{

class Timer final
{
public:
  ~Timer( ) noexcept(false);

  /*
   * start: start a new section with a given name
   * end: end the deepest active section in the section tree
   * getStateOfActiveSection: get data for the current active
   *   section in the globalSection tree
   */
  void start( const std::string& name );
  SectionResultPtr end( );
  SectionResultPtr getStateOfActiveSection( ) const;

  // checkpoint is always executed in log, start and end
  static void checkpoint( );

  /*
   * get the Timer instance ( -->singleton pattern )
   */
  static Timer& instance( );

private:
  Timer( );
  explicit Timer( const Timer &obj );
  Timer& operator=( const Timer& );

  // handles SIGABRT, SIGTERM and SIGINT if catchSignals is set
  static void sighandler( int signal );

  // finalize results gained so far
  void finalize( ) const;

  /*
   * abort: if set, program will be finalized and terminated at the next checkpoint() call
   * globalSection: represents the highest scope and holds the whole section tree
   * firstStart: is true until start() is called the first time
   */
  static bool abort;
  SectionPtr globalSection;
  bool firstStart;
};

} // namespace time

#endif // TIME_TIMER_HPP_
