/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFClassInfo.i                   Class information (interface).
 * =========================================================================

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
#include "ifobject/IFClassInfo.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFClassInfo;

typedef std::vector<const Ionflux::ObjectBase::IFClassInfo*> IFClassInfoVector;
 
struct IFOpParamInfo
{
    const Ionflux::ObjectBase::IFClassInfo* type;
    std::string name;
    std::string desc;
    bool optional;
    Ionflux::ObjectBase::IFObject* defaultValue;
};
 
struct IFOpResultInfo
{
    const Ionflux::ObjectBase::IFClassInfo* type;
    std::string desc;
};
 
struct IFOpInfo
{
    Ionflux::ObjectBase::IFOpName name;
    Ionflux::ObjectBase::IFOpParamInfoVector paramInfo;
    Ionflux::ObjectBase::IFOpResultInfoVector resultInfo;
};

class IFClassInfo
{
    public:
        
        IFClassInfo();
        virtual ~IFClassInfo();
        virtual int getNumBaseClasses() const;
        virtual const Ionflux::ObjectBase::IFClassInfo* 
        getBaseClassInfo(unsigned int index) const;
        virtual bool isDerivedFrom(const Ionflux::ObjectBase::IFClassInfo* 
        searchClass, bool recursive = true) const;
        virtual bool isBaseOf(const Ionflux::ObjectBase::IFClassInfo* 
        checkClass, bool recursive = true) const;
        virtual bool isDerivedFrom(const std::string& searchClassName, bool
        recursive = true) const;
        virtual void getOpInfo(Ionflux::ObjectBase::IFOpNameInfoMap& 
        target) const;
        virtual const Ionflux::ObjectBase::IFOpInfo* getOpInfo(const 
        Ionflux::ObjectBase::IFOpName& opName) const;
        virtual std::string getName() const;
        virtual std::string getDesc() const;
};

}

}
