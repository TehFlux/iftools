/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMMEventHandler.i              Memory management event handler 
 * (interface).
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
#include "ifobject/IFMMEventHandler.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFMMEvent;

class IFMMEventHandlerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFMMEventHandlerClassInfo();
        virtual ~IFMMEventHandlerClassInfo();
};

class IFMMEventHandler
: public IFObject
{
    public:
        
        IFMMEventHandler();
		IFMMEventHandler(const Ionflux::ObjectBase::IFMMEventHandler& other);
        IFMMEventHandler(Ionflux::ObjectBase::IFMMEventHandler* initTarget,
        const std::string& initLogFileName = "", bool initSilentFlag = 
        true);
        virtual ~IFMMEventHandler();
        virtual void clearLogFile() const;
        virtual void handleMMEvent(const Ionflux::ObjectBase::IFMMEvent& 
        event) const;
        virtual std::string getValueString() const;
        static Ionflux::ObjectBase::IFMMEventHandler* getInstance();
        static void cleanup();
		virtual Ionflux::ObjectBase::IFMMEventHandler* copy() const;
		static Ionflux::ObjectBase::IFMMEventHandler* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::ObjectBase::IFMMEventHandler* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::ObjectBase::IFMMEventHandler* 
		create(Ionflux::ObjectBase::IFMMEventHandler* initTarget, const 
		std::string& initLogFileName = "", bool initSilentFlag = true, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setTarget(Ionflux::ObjectBase::IFMMEventHandler* 
        newTarget);
        virtual Ionflux::ObjectBase::IFMMEventHandler* getTarget() const;
        virtual void setLogFileName(const std::string& newLogFileName);
        virtual std::string getLogFileName() const;
        virtual void setSilentFlag(bool newSilentFlag);
        virtual bool getSilentFlag() const;
};

}

}
