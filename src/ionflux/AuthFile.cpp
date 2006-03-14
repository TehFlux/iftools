/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AuthFile.cpp                    File based authentication.
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

#include "ionflux/AuthFile.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const TokenType AuthFile::TT_USER_PASS_SEP = {
	TokenType::USERTYPE_ID + 1, ":", false, 1};

AuthFile::AuthFile()
: authFile("")
{
	// TODO: Nothing ATM. ;-)
}

AuthFile::AuthFile(const std::string &initAuthFile)
{
	setAuthFile(initAuthFile);
	parse();
}

AuthFile::~AuthFile()
{
	// TODO: Nothing ATM. ;-)
}

void AuthFile::parse()
{
	if (authFile == "")
		return;
	string authFileInput = readFile(authFile);
	if (authFileInput == "")
		return;
	Tokenizer tok;
	tok.addTokenType(TT_USER_PASS_SEP);
	tok.setTokenTypeAnything();
	tok.setInput(authFileInput);
	Token currentToken = tok.nextToken();
	AuthData currentAuth;
	authData.clear();
	bool error = false;
	string errorReason;
	while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
		&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID)
		&& !error)
	{
		// Skip leading whitespace.
		while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
			currentToken = tok.nextToken();
		// Extract username.
		currentAuth.username = "";
		while ((currentToken.typeID != TT_USER_PASS_SEP.typeID)
			&& (currentToken.typeID != Tokenizer::TT_NONE.typeID)
			&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
		{
			currentAuth.username.append(currentToken.value);
			currentToken = tok.nextToken();
		}
		if (currentToken.typeID != TT_USER_PASS_SEP.typeID)
		{
			error = true;
			errorReason = "Username/password separator expected.";
		} else
		{
			currentToken = tok.nextToken();
			// Extract password.
			if (currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
				currentAuth.password = currentToken.value;
			currentToken = tok.nextToken();
			// Add authentication data record.
			authData.push_back(currentAuth);
			// Skip trailing whitespace.
			while ((currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
				|| (currentToken.typeID == Tokenizer::TT_LINETERM.typeID))
				currentToken = tok.nextToken();
		}
	}
	if (currentToken.typeID == Tokenizer::TT_INVALID.typeID)
		errorReason = "Invalid token.";
	if (error)
	{
		ostringstream status;
		status << "[AuthFile::parse] ERROR: Parse error at token '" 
			<< currentToken.value << "': " << errorReason;
		log.msg(status.str(), log.VL_ERROR);
	}
}

void AuthFile::setAuthFile(const std::string &newAuthFile)
{
	authFile = newAuthFile;
}

bool AuthFile::auth(const std::string &username, const std::string &password)
{
	bool found = false;
	unsigned int i = 0;
	while (!found && (i < authData.size()))
	{
		if (authData[i].username == username)
			found = true;
		else
			i++;
	}
	if (!found)
		return false;
	if (sha1(password) == parseHex(authData[i].password))
		return true;
	return false;
}

void AuthFile::getSecret(const std::string &username, std::string &secret)
{
	bool found = false;
	unsigned int i = 0;
	while (!found && (i < authData.size()))
	{
		if (authData[i].username == username)
			found = true;
		else
			i++;
	}
	if (!found)
	{
		secret = "";
		return;
	}
	secret = parseHex(authData[i].password);
	return;
}

Reporter &AuthFile::getLog()
{
	return log;
}

void AuthFile::printDebugInfo()
{
	if (authData.size() == 0)
	{
		cout << "No authentication records available." << endl;
		return;
	}
	for (unsigned int i = 0; i < authData.size(); i++)
	{
		cout << "[" << i << "] " << authData[i].username << ":" 
			<< authData[i].password << endl;
	}
}

}

}

/** \file AuthFile.cpp
 * \brief File based authentication implementation.
 */
