/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utf8tokenizer.cpp                  UTF-8 tokenizer test.
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
#include "ionflux/CLArgs.hpp"
#include "ionflux/ConfigTree.hpp"
#include "ionflux/Utf8Tokenizer.hpp"

typedef std::map<std::string, Ionflux::Tools::Utf8TokenType> TokenTypeNameMap;

using namespace std;
using namespace Ionflux::Tools;

/// Initialize token types from a configuration node.
void getTokenTypes(Ionflux::Tools::Node& source, TokenTypeNameMap& target)
{
	target.clear();
	Node& tokenTypeNode = source["tokenType"];
	unsigned int numTokenTypes = tokenTypeNode.getNumChildren();
	Node* currentChild = 0;
	string tokenTypeName;
	Utf8TokenType currentTokenType;
	for (unsigned int i = 0; i < numTokenTypes; i++)
	{
		currentChild = tokenTypeNode.getChild(i);
		if (currentChild != 0)
		{
			tokenTypeName = (*currentChild)["name"].getData();
			currentTokenType.typeID = 
				strtol((*currentChild)["typeID"].getData().c_str(), 0, 10);
			currentTokenType.validChars = 
				utf8Unescape(unquote((*currentChild)["validChars"].getData()));
			currentTokenType.maxChars = 
				strtol((*currentChild)["maxChars"].getData().c_str(), 0, 10);
			// ----- DEBUG ----- //
			cerr << "[getTokenTypes] DEBUG: Adding token type '" 
				<< tokenTypeName << "' (typeID = " << currentTokenType.typeID 
				<< ", validChars = '" << currentTokenType.validChars 
				<< "', maxChars = '" << currentTokenType.maxChars 
				<< "') to the map." << endl;
			// ----- DEBUG ----- */
			target[tokenTypeName] = currentTokenType;
		}
	}
}

/// Add token types from a map to the tokenizer.
void addTokenTypes(TokenTypeNameMap& source, Utf8Tokenizer& target)
{
	for (TokenTypeNameMap::iterator j = source.begin(); j != source.end(); j++)
	{
		// ----- DEBUG ----- //
		cerr << "[addTokenTypes] DEBUG: Adding token type '" << (*j).first 
			<< "' to tokenizer." << endl;
		// ----- DEBUG ----- */
		target.addTokenType((*j).second);
	}
}

/// Process tests.
void processTests(Utf8Tokenizer& tok, TokenTypeNameMap& defaultTokenTypes,
	Ionflux::Tools::Node& testConfig)
{
	unsigned int numTests = testConfig.getNumChildren();
	Node* currentChild = 0;
	for (unsigned int i = 0; i < numTests; i++)
	{
		currentChild = testConfig.getChild(i);
		if (currentChild != 0)
		{
			cerr << "Processing test " << i << ":" << endl;
			tok.clearTokenTypes();
			bool useDefaultTokenTypes = toBool((*currentChild)
				["useDefaultTokenTypes"].getData());
			bool addDefaultTokenType = toBool((*currentChild)
				["addDefaultTokenType"].getData());
			bool extractQuoted = toBool((*currentChild)
				["extractQuoted"].getData());
			bool extractEscaped = toBool((*currentChild)
				["extractEscaped"].getData());
			if (useDefaultTokenTypes)
				addTokenTypes(defaultTokenTypes, tok);
			if (addDefaultTokenType)
				tok.addDefaultTokenType();
			if (extractQuoted)
				tok.setExtractQuoted(true);
			if (extractEscaped)
				tok.setExtractEscaped(true);
			TokenTypeNameMap testTokenTypes;
			getTokenTypes(*currentChild, testTokenTypes);
			addTokenTypes(testTokenTypes, tok);
			Node& inputNode = (*currentChild)["input"];
			for (unsigned int k = 0; k < inputNode.getNumData(); k++)
			{
				string currentInput = inputNode.getData(k);
				cerr << "  Setting input to '" << currentInput << "'." << endl;
				tok.setInput(currentInput);
				Utf8Token currentToken = tok.getNextToken();
				unsigned int tokenCount = 0;
				while (Utf8Tokenizer::isValid(currentToken))
				{
					cerr << "    [" << tokenCount << "] '" 
						<< currentToken.value << "' ("
						<< currentToken.typeID << ")" << endl;
					currentToken = tok.getNextToken();
					tokenCount++;
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLParams params;
	args.getParams(params);
	string configFile = "test/conf/utf8tokenizer.conf";
	if (params.size() > 0)
		configFile = params[0];
	ConfigTree config;
	config.readConfig(configFile);
	TokenTypeNameMap defaultTokenTypes;
	getTokenTypes(config["defaultTokenTypes"], defaultTokenTypes);
	Utf8Tokenizer tok;
	processTests(tok, defaultTokenTypes, config["test"]);
	return 0;
}

/** \file utf8tokenizer.cpp
 * \brief UTF-8 tokenizer test.
 */
