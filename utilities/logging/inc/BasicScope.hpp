/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_ABSSCOPE_HPP_
#define UTILITIES_ABSSCOPE_HPP_

// --- Internal Includes ---
#include <string>
#include <memory>
#include "ScopeBehavior.hpp"
#include "utilities/inc/loggingTypes.hpp"

namespace utilities
{

class BasicScope
{
public:
  BasicScope( const std::string& name,
              ScopeBehaviorPtr scopeBehavior = ScopeBehaviorPtr( new ScopeBehavior ) );
  virtual ~BasicScope( ) noexcept(false);

  virtual void close( );

protected:
  ScopeBehaviorPtr myBehavior;
  std::string myName;
  bool scopeWasClosed;

private:
  explicit BasicScope( const BasicScope& );
  BasicScope& operator=( const BasicScope& );
};

} // namespace utilities 

#endif // UTILITIES_ABSSCOPE_HPP_
