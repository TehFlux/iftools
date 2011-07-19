#ifndef IONFLUX_OBJECT_SERIALIZE
#define IONFLUX_OBJECT_SERIALIZE
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * serialize.hpp                 Serialization utilities.
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

#include <string>
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/** Pack data (big-endian).
 *
 * Packs the data into a string. The default implementation will work for 
 * any type which can be stored byte-wise. Data is stored in big-endian order 
 * (MSB first).
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
template<class T>
void packBE(const T& source, std::string& target, bool append = true)
{
	static const unsigned int dataSize = sizeof(T);
	std::string buffer;
	buffer.assign(dataSize, '\0');
	const unsigned char* rawData = 
		reinterpret_cast<const unsigned char*>(&source);
	for (unsigned int i = 0; i < dataSize; i++)
		buffer[i] = rawData[dataSize - i - 1];
	if (append)
		target.append(buffer);
	else
		target = buffer;
}

/** Pack data (little-endian).
 *
 * Packs the data into a string. The default implementation will work for 
 * any type which can be stored byte-wise. Data is stored in little-endian 
 * order (LSB first).
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
template<class T>
void packLE(const T& source, std::string& target, bool append = true)
{
	static const unsigned int dataSize = sizeof(T);
	std::string buffer;
	buffer.assign(dataSize, '\0');
	const unsigned char* rawData = 
		reinterpret_cast<const unsigned char*>(&source);
	for (unsigned int i = 0; i < dataSize; i++)
		buffer[i] = rawData[i];
	if (append)
		target.append(buffer);
	else
		target = buffer;
}

/** Pack data.
 *
 * Packs the data into a string. The default implementation will work for 
 * any type which can be stored byte-wise.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
template<class T>
void pack(const T& source, std::string& target, bool append = true)
{
	packBE(source, target, append);
}

/** Unpack data (big-endian).
 *
 * Unpacks the data from a string. The default implementation will work for 
 * any type which can be stored byte-wise. The source data is assumed to be 
 * stored in big-endian order (MSB first).
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or -1 if the data could not be unpacked
 */
template<class T>
int unpackBE(const std::string& source, T& target, int offset = 0)
{
	static const unsigned int dataSize = sizeof(T);
	if ((offset + dataSize) > source.size())
		return -1;
	unsigned char* rawData = reinterpret_cast<unsigned char*>(&target);
	for (unsigned int i = 0; i < dataSize; i++)
		rawData[dataSize - i - 1] = source[i + offset];
	return offset + dataSize;
}

/** Unpack data (little-endian).
 *
 * Unpacks the data from a string. The default implementation will work for 
 * any type which can be stored byte-wise. The source data is assumed to be 
 * stored in little-endian order (LSB first).
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or -1 if the data could not be unpacked
 */
template<class T>
int unpackLE(const std::string& source, T& target, int offset = 0)
{
	static const unsigned int dataSize = sizeof(T);
	if ((offset + dataSize) > source.size())
		return -1;
	unsigned char* rawData = reinterpret_cast<unsigned char*>(&target);
	for (unsigned int i = 0; i < dataSize; i++)
		rawData[i] = source[i + offset];
	return offset + dataSize;
}

/** Unpack data.
 *
 * Unpacks the data from a string. The default implementation will work for 
 * any type which can be stored byte-wise.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or -1 if the data could not be unpacked
 */
template<class T>
int unpack(const std::string& source, T& target, int offset = 0)
{
    return unpackBE(source, target, offset);
}

/** Pack data (string).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
void pack(const std::string& source, std::string& target, bool append = true);

/** Unpack data (string).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or -1 if the data could not be unpacked
 */
int unpack(const std::string& source, std::string& target, 
	int offset = 0);

/** Pack data (float).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
void pack(float source, std::string& target, bool append = true);

/** Unpack data (float).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or -1 if the data could not be unpacked
 */
int unpack(const std::string& source, float& target, 
	int offset = 0);

/** Pack data (double).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
void pack(double source, std::string& target, bool append = true);

/** Unpack data (double).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or -1 if the data could not be unpacked
 */
int unpack(const std::string& source, double& target, 
	int offset = 0);

}

}

/** \file serialize.hpp
 * \brief Serialization utilities (header).
 */
#endif
