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
#include "ifobject/IFMutex.hpp"
#include "ifobject/IFGuard.hpp"
#include "ifobject/IFLogMessage.hpp"
#include "ifobject/IFSignal.hpp"
#include "ifobject/IFExampleEvent.hpp"
#include <sstream>

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

// structure constants
const int Blah::SOME_FLAG = -1;

// operation info records
Ionflux::ObjectBase::IFOpInfo IFExampleClassClassInfo::OP_INFO_DOSTUFFWITHOBJECTOP;

IFExampleClassClassInfo::IFExampleClassClassInfo()
{
	name = "IFExampleClass";
	desc = "Example class";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
	Ionflux::ObjectBase::IFOpParamInfo currentParam;
	Ionflux::ObjectBase::IFOpResultInfo currentResult;
	OP_INFO_DOSTUFFWITHOBJECTOP.name = "doStuffWithObjectOp";
	currentParam.type = Ionflux::ObjectBase::IFObject::CLASS_INFO;
	currentParam.name = "victim";
	currentParam.desc = "object";
	currentParam.optional = false;
	currentParam.defaultValue = false;
	OP_INFO_DOSTUFFWITHOBJECTOP.paramInfo.push_back(currentParam);
	currentResult.type = Ionflux::ObjectBase::IFObject::CLASS_INFO;
	currentResult.desc = "result";
	OP_INFO_DOSTUFFWITHOBJECTOP.resultInfo.push_back(currentResult);
	opInfo = new IFOpNameInfoMap();
	(*opInfo)[OP_INFO_DOSTUFFWITHOBJECTOP.name] = &OP_INFO_DOSTUFFWITHOBJECTOP;
}

IFExampleClassClassInfo::~IFExampleClassClassInfo()
{
	delete opInfo;
}

// protected member constants
const std::string IFExampleClass::SOME_UID = "42";

// public member constants
const std::string IFExampleClass::MODULE_NAME = "Example";
const unsigned int IFExampleClass::MODULE_VERSION = 1;

// signal type and instance name constants
const Ionflux::ObjectBase::IFSignalType IFExampleClass::SIGNAL_TYPE_EXAMPLE = 
	"void,const Ionflux::Example::IFExampleEvent&";
const std::string IFExampleClass::SIGNAL_NAME_FIRST = "first";
const std::string IFExampleClass::SIGNAL_NAME_SECOND = "second";

// run-time type information instance constants
const IFExampleClassClassInfo IFExampleClass::iFExampleClassClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFExampleClass::CLASS_INFO = &IFExampleClass::iFExampleClassClassInfo;

IFExampleClass::IFExampleClass()
: signalFirstWrapper(0), signalSecondWrapper(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// NOTE: The following line is required for guards to work.
	setGuardEnabled(true);
	// TODO: Nothing ATM. ;-)
}

IFExampleClass::IFExampleClass(double initMiep)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// NOTE: The following line is required for guards to work.
	setGuardEnabled(true);
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
	IFGuard functionGuard(guardMutex);
	// TODO: Implementation.
	return 0;
}

Ionflux::ObjectBase::IFObject* 
IFExampleClass::doStuffWithObjectImpl(Ionflux::ObjectBase::IFObject* 
victim)
{
	IFGuard functionGuard(guardMutex);
	// TODO: Implementation.
	return 0;
}

bool IFExampleClass::opDoStuffWithObjectOp(Ionflux::ObjectBase::IFObject* 
victim, Ionflux::ObjectBase::IFObjectVector* target)
{
	return doStuffWithObjectImpl(victim);
}

bool IFExampleClass::opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
	const Ionflux::ObjectBase::IFObjectVector* params, 
	Ionflux::ObjectBase::IFObjectVector* target)
{
	const IFOpInfo* opInfo = theClass->getOpInfo(opName);
	if (opInfo == 0)
	{
		// Try one of the base classes.
		ostringstream state;
		state << "Operation not supported: '" << opName << "'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "opDispatch"));
		return false;
	}
	// Check parameters.
	IFObjectVector checkedParams;
	unsigned int numParams = opInfo->paramInfo.size();
	unsigned int i = 0;
	bool paramsOK = true;
	while ((i < numParams)
		&& paramsOK)
	{
		const IFOpParamInfo* paramInfo = &(opInfo->paramInfo[i]);
		if ((params != 0) 
			&& (i < params->size()))
		{
			/* Parameter is defined.
			   Check parameter type. */
			if ((paramInfo->type == 0)
				|| (paramInfo->type == (*params)[i]->getClass())
				|| ((*params)[i]->getClass()->isDerivedFrom(paramInfo->type)))
				checkedParams.push_back((*params)[i]);
			else
			{
				ostringstream state;
				state << "Parameter " << i << " for operation '"
					<< opName << "' is of wrong type (type is " 
					<< (*params)[i]->getClassName() << ", expected " 
					<< paramInfo->type->getName() << ").";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));
				return false;
			}
		} else
		{
			// Parameter is missing.
			if (!paramInfo->optional)
			{
				ostringstream state;
				state << "Required parameter " << i << " for operation '"
					<< opName << "' is missing.";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));
				return false;
			}
			checkedParams.push_back(paramInfo->defaultValue);
		}
		i++;
	}
	// Call the appropriate operation proxy.
	if (opName == "doStuffWithObjectOp")
		return opDoStuffWithObjectOp(
			checkedParams[0], 
			target);
	ostringstream state;
	state << "Failed to dispatch operation '"
		<< opName << "' for some unknown reason (this should not happen).";
	log(IFLogMessage(state.str(), VL_ERROR, 
		this, "opDispatch"));
	return false;
}

bool IFExampleClass::opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
	const Ionflux::ObjectBase::IFObjectVector* params, 
	Ionflux::ObjectBase::IFObjectVector* target) const
{
	const IFOpInfo* opInfo = theClass->getOpInfo(opName);
	if (opInfo == 0)
	{
		// Try one of the base classes.
		ostringstream state;
		state << "Operation not supported: '" << opName << "'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "opDispatch"));
		return false;
	}
	// Check parameters.
	IFObjectVector checkedParams;
	unsigned int numParams = opInfo->paramInfo.size();
	unsigned int i = 0;
	bool paramsOK = true;
	while ((i < numParams)
		&& paramsOK)
	{
		const IFOpParamInfo* paramInfo = &(opInfo->paramInfo[i]);
		if ((params != 0) 
			&& (i < params->size()))
		{
			/* Parameter is defined.
			   Check parameter type. */
			if ((paramInfo->type == 0)
				|| (paramInfo->type == (*params)[i]->getClass())
				|| ((*params)[i]->getClass()->isDerivedFrom(paramInfo->type)))
				checkedParams.push_back((*params)[i]);
			else
			{
				ostringstream state;
				state << "Parameter " << i << " for operation '"
					<< opName << "' is of wrong type (type is " 
					<< (*params)[i]->getClassName() << ", expected " 
					<< paramInfo->type->getName() << ").";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));
				return false;
			}
		} else
		{
			// Parameter is missing.
			if (!paramInfo->optional)
			{
				ostringstream state;
				state << "Required parameter " << i << " for operation '"
					<< opName << "' is missing.";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));
				return false;
			}
			checkedParams.push_back(paramInfo->defaultValue);
		}
		i++;
	}
	// Call the appropriate operation proxy.
	ostringstream state;
	state << "Failed to dispatch operation '"
		<< opName << "' (this is probably because there is no const "
		"implementation available for the operation, but the object on "
		"which the operation has been called is const).";
	log(IFLogMessage(state.str(), VL_ERROR, 
		this, "opDispatch"));
	return false;
}

IFExampleEvent* IFExampleClass::createExampleEvent()
{
	IFGuard functionGuard(guardMutex);
	IFExampleEvent* event = new IFExampleEvent();
	if (event == 0)
	{
		log(IFLogMessage("Could not allocate event.", 
			VL_ASSERTION, this, "createExampleEvent"));
		return 0;
	}
	addLocalRef(event);
	return event;
}

void IFExampleClass::doNothing() const
{
	IFGuard functionGuard(guardMutex);
	cout << "Doing nothing." << endl;
}

void IFExampleClass::setSomeValue(int newSomeValue)
{
	IFGuard propertyGuard(guardMutex);
	someValue = newSomeValue;
}

int IFExampleClass::getSomeValue() const
{
	IFGuard propertyGuard(guardMutex);
	return someValue;
}

void IFExampleClass::setSomeText(const std::string& newSomeText)
{
	IFGuard propertyGuard(guardMutex);
	someText = newSomeText;
}

std::string IFExampleClass::getSomeText() const
{
	IFGuard propertyGuard(guardMutex);
	return someText;
}

double IFExampleClass::getRoProp() const
{
	IFGuard propertyGuard(guardMutex);
	return roProp;
}

void IFExampleClass::setSpecialBlah(Blah* newSpecialBlah)
{
	IFGuard propertyGuard(guardMutex);
	specialBlah = newSpecialBlah;
}

Blah* IFExampleClass::getSpecialBlah() const
{
	IFGuard propertyGuard(guardMutex);
	return specialBlah;
}

unsigned int IFExampleClass::getNumBlupps() const
{
	IFGuard propertyGuard(guardMutex);
	return blupps.size();
}

Blupp* IFExampleClass::getBlupp(unsigned int elementIndex) const
{
	IFGuard propertyGuard(guardMutex);
	if (elementIndex < blupps.size())
		return blupps[elementIndex];
	return 0;
}

int IFExampleClass::findBlupp(Blupp* needle, unsigned int occurence) const
{
	IFGuard propertyGuard(guardMutex);
	bool found = false;
	Blupp* currentBlupp = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < blupps.size()))
	{
		currentBlupp = blupps[i];
		if (currentBlupp == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Blupp*>& IFExampleClass::getBlupps()
{
	IFGuard propertyGuard(guardMutex);
	return blupps;
}

void IFExampleClass::addBlupp(Blupp* addElement)
{
	IFGuard propertyGuard(guardMutex);
	blupps.push_back(addElement);
}

void IFExampleClass::removeBlupp(Blupp* removeElement)
{
	IFGuard propertyGuard(guardMutex);
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

void IFExampleClass::removeBluppIndex(unsigned int removeIndex)
{
	IFGuard propertyGuard(guardMutex);
    if (removeIndex > blupps.size())
        return;
    blupps.erase(blupps.begin() + removeIndex);
}

void IFExampleClass::clearBlupps()
{
	IFGuard propertyGuard(guardMutex);
	blupps.clear();
}

unsigned int IFExampleClass::getBlahs() const
{
	IFGuard propertyGuard(guardMutex);
	return blahs.size();
}

Blah* IFExampleClass::getBlah(const std::string& elementKey) const
{
	IFGuard propertyGuard(guardMutex);
	std::map<std::string, Blah*>::const_iterator i = blahs.find(elementKey);
	if (i != blahs.end())
		return (*i).second;
	return 0;
}

std::map<std::string, Blah*>& IFExampleClass::getBlahs()
{
	IFGuard propertyGuard(guardMutex);
	return blahs;
}

void IFExampleClass::addBlah(const std::string& elementKey, Blah* 
addElement)
{
	IFGuard propertyGuard(guardMutex);
	Blah* theBlah = getBlah(elementKey);
	if (theBlah != 0)
		return;
	blahs[elementKey] = addElement;
}

void IFExampleClass::removeBlah(const std::string& elementKey)
{
	IFGuard propertyGuard(guardMutex);
	std::map<std::string, Blah*>::iterator i = blahs.find(elementKey);
	if (i != blahs.end())
	{
		blahs.erase(i);
	}
}

void IFExampleClass::clearBlahs()
{
	IFGuard propertyGuard(guardMutex);
	blahs.clear();
}

bool IFExampleClass::serialize(std::string& target) const
{
	if (!IFObject::serialize(target))
		return false;
	target.clear();
	pack(someValue, target);
	pack(someText, target);
	pack(roProp, target);
	pack(miep, target);
	return true;
}

int IFExampleClass::deserialize(const std::string& source, int offset)
{
	offset = IFObject::deserialize(source, offset);
	if (offset < 0)
		return false;
	offset = unpack(source, someValue, offset);
	if (offset < 0)
	{
		ostringstream state;
		state << "Could not deserialize property 'someValue'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
		return false;
	}
	offset = unpack(source, someText, offset);
	if (offset < 0)
	{
		ostringstream state;
		state << "Could not deserialize property 'someText'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
		return false;
	}
	offset = unpack(source, roProp, offset);
	if (offset < 0)
	{
		ostringstream state;
		state << "Could not deserialize property 'roProp'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
		return false;
	}
	offset = unpack(source, miep, offset);
	if (offset < 0)
	{
		ostringstream state;
		state << "Could not deserialize variable 'miep'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
		return false;
	}
	return offset;
}

IFExampleSignal& IFExampleClass::getSignalFirst()
{
	return signalFirst;
}

Ionflux::ObjectBase::IFSignal* IFExampleClass::getSignalFirstWrapper()
{
	if (signalFirstWrapper == 0)
	{
		signalFirstWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalFirst, SIGNAL_TYPE_EXAMPLE, 
			SIGNAL_NAME_FIRST);
		if (signalFirstWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				VL_ASSERTION, this, 
				"getSignalFirstWrapper"));
		addLocalRef(signalFirstWrapper);
	}
	return signalFirstWrapper;
}

IFExampleSignal& IFExampleClass::getSignalSecond()
{
	return signalSecond;
}

Ionflux::ObjectBase::IFSignal* IFExampleClass::getSignalSecondWrapper()
{
	if (signalSecondWrapper == 0)
	{
		signalSecondWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalSecond, SIGNAL_TYPE_EXAMPLE, 
			SIGNAL_NAME_SECOND);
		if (signalSecondWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				VL_ASSERTION, this, 
				"getSignalSecondWrapper"));
		addLocalRef(signalSecondWrapper);
	}
	return signalSecondWrapper;
}

}

}

/** \file IFExampleClass.cpp
 * \brief Example class implementation.
 */
