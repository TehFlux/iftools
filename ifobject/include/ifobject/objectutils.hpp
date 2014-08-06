#ifndef IONFLUX_OBJECT_OBJECT_UTILS
#define IONFLUX_OBJECT_OBJECT_UTILS
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2013 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * objectutils.hpp                 Object utility functions (header).
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
#include <vector>
#include <sstream>
#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "ifobject/IFError.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/// Checked allocation.
template<class T>
T* create(const Ionflux::ObjectBase::IFObject* sourceObj, 
    const std::string& source = "", const std::string& objName = "object")
{
    T* nt = new T();
    if (nt == 0)
    {
        std::ostringstream status;
        status << "Could not allocate " << objName << ".";
        throw IFError(sourceObj->getErrorString(status.str(), source));
    }
    return nt;
}

/// Null pointer check.
template<class T>
T* nullPointerCheck(T* p, const Ionflux::ObjectBase::IFObject* sourceObj, 
    const std::string& source = "", const std::string& objName = "Pointer")
{
    if (p == 0)
    {
        std::ostringstream status;
        status << objName << " is null.";
        throw IFError(sourceObj->getErrorString(status.str(), source));
    }
    return p;
}

/// Checked dynamic cast.
template<class T0, class T1>
T0* checkedDynamicCast(T1* p, 
    const Ionflux::ObjectBase::IFObject* sourceObj, 
    const std::string& source = "", const std::string& objName = "pointer", 
    const std::string& expectedType = "<unknown>")
{
    T0* result = dynamic_cast<T0*>(p);
    if (result == 0)
    {
        std::ostringstream status;
        status << objName << " has unexpected type "
            "(expected type: " << expectedType << ").";
        throw IFError(sourceObj->getErrorString(status.str(), source));
    }
    return result;
}

/// Range check.
template<class T0>
T0 rangeCheck(T0& v, const T0& lower, const T0& upper, 
    const Ionflux::ObjectBase::IFObject* sourceObj, 
    const std::string& source = "", 
    const std::string& objName = "object")
{
    if ((v < lower) 
        || (v > upper))
    {
        std::ostringstream status;
        status << objName << " out of bounds (v = " << v 
            << ", range = [" << upper << ", " << lower << "].";
        throw IFError(sourceObj->getErrorString(status.str(), source));
    }
    return v;
}

}

}

/** \file objectutils.hpp
 * \brief Object utility functions (header).
 */
#endif
