/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_PERCENTAGE_HPP_
#define UTILITIES_PERCENTAGE_HPP_

// --- Std Includes ---
#include <ostream>

namespace utilities
{

class Percentage final
{
public:
  Percentage( );
  Percentage( int numberOfDecimals, bool printPercentageCharakter = true );
  Percentage( double ratio, int numberOfDecimals, bool printPercentageCharakter = true );
  Percentage( double numerator, double denominator, bool printPercentageCharakter = true );
  Percentage( double numerator, double denominator, int numberOfDecimals, bool printPercentageCharakter = true );

  ~Percentage( );

  void setValue( double ratio );
  void setValue( double numerator, double denominator );
  void setNumberOfDecimals( int numberOfDecimals );
  double getPercentage( ) const;

  friend std::ostream& operator<< ( std::ostream& os, const Percentage& percentage );

private:
  explicit Percentage( const Percentage& );
  Percentage& operator=( const Percentage& );

  double myPercentage;
  int myNumberOfDecimals;
  bool printPercentage;
};


} // namespace utilities
#endif // UTILITIES_PERCENTAGE_HPP_
