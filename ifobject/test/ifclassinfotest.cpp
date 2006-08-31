/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifclassinfotest.cpp               Test for IFClassInfo
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
#include "ifobject/IFClassInfo.hpp"

using namespace std;

/* This is the simple class information hierarchy created for this example:

      A
	 / \
	B   C
	   / \
	  D   E
*/

// Class info for class A
class AClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		AClassInfo()
		{
			name = "A";
			desc = "Class A";
		}
		
		virtual ~AClassInfo() { }
};

// Global class iformation instance for class A
AClassInfo A_CLASS_INFO;

// Class info for class B
class BClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		BClassInfo()
		{
			name = "B";
			desc = "Class B";
			baseClassInfo.push_back(&A_CLASS_INFO);
		}
		
		virtual ~BClassInfo()
		{ }
};

// Global class iformation instance for class B
BClassInfo B_CLASS_INFO;

// Class info for class C
class CClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		CClassInfo()
		{
			name = "C";
			desc = "Class C";
			baseClassInfo.push_back(&A_CLASS_INFO);
		}
		
		virtual ~CClassInfo()
		{ }
};

// Global class iformation instance for class C
CClassInfo C_CLASS_INFO;

// Class info for class D
class DClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		DClassInfo()
		{
			name = "D";
			desc = "Class D";
			baseClassInfo.push_back(&C_CLASS_INFO);
		}
		
		virtual ~DClassInfo()
		{ }
};

// Global class information instance for class D
DClassInfo D_CLASS_INFO;

// Class info for class E
class EClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		EClassInfo()
		{
			name = "E";
			desc = "Class E";
			baseClassInfo.push_back(&C_CLASS_INFO);
		}
		
		virtual ~EClassInfo()
		{ }
};

// Global class information instance for class E
EClassInfo E_CLASS_INFO;

void printClassInfo(const Ionflux::ObjectBase::IFClassInfo* classInfo,
	Ionflux::ObjectBase::IFClassInfoVector* otherClassInfo)
{
	if (classInfo == 0)
	{
		cerr << "[printClassInfo] ERROR: Class info is null." << endl;
		return;
	}
	if (otherClassInfo == 0)
	{
		cerr << "[printClassInfo] ERROR: Other class info is null." << endl;
		return;
	}
	cout << "Class information for class '" << classInfo->getName() << "':" 
		<< endl
		<< "  description: '" << classInfo->getDesc() << "'" << endl
		<< "  inheritance:" << endl
		<< "    base classes: ";
	unsigned int numBaseClasses = classInfo->getNumBaseClasses();
	Ionflux::ObjectBase::IFClassInfo* currentInfo = 0;
	for (unsigned int k = 0; k < numBaseClasses; k++)
	{
		currentInfo = classInfo->getBaseClassInfo(k);
		if (currentInfo != 0)
		{
			cout << "'" << currentInfo->getName() << "'";
			if (k != (numBaseClasses - 1))
				cout << ", ";
		}
	}
	cout << endl;
	Ionflux::ObjectBase::IFClassInfoVector::const_iterator i;
	for (i = otherClassInfo->begin(); i != otherClassInfo->end(); i++)
	{
		currentInfo = *i;
		if (currentInfo != 0)
		{
			cout << "  class '" << currentInfo->getName() << "':" << endl
				<< "    base: ";
			if (classInfo->isDerivedFrom(currentInfo, false))
				cout << "(direct)";
			else
			if (classInfo->isDerivedFrom(currentInfo))
				cout << "(indirect)";
			else
				cout << "(no)";
			cout << ", derived: ";
			if (classInfo->isBaseOf(currentInfo, false))
				cout << "(direct)";
			else
			if (classInfo->isBaseOf(currentInfo))
				cout << "(indirect)";
			else
				cout << "(no)";
			cout << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	cout << "Test for IFClassInfo" << endl;
	cout << "Populating class info vector... ";
	Ionflux::ObjectBase::IFClassInfoVector classInfo;
	classInfo.push_back(&A_CLASS_INFO);
	classInfo.push_back(&B_CLASS_INFO);
	classInfo.push_back(&C_CLASS_INFO);
	classInfo.push_back(&D_CLASS_INFO);
	classInfo.push_back(&E_CLASS_INFO);
	cout << "done." << endl;
	Ionflux::ObjectBase::IFClassInfoVector::const_iterator i;
	for (i = classInfo.begin(); i != classInfo.end(); i++)
		printClassInfo(*i, &classInfo);
	cout << "All tests finished." << endl;
	return 0;
}

/** \file ifclassinfotest.cpp
 * \brief Test for IFClassInfo
 */
