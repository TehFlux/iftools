#ifndef IONFLUX_TOOLS_UTF8TOKENIZER
#define IONFLUX_TOOLS_UTF8TOKENIZER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Utf8Tokenizer.hpp                 Tokenizer with UTF-8 support.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/Utf8TokenTypeMap.hpp"
#include "ionflux/ManagedObject.hpp"

namespace Ionflux
{

namespace Tools
{

/** A token for the UTF-8 tokenizer..
 * \ingroup tokenizer
 */
struct Utf8Token
{
	/// Numeric token type ID.
	int typeID;
	/// UTF-8 encoded value of the token.
	std::string value;
};

/// Class information for class Utf8Tokenizer.
class Utf8TokenizerClassInfo
: public Ionflux::Tools::ClassInfo
{
	public:
		/// Constructor.
		Utf8TokenizerClassInfo();
		/// Destructor.
		virtual ~Utf8TokenizerClassInfo() { };
};

/** Tokenizer with UTF-8 support.
 * \ingroup tokenizer
 *
 * A generic tokenizer for parsing UTF-8 strings. To set up a tokenizer, 
 * first create a Utf8Tokenizer object. This will be set up using the 
 * default token types Utf8Tokenizer::TT_WHITESPACE, 
 * Utf8Tokenizer::TT_LINETERM and Utf8Tokenizer::TT_IDENTIFIER. You may 
 * then add your own custom token types and optionally set up the 
 * Utf8Tokenizer::TT_ANYTHING token type (which will match anything not 
 * matched by previously defined token types). To enable extraction of 
 * quoted strings and escaped characters, call 
 * Utf8Tokenizer::setExtractQuoted() with \c true as an argument.\n
 * To get a token from the token stream, call 
 * Utf8Tokenizer::getNextToken(). Make sure your code handles the 
 * Utf8Tokenizer::TT_NONE and Utf8Tokenizer::TT_INVALID special token types
 * (which cannot be disabled). Utf8Tokenizer::getNextToken() will always 
 * return Utf8Tokenizer::TT_NONE at the end of the token stream and 
 * Utf8Tokenizer::TT_INVALID if an invalid token is encountered.
 */
class Utf8Tokenizer
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Input characters to be tokenized.
		std::vector<unsigned int> theInput;
		/// Quote characters.
		std::vector<unsigned int> quoteChars;
		/// Current position in the input character string.
		unsigned int currentPos;
		/// Position of the current token in the input character string.
		unsigned int currentTokenPos;
		/// The current quote character.
		unsigned int currentQuoteChar;
		/// Token type map.
		Utf8TokenTypeMap* typeMap;
		/// Current token.
		Utf8Token currentToken;
		/// Extract quoted strings flag.
		bool extractQuoted;
		/// Extract escaped characters flag.
		bool extractEscaped;
		
	public:
		/// Token type: invalid (special).
		static const Utf8TokenType TT_INVALID;
		/// Token type: none (special).
		static const Utf8TokenType TT_NONE;
		/// Token type: default (special).
		static const Utf8TokenType TT_DEFAULT;
		/// Token type: quoted (special).
		static const Utf8TokenType TT_QUOTED;
		/// Token type: escaped (special).
		static const Utf8TokenType TT_ESCAPED;
		/// Token type: linear whitespace.
		static const Utf8TokenType TT_LINEAR_WHITESPACE;
		/// Token type: linear whitespace.
		static const Utf8TokenType TT_LINETERM;
		/// Token type: identifier.
		static const Utf8TokenType TT_IDENTIFIER;
		/// Token type: identifier.
		static const Utf8TokenType TT_NUMBER;
		/// Token type: latin alphabet.
		static const Utf8TokenType TT_ALPHA;
		/// Token type: default separators.
		static const Utf8TokenType TT_DEFAULT_SEP;
		/// Token type: lots of latin characters.
		static const Utf8TokenType TT_LATIN;
		/// Token type: invalid (special).
		static const Utf8Token TOK_INVALID;
		/// Token type: none (special).
		static const Utf8Token TOK_NONE;
		/// Quote characters.
		static const std::string QUOTE_CHARS;
		/// Escape character.
		static const unsigned int ESCAPE_CHAR;
		/// Class information instance.
		static const Utf8TokenizerClassInfo utf8TokenizerClassInfo;
		/// Class information.
		static const Ionflux::Tools::ClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Utf8Tokenizer object.
		 */
		Utf8Tokenizer();
		
		/** Constructor.
		 *
		 * Construct new Utf8Tokenizer object.
		 *
		 * \param initInput UTF-8 input string.
		 */
		Utf8Tokenizer(const std::string& initInput);
		
		/** Constructor.
		 *
		 * Construct new Utf8Tokenizer object.
		 *
		 * \param initTokenTypes Token types.
		 * \param initInput UTF-8 input string.
		 */
		Utf8Tokenizer(const std::vector<Utf8TokenType>& initTokenTypes, const 
		std::string& initInput = "");
		
		/** Destructor.
		 *
		 * Destruct Utf8Tokenizer object.
		 */
		virtual ~Utf8Tokenizer();
		
		/** Reset.
		 *
		 * Reset the tokenizer.
		 */
		virtual void reset();
		
		/** Clear token types.
		 *
		 * Remove all token types.
		 */
		virtual void clearTokenTypes();
		
		/** Use default token types.
		 *
		 * Use default token types (TT_LINEAR_WHITESPACE, TT_IDENTIFIER, 
		 * TT_LINETERM).
		 */
		virtual void useDefaultTokenTypes();
		
		/** Add default token type.
		 *
		 * Add a special token type TT_DEFAULT which will be returned if a 
		 * token is not recognized.
		 */
		virtual void addDefaultTokenType();
		
		/** Set token types.
		 *
		 * Set the token types for the tokenizer.
		 *
		 * \param newTokenTypes .
		 */
		virtual void setTokenTypes(const std::vector<Utf8TokenType>& 
		newTokenTypes);
		
		/** Add token types.
		 *
		 * Add the specified token types.
		 *
		 * \param newTokenTypes .
		 */
		virtual void addTokenTypes(const std::vector<Utf8TokenType>& 
		newTokenTypes);
		
		/** Add token type.
		 *
		 * Add the specified token type.
		 *
		 * \param newTokenType Token type.
		 */
		virtual void addTokenType(const Utf8TokenType& newTokenType);
		
		/** Set input.
		 *
		 * Set the UTF-8 encoded input string.
		 *
		 * \param newInput UTF-8 input string.
		 */
		virtual void setInput(const std::string& newInput);
		
		/** Set input.
		 *
		 * Set the unicode input characters.
		 *
		 * \param newInput Unicode characters.
		 */
		virtual void setInput(const std::vector<unsigned int>& newInput);
		
		/** Get next token.
		 *
		 * Get the next token from the input string. If the optional \c 
		 * otherTypeMap is set, the specified token type map will be used 
		 * instead of the default token type map.
		 *
		 * \param otherTypeMap Token type map.
		 *
		 * \return Next token.
		 */
		virtual Utf8Token getNextToken(Utf8TokenTypeMap* otherTypeMap = 0);
		
		/** Get current token.
		 *
		 * Get the current token from the input string.
		 *
		 * \return Current token.
		 */
		virtual Utf8Token getCurrentToken();
		
		/** Get current token type.
		 *
		 * Get the type ID of the current token.
		 *
		 * \return Type ID of current token.
		 */
		virtual int getCurrentTokenType();
		
		/** Get current position.
		 *
		 * Get the current position in the input string.
		 *
		 * \return Current position.
		 */
		virtual unsigned int getCurrentPos();
		
		/** Get current token position.
		 *
		 * Get the position of the current token in the input string.
		 *
		 * \return Current token position.
		 */
		virtual unsigned int getCurrentTokenPos();
		
		/** Get quote character.
		 *
		 * Get the quote character for the current token.
		 *
		 * \return Current quote character.
		 */
		virtual unsigned int getQuoteChar();
		
		/** Validate token.
		 *
		 * Check whether the specified token is valid (i.e. it is not invalid 
		 * or empty).
		 *
		 * \param checkToken Token to be checked.
		 *
		 * \return \c true if the specified token is valid, \c false otherwise.
		 */
		static bool isValid(const Utf8Token& checkToken);
		
		/** Set extract quoted strings flag.
		 *
		 * Set new value of extract quoted strings flag.
		 *
		 * \param newExtractQuoted New value of extract quoted strings flag.
		 */
		virtual void setExtractQuoted(bool newExtractQuoted);
		
		/** Get extract quoted strings flag.
		 *
		 * \return Current value of extract quoted strings flag.
		 */
		virtual bool getExtractQuoted() const;
		
		/** Set extract escaped characters flag.
		 *
		 * Set new value of extract escaped characters flag.
		 *
		 * \param newExtractEscaped New value of extract escaped characters flag.
		 */
		virtual void setExtractEscaped(bool newExtractEscaped);
		
		/** Get extract escaped characters flag.
		 *
		 * \return Current value of extract escaped characters flag.
		 */
		virtual bool getExtractEscaped() const;
};

}

}

/** \file Utf8Tokenizer.hpp
 * \brief Tokenizer with UTF-8 support header.
 */
#endif
