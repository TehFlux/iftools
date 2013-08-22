#ifndef IONFLUX_OBJECT_UTILS
#define IONFLUX_OBJECT_UTILS
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2013 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.hpp                 Utility functions (header).
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
#include <sstream>
#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "ifobject/IFError.hpp"

namespace Ionflux
{

namespace ObjectBase
{

class IFObject;

/// Checked allocation.
template<class T>
T* create(const std::string& source = "", 
    const std::string& objName = "object")
{
    T* nt = new T();
    if (nt == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << "Could not allocate " << objName << ".";
        throw IFError(status.str());
    }
    return nt;
}

/// Checked allocation.
template<class T, class A>
T* create1(A arg0, const std::string& source = "", 
    const std::string& objName = "object")
{
    T* nt = new T(arg0);
    if (nt == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << "Could not allocate " << objName << ".";
        throw IFError(status.str());
    }
    return nt;
}

/// Checked allocation.
template<class T, class A0, class A1>
T* create2(A0 arg0, A1 arg1, const std::string& source = "", 
    const std::string& objName = "object")
{
    T* nt = new T(arg0, arg1);
    if (nt == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << "Could not allocate " << objName << ".";
        throw IFError(status.str());
    }
    return nt;
}

/// Checked allocation.
template<class T, class A0, class A1, class A2>
T* create3(A0 arg0, A1 arg1, A2 arg2, const std::string& source = "", 
    const std::string& objName = "object")
{
    T* nt = new T(arg0, arg1, arg2);
    if (nt == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << "Could not allocate " << objName << ".";
        throw IFError(status.str());
    }
    return nt;
}

/// Checked allocation.
template<class T, class A0, class A1, class A2, class A3>
T* create4(A0 arg0, A1 arg1, A2 arg2, A3 arg3, 
    const std::string& source = "", 
    const std::string& objName = "object")
{
    T* nt = new T(arg0, arg1, arg2, arg3);
    if (nt == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << "Could not allocate " << objName << ".";
        throw IFError(status.str());
    }
    return nt;
}

/// Checked allocation.
template<class T, class A0, class A1, class A2, class A3, class A4>
T* create5(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, 
    const std::string& source = "", 
    const std::string& objName = "object")
{
    T* nt = new T(arg0, arg1, arg2, arg3, arg4);
    if (nt == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << "Could not allocate " << objName << ".";
        throw IFError(status.str());
    }
    return nt;
}

/// Null pointer check.
template<class T>
T* nullPointerCheck(T* p, const std::string& source = "", 
    const std::string& objName = "Pointer")
{
    if (p == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << objName << " is null.";
        throw IFError(status.str());
    }
    return p;
}

/// Checked dynamic cast.
template<class T0, class T1>
T0* checkedDynamicCast(T1* p, const std::string& source = "", 
    const std::string& objName = "pointer", 
    const std::string& expectedType = "<unknown>")
{
    T0* result = dynamic_cast<T0*>(p);
    if (result == 0)
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << " " << objName << " has unexpected type "
            "(expected type: " << expectedType << ").";
        throw IFError(status.str());
    }
    return result;
}

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

/** Write to file.
 *
 * Writes the specified byte string to a file. If 'writeMode' is 'w' (or 0), 
 * the file is overwritten, if 'writeMode' is 'a', the byte string is appended 
 * to the file.
 *
 * \param fileName File name.
 * \param data Data to be written.
 * \param writeMode File write mode.
 *
 * \return \c true on success, \c false otherwise.
 */
bool writeFile(const std::string& fileName, const std::string& data, 
	char writeMode = 'w');

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

/// Convert string to bool.
bool toBool(const std::string& bytes);

/** Convert string to float.
 *
 * This is a float conversion function that does not depend on the locale 
 * (unlike strtod).
 *
 * \param bytes bytes
 *
 * \note This is rather a hack and may lack precision. Use strtod if at all 
 * possible.
 *
 * \return result of the conversion
 */
double toFloat(const std::string& bytes);

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

/** Make readable hexadecimal code.
 *
 * Convert a string that not necessarily contains readable characters to
 * readable hexadecimal code.
 *
 * \param inputData A string of bytes to be converted.
 *
 * \return Hexadecimal string.
 */
std::string makeHex(const std::string& inputData);

/** Replace unreadable characters.
 *
 * Convert a string that not necessarily contains readable characters to
 * readable characters, replacing characters considered unreadable with 
 * 'replacement'.
 *
 * \param inputData A string of bytes to be converted.
 * \param replacement A string with which to replace unreadable characters.
 *
 * \return String composed of readable characters.
 */
std::string makeReadable(const std::string& inputData, 
	const std::string& replacement);

/** Make nice hexadecimal output.
 *
 * This function generates a nice human readable hexadecimal output from a 
 * string of hexadecimal bytes and a readable representation of that string, 
 * similar to the display of a hex editor.
 *
 * \param hex String of bytes in hexadecimal representation.
 * \param readable Readable representation of the string.
 * \param bytesPerLine How many bytes to display per line.
 * \param groupBytes How many bytes to display in each group.
 *
 * \return Nicely formatted hexadecimal output.
 */
std::string makeNiceHex(const std::string& hex, const std::string& readable, 
	int bytesPerLine, int groupBytes);

/** Parse hex string.
 *
 * Parse a hex string into a byte string.
 *
 * \param inputData The hex string to be parsed.
 *
 * \return The bytes represented by the hexadecimal string.
 */
std::string parseHex(const std::string& inputData);

/** Calculate SHA-1 hash.
 *
 * Calculate the SHA-1 hash for a string.
 *
 * \param secret The string containing the secret which should be hashed.
 * \param hexOut If set to \c true, the return value will be a hexadecimal 
 * string.
 *
 * \return SHA-1 hash of the input secret.
 */
std::string sha1(const std::string& secret, bool hexOut = false);

/** Calculate HMAC-SHA hash.
 *
 * Calculate the HMAC-SHA hash for a key and a message.
 *
 * \param key The string containing the key.
 * \param message The string containing the message.
 * \param hexOut If set to \c true, the return value will be a hexadecimal 
 * string.
 *
 * \return HMAC-SHA hash of the input key and message.
 */
std::string hmac(const std::string& key, const std::string& message, 
    bool hexOut = false);

/** Set vector from value list.
 *
 * Initialize the elements of a vector from a list of values, given 
 * as a string.
 * 
 * \param data list data
 * \param target target vector
 * \param separator separator
 */
void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::IntVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);

/** Set vector from value list.
 *
 * Initialize the elements of a vector from a list of values, given 
 * as a string.
 * 
 * \param data list data
 * \param target target vector
 * \param separator separator
 */
void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::UIntVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);

/** Set vector from value list.
 *
 * Initialize the elements of a vector from a list of values, given 
 * as a string.
 * 
 * \param data list data
 * \param target target vector
 * \param separator separator
 */
void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::DoubleVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);

/** Get indentation string
 *
 * Get a string of characters that can be used for indentation.
 *
 * \param level indentation level
 * \param indentWidth indentation width (per level)
 * \param indentChar indentation character
 *
 * \return indentation string
 */
std::string getIndent(unsigned int level = 0, 
    unsigned int indentWidth = DEFAULT_INDENT_WIDTH, 
    char indentChar = ' ');

/** Escape string.
 *
 * Escapes a string so it may be used (for example) with a function like 
 * explodeQuoted(), or anything else that requires quotes and whitespace to 
 * be escaped.
 *
 * \param source String to be escaped.
 * \param escapeWhat Characters which should be escaped.
 *
 * \return Escaped string.
 *
 * \sa explodeQuoted()
 */
std::string escape(const std::string &source, 
	const std::string& escapeWhat = " '\"");

/** Get string representation for memory management event.
 *
 * Get a string representation for a memory management event.
 *
 * \param typeID type ID
 *
 * \return string representation
 */
std::string mmTypeIDGetString(Ionflux::ObjectBase::MMEventTypeID typeID);

/// Get timestamp.
std::string getTimestamp();

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
