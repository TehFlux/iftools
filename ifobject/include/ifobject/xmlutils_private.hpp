#ifndef IONFLUX_OBJECT_XMLUTILS_PRIVATE
#define IONFLUX_OBJECT_XMLUTILS_PRIVATE
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2013 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils_private.hpp              XML utility functions (header).
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
#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#undef TIXML_USE_STL
#include "ifobject/constants.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/IFError.hpp"

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Find element by ID.
TiXmlElement* findElementByID(TiXmlElement* start, 
    const std::string& elementName, const std::string& elementID);

/// Find element by name.
TiXmlElement* findElementByName(TiXmlElement* start, 
    const std::string& elementName);

/// Get attribute value.
std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName);

/// Get attribute value.
void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target);

/// Get attribute value.
std::string getAttributeValue(TiXmlElement* e0, 
    const std::string& attributeName, bool optional = false);

/// Check element name.
bool checkElementName(TiXmlElement* e0, 
    const std::string& elementName);

/** Check element name.
 * If the element name does not match the expected value, throw an exception.
 */
void checkElementNameOrError(TiXmlElement* e0, 
    const std::string& elementName, 
    const std::string& source = "checkElementNameOrError");

/** Find an element by name.
 * If the element cannot be found, throw an exception.
 */
TiXmlElement* findElementByNameOrError(TiXmlElement* e0, 
    const std::string& elementName, 
    const std::string& source = "findElementByNameOrError");

/// Load document. If the document cannot be loaded, throw an exception.
void loadDocumentOrError(TiXmlDocument& d0, 
    const std::string& source = "loadDocumentOrError");

/// Initialize object from an XML element.
void getObject(TiXmlElement* e0, Ionflux::ObjectBase::IFObject& target);

/// Escape XML entities.
std::string xmlEscape(const std::string& bytes);

/// Get vector of integers from an XML element.
void getIntVector(TiXmlElement* e0, 
    Ionflux::ObjectBase::IntVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);

/// Get vector of unsigned integers from an XML element.
void getUIntVector(TiXmlElement* e0, 
    Ionflux::ObjectBase::UIntVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);

/// Get vector of doubles from an XML element.
void getDoubleVector(TiXmlElement* e0, 
    Ionflux::ObjectBase::DoubleVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);

/// Initialize an object from an XML element.
template<class T>
void getObject0(TiXmlElement* e0, T& target, 
    const std::string& elementName)
{
    checkElementNameOrError(e0, elementName, "getObject0");
    getObject(e0, target);
}

/// Get vector of objects from an XML element.
template<class T, class TP>
void getObjVector(TiXmlElement* e0, 
    std::vector<TP>& target, const std::string& elementName = "vec", 
    const std::string& childElementName = "")
{
    checkElementNameOrError(e0, elementName, "getObjVector");
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    {
        const char* a0 = ce0->Value();
        if (std::string(a0) == childElementName)
        {
            TP co0 = T::create();
            getObject0(ce0, *co0, childElementName);
            target.push_back(co0);
        }
        ce0 = ce0->NextSiblingElement();
    }
}

/// Load object from XML file.
template<class T>
void loadFromFile(const std::string& fileName, T& target, 
    const std::string& elementName)
{
    TiXmlDocument d0(fileName.c_str());
    loadDocumentOrError(d0, "loadFromFile");
    TiXmlElement* m0 = findElementByNameOrError(d0.RootElement(), 
        elementName);
    getObject0(m0, target, elementName);
}

/// Get dictionary of objects from an XML element.
template<class T, class TP>
void getObjMap(TiXmlElement* e0, 
    std::map<std::string, TP>& target, const std::string& elementName = "vec", 
    const std::string& childElementName = "")
{
    checkElementNameOrError(e0, elementName, "getObjMap");
    TiXmlElement* ee0 = e0->FirstChildElement();
    while (ee0 != 0)
    {
        const char* a0 = ee0->Value();
        if (std::string(a0) == "entry")
        {
            std::string k = getAttributeValue(ee0, "key");
            TiXmlElement* ce0 = findElementByNameOrError(ee0, 
                childElementName, "getObjMap");
            TP co0 = T::create();
            getObject0(ce0, *co0, childElementName);
            typename std::map<std::string, TP>::iterator j = target.find(k);
            if (j != target.end())
            {
                std::ostringstream status;
                status << "[getObjMap] Duplicate key: '" << k << "'";
                throw IFError(status.str());
            }
            target[k] = co0;
        }
        ee0 = ee0->NextSiblingElement();
    }
}

}

}

}

/** \file xmlutils_private.hpp
 * \brief XML utility functions (header).
 */
#endif
