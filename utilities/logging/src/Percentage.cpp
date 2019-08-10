/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/Percentage.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- Std Includes ---
#include <iomanip>

namespace utilities
{

Percentage::Percentage( ) :
    myPercentage( 0 ),
    myNumberOfDecimals( 3 ),
    printPercentage( true )

{
}

Percentage::Percentage( int numberOfDecimals,
                        bool printPercentageCharakter ) :
    myPercentage( 0 ),
    myNumberOfDecimals( numberOfDecimals ),
    printPercentage( printPercentageCharakter )
{
}

Percentage::Percentage( double ratio,
                        int numberOfDecimals,
                        bool printPercentageCharakter ) :
    myPercentage( ratio * 100 ),
    myNumberOfDecimals( numberOfDecimals ),
    printPercentage( printPercentageCharakter )
{
}

Percentage::Percentage( double numerator,
                        double denominator,
                        bool printPercentageCharakter ) :
    myPercentage( numerator / denominator * 100 ),
    myNumberOfDecimals( 3 ),
    printPercentage( printPercentageCharakter )
{
}

Percentage::Percentage( double numerator,
                        double denominator,
                        int numberOfDecimals,
                        bool printPercentageCharakter ) :
    myPercentage( numerator / denominator * 100 ),
    myNumberOfDecimals( numberOfDecimals ),
    printPercentage( printPercentageCharakter )
{
}

Percentage::~Percentage( )
{
}

void Percentage::setValue( double ratio )
{
  FUNCTION_START;

  myPercentage = ratio * 100;

  FUNCTION_END;
}

void Percentage::setNumberOfDecimals( int numberOfDecimals )
{
  FUNCTION_START;

  myNumberOfDecimals = numberOfDecimals;

  FUNCTION_END;
}

double Percentage::getPercentage( ) const
{
  FUNCTION_START;

  return myPercentage;

  FUNCTION_END;
}

void Percentage::setValue( double numerator,
                           double denominator )
{
  myPercentage = numerator / denominator * 100;
}

std::ostream& operator <<( std::ostream& os, const Percentage& percentage )
{
  FUNCTION_START;

  os << std::fixed << std::setprecision( percentage.myNumberOfDecimals )
      << percentage.myPercentage;

  if( percentage.printPercentage )
  {
    os << " %";
  }

  return os;

  FUNCTION_END;
}

} // namespace utilities
