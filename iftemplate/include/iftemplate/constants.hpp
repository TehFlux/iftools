#ifndef IONFLUX_TEMPLATE_CONSTANTS
#define IONFLUX_TEMPLATE_CONSTANTS
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * constants.hpp                     Constant definitions.
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
#include <climits>
#include "iftemplate/types.hpp"

namespace Ionflux
{

namespace Template
{

/// Token type ID: invalid.
const TokenTypeID TT_ID_INVALID = -1;
/// Token type ID: none.
const TokenTypeID TT_ID_NONE = 0;
/// Token type ID: anything.
const TokenTypeID TT_ID_ANYTHING = 1;
/** Token type ID: User type.
 *
 * To define your own token types, use USERTYPE_ID + n as 
 * a token type ID, where n is a positive number unique to the token 
 * type in your application.
 */
const TokenTypeID TT_ID_USERTYPE = 100;

/// Token type: invalid.
const TokenType TT_INVALID = { TT_ID_INVALID, "", false, 0 };
/// Token type: none.
const TokenType TT_NONE = { TT_ID_NONE, "", false, 0 };
/// Token type: quoted.
const TokenType TT_QUOTED = { 2, "", false, 0 };
/// Token type: escaped.
const TokenType TT_ESCAPED = { 3, "", false, 0 };
/// Token type: whitespace.
const TokenType TT_WHITESPACE = { 4, " \t", false, 0 };
/// Token type: lineterm.
const TokenType TT_LINETERM = { 5, "\n\r", false, 1 };
/// Token type: identifier.
const TokenType TT_IDENTIFIER = { 6, 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", 
	false, 0 };
/// Token type: number.
const TokenType TT_NUMBER = { 7, "0123456789", false, 0 };
/// Token type: alpha.
const TokenType TT_ALPHA = { 8, 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 
	false, 0 };
/// Token type: default separator.
const TokenType TT_DEFAULT_SEP = { 7, "_-.", false, 0 };

/// Token: invalid,
const Token TOK_INVALID = {TT_ID_INVALID, ""};
/// Token: none.
const Token TOK_NONE = {TT_ID_NONE, ""};

/// Quote characters.
const std::string QUOTE_CHARS = "\"'";
/// Escape character.
const char ESCAPE_CHAR = '\\';

/// Default size for directory name buffers.
const int DIR_BUFFER_SIZE = 1024;
/// Maximum size for directory name buffers.
const int DIR_BUFFER_SIZE_MAX = 65536;
/// Directory separator.
const char DIR_SEPARATOR = '/';
/// File extension separator.
const char FILE_EXT_SEPARATOR = '.';

/// Template file extension.
const std::string TEMPLATE_FILE_EXT = ".tpl";
/// Template module separator.
const std::string TEMPLATE_MODULE_SEP = ".";
/// Default template path separator.
const std::string DEFAULT_TEMPLATE_PATH_SEP = ":";

}

}

/** \file constants.hpp
 * \brief Constants (header).
 */
#endif
