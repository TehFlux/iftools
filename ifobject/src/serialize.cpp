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
#include <arpa/inet.h>

namespace Ionflux
{

namespace ObjectBase
{

void pack(const std::string& source, std::string& target, bool append)
{
	std::string buffer;
	pack(static_cast<unsigned int>(source.size()), buffer, false);
	buffer.append(source);
	if (append)
		target.append(buffer);
	else
		target = buffer;
}

int unpack(const std::string& source, std::string& target, 
	int offset)
{
	unsigned int dataSize = 0;
	offset = unpack(source, dataSize, offset);
	if ((offset == -1)
		|| ((offset + dataSize) > source.size()))
		return -1;
	target = source.substr(offset, dataSize);
	offset += dataSize;
	return offset;
}

void pack(float source, std::string& target, bool append)
{
    packBE(source, target, append);
}

int unpack(const std::string& source, float& target, int offset)
{
    return unpackBE(source, target, offset);
}

void pack(double source, std::string& target, bool append)
{
    packBE(source, target, append);
}

int unpack(const std::string& source, double& target, int offset)
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
    int offset)
{
	bool isNonNull = false;
	unpack(source, isNonNull, offset);
	return isNonNull;
}

int unpackObj(const std::string& source, Ionflux::ObjectBase::IFObject*& target, 
    int offset)
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
    UInt64 s0 = source.size();
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

int unpack(const std::string& source, 
    Ionflux::ObjectBase::PointerOffsetMap& target, int offset)
{
    UInt64 s0 = 0;
    int o0 = unpack(source, s0, offset);
    for (UInt64 i = 0; i < s0; i++)
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

}

}

/** \file serialize.cpp
 * \brief Serialization utilities (implementation).
 */
