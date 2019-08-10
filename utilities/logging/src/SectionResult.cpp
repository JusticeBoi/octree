/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/SectionResult.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

SectionResult::SectionResult( ) :
  name( "unnamedSectionResult" ),
  treeDepth( 0 ),
  callCount( 0 ),
  elapsedTime( 0.0 )
{
}

SectionResult::SectionResult( std::string sectionName,
                              size_t callTreeDepth,
                              int sectionCallCount,
                              double sectionElapsedTime ) :
    name( sectionName ),
    treeDepth( callTreeDepth ),
    callCount( sectionCallCount ),
    elapsedTime( sectionElapsedTime )
{
}

} // namespace utilities 

