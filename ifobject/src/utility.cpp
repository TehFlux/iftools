/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utility.cpp                 Utility functions (implementation).
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

#include <sstream>
#include <fstream>
#include "ifobject/utility.hpp"
#include "ifobject/IFObject.hpp"
#include "ifobject/IFLogMessage.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

bool readFile(const std::string& fileName, std::string& target, 
    Ionflux::ObjectBase::IFObject* logTarget)
{
	ifstream inFile(fileName.c_str());
    if (!inFile)
    {
        if (logTarget != 0)
        {
            ostringstream message;
            message << "Could not open file '" << fileName << "'.";
            logTarget->log(IFLogMessage(message.str(), VL_ERROR, 0, 
                "readFile"));
        }
        return false;
    }
	char *buffer = new char[READ_BUFFER_SIZE];
	int bytesRead;
	inFile.read(buffer, READ_BUFFER_SIZE);
	bytesRead = inFile.gcount();
    target = "";
	while (bytesRead > 0)
	{
		target.append(buffer, bytesRead);
		inFile.read(buffer, READ_BUFFER_SIZE);
		bytesRead = inFile.gcount();
	}
	delete[] buffer;
    return true;
}

void explode(const std::string& bytes, const std::string& splitString, 
	std::vector<std::string>& result)
{
	result.clear();
	if ((bytes.size() == 0) 
        || (splitString.size() == 0))
		return;
	string::size_type currentPos = 0;
	string::size_type nextPos;
	while ((currentPos < bytes.size()) 
		&& ((nextPos = bytes.find(splitString, currentPos)) != string::npos))
	{
		if ((nextPos - currentPos) > 0)
			result.push_back(bytes.substr(currentPos, nextPos - currentPos));
		else
			result.push_back("");
		currentPos = nextPos + 1;
	}
	result.push_back(bytes.substr(currentPos, bytes.size() - currentPos));
}

bool isOneOf(char c, const std::string& testChars)
{
	if (testChars.size() == 0)
		return false;
	if (testChars.find_first_of(c) == string::npos)
		return false;
	return true;
}

bool isNumber(const std::string &bytes)
{
	if (bytes.size() == 0)
		return false;
	bool result = true;
	unsigned int i = 0;
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], "0123456789"));
		i++;
	}
	return result;
}

bool isInteger(const std::string &bytes)
{
	if (bytes.size() == 0)
		return false;
	bool result = true;
	unsigned int i = 0;
	// Check signum.
	if ((bytes.size() > 1) && isOneOf(bytes[i], "+-"))
		i++;
	// Check integer part.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], "0123456789"));
		i++;
	}
	return result;
}

bool isFloat(const std::string &bytes)
{
	if (bytes.size() == 0)
		return false;
	const string numbers = "0123456789";
	const string dots = ".";
	const string exponent = "eE";
	const string signum = "+-";
	unsigned int i = 0;
	if (bytes.size() == 1)
		return isOneOf(bytes[0], numbers);
	// Check signum.
	if (isOneOf(bytes[i], signum))
		i++;
	bool result = true;
	// Check integer part.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], numbers));
		i++;
	}
	/* Accept dot if it is either preceded by a number (thus i > 1) 
	   or the next character is a number. */
	if (isOneOf(bytes[i - 1], dots) 
		&& ((i > 1) || ((i < bytes.size()) && isOneOf(bytes[i], numbers))))
		result = true;
	// Check decimal part.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], numbers));
		i++;
	}
	if (isOneOf(bytes[i - 1], exponent))
		result = true;
	// Check signum of exponent.
	if ((i < bytes.size()) && isOneOf(bytes[i], signum))
		i++;
	// Check exponent.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], numbers));
		i++;
	}
	return result;
}

bool isIdentifier(const std::string &bytes)
{
	const string identifierChars = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
	bool result = true;
	for (unsigned int i = 0; i < bytes.size(); i++)
		result = (result && isOneOf(bytes[i], identifierChars));
	return result;
}

std::string toUpper(const std::string &text, unsigned int numChars, 
	unsigned int offset)
{
	ostringstream result;
	char currentChar;
	if (numChars == 0)
		numChars = text.size();
	unsigned int count = 0;
	for (unsigned int i = 0; i < text.size(); i++)
	{
		if ((i >= offset) && (count < numChars))
		{
			currentChar = static_cast<char>(toupper(text[i]));
			count++;
		} else
			currentChar = text[i];
		result << currentChar;
	}
	return result.str();
}

std::string toLower(const std::string &text, unsigned int numChars, 
	unsigned int offset)
{
	ostringstream result;
	char currentChar;
	if (numChars == 0)
		numChars = text.size();
	unsigned int count = 0;
	for (unsigned int i = 0; i < text.size(); i++)
	{
		if ((i >= offset) && (count < numChars))
		{
			currentChar = static_cast<char>(tolower(text[i]));
			count++;
		} else
			currentChar = text[i];
		result << currentChar;
	}
	return result.str();
}

std::string trim(const std::string& bytes, bool leftTrim, bool rightTrim)
{
	if (bytes.size() == 0)
		return "";
	unsigned int from = 0;
	unsigned int to = bytes.size() - 1;
	static const string trimChars = " \t\r\n";
	if (leftTrim)
		while ((from <= to)
			&& isOneOf(bytes[from], trimChars))
			from++;
	if (rightTrim)
		while ((to >= from)
			&& isOneOf(bytes[to], trimChars))
			to--;
	string result;
	for (unsigned int i = from; i <= to; i++)
		result.append(1, bytes[i]);
	return result;
}

bool hasPrefix(const std::string& bytes, const std::string& prefix, 
    bool ignoreCase)
{
    std::string checkBytes;
    std::string checkPrefix;
    if (ignoreCase)
    {
        checkBytes = toLower(bytes);
        checkPrefix = toLower(prefix);
    } else
    {
        checkBytes = bytes;
        checkPrefix = prefix;
    }
    if (checkBytes.size() < checkPrefix.size())
        return false;
    if (checkBytes.substr(0, checkPrefix.size()) == checkPrefix)
        return true;
    return false;
}

bool hasPrefix(const std::string& bytes, const std::vector<std::string>& 
    prefixes, bool ignoreCase)
{
    std::vector<std::string>::const_iterator i = prefixes.begin();
    while (i != prefixes.end())
    {
        if (hasPrefix(bytes, *i, ignoreCase))
            return true;
    }
    return false;
}

}

}

/** \file utility.cpp
 * \brief Utility functions (implementation).
 */
