#ifndef IONFLUX_OBJECT_TYPES
#define IONFLUX_OBJECT_TYPES
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * types.hpp                 Various types.
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

#include <set>
#include <vector>
#include <map>
#include <string>
#include "stdint.h"
#include "sigc++/signal.h"

namespace Ionflux
{

namespace ObjectBase
{

// integers
typedef int8_t Int8;
typedef uint8_t UInt8;
typedef int16_t Int16;
typedef uint16_t UInt16;
typedef int32_t Int32;
typedef uint32_t UInt32;
typedef int64_t Int64;
typedef uint64_t UInt64;

// unicode characters
typedef UInt32 IFUniChar;

// forward declarations
class IFObject;
struct IFObjectRefInfo;
struct IFOpParamInfo;
struct IFOpResultInfo;
struct IFOpInfo;

// other types
typedef std::string IFObjectID;
typedef std::string IFParamID;
typedef int IFIDNum;
typedef int IFEventType;
typedef	std::set<Ionflux::ObjectBase::IFObject*> IFObjectSet;
typedef	std::vector<Ionflux::ObjectBase::IFObject*> IFObjectVector;
typedef std::map<Ionflux::ObjectBase::IFObject*, IFObjectRefInfo*> IFObjectRefMap;
typedef std::string IFSignalType;
typedef int IFMutexType;
typedef sigc::signal_base* IFSignalBase;
typedef int IFAtomic;
typedef std::string IFOpName;
typedef std::vector<IFOpParamInfo> IFOpParamInfoVector;
typedef std::vector<IFOpResultInfo> IFOpResultInfoVector;
typedef std::map<IFOpName, const IFOpInfo*> IFOpNameInfoMap;
typedef std::vector<std::string> StringVector;
typedef std::vector<double> DoubleVector;
typedef std::vector<int> IntVector;
typedef std::vector<unsigned int> UIntVector;

namespace XMLUtils
{

class IFXMLObjectFactory;

}

typedef std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*> 
    XMLObjectFactoryVector;

/// Cache entry.
struct IFCacheEntry
{
    /// Item ID.
    std::string itemID;
    /// Time the entry was created.
    Ionflux::ObjectBase::UInt64 cTime;
    /// Time of the last hit.
    Ionflux::ObjectBase::UInt64 hTime;
    /// Number of hits.
    Ionflux::ObjectBase::UInt64 hits;
    /// Item.
    Ionflux::ObjectBase::IFObject* item;
};

/// Cache policy.
typedef unsigned int CachePolicy;

/// Memory management event type ID.
typedef int MMEventTypeID;

/// Line buffer.
struct LineBuffer
{
    /// Data.
    char** data;
    /// Size.
    int size;
};

/// Line buffer (constant data).
struct LineBufferConst
{
    /// Data.
    const char** data;
    /// Size.
    int size;
};

}

}

/** \file types.hpp
 * \brief Various types.
 */
#endif
