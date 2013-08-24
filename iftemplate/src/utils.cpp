/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.cpp                     Utility functions (implementation).
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
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <dirent.h>
#include "ifobject/serialize.hpp"
#include "ifobject/utils.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/NodeReference.hpp"
#include "iftemplate/CharTypeMap.hpp"
#include "iftemplate/File.hpp"
#include "iftemplate/Tokenizer.hpp"

namespace Ionflux
{

namespace Template
{

int unpackInt(const std::string& bytes)
{
    int v = 0;
    Ionflux::ObjectBase::unpack(bytes, v);
    return v;
}

bool unpackBool(const std::string& bytes)
{
    bool v = false;
    Ionflux::ObjectBase::unpack(bytes, v);
    return v;
}

std::string nodeRefTypeToString(Ionflux::Template::NodeRefTypeID t)
{
    if (t == NodeReference::TYPE_INVALID)
        return "INVALID";
    if (t == NodeReference::TYPE_NAME)
        return "NAME";
    if (t == NodeReference::TYPE_ID)
        return "ID";
    if (t == NodeReference::TYPE_PATH)
        return "PATH";
    if (t == NodeReference::TYPE_EMPTY)
        return "EMPTY";
    return "<unknown>";
}

int getOpPrecedence(const std::string &op, bool unary)
{
	int result = -1;
	if ((op == "++") || (op == "--") || (op == "~") || (op == "!")
		|| (unary && ((op == "+") || (op == "-"))))
		return 10;
	else
	if ((op == "*") || (op == "/") || (op == "%"))
		return 9;
	else
	if ((op == "+") || (op == "-"))
		return 8;
	else
	if ((op == "<<") || (op == ">>"))
		return 7;
	else
	if ((op == "<") || (op == "<=") || (op == ">") || (op == ">="))
		return 6;
	else
	if ((op == "==") || (op == "!="))
		return 5;
	else
	if (op == "&")
		return 4;
	else
	if (op == "^")
		return 3;
	else
	if (op == "|")
		return 2;
	else
	if (op == "&&")
		return 1;
	else
	if (op == "||")
		return 0;
	return result;
}

bool hasType(const Ionflux::Template::Token& t, 
    Ionflux::Template::TokenTypeID typeID)
{
    return (t.typeID == typeID);
}

bool isValid(const Ionflux::Template::Token& t)
{
    return (t.typeID != TT_INVALID.typeID);
}

bool isNonEmpty(const Ionflux::Template::Token& t)
{
    return ((t.typeID != TT_INVALID.typeID) 
        && (t.typeID != TT_NONE.typeID));
}

bool hasCharValue(const Ionflux::Template::Token& t, char c)
{
    if (t.value.size() < 1)
        return false;
    return (t.value[0] == c);
}

Ionflux::Template::TokenType createTokenType(
    Ionflux::Template::TokenTypeID typeID, const std::string& validChars, 
    bool invert, int maxChars, bool userType)
{
    TokenType result;
    result.typeID = typeID;
    if (userType)
        result.typeID += TT_ID_USERTYPE;
    result.validChars = validChars;
    result.invert = invert;
    result.maxChars = maxChars;
    return result;
}

const Ionflux::Template::CharTypeMap& getCharTypes()
{
	static CharTypeMap charTypes;
	return charTypes;
}

std::string urlEncode(const std::string& bytes)
{
	const CharTypeMap& charTypes = getCharTypes();
	std::string result;
	unsigned char c;
	TokenType charType;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
		c = bytes[i];
		charType = charTypes.getTokenType(c);
		if ((charType.typeID == TT_NUMBER.typeID)
			|| (charType.typeID == TT_ALPHA.typeID)
			|| (charType.typeID == TT_DEFAULT_SEP.typeID))
			result.append(1, c);
		else
		if (c == ' ')
			result.append(1, '+');
		else
		{
			result.append(1, '%');
			result.append(Ionflux::ObjectBase::toUpper(
			    Ionflux::ObjectBase::makeHex(bytes.substr(i, 1))));
		}
	}
	return result;
}

std::string urlDecode(const std::string& bytes)
{
	std::string result;
	unsigned char c;
	unsigned int i = 0;
	while (i < bytes.size())
	{
		c = bytes[i];
		if (c == '+')
			result.append(1, ' ');
		else
		if ((c == '%') 
			&& ((i + 2) < bytes.size()))
		{
			result.append(Ionflux::ObjectBase::parseHex(
			    bytes.substr(i + 1, 2)));
			i += 2;
		}
		else
			result.append(1, c);
		i++;
	}
	return result;
}

bool readDir(const std::string &dirName, std::vector<std::string> &target, 
	bool prependDirName, bool recursive)
{
	if (dirName.size() == 0)
		return false;
	DIR* currentDir = opendir(dirName.c_str());
	if (currentDir == 0)
		return false;
	target.clear();
	dirent* currentEntry;
	std::string entryName;
	std::string fullPathName;
	std::string prependName = dirName;
	Ionflux::ObjectBase::StringVector currentDirEntries;
	if (dirName[dirName.size() - 1] != DIR_SEPARATOR)
		prependName.append(1, DIR_SEPARATOR);
	while ((currentEntry = readdir(currentDir)) != 0)
	{
		entryName = currentEntry->d_name;
		if ((entryName != ".") && (entryName != ".."))
		{
			fullPathName = prependName + entryName;
			if (prependDirName)
				target.push_back(fullPathName);
			else
				target.push_back(entryName);
			if (recursive)
			{
				currentDirEntries.clear();
				readDir(fullPathName, currentDirEntries, prependDirName, 
					recursive);
				for (unsigned int i = 0; i < currentDirEntries.size(); i++)
					target.push_back(currentDirEntries[i]);
			}
		}
	}
	closedir(currentDir);
	return true;
}

bool getFileList(const std::vector<std::string>& pathList, 
	std::vector<std::string>& target, bool recursive)
{
	File currentFile;
	Ionflux::ObjectBase::StringVector currentDirFiles;
	for (unsigned int i = 0; i < pathList.size(); i++)
	{
		currentFile.setFullName(pathList[i]);
		if (currentFile.isDir())
		{
			/* ----- DEBUG ----- //
			cerr << "[getFileList] DEBUG: "
				"Checking for input files in directory '" 
				<< currentFile.getFullName() << "' ..." << endl;
			// ----- DEBUG ----- */
			readDir(currentFile.getFullName(), currentDirFiles, true, false);
			for (unsigned int k = 0; k < currentDirFiles.size(); k++)
			{
				currentFile.setFullName(currentDirFiles[k]);
				if (recursive 
					&& currentFile.isDir())
				{
					Ionflux::ObjectBase::StringVector currentDirPathList;
					currentDirPathList.push_back(currentDirFiles[k]);
					getFileList(currentDirPathList, target, recursive);
				} else
				if (!currentFile.isDir())
				{
                    /* ----- DEBUG ----- //
                    cerr << "[getFileList] DEBUG: "
                        "Adding file '" << currentDirFiles[k] << "'." 
                        << endl;
                    // ----- DEBUG ----- */
                    target.push_back(currentDirFiles[k]);
				}
			}
		} else
		{
            /* ----- DEBUG ----- //
            cerr << "[getFileList] DEBUG: "
                "Adding file '" << currentFile.getFullName() << "'." 
                << endl;
            // ----- DEBUG ----- */
            target.push_back(currentFile.getFullName());
		}
	}
	return true;
}

std::string getCurrentDir()
{
	int bufferSize = DIR_BUFFER_SIZE;
	char* buf = new char[bufferSize];
	std::string result;
	char* success = 0;
	while (((success = getcwd(buf, bufferSize)) == 0) 
		&& (bufferSize < DIR_BUFFER_SIZE_MAX))
	{
		delete buf;
		bufferSize *= 2;
		buf = new char[bufferSize];
	}
	if (success != 0)
		result = buf;
	delete buf;
	return result;
}

void explodeQuoted(const std::string& bytes, 
    Ionflux::ObjectBase::StringVector& result)
{
	result.clear();
	if (bytes.size() == 0)
		return;
	Tokenizer tok;
	tok.setTokenTypeAnything();
	tok.setInput(bytes);
	tok.setExtractQuoted(true);
	Token currentToken = tok.getNextToken();
	std::string currentElement;
	while (isNonEmpty(currentToken))
	{
		if (hasType(currentToken, TT_WHITESPACE.typeID))
		{
			result.push_back(currentElement);
			currentElement = "";
		} else
			currentElement.append(currentToken.value);
		currentToken = tok.getNextToken();
	}
	result.push_back(currentElement);
}

}

}

/** \file utils.cpp
 * \brief Utility functions (implementation).
 */
