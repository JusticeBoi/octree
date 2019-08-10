/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_SCIENTIFICDOUBLE_HPP_
#define UTILITIES_SCIENTIFICDOUBLE_HPP_

// --- Std Includes ---
#include <ostream>

namespace utilities
{

class ScientificDouble final
{
public:
  ScientificDouble( );
  ScientificDouble( double doubleValue );
  ScientificDouble( double doubleValue, size_t outputPrecision );
  ~ScientificDouble( );

  friend std::ostream& operator<< ( std::ostream& os, const ScientificDouble& scientificDouble );

  std::string to_string( ) const;

  double value;
  size_t precision;
private:
  explicit ScientificDouble( const ScientificDouble& );
  ScientificDouble& operator=( const ScientificDouble& );

};

} // namespace utilities
#endif // UTILITIES_SCIENTIFICDOUBLE_HPP_
