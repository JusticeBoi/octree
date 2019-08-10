/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_LOOPEDSCOPE_HPP_
#define UTILITIES_LOOPEDSCOPE_HPP_

// --- Utilities Includes ---
#include "BasicScope.hpp"
#include "utilities/inc/loggingTypes.hpp"

namespace utilities
{

class LoopedScope final : public BasicScope
{
public:
	  LoopedScope( const std::string& name,
			  	   SectionResultPtr loopSummaryResult );

	  LoopedScope( const std::string& name,
			  	   SectionResultPtr loopSummaryResult,
			  	   LoopProgressStatePtr progressState );

  ~LoopedScope( ) override;

  void close( ) override;

  static void printLoopResult( SectionResultPtr result );
private:
  explicit LoopedScope( const LoopedScope& );
  LoopedScope& operator=( const LoopedScope& );

  SectionResultPtr myResult;
  LoopProgressStatePtr myProgress;
};

} // namespace utilities 

#endif // UTILITIES_LOOPEDSCOPE_HPP_
