/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

// --- Standard Includes ---
#include <exception>
#include <string>
#include <memory>

namespace utilities
{

class Location;
class CallStack;

class Exception final : public virtual std::exception
{
public:
  Exception( const std::string& message,
             const std::string& function,
             const std::string& file,
             const int& line ) throw ( );

  Exception( const std::string& message,
             const Location& location ) throw ( );

  Exception( const Exception& object ) throw ( );

  ~Exception( ) throw ( ) override;

  Exception& operator=( const Exception& object ) throw ( );

  const char* what( ) const noexcept override;

  const std::string& getMessage( ) const throw ( );

  const Location& getLocation( ) const throw ( );

  CallStack& getCallStack( ) throw ( );
  const CallStack& getCallStack( ) const throw ( );

  void addStackFrame( const std::string& function,
                              const std::string& file,
                              const int& line );

private:
  struct ExceptionImplementation;
  std::shared_ptr<ExceptionImplementation> myImplementation;
};

std::ostream& operator<<( std::ostream& output,
                          const Exception& exception ) throw ( );

}  // utilities

#endif // EXCEPTION_HPP_
