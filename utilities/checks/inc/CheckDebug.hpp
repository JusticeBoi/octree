/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_CHECKDEBUG_HPP_
#define UTILITIES_CHECKDEBUG_HPP_

// --- Internal Includes ---
//#include "adhocpp_config.hpp"

#ifdef ADHOCPP_ENABLE_DEBUG_CHECKS

// --- Utilities Includes ---
#include "Check.hpp"

#define ADHOCPP_CHECK_MSG_DBG( expression,\
                               message ) \
ADHOCPP_CHECK_MSG( expression,\
                   message )

#define ADHOCPP_CHECK_DBG( expression ) \
ADHOCPP_CHECK_MSG( expression,\
                   "")

#define ADHOCPP_CHECK_EQUAL_MSG_DBG( leftValue,\
                                     rightValue,\
                                     message ) \
ADHOCPP_CHECK_EQUAL_MSG( leftValue,\
                         rightValue,\
                         message )
 
#define ADHOCPP_CHECK_EQUAL_DBG( leftValue,\
                                 rightValue ) \
ADHOCPP_CHECK_EQUAL_MSG( leftValue,\
                         rightValue,\
                         "" )

#define ADHOCPP_CHECK_NEAR_MSG_DBG( leftValue,\
                                    rightValue,\
                                    tolerance,\
                                    message ) \
ADHOCPP_CHECK_NEAR_MSG( leftValue,\
                        rightValue,\
                        tolerance,\
                        message )

#define ADHOCPP_CHECK_NEAR_DBG( leftValue,\
                                rightValue,\
                                tolerance ) \
ADHOCPP_CHECK_NEAR_MSG( leftValue,\
                        rightValue,\
                        tolerance,\
                        "" )

#define ADHOCPP_CHECK_NOT_EQUAL_MSG_DBG( leftValue,\
                                         rightValue,\
                                         message ) \
ADHOCPP_CHECK_NOT_EQUAL_MSG( leftValue,\
                             rightValue,\
                             message )

#define ADHOCPP_CHECK_NOT_EQUAL_DBG( leftValue,\
                                     rightValue ) \
ADHOCPP_CHECK_NOT_EQUAL_MSG( leftValue,\
                             rightValue,\
                             "" )

#define ADHOCPP_CHECK_NOT_NEAR_MSG_DBG( leftValue,\
                                        rightValue,\
                                        tolerance,\
                                        message ) \
ADHOCPP_CHECK_NOT_NEAR_MSG( leftValue,\
                            rightValue,\
                            tolerance,\
                            message )

#define ADHOCPP_CHECK_NOT_NEAR_DBG( leftValue,\
                                    rightValue,\
                                    tolerance ) \
ADHOCPP_CHECK_NOT_NEAR_MSG( leftValue,\
                            rightValue,\
                            tolerance,\
                            "" )

#define ADHOCPP_CHECK_GREATER_MSG_DBG( leftValue,\
                                       rightValue,\
                                       message ) \
ADHOCPP_CHECK_GREATER_MSG( leftValue,\
                           rightValue,\
                           message )

#define ADHOCPP_CHECK_GREATER_DBG( leftValue,\
                                   rightValue ) \
ADHOCPP_CHECK_GREATER_MSG( leftValue,\
                           rightValue,\
                           "" )

#define ADHOCPP_CHECK_GREATER_EQUAL_MSG_DBG( leftValue,\
                                             rightValue,\
                                             message ) \
ADHOCPP_CHECK_GREATER_EQUAL_MSG( leftValue,\
                                 rightValue,\
                                 message )

#define ADHOCPP_CHECK_GREATER_EQUAL_DBG( leftValue,\
                                         rightValue ) \
ADHOCPP_CHECK_GREATER_EQUAL_MSG( leftValue,\
                                 rightValue,\
                                 "" )

#define ADHOCPP_CHECK_GREATER_NEAR_MSG_DBG( leftValue,\
                                            rightValue,\
                                            tolerance,\
                                            message ) \
ADHOCPP_CHECK_GREATER_NEAR_MSG( leftValue,\
                                rightValue,\
                                tolerance,\
                                message )

#define ADHOCPP_CHECK_GREATER_NEAR_DBG( leftValue,\
                                        rightValue,\
                                        tolerance ) \
ADHOCPP_CHECK_GREATER_NEAR_MSG( leftValue,\
                                rightValue,\
                                tolerance,\
                                "" )

#define ADHOCPP_CHECK_LESS_MSG_DBG( leftValue,\
                                    rightValue,\
                                    message ) \
ADHOCPP_CHECK_LESS_MSG( leftValue,\
                        rightValue,\
                        message )

#define ADHOCPP_CHECK_LESS_DBG( leftValue,\
                                rightValue ) \
ADHOCPP_CHECK_LESS_MSG( leftValue,\
                        rightValue,\
                        "" )

#define ADHOCPP_CHECK_LESS_EQUAL_MSG_DBG( leftValue,\
                                          rightValue,\
                                          message ) \
ADHOCPP_CHECK_LESS_EQUAL_MSG( leftValue,\
                              rightValue,\
                              message )

#define ADHOCPP_CHECK_LESS_EQUAL_DBG( leftValue,\
                                      rightValue ) \
ADHOCPP_CHECK_LESS_EQUAL_MSG( leftValue,\
                              rightValue,\
                              "" )

#define ADHOCPP_CHECK_LESS_NEAR_MSG_DBG( leftValue,\
                                         rightValue,\
                                         tolerance,\
                                         message ) \
ADHOCPP_CHECK_LESS_NEAR_MSG( leftValue,\
                             rightValue,\
                             tolerance,\
                             message )

#define ADHOCPP_CHECK_LESS_NEAR_DBG( leftValue,\
                                     rightValue,\
                                     tolerance ) \
ADHOCPP_CHECK_LESS_NEAR_MSG( leftValue,\
                             rightValue,\
                             tolerance,\
                             "" )

#else

#define ADHOCPP_CHECK_MSG_DBG( expression,\
                               message )

#define ADHOCPP_CHECK_DBG( expression )

#define ADHOCPP_CHECK_EQUAL_MSG_DBG( leftValue,\
                                     rightValue,\
                                     message )
 
#define ADHOCPP_CHECK_EQUAL_DBG( leftValue,\
                                 rightValue )

#define ADHOCPP_CHECK_NEAR_MSG_DBG( leftValue,\
                                    rightValue,\
                                    tolerance,\
                                    message )

#define ADHOCPP_CHECK_NEAR_DBG( leftValue,\
                                rightValue,\
                                tolerance )

#define ADHOCPP_CHECK_NOT_EQUAL_MSG_DBG( leftValue,\
                                         rightValue,\
                                         message )

#define ADHOCPP_CHECK_NOT_EQUAL_DBG( leftValue,\
                                     rightValue )

#define ADHOCPP_CHECK_NOT_NEAR_MSG_DBG( leftValue,\
                                        rightValue,\
                                        tolerance,\
                                        message )

#define ADHOCPP_CHECK_NOT_NEAR_DBG( leftValue,\
                                    rightValue,\
                                    tolerance )

#define ADHOCPP_CHECK_GREATER_MSG_DBG( leftValue,\
                                       rightValue,\
                                       message )

#define ADHOCPP_CHECK_GREATER_DBG( leftValue,\
                                   rightValue )

#define ADHOCPP_CHECK_GREATER_EQUAL_MSG_DBG( leftValue,\
                                             rightValue,\
                                             message )

#define ADHOCPP_CHECK_GREATER_EQUAL_DBG( leftValue,\
                                         rightValue )

#define ADHOCPP_CHECK_GREATER_NEAR_MSG_DBG( leftValue,\
                                            rightValue,\
                                            tolerance,\
                                            message )

#define ADHOCPP_CHECK_GREATER_NEAR_DBG( leftValue,\
                                        rightValue,\
                                        tolerance )

#define ADHOCPP_CHECK_LESS_MSG_DBG( leftValue,\
                                    rightValue,\
                                    message )

#define ADHOCPP_CHECK_LESS_DBG( leftValue,\
                                rightValue )

#define ADHOCPP_CHECK_LESS_EQUAL_MSG_DBG( leftValue,\
                                          rightValue,\
                                          message )

#define ADHOCPP_CHECK_LESS_EQUAL_DBG( leftValue,\
                                      rightValue )

#define ADHOCPP_CHECK_LESS_NEAR_MSG_DBG( leftValue,\
                                         rightValue,\
                                         tolerance,\
                                         message )

#define ADHOCPP_CHECK_LESS_NEAR_DBG( leftValue,\
                                     rightValue,\
                                     tolerance )

#endif // ADHOCPP_ENABLE_DEBUG_CHECKS

#endif // UTILITIES_CHECKDEBUG_HPP_
