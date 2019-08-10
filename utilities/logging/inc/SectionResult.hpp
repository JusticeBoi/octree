/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef utilities_SECTIONRESULT_HPP_
#define utilities_SECTIONRESULT_HPP_

// --- Std Includes ---
#include <string>

namespace utilities
{

struct SectionResult
{
  SectionResult( );
  SectionResult( std::string sectionName,
                 size_t callTreeDepth,
                 int sectionCallCount,
                 double sectionElapsedTime );

  std::string name;
  size_t treeDepth;
  int callCount;
  double elapsedTime;
};

} // namespace utilities 
#endif // utilities_SECTIONRESULT_HPP_ 
