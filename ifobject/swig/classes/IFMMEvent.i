/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMMEvent.i                     Memory Management Event (interface).
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
#include "ifobject/IFMMEvent.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFMMEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFMMEventClassInfo();
        virtual ~IFMMEventClassInfo();
};

class IFMMEvent
: public IFObject
{
    public:
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_UNDEFINED;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_CREATE;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_DELETE;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_ADD_REF;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_REMOVE_REF;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_ADD_LOCAL_REF;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_REMOVE_LOCAL_REF;
        
        IFMMEvent();
		IFMMEvent(const Ionflux::ObjectBase::IFMMEvent& other);
        IFMMEvent(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
        Ionflux::ObjectBase::IFObject* initObject, unsigned int 
        initObjectRefCount = 0, const Ionflux::ObjectBase::IFObject* 
        initParentObject = 0);
        virtual ~IFMMEvent();
        virtual bool operator==(const Ionflux::ObjectBase::IFMMEvent& 
        other) const;
        virtual bool operator!=(const Ionflux::ObjectBase::IFMMEvent& 
        other) const;
        virtual std::string getValueString() const;
		virtual Ionflux::ObjectBase::IFMMEvent* copy() const;
		static Ionflux::ObjectBase::IFMMEvent* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::ObjectBase::IFMMEvent* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::ObjectBase::IFMMEvent* 
		create(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
		Ionflux::ObjectBase::IFObject* initObject, unsigned int 
		initObjectRefCount = 0, const Ionflux::ObjectBase::IFObject* 
		initParentObject = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setTypeID(Ionflux::ObjectBase::MMEventTypeID 
        newTypeID);
        virtual Ionflux::ObjectBase::MMEventTypeID getTypeID() const;
        virtual void setObject(const Ionflux::ObjectBase::IFObject* 
        newObject);
        virtual const Ionflux::ObjectBase::IFObject* getObject() const;
        virtual void setObjectRefCount(unsigned int newObjectRefCount);
        virtual unsigned int getObjectRefCount() const;
        virtual void setParentObject(const Ionflux::ObjectBase::IFObject* 
        newParentObject);
        virtual const Ionflux::ObjectBase::IFObject* getParentObject() 
        const;
};

}

}
