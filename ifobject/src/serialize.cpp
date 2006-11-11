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

std::string pack(bool source)
{
	if (source)
		return "\1";
	return "\0";
}

std::string pack(int source)
{
	return pack(static_cast<unsigned int>(source));
}

std::string pack(unsigned int source)
{
	std::string result = "\0\0\0\0";
	for (int i = 0; i < 4; i++)
		result[i] = source & (0xff << (2 * i));
	return result;
}

std::string pack(const std::string& source)
{
	std::string result = pack(source.size());
	result.append(source);
	return result;
}

int unpackBool(const std::string source, bool& target, int offset)
{
	if (static_cast<unsigned int>(offset) >= source.size())
		return -1;
	if (source[offset] == '\1')
		target = true;
	else
		target = false;
	return offset + 1;
}

int unpackInt(const std::string source, int& target, int offset)
{
	unsigned int value = 0;
	if (unpackUInt(source, value, offset) == -1)
		return -1;
	target = static_cast<int>(value);
	return offset + 4;
}

int unpackUInt(const std::string source, unsigned int& target, int offset)
{
	if ((static_cast<unsigned int>(offset) + 3) >= source.size())
		return -1;
	target = 0;
	for (int i = 0; i < 4; i++)
		target |= ((source[offset + i] & 0xff) << (2 * i));
	return offset + 4;
}

int unpackString(const std::string source, std::string& target, int offset)
{
	unsigned int length = 0;
	if (unpackUInt(source, length, offset) == -1)
		return -1;
	offset += 4;
	if ((static_cast<unsigned int>(offset) + length - 1) >= source.size())
		return -1;
	target = source.substr(offset, length);
	return offset + length;
}

}

}

/** \file serialize.cpp
 * \brief Serialization utilities (implementation).
 */
