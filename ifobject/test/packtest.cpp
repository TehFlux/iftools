/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2014 Joern P. Meier
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
#include "ifobject/utils.hpp"
#include "ifobject/utf8.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

// Default hex output.
std::string makeNiceHex0(const std::string& data, int bytesPerLine = 20, 
	int groupBytes = 10)
{
    UniCharVector v0;
    utf8MakeReadable(data, v0);
	return utf8MakeNiceHex(makeHex(data), v0, bytesPerLine, groupBytes);
}

int main(int argc, char* argv[])
{
	cout << "Test for data packing" << endl;
	string buffer;
	// bool
	bool testBool = true;
	cout << "--> bool: " << testBool << endl;
	pack(testBool, buffer, false);
	cout << makeNiceHex0(buffer);
	bool unpackedBool = false;
	unpack(buffer, unpackedBool);
	cout << "<-- bool: " << unpackedBool << endl;
	testBool = false;
	cout << "--> bool: " << testBool << endl;
	pack(testBool, buffer, false);
	cout << makeNiceHex0(buffer);
	unpackedBool = true;
	unpack(buffer, unpackedBool);
	cout << "<-- bool: " << unpackedBool << endl;
	// int
	int testInt = static_cast<int>(0xfacefade);
	cout << "--> int: " << testInt << endl;
	pack(testInt, buffer, false);
	cout << makeNiceHex0(buffer);
	int unpackedInt = 0;
	unpack(buffer, unpackedInt);
	cout << "<-- int: " << unpackedInt << endl;
	// double
	double testDouble = 1.5231;
	cout << "--> double: " << testDouble << endl;
	pack(testDouble, buffer, false);
	cout << makeNiceHex0(buffer);
	double unpackedDouble = 0;
	unpack(buffer, unpackedDouble);
	cout << "<-- double: " << unpackedDouble << endl;
	// UInt16
	UInt16 testUInt16 = 0xface;
	cout << "--> UInt16: " << testUInt16 << endl;
	pack(testUInt16, buffer, false);
	cout << makeNiceHex0(buffer);
	UInt16 unpackedUInt16 = 0;
	unpack(buffer, unpackedUInt16);
	cout << "<-- UInt16: " << unpackedUInt16 << endl;
	// UInt64
	UInt64 testUInt64 = 0xfacefadefadefaceLL;
	cout << "--> UInt64: " << testUInt64 << endl;
	pack(testUInt64, buffer, false);
	cout << makeNiceHex0(buffer);
	UInt64 unpackedUInt64 = 0;
	unpack(buffer, unpackedUInt64);
	cout << "<-- UInt64: " << unpackedUInt64 << endl;
	cout << "All tests finished." << endl;
	return 0;
}

/** \file packtest.cpp
 * \brief Test for data packing
 */
