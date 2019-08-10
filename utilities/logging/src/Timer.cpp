/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/Timer.hpp"
#include "../inc/TabulatedOutput.hpp"
#include "../inc/Percentage.hpp"
#include "../inc/TimeSpan.hpp"
#include "../inc/Section.hpp"
#include "../inc/Logger.hpp"
#include "../inc/ScientificDouble.hpp"
#include "../inc/XmlTreeGenerator.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- Std Includes ---
#include <iostream>
#include <sstream>
#include <signal.h>

// --- Boost Includes ---
#include <boost/timer/timer.hpp>

namespace utilities
{

bool Timer::abort = false;

Timer::Timer( ):
    globalSection( new Section( "global", 0 ) ),
    firstStart( true )
{
  FUNCTION_START;

  FUNCTION_END;
}

Timer::~Timer( ) noexcept(false)
{
  FUNCTION_START;

  if( abort == false && LogConfiguration::silent == false )
  {
    // make sure that all sections are closed;
    globalSection->finish( );

    finalize( );
  }

  FUNCTION_END;
}

Timer& Timer::instance( )
{
  FUNCTION_START;

  static Timer timer;
  if( abort == false ) timer.checkpoint( );
  return timer;

  FUNCTION_END;
}


void Timer::start( const std::string& name )
{
  FUNCTION_START;

  if( firstStart && LogConfiguration::catchSignals == true
      && LogConfiguration::silent == false )
  {
    signal( SIGABRT, &Timer::sighandler );
    signal( SIGTERM, &Timer::sighandler );
    signal( SIGINT, &Timer::sighandler );
    firstStart = false;
  }

  checkpoint( );

  // forward the start call to the section tree and send result to Logger
  Logger::logScopeStart( globalSection->start( name ) );

  FUNCTION_END;
}

SectionResultPtr Timer::end( )
{
  FUNCTION_START;

  checkpoint( );

  SectionResultPtr result = globalSection->end( );

  Logger::logScopeEnd( result );

  return result;

  FUNCTION_END;
}

void Timer::finalize( ) const
{
  FUNCTION_START;

  std::stringstream resultStream;
  std::vector<SectionResult> resultVector;

  // recursively write results of each section into resultVector
  globalSection->finalize( resultVector );

  // ========================= Prepare Tables ==================================

  // set column names
  std::vector<std::string> outputColumnNames = { "name",
      "call count", "elapsed time", "percentage time", "elapsed time[s]" };
  std::vector<std::string> csvColumnNames = { "name", "tree depth",
      "call count", "elapsed time", "percentage time", "elapsed time[s]" };

  // set alignment of entries of each column
  std::vector<Alignment> outputAlignment( 5, Alignment::Right );
  outputAlignment[0] = Alignment::Left;
  outputAlignment[1] = Alignment::Center;
  outputAlignment[4] = Alignment::Center;

  std::vector<Alignment> csvAlignment( 6, Alignment::Right );
  csvAlignment[0] = Alignment::Left;

  // create tables
  TabulatedOutput outputTable( outputColumnNames, '|', true);
  outputTable.spaceCharacter = LogConfiguration::summarySpaceCharacter;
  TabulatedOutput csvTable( csvColumnNames, ',', false );

  // set alignment
  outputTable.alignColumns( outputAlignment );
  csvTable.alignColumns( csvAlignment );

  size_t indentation = 2;

  // ============= Add a row for each SectionResult to Tables ================

  // add each row of the result vector to the table classes
  for( const SectionResult& result : resultVector )
  {
    outputTable.addRow(
        std::string( indentation * result.treeDepth,
                     LogConfiguration::summarySpaceCharacter ) + result.name, // name
        result.callCount,                                                     // call count
        TimeSpan( result.elapsedTime ),                                       // elapsed time
        Percentage( result.elapsedTime, resultVector[0].elapsedTime, true ),  // percentage time
        ScientificDouble( result.elapsedTime ) );                             // scientific presentation

    csvTable.addRow(
        result.name,                                                           // name
        result.treeDepth,                                                      // scope tree depth
        result.callCount,                                                      // call count
        TimeSpan( result.elapsedTime ),                                        // elapsed time in scope
        Percentage( result.elapsedTime, resultVector[0].elapsedTime, false ),  // relative time compared to global
        ScientificDouble( result.elapsedTime ) );                              // scientific presentation
  }

  // ================== Produce file and console output ======================

  // write results to files
  if( LogConfiguration::fileName != "" )
  {
    outputTable.writeToFile( LogConfiguration::fileName + "_summary.txt" );
    csvTable.writeToFile( LogConfiguration::fileName + "_summary.csv" );
  }

  // write result summary to standard output stream
  std::stringstream summary;
  outputTable.writeToStream( summary );
  if ( LogConfiguration::showTimingSummary == true )
  {
#pragma omp critical( AdhocppLoggingCout )
    {
    std::cout << summary.str( );
    }
  }

  // =========================== XML Output =================================

  // construct global xml element
  XmlTreeGenerator::XmlElement globalElement( "section" );
  globalElement.attributes.push_back( XmlTreeGenerator::XmlAttribute( "name", "global" ) );
  globalElement.attributes.push_back( XmlTreeGenerator::XmlAttribute( "call_count", "1" ) );
  globalElement.attributes.push_back( XmlTreeGenerator::XmlAttribute( "elapsed_time",
      ScientificDouble( resultVector[0].elapsedTime ).to_string( ) ) );
  globalElement.attributes.push_back( XmlTreeGenerator::XmlAttribute( "time_unit", "seconds" ) );

  // generate the tree by evaluating the tree depth of the SectionResults
  for( size_t i = 1; i < resultVector.size( ); ++i )
  {
    XmlTreeGenerator::XmlElement element( "section" );
    element.attributes.push_back( XmlTreeGenerator::XmlAttribute( "name", resultVector[i].name ) );
    element.attributes.push_back( XmlTreeGenerator::XmlAttribute( "call_count", std::to_string( resultVector[i].callCount ) ) );
    element.attributes.push_back( XmlTreeGenerator::XmlAttribute( "elapsed_time",
        ScientificDouble( resultVector[i].elapsedTime ).to_string( ) ) );
    element.attributes.push_back( XmlTreeGenerator::XmlAttribute( "time_unit", "seconds" ) );

    size_t elementTreeDepth = resultVector[i].treeDepth;
    XmlTreeGenerator::XmlElement* elementPtr = &globalElement;

    // iterate down the existing tree until last element is found
    for( size_t j = 1; j < elementTreeDepth; ++j )
    {
      elementPtr = &( elementPtr->subElements.back( ) );
    }
    elementPtr->subElements.push_back( element );
  }

  XmlTreeGenerator xmlGenerator( globalElement );
  xmlGenerator.generateXmlOutput( LogConfiguration::fileName + "_summary.xml" );

  FUNCTION_END;
}

void Timer::checkpoint( )
{
  FUNCTION_START;

  if( abort )
  {
    // restore cursor
    if( LogConfiguration::fancy == true )
    {
#pragma omp critical( AdhocppLoggingCout )
      {
        std::cout << "\33[?25h\n";
      }
    }

    // make sure that all sections are closed;
    instance().globalSection->finish( );

    instance().finalize( );

    exit( 0 );
  }

  FUNCTION_END;
}

void Timer::sighandler( int signal )
{
  FUNCTION_START;
#pragma omp critical( AdhocppLoggingCout )    // TODO Landesberger: could a deadlock prevent htis from showing up?
  {
  std::cout << "\b\bCaught signal...\nOptions [1]:\n";
  std::cout << "[1] exit program at next checkpoint\n";
  std::cout << "[2] exit program now (not safe)\n";
  std::cout << "[3] continue (not safe)\n";
  std::cout << "input: ";
  std::string option = "";
  std::getline( std::cin, option );

  if( option == "2" )
  {
    std::cout << "=> terminating...\n";
    exit( signal );
  }
  else if( option == "3" )
  {
    std::cout << "=> continuing...\n";
  }
  else
  {
    std::cout << "=> safely terminating execution at next checkpoint...\n";
    Timer::instance( ).abort = true;
  }
  }
  FUNCTION_END;
}

SectionResultPtr Timer::getStateOfActiveSection( ) const
{
  FUNCTION_START;

  return globalSection->getStateOfActiveSection( );

  FUNCTION_END;
}

} // adhocpp
