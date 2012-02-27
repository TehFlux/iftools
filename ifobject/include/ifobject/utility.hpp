#ifndef IONFLUX_OBJECT_UTILITY
#define IONFLUX_OBJECT_UTILITY
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utility.hpp                 Utility functions (header).
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
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace ObjectBase
{

class IFObject;

/// Default size for read buffers.
const unsigned int READ_BUFFER_SIZE = 4096;

/** Read file.
 *
 * Read data from a file.
 *
 * \param fileName File name.
 * \param fileName Where to store the data.
 * \param logTarget Target for logging messages.
 *
 * \return \c true if the file can be read from, \c false otherwise.
 */
bool readFile(const std::string& fileName, std::string& target, 
    Ionflux::ObjectBase::IFObject* logTarget = 0);

/** Explode a string.
 *
 * Splits up a string of bytes at 'splitString', creating a vector containing 
 * the separated elements.
 *
 * \param bytes String to be exploded.
 * \param splitString Separator string.
 * \param result Vector to store the result in.
 */
void explode(const std::string& bytes, const std::string& splitString, 
	std::vector<std::string>& result);

/** Check type of a character.
 *
 * Returns \c true if the character 'c' is one of the characters of
 * 'testChars'.
 *
 * \param c Character to be checked.
 * \param testChars String of characters.
 * \param invert Invert the result
 *
 * \return \c true if the character 'c' is one of the characters of
 * 'testChars', \c false otherwise.
 */
bool isOneOf(char c, const std::string& testChars, bool invert = false);

/** Check whether a string represents a number.
 *
 * Returns \c true if the string represents a (decimal) number, \c false 
 * otherwise.
 *
 * \param bytes String to be checked.
 *
 * \return \c true if the string represents a (decimal) number, \c false 
 * otherwise.
 */
bool isNumber(const std::string &bytes);

/** Check whether a string represents an integer.
 *
 * Returns \c true if the string represents a (decimal) integer value 
 * (positive or negative), \c false otherwise.
 *
 * \param bytes String to be checked.
 *
 * \return \c true if the string represents a (decimal) integer, \c false 
 * otherwise.
 */
bool isInteger(const std::string &bytes);

/** Check whether a string represents a float.
 *
 * Returns \c true if the string represents a (decimal) floating point value 
 * (positive or negative), \c false otherwise.
 *
 * \param bytes String to be checked.
 *
 * \return \c true if the string represents a (decimal) floating point value, 
 * \c false otherwise.
 */
bool isFloat(const std::string &bytes);

/** Check whether a string represents an identifier.
 *
 * Returns \c true if the string represents an idenifier, \c false otherwise.
 *
 * \note For purposes of this function, an identifier is a byte string 
 * consisting of alphanumeric characters or underscores '_' (in 8-bit ASCII 
 * encoding).
 *
 * \param bytes String to be checked.
 *
 * \return \c true if the string represents an idenifier, \c false otherwise.
 */
bool isIdentifier(const std::string &bytes);

/** Convert string to upper case.
 *
 * Convert a text string to upper case if possible.
 *
 * \param text Input text string.
 * \param numChars Maximum number of characters to convert.
 * \param offset Index where to start case conversion.
 *
 * \return Upper case string.
 */
std::string toUpper(const std::string &text, unsigned int numChars = 0, 
	unsigned int offset = 0);

/** Convert string to lower case.
 *
 * Convert a text string to lower case if possible.
 *
 * \param text Input text string.
 * \param numChars Maximum number of characters to convert.
 * \param offset Index where to start case conversion.
 *
 * \return Lower case string.
 */
std::string toLower(const std::string &text, unsigned int numChars = 0, 
	unsigned int offset = 0);

/** Trim byte string.
 *
 * Remove whitespace characters from the beginning and end of the specified 
 * string.
 *
 * \param bytes Byte string.
 * \param leftTrim Remove whitespace from beginning of string.
 * \param rightTrim Remove whitespace from end of string.
 *
 * \return String with whitespace removed from beginning and end.
 */
std::string trim(const std::string& bytes, bool leftTrim = true, 
	bool rightTrim = true);

/** Prefix check.
 *
 * Check whether the string of bytes has the specified prefix.
 *
 * \param bytes Data to be checked.
 * \param prefix Prefix.
 * \param ignoreCase Ignore case.
 *
 * \return \c true if the data has the prefix, \c false otherwise.
 */
bool hasPrefix(const std::string& bytes, const std::string& prefix, 
    bool ignoreCase = true);

/** Prefix check.
 *
 * Check whether the string of bytes has any of the specified prefixes.
 *
 * \param bytes Data to be checked.
 * \param prefixes Vector of prefixes.
 * \param ignoreCase Ignore case.
 *
 * \return \c true if the data has any of the prefixes, \c false otherwise.
 */
bool hasPrefix(const std::string& bytes, const std::vector<std::string>& 
    prefixes, bool ignoreCase = true);

/** Get time ticks.
 *
 * Get a time tick value.
 *
 * \return Time tick value.
 */
Ionflux::ObjectBase::UInt64 getTimeTicks();

}

}

/** \file utility.hpp
 * \brief Utility functions (header).
 */
#endif
