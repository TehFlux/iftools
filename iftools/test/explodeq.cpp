/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * explodeq.cpp                  Explode quoted string test.
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
	vector<string> exploded;
	test.push_back("test1");
	test.push_back("test1 test2");
	test.push_back("test1\\ test2");
	test.push_back("test1 test2 \"test3\"");
	test.push_back("test1 test2 \"test3 test4\"");
	test.push_back("test1 test2 \"test3 'test4 test5' test6\" test7");
	test.push_back("test1 test2 \"test3 'test4 test5' test6\" 'test7 test8'");
	test.push_back("test1 \"\" test2");
	test.push_back(" ");
	test.push_back("\\\"");
	for (unsigned int i = 0; i < test.size(); i++)
	{
		cout << "Test #" << (i+1) << ":" << endl
			<< "  Test string: " << test[i] << endl;
		explodeQuoted(test[i], exploded);
		cout << "  Elements:" << endl;
		for (unsigned int k = 0; k < exploded.size(); k++)
			cout << "    [" << k << "]: " << exploded[k] << endl;
	}
	return 0;
}

/** \file explodeq.cpp
 * \brief Explode quoted string test.
 */
