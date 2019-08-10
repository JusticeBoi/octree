/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_PROGRESSINDICATOR_HPP_
#define UTILITIES_PROGRESSINDICATOR_HPP_

// --- Std Includes ---
#include <string>
#include <memory>

namespace utilities
{

struct LoopProgressState
{
	LoopProgressState( double start, double current, double end ) :
		startCount( start ),
		currentCount( current ),
		expectedCount( end )
	{

	}
  double startCount;
  double currentCount;
  double expectedCount;
};

class ProgressIndicator final
{
public:
  ProgressIndicator( const std::string& statement, size_t expectedCount );
  ProgressIndicator( const std::string& statement, size_t expectedCount, size_t startingValue );

  ~ProgressIndicator( );

  size_t operator +=( size_t increment );
  size_t operator ++( );

  static bool printProgress( const std::string& statement,
                             double startCount,
                             double currentCount,
                             double expectedCount );

private:
  explicit ProgressIndicator( const ProgressIndicator& );
  ProgressIndicator& operator=( const ProgressIndicator& );

  void printStatement( );

  std::string myStatement;
  std::string colorStart;
  std::string colorEnd;
  std::string indendation;
  size_t myExpectedCount;
  size_t count;
  bool hasFinished;
};

} // namespace utilities 
#endif // UTILITIES_PROGRESSINDICATOR_HPP_
