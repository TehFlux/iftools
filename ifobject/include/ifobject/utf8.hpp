#ifndef IONFLUX_OBJECT_UTF8
#define IONFLUX_OBJECT_UTF8
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utf8.hpp                 UTF-8 encoding/decoding.
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
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/** Convert unicode character to UTF-8.
 *
 * Convert an unicode character to an UTF-8 string.
 *
 * \param uniChar unicode character
 * \param logTarget object to be used for logging
 *
 * \return UTF-8 string
 */
std::string uniCharToUTF8(IFUniChar uniChar);

/** Decode unicode character.
 *
 * Decode a single unicode character from a UTF-8 string.
 *
 * \param bytes UTF-8 string
 * \param target Where to store the unicode character.
 * \param logTarget object to be used for logging
 *
 * \return \c true if decoding is successful, \c false otherwise
 */
bool utf8ToUniChar(const std::string& bytes, IFUniChar& target);

/** Convert unicode character sequence to UTF-8.
 *
 * Convert a sequence of unicode characters to an UTF-8 string.
 *
 * \param uniChars sequence of unicode characters
 * \param target Where to store the UTF-8 string.
 * \param logTarget object to be used for logging
 */
void uniCharToUTF8(const std::vector<IFUniChar>& uniChars, 
	std::string& target);

/** Get size of UTF-8 character.
 *
 * Get the size of an unicode character which is encoded with UTF-8. This is 
 * done by examining the first byte.
 *
 * \param byte first byte of UTF-8 encoded character
 * \param logTarget object to be used for logging
 *
 * \return size of utf-8 encoded character in bytes
 */
unsigned int utf8GetSize(unsigned char byte);

/** Decode unicode character sequence.
 *
 * Decode a sequence of unicode characters from a UTF-8 string.
 *
 * \param bytes UTF-8 string
 * \param target Where to store the unicode character sequence.
 * \param logTarget object to be used for logging
 *
 * \return \c true if decoding is successful, \c false otherwise
 */
bool utf8ToUniChar(const std::string& bytes, 
	std::vector<IFUniChar>& target);

/** Get size of UTF-8 string.
 *
 * Get the size in characters of the specified UTF-8 encoded string.
 *
 * \param bytes UTF-8 encoded string
 * \param logTarget object to be used for logging
 *
 * \return size of string in characters, or 0 if an error occured
 */
unsigned int utf8GetSize(const std::string& bytes);

}

}

/** \file utf8.hpp
 * \brief UTF-8 encoding/decoding (header).
 */
#endif
