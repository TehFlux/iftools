/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utf8.cpp                 UTF-8 encoding/decoding.
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

#include <iostream>
#include <sstream>
#include "ifobject/utf8.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/log.hpp"
#include "ifobject/IFError.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

std::string uniCharToUTF8(IFUniChar uniChar)
{
	std::string result;
	if (uniChar < 128U)
		result.append(1, static_cast<unsigned char>(uniChar));
	else if (uniChar < 2048U) 
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 6) | 0xc0));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else if (uniChar < 65536U)
	{
		result.append(1, static_cast<unsigned char>(
			(uniChar >> 12) | 0xe0));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 6) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			(uniChar & 0x3f) | 0x80));
	} else if (uniChar < 2097152U)
	{
		result.append(1, static_cast<unsigned char>(
			(uniChar >> 18) | 0xf0));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 12) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 6) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			(uniChar & 0x3f) | 0x80));
	} else if (uniChar < 67108864U)
	{
		result.append(1, static_cast<unsigned char>(
			(uniChar >> 24) | 0xf8));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 18) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 12) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 6) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			(uniChar & 0x3f) | 0x80)); 
	} else if (uniChar < 2147483648U)
	{ 		
		result.append(1, static_cast<unsigned char>(
			(uniChar >> 30) | 0xfc));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 24) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 18) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 12) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			((uniChar >> 6) & 0x3f) | 0x80));
		result.append(1, static_cast<unsigned char>(
			(uniChar & 0x3f) | 0x80));
	} else
	{
	    std::ostringstream status;
	    status << "[uniCharToUTF8] " 
	        << "Character not representable by UTF-8 (" << uniChar 
	        << ").";
	    throw IFError(status.str());
	}
	return result;
}

bool utf8ToUniChar(const std::string& bytes, IFUniChar& target)
{
	unsigned int size = bytes.size();
	target = 0;
	bool result = true;
	if (size == 1)
	{
		if ((bytes[0] >> 7) != 0)
		    throw IFError("[utf8ToUniChar] Invalid single-byte character.");
        else
			target = bytes[0];
	} else
	{
		unsigned char byte = bytes[0];
		target = ((byte & (0xff >> (size + 1))) << (6 * (size - 1)));
		unsigned int i = 1;
		while (result && (i < size))
		{
			byte = bytes[i];
			if ((byte >> 6) != 2)
			{
				ostringstream state;
				state << "[utf8ToUniChar] Invalid byte (" 
					<< static_cast<unsigned int>(byte) 
					<< ") in UTF-8 sequence at position " << i << ".";
                throw IFError(state.str());
			} else
				target |= ((byte & 0x3f) << (6 * (size - 1 - i)));
			i++;
		}
	}
	return result;
}

void uniCharToUTF8(const std::vector<IFUniChar>& uniChars, 
	std::string& target)
{
	target = "";
	for (unsigned int i = 0; i < uniChars.size(); i++)
		target.append(uniCharToUTF8(uniChars[i]));
}

unsigned int utf8GetSize(unsigned char byte)
{ 
	if (byte < 128)
		return 1;
	else if ((byte & 0xe0) == 0xc0) 
		return 2;
	else if ((byte & 0xf0) == 0xe0) 
		return 3;
	else if ((byte & 0xf8) == 0xf0)
		return 4;
	else if ((byte & 0xfc) == 0xf8)
		return 5;
	else if ((byte & 0xfe) == 0xfc)
		return 6;
	throw IFError("[utf8GetSize] Invalid character size."); 
	return 0;
}

bool utf8ToUniChar(const std::string& bytes, 
	std::vector<IFUniChar>& target)
{ 
	unsigned int size = bytes.size(); 
	unsigned int i = 0;
	unsigned int charSize = 0; 
	IFUniChar currentChar = 0; 
	bool result = true; 
	target.clear();
	while (result && (i < size)) 
	{
		charSize = utf8GetSize(bytes[i]);
		if ((charSize > 0) 
			&& ((i + charSize) <= size) 
			&& utf8ToUniChar(bytes.substr(i, charSize), currentChar))
			i += charSize;
		else
		{
			ostringstream state;
			state << "Could not convert UTF-8 character " "(size = " 
				<< charSize << ", position = " << i << ").";
			throw IFError(state.str());
		}
		if (result)
			target.push_back(currentChar);
	}
	return result;
}

unsigned int utf8GetSize(const std::string& bytes)
{
	unsigned int size = bytes.size();
	unsigned int i = 0;
	unsigned int charLen = 0;
	unsigned int result = 0;
	bool error = false;
	while (!error 
		&& (i < size))
	{
		charLen = utf8GetSize(bytes[i]);
		if (charLen > 0)
		{
			result++;
			i += charLen;
		} else
			error = true;
	}
	if (error)
		return 0;
	return result; 
}

void utf8MakeReadable(const std::string& inputData, 
	Ionflux::ObjectBase::UniCharVector& target, 
	Ionflux::ObjectBase::IFUniChar replacement)
{
    std::ostringstream buffer;
	unsigned char currentChar;
	for (unsigned int i = 0; i < inputData.size(); i++)
	{
		currentChar = static_cast<unsigned char>(inputData[i]);
		if (((currentChar >= 32) && (currentChar <= 126)) 
		    || (currentChar >= 161))
		{
			target.push_back(currentChar);
		} else
		{
			target.push_back(replacement);
		}
	}
}

std::string utf8MakeNiceHex(const std::string& hex, 
    const Ionflux::ObjectBase::UniCharVector& readable, 
    int bytesPerLine, int groupBytes, bool showPos)
{
    std::ostringstream buffer;
	string paddedHex(hex);
	UniCharVector paddedReadable(readable);
	if ((paddedHex.size() % 2) != 0)
		paddedHex.append(" ");
	while (((paddedHex.size() / 2) % bytesPerLine) != 0)
		paddedHex.append("  ");
	unsigned int bytes = paddedHex.size() / 2;
	while (paddedReadable.size() < bytes)
		paddedReadable.push_back(32);
	int readablePos = 0;
	int lineNum = 0;
	for (unsigned int i = 0; i < bytes; i++)
	{
		if (((i % bytesPerLine) == 0) 
		    && (lineNum > 0))
		{
		    buffer << "\n";
		}
		buffer << paddedHex.substr(2 * i, 2) << " ";
		if ((((i + 1) % groupBytes) == 0) 
		    && (((i + 1) % bytesPerLine) != 0))
			buffer << " ";
		if (((i + 1) % bytesPerLine) == 0)
		{
			buffer << " ";
			for (int k = 0; k < bytesPerLine; k++)
			    buffer << uniCharToUTF8(paddedReadable[readablePos + k]);
			if (showPos)
			    buffer << "  " << (i + 1);
			readablePos += bytesPerLine;
			lineNum++;
		}
	}
	return buffer.str();
}

std::string utf8MakeNiceHexForData(const std::string& data, 
    int bytesPerLine, int groupBytes, bool showPos)
{
    UniCharVector v0;
    utf8MakeReadable(data, v0);
	return utf8MakeNiceHex(makeHex(data), v0, bytesPerLine, groupBytes, 
	    showPos);
}

}

}

/** \file utf8.cpp
 * \brief UTF-8 encoding/decoding (implementation).
 */
