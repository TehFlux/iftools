/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * packtest.cpp               Test for data packing
 * =========================================================================
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

 * ========================================================================== */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "ifobject/serialize.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

// UTF-8 encoder from iftools
std::string uintToUtf8(unsigned int uniChar)
{
	string result;
	if (uniChar < 128U)
		result.append(1, static_cast<unsigned char>(uniChar));
	else
	if (uniChar < 2048U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 6) | 0xc0));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
	if (uniChar < 65536U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 12) | 0xe0));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
	if (uniChar < 2097152U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 18) | 0xf0));
		result.append(1, static_cast<unsigned char>(((uniChar >> 12) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
	if (uniChar < 67108864U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 24) | 0xf8));
		result.append(1, static_cast<unsigned char>(((uniChar >> 18) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 12) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) 
			| 0x80));
	} else
	if (uniChar < 2147483648U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 30) | 0xfc));
		result.append(1, static_cast<unsigned char>(((uniChar >> 24) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 18) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 12) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
		cerr << "[uintToUtf8] WARNING: Character " << uniChar 
			<< " not representable by UTF-8." << endl;
	return result;
}

// Hex functions from iftools.
std::string makeHex(const std::string& inputData)
{
	ostringstream buffer;
	buffer << uppercase << right << setfill('0') << hex;
	for (unsigned int i = 0; i < inputData.size(); i++)
		buffer << setw(2) << int(static_cast<unsigned char>(inputData[i]));
	return buffer.str();
}

std::string makeReadable(const std::string& inputData, 
	const std::string& replacement)
{
	ostringstream buffer;
	unsigned int currentChar;
	for (unsigned int i = 0; i < inputData.size(); i++)
	{
		currentChar = static_cast<unsigned int>(
			static_cast<unsigned char>(inputData[i]));
		if ((currentChar >= 32) && (currentChar <= 126))
		{
			buffer << inputData[i];
		} else
		if (currentChar >= 127)
		{
			buffer << uintToUtf8(currentChar);
		} else
		{
			buffer << replacement;
		}
	}
	return buffer.str();
}

std::string makeNiceHex(const std::string& hex, const std::string& readable, 
	int bytesPerLine, int groupBytes)
{
	ostringstream buffer;
	string paddedHex(hex);
	string paddedReadable(readable);
	if ((paddedHex.size() % 2) != 0)
		paddedHex.append(" ");
	while (((paddedHex.size() / 2) % bytesPerLine) != 0)
		paddedHex.append("  ");
	unsigned int bytes = paddedHex.size() / 2;
	while (paddedReadable.size() < bytes)
		paddedReadable.append(" ");
	int readablePos = 0;
	for (unsigned int i = 0; i < bytes; i++)
	{
		buffer << paddedHex.substr(2 * i, 2) << " ";
		if ((((i + 1) % groupBytes) == 0) && (((i + 1) % bytesPerLine) != 0))
			buffer << " ";
		if (((i + 1) % bytesPerLine) == 0)
		{
			buffer << " " << paddedReadable.substr(readablePos, bytesPerLine) 
				<< "\n";
			readablePos += bytesPerLine;
		}
	}
	return buffer.str();
}

// Default hex output.
std::string makeNiceHex(const std::string& data, int bytesPerLine = 20, 
	int groupBytes = 10)
{
	return makeNiceHex(makeHex(data), makeReadable(data, "."), 
		bytesPerLine, groupBytes);
}

int main(int argc, char* argv[])
{
	cout << "Test for data packing" << endl;
	string buffer;
	// bool
	bool testBool = true;
	cout << "--> bool: " << testBool << endl;
	pack(testBool, buffer, false);
	cout << makeNiceHex(buffer);
	bool unpackedBool = false;
	unpack(buffer, unpackedBool);
	cout << "<-- bool: " << unpackedBool << endl;
	testBool = false;
	cout << "--> bool: " << testBool << endl;
	pack(testBool, buffer, false);
	cout << makeNiceHex(buffer);
	unpackedBool = true;
	unpack(buffer, unpackedBool);
	cout << "<-- bool: " << unpackedBool << endl;
	// int
	int testInt = static_cast<int>(0xfacefade);
	cout << "--> int: " << testInt << endl;
	pack(testInt, buffer, false);
	cout << makeNiceHex(buffer);
	int unpackedInt = 0;
	unpack(buffer, unpackedInt);
	cout << "<-- int: " << unpackedInt << endl;
	// UInt64
	UInt64 testUInt64 = 0xfacefadefadefaceLL;
	cout << "--> UInt64: " << testUInt64 << endl;
	pack(testUInt64, buffer, false);
	cout << makeNiceHex(buffer);
	UInt64 unpackedUInt64 = 0;
	unpack(buffer, unpackedUInt64);
	cout << "<-- UInt64: " << unpackedUInt64 << endl;
	cout << "All tests finished." << endl;
	return 0;
}

/** \file packtest.cpp
 * \brief Test for data packing
 */
