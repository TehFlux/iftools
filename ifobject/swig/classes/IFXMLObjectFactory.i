/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFXMLObjectFactory.i            XML object factory (interface).
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
%{
#include "ifobject/IFXMLObjectFactory.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

class IFXMLObjectFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFXMLObjectFactoryClassInfo();
        virtual ~IFXMLObjectFactoryClassInfo();
};

class IFXMLObjectFactory
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        IFXMLObjectFactory();
		IFXMLObjectFactory(const Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& other);
        virtual ~IFXMLObjectFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual Ionflux::ObjectBase::IFObject* createObject();
        virtual std::string getValueString() const;
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* copy() const;
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumFactories() const;
        virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
        getFactory(unsigned int elementIndex = 0) const;
		virtual int 
		findFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* needle, 
		unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>& 
        getFactories();
        virtual void 
        addFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
        addElement);
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* addFactory();
		virtual void 
		addFactories(std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>&
		newFactories);
		virtual void 
		addFactories(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		newFactories);        
        virtual void 
        removeFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
        removeElement);
		virtual void removeFactoryIndex(unsigned int removeIndex);
		virtual void clearFactories();
};

}

}

}
