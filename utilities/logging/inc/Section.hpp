/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_SECTION_HPP_
#define UTILITIES_SECTION_HPP_

// --- Internal Includes ---
#include "utilities/inc/loggingTypes.hpp"
#include "SectionResult.hpp"

// --- Std Includes ---
#include <string>
#include <vector>
#include <memory>
#include <sstream>

// --- Boost Includes ---
#include <boost/timer/timer.hpp>

namespace utilities
{

/*
 * Objects of the Section class build a tree representing the call
 * structure of the code. Every Section object has a std::vector
 * member storing sub-sections opened during the time the object
 * was active. The tree could look like this:
 *
 *
 *         globalSection          myCallTreeDepth = 0
 *              |
 *              |
 *              <>
 *             main               myCallTreeDepth = 1
 *            /   \
 *           /     \
 *          <>      <>
 *    funtion1    function2       myCallTreeDepth = 2
 *    /  |  \      /  |  \
 *  ... ... ... ...  ... ...      myCallTreeDepth = 3
 */
class Section final
{
public:
  Section( const std::string& name, double callTreeDepth );
  ~Section( );

 /*
  * The start() method
  *   1. searches for active sections in the sub-section vector by
  *      checking its isActive flag. If one was found the start() call
  *      is simply forwarded. The function returns after that.
  *   2. checks for sub-sections with the same name. In that case its
  *      resume() method is called and the function returns.
  *   3. creates a new Section and push_back the object.
  * start() and getDepthOfActiveSection() return both the current state
  * of the last active section.
  */
  SectionResultPtr start( const std::string& name );
  SectionResultPtr getStateOfActiveSection( ) const;

 /*
  * end() forwards the call through the active tree until the last/
  * deepest active section is reached. This section is then set
  * inactive and the timer stopped.
  */
  SectionResultPtr end( );

 /*
  * finish() sets the Section object and recursively all sub-sections
  * inactive.
  * finalize() adds the sections results to the resultVector and calls
  * finalize() of all sub-sections.
  */
  void finish( );
  void finalize( std::vector<SectionResult>& resultVector ) const;

private:
  explicit Section( const Section &obj );
  Section& operator=( const Section& );

  // activates section
  void resume( );
  // returns the results gained until now of this section
  SectionResult& getCurrentState( SectionResult& result ) const;

  // conceptual members
  bool isActive;
  const std::string myName;
  std::vector<std::shared_ptr<Section>> myCallTree;
  size_t myCallTreeDepth;

  // timing/profiling members
  size_t callCount;
  boost::timer::cpu_timer cpuTimer;
  double timeAtLastStart;
};

} // namespace utilities

#endif // UTILITIES_SECTION_HPP_
