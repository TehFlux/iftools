/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFExampleClass.cpp              Example class (implementation).
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
 * 
 * ========================================================================== */

#include "ifobject/IFExampleClass.hpp"
#include "ifobject/IFSignal.hpp"
#include "ifobject/IFExampleEvent.hpp"

using namespace std;

namespace Ionflux
{

namespace Example
{

// structure constants
const int Blah::SOME_FLAG = -1;

IFExampleClassClassInfo::IFExampleClassClassInfo()
{
	name = "IFExampleClass";
	desc = "Example class";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

// protected member constants
const std::string IFExampleClass::SOME_UID = 42;

// public member constants
const std::string IFExampleClass::MODULE_NAME = "Example";
const unsigned int IFExampleClass::MODULE_VERSION = 1;

// signal type and instance name constants
const SignalType IFExampleClass::SIGNAL_TYPE_EXAMPLE = 
	"void,const Ionflux::Example::IFExampleEvent&";
const std::string IFExampleClass::SIGNAL_NAME_FIRST = "first";
const std::string IFExampleClass::SIGNAL_NAME_SECOND = "second";

// run-time type information instance constants
const IFExampleClassClassInfo IFExampleClass::iFExampleClassClassInfo;
const ClassInfo* IFExampleClass::CLASS_INFO = &IFExampleClass::iFExampleClassClassInfo;

IFExampleClass::IFExampleClass()
: firstWrapper(0), secondWrapper(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}
IFExampleClass::IFExampleClass(double initMiep)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}
IFExampleClass::~IFExampleClass()
{
	clearBlupps();
	clearBlahs();
	// TODO: Nothing ATM. ;-)
}

int IFExampleClass::doStuff(int foo, char bar)
{
	// TODO: Implementation.
	return 0;
}

IFExampleEvent* IFExampleClass::createExampleEvent()
{
	IFExampleEvent* event = new IFExampleEvent();
	if (event == 0)
	{
		std::cerr << "[IFExampleClass::createExampleEvent] ERROR: " 
			"Could not allocate event." << std::endl;
		return 0;
	}
	addLocalRef(event);
	return event;
}

void IFExampleClass::doNothing() const
{
	cout << "Doing nothing." << endl;
}

void IFExampleClass::setSomeValue(int newSomeValue)
{
	someValue = newSomeValue;
}

int IFExampleClass::getSomeValue() const
{
	return someValue;
}

void IFExampleClass::setSomeText(const std::string& newSomeText)
{
	someText = newSomeText;
}

std::string IFExampleClass::getSomeText() const
{
	return someText;
}

double IFExampleClass::getRoProp() const
{
	return roProp;
}

void IFExampleClass::setSpecialBlah(Blah* newSpecialBlah)
{
	specialBlah = newSpecialBlah;
}

Blah* IFExampleClass::getSpecialBlah() const
{
	return specialBlah;
}

unsigned int IFExampleClass::getNumBlupps() const
{
	return blupps.size();
}

Blupp* IFExampleClass::getBlupp(unsigned int elementIndex) const
{
	if (elementIndex < blupps.size())
		return blupps[elementIndex];
	return 0;
}

std::vector<Blupp*>& IFExampleClass::getBlupps()
{
	return blupps;
}

void IFExampleClass::addBlupp(Blupp* addElement)
{
	blupps.push_back(addElement);
}

void IFExampleClass::removeBlupp(Blupp* removeElement)
{
	bool found = false;
	Blupp* currentBlupp = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < blupps.size()))
	{
		currentBlupp = blupps[i];
		if (currentBlupp == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		blupps.erase(blupps.begin() + i);
	}
}

void IFExampleClass::clearBlupps()
{
	blupps.clear();
}

unsigned int IFExampleClass::getNumBlahs() const
{
	return blahs.size();
}

Blah* IFExampleClass::getBlah(const std::string& elementKey) const
{
	std::map<std::string, Blah*>::const_iterator i = blahs.find(elementKey);
	if (i != blahs.end())
		return (*i).second;
	return 0;
}

std::map<std::string, Blah*>& IFExampleClass::getBlahs()
{
	return blahs;
}

void IFExampleClass::addBlah(const std::string& elementKey, Blah* 
addElement)
{
	Blah* theBlah = getBlah(elementKey);
	if (theBlah != 0)
		return;
	blahs[elementKey] = addElement;
}

void IFExampleClass::removeBlah(const std::string& elementKey)
{
	std::map<std::string, Blah*>::iterator i = blahs.find(elementKey);
	if (i != blahs.end())
	{
		blahs.erase(i);
	}
}

void IFExampleClass::clearBlahs()
{
	blahs.clear();
}

IFExampleSignal& IFExampleClass::getSignalFirst()
{
	return signalFirst;
}

Ionflux::Stuff::IFSignal* IFExampleClass::getSignalFirstWrapper()
{
	if (signalFirstWrapper == 0)
	{
		signalFirstWrapper = new Ionflux::Stuff::IFSignal(
			&signalFirst, SIGNAL_TYPE_EXAMPLE, 
			SIGNAL_NAME_FIRST);
		if (signalFirstWrapper == 0)
			std::cerr << "[IFExampleClass::getSignalFirstWrapper] ERROR: " 
				"Could not allocate signal wrapper." << std::endl;
		addLocalRef(signalFirstWrapper);
	}
	return signalFirstWrapper;
}

IFExampleSignal& IFExampleClass::getSignalSecond()
{
	return signalSecond;
}

Ionflux::Stuff::IFSignal* IFExampleClass::getSignalSecondWrapper()
{
	if (signalSecondWrapper == 0)
	{
		signalSecondWrapper = new Ionflux::Stuff::IFSignal(
			&signalSecond, SIGNAL_TYPE_EXAMPLE, 
			SIGNAL_NAME_SECOND);
		if (signalSecondWrapper == 0)
			std::cerr << "[IFExampleClass::getSignalSecondWrapper] ERROR: " 
				"Could not allocate signal wrapper." << std::endl;
		addLocalRef(signalSecondWrapper);
	}
	return signalSecondWrapper;
}

}

}

/** \file IFExampleClass.cpp
 * \brief Example class implementation.
 */
