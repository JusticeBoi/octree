/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_SCOPEBEHAVIOR_HPP_
#define UTILITIES_SCOPEBEHAVIOR_HPP_

#include <memory>

namespace utilities
{

class ScopeBehavior
{
public:
  ScopeBehavior( );
  virtual ~ScopeBehavior( );

  virtual void restore( );

private:
  explicit ScopeBehavior( const ScopeBehavior& );
  ScopeBehavior& operator=( const ScopeBehavior& );

};

} // namespace utilities 
#endif // UTILITIES_SCOPEBEHAVIOR_HPP_
