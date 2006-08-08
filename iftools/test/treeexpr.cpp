/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * treeexpr.cpp                  Tree expression parser test.
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
#include "ionflux/TreeEval.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	vector<TreeExprElement> elements;
	TreeExprElement currentElement;
	vector<string> test;
	test.push_back("1");
	test.push_back("1 + 2");
	test.push_back("1 + 2 * 3");
	test.push_back("1 + a * 3 / b");
	test.push_back("1 + foo * 3 / bar");
	test.push_back("1 + foo * 3 / bar.baz");
	test.push_back("1 + -foo * .3 / (bar.baz + -2)");
	test.push_back("foo.bar[baz].moo[\".geez[\\\"45\\\"][1]\"]"
		".(.blupp.(.42).6[1][.foo[2]]).frob.16[12] + foo.bar");
	test.push_back("\"foo\" + 'bar'");
	string elementType;
	for (unsigned int i = 0; i < test.size(); i++)
	{
		cout << "Test #" << (i+1) << ":" << endl
			<< "  Test string: " << test[i] << endl
			<< "  Elements:" << endl;
		TreeEval::parseTreeExpr(test[i], elements);
		for (unsigned int k = 0; k < elements.size(); k++)
		{
			currentElement = elements[k];
			if (currentElement.type == TreeExprElement::TE_INVALID)
				elementType = "TE_INVALID";
			else
			if (currentElement.type == TreeExprElement::TE_VAR)
				elementType = "TE_VAR";
			else
			if (currentElement.type == TreeExprElement::TE_CONST)
				elementType = "TE_CONST";
			else
			if (currentElement.type == TreeExprElement::TE_OP)
				elementType = "TE_OP";
			cout << "    [" << k << "]: type = " << elementType 
				<< ", value = '" << currentElement.value << "'" << endl;
		}
	}
	return 0;
}

/** \file treeexpr.cpp
 * \brief Tree expression parser test.
 */
