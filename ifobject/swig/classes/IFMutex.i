/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMutex.i                       Mutex (interface).
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
#include "ifobject/IFMutex.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFMutexClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFMutexClassInfo();
        virtual ~IFMutexClassInfo();
};

class IFMutex
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::ObjectBase::IFMutexType TYPE_DEFAULT;
		static const Ionflux::ObjectBase::IFMutexType TYPE_NORMAL;
		static const Ionflux::ObjectBase::IFMutexType TYPE_ERRORCHECK;
		static const Ionflux::ObjectBase::IFMutexType TYPE_RECURSIVE;
        
        IFMutex();
        IFMutex(Ionflux::ObjectBase::IFMutexType initType);
        virtual ~IFMutex();
        virtual bool lock();
        virtual bool tryLock();
        virtual bool unlock();
        static Ionflux::ObjectBase::IFObject* 
        create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual Ionflux::ObjectBase::IFObject* copy() const;
        virtual std::string getString() const;
        virtual Ionflux::ObjectBase::IFMutexType getType() const;
};

}

}
