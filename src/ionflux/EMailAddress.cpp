/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * EMailAddress.cpp                EMail address.
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

#include "ionflux/EMailAddress.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const Ionflux::Tools::TokenType EMailAddress::TT_ATOM_TEXT = {
	TokenType::USERTYPE_ID + 1301, 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	"!#$%&'*+-/=?^_`{|}~", false, 0};
const Ionflux::Tools::TokenType EMailAddress::TT_SPECIAL = {
	TokenType::USERTYPE_ID + 1302, "()<>[]:;@\\,.\"", false, 1};
const Ionflux::Tools::TokenType EMailAddress::TT_FWS = {
	TokenType::USERTYPE_ID + 1303, " \t\r\n", false, 0};

EMailAddress::EMailAddress()
{
	// TODO: Nothing ATM. ;-)
}

EMailAddress::EMailAddress(const EMailAddress& initAddress)
{
	*this = initAddress;
}

EMailAddress::EMailAddress(const std::string& initRawAddress)
{
	*this = initRawAddress;
}

EMailAddress::~EMailAddress()
{
	// TODO: Nothing ATM. ;-)
}

void EMailAddress::clear()
{
	validAddress = false;
	mailboxes.clear();
	rawAddress = "";
	displayName = "";
}

bool EMailAddress::parse(const std::string& newRawAddress)
{
	if (newRawAddress.size() > 0)
		rawAddress = newRawAddress;
	validAddress = true;
	mailboxes.clear();
	displayName = "";
	Tokenizer tok;
	tok.clearTokenTypes();
	tok.addTokenType(TT_ATOM_TEXT);
	tok.addTokenType(TT_SPECIAL);
	tok.addTokenType(TT_FWS);
	tok.setTokenTypeAnything();
	tok.setExtractQuoted(false);
	tok.setExtractEscaped(true);
	tok.setInput(rawAddress);
	Token currentToken = tok.getNextToken();
	string item;
	Mailbox mailbox;
	StringTrim trim;
	bool quoted = false;
	unsigned int nestingLevel = 0;
	bool havePhrase = true;
	bool haveQuotedString = true;
	bool haveDotAtom = true;
	bool haveAtom = true;
	bool haveAddress = false;
	bool haveAngleAddress = false;
	bool haveGroup = false;
	while (Tokenizer::isValid(currentToken))
	{
		while ((currentToken.typeID == TT_ATOM_TEXT.typeID)
			|| (currentToken.typeID == TT_FWS.typeID))
		{
			// Append atom tokens.
			if (currentToken.typeID == TT_ATOM_TEXT.typeID)
				haveQuotedString = false;
			item.append(currentToken.value);
			currentToken = tok.getNextToken();
		}
		if (currentToken.typeID == TT_SPECIAL.typeID)
		{
			// Special character.
			if (currentToken.value == "\"")
			{
				// Quote character.
				haveDotAtom = false;
				haveAtom = false;
				quoted = true;
				item.append(currentToken.value);
				currentToken = tok.getNextToken();
				while (quoted && Tokenizer::isValid(currentToken))
				{
					item.append(currentToken.value);
					if ((currentToken.typeID == TT_SPECIAL.typeID)
						&& (currentToken.value == "\""))
						quoted = false;
					currentToken = tok.getNextToken();
				}
			} else
			if (currentToken.value == "(")
			{
				// Comment.
				nestingLevel = 1;
				item.append(currentToken.value);
				currentToken = tok.getNextToken();
				while ((nestingLevel > 0) 
					&& Tokenizer::isValid(currentToken))
				{
					item.append(currentToken.value);
					if (currentToken.typeID == TT_SPECIAL.typeID)
					{
						if (currentToken.value == "(")
							nestingLevel++;
						else
						if (currentToken.value == ")")
							nestingLevel--;
					}
					currentToken = tok.getNextToken();
				}
			} else
			if (currentToken.value == ".")
			{
				// Dot special character.
				havePhrase = false;
				haveAtom = false;
				item.append(currentToken.value);
				currentToken = tok.getNextToken();
			} else
			if (currentToken.value == "@")
			{
				// At special character.
				if (haveAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Unexpected token "
						"'@' in address." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (!(haveDotAtom || haveQuotedString))
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Dot-atom or "
						"quoted string expected before '@'." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				mailbox.localPart = trim.process(item, 0);
				if (mailbox.localPart.size() == 0)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Local part of "
						"address is empty." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				item = "";
				havePhrase = true;
				haveQuotedString = true;
				haveDotAtom = true;
				haveAtom = true;
				haveAddress = true;
				currentToken = tok.getNextToken();
			} else
			if (currentToken.value == "<")
			{
				if (haveAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Unexpected token "
						"'<' in address." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (haveAngleAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Unexpected token "
						"'<' in angle address." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (!havePhrase)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Phrase expected "
						"before '<'." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				mailbox.displayName = trim.process(item, 0);
				item = "";
				havePhrase = true;
				haveQuotedString = true;
				haveDotAtom = true;
				haveAtom = true;
				haveAngleAddress = true;
				currentToken = tok.getNextToken();
			} else
			if (currentToken.value == ">")
			{
				if (!haveDotAtom)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Dot-atom expected "
						"before '>'." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (!haveAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Address expected "
						"before '>'." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (!haveAngleAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: '<' missing "
						"before '>'." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				mailbox.domain = trim.process(item, 0);
				if (mailbox.domain.size() == 0)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Domain of "
						"address is empty." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				item = "";
				havePhrase = true;
				haveQuotedString = true;
				haveDotAtom = true;
				haveAtom = true;
				haveAddress = false;
				haveAngleAddress = false;
				mailbox.address = mailbox.localPart + "@" + mailbox.domain;
				mailboxes.push_back(mailbox);
				mailbox.displayName = "";
				mailbox.address = "";
				mailbox.localPart = "";
				mailbox.domain = "";
				currentToken = tok.getNextToken();
			} else
			if (currentToken.value == ":")
			{
				if (haveAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Unexpected token "
						"':' in address." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (haveAngleAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Unexpected token "
						"':' in angle address." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (!havePhrase)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Phrase expected "
						"before ':'." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				displayName = trim.process(item, 0);
				item = "";
				havePhrase = true;
				haveQuotedString = true;
				haveDotAtom = true;
				haveAtom = true;
				haveGroup = true;
				currentToken = tok.getNextToken();
			} else
			if (currentToken.value == ",")
			{
				if (haveAddress)
				{
					// Open address.
					if (!haveDotAtom)
					{
						// ----- DEBUG ----- //
						cerr << "[EMailAddress::parse] ERROR: Expected "
							"dot-atom before ','." << endl;
						// ----- DEBUG ----- */
						validAddress = false;
						return false;
					}
					mailbox.domain = trim.process(item, 0);
					if (mailbox.domain.size() == 0)
					{
						// ----- DEBUG ----- //
						cerr << "[EMailAddress::parse] ERROR: Domain of "
							"address is empty." << endl;
						// ----- DEBUG ----- */
						validAddress = false;
						return false;
					}
					mailbox.address = mailbox.localPart + "@" + mailbox.domain;
					mailboxes.push_back(mailbox);
					mailbox.displayName = "";
					mailbox.address = "";
					mailbox.localPart = "";
					mailbox.domain = "";
					haveAddress = false;
				}
				if (haveAngleAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Unexpected token "
						"',' in angle address." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (!haveGroup)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: ':' missing "
						"before ','." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				item = "";
				havePhrase = true;
				haveQuotedString = true;
				haveDotAtom = true;
				haveAtom = true;
				currentToken = tok.getNextToken();
			} else
			if (currentToken.value == ";")
			{
				if (haveAddress)
				{
					// Open address.
					if (!haveDotAtom)
					{
						// ----- DEBUG ----- //
						cerr << "[EMailAddress::parse] ERROR: Expected "
							"dot-atom before ';'." << endl;
						// ----- DEBUG ----- */
						validAddress = false;
						return false;
					}
					mailbox.domain = trim.process(item, 0);
					if (mailbox.domain.size() == 0)
					{
						// ----- DEBUG ----- //
						cerr << "[EMailAddress::parse] ERROR: Domain of "
							"address is empty." << endl;
						// ----- DEBUG ----- */
						validAddress = false;
						return false;
					}
					mailbox.address = mailbox.localPart + "@" + mailbox.domain;
					mailboxes.push_back(mailbox);
					mailbox.displayName = "";
					mailbox.address = "";
					mailbox.localPart = "";
					mailbox.domain = "";
					haveAddress = false;
				}
				if (haveAngleAddress)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: Unexpected token "
						"';' in angle address." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				if (!haveGroup)
				{
					// ----- DEBUG ----- //
					cerr << "[EMailAddress::parse] ERROR: ':' missing "
						"before ';'." << endl;
					// ----- DEBUG ----- */
					validAddress = false;
					return false;
				}
				item = "";
				havePhrase = true;
				haveQuotedString = true;
				haveDotAtom = true;
				haveAtom = true;
				haveGroup = false;
				currentToken = tok.getNextToken();
			} else
			{
				// ----- DEBUG ----- //
				cerr << "[EMailAddress::parse] ERROR: Unexpected special "
					"character '" << currentToken.value << "'." << endl;
				// ----- DEBUG ----- */
				validAddress = false;
				return false;
			}
		} else
		if (Tokenizer::isValid(currentToken))
		{
			// ----- DEBUG ----- //
			cerr << "[EMailAddress::parse] ERROR: Unexpected token '"
				<< currentToken.value << "'." << endl;
			// ----- DEBUG ----- */
			validAddress = false;
			return false;
		}
	}
	if (quoted || (nestingLevel > 0))
	{
		// ----- DEBUG ----- //
		cerr << "[EMailAddress::parse] ERROR: Quote or comment "
			"parenthesis mismatch." << endl;
		// ----- DEBUG ----- */
		validAddress = false;
		return false;
	}
	if (haveGroup)
	{
		// ----- DEBUG ----- //
		cerr << "[EMailAddress::parse] ERROR: ';' missing "
			"after ':'." << endl;
		// ----- DEBUG ----- */
		validAddress = false;
		return false;
	}
	if (haveAngleAddress)
	{
		// ----- DEBUG ----- //
		cerr << "[EMailAddress::parse] ERROR: '>' missing "
			"after '<'." << endl;
		// ----- DEBUG ----- */
		validAddress = false;
		return false;
	}
	if (haveAddress)
	{
		// Open address.
		if (!haveDotAtom)
		{
			// ----- DEBUG ----- //
			cerr << "[EMailAddress::parse] ERROR: Expected "
				"dot-atom before ';'." << endl;
			// ----- DEBUG ----- */
			validAddress = false;
			return false;
		}
		mailbox.domain = trim.process(item, 0);
		if (mailbox.domain.size() == 0)
		{
			// ----- DEBUG ----- //
			cerr << "[EMailAddress::parse] ERROR: Domain of "
				"address is empty." << endl;
			// ----- DEBUG ----- */
			validAddress = false;
			return false;
		}
		mailbox.address = mailbox.localPart + "@" + mailbox.domain;
		mailboxes.push_back(mailbox);
	}
	if ((mailboxes.size() == 1)
		&& (displayName.size() == 0))
		displayName = mailboxes[0].displayName;
	return true;
}

bool EMailAddress::isValid() const
{
	return validAddress;
}

const std::vector<Mailbox>& EMailAddress::getMailboxes() const
{
	return mailboxes;
}

unsigned int EMailAddress::getNumMailboxes() const
{
	return mailboxes.size();
}

Mailbox EMailAddress::getMailbox(unsigned int mailboxIndex) const
{
	if (mailboxIndex > mailboxes.size())
		return Mailbox();
	return mailboxes[mailboxIndex];
}

EMailAddress& EMailAddress::operator=(const EMailAddress& newEMailAddress)
{
	mailboxes = newEMailAddress.getMailboxes();
	rawAddress = newEMailAddress.getRawAddress();
	validAddress = newEMailAddress.isValid();
	displayName = newEMailAddress.getDisplayName();
	return *this;
}

EMailAddress& EMailAddress::operator=(const std::string& newRawAddress)
{
	setRawAddress(newRawAddress);
	return *this;
}

void EMailAddress::printDebugInfo() const
{
	cerr << "EMailAddress DEBUG information:" << endl
		<< "  rawAddress = '" << rawAddress << "'" << endl
		<< "  displayName = '" << displayName << "'" << endl
		<< "Mailboxes:" << endl;
	for (unsigned int i = 0; i < mailboxes.size(); i++)
		cerr << "  [" << i << "] displayName = '" << mailboxes[i].displayName 
			<< "', address = '" << mailboxes[i].address << "'"
			<< ", localPart = '" << mailboxes[i].localPart << "'"
			<< ", domain = '" << mailboxes[i].domain  << "'" << endl;
	cerr << "This address is ";
	if (validAddress)
		cerr << "VALID." << endl;
	else
		cerr << "NOT VALID." << endl;
}

void EMailAddress::setRawAddress(const std::string& newRawAddress)
{
	string oldRawAddress = rawAddress;
	rawAddress = newRawAddress;
	if (rawAddress != oldRawAddress)
		parse();
}

void EMailAddress::setDisplayName(const std::string& newDisplayName)
{
	displayName = newDisplayName;
}

std::string EMailAddress::getRawAddress() const
{
	return rawAddress;
}

std::string EMailAddress::getDisplayName() const
{
	return displayName;
}

}

}

/** \file EMailAddress.cpp
 * \brief EMail address implementation.
 */
