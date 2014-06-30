#ifndef IONFLUX_OBJECT_IFXMLOBJECTFACTORY
#define IONFLUX_OBJECT_IFXMLOBJECTFACTORY
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFXMLObjectFactory.hpp          XML object factory (header).
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

#include "ifobject/types.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

/// Class information for class IFXMLObjectFactory.
class IFXMLObjectFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFXMLObjectFactoryClassInfo();
		/// Destructor.
		virtual ~IFXMLObjectFactoryClassInfo();
};

/** XML object factory.
 * \ingroup ifobject
 *
 * A factory that creates objects from XML data.
 */
class IFXMLObjectFactory
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Child XML object factories.
		std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*> factories;
		
	public:
		/// Class information instance.
		static const IFXMLObjectFactoryClassInfo iFXMLObjectFactoryClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFXMLObjectFactory object.
		 */
		IFXMLObjectFactory();
		
		/** Constructor.
		 *
		 * Construct new IFXMLObjectFactory object.
		 *
		 * \param other Other object.
		 */
		IFXMLObjectFactory(const Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& other);
		
		/** Destructor.
		 *
		 * Destruct IFXMLObjectFactory object.
		 */
		virtual ~IFXMLObjectFactory();
		
		/** Get XML element name.
		 *
		 * Get the XML element name that this factory creates objects for.
		 *
		 * \return XML element name.
		 */
		virtual std::string getObjectXMLElementName() const;
		
		/** Get class name.
		 *
		 * Get the name of the class this factory creates objects for. This 
		 * should be overridden by derived classes to return the name of the 
		 * base type.
		 *
		 * \return Class name.
		 */
		virtual std::string getObjectClassName() const;
		
		/** Initialize object.
		 *
		 * Initialize an object from an XML element. This should be overridden
		 * by derived classes to initialize an object of the base type.
		 *
		 * \param xmlElement XML element.
		 * \param target Target object.
		 * \param elementName XML element name.
		 */
		virtual void initObject(TiXmlElement* xmlElement, 
		Ionflux::ObjectBase::IFObject* target, const std::string& elementName = 
		"") const;
		
		/** Initialize object.
		 *
		 * Initialize an object from an XML element.
		 *
		 * \param xmlElement XML element.
		 * \param target Target object.
		 * \param elementName XML element name.
		 */
		virtual void initObject(TiXmlElement* xmlElement, 
		Ionflux::ObjectBase::IFObject& target, const std::string& elementName = 
		"") const;
		
		/** Initialize object.
		 *
		 * Initialize an object from XML data.
		 *
		 * \param data XML data.
		 * \param target Target object.
		 */
		virtual void initObject(const std::string& data, 
		Ionflux::ObjectBase::IFObject& target) const;
		
		/** Create new object.
		 *
		 * Create a new object. This should be overridden by derived classes 
		 * to create a new object of the base type.
		 *
		 * \return New object.
		 */
		virtual Ionflux::ObjectBase::IFObject* createObject() const;
		
		/** Create object.
		 *
		 * Create a new object from an XML element.
		 *
		 * \param xmlElement XML element.
		 * \param elementName XML element name.
		 *
		 * \return New object.
		 */
		virtual Ionflux::ObjectBase::IFObject* createObject(TiXmlElement* 
		xmlElement, const std::string& elementName = "") const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& 
		operator=(const Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of factories.
		 *
		 * \return Number of factories.
		 */
		virtual unsigned int getNumFactories() const;
		
		/** Get factory.
		 *
		 * Get the factory at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Factory at specified index.
		 */
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getFactory(unsigned int elementIndex = 0) const;
		
		/** Find factory.
		 *
		 * Find the specified occurence of a factory.
		 *
		 * \param needle Factory to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the factory, or -1 if the factory cannot be found.
		 */
		virtual int 
		findFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* needle, 
		unsigned int occurence = 1) const;
        
		/** Get child XML object factories.
		 *
		 * \return child XML object factories.
		 */
		virtual std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>& 
		getFactories();
		
		/** Add factory.
		 *
		 * Add a factory.
		 *
		 * \param addElement Factory to be added.
		 */
		virtual void 
		addFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		addElement);
		
		/** Create factory.
		 *
		 * Create a new factory which is managed by the factory set.
		 *
		 * \return New factory.
		 */
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* addFactory();
		
		/** Add factories.
		 *
		 * Add factories from a factory vector.
		 *
		 * \param newFactories factories.
		 */
		virtual void addFactories(const 
		std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>& 
		newFactories);
		
		/** Add factories.
		 *
		 * Add factories from a factory set.
		 *
		 * \param newFactories factories.
		 */
		virtual void 
		addFactories(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		newFactories);
		
		/** Remove factory.
		 *
		 * Remove a factory.
		 *
		 * \param removeElement Factory to be removed.
		 */
		virtual void 
		removeFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		removeElement);
		
		/** Remove factory.
		 *
		 * Remove a factory.
		 *
		 * \param removeIndex Factory to be removed.
		 */
		virtual void removeFactoryIndex(unsigned int removeIndex);
		
		/** Clear factories.
		 *
		 * Clear all factories.
		 */
		virtual void clearFactories();
};

}

}

}

/** \file IFXMLObjectFactory.hpp
 * \brief XML object factory (header).
 */
#endif
