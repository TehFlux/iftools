/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * numcheck.cpp                  Number checking test.
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
#include <vector>
#include "ionflux/tools.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	vector<string> test;
	test.push_back("1");
	test.push_back("123");
	test.push_back("-1");
	test.push_back("-123");
	test.push_back(".1");
	test.push_back(".123");
	test.push_back("-.1");
	test.push_back("-.123");
	test.push_back("1.2");
	test.push_back("12.345");
	test.push_back("-1.2");
	test.push_back("-12.345");
	test.push_back("1e2");
	test.push_back(".1e2");
	test.push_back("1.2e3");
	test.push_back("-.1e2");
	test.push_back("-1.2e3");
	test.push_back("1.12e+3");
	test.push_back("12.34e-5");
	test.push_back(".");
	test.push_back(".e12");
	test.push_back(".e-12");
	test.push_back("1.e-23");
	test.push_back("abcde");
	test.push_back("123abcde");
	test.push_back("abcde123");
	test.push_back("abc123de");
	bool nothing = true;
	for (unsigned int i = 0; i < test.size(); i++)
	{
		cout << "Test #" << (i+1) << ":" << endl
			<< "  Test string: " << test[i] << endl
			<< "  Which is:";
		nothing = true;
		if (isNumber(test[i]))
		{
			cout << " number";
			nothing = false;
		}
		if (isInteger(test[i]))
		{
			cout << " integer";
			nothing = false;
		}
		if (isFloat(test[i]))
		{
			cout << " float";
			nothing = false;
		}
		if (nothing)
			cout << " string";
		cout << endl;
	}
	return 0;
}

/** \file numcheck.cpp
 * \brief Number checking test.
 */
