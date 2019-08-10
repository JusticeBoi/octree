/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2013, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_CHECK_HPP_
#define UTILITIES_CHECK_HPP_

// --- Standard Includes ---
#include <cmath>
#include <string>
#include <limits>
#include <sstream>

// --- Utilities Includes ---
#include "utilities/inc/compare.hpp"

// can not include conversion as this would introduce nasty
// circular dependencies ... even with the include guard
#include "utilities/inc/stringify.hpp"

#include "utilities/inc/exceptions.hpp"

/**
 * Minimum tolerance macro to be used in ADHOCPP_CHECK_*_NEAR_* macros or
 * check*Near functions instead of a specified value.
 */
const double ADHOCPP_MIN_DOUBLE_TOLERANCE __attribute__((unused)) = utilities::minimumTolerance<double>( );

/*
 * Calling check function templates includes creating string objects, which is
 * very expensive. Thus, the following macros include pre-checking conditionals
 * to prevent unnecessary calls, ie call the function templates only if they
 * are going to fail.
 */

/**
 * Checks if an expression is true. If not, an exception is thrown with a
 * corresponding message given by the user.
 * @param expression Expression to be checked
 * @param message Message to be logged
 */

#define ADHOCPP_CHECK_MSG( expression,\
                           message ) \
if( !( expression ) ) \
utilities::check( #expression,\
                           expression,\
                           _LOCATION,\
                           message )

/**
 * Checks if an expression is true. If not, an exception is thrown.
 * @param expression Expression to be checked
 */
#define ADHOCPP_CHECK( expression ) \
ADHOCPP_CHECK_MSG( expression,\
                   "")

/**
 * Checks if the left value is equal to the right value. If not, an exception is
 * thrown with a corresponding message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_EQUAL_MSG( leftValue,\
                                 rightValue,\
                                 message ) \
if( ( leftValue ) != ( rightValue ) ) \
utilities::checkEqual( #leftValue,\
                                leftValue,\
                                #rightValue,\
                                rightValue,\
                                _LOCATION,\
                                message )

/**
 * Checks if the left value is equal to the right value. If not, an exception is
 * thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 */
#define ADHOCPP_CHECK_EQUAL( leftValue,\
                             rightValue ) \
ADHOCPP_CHECK_EQUAL_MSG( leftValue,\
                         rightValue,\
                         "" )

/**
 * Checks if the left value is equal to the right value, given a certain
 * tolerance. If not, an exception is thrown with a corresponding message given
 * by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_NEAR_MSG( leftValue,\
                                rightValue,\
                                tolerance,\
                                message ) \
if( std::abs( leftValue - rightValue ) > std::abs( tolerance ) ) \
utilities::checkNear( #leftValue,\
                               leftValue,\
                               #rightValue,\
                               rightValue,\
                               tolerance,\
                               _LOCATION,\
                               message )

/**
 * Checks if the left value is equal to the right value, given a certain
 * tolerance. If not, an exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 */
#define ADHOCPP_CHECK_NEAR( leftValue,\
                            rightValue,\
                            tolerance ) \
ADHOCPP_CHECK_NEAR_MSG( leftValue,\
                        rightValue,\
                        tolerance,\
                        "" )

/**
 * Checks if the left value is not equal to the right value. If they are equal,
 * an exception is thrown with a corresponding message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_NOT_EQUAL_MSG( leftValue,\
                                     rightValue,\
                                     message ) \
if( leftValue == rightValue ) \
utilities::checkNotEqual( #leftValue,\
                                   leftValue,\
                                   #rightValue,\
                                   rightValue,\
                                   _LOCATION,\
                                   message )

/**
 * Checks if the left value is not equal to the right value. If they are equal,
 * an exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 */
#define ADHOCPP_CHECK_NOT_EQUAL( leftValue,\
                                 rightValue ) \
ADHOCPP_CHECK_NOT_EQUAL_MSG( leftValue,\
                             rightValue,\
                             "" )

/**
 * Checks if the left value is not equal to the right value, given a certain
 * tolerance. If they are equal, an exception is thrown with a corresponding
 * message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_NOT_NEAR_MSG( leftValue,\
                                    rightValue,\
                                    tolerance,\
                                    message ) \
if( std::abs( leftValue - rightValue ) <= std::abs( tolerance ) ) \
utilities::checkNotNear( #leftValue,\
                                  leftValue,\
                                  #rightValue,\
                                  rightValue,\
                                  tolerance,\
                                  _LOCATION,\
                                  message )

/**
 * Checks if the left value is not equal to the right value, given a certain
 * tolerance. If they are equal, an exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 */
#define ADHOCPP_CHECK_NOT_NEAR( leftValue,\
                                rightValue,\
                                tolerance ) \
ADHOCPP_CHECK_NOT_NEAR_MSG( leftValue,\
                            rightValue,\
                            tolerance,\
                            "" )

/**
 * Checks if the left value is greater than the right value. If not, an
 * exception is thrown with a corresponding message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_GREATER_MSG( leftValue,\
                                   rightValue,\
                                   message ) \
if( leftValue <= rightValue ) \
utilities::checkGreater( #leftValue,\
                                  leftValue,\
                                  #rightValue,\
                                  rightValue,\
                                  _LOCATION,\
                                  message )

/**
 * Checks if the left value is greater than the right value. If not, an
 * exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 */
#define ADHOCPP_CHECK_GREATER( leftValue,\
                               rightValue ) \
ADHOCPP_CHECK_GREATER_MSG( leftValue,\
                           rightValue,\
                           "" )

/**
 * Checks if the left value is greater than or equal to the right value. If not,
 * an exception is thrown with a corresponding message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_GREATER_EQUAL_MSG( leftValue,\
                                         rightValue,\
                                         message ) \
if( leftValue < rightValue ) \
utilities::checkGreaterEqual( #leftValue,\
                                       leftValue,\
                                       #rightValue,\
                                       rightValue,\
                                       _LOCATION,\
                                       message )

/**
 * Checks if the left value is greater than or equal to the right value. If not,
 * an exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 */
#define ADHOCPP_CHECK_GREATER_EQUAL( leftValue,\
                                     rightValue ) \
ADHOCPP_CHECK_GREATER_EQUAL_MSG( leftValue,\
                                 rightValue,\
                                 "" )

/**
 * Checks if the left value is greater than or equal to the right value, given a
 * certain tolerance. If not, an exception is thrown with a corresponding
 * message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_GREATER_NEAR_MSG( leftValue,\
                                        rightValue,\
                                        tolerance,\
                                        message ) \
if( leftValue < rightValue ) \
utilities::checkGreaterNear( #leftValue,\
                                      leftValue,\
                                      #rightValue,\
                                      rightValue,\
                                      tolerance,\
                                      _LOCATION,\
                                      message )

/**
 * Checks if the left value is greater than or equal to the right value, given a
 * certain tolerance. If not, an exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 */
#define ADHOCPP_CHECK_GREATER_NEAR( leftValue,\
                                    rightValue,\
                                    tolerance ) \
ADHOCPP_CHECK_GREATER_NEAR_MSG( leftValue,\
                                rightValue,\
                                tolerance,\
                                "" )

/**
 * Checks if the left value is less than the right value. If not, an exception
 * is thrown with a corresponding message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_LESS_MSG( leftValue,\
                                rightValue,\
                                message ) \
if( leftValue >= rightValue ) \
utilities::checkLess( #leftValue,\
                               leftValue,\
                               #rightValue,\
                               rightValue,\
                               _LOCATION,\
                               message )

/**
 * Checks if the left value is less than the right value. If not, an exception
 * is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 */
#define ADHOCPP_CHECK_LESS( leftValue,\
                            rightValue ) \
ADHOCPP_CHECK_LESS_MSG( leftValue,\
                        rightValue,\
                        "" )

/**
 * Checks if the left value is less than or equal to the right value. If not,
 * an exception is thrown with a corresponding message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_LESS_EQUAL_MSG( leftValue,\
                                      rightValue,\
                                      message ) \
if( leftValue > rightValue ) \
utilities::checkLessEqual( #leftValue,\
                                    leftValue,\
                                    #rightValue,\
                                    rightValue,\
                                    _LOCATION,\
                                    message )

/**
 * Checks if the left value is less than or equal to the right value. If not,
 * an exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 */
#define ADHOCPP_CHECK_LESS_EQUAL( leftValue,\
                                  rightValue ) \
ADHOCPP_CHECK_LESS_EQUAL_MSG( leftValue,\
                              rightValue,\
                              "" )

/**
 * Checks if the left value is less than or equal to the right value, given a
 * certain tolerance. If not, an exception is thrown with a corresponding
 * message given by the user.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 * @param message Message to be logged
 */
#define ADHOCPP_CHECK_LESS_NEAR_MSG( leftValue,\
                                     rightValue,\
                                     tolerance,\
                                     message ) \
if( leftValue > rightValue ) \
utilities::checkLessNear( #leftValue,\
                                   leftValue,\
                                   #rightValue,\
                                   rightValue,\
                                   tolerance,\
                                   _LOCATION,\
                                   message )

/**
 * Checks if the left value is less than or equal to the right value, given a
 * certain tolerance. If not, an exception is thrown.
 * @param leftValue Left value
 * @param rightValue Right value
 * @param tolerance Tolerance value
 */
#define ADHOCPP_CHECK_LESS_NEAR( leftValue,\
                                 rightValue,\
                                 tolerance ) \
ADHOCPP_CHECK_LESS_NEAR_MSG( leftValue,\
                             rightValue,\
                             tolerance,\
                             "" )

namespace utilities
{

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_MSG or ADHOCPP_CHECK. The reason is that these macros
 * perform pre-checking that makes them a lot faster than calling this function
 * directly and, additionally, they are able to fill in automatically diagnostic
 * messages.
 * 
 * Checks if an expression is true. If not, an exception is thrown with
 * corresponding diagnostic information. 
 * @param expressionString The expression stringified in order to be part of the
 * diagnostic message.
 * @param expressionValue The value of the expression to be checked.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void check( const std::string& expressionString,
            const T& expressionValue,
            const std::string& function,
            const std::string& file,
            const int& line,
            const std::string& failMessage )
{
  if ( !expressionValue )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << expressionString << "{" << stringify( !expressionValue ) << "}";

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_EQUAL_MSG or ADHOCPP_CHECK_EQUAL. The reason is that
 * these macros perform pre-checking that makes them a lot faster than calling
 * this function directly and, additionally, they are able to fill in
 * automatically diagnostic messages.
 * 
 * Checks if the left value is equal to the right value. If not, an exception is
 * thrown with corresponding diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkEqual( const std::string& leftVariable,
                 const T& leftValue,
                 const std::string& rightVariable,
                 const T& rightValue,
                 const std::string& function,
                 const std::string& file,
                 const int& line,
                 const std::string& failMessage )
{
  if ( leftValue != rightValue )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " == "
        << rightVariable << "{" << stringify( rightValue ) << "}";

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

void checkEqual( const std::string& leftVariable,
                 const int& leftValue,
                 const std::string& rightVariable,
                 const size_t& rightValue,
                 const std::string& function,
                 const std::string& file,
                 const int& line,
                 const std::string& failMessage );

void checkEqual( const std::string& leftVariable,
                 const size_t& leftValue,
                 const std::string& rightVariable,
                 const int& rightValue,
                 const std::string& function,
                 const std::string& file,
                 const int& line,
                 const std::string& failMessage );

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_NEAR_MSG or ADHOCPP_CHECK_NEAR. The reason is that
 * these macros perform pre-checking that makes them a lot faster than calling
 * this function directly and, additionally, they are able to fill in
 * automatically diagnostic messages.
 * 
 * Checks if the left value is equal to the right value, given a certain
 * tolerance. If not, an exception is thrown with corresponding diagnostic
 * information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param tolerance The given tolerance for the check.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkNear( const std::string& leftVariable,
                const T& leftValue,
                const std::string& rightVariable,
                const T& rightValue,
                const T& tolerance,
                const std::string& function,
                const std::string& file,
                const int& line,
                const std::string& failMessage )
{
  if ( !compareEqual( leftValue, rightValue, tolerance ) )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " == "
        << rightVariable << "{" << stringify( rightValue ) << "}" << " with tolerance: " << stringify( tolerance );

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_NOT_EQUAL_MSG or ADHOCPP_CHECK_NOT_EQUAL. The reason is
 * that these macros perform pre-checking that makes them a lot faster than
 * calling this function directly and, additionally, they are able to fill in
 * automatically diagnostic messages.
 * 
 * Checks if the left value is not equal to the right value. If they are equal,
 * an exception is thrown with corresponding diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkNotEqual( const std::string& leftVariable,
                    const T& leftValue,
                    const std::string& rightVariable,
                    const T& rightValue,
                    const std::string& function,
                    const std::string& file,
                    const int& line,
                    const std::string& failMessage )
{
  if ( leftValue == rightValue )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " != "
        << rightVariable << "{" << stringify( rightValue ) << "}";

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

void checkNotEqual( const std::string& leftVariable,
                    const int& leftValue,
                    const std::string& rightVariable,
                    const size_t& rightValue,
                    const std::string& function,
                    const std::string& file,
                    const int& line,
                    const std::string& failMessage );

void checkNotEqual( const std::string& leftVariable,
                    const size_t& leftValue,
                    const std::string& rightVariable,
                    const int& rightValue,
                    const std::string& function,
                    const std::string& file,
                    const int& line,
                    const std::string& failMessage );

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_NOT_NEAR_MSG or ADHOCPP_CHECK_NOT_NEAR. The reason is
 * that these macros perform pre-checking that makes them a lot faster than
 * calling this function directly and, additionally, they are able to fill in
 * automatically diagnostic messages.
 * 
 * Checks if the left value is not equal to the right value, given a certain
 * tolerance. If they are equal, an exception is thrown with corresponding
 * diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param tolerance The given tolerance for the check.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkNotNear( const std::string& leftVariable,
                   const T& leftValue,
                   const std::string& rightVariable,
                   const T& rightValue,
                   const T& tolerance,
                   const std::string& function,
                   const std::string& file,
                   const int& line,
                   const std::string& failMessage )
{
  if ( compareEqual( leftValue, rightValue, tolerance ) )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " != "
        << rightVariable << "{" << stringify( rightValue ) << "}" << " with tolerance: " << stringify( tolerance );

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_GREATER_MSG or ADHOCPP_CHECK_GREATER. The reason is
 * that these macros perform pre-checking that makes them a lot faster than
 * calling this function directly and, additionally, they are able to fill in
 * automatically diagnostic messages.
 * 
 * Checks if the left value is greater than the right value. If not, an 
 * exception is thrown with corresponding diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkGreater( const std::string& leftVariable,
                   const T& leftValue,
                   const std::string& rightVariable,
                   const T& rightValue,
                   const std::string& function,
                   const std::string& file,
                   const int& line,
                   const std::string& failMessage )
{
  if ( leftValue <= rightValue )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " > "
        << rightVariable << "{" << stringify( rightValue ) << "}";

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

void checkGreater( const std::string& leftVariable,
                   const int& leftValue,
                   const std::string& rightVariable,
                   const size_t& rightValue,
                   const std::string& function,
                   const std::string& file,
                   const int& line,
                   const std::string& failMessage );

void checkGreater( const std::string& leftVariable,
                   const size_t& leftValue,
                   const std::string& rightVariable,
                   const int& rightValue,
                   const std::string& function,
                   const std::string& file,
                   const int& line,
                   const std::string& failMessage );

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_GREATER_EQUAL_MSG or ADHOCPP_CHECK_GREATER_EQUAL. The
 * reason is that these macros perform pre-checking that makes them a lot faster
 * than calling this function directly and, additionally, they are able to fill
 * in automatically diagnostic messages.
 * 
 * Checks if the left value is greater than or equal to the right value. If not,
 * an exception is thrown with corresponding diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkGreaterEqual( const std::string& leftVariable,
                        const T& leftValue,
                        const std::string& rightVariable,
                        const T& rightValue,
                        const std::string& function,
                        const std::string& file,
                        const int& line,
                        const std::string& failMessage )
{
  if ( leftValue < rightValue )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " >= "
        << rightVariable << "{" << stringify( rightValue ) << "}";

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

void checkGreaterEqual( const std::string& leftVariable,
                        const int& leftValue,
                        const std::string& rightVariable,
                        const size_t& rightValue,
                        const std::string& function,
                        const std::string& file,
                        const int& line,
                        const std::string& failMessage );

void checkGreaterEqual( const std::string& leftVariable,
                        const size_t& leftValue,
                        const std::string& rightVariable,
                        const int& rightValue,
                        const std::string& function,
                        const std::string& file,
                        const int& line,
                        const std::string& failMessage );

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_GREATER_NEAR_MSG or ADHOCPP_CHECK_GREATER_NEAR. The
 * reason is that these macros perform pre-checking that makes them a lot faster
 * than calling this function directly and, additionally, they are able to fill
 * in automatically diagnostic messages.
 * 
 * Checks if the left value is greater than or equal to the right value, given a
 * certain tolerance. If not, an exception is thrown with corresponding
 * diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param tolerance The given tolerance for the check.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkGreaterNear( const std::string& leftVariable,
                       const T& leftValue,
                       const std::string& rightVariable,
                       const T& rightValue,
                       const T& tolerance,
                       const std::string& function,
                       const std::string& file,
                       const int& line,
                       const std::string& failMessage )
{
  if ( !compareGreaterEqual( leftValue, rightValue, tolerance ) )
  {
    std::ostringstream exceptionMessage;
    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " >= "
        << rightVariable << "{" << stringify( rightValue ) << "}" << " with tolerance: " << stringify( tolerance );

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_LESS_MSG or ADHOCPP_CHECK_LESS. The reason is
 * that these macros perform pre-checking that makes them a lot faster than
 * calling this function directly and, additionally, they are able to fill in
 * automatically diagnostic messages.
 * 
 * Checks if the left value is less than the right value. If not, an exception
 * is thrown with corresponding diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkLess( const std::string& leftVariable,
                const T& leftValue,
                const std::string& rightVariable,
                const T& rightValue,
                const std::string& function,
                const std::string& file,
                const int& line,
                const std::string& failMessage )
{
  if ( leftValue >= rightValue )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " < "
        << rightVariable << "{" << stringify( rightValue ) << "}";

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

void checkLess( const std::string& leftVariable,
                const int& leftValue,
                const std::string& rightVariable,
                const size_t& rightValue,
                const std::string& function,
                const std::string& file,
                const int& line,
                const std::string& failMessage );

void checkLess( const std::string& leftVariable,
                const size_t& leftValue,
                const std::string& rightVariable,
                const int& rightValue,
                const std::string& function,
                const std::string& file,
                const int& line,
                const std::string& failMessage );

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_LESS_EQUAL_MSG or ADHOCPP_CHECK_LESS_EQUAL. The reason
 * is that these macros perform pre-checking that makes them a lot faster than
 * calling this function directly and, additionally, they are able to fill in
 * automatically diagnostic messages.
 * 
 * Checks if the left value is less than or equal to the right value. If not,
 * an exception is thrown with corresponding diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkLessEqual( const std::string& leftVariable,
                     const T& leftValue,
                     const std::string& rightVariable,
                     const T& rightValue,
                     const std::string& function,
                     const std::string& file,
                     const int& line,
                     const std::string& failMessage )
{
  if ( leftValue > rightValue )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " <= "
        << rightVariable << "{" << stringify( rightValue ) << "}";

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

void checkLessEqual( const std::string& leftVariable,
                     const int& leftValue,
                     const std::string& rightVariable,
                     const size_t& rightValue,
                     const std::string& function,
                     const std::string& file,
                     const int& line,
                     const std::string& failMessage );

void checkLessEqual( const std::string& leftVariable,
                     const size_t& leftValue,
                     const std::string& rightVariable,
                     const int& rightValue,
                     const std::string& function,
                     const std::string& file,
                     const int& line,
                     const std::string& failMessage );

/**
 * This function is not to be directly accessed but rather by the corresponding
 * macros: ADHOCPP_CHECK_LESS_NEAR_MSG or ADHOCPP_CHECK_LESS_NEAR. The
 * reason is that these macros perform pre-checking that makes them a lot faster
 * than calling this function directly and, additionally, they are able to fill
 * in automatically diagnostic messages.
 * 
 * Checks if the left value is less than or equal to the right value, given a
 * certain tolerance. If not, an exception is thrown with corresponding
 * diagnostic information. 
 * @param leftVariable The left value stringified in order to be part of the
 * diagnostic message.
 * @param leftValue The left value of the expression to be checked.
 * @param rightVariable The right value stringified in order to be part of the
 * diagnostic message.
 * @param rightValue The right value of the expression to be checked.
 * @param tolerance The given tolerance for the check.
 * @param function The name of the function that is responsible for calling this
 * check.
 * @param file The name of the file where this function is defined.
 * @param line The number of line in this file that the function is defined.
 * @param failMessage Diagnostic message given by the user.
 */
template<typename T>
void checkLessNear( const std::string& leftVariable,
                    const T& leftValue,
                    const std::string& rightVariable,
                    const T& rightValue,
                    const T& tolerance,
                    const std::string& function,
                    const std::string& file,
                    const int& line,
                    const std::string& failMessage )
{
  if ( !compareLessEqual( leftValue, rightValue, tolerance ) )
  {
    std::ostringstream exceptionMessage;

    exceptionMessage << "Check failed for " << leftVariable << "{" << stringify( leftValue ) << "}" << " <= "
        << rightVariable << "{" << stringify( rightValue ) << "}" << " with tolerance: " << stringify( tolerance );

    if ( failMessage != "" )
      exceptionMessage << "\t" << "message: " << failMessage;

    THROW_LOCATION( exceptionMessage.str( ), function, file, line );
  }

  return;
}

} // utilities

#endif // UTILITIES_CHECK_HPP_
