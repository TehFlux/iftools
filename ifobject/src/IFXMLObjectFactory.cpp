/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFXMLObjectFactory.cpp          XML object factory (implementation).
 * =========================================================================
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

#include "ifobject/IFXMLObjectFactory.hpp"
#include "ifobject/xmlutils_private.hpp"
#include "ifobject/IFError.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

IFXMLObjectFactoryClassInfo::IFXMLObjectFactoryClassInfo()
{
	name = "IFXMLObjectFactory";
	desc = "XML object factory";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

IFXMLObjectFactoryClassInfo::~IFXMLObjectFactoryClassInfo()
{
}

// run-time type information instance constants
const IFXMLObjectFactoryClassInfo IFXMLObjectFactory::iFXMLObjectFactoryClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFXMLObjectFactory::CLASS_INFO = &IFXMLObjectFactory::iFXMLObjectFactoryClassInfo;

IFXMLObjectFactory::IFXMLObjectFactory()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFXMLObjectFactory::IFXMLObjectFactory(const Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

IFXMLObjectFactory::~IFXMLObjectFactory()
{
	clearFactories();
	// TODO: Nothing ATM. ;-)
}

std::string IFXMLObjectFactory::getObjectXMLElementName() const
{
	// TODO: Implementation.
	return Ionflux::ObjectBase::IFObject::XML_ELEMENT_NAME;
}

std::string IFXMLObjectFactory::getObjectClassName() const
{
	/* NOTE: This should be obtained via a global singleton IFClassInfo 
	         instance of the appropriate type. */
	return "IFObject";
}

void IFXMLObjectFactory::initObject(TiXmlElement* xmlElement, 
Ionflux::ObjectBase::IFObject* target, const std::string& elementName) 
const
{
	if (xmlElement == 0)
	    throw IFError(getErrorString("XML element is null.", "initObject"));
	if (target == 0)
	    throw IFError(getErrorString("Target object is null.", "initObject"));
	checkElementNameOrError(xmlElement, elementName, 
	    "IFXMLObjectFactory::init");
	Ionflux::ObjectBase::XMLUtils::getObject(xmlElement, *target);
}

Ionflux::ObjectBase::IFObject* IFXMLObjectFactory::createObject()
{
	// TODO: Implementation.
	return IFObject::create();
}

Ionflux::ObjectBase::IFObject* 
IFXMLObjectFactory::createObject(TiXmlElement* xmlElement, const 
std::string& elementName)
{
	std::string en0(xmlElement->Value());
	IFObject* o0 = 0;
	if (en0 == getObjectXMLElementName())
	{
	    // Create an object of the base type.
	    o0 = createObject();
	    initObject(xmlElement, o0, en0);
	} else
	{
	    unsigned int k = 0;
	    unsigned int numFactories = getNumFactories();
	    while ((k < numFactories) 
	        && (o0 == 0))
	    {
	        IFXMLObjectFactory* f0 = getFactory(k);
	        if (en0 == f0->getObjectXMLElementName())
	            o0 = f0->createObject(xmlElement, en0);
	        k++;
	    }
	    if (o0 == 0)
	    {
	        std::ostringstream status;
	        status << "Unexpected child element name: '" << en0 << "'";
	        throw IFError(getErrorString(status.str(), "createObject"));
	    }
	}
	return o0;
}

std::string IFXMLObjectFactory::getValueString() const
{
	ostringstream status;
	status << getObjectClassName() << "; <" << getObjectXMLElementName() 
	    << ">; [";
	bool e0 = true;
	for (XMLObjectFactoryVector::const_iterator i = factories.begin(); 
	    i != factories.end(); i++)
	{
	    if (!e0)
	        status << ", ";
	    else
	        e0 = false;
	    status << "(" << (*i)->getValueString() << ")";
	}
	if (factories.size() == 0)
	    status << "<none>";
	status << "]";
	return status.str();
}

unsigned int IFXMLObjectFactory::getNumFactories() const
{
    return factories.size();
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
IFXMLObjectFactory::getFactory(unsigned int elementIndex) const
{
    if (elementIndex < factories.size())
		return factories[elementIndex];
	return 0;
}

int 
IFXMLObjectFactory::findFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* currentFactory = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < factories.size()))
	{
		currentFactory = factories[i];
		if (currentFactory == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>& 
IFXMLObjectFactory::getFactories()
{
    return factories;
}

void 
IFXMLObjectFactory::addFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*
addElement)
{
	addLocalRef(addElement);
	factories.push_back(addElement);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
IFXMLObjectFactory::addFactory()
{
	Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* o0 = IFXMLObjectFactory::create();
	addFactory(o0);
	return o0;
}

void IFXMLObjectFactory::addFactories(const 
std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>& 
newFactories)
{
	for (std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>::const_iterator i = newFactories.begin(); 
	    i != newFactories.end(); i++)
	    addFactory(*i);
}

void 
IFXMLObjectFactory::addFactories(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*
newFactories)
{
	for (unsigned int i = 0; 
	    i < newFactories->getNumFactories(); i++)
	    addFactory(newFactories->getFactory(i));
}

void 
IFXMLObjectFactory::removeFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*
removeElement)
{
    bool found = false;
	Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* currentFactory = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < factories.size()))
	{
		currentFactory = factories[i];
		if (currentFactory == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		factories.erase(factories.begin() + i);
		if (currentFactory != 0)
			removeLocalRef(currentFactory);
	}
}

void IFXMLObjectFactory::removeFactoryIndex(unsigned int removeIndex)
{
    if (removeIndex > factories.size())
        return;
	Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* e0 = factories[removeIndex];
    factories.erase(factories.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void IFXMLObjectFactory::clearFactories()
{
    std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>::iterator i;
	for (i = factories.begin(); i != factories.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	factories.clear();
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& 
IFXMLObjectFactory::operator=(const 
Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& other)
{
    if (this == &other)
        return *this;
    XMLObjectFactoryVector v0;
    for (XMLObjectFactoryVector::const_iterator i = 
        other.factories.begin(); i != other.factories.end(); i++)
        v0.push_back((*i)->copy());
    clearFactories();
    addFactories(v0);
	return *this;
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
IFXMLObjectFactory::copy() const
{
    IFXMLObjectFactory* newIFXMLObjectFactory = create();
    *newIFXMLObjectFactory = *this;
    return newIFXMLObjectFactory;
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
IFXMLObjectFactory::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<IFXMLObjectFactory*>(other);
}

Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
IFXMLObjectFactory::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    IFXMLObjectFactory* newObject = new IFXMLObjectFactory();
    if (newObject == 0)
    {
        throw IFError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

}

/** \file IFXMLObjectFactory.cpp
 * \brief XML object factory implementation.
 */
