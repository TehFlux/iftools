/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * nodeindex.cpp                  Node index test.
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
#include "ionflux/Node.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	MTRand *randomizer = new MTRand(time(0));
	unsigned int n = 10000;
	if (argc > 1)
		n = strtol(argv[1], 0, 10);
	unsigned int nameLength = 10;
	vector<string> names;
	string currentName;
	clock_t startTicks;
	clock_t endTicks;
	double elapsedSecs;
	cout << "Generating " << n << " random node names of length " 
		<< nameLength << "...";
	startTicks = clock();
	for (unsigned int i = 0; i < n; i++)
	{
		getRandomIdentifier(currentName, nameLength, randomizer);
		names.push_back(currentName);
	}
	endTicks = clock();
	elapsedSecs = static_cast<double>(endTicks - startTicks) / CLOCKS_PER_SEC;
	cout << " done. (" << elapsedSecs << " secs)" << endl;
	Node normal;
	Node indexed;
	normal.setAutoCreate(true);
	normal.setIndexMode(Node::INDEX_MODE_NONE);
	indexed.setAutoCreate(true);
	indexed.setIndexMode(Node::INDEX_MODE_NODE);
	cout << "Creating child nodes for normal node ...";
	Node *currentChild;
	startTicks = clock();
	for (unsigned int i = 0; i < n; i++)
	{
		currentChild = normal.addChild();
		currentChild->setID(i);
		currentChild->setName(names[i]);
	}
	endTicks = clock();
	elapsedSecs = static_cast<double>(endTicks - startTicks) / CLOCKS_PER_SEC;
	cout << " done. (" << elapsedSecs << " secs)" << endl;
	cout << "Creating child nodes for indexed node ...";
	startTicks = clock();
	for (unsigned int i = 0; i < n; i++)
	{
		currentChild = indexed.addChild();
		currentChild->setID(i);
		currentChild->setName(names[i]);
	}
	endTicks = clock();
	elapsedSecs = static_cast<double>(endTicks - startTicks) / CLOCKS_PER_SEC;
	cout << " done. (" << elapsedSecs << " secs)" << endl;
	double normalTime;
	double indexedTime;
	cout << "Accessing " << n << " child nodes of normal node by name "
		"(this may take a while, please wait)...";
	cout.flush();
	startTicks = clock();
	for (unsigned int i = 0; i < n; i++)
		currentChild = normal.findChild(names[i], false);
	endTicks = clock();
	normalTime = static_cast<double>(endTicks - startTicks) / CLOCKS_PER_SEC;
	cout << " done. (" << normalTime << " secs)" << endl;
	cout << "Accessing " << n << " child nodes of indexed node by name...";
	cout.flush();
	startTicks = clock();
	for (unsigned int i = 0; i < n; i++)
		currentChild = indexed.findChild(names[i], false);
	endTicks = clock();
	indexedTime = static_cast<double>(endTicks - startTicks) / CLOCKS_PER_SEC;
	cout << " done. (" << indexedTime << " secs)" << endl;
	cout << "Result of access by name:" << endl
		<< "  Normal:  " << (n / normalTime) << " accesses/sec" << endl
		<< "  Indexed: " << (n / indexedTime) << " accesses/sec" << endl;
	cout << "Accessing " << n << " child nodes of normal node by ID "
		"(this may take a while, please wait)...";
	cout.flush();
	startTicks = clock();
	for (unsigned int i = 0; i < n; i++)
		currentChild = normal.findChild(i, false);
	endTicks = clock();
	normalTime = static_cast<double>(endTicks - startTicks) / CLOCKS_PER_SEC;
	cout << " done. (" << normalTime << " secs)" << endl;
	cout << "Accessing " << n << " child nodes of indexed node by ID...";
	cout.flush();
	startTicks = clock();
	for (unsigned int i = 0; i < n; i++)
		currentChild = indexed.findChild(i, false);
	endTicks = clock();
	indexedTime = static_cast<double>(endTicks - startTicks) / CLOCKS_PER_SEC;
	cout << " done. (" << indexedTime << " secs)" << endl;
	cout << "Result of access by ID:" << endl
		<< "  Normal:  " << (n / normalTime) << " accesses/sec" << endl
		<< "  Indexed: " << (n / indexedTime) << " accesses/sec" << endl;
	delete randomizer;
	return 0;
}

/** \file nodeindex.cpp
 * \brief Node index test.
 */
