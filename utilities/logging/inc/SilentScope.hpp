/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_SILENTSCOPE_HPP_
#define UTILITIES_SILENTSCOPE_HPP_

// --- Internal Includes ---
#include "utilities/inc/loggingTypes.hpp"
#include "BasicScope.hpp"

// --- Std Includes ---
#include <memory>

namespace utilities
{

class SilentScope final : public BasicScope
{
public:
  SilentScope( const std::string& name );
  ~SilentScope( ) noexcept(false) override;

  void close( ) override;

  void subscope( const std::string& name );
  void closeSubscope( );

private:
  explicit SilentScope( const SilentScope& );
  SilentScope& operator=( const SilentScope& );

  BasicScopePtr mySubscope;
};

} // namespace utilities
#endif // UTILITIES_SILENTSCOPE_HPP_
