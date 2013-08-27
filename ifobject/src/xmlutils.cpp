/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2013 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils.cpp                   XML utility functions (implementation).
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
#include <sstream>
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifobject/IFError.hpp"
#include "ifobject/IFObject.hpp"
#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#undef TIXML_USE_STL

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{


TiXmlElement* findElementByID(TiXmlElement* start, 
    const std::string& elementName, const std::string& elementID)
{
    if (start == 0)
        return 0;
    const char* a0 = start->Attribute("id");
    if (a0 != 0)
    {
        const char* b0 = start->Value();
        if ((std::string(a0) == elementID) 
            && (std::string(b0) == elementName))
            return start;
    }
    TiXmlElement* e1 = start->FirstChildElement();
    TiXmlElement* e0 = findElementByID(e1, elementName, elementID);
    while ((e0 == 0) 
        && (e1 != 0))
    {
        e1 = e1->NextSiblingElement();
        if (e1 != 0)
            e0 = findElementByID(e1, elementName, elementID);
    }
    return e0;
}

TiXmlElement* findElementByName(TiXmlElement* start, 
    const std::string& elementName)
{
    if (start == 0)
        return 0;
    const char* a0 = start->Value();
    if (std::string(a0) == elementName)
        return start;
    TiXmlElement* e0 = start->FirstChildElement();
    if (e0 != 0)
        a0 = e0->Value();
    while ((e0 != 0) 
        && (std::string(a0) != elementName))
    {
        e0 = e0->NextSiblingElement();
        if (e0 != 0)
            a0 = e0->Value();
    }
    return e0;
}

std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName)
{
    std::ostringstream message;
    TiXmlDocument d0(fileName.c_str());
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        message << "[getAttrValue] Unable to read from file '" \
            << fileName << "'.";
        throw IFError(message.str());
    }
    TiXmlElement* result = findElementByID(d0.RootElement(), 
        elementName, elementID);
    if (result != 0)
    {
        const char* a0 = result->Attribute(attrName.c_str());
        if (a0 != 0)
            return std::string(a0);
    }
    return "";
}

void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target)
{
    std::ostringstream message;
    TiXmlDocument d0(fileName.c_str());
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        message << "Unable to read from file '" << fileName << "'.";
        throw IFError(message.str());
    }
    for (Ionflux::ObjectBase::StringVector::const_iterator 
        i = elementIDs.begin(); i != elementIDs.end(); i++)
    {
        std::string elementID = *i;
        TiXmlElement* result = findElementByID(d0.RootElement(), 
            elementName, elementID);
        if (result != 0)
        {
            const char* a0 = result->Attribute(attrName.c_str());
            if (a0 != 0)
                target.push_back(std::string(a0));
            else
            {
                message << "[getAttrValues] Attribute '" << attrName 
                    << "' not found on element ID '" << elementID << "'.";
                throw IFError(message.str());
            }
        }
    }
}

// Get attribute value.
std::string getAttributeValue(TiXmlElement* e0, const std::string& 
    attributeName, bool optional)
{
    const char* a0 = e0->Value();
    std::string elementName(a0);
    a0 = e0->Attribute(attributeName.c_str());
    if (a0 == 0)
    {
        if (!optional)
        {
            std::ostringstream status;
            status << "[getAttributeValue] Element '" << elementName \
                << "' does not have attribute '" << attributeName << "'.";
            throw IFError(status.str());
        } else
            return "";
    }
    return a0;
}

// Check element name.
bool checkElementName(TiXmlElement* e0, const std::string& elementName)
{
    const char* a0 = e0->Value();
    if (std::string(a0) != elementName)
        return false;
    return true;
}

/* Check element name. If the element name does not match the expected 
   value, throw an exception. */
void checkElementNameOrError(TiXmlElement* e0, 
    const std::string& elementName, 
    const std::string& source)
{
    if (!checkElementName(e0, elementName))
    {
        const char* a0 = e0->Value();
        std::ostringstream status;
        status << "[" << source << "] Unexpected element name: " << a0 
            << " (expected: " << elementName << ")";
        throw IFError(status.str());
    }
}

/* Find an element by name. If the element cannot be found, throw 
   an exception. */
TiXmlElement* findElementByNameOrError(TiXmlElement* e0, 
    const std::string& elementName, 
    const std::string& source)
{
    TiXmlElement* m0 = findElementByName(e0, elementName);
    if (m0 == 0)
    {
        std::ostringstream message;
        message << "[" << source << "] Element '" 
            << elementName << "' not found.";
        throw IFError(message.str());
    }
    return m0;
}

// Load document. If the document cannot be loaded, throw an exception.
void loadDocumentOrError(TiXmlDocument& d0, 
    const std::string& source)
{
    if (!d0.LoadFile(TIXML_ENCODING_UTF8))
    {
        const char* a0 = d0.Value();
        std::ostringstream message;
        message << "[" << source << "] Unable to read from file '" 
            << a0 << "'.";
        throw IFError(message.str());
    }
}

// Initialize object from an XML element.
void getObject(TiXmlElement* e0, Ionflux::ObjectBase::IFObject& target)
{
    try
    {
        // 'name' is optional.
        std::string av = getAttributeValue(e0, "name");
        target.setID(av);
    } catch (IFError e)
    { }
}

std::string xmlEscape(const std::string& bytes)
{
    std::string result;
	char byte;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
		byte = bytes[i];
		if (byte == '<')
			result.append("&lt;");
		else
		if (byte == '>')
			result.append("&gt;");
		else
		if (byte == '&')
			result.append("&amp;");
		else
		if (byte == '"')
			result.append("&quot;");
		else
		if (byte == '\'')
			result.append("&apos;");
		else
			result.append(1, byte);
	}
	return result;
}

// Get vector of integers from an XML element.
void getIntVector(TiXmlElement* e0, 
    Ionflux::ObjectBase::IntVector& target, 
    const std::string& separator)
{
    checkElementNameOrError(e0, XML_ELEMENT_NAME_INT_VECTOR, 
        "getIntVector");
    std::string av = getAttributeValue(e0, "d");
    vectorFromList(av, target, separator);
}

void setFromXML(const std::string& data, 
    Ionflux::ObjectBase::IntVector& v)
{
    TiXmlDocument d0;
    /* NOTE: Probably a peculiarity of tinyxml, there must be at least one 
             character after the data. Or there could of course also be 
             something wrong with how tinyxml is used here. Anyway, this 
             seems to work. */
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw IFError("[setFromXML] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = findElementByNameOrError(d0.RootElement(), 
        XML_ELEMENT_NAME_INT_VECTOR);
    getIntVector(m0, v);
}

// Get vector of unsigned integers from an XML element.
void getUIntVector(TiXmlElement* e0, 
    Ionflux::ObjectBase::UIntVector& target, 
    const std::string& separator)
{
    checkElementNameOrError(e0, XML_ELEMENT_NAME_UINT_VECTOR, 
        "getUIntVector");
    std::string av = getAttributeValue(e0, "d");
    vectorFromList(av, target, separator);
}

// Get vector of doubles from an XML element.
void getDoubleVector(TiXmlElement* e0, 
    Ionflux::ObjectBase::DoubleVector& target, 
    const std::string& separator)
{
    checkElementNameOrError(e0, XML_ELEMENT_NAME_DOUBLE_VECTOR, 
        "getDoubleVector");
    std::string av = getAttributeValue(e0, "d");
    vectorFromList(av, target, separator);
}

std::string getXML0(const Ionflux::ObjectBase::IntVector& v, 
    const std::string& name, unsigned int indentLevel, 
    const std::string& attributes)
{
    std::ostringstream xmlData;
    std::string iws = getIndent(indentLevel);
    xmlData << iws << "<" << XML_ELEMENT_NAME_INT_VECTOR;
    if (name.size() > 0)
        xmlData << " name=\"" << name << "\"";
    if (attributes.size() > 0)
        xmlData << " " << attributes;
    xmlData << " d=\"";
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (i > 0)
            xmlData << ",";
        xmlData << v[i];
    }
    xmlData << "\" />";
    return xmlData.str();
}

std::string getXML0(const Ionflux::ObjectBase::UIntVector& v, 
    const std::string& name, unsigned int indentLevel, 
    const std::string& attributes)
{
    std::ostringstream xmlData;
    std::string iws = getIndent(indentLevel);
    xmlData << iws << "<" << XML_ELEMENT_NAME_UINT_VECTOR;
    if (name.size() > 0)
        xmlData << " name=\"" << name << "\"";
    if (attributes.size() > 0)
        xmlData << " " << attributes;
    xmlData << " d=\"";
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (i > 0)
            xmlData << ",";
        xmlData << v[i];
    }
    xmlData << "\" />";
    return xmlData.str();
}

std::string getXML0(const Ionflux::ObjectBase::DoubleVector& v, 
    const std::string& name, unsigned int indentLevel, 
    const std::string& attributes)
{
    std::ostringstream xmlData;
    std::string iws = getIndent(indentLevel);
    xmlData << iws << "<" << XML_ELEMENT_NAME_DOUBLE_VECTOR;
    if (name.size() > 0)
        xmlData << " name=\"" << name << "\"";
    if (attributes.size() > 0)
        xmlData << " " << attributes;
    xmlData << " d=\"";
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (i > 0)
            xmlData << ",";
        xmlData << v[i];
    }
    xmlData << "\" />";
    return xmlData.str();
}

}

}

}

/** \file xmlutils.cpp
 * \brief XML utility functions (implementation).
 */
