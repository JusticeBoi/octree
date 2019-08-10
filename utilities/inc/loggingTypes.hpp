/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_LOGGINGTYPES_HPP_
#define UTILITIES_LOGGINGTYPES_HPP_

// --- Internal Includes ---
#include <memory>
#include <string>
#include <vector>

namespace utilities
{

class Section;
typedef std::shared_ptr<Section> SectionPtr;

struct SectionResult;
typedef std::shared_ptr<SectionResult> SectionResultPtr;
typedef std::vector<SectionResultPtr> SectionResultVector;

class TimeSpan;
typedef std::shared_ptr<TimeSpan> TimeSpanPtr;

class Scope;
typedef std::shared_ptr<Scope> ScopePtr;

class BasicScope;
typedef std::shared_ptr<BasicScope> BasicScopePtr;

class ScopeBehavior;
typedef std::shared_ptr<ScopeBehavior> ScopeBehaviorPtr;

struct LoopProgressState;
typedef std::shared_ptr<LoopProgressState> LoopProgressStatePtr;

} // namespace utilities
#endif // UTILITIES_LOGGINGTYPES_HPP_
