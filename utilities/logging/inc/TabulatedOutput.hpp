/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_TABULATEDOUTPUT_HPP_
#define UTILITIES_TABULATEDOUTPUT_HPP_

// --- Std Includes ---
#include <vector>
#include <string>

namespace utilities
{

enum Alignment
{
  Left,
  Center,
  Right
};

/*
 * TabulatedOutput makes a nice formatted output like this:
 *
 * name               | call count | elapsed time | percentage time
 * -------------------|------------|--------------|----------------
 * global             | 1          | 3.31514      | 100
 *   main             | 1          | 3.31508      | 99.9982
 *     function_1     | 1          | 3.31499      | 99.9956
 *       function_1_1 | 10         | 3.31494      | 99.9939
 *       function_1_2 | 1          | 1.9639e-05   | 0.000592404
 *     function_2     | 1          | 6.7353e-05   | 0.00203168
 *
 * the top row of column names is passed as std::vector<std::string>.
 * Its length is stored as numberOfColumns. You can then basically
 * add rows and write the table to a stream or file.
 */
class TabulatedOutput final
{
public:
  /*
   * columnSeparatingCharacter separates the entries in a row
   * printSeparatingLine specifies if the line between the column
   * names and the body should be printed.
   */
  TabulatedOutput( const std::vector<std::string>& columnNames,
                   char columnSeparatingCharacter = '|',
                   bool printSeparatingLine = true );

  ~TabulatedOutput( );

  /*
   * addRow can handle arguments which support the operator <<()
   * that is used to convert them into a string
   */
  template<typename... EntryTypes>
  void addRow( const EntryTypes&... entries );
  void addRow( const std::vector<std::string>& entries );

  // specify the allignment of each column
  void alignColumns( const std::vector<Alignment>& columnAlignment );

  // get the formated table
  void writeToStream( std::ostream& outputStream ) const;
  void writeToFile( const std::string& fileName ) const;

  // specify which character should be used to fill whitespace
  char spaceCharacter;

private:
  explicit TabulatedOutput( const TabulatedOutput& );
  TabulatedOutput& operator=( const TabulatedOutput& );

  // recursive method to get all entries of the argument list
  template<typename Arg1, typename... EntryTypes>
  void addRow( std::vector<std::string>& row,
               const Arg1& arg1,
               const EntryTypes&... entries );

  /*
   *  format a column by filling in whitespace depending on the
   *  length of the largest string
  */
  void getFormattedResultColumn( const std::vector<std::string>& entries,
                                 const std::string& columnName,
                                 std::vector<std::string>& outputVector,
                                 Alignment alignment ) const;

  // write the entries a std::vector of columns into a ostream
  void assembleColumnsIntoTable( const std::vector<std::vector<std::string>>& columnVector,
                                 std::ostream& outputStream ) const;

  const char separatingCharacter;
  const bool printLine;
  const std::vector<std::string> myColumnNames;
  const size_t numberOfColumns;
  std::vector<std::vector<std::string> > myData;
  std::vector<Alignment> myAlignment;

};

} // namespace utilities

#include "../impl/TabulatedOutput_impl.hpp"
#endif // UTILITIES_TABULATEDOUTPUT_HPP_
