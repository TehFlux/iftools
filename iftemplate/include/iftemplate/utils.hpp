#ifndef IONFLUX_TEMPLATE_UTILS
#define IONFLUX_TEMPLATE_UTILS
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.hpp                     Utility functions (header).
 * =========================================================================
 *
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
#include <string>
#include "ifobject/types.hpp"
#include "ifobject/IFObject.hpp"
#include "iftemplate/IFTemplateError.hpp"
#include "iftemplate/types.hpp"
#include "iftemplate/constants.hpp"

namespace Ionflux
{

namespace Template
{

class CharTypeMap;

/// Check whether token is valid.
bool isValid(const Ionflux::Template::Token& token);

/** Unpack integer.
 *
 * This is a wrapper around Ionflux::ObjectBase::unpack() used for 
 * compatibility with old code.
 */
int unpackInt(const std::string& bytes);

/** Unpack bool.
 *
 * This is a wrapper around Ionflux::ObjectBase::unpack() used for 
 * compatibility with old code.
 */
bool unpackBool(const std::string& bytes);

/// Get string representation for node reference type ID.
std::string nodeRefTypeToString(Ionflux::Template::NodeRefTypeID t);

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

/// Token type check.
bool hasType(const Ionflux::Template::Token& t, 
    Ionflux::Template::TokenTypeID typeID);

/// Token validity check.
bool isValid(const Ionflux::Template::Token& t);

/// Token non-empty check.
bool isNonEmpty(const Ionflux::Template::Token& t);

/// Token character check.
bool hasCharValue(const Ionflux::Template::Token& t, char c);

/** Create token type.
 *
 * Create a token type. If \c userType is set to \c true, the token type ID 
 * will be offset by TT_ID_USERTYPE automatically.
 *
 * \param typeID token type ID
 * \param validChars valid characters
 * \param invert invert matching behavior
 * \param maxChars maximum number of characters
 * \param userType create a user-defined type
 *
 * \return New token type.
 */
Ionflux::Template::TokenType createTokenType(
    Ionflux::Template::TokenTypeID typeID, const std::string& validChars, 
    bool invert, int maxChars, bool userType = true);

/** Get character type lookup map.
 *
 * Get a static character type lookup map.
 *
 * \return Character type lookup map.
 */
const Ionflux::Template::CharTypeMap& getCharTypes();

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
bool readDir(const std::string& dirName, 
    Ionflux::ObjectBase::StringVector& target, 
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
 *
 * \return \c true on success, \c false otherwise.
 */
bool getFileList(const Ionflux::ObjectBase::StringVector& pathList, 
	Ionflux::ObjectBase::StringVector& target, bool recursive = false);

/// Null pointer check.
template<class T>
T* nullPointerCheck(T* p, Ionflux::ObjectBase::IFObject* sourceObj, 
    const std::string& source = "", const std::string& objName = "Pointer")
{
    if (p == 0)
    {
        std::ostringstream status;
        status << objName << " is null.";
        throw IFTemplateError(sourceObj->getErrorString(status.str(), source));
    }
    return p;
}

/** Explode a string.
 *
 * Explodes a string using whitespace separators. Quoted parts of the string 
 * are treated as a single element. Valid quote characters are ' and ". Quote 
 * characters may be escaped using '\\'.
 *
 * \param bytes Byte String to be exploded.
 * \param result Vector to store the result in.
 */
void explodeQuoted(const std::string& bytes, 
    Ionflux::ObjectBase::StringVector& result);

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
