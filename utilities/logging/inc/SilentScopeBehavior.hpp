/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_SILENTSCOPEBEHAVIOR_HPP_
#define UTILITIES_SILENTSCOPEBEHAVIOR_HPP_

// --- Internal Includes ---
#include "ScopeBehavior.hpp"
#include "utilities/inc/loggingTypes.hpp"
#include "LogConfiguration.hpp"

namespace utilities
{

class SilentScopeBehavior final : public ScopeBehavior
{
public:
  SilentScopeBehavior( );
  ~SilentScopeBehavior( ) override;

  void restore( ) override;

private:
  explicit SilentScopeBehavior( const SilentScopeBehavior& );
  SilentScopeBehavior& operator=( const SilentScopeBehavior& );

  size_t cachedDepth;
  LogLevels cachedConsoleLogLevel;
};

} // namespace utilities 
#endif // UTILITIES_SILENTSCOPEBEHAVIOR_HPP_
