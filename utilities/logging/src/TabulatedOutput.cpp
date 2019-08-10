/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/TabulatedOutput.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- StdIncludes ---
#include <iostream>
#include <fstream>

namespace utilities
{

TabulatedOutput::TabulatedOutput( const std::vector<std::string>& columnNames,
                                  char columnSeparatingCharacter,
                                  bool printSeparatingLine ) :
    spaceCharacter( ' ' ),
    separatingCharacter( columnSeparatingCharacter ),
    printLine( printSeparatingLine ),
    myColumnNames( columnNames ),
    numberOfColumns( columnNames.size( ) ),
    myAlignment( numberOfColumns, Alignment::Left )
{
}
TabulatedOutput::~TabulatedOutput( )
{
}

void TabulatedOutput::addRow( const std::vector<std::string>& entries )
{
  FUNCTION_START;

  if( entries.size( ) >= numberOfColumns )
  {
    myData.push_back( entries );
  }
  else
  {
    std::cout << "vector passed to TabulatedOutput::addRow is too small!\n";
  }

  FUNCTION_END;
}

void TabulatedOutput::writeToStream( std::ostream& outputStream ) const
{
  FUNCTION_START;

  // transpose the vector of rows (myData) into a vector of columns
  std::vector<std::vector<std::string>> columnVector( numberOfColumns );
  for( const std::vector<std::string>& row : myData )
  {
    for( size_t columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex )
    {
      columnVector[columnIndex].push_back( row[columnIndex] );
    }
  }

  // format each column of columnVector
  for( size_t columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex )
  {
    std::vector<std::string> formattedColumn;
    getFormattedResultColumn( columnVector[columnIndex], myColumnNames[columnIndex],
        formattedColumn, myAlignment[columnIndex] );
    columnVector[columnIndex] = formattedColumn;
  }

  // write formatted columns of columnVector into outputStream
  assembleColumnsIntoTable( columnVector, outputStream );

  FUNCTION_END;
}

void TabulatedOutput::getFormattedResultColumn( const std::vector<std::string>& entries,
                                                const std::string& columnName,
                                                std::vector<std::string>& outputVector,
                                                Alignment alignment ) const
{
  FUNCTION_START;

  // get the length of the largest string of that column
  size_t maxLength = columnName.length( );
  for( const std::string& entry : entries )
  {
    if( entry.length( ) > maxLength )
    {
      maxLength = entry.length( );
    }
  }
  std::string line;

  // print the column name
  line = columnName + std::string( maxLength - columnName.length( ), ' ' );
  outputVector.push_back( line );

  // print the separating line
  if( printLine )
  {
    line = std::string( maxLength, '-' );
    outputVector.push_back( line );
  }


  // print the entries
  for( const std::string& entry : entries )
  {
    size_t space = maxLength - entry.length( );
    size_t indent = static_cast<double>( alignment ) / 2.0 * space + 0.5;
    line = std::string( indent, spaceCharacter ) + entry +
        std::string( space - indent, spaceCharacter );
    outputVector.push_back( line );
  }

  FUNCTION_END;
}

void TabulatedOutput::writeToFile( const std::string& fileName ) const
{
  FUNCTION_START;

  // open file
  std::ofstream outputFile;
  outputFile.open(  fileName, std::fstream::out );

  // try to write into file
  if( outputFile.is_open( ) )
  {
    writeToStream( outputFile );
    outputFile.close( );
  }
  else
  {
    std::cout << "error opening file " << fileName;
  }

  FUNCTION_END;
}

void TabulatedOutput::assembleColumnsIntoTable( const std::vector< std::vector<std::string> >& columnVector,
                                                std::ostream& outputStream ) const
{
  FUNCTION_START;

  // get sizes of rows and columns
  size_t numberOfColumns = columnVector.size( );
  size_t numberOfRows = columnVector[0].size( );

  std::string separation = { ' ', separatingCharacter, ' '};

  // iterate over rows and columns and write entries into outputStream
  for( size_t rowNumber = 0; rowNumber < numberOfRows; ++rowNumber )
  {
    outputStream << columnVector[0][rowNumber];
    for( size_t columnNumber = 1; columnNumber < numberOfColumns; ++columnNumber )
    {
      outputStream << separation << columnVector[columnNumber][rowNumber];
    }
    outputStream << "\n";
    if( printLine && rowNumber == 0 )
    {
      separation = { '-', separatingCharacter, '-' };
    }
    else
    {
      separation = { spaceCharacter, separatingCharacter, spaceCharacter };
    }
  }

  FUNCTION_END;
}

void TabulatedOutput::alignColumns( const std::vector<Alignment>& columnAlignment )
{
  FUNCTION_START;

  for( size_t i = 0; i < columnAlignment.size( ) && i < numberOfColumns; ++i )
  {
    myAlignment[i] = columnAlignment[i];
  }

  FUNCTION_END;
}

} // namespace utilities
