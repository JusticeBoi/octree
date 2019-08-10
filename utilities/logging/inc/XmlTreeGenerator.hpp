/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef utilities_XMLTREEGENERATOR_HPP_
#define utilities_XMLTREEGENERATOR_HPP_

// --- Std Includes ---
#include <ostream>
#include <string>
#include <vector>

namespace utilities
{
/*
 * XmlTreeGenerator can produce xml output for representing a tree structure.
 * Each tree element consists of a vector of attributes and a vector of sub
 * elements. The constructor of XmlTreeGenerator takes the top-most element
 * and the name of the tags used in the output.
 * generateXmlOutput( ) produces the output.
 */
class XmlTreeGenerator final
{
public:
  struct XmlAttribute
  {
    XmlAttribute( );
    XmlAttribute( const std::string& attributeName, const std::string& attributeValue );

    std::string name;
    std::string value;
  };

  struct XmlElement
  {
    XmlElement( );
    XmlElement( const std::string& elementName );
    std::string name;
    std::vector<XmlAttribute> attributes;
    std::vector<XmlElement> subElements;
    std::string data;
  };

  XmlTreeGenerator( const XmlElement& topElement );
  ~XmlTreeGenerator( );

  void generateXmlOutput( std::ostream& outputStream ) const;
  void generateXmlOutput( const std::string& fileName ) const;

private:
  explicit XmlTreeGenerator( const XmlTreeGenerator& );
  XmlTreeGenerator& operator=( const XmlTreeGenerator& );

  void generateXmlOutput( const XmlElement& element, std::ostream& outputStream ) const;

  XmlElement myTopElement;
};

} // namespace utilities 
#endif // utilities_XMLTREEGENERATOR_HPP_ 
