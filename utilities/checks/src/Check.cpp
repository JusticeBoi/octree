/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Utilities Includes ---
#include "../inc/Check.hpp"

namespace utilities
{

void checkEqual( const std::string& leftVariable,
                 const int& leftValue,
                 const std::string& rightVariable,
                 const size_t& rightValue,
                 const std::string& function,
                 const std::string& file,
                 const int& line,
                 const std::string& failMessage )
{
  if( leftValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkEqual( leftVariable,
              static_cast< size_t >( leftValue ),
              rightVariable,
              rightValue,
              function,
              file,
              line,
              failMessage );

  return;
}

void checkEqual( const std::string& leftVariable,
                 const size_t& leftValue,
                 const std::string& rightVariable,
                 const int& rightValue,
                 const std::string& function,
                 const std::string& file,
                 const int& line,
                 const std::string& failMessage )
{
  if( rightValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkEqual( leftVariable,
              leftValue,
              rightVariable,
              static_cast< size_t >( rightValue ),
              function,
              file,
              line,
              failMessage );

  return;
}

void checkNotEqual( const std::string& leftVariable,
                    const int& leftValue,
                    const std::string& rightVariable,
                    const size_t& rightValue,
                    const std::string& function,
                    const std::string& file,
                    const int& line,
                    const std::string& failMessage )
{
  if( leftValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkNotEqual( leftVariable,
                 static_cast< size_t >( leftValue ),
                 rightVariable,
                 rightValue,
                 function,
                 file,
                 line,
                 failMessage );

  return;
}

void checkNotEqual( const std::string& leftVariable,
                    const size_t& leftValue,
                    const std::string& rightVariable,
                    const int& rightValue,
                    const std::string& function,
                    const std::string& file,
                    const int& line,
                    const std::string& failMessage )
{
  if( rightValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkNotEqual( leftVariable,
                 leftValue,
                 rightVariable,
                 static_cast< size_t >( rightValue ),
                 function,
                 file,
                 line,
                 failMessage );

  return;
}

void checkGreater( const std::string& leftVariable,
                   const int& leftValue,
                   const std::string& rightVariable,
                   const size_t& rightValue,
                   const std::string& function,
                   const std::string& file,
                   const int& line,
                   const std::string& failMessage )
{
  if( leftValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkGreater( leftVariable,
                static_cast< size_t >( leftValue ),
                rightVariable,
                rightValue,
                function,
                file,
                line,
                failMessage );

  return;
}

void checkGreater( const std::string& leftVariable,
                   const size_t& leftValue,
                   const std::string& rightVariable,
                   const int& rightValue,
                   const std::string& function,
                   const std::string& file,
                   const int& line,
                   const std::string& failMessage )
{
  if( rightValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkGreater( leftVariable,
                leftValue,
                rightVariable,
                static_cast< size_t >( rightValue ),
                function,
                file,
                line,
                failMessage );

  return;
}

void checkGreaterEqual( const std::string& leftVariable,
                        const int& leftValue,
                        const std::string& rightVariable,
                        const size_t& rightValue,
                        const std::string& function,
                        const std::string& file,
                        const int& line,
                        const std::string& failMessage )
{
  if( leftValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkGreaterEqual( leftVariable,
                     static_cast< size_t >( leftValue ),
                     rightVariable,
                     rightValue,
                     function,
                     file,
                     line,
                     failMessage );

  return;
}

void checkGreaterEqual( const std::string& leftVariable,
                        const size_t& leftValue,
                        const std::string& rightVariable,
                        const int& rightValue,
                        const std::string& function,
                        const std::string& file,
                        const int& line,
                        const std::string& failMessage )
{
  if( rightValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkGreaterEqual( leftVariable,
                     leftValue,
                     rightVariable,
                     static_cast< size_t >( rightValue ),
                     function,
                     file,
                     line,
                     failMessage );

  return;
}

void checkLess( const std::string& leftVariable,
                const int& leftValue,
                const std::string& rightVariable,
                const size_t& rightValue,
                const std::string& function,
                const std::string& file,
                const int& line,
                const std::string& failMessage )
{
  if( leftValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkLess( leftVariable,
             static_cast< size_t >( leftValue ),
             rightVariable,
             rightValue,
             function,
             file,
             line,
             failMessage );

  return;
}

void checkLess( const std::string& leftVariable,
                const size_t& leftValue,
                const std::string& rightVariable,
                const int& rightValue,
                const std::string& function,
                const std::string& file,
                const int& line,
                const std::string& failMessage )
{
  if( rightValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkLess( leftVariable,
             leftValue,
             rightVariable,
             static_cast< size_t >( rightValue ),
             function,
             file,
             line,
             failMessage );

  return;
}

void checkLessEqual( const std::string& leftVariable,
                     const int& leftValue,
                     const std::string& rightVariable,
                     const size_t& rightValue,
                     const std::string& function,
                     const std::string& file,
                     const int& line,
                     const std::string& failMessage )
{
  if( leftValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkLessEqual( leftVariable,
                  static_cast< size_t >( leftValue ),
                  rightVariable,
                  rightValue,
                  function,
                  file,
                  line,
                  failMessage );

  return;
}

void checkLessEqual( const std::string& leftVariable,
                     const size_t& leftValue,
                     const std::string& rightVariable,
                     const int& rightValue,
                     const std::string& function,
                     const std::string& file,
                     const int& line,
                     const std::string& failMessage )
{
  if( rightValue < 0 )
  {
    THROW_LOCATION( "Illegal comparison between negative integer and "\
                            "unsigned integer expressions",
                            function,
                            file,
                            line );
  }

  checkLessEqual( leftVariable,
                  leftValue,
                  rightVariable,
                  static_cast< size_t >( rightValue ),
                  function,
                  file,
                  line,
                  failMessage );

  return;
}

} // utilities
