/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifobjecttest.cpp               Test for IFObject
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
#include "ifobject/utf8.hpp"
#include "ifobject/IFObject.hpp"
#include "ifobject/IFObjectEvent.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

// Event handler: ID number changed.
bool objectIDNumChanged(const IFObjectEvent& event)
{
	cout << "[objectIDNumChanged] ID num changed:" << endl
		<< "    source   = " << event.getSource()->getString() << endl
		<< "    oldIDNum = " << event.getOldIDNum() << endl
		<< "    newIDNum = " << event.getNewIDNum() << endl;
	return true;
}

// Event handler: ID changed.
bool objectIDChanged(const IFObjectEvent& event)
{
	cout << "[objectIDChanged] ID changed:" << endl
		<< "    source   = " << event.getSource()->getString() << endl
		<< "    oldID = " << event.getOldID() << endl
		<< "    newID = " << event.getNewID() << endl;
	return true;
}

// Default hex output.
std::string makeNiceHex(const std::string& data, int bytesPerLine = 20, 
	int groupBytes = 10)
{
	return utf8MakeNiceHexForData(makeHex(data), bytesPerLine, groupBytes);
}

int main(int argc, char* argv[])
{
	cout << "Test for IFObject" << endl;
	cout << "Creating objects... ";
	IFObjectVector objects;
	objects.push_back(IFObject::create());
	objects.push_back(IFObject::create());
	cout << "done." << endl;
	cout << "Connecting signal handlers... ";
	for (IFObjectVector::iterator i = objects.begin(); 
		i != objects.end(); i++)
	{
		(*i)->getSignalObjectIDNumChanged().connect(
			sigc::ptr_fun(objectIDNumChanged));
		(*i)->getSignalObjectIDChanged().connect(
			sigc::ptr_fun(objectIDChanged));
	}
	cout << "done." << endl;
	cout << "Assigning IDs... " << endl;
	unsigned int idCount = 0;
	ostringstream state;
	for (IFObjectVector::iterator i = objects.begin(); 
		i != objects.end(); i++)
	{
		(*i)->setIDNum(idCount);
		state.str("");
		state << "object" << idCount;
		(*i)->setID(state.str());
		idCount++;
	}
	cout << "Done." << endl;
	// test operations
	cout << "Testing operation 'log'... " << endl;
	IFObjectVector opParams;
	opParams.push_back(objects[1]);
	objects[0]->doOp("log", &opParams);
	cout << "Done." << endl;
	// test serialization
	cout << "Testing serialization... " << endl;
	for (IFObjectVector::iterator i = objects.begin(); 
		i != objects.end(); i++)
	{
		string buffer;
		(*i)->serialize(buffer);
		cout << "---> " << (*i)->getString() << endl;
		cout << makeNiceHex(buffer);
		IFObject restoredObject;
		restoredObject.deserialize(buffer);
		cout << "<--- " << restoredObject.getString() << endl;
	}
	cout << "Done." << endl;
	// test local references
	cout << "Adding local references... " << endl;
	cout << "    -> object[1] will be managed by object[0]" << endl;
	objects[0]->addLocalRef(objects[1]);
	objects[1] = 0;
	cout << "Done." << endl;
	cout << "Destroying objects... ";
	for (IFObjectVector::iterator i = objects.begin(); 
		i != objects.end(); i++)
	{
		if (*i != 0)
			delete *i;
		*i = 0;
	}
	cout << "done." << endl;
	cout << "(Use valgrind to check whether all objects have been "
		"destroyed.)" << endl;
	cout << "All tests finished." << endl;
	return 0;
}

/** \file ifobjecttest.cpp
 * \brief Test for IFObject
 */
