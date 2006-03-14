/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * tokenizer.cpp                  Tokenizer test.
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

#include <iostream>
#include <string>
#include "ionflux/Tokenizer.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	string test = "This is a function call:\nfoo('bar', 'b\\'az')";
	Tokenizer tok(test);
	cout << "Test string:" << endl << test << endl;
	/* NOTE: Fully qualified name of TokenType required by MinGW for some 
	   unknown reason. Strange, since all other types from Tokenizer.h are 
	   imported, apparently, without problems. */
	Ionflux::Tools::TokenType notIdentifier = Tokenizer::TT_IDENTIFIER;
	notIdentifier.typeID = TokenType::USERTYPE_ID + 1;
	notIdentifier.invert = true;
	notIdentifier.maxChars = 1;
	tok.addTokenType(notIdentifier);
	int numTokens = 0;
	Token currentToken = tok.nextToken();
	cout << "Running with notIdentifier user type (maxChars = 1):" 
		<< endl;
	while((currentToken.typeID != Tokenizer::TT_NONE.typeID)
		&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
	{
		cout << "    Token #" << (numTokens + 1) << " (typeID " 
			<< currentToken.typeID << "): '" << currentToken.value << "'"
			<< endl;
		currentToken = tok.nextToken();
		numTokens++;
	}
	if (currentToken.typeID == Tokenizer::TT_INVALID.typeID)
		cout << "Invalid token, aborted." << endl;
	tok.reset();
	tok.useDefaultTokenTypes();
	tok.setTokenTypeAnything();
	numTokens = 0;
	currentToken = tok.nextToken();
	cout << "Running with TT_ANYTHING special type (maxChars = 0):" 
		<< endl;
	while((currentToken.typeID != Tokenizer::TT_NONE.typeID)
		&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
	{
		cout << "    Token #" << (numTokens + 1) << " (typeID " 
			<< currentToken.typeID << "): '" << currentToken.value << "'"
			<< endl;
		currentToken = tok.nextToken();
		numTokens++;
	}
	if (currentToken.typeID == Tokenizer::TT_INVALID.typeID)
		cout << "Invalid token, aborted." << endl;
	return 0;
}

/** \file tokenizer.cpp
 * \brief Tokenizer test.
 */
