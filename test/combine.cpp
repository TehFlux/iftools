/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * combine.cpp                  Combine test.
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
#include "ionflux/ConfigTree.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	string defaultConfigFile = "./test/conf/combine.conf";
	string configFile;
	if (argc >= 2)
		configFile = argv[1];
	else
		configFile = defaultConfigFile;
	ConfigTree config;
	config.readConfig(configFile);
	Node &root = *config.getRoot();
	Node combinations;
	Node *currentNode = 0;
	cout << "Data items:" << endl;
	for (unsigned int i = 0; i < root.getNumChildren(); i++)
	{
		currentNode = root.getChild(i);
		if (currentNode == 0)
		{
			cerr << "ERROR: Current node is null." << endl;
			return -1;
		}
		cout << (i + 1) << ") " << currentNode->getName() << endl;
		for (unsigned int k = 0; k < currentNode->getNumData(); k++)
			cout << "  " << (k + 1) << ") " << currentNode->getData(k) << endl;
	}
	bool result = root.combine(0, root.getNumChildren() - 1, combinations);
	if (!result)
	{
		cerr << "ERROR: combine() failed." << endl;
		return -1;
	}
	cout << "Combinations:" << endl;
	for (unsigned int i = 0; i < combinations.getNumChildren(); i++)
	{
		currentNode = combinations.getChild(i);
		if (currentNode == 0)
		{
			cerr << "ERROR: Current node is null." << endl;
			return -1;
		}
		cout << (i + 1) << ") ";
		for (unsigned k = 0; k < currentNode->getNumData(); k++)
		{
			if (k > 0)
				cout << ", ";
			cout << currentNode->getData(k);
		}
		cout << endl;
	}
	return 0;
}

/** \file combine.cpp
 * \brief Combine test.
 */
