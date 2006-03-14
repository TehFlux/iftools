#ifndef IONFLUX_TOOLS
#define IONFLUX_TOOLS
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * tools.hpp                    Various tools & helper functions
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <termios.h>
#include <stdio.h>
#include <bzlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "sha1.h"
#ifndef HAVE_WINSOCK
#include <netinet/in.h>
#else
#include <winsock.h>
#endif
#ifndef NO_FORK
#include <sys/stat.h>
#include <paths.h>
#include <fcntl.h>
#endif
#include "MersenneTwister.h"
#include "ionflux/Tokenizer.hpp"

/** Ionflux software projects.
 *
 * Namespace for the Ionflux software projects.
 */
namespace Ionflux
{

/** Ionflux Tools
 *
 * Namespace for the Ionflux tools.
 */
namespace Tools
{

class CharTypeMap;

/** \addtogroup general General tools
 *
 * General tools and utility classes and functions.
 *
 * @{
 */

/// Module name.
const std::string MODULE_NAME = "Ionflux Tools";
/// Module version.
const std::string MODULE_VERSION = "0.2.3";
/// Default size for read buffers.
const int READ_BUFFER_SIZE = 1024;
/// Default size for compression (and decompression) buffers.
const int COMPRESS_BUFFER_SIZE = 1024;
/// Default size for directory name buffers.
const int DIR_BUFFER_SIZE = 1024;
/// Maximum size for directory name buffers.
const int DIR_BUFFER_SIZE_MAX = 65536;
/// Directory separator.
const char DIR_SEPARATOR = '/';

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

/** Calculate SHA-1 hash
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

/** Explode a string.
 *
 * Splits up a string of bytes at 'splitString', creating a vector containing 
 * the separated elements.
 *
 * \param bytes Byte String to be exploded.
 * \param splitString Separator string.
 * \param result Vector to store the result in.
 */
void explode(const std::string& bytes, const std::string& splitString, 
	std::vector<std::string>& result);

/** Explode a string.
 *
 * Explodes a string using whitespace separators. Quoted parts of the string 
 * are treated as a single element. Valid quote characters are ' and ". Quote 
 * characters may be escaped using '\\'.
 *
 * \param bytes Byte String to be exploded.
 * \param result Vector to store the result in.
 */
void explodeQuoted(const std::string& bytes, std::vector<std::string>& result);

/** Check type of a character.
 *
 * Returns \c true if the character 'c' is one of the characters of
 * 'testChars'.
 *
 * \param c Character to be checked.
 * \param testChars String of characters.
 *
 * \return \c true if the character 'c' is one of the characters of
 * 'testChars', \c false otherwise.
 */
bool isOneOf(char c, const std::string& testChars);

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

/** Check whether a string represents an alpha.
 *
 * Returns \c true if the string represents a (latin) alpha, \c false 
 * otherwise.
 *
 * \param bytes String to be checked.
 *
 * \return \c true if the string represents a (latin) alpha, \c false 
 * otherwise.
 */
bool isAlpha(const std::string &bytes);

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
 * consisting of alphanumeric characters or underscores '_' (in 8-bit 
 * ISO-8859-1 encoding).
 *
 * \param bytes String to be checked.
 *
 * \return \c true if the string represents an idenifier, \c false otherwise.
 */
bool isIdentifier(const std::string &bytes);

/** Read a file.
 *
 * Reads a file and returns the complete contents as a byte string.
 *
 * \param fileName File name.
 *
 * \return Contents of the file.
 */
std::string readFile(const std::string& fileName);

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
	char writeMode);

/** Compress data.
 *
 * Compresses data using bzip2.
 *
 * \param inputData The data to be compressed.
 * \param outputBuffer Where to store the compressed data.
 *
 * \return \c true on success, \c false otherwise.
 */
bool bz2Compress(const std::string& inputData, std::string &outputBuffer);

/** Decompress data.
 *
 * Decompresses data using bzip2.
 *
 * \param inputData The data to be decompressed.
 * \param outputBuffer Where to store the decompressed data.
 *
 * \return \c true on success, \c false otherwise.
 */
bool bz2Decompress(const std::string& inputData, std::string &outputBuffer);

/** Pack integer.
 *
 * Packs an integer value into a byte string (in network byte order).
 *
 * \param data The integer to be packed.
 *
 * \return The bytes of the integer, in network byte order.
 */
std::string packInt(int data);

/** Pack double.
 *
 * Packs a double precision floating point value into a byte string (in host 
 * byte order).
 *
 * \param data The double to be packed.
 *
 * \return The bytes of the double, in host byte order.
 */
std::string packDouble(double data);

/** Pack boolean.
 *
 * Packs a boolean value into a byte string (in network byte order).
 *
 * \note Although a boolean may be represented as a single bit, the resulting 
 * string will be 1 byte long.
 *
 * \param data The boolean to be packed.
 *
 * \return A byte equivalent the boolean value true (different from zero) or 
 * false (equal to zero).
 */
std::string packBool(bool data);

/** Unpack integer.
 *
 * Unpacks an integer value from a byte string (in network byte order).
 *
 * \param data The bytes to be unpacked.
 *
 * \return The integer extracted from the data bytes.
 */
int unpackInt(const std::string &data);

/** Unpack double.
 *
 * Unpacks a double value from a byte string.
 *
 * \param data The bytes to be unpacked.
 *
 * \return The double extracted from the data bytes.
 */
double unpackDouble(const std::string &data);

/** Unpack boolean.
 *
 * Unpacks a boolean value from a byte string.
 *
 * \param data The bytes to be unpacked.
 *
 * \return Boolean equivalent to the data byte.
 */
bool unpackBool(const std::string &data);

/** Initialize socket API.
 *
 * Initialize the socket API. This may be necessary on some systems (Win32), 
 * while it does nothing on others (Linux, BSD).
 */
void socketInit();

/** Shutdown socket API.
 *
 * Shutdown the socket API. This may be necessary on some systems (Win32), 
 * while it does nothing on others (Linux, BSD).
 */
void socketShutdown();

/** Daemonize.
 *
 * Detaches the process from the terminal.
 */
void daemonize();

/** Parse hex string.
 *
 * Parse a hex string into a byte string.
 *
 * \param inputData The hex string to be parsed.
 *
 * \return The bytes represented by the hexadecimal string.
 */
std::string parseHex(const std::string &inputData);

/** Get a password.
 *
 * Reads a password from standard input.
 *
 * \param prompt Password prompt.
 * \param password Where to store the password.
 */
void getPassword(const std::string &prompt, std::string &password);

/** Get random bytes.
 *
 * Gets a specified number of random bytes.
 *
 * \note You can specify an MTRand object to be used for random number 
 * generation. If you pass null, a random number source will be generated 
 * automatically (not recommended).
 *
 * \param bytes Buffer in which to store the random bytes.
 * \param n Number of random bytes.
 * \param source Random number source.
 */
void getRandomBytes(std::string &bytes, unsigned int n, MTRand *source);

/** Get random identifier.
 *
 * Gets a random identifier of specified length.
 *
 * \note You can specify an MTRand object to be used for random number 
 * generation. If you pass null, a random number source will be generated 
 * automatically (not recommended).
 *
 * \param bytes Buffer in which to store the random identifier.
 * \param n Length of random identifier.
 * \param source Random number source.
 */
void getRandomIdentifier(std::string &bytes, unsigned int n, MTRand *source);

/** Read directory entries.
 *
 * Reads all entries from a directory and stores them in a vector.
 *
 * \param dirName Name (or path) of the directory.
 * \param target Where to store the directory entries.
 * \param prependDirName Whether to prepend the directory name (or path) to 
 * the entries.
 * \param recursive Whether to read the directory recursively.
 *
 * \return \c true on success, \c false otherwise.
 */
bool readDir(const std::string &dirName, std::vector<std::string> &target, 
	bool prependDirName = false, bool recursive = false);

/** Get current working directory.
 *
 * \return The current working directory.
 */
std::string getCurrentDir();

/** Get file list.
 *
 * Get a list of files from a list of paths. The specified paths may be 
 * searched recursively and an optional regular expression may be specified 
 * as a filter.
 *
 * \param pathList List of files and directories.
 * \param target Where to store the file names.
 * \param recursive Whether to search for files recursively.
 * \param filterExpr Regular expression to match file names with.
 *
 * \return \c true on success, \c false otherwise.
 */
bool getFileList(const std::vector<std::string>& pathList, 
	std::vector<std::string>& target, bool recursive = false, 
	const std::string& filterExpr = "");

/** Get operator precedence.
 *
 * Get a numeric value indicating the order of precedence of the specified 
 * operator. The value thus obtained may be used to determine the precedence 
 * of one operator over another operator.
 *
 * \note \c unary needs to be specified only for operators for which 
 * unary-ness is ambiguous. i.e. which exist as both a unary and a binary 
 * operator.
 *
 * \param op Operator.
 * \param unary Whether the operator should be treated as an unary operator 
 * (applies only if unary-ness of operator is amiguous).
 *
 * \return Non-negative numeric value indicating order of precedence, or -1 
 * if the operator is not recognized.
 */
int getOpPrecedence(const std::string &op, bool unary = false);

/** Escape string.
 *
 * Escapes a string so it may be used (for example) with a function like 
 * explodeQuoted(), or anything else thar requires quotes and whitespace to 
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

/** Convert string to bool.
 *
 * Converts a boolean string (e.g. 'yes', 'no', 'true', 'false') to a value 
 * of type bool if possible.
 *
 * \note If the string cannot be converted to a bool, the function returns 
 * \c false anyway.
 *
 * \param text Boolean text string.
 *
 * \return Boolean value.
 */
bool toBool(const std::string &text);

/** Get UTF-8 character size.
 *
 * Get the size, in bytes, of the UTF-8 character starting at \c byte.
 *
 * \param byte Byte.
 *
 * \return Size of UTF-8 character, or 0 if \c byte is not the first byte of 
 * an UTF-8 character.
 */
unsigned int utf8GetSize(unsigned char byte);

/** Get UTF-8 character string size.
 *
 * Get the size, in characters, of the specified UTF-8 character string.
 *
 * \param bytes UTF-8 character string.
 *
 * \return Size of UTF-8 character string, or 0 if an error occurs.
 */
unsigned int utf8GetSize(const std::string& bytes);

/** Convert UTF-8 character to unsigned int.
 *
 * Converts an UTF-8 character to an <tt>unsigned int</tt> if possible.
 *
 * \param bytes String containing the bytes of an UTF-8 character.
 * \param target Where to store the result.
 *
 * \return \c true on success, \c false if the character cannot be decoded.
 */
bool utf8ToUInt(const std::string& bytes, unsigned int& target);

/** Convert UTF-8 character string to unsigned int vector.
 *
 * Converts an UTF-8 character string to a vector of <tt>unsigned int</tt> 
 * if possible.
 *
 * \param bytes String containing the bytes of an UTF-8 character.
 * \param target Where to store the result.
 *
 * \return \c true on success, \c false if one of the characters cannot be 
 * decoded.
 */
bool utf8ToUInt(const std::string& bytes, std::vector<unsigned int>& target);

/** Convert unsigned int to UTF-8 character.
 *
 * Converts the specified unicode character code to a UTF-8 character, 
 * represented by a byte string.
 *
 * \param uniChar Unicode character code.
 *
 * \return UTF-8 character.
 */
std::string uintToUtf8(unsigned int uniChar);

/** Convert unsigned int vector to UTF-8 character string.
 *
 * Converts the specified unicode character codes to a UTF-8 character string.
 *
 * \param uniChars Vector of unicode character codes.
 * \param target Where to store the UTF-8 character string.
 */
void uintToUtf8(const std::vector<unsigned int>& uniChars, 
	std::string& target);

/** Trim UTF-8 string.
 *
 * Remove whitespace characters from the beginning and end of the specified 
 * UTF-8 string.
 *
 * \sa trim
 *
 * \param bytes UTF-8 string.
 * \param leftTrim Remove whitespace from beginning of string.
 * \param rightTrim Remove whitespace from end of string.
 *
 * \return String with whitespace removed from beginning and end.
 */
std::string utf8Trim(const std::string& bytes, bool leftTrim = true, 
	bool rightTrim = true);

/** Check type of Unicode character.
 *
 * Returns \c true if the character 'c' is one of the characters of
 * 'testChars'.
 *
 * \param c Unicode Character to be checked.
 * \param testChars UTF-8 string of characters.
 *
 * \return \c true if the character 'c' is one of the characters of
 * 'testChars', \c false otherwise.
 */
bool utf8IsOneOf(unsigned int c, const std::string& testChars);

/** Check type of Unicode character.
 *
 * Returns \c true if the character 'c' is one of the characters of
 * 'testChars'.
 *
 * \param c Unicode Character to be checked.
 * \param testChars Unicode characters.
 *
 * \return \c true if the character 'c' is one of the characters of
 * 'testChars', \c false otherwise.
 */
bool utf8IsOneOf(unsigned int c, const std::vector<unsigned int>& testChars);

/** Escape UTF-8 string.
 *
 * Escape an UTF-8 string.
 *
 * \param source UTF-8 string of characters.
 *
 * \return An escaped string of ASCII characters.
 */
std::string utf8Escape(const std::string& source);

/** Unescape ASCII string.
 *
 * Unescape a string of ASCII characters.
 *
 * \param source ASCII string of characters.
 *
 * \return An unescaped string of UTF-8 characters.
 */
std::string utf8Unescape(const std::string& source);

/** Quote string.
 *
 * Add quotes to a string.
 *
 * \param source String to be quoted.
 * \param quoteChar Quote character to be used.
 *
 * \return Quoted string.
 */
std::string quote(const std::string& source, 
	const unsigned char quoteChar = '\'');

/** Unquote string.
 *
 * Remove quotes from a string.
 *
 * \param source String to be unquoted.
 * \param addQuoteChars Additional quote characters.
 *
 * \return Unquoted string.
 */
std::string unquote(const std::string& source, 
	const std::string& addQuoteChars = "");

/** Trim byte string.
 *
 * Remove whitespace characters from the beginning and end of the specified 
 * string.
 *
 * \sa utf8Trim
 *
 * \param bytes Byte string.
 * \param leftTrim Remove whitespace from beginning of string.
 * \param rightTrim Remove whitespace from end of string.
 *
 * \return String with whitespace removed from beginning and end.
 */
std::string trim(const std::string& bytes, bool leftTrim = true, 
	bool rightTrim = true);

/** Get character type lookup map.
 *
 * Get a static character type lookup map.
 *
 * \return Character type lookup map.
 */
const CharTypeMap& getCharTypes();

/** URL-encode bytes.
 *
 * Encode bytes according to RFC 1738.
 *
 * \param bytes Bytes to be encoded.
 *
 * \return URL-encoded bytes.
 */
std::string urlEncode(const std::string& bytes);

/** URL-decode bytes.
 *
 * Decode bytes according to RFC 1738.
 *
 * \param bytes Bytes to be decoded.
 *
 * \return URL-decoded bytes.
 */
std::string urlDecode(const std::string& bytes);

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

/** Validate path.
 *
 * Validate a path. Missing directories will be created automatically.
 *
 * \param path Path.
 * \param mask Mask for newly created directories.
 *
 * \return \c true on success, \c false otherwise.
 */
bool validatePath(const std::string& path, int mask = 0755);

/** Escape XML markup.
 *
 * Escape a string so it may be used in an XML document without interfering 
 * with markup.
 *
 * \param bytes Bytes to be escaped.
 *
 * \return escaped String;
 */
std::string xmlEscape(const std::string& bytes);

/** Get randomizer.
 *
 * Get a (static) MT randomizer.
 *
 * \return MT randomizer.
 */
MTRand& getRandomizer();

/// @}

}

}

/** \file tools.hpp
 * \brief Various tools & helper functions header.
 */
#endif
