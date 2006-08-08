/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * stringfilter.cpp                  String filter test.
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
#include "ionflux/StringFilter.hpp"

using namespace std;
using namespace Ionflux::Tools;

/// String filter test data.
struct FilterTest
{
	/// String filter expression.
	std::string expr;
	/// Test string.
	std::string test;
};

int main(int argc, char* argv[])
{
	StringFilter filter;
	vector<FilterTest> tests;
	FilterTest currentTest;
	currentTest.expr = "erase('green ')|replace('elephants', 'moons')|"
		"trim|uppercase|truncate('20', '...')|center('50', ' ', '*')";
	currentTest.test = "    At least three green elephants orbit around "
		"Jupiter.   ";
	tests.push_back(currentTest);
	currentTest.expr = "move('6', '4', 'front')|move('9', '1', '4')";
	currentTest.test = "06-18-2004";
	tests.push_back(currentTest);
	currentTest.expr = "numformat('2', '.', ',')";
	currentTest.test = "abc 12345abc";
	tests.push_back(currentTest);
	currentTest.expr = "translate('letabgozs', '137489025')|trim";
	currentTest.test = "    At least three green elephants orbit around "
		"Jupiter.   ";
	tests.push_back(currentTest);
	currentTest.expr = "rpad(' ', 20)";
	currentTest.test = "Xenon";
	tests.push_back(currentTest);
	currentTest.expr = "lpad('0', 6)";
	currentTest.test = "123";
	tests.push_back(currentTest);
	currentTest.expr = "trim";
	currentTest.test = "     ";
	tests.push_back(currentTest);
	// Process all test cases.
	string result;
	for (unsigned int i = 0; i < tests.size(); i++)
	{
		cout << "Test #" << (i + 1) << ":" << endl;
		cout << "    Filter expression:" << endl 
			<< "        " << tests[i].expr << endl;
		filter.setFilter(tests[i].expr);
		// filter.printDebugInfo();
		cout << "    Test string:" << endl 
			<< "        '" << tests[i].test << "'" << endl;
		result = filter.apply(tests[i].test);
		cout << "    Result string:" << endl 
			<< "        '" << result << "'" << endl;
	}
	return 0;
}

/** \file stringfilter.cpp
 * \brief String filter test.
 */
