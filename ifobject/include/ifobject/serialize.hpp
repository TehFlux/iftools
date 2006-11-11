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

namespace Ionflux
{

namespace ObjectBase
{

/** Pack data into string (bool).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 *
 * \return packed data
 */
std::string pack(bool source);

/** Pack data into string (int).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 *
 * \return packed data
 */
std::string pack(int source);

/** Pack data into string (unsigned int).
 *
 * Packs the data into a string.
 *
 * \param source data to be packed
 *
 * \return packed data
 */
std::string pack(unsigned int source);

/** Pack data into string (string).
 *
 * Packs the data into a string. The result will contain the length of the 
 * string in the first 4 bytes.
 *
 * \param source data to be packed
 *
 * \return packed data
 */
std::string pack(const std::string& source);

/** Unpack data from string (bool).
 *
 * Unpacks data from a string.
 *
 * \param source buffer which contains the data to be unpacked
 * \param offset offset of the data to be unpacked
 * \param target where to store the result
 *
 * \return offset of remaining data, or -1 if an error occured
 */
int unpackBool(const std::string source, bool& target, int offset = 0);

/** Unpack data from string (int).
 *
 * Unpacks data from a string.
 *
 * \param source buffer which contains the data to be unpacked
 * \param offset offset of the data to be unpacked
 * \param target where to store the result
 *
 * \return offset of remaining data, or -1 if an error occured
 */
int unpackInt(const std::string source, int& target, int offset = 0);

/** Unpack data from string (unsigned int).
 *
 * Unpacks data from a string.
 *
 * \param source buffer which contains the data to be unpacked
 * \param offset offset of the data to be unpacked
 * \param target where to store the result
 *
 * \return offset of remaining data, or -1 if an error occured
 */
int unpackUInt(const std::string source, unsigned int& target, int offset = 0);

/** Unpack data from string (string).
 *
 * Unpacks data from a string.
 *
 * \param source buffer which contains the data to be unpacked
 * \param offset offset of the data to be unpacked
 * \param target where to store the result
 *
 * \return offset of remaining data, or -1 if an error occured
 */
int unpackString(const std::string source, std::string& target, int offset = 0);

}

}

/** \file serialize.hpp
 * \brief Serialization utilities (header).
 */
#endif
