/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/ScientificDouble.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- Std Includes ---
#include <iomanip>
#include <sstream>

namespace utilities
{

ScientificDouble::ScientificDouble( ) :
    value( 0.0 ),
    precision( 3 )
{
}

ScientificDouble::ScientificDouble( double doubleValue ) :
    value( doubleValue ),
    precision( 5 )
{
}

ScientificDouble::ScientificDouble( double doubleValue, size_t outputPrecision ) :
    value( doubleValue ),
    precision( outputPrecision )
{
}

ScientificDouble::~ScientificDouble( )
{
}

std::ostream& operator<< ( std::ostream& os, const ScientificDouble& scientificDouble )
{
  FUNCTION_START;

  return os << std::setprecision( scientificDouble.precision )
      << std::scientific << scientificDouble.value;

  FUNCTION_END;
}
std::string ScientificDouble::to_string( ) const
{
  FUNCTION_START;

  std::stringstream sStream;

  sStream << *this;

  return sStream.str( );

  FUNCTION_END;
}


} // namespace utilities

