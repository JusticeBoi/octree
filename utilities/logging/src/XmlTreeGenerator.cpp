/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/XmlTreeGenerator.hpp"

// --- Utilities Includes ---
#include "utilities/inc/functionessentials.hpp"

// --- Utilities Includes ---
#include <fstream>
#include <iostream>

namespace utilities
{


XmlTreeGenerator::XmlAttribute::XmlAttribute( const std::string& attributeName,
                                              const std::string& attributeValue ) :
    name( attributeName ),
    value( attributeValue )
{
}

XmlTreeGenerator::XmlAttribute::XmlAttribute( ) :
    XmlAttribute( "emptyAttribute", "" )
{
}

XmlTreeGenerator::XmlElement::XmlElement( ) :
    name( "UnnamedXmlElement" ),
    data( "" )
{
}

XmlTreeGenerator::XmlElement::XmlElement( const std::string& elementName ) :
    name( elementName ),
    data( "" )
{
}

XmlTreeGenerator::XmlTreeGenerator( const XmlElement& topElement ) :
    myTopElement( topElement )
{
}

XmlTreeGenerator::~XmlTreeGenerator( )
{
}

void XmlTreeGenerator::generateXmlOutput( std::ostream& outputStream ) const
{
  FUNCTION_START;

  outputStream << "<?xml version=\"1.0\"?>\n";
  generateXmlOutput( myTopElement, outputStream );

  FUNCTION_END;
}

void XmlTreeGenerator::generateXmlOutput( const XmlElement& element, std::ostream& outputStream ) const
{
  FUNCTION_START;

  // add tag
  outputStream << "<" << element.name;

  // add attributes
  for( const XmlAttribute& attribute : element.attributes )
  {
    outputStream << " " << attribute.name << "=\"" << attribute.value << "\"";
  }
  outputStream << ">\n" << element.data;

  if( element.data != "" )
  {
    outputStream << "\n";
  }

  // call generateXmlOutput for all sub elements
  for( const XmlElement& subElement : element.subElements )
  {
    generateXmlOutput( subElement, outputStream );
  }

  // close tag
  outputStream << "</" << element.name << ">\n";

  FUNCTION_END;
}

void XmlTreeGenerator::generateXmlOutput( const std::string& fileName ) const
{
  FUNCTION_START;

  // open file
  std::ofstream fileStream;
  fileStream.open( fileName );

  if( fileStream.is_open( ) )
  {
    // write to filestream if file is open
    generateXmlOutput( fileStream );
    fileStream.close( );
  }
  else
  {
    std::cout << "Error opening file: " << fileName << "\n";
  }

  FUNCTION_END;
}

} // namespace utilities 
