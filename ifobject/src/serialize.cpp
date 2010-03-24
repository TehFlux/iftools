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


}

}

/** \file serialize.cpp
 * \brief Serialization utilities (implementation).
 */