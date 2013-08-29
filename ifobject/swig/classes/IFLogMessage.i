/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFLogMessage.i                  Log message (interface).
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
#include "ifobject/IFLogMessage.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFLogMessageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFLogMessageClassInfo();
        virtual ~IFLogMessageClassInfo();
};

class IFLogMessage
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const std::string TEXT_ASSERTION;
		static const std::string TEXT_SILENT;
		static const std::string TEXT_ERROR_CRITICAL;
		static const std::string TEXT_ERROR;
		static const std::string TEXT_WARNING;
		static const std::string TEXT_WARNING_OPT;
		static const std::string TEXT_INFO;
		static const std::string TEXT_INFO_OPT;
		static const std::string TEXT_DEBUG;
		static const std::string TEXT_DEBUG_OPT;
		static const std::string TEXT_DEBUG_INSANE;
		static const std::string TEXT_ALL;
        
        IFLogMessage();
        IFLogMessage(const std::string& initMessage, 
        Ionflux::ObjectBase::IFVerbosityLevel initLevel = 
        Ionflux::ObjectBase::VL_INFO, const Ionflux::ObjectBase::IFObject* 
        initSource = 0, const std::string& initFunctionName = "");
        virtual ~IFLogMessage();
        static Ionflux::ObjectBase::IFObject* 
        create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual Ionflux::ObjectBase::IFObject* copy() const;
        static std::string 
        getLevelString(Ionflux::ObjectBase::IFVerbosityLevel otherLevel);
        static Ionflux::ObjectBase::IFVerbosityLevel 
        getLevelFromString(const std::string& levelString);
        virtual std::string getString() const;
        virtual bool serialize(std::string& target) const;
        virtual int deserialize(const std::string& source, int offset = 0);
        virtual void setMessage(const std::string& newMessage);
        virtual std::string getMessage() const;
        virtual void setLevel(Ionflux::ObjectBase::IFVerbosityLevel 
        newLevel);
        virtual Ionflux::ObjectBase::IFVerbosityLevel getLevel() const;
        virtual void setSource(const Ionflux::ObjectBase::IFObject* 
        newSource);
        virtual const Ionflux::ObjectBase::IFObject* getSource() const;
        virtual void setSourceFunctionName(const std::string& 
        newSourceFunctionName);
        virtual std::string getSourceFunctionName() const;
};

}

}
