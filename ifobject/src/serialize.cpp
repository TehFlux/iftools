/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * serialize.cpp                 Serialization utilities.
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

#include "ifobject/serialize.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/IFObject.hpp"
#include <sstream>
#include <iomanip>
#include <arpa/inet.h>

namespace Ionflux
{

namespace ObjectBase
{

void pack(const std::string& source, std::string& target, bool append)
{
	std::string buffer;
	pack(static_cast<DataSize>(source.size()), buffer, false);
	buffer.append(source);
	if (append)
		target.append(buffer);
	else
		target = buffer;
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    std::string& target, Ionflux::ObjectBase::DataSize offset)
{
	DataSize dataSize = 0;
	offset = unpack(source, dataSize, offset);
	if ((offset == DATA_SIZE_INVALID)
		|| ((offset + dataSize) > source.size()))
		return DATA_SIZE_INVALID;
	target = source.substr(offset, dataSize);
	offset += dataSize;
	return offset;
}

void pack(float source, std::string& target, bool append)
{
    packBE(source, target, append);
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    float& target, Ionflux::ObjectBase::DataSize offset)
{
    return unpackBE(source, target, offset);
}

void pack(double source, std::string& target, bool append)
{
    packBE(source, target, append);
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    double& target, Ionflux::ObjectBase::DataSize offset)
{
    return unpackBE(source, target, offset);
}

void packObj(const Ionflux::ObjectBase::IFObject* source, std::string& 
target, bool append)
{
	std::string buffer;
	if (source == 0)
		pack(false, buffer);
	else
	{
		pack(true, buffer);
		source->serialize(buffer);
	}
	if (append)
		target.append(buffer);
	else
		target = buffer;
}

bool unpackNonNullCheck(const std::string& source, 
    Ionflux::ObjectBase::DataSize offset)
{
	bool isNonNull = false;
	unpack(source, isNonNull, offset);
	return isNonNull;
}

Ionflux::ObjectBase::DataSize unpackObj(const std::string& source, 
    Ionflux::ObjectBase::IFObject*& target, 
    Ionflux::ObjectBase::DataSize offset)
{
	bool isNonNull = false;
	offset = unpack(source, isNonNull, offset);
	if (!isNonNull)
	{
	    target = 0;
		return offset;
	}
	Ionflux::ObjectBase::nullPointerCheck(target, "unpack", "Target object");
    offset = target->deserialize(source, offset);
	return offset;
}

void pack(const Ionflux::ObjectBase::PointerOffsetMap& source, 
    std::string& target, bool append)
{
    std::string t0;
    DataSize s0 = source.size();
    pack(s0, t0, true);
    for (PointerOffsetMap::const_iterator i = source.begin(); 
        i != source.end(); i++)
    {
        pack(reinterpret_cast<UInt64>((*i).first), t0, true);
        pack((*i).second, t0, true);
    }
	if (append)
		target.append(t0);
	else
		target = t0;
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::ObjectBase::PointerOffsetMap& target, 
    Ionflux::ObjectBase::DataSize offset)
{
    DataSize s0 = 0;
    DataSize o0 = unpack(source, s0, offset);
    for (DataSize i = 0; i < s0; i++)
    {
        UInt64 k0 = 0;
        UInt64 v0 = 0;
        o0 = unpack(source, k0, o0);
        o0 = unpack(source, v0, o0);
        GenericPointer p0 = reinterpret_cast<GenericPointer>(k0);
        target[p0] = v0;
    }
    return o0;
}

Ionflux::ObjectBase::MagicWord createMagicWord(
    Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1)
{
    return ((static_cast<MagicWord>(s0) << 16) 
        | static_cast<MagicWord>(s1));
}

void pack(
    Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1, 
    std::string& target, bool append)
{
    MagicWord w = createMagicWord(s0, s1);
    pack(w, target, append);
}

Ionflux::ObjectBase::DataSize unpackAndCheckMagicWord(
    const std::string& source, Ionflux::ObjectBase::MagicWord w, 
    Ionflux::ObjectBase::DataSize offset, 
    const Ionflux::ObjectBase::IFObject* sourceObj, 
    const std::string& sourceName)
{
    MagicWord t0;
    DataSize o0 = unpack(source, t0, offset);
    if (o0 == DATA_SIZE_INVALID)
    {
        std::ostringstream status;
        status << "Could not deserialize magic word (offset = " 
            << offset << ", source.size = " << source.size() << ").";
        throw IFError(getErrorString(status.str(), sourceName, 
            sourceObj));
    }
    if (t0 != w)
    {
        std::ostringstream status;
        status << "Magic word not found (offset = " 
            << o0 << ", source.size = " << source.size() 
            << ", magicWord = 0x" << std::right << std::setfill('0') 
            << std::hex << w << ").";
        throw IFError(getErrorString(status.str(), sourceName, 
            sourceObj));
    }
    return o0;
}

Ionflux::ObjectBase::DataSize unpackAndCheckMagicWord(
    const std::string& source, Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1, 
    Ionflux::ObjectBase::DataSize offset, 
    const Ionflux::ObjectBase::IFObject* sourceObj, 
    const std::string& sourceName)
{
    MagicWord w0 = createMagicWord(s0, s1);
    return unpackAndCheckMagicWord(source, w0, offset, 
        sourceObj, sourceName);
}

}

}

/** \file serialize.cpp
 * \brief Serialization utilities (implementation).
 */
