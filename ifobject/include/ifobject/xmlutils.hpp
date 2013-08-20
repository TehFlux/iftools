#ifndef IONFLUX_OBJECT_XMLUTILS
#define IONFLUX_OBJECT_XMLUTILS
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2013 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils.hpp                     XML utility functions (header).
 * ==========================================================================
 *
 * This file is part of Ionflux Object Base System.
 * 
 * Ionflux Object Base System is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the 
 * License, or (at your option) any later version.
 * 
 * Ionflux Object Base System is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Object Base System; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */
#include <string>
#include <sstream>
#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "ifobject/utils.hpp"

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/** Get attribute value.
 *
 * Get the value of an attribute from an element, identified by an element 
 * ID, within a certain XML file.
 *
 * \param fileName File name.
 * \param elementName Element name.
 * \param elementID Element ID.
 * \param attrName Attribute name.
 *
 * \return Attribute value, or an empty string if the attribute is not found.
 */
std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName);

/** Get attribute values.
 *
 * Get the values of a specified attribute from multiple elements, 
 * identified by a vector of element IDs, within a certain XML file.
 *
 * \param fileName File name.
 * \param elementName Element name.
 * \param attrName Attribute name.
 * \param elementIDs Element IDs.
 * \param target Where to store the extracted attributes.
 */
void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target);

/** Escape XML.
 *
 * Escape the string so that it can be used as an XML attribute value.
 *
 * \param bytes data to be escaped
 *
 * \return escaped data
 */
std::string xmlEscape(const std::string& bytes);

/** Get XML (IntVector)
 *
 * Get an XML representation for a vector of integers.
 *
 * \param v vector
 * \param name name attribute value
 * \param indentLevel indentation level
 *
 * \return XML representation
 */
std::string getXML0(const Ionflux::ObjectBase::IntVector& v, 
    const std::string& name = "", unsigned int indentLevel = 0);

/** Set vector of integers from XML.
 *
 * Initialize a vector of integers from an XML representation.
 *
 * \param data XML data
 * \param v vector
 */
void setFromXML(const std::string& data, 
    Ionflux::ObjectBase::IntVector& v);

/** Get XML (UIntVector)
 *
 * Get an XML representation for a vector of unsigned integers.
 *
 * \param v vector
 * \param name name attribute value
 * \param indentLevel indentation level
 *
 * \return XML representation
 */
std::string getXML0(const Ionflux::ObjectBase::UIntVector& v, 
    const std::string& name = "", unsigned int indentLevel = 0);

/** Get XML (DoubleVector)
 *
 * Get an XML representation for a vector of double precision floating point 
 * numbers.
 *
 * \param v vector
 * \param name name attribute value
 * \param indentLevel indentation level
 *
 * \return XML representation
 */
std::string getXML0(const Ionflux::ObjectBase::DoubleVector& v, 
    const std::string& name = "", unsigned int indentLevel = 0);

/** Get XML
 *
 * Get an XML representation for a vector of objects.
 *
 * \param v vector
 * \param name name attribute value
 * \param indentLevel indentation level
 *
 * \return XML representation
 */
template<class T>
std::string getXML0(const std::vector<T>& v, 
    const std::string& elementName = "vec", const std::string& name = "", 
    unsigned int indentLevel = 0)
{
    std::ostringstream xmlData;
    std::string iws = getIndent(indentLevel);
    xmlData << iws << "<" << elementName;
    if (name.size() > 0)
        xmlData << " name=\"" << name << "\"";
    xmlData << ">";
    for (unsigned int i = 0; i < v.size(); i++)
    {
        T e0 = v[i];
        xmlData << "\n" << e0->getXML0(indentLevel + 1);
    }
    xmlData << "\n" << iws << "</" << elementName << ">";
    return xmlData.str();
}

}

}

}

/** \file xmlutils.hpp
 * \brief XML utility functions (header).
 */
#endif