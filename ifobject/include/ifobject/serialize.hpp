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
#include <iostream>
#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/IFError.hpp"

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
	static const DataSize dataSize = sizeof(T);
	std::string buffer;
	buffer.assign(dataSize, '\0');
	const unsigned char* rawData = 
		reinterpret_cast<const unsigned char*>(&source);
	for (DataSize i = 0; i < dataSize; i++)
		buffer[i] = rawData[dataSize - i - 1];
	if (append)
		target.append(buffer);
	else
		target = buffer;
}

/** Pack data to stream (big-endian).
 *
 * Packs the data into a stream. The default implementation will work for 
 * any type which can be stored byte-wise. Data is stored in big-endian order 
 * (MSB first).
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
template<class T>
void packBE(const T& source, std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
	std::string buffer;
	packBE(source, buffer, false);
	writeToStream(target, buffer, offset);
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
	static const DataSize dataSize = sizeof(T);
	std::string buffer;
	buffer.assign(dataSize, '\0');
	const unsigned char* rawData = 
		reinterpret_cast<const unsigned char*>(&source);
	for (DataSize i = 0; i < dataSize; i++)
		buffer[i] = rawData[i];
	if (append)
		target.append(buffer);
	else
		target = buffer;
}

/** Pack data to stream (little-endian).
 *
 * Packs the data into a stream. The default implementation will work for 
 * any type which can be stored byte-wise. Data is stored in little-endian 
 * order (LSB first).
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
template<class T>
void packLE(const T& source, std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
	std::string buffer;
	packLE(source, buffer, false);
	writeToStream(target, buffer, offset);
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

/** Pack data.
 *
 * Packs the data into a string. The default implementation will work for 
 * any type which can be stored byte-wise.
 *
 * \param source data to be packed
 * \param target target stream
 * \param append whether data should be appended to or replace the target data
 */
template<class T>
void pack(const T& source, std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
	packBE(source, target, offset);
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
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class T>
Ionflux::ObjectBase::DataSize unpackBE(const std::string& source, T& target, 
    Ionflux::ObjectBase::DataSize offset = 0)
{
	static const DataSize dataSize = sizeof(T);
	if ((offset + dataSize) > source.size())
		return DATA_SIZE_INVALID;
	unsigned char* rawData = reinterpret_cast<unsigned char*>(&target);
	for (DataSize i = 0; i < dataSize; i++)
		rawData[dataSize - i - 1] = source[i + offset];
	return offset + dataSize;
}

/** Unpack data (big-endian).
 *
 * Unpacks the data from a stream. The default implementation will work for 
 * any type which can be stored byte-wise. The source data is assumed to be 
 * stored in big-endian order (MSB first).
 *
 * \param source source stream
 * \param target where to store the unpacked data
 * \param offset stream offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class T>
Ionflux::ObjectBase::DataSize unpackBE(std::istream& source, T& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
	static const DataSize s0 = sizeof(T);
    std::string t0;
    DataSize s1 = readFromStream(source, t0, s0, offset);
    if (s1 < s0)
    {
        std::ostringstream status;
        status << "[unpack] " 
            "Could not unpack data from stream (size = " << s0;
        if (offset != DATA_SIZE_INVALID)
            status << ", offset = " << offset;
        status << ").";
        throw IFError(status.str());
    }
    unpackBE(t0, target, 0);
    return source.tellg();
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
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class T>
Ionflux::ObjectBase::DataSize unpackLE(const std::string& source, T& target, 
    Ionflux::ObjectBase::DataSize offset = 0)
{
	static const DataSize dataSize = sizeof(T);
	if ((offset + dataSize) > source.size())
		return DATA_SIZE_INVALID;
	unsigned char* rawData = reinterpret_cast<unsigned char*>(&target);
	for (DataSize i = 0; i < dataSize; i++)
		rawData[i] = source[i + offset];
	return offset + dataSize;
}

/** Unpack data (little-endian).
 *
 * Unpacks the data from a stream. The default implementation will work for 
 * any type which can be stored byte-wise. The source data is assumed to be 
 * stored in little-endian order (LSB first).
 *
 * \param source source stream
 * \param target where to store the unpacked data
 * \param offset stream offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class T>
Ionflux::ObjectBase::DataSize unpackLE(std::istream& source, T& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
	static const DataSize s0 = sizeof(T);
    std::string t0;
    DataSize s1 = readFromStream(source, t0, s0, offset);
    if (s1 < s0)
    {
        std::ostringstream status;
        status << "[unpack] " 
            "Could not unpack data from stream (size = " << s0;
        if (offset != DATA_SIZE_INVALID)
            status << ", offset = " << offset;
        status << ").";
        throw IFError(status.str());
    }
    unpackLE(t0, target, 0);
    return source.tellg();
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
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class T>
Ionflux::ObjectBase::DataSize unpack(const std::string& source, T& target, 
    Ionflux::ObjectBase::DataSize offset = 0)
{
    return unpackBE(source, target, offset);
}

/** Unpack data.
 *
 * Unpacks the data from a stream. The default implementation will work for 
 * any type which can be stored byte-wise.
 *
 * \param source source stream
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class T>
Ionflux::ObjectBase::DataSize unpack(std::istream& source, T& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
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
void pack(const std::string& source, std::string& target, 
    bool append = true);

/** Pack data (string).
 *
 * Packs the data into a stream.
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
void pack(const std::string& source, std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Unpack data (string).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    std::string& target, Ionflux::ObjectBase::DataSize offset = 0);

/** Unpack data (string).
 *
 * Unpacks the data from a stream.
 *
 * \param source source stream
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(std::istream& source, 
    std::string& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Pack data (float).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
void pack(float source, std::string& target, bool append = true);

/** Pack data (float).
 *
 * Packs the data into a stream.
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
void pack(float source, std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Unpack data (float).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    float& target, Ionflux::ObjectBase::DataSize offset = 0);

/** Unpack data (float).
 *
 * Unpacks the data from a stream.
 *
 * \param source source stream
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(std::istream& source, 
    float& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Pack data (double).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
void pack(double source, std::string& target, bool append = true);

/** Pack data (double).
 *
 * Packs the data into a stream.
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
void pack(double source, std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Unpack data (double).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    double& target, Ionflux::ObjectBase::DataSize offset = 0);

/** Unpack data (double).
 *
 * Unpacks the data from a stream.
 *
 * \param source source stream
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(std::istream& source, 
    double& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Pack object.
 *
 * Pack an object into a string. This uses the serialize() method of the
 * object to obtain a serialized representation of the persistent state 
 * of the object, which is then stored in the target buffer. The data 
 * will be prefixed by \c true if the object is non-null and by \c false
 * if the object is null.
 *
 * \param source source object.
 * \param target where to store the packed data.
 * \param append whether data should be appended to or replace the target 
 * data.
 */
void packObj(const Ionflux::ObjectBase::IFObject* source, 
    std::string& target, bool append = true);

/** Pack object.
 *
 * Pack an object into a stream. This uses the serialize() method of the
 * object to obtain a serialized representation of the persistent state 
 * of the object, which is then stored in the target stream. The data 
 * will be prefixed by \c true if the object is non-null and by \c false
 * if the object is null.
 *
 * \param source source object.
 * \param target target stream.
 * \param append whether data should be appended to or replace the target 
 * data.
 */
void packObj(const Ionflux::ObjectBase::IFObject* source, 
    std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Non-null object check.
 *
 * Check whether the next object to be unpacked is non-null.
 *
 * \param source data to be unpacked.
 * \param offset offset from which to start unpacking.
 *
 * \return \c true if the object is non-null, \c false otherwise.
 */
bool unpackNonNullCheck(const std::string& source, 
    Ionflux::ObjectBase::DataSize offset = 0);

/** Non-null object check.
 *
 * Check whether the next object to be unpacked is non-null.
 *
 * \param source data to be unpacked.
 * \param offset offset from which to start unpacking.
 *
 * \return \c true if the object is non-null, \c false otherwise.
 */
bool unpackNonNullCheck(std::istream& source, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Unpack object.
 *
 * Unpack an object from a string. This uses the deserialize() method of
 * the object to restore the persistent state of the child object from 
 * the source buffer. The source data must start with a packed boolean 
 * value to indicate whether the object is non-null. If the object is null, 
 * \c target will be set to null.
 *
 * \sa unpackNonNullCheck()
 *
 * \param source data to be unpacked.
 * \param target where to store the unpacked data.
 * \param offset offset from which to start unpacking.
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked.
 */
Ionflux::ObjectBase::DataSize unpackObj(const std::string& source, 
    Ionflux::ObjectBase::IFObject*& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/** Unpack object.
 *
 * Unpack an object from a stream. This uses the deserialize() method of
 * the object to restore the persistent state of the child object from 
 * the source buffer. The source data must start with a packed boolean 
 * value to indicate whether the object is non-null. If the object is null, 
 * \c target will be set to null.
 *
 * \sa unpackNonNullCheck()
 *
 * \param source source stream.
 * \param target where to store the unpacked data.
 * \param offset offset from which to start unpacking.
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked.
 */
Ionflux::ObjectBase::DataSize unpackObj(std::istream& source, 
    Ionflux::ObjectBase::IFObject*& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Pack data (PointerOffsetMap).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
void pack(const Ionflux::ObjectBase::PointerOffsetMap& source, 
    std::string& target, bool append = true);

/** Pack data (PointerOffsetMap).
 *
 * Packs the data into a stream.
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
void pack(const Ionflux::ObjectBase::PointerOffsetMap& source, 
    std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Unpack data (PointerOffsetMap).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::ObjectBase::PointerOffsetMap& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/** Unpack data (PointerOffsetMap).
 *
 * Unpacks the data from a stream.
 *
 * \param source source stream.
 * \param target where to store the unpacked data.
 * \param offset offset from which to start unpacking.
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
Ionflux::ObjectBase::DataSize unpack(std::istream& source, 
    Ionflux::ObjectBase::PointerOffsetMap& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Create magic word.
 *
 * Create a magic word from two syllables.
 *
 * \param s0 syllable (0)
 * \param s1 syllable (1)
 *
 * \return magic word
 */
Ionflux::ObjectBase::MagicWord createMagicWord(
    Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1);

/** Pack magic syllables.
 *
 * Packs the two magic syllables into a string as a magic word.
 *
 * \param s0 magic syllable to be packed (0)
 * \param s1 magic syllable to be packed (1)
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
void pack(
    Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1, 
    std::string& target, bool append = true);

/** Pack magic syllables.
 *
 * Packs the two magic syllables into a stream as a magic word.
 *
 * \param s0 magic syllable to be packed (0)
 * \param s1 magic syllable to be packed (1)
 * \param target target stream
 * \param offset stream offset
 */
void pack(
    Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1, 
    std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID);

/** Unpack and check magic word.
 *
 * Unpacks a magic word from the source string and checks if it is equal to 
 * the specified magic word. The function throws an exception if the magic 
 * word is not equal to the expected magic word or if the magic word could 
 * not be unpacked.
 *
 * \param source data to be unpacked
 * \param w magic word
 * \param offset offset from which to start unpacking
 * \param sourceObj source object
 * \param sourceName source name
 *
 * \return new offset
 */
Ionflux::ObjectBase::DataSize unpackAndCheckMagicWord(
    const std::string& source, Ionflux::ObjectBase::MagicWord w, 
    Ionflux::ObjectBase::DataSize offset = 0, 
    const Ionflux::ObjectBase::IFObject* sourceObj = 0, 
    const std::string& sourceName = "");

/** Unpack and check magic word.
 *
 * Unpacks a magic word from the source stream and checks if it is equal to 
 * the specified magic word. The function throws an exception if the magic 
 * word is not equal to the expected magic word or if the magic word could 
 * not be unpacked.
 *
 * \param source source stream
 * \param w magic word
 * \param offset stream offset from which to start unpacking
 * \param sourceObj source object
 * \param sourceName source name
 *
 * \return new offset
 */
Ionflux::ObjectBase::DataSize unpackAndCheckMagicWord(
    std::istream& source, Ionflux::ObjectBase::MagicWord w, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID, 
    const Ionflux::ObjectBase::IFObject* sourceObj = 0, 
    const std::string& sourceName = "");

/** Unpack and check magic syllables.
 *
 * Unpacks a magic word from the source string and checks if it is equal to 
 * the specified magic syllables. The function throws an exception if the 
 * magic word is not equal to the expected magic word or if the magic word 
 * could not be unpacked.
 *
 * \param source data to be unpacked
 * \param s0 syllable (0)
 * \param s1 syllable (1)
 * \param offset offset from which to start unpacking
 * \param sourceObj source object
 * \param sourceName source name
 *
 * \return new offset
 */
Ionflux::ObjectBase::DataSize unpackAndCheckMagicWord(
    const std::string& source, Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1, 
    Ionflux::ObjectBase::DataSize offset = 0, 
    const Ionflux::ObjectBase::IFObject* sourceObj = 0, 
    const std::string& sourceName = "");

/** Unpack and check magic syllables.
 *
 * Unpacks a magic word from the source stream and checks if it is equal to 
 * the specified magic syllables. The function throws an exception if the 
 * magic word is not equal to the expected magic word or if the magic word 
 * could not be unpacked.
 *
 * \param source source stream
 * \param s0 syllable (0)
 * \param s1 syllable (1)
 * \param offset offset from which to start unpacking
 * \param sourceObj source object
 * \param sourceName source name
 *
 * \return new offset
 */
Ionflux::ObjectBase::DataSize unpackAndCheckMagicWord(
    std::istream& source, Ionflux::ObjectBase::MagicSyllable s0, 
    Ionflux::ObjectBase::MagicSyllable s1, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID, 
    const Ionflux::ObjectBase::IFObject* sourceObj = 0, 
    const std::string& sourceName = "");

/** Pack data (vector).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
template<class ET, class PT> 
void packVec(const typename std::vector<ET>& source, 
    std::string& target, bool append = true)
{
    std::string t0;
    pack(static_cast<DataSize>(source.size()), t0);
    for (typename std::vector<ET>::const_iterator i = source.begin(); 
        i != source.end(); i++)
    {
        pack(static_cast<PT>(*i), t0, true);
    }
	if (append)
		target.append(t0);
	else
		target = t0;
}

/** Pack data (vector).
 *
 * Packs the data into a stream.
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
template<class ET, class PT> 
void packVec(const std::vector<ET>& source, 
    std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
    pack(static_cast<DataSize>(source.size()), target, offset);
    for (typename std::vector<ET>::const_iterator i = source.begin(); 
        i != source.end(); i++)
        pack(static_cast<PT>(*i), target);
}

/** Unpack data (vector).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class ET, class PT> 
Ionflux::ObjectBase::DataSize unpackVec(const std::string& source, 
    std::vector<ET>& target, 
    Ionflux::ObjectBase::DataSize offset = 0)
{
    DataSize n0 = 0;
    DataSize o0 = unpack(source, n0, offset);
    DataSize s0 = sizeof(PT);
	if ((o0 == DATA_SIZE_INVALID)
		|| ((o0 + n0 * s0) > source.size()))
		return DATA_SIZE_INVALID;
    for (DataSize i = 0; i < n0; i++)
    {
        PT v0;
        o0 = unpack(source, v0, o0);
        if (offset == DATA_SIZE_INVALID)
            return DATA_SIZE_INVALID;
        target.push_back(static_cast<ET>(v0));
    }
}

/** Unpack data (vector).
 *
 * Unpacks the data from a stream.
 *
 * \param source source stream.
 * \param target where to store the unpacked data.
 * \param offset offset from which to start unpacking.
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class ET, class PT> 
Ionflux::ObjectBase::DataSize unpackVec(std::istream& source, 
    std::vector<ET>& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
    DataSize n0 = 0;
    unpack(source, n0, offset);
    for (DataSize i = 0; i < n0; i++)
    {
        PT cv;
        unpack(source, cv);
        target.push_back(static_cast<ET>(cv));
    }
	return source.tellg();
}

/** Pack data (map).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 * \param target where to store the packed data
 * \param append whether data should be appended to or replace the target data
 */
template<class KT, class VT, class KPT, class VPT> 
void packMap(const typename std::map<KT, VT>& source, 
    std::string& target, bool append = true)
{
    std::string t0;
    pack(static_cast<DataSize>(source.size()), t0);
    for (typename std::map<KT, VT>::const_iterator i = source.begin(); 
        i != source.end(); i++)
    {
        pack(static_cast<KPT>((*i).first), t0, true);
        pack(static_cast<VPT>((*i).second), t0, true);
    }
	if (append)
		target.append(t0);
	else
		target = t0;
}

/** Pack data (map).
 *
 * Packs the data into a stream.
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
template<class KT, class VT, class KPT, class VPT> 
void packMap(const std::map<KT, VT>& source, 
    std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
	std::string t0;
	packMap<KT, VT, KPT, VPT>(source, t0, false);
	writeToStream(target, t0, offset);
}

/** Unpack data (map).
 *
 * Unpacks the data from a string.
 *
 * \param source data to be unpacked
 * \param target where to store the unpacked data
 * \param offset offset from which to start unpacking
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class KT, class VT, class KPT, class VPT> 
Ionflux::ObjectBase::DataSize unpackMap(const std::string& source, 
    std::map<KT, VT>& target, 
    Ionflux::ObjectBase::DataSize offset = 0)
{
    DataSize n0 = 0;
    DataSize o0 = unpack(source, n0, offset);
    DataSize s0 = sizeof(KPT);
    DataSize s1 = sizeof(VPT);
	if ((o0 == DATA_SIZE_INVALID)
		|| ((o0 + n0 * (s0 + s1)) > source.size()))
		return DATA_SIZE_INVALID;
    for (DataSize i = 0; i < n0; i++)
    {
        KPT k0;
        o0 = unpack(source, k0, o0);
        if (offset == DATA_SIZE_INVALID)
            return DATA_SIZE_INVALID;
        VPT v0;
        o0 = unpack(source, v0, o0);
        if (offset == DATA_SIZE_INVALID)
            return DATA_SIZE_INVALID;
        target[static_cast<KT>(k0)] = static_cast<VT>(v0);
    }
    return o0;
}

/** Unpack data (map).
 *
 * Unpacks the data from a stream.
 *
 * \param source source stream.
 * \param target where to store the unpacked data.
 * \param offset offset from which to start unpacking.
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class KT, class VT, class KPT, class VPT> 
Ionflux::ObjectBase::DataSize unpackMap(std::istream& source, 
    std::map<KT, VT>& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID)
{
    DataSize n0 = 0;
    unpack(source, n0, offset);
    DataSize s0 = sizeof(KPT);
    DataSize s1 = sizeof(VPT);
	std::string t0;
	DataSize s2 = readFromStream(source, t0, n0 * (s0 + s1), 
	    DATA_SIZE_INVALID);
	if (s2 < (n0 * (s0 + s1)))
	{
        std::ostringstream status;
        status << "[unpack] " 
            "Could not unpack map from stream (numElements = " << n0 
            << ", keySize = " << s0 << ", valueSize = " << s1;
        if (offset != DATA_SIZE_INVALID)
            status << ", offset = " << offset;
        status << ").";
        throw IFError(status.str());
	}
	return source.tellg();
}

/** Pack data (vector of objects).
 *
 * Packs the data into a stream.
 *
 * \param source data to be packed
 * \param target target stream
 * \param offset stream offset
 */
template<class ET> 
void packObjVec0(const typename std::vector<ET*>& source, 
    std::ostream& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID, 
    bool addMagicWord = false)
{
    DataSize n0 = source.size();
    pack(n0, target, offset);
    for (typename std::vector<ET*>::const_iterator i = source.begin(); 
        i != source.end(); i++)
    {
        ET* o0 = nullPointerCheck(*i, "packObjVec0", "Element");
        o0->serialize(target, addMagicWord);
    }
}

/** Unpack data (vector of objects).
 *
 * Unpacks the data from a stream.
 *
 * \param source source stream.
 * \param target where to store the unpacked data.
 * \param offset offset from which to start unpacking.
 *
 * \return new offset, or DATA_SIZE_INVALID if the data could not be unpacked
 */
template<class ET> 
Ionflux::ObjectBase::DataSize unpackObjVec0(std::istream& source, 
    typename std::vector<ET*>& target, 
    Ionflux::ObjectBase::DataSize offset = DATA_SIZE_INVALID, 
    bool checkMagicWord = false)
{
    DataSize n0 = 0;
    unpack(source, n0, offset);
    for (DataSize i = 0; i < n0; i++)
    {
        ET* o0 = ET::create();
        o0->deserialize(source, DATA_SIZE_INVALID, checkMagicWord);
        target.push_back(o0);
    }
	return source.tellg();
}

}

}

/** \file serialize.hpp
 * \brief Serialization utilities (header).
 */
#endif
