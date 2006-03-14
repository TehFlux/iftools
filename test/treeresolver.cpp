/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * treeresolver.cpp                  Tree resolver test.
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
#include "ionflux/TreeResolver.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	string treePath = "foo.bar[baz].moo[\".geez[\\\"45\\\"][1]\"]"
		".(.blupp.(.42).6[1][.foo[2]]).frob.16[12][\"A text subscript.\"]";
	vector<NodeReference> nodeRefs;
	cout << "Tree path:" << endl;
	cout << treePath << endl;
	cout << "Parsing tree path... ";
	TreeResolver::parseTreePath(treePath, nodeRefs);
	cout << "done." << endl;
	cout << "Result:" << endl;
	vector<NodeReference>::const_iterator i;
	for (i = nodeRefs.begin(); i != nodeRefs.end(); i++)
	{
		(*i).printDebugInfo();
	}
	return 0;
}

/** \file treeresolver.cpp
 * \brief Tree resolver test.
 */
