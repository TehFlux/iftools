/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * pack.cpp                  Data type packing test.
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
#include "ionflux/tools.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	int intData = 12345;
	double doubleData = 6.6260755;
	bool boolData = true;
	string boolText;
	cout << "Packing int:" << endl
		<< "    value:    " << intData << endl
		<< "    packed:   0x" << makeHex(packInt(intData)) << endl
		<< "    unpacked: " << unpackInt(packInt(intData)) << endl;
	cout << "Packing double:" << endl
		<< "    value:    " << doubleData << endl
		<< "    packed:   0x" << makeHex(packDouble(doubleData)) << endl
		<< "    unpacked: " << unpackDouble(packDouble(doubleData)) << endl;
	cout << "Packing bool:" << endl
		<< "    value:    " << boolData << endl
		<< "    packed:   0x" << makeHex(packBool(boolData)) << endl
		<< "    unpacked: " << unpackBool(packBool(boolData)) << endl;
	return 0;
}

/** \file pack.cpp
 * \brief Data type packing test.
 */
