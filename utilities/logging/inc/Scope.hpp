/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_SCOPE2_HPP_
#define UTILITIES_SCOPE2_HPP_

// --- Internal Includes ---
#include "utilities/inc/loggingTypes.hpp"
#include "utilities/inc/AnonymousVariable.hpp"
#include "BasicScope.hpp"

namespace utilities
{

class Scope final : public BasicScope
{
public:
  explicit Scope( const std::string& name );
  ~Scope( ) override;

  // close the scope manually (is also done in destructor)
  void close( ) override;

  /*
   * The subscope methods open a new scope which stays open until:
   * 1. closeSubscope( ) is called
   * 2. another subscope is opened
   * 3. close( ) is called
   * 4. the destructor of the Scope object is called (which calls close( ) )
   *
   * subscope: standard subscope, behaves like Scope
   * silentSubscope: behaves like SilentScope: produces no std::cout
   * loopSubscope: prints only a loop summary when the destructor of the Scope
   *     object is called. During loop iteration no output is produced.
   *     There is also the possibility to add a progress indicator by passing
   *     startCount, currentCount, expectedCount to the function. This will
   *     produce output only if LogConfiguration::fancy is set.
   */
  void subscope( const std::string& name );
  void silentSubscope( const std::string& name );
  void loopSubscope( const std::string& name );
  void loopSubscope( const std::string& name,
                     double startCount,
                     double currentCount,
                     double expectedCount );
  void closeSubscope( );

private:
  explicit Scope( const Scope& );
  Scope& operator=( const Scope& );

  BasicScopePtr mySubScope;
  SectionResultVector myLoopResults;
};


#define LOG_SCOPE(message)                  \
utilities::Scope ANONYMOUS_VARIABLE(CURRENT_LOG_SCOPE){message}

#define SCOPED_FUNCTION_START FUNCTION_START \
  utilities::Scope macroGeneratedScope( __FUNCTION__ )

#define SCOPED_FUNCTION_END FUNCTION_END

} // namespace utilities 
#endif // UTILITIES_SCOPE2_HPP_
