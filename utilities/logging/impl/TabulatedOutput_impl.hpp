/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef TIME_TABULATEDOUTPUT_IMPL_HPP
#define TIME_TABULATEDOUTPUT_IMPL_HPP

// --- Std Includes ---
#include <sstream>

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

namespace utilities
{

template<typename... EntryTypes>
void TabulatedOutput::addRow( const EntryTypes&... entries )
{
  FUNCTION_START;

  std::vector<std::string> row;
  if( sizeof...(entries) != 0 )
  {
    addRow( row, entries... );
  }
  for( size_t i = row.size( ); i <= numberOfColumns; ++i )
  {
    row.push_back( "" );
  }
  myData.push_back( row );

  FUNCTION_END;
}

template<typename Arg1, typename... EntryTypes>
void TabulatedOutput::addRow( std::vector<std::string>& row, const Arg1& arg1, const EntryTypes&... entries )
{
  FUNCTION_START;

  std::stringstream entry;
  entry << arg1;
  row.push_back( entry.str( ) );

  if( sizeof...(entries) != 0 )
  {
    addRow( row, entries... );
  }
  else
  {
    return;
  }

  FUNCTION_END;
}

} // namespace utilities

#endif //TIME_TABULATEDOUTPUT_IMPL_HPP
