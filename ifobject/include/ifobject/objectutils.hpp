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
T* create(Ionflux::ObjectBase::IFObject* sourceObj, 
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
T* nullPointerCheck(T* p, Ionflux::ObjectBase::IFObject* sourceObj, 
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

}

}

/** \file objectutils.hpp
 * \brief Object utility functions (header).
 */
#endif
