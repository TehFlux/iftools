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
#include <iostream>
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
        status << objName << " has unexpected type "
            "(expected type: " << expectedType << ").";
        throw IFError(status.str());
    }
    return result;
}

/// Range check.
template<class T0>
T0 rangeCheck(T0& v, const T0& lower, const T0& upper, 
    const std::string& source = "", 
    const std::string& objName = "object")
{
    if ((v < lower) 
        || (v > upper))
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << objName << " out of bounds (v = " << v 
            << ", range = [" << upper << ", " << lower << "].";
        throw IFError(status.str());
    }
    return v;
}

/** Read file.
 *
 * Read data from a file.
 *
 * \param fileName File name.
 * \param target Where to store the data.
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
 * \param showPos Show the current byte position at the end of each line.
 *
 * \return Nicely formatted hexadecimal output.
 */
std::string makeNiceHex(const std::string& hex, const std::string& readable, 
	int bytesPerLine = 20, int groupBytes = 10, bool showPos = true);

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

/** Add values to vector.
 *
 * Add values to a vector.
 * 
 * \param target target vector
 * \param numValues number of values to add
 * \param v0 value (0)
 * \param v1 value (1)
 * \param v2 value (2)
 * \param v3 value (3)
 * \param v4 value (4)
 * \param v5 value (5)
 * \param v6 value (6)
 * \param v7 value (7)
 * \param v8 value (8)
 * \param v9 value (9)
 * \param v10 value (10)
 * \param v11 value (11)
 * \param v12 value (12)
 * \param v13 value (13)
 * \param v14 value (14)
 * \param v15 value (15)
 */
void addValues(Ionflux::ObjectBase::IntVector& target, 
    unsigned int numValues, 
    int v0 = 0, int v1 = 0, int v2 = 0, int v3 = 0, 
    int v4 = 0, int v5 = 0, int v6 = 0, int v7 = 0, 
    int v8 = 0, int v9 = 0, int v10 = 0, int v11 = 0, 
    int v12 = 0, int v13 = 0, int v14 = 0, int v15 = 0);

/** Add values to vector.
 *
 * Add values to a vector.
 * 
 * \param target target vector
 * \param numValues number of values to add
 * \param v0 value (0)
 * \param v1 value (1)
 * \param v2 value (2)
 * \param v3 value (3)
 * \param v4 value (4)
 * \param v5 value (5)
 * \param v6 value (6)
 * \param v7 value (7)
 * \param v8 value (8)
 * \param v9 value (9)
 * \param v10 value (10)
 * \param v11 value (11)
 * \param v12 value (12)
 * \param v13 value (13)
 * \param v14 value (14)
 * \param v15 value (15)
 */
void addValues(Ionflux::ObjectBase::UIntVector& target, 
    unsigned int numValues, 
    unsigned int v0 = 0, unsigned int v1 = 0, 
    unsigned int v2 = 0, unsigned int v3 = 0, 
    unsigned int v4 = 0, unsigned int v5 = 0, 
    unsigned int v6 = 0, unsigned int v7 = 0, 
    unsigned int v8 = 0, unsigned int v9 = 0, 
    unsigned int v10 = 0, unsigned int v11 = 0, 
    unsigned int v12 = 0, unsigned int v13 = 0, 
    unsigned int v14 = 0, unsigned int v15 = 0);

/** Add values to vector.
 *
 * Add values to a vector.
 * 
 * \param target target vector
 * \param numValues number of values to add
 * \param v0 value (0)
 * \param v1 value (1)
 * \param v2 value (2)
 * \param v3 value (3)
 * \param v4 value (4)
 * \param v5 value (5)
 * \param v6 value (6)
 * \param v7 value (7)
 * \param v8 value (8)
 * \param v9 value (9)
 * \param v10 value (10)
 * \param v11 value (11)
 * \param v12 value (12)
 * \param v13 value (13)
 * \param v14 value (14)
 * \param v15 value (15)
 */
void addValues(Ionflux::ObjectBase::DoubleVector& target, 
    unsigned int numValues, 
    double v0 = 0., double v1 = 0., double v2 = 0., double v3 = 0., 
    double v4 = 0., double v5 = 0., double v6 = 0., double v7 = 0., 
    double v8 = 0., double v9 = 0., double v10 = 0., double v11 = 0., 
    double v12 = 0., double v13 = 0., double v14 = 0., double v15 = 0.);

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

/** Append directory separator.
 *
 * Append directory separator to \c path, if not already present.
 *
 * \param path Path to which a directory separator should be appended.
 * \param separator Directory separator to be used.
 *
 * \return Path with directory separator appended.
 */
std::string appendDirSeparator(const std::string& path, 
	unsigned char separator = DIR_SEPARATOR);

/** Prepend directory separator.
 *
 * Prepend directory separator to \c path, if not already present.
 *
 * \param path Path to which a directory separator should be prepended.
 * \param separator Directory separator to be used.
 *
 * \return Path with directory separator prepended.
 */
std::string prependDirSeparator(const std::string& path, 
	unsigned char separator = DIR_SEPARATOR);

/** Create line buffer.
 * 
 * Create a line buffer for the specified vector of strings.
 * 
 * \param data data vector
 * 
 * \sa cleanupLineBuffer()
 */
Ionflux::ObjectBase::LineBuffer createLineBuffer(
    const Ionflux::ObjectBase::StringVector& data);

/** Create line buffer.
 * 
 * Create a line buffer for the specified string. The string may contain 
 * several lines, separated by newline characters. The newline characters 
 * will not be included in the line buffer.
 * 
 * \param data data vector
 * 
 * \sa cleanupLineBuffer()
 *
 * \return line buffer
 */
Ionflux::ObjectBase::LineBuffer createLineBuffer(const std::string& data);

/** Cleanup line buffer.
 * 
 * Clean up a line buffer and free any resources associated with the 
 * line buffer.
 * 
 * \param lineBuffer line buffer
 * 
 * \sa createLineBuffer()
 */
void cleanupLineBuffer(Ionflux::ObjectBase::LineBuffer& lineBuffer);

/** Get string vector.
 * 
 * Initialize a string vector from a line buffer.
 * 
 * \param lineBuffer line buffer
 * \param target where to store the data
 * 
 * \sa createLineBuffer()
 */
void getStringVector(const Ionflux::ObjectBase::LineBuffer& lineBuffer, 
    Ionflux::ObjectBase::StringVector& target);

/** Create constant data line buffer.
 * 
 * Create a constant data line buffer from a line buffer. The constant data 
 * line buffer will reference the data from the specified line buffer during 
 * its life-time.
 * 
 * \param lineBuffer line buffer
 * 
 * \sa createLineBuffer()
 *
 * \return constant data line buffer
 */
Ionflux::ObjectBase::LineBufferConst createLineBufferConst(
    const Ionflux::ObjectBase::LineBuffer& lineBuffer);

/// Clean up line buffer.
void cleanupLineBuffer(Ionflux::ObjectBase::LineBufferConst& lineBuffer);

/** Get string representation of value (vector).
 * 
 * Get a string representation of the value of a vector.
 * 
 * \param v vector
 * \param sep separator string
 *
 * \return string representation
 */
template<class T>
std::string getValueStringVec(const T& v, const std::string& sep = ", ")
{
    std::ostringstream status;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (i > 0)
            status << sep;
        status << v[i];
    }
    return status.str();
}

/** Get error string.
 *
 * Get a string that can be used for reporting an error message.
 *
 * \param message error message
 * \param source source of the error
 * \param sourceObj source object
 *
 * \return error message string
 */
std::string getErrorString(const std::string& message, 
    const std::string& source = "", 
    const Ionflux::ObjectBase::IFObject* sourceObj = 0);

/** Read from stream.
 * 
 * Read data from the specified stream and store it in the target string. If 
 * \c numBytes is \c DATA_SIZE_INVALID, the maximum number of bytes possible 
 * will be read from the stream. If \c offset is not DATA_SIZE_INVALID, 
 * data will be read starting from the specified offset.
 *
 * \param s input stream
 * \param target where to store the data
 * \param numBytes number of bytes to read
 * \param offset offset
 *
 * \return number of bytes read
 */
Ionflux::ObjectBase::DataSize readFromStream(std::istream& s, 
    std::string& target, Ionflux::ObjectBase::DataSize numBytes = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, 
    Ionflux::ObjectBase::DataSize offset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID);

/** Write to stream.
 * 
 * Write data to the specified stream. If \c offset is not DATA_SIZE_INVALID, 
 * data will be written starting from the specified offset.
 *
 * \param s output stream
 * \param source source data
 * \param offset offset
 *
 * \return number of bytes written
 */
Ionflux::ObjectBase::DataSize writeToStream(std::ostream& s, 
    const std::string& source, Ionflux::ObjectBase::DataSize offset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID);

/// Get string representation for a stream type ID.
std::string getStreamTypeValueString(Ionflux::ObjectBase::StreamTypeID t);

/// Checked map lookup.
template<class KT, class VT>
VT checkedLookup(typename std::map<KT, VT>& m, 
    const KT& key, const std::string& source = "", 
    const std::string& objName = "object")
{
    typename std::map<KT, VT>::iterator i = m.find(key);
    if (i == m.end())
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << objName << " not found (key = " << key << ").";
        throw IFError(status.str());
    }
    return (*i).second;
}

/// Checked map lookup.
template<class KT, class VT>
VT checkedLookup(const typename std::map<KT, VT>& m, 
    const KT& key, const std::string& source = "", 
    const std::string& objName = "object")
{
    typename std::map<KT, VT>::const_iterator i = m.find(key);
    if (i == m.end())
    {
        std::ostringstream status;
        if (source.size() > 0)
            status << "[" << source << "] ";
        status << objName << " not found (key = " << key << ").";
        throw IFError(status.str());
    }
    return (*i).second;
}

/** Get string representation for vector.
 *
 * Get a string representation for a vector. The string is constructed by 
 * joining the string representation for each vector element with the 
 * specified separator string.
 *
 * \param v vector
 * \param sep separator string
 *
 * \return string representation of vector
 */
template<class ET>
std::string getVecString(const typename std::vector<ET>& v, 
    const std::string& sep = 
    Ionflux::ObjectBase::DEFAULT_COORD_SEPARATOR)
{
    std::ostringstream result;
    bool e0 = true;
    for (typename std::vector<ET>::const_iterator i = v.begin(); 
        i != v.end(); i++)
    {
        if (!e0)
            result << sep;
        else
            e0 = false;
        result << *i;
    }
    return result.str();
}

/// Get value string (boolean).
std::string getBooleanValueString(bool v);

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
