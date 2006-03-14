#ifndef IONFLUX_TOOLS_TOKENIZER
#define IONFLUX_TOOLS_TOKENIZER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tokenizer.hpp                    Generic byte string tokenizer.
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
#include <vector>
#include "ionflux/tools.hpp"
#include "ionflux/TokenTypeMap.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup tokenizer String tokenizer
 *
 * A generic byte string tokenizer.
 *
 * @{
 */

/// Token type.
struct TokenType
{
	/// Numeric token type ID.
	int typeID;
	/// Valid characters for this token type.
	std::string validChars;
	/** Whether to invert the matching behavior.
	 *
	 * Set the invert flag if you want a token type to match any character 
	 * except those specified in validChars.
	 */
	bool invert;
	/** Maximum characters a token of this type can have.
	 *
	 * Set this to 0 (zero) or less to match any amount of characters.
	 */
	int maxChars;
	
	/** Token type ID: User type.
	 *
	 * To define your own token types, use USERTYPE_ID + n as 
	 * a token type ID, where n is a positive number unique to the token 
	 * type in your application.
	 */
	static const int USERTYPE_ID;
};

/// Token.
struct Token
{
	/// Numeric token type ID.
	int typeID;
	/// Token value.
	std::string value;
};

class TokenTypeMap;

/** Generic byte string tokenizer.
 *
 * A generic tokenizer for parsing byte strings. To set up a tokenizer, first 
 * create a Tokenizer object. This will be set up using the default token 
 * types Tokenizer::TT_WHITESPACE, Tokenizer::TT_LINETERM and 
 * Tokenizer::TT_IDENTIFIER. You may then add your own custom token types and 
 * optionally set up the Tokenizer::TT_ANYTHING token type (which will match 
 * anything not matched by previously defined token types). To enable 
 * extraction of quoted strings and escaped characters, call 
 * Tokenizer::setExtractQuoted() with \c true as an argument.\n
 * To get a token from the token stream, call Tokenizer::getNextToken(). Make 
 * sure your code handles the Tokenizer::TT_NONE and Tokenizer::TT_INVALID 
 * special token types (which cannot be disabled). Tokenizer::getNextToken() 
 * will always return Tokenizer::TT_NONE at the end of the token stream and 
 * Tokenizer::TT_INVALID if an invalid token is encountered.
 */
class Tokenizer
{
	protected:
		/// The input string to be parsed.
		std::string theInput;
		/// Current parsing position in the input string.
		unsigned int currentPos;
		/// Position of current token in the input string.
		unsigned int currentTokenPos;
		/// Current token.
		Token currentToken;
		/// Extract quoted strings flag.
		bool extractQuoted;
		/// Quote character.
		char currentQuoteChar;
		/// Extract escaped characters flag.
		bool extractEscaped;
		/// Token type map.
		TokenTypeMap *typeMap;
		
	public:
		/// Token type: Anything. (special)
		TokenType TT_ANYTHING;
		/// Token type: Invalid token. (special)
		static const TokenType TT_INVALID;
		/// Token type: No token. (special)
		static const TokenType TT_NONE;
		/// Token type: Quoted string. (special)
		static const TokenType TT_QUOTED;
		/// Token type: Escaped character. (special)
		static const TokenType TT_ESCAPED;
		/// Token type: Linear whitespace.
		static const TokenType TT_WHITESPACE;
		/// Token type: Line terminator.
		static const TokenType TT_LINETERM;
		/// Token type: Number.
		static const TokenType TT_NUMBER;
		/// Token type: Alpha (latin).
		static const TokenType TT_ALPHA;
		/// Token type: Default separator characters.
		static const TokenType TT_DEFAULT_SEP;
		/// Token type: Identifier.
		static const TokenType TT_IDENTIFIER;
		/// Token: Invalid token. (special)
		static const Token TOK_INVALID;
		/// Token: No token. (special)
		static const Token TOK_NONE;
		/// Type ID of the TT_ANYTHING token type.
		static const int TT_ANYTHING_TYPE_ID;
		/// Quote characters.
		static const std::string QUOTE_CHARS;
		/// Escape character.
		static const char ESCAPE_CHAR;
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 */
		Tokenizer();
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 *
		 * \param initInput The input string to be parsed.
		 */
		Tokenizer(const std::string& initInput);
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 *
		 * \param initTokenTypes Token types this tokenizer recognizes.
		 */
		Tokenizer(const std::vector<TokenType>& initTokenTypes);
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 *
		 * \param initTokenTypes Token types this tokenizer recognizes.
		 * \param initInput The input string to be parsed.
		 */
		Tokenizer(const std::vector<TokenType>& initTokenTypes, 
			const std::string& initInput);
		
		/** Destructor.
		 *
		 * Destruct Tokenizer object.
		 */
		virtual ~Tokenizer();
		
		/** Clear token types.
		 *
		 * Removes all token types from the set of recognized token types.
		 *
		 * \note Special token types will still be available to the tokenizer. 
		 * You can always restore the default set of token types with 
		 * useDefaultTokenTypes().
		 *
		 * \sa useDefaultTokenTypes()
		 */
		virtual void clearTokenTypes();
		
		/** Use default token types.
		 *
		 * Initializes the set of recognized token types with the default 
		 * token types.
		 */
		virtual void useDefaultTokenTypes();
		
		/** Set token types.
		 *
		 * Set the set of token types recognized by this tokenizer.\n
		 *
		 * \note The special token types are always available, regardless of
		 * whether they are added or not.
		 *
		 * \param newTokenTypes Set of token types.
		 */
		virtual void setTokenTypes(const std::vector<TokenType>& newTokenTypes);
		
		/** Add a token type.
		 *
		 * Adds a token type (possibly user defined) to the set of token types
		 * recognized by this tokenizer.
		 *
		 * \param newTokenType Token type to be added.
		 */
		virtual void addTokenType(const TokenType& newTokenType);
		
		/** Add token types.
		 *
		 * Adds token types (possibly user defined) to the set of token types 
		 * recognized by this Tokenizer.
		 *
		 * \param newTokenTypes Set of token types to be added.
		 */
		virtual void addTokenTypes(const std::vector<TokenType>& newTokenTypes);
		
		/** Set input.
		 *
		 * Sets the input string to be parsed.
		 *
		 * \param newInput The input string to be parsed.
		 */
		virtual void setInput(const std::string& newInput);
		
		/** Get next token.
		 *
		 * Parse the input string and get the next token.
		 *
		 * \deprecated You should not use this function because its name is 
		 * inconsistent with the interface. Use getNextToken() instead. This 
		 * function is provided for backward compatibility only. 
		 *
		 * \return The next token from the current input.
		 *
		 * \sa getNextToken()
		 */
		virtual Token nextToken();
		
		/** Get next token.
		 *
		 * Parse the input string and get the next token.
		 *
		 * \param otherMap Token type map to be used for extracting the next 
		 * token.
		 *
		 * \return The next token from the current input.
		 */
		virtual Token getNextToken(const TokenTypeMap &otherMap);
		
		/** Get next token.
		 *
		 * Parse the input string and get the next token.
		 *
		 * \return The next token from the current input.
		 */
		virtual Token getNextToken();
		
		/** Get current token.
		 *
		 * Get the current token.
		 *
		 * \return The current token.
		 */
		virtual Token getCurrentToken();
		
		/** Get type of current token.
		 *
		 * Get the type of the current token.
		 *
		 * \return Type ID of the current token.
		 */
		virtual int getCurrentTokenType();
		
		/** Reset the parser.
		 *
		 * Reset the parser so the input can be parsed again from the 
		 * beginning.
		 */
		virtual void reset();
		
		/** Set special token type TT_ANYTHING.
		 *
		 * This sets up a special token type TT_ANYTHING that will match any
		 * characters not matched by any of the previously defined token 
		 * types.
		 *
		 * \note You may call this again to update TT_ANYTHING if you add 
		 * further token types after a call to setTokenTypeAnything().
		 */
		virtual void setTokenTypeAnything();
		
		/** Set quoted string extraction flag.
		 *
		 * Pass \c true to this function to enable extraction of quoted 
		 * strings (and escaped characters), or disable this feature by 
		 * passing \c false.
		 *
		 * \note If you enable extraction of quoted strings, you should make 
		 * sure that your code handles the TT_QUOTED and TT_ESCAPED special 
		 * token types.
		 *
		 * \param newExtractQuoted Whether to extract quoted strings.
		 */
		virtual void setExtractQuoted(bool newExtractQuoted);
		
		/** Set escaped character extraction flag.
		 *
		 * Pass \c true to this function to enable extraction of escaped 
		 * characters, or disable this feature by passing \c false.
		 *
		 * \note If you enable extraction of escaped characters, you should 
		 * make sure that your code handles the TT_ESCAPED special token type. 
		 * If you have enabled quoted string extraction, escaped character 
		 * extraction will also be enabled by default (and cannot be disabled).
		 *
		 * \param newExtractEscaped Whether to extract escaped characters.
		 */
		virtual void setExtractEscaped(bool newExtractEscaped);
		
		/** Get current position.
		 *
		 * Get the current parsing position relative to the first character 
		 * of the input string.
		 *
		 * \return Current parsing position.
		 */
		virtual unsigned int getCurrentPos();
		
		/** Get position of current token.
		 *
		 * Get the position of the current token relative to the first 
		 * character of the input string.
		 *
		 * \return Position of current token.
		 */
		virtual unsigned int getCurrentTokenPos();
		
		/** Get quote character.
		 *
		 * Get the quote character of a quoted string.
		 *
		 * \return Quote character of the current token if this token is a 
		 * quoted string, or 0, if the current token is not a quoted string.
		 */
		virtual char getQuoteChar();
		
		/** Check type of a character.
		 *
		 * Returns \c true if the character \c c is one of the characters of
		 * \c testChars (if \c invert is false). If you pass \c true to 
		 * \c invert, the return value is inverted, i.e. the function 
		 * returns \c true if \c c is not one of the characters of 
		 * \c testChars.
		 *
		 * \deprecated You should not use this, since it is obsolete and may 
		 * be removed in future versions. Use Ionflux::Tools::isOneOf() 
		 * instead. This function is provided for backward compatibility only.
		 *
		 * \param c Character to be checked.
		 * \param testChars String of characters.
		 * \param invert Whether to invert the result.
		 *
		 * \return \c true if the character is one of \c testChars, \c false 
		 * otherwise. The result is inverted if \c true is passed to 
		 * \c invert.
		 */
		static bool isOneOf(char c, const std::string& testChars, bool invert);
		
		/** Check whether a token is valid.
		 *
		 * Check whether a token is a valid and well defined token (i.e., not 
		 * TT_NONE or TT_INVALID).
		 *
		 * \param token Token to be checked.
		 */
		static bool isValid(Token& token);
};

/// @}

}

}

/** \file Tokenizer.hpp
 * \brief Generic byte string tokenizer header.
 */
#endif
