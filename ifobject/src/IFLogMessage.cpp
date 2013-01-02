/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFLogMessage.cpp                Log message (implementation).
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

#include "ifobject/IFLogMessage.hpp"
#include "ifobject/IFMutex.hpp"
#include "ifobject/IFGuard.hpp"
#include <sstream>
#include "ifobject/serialize.hpp"
#include "ifobject/utils.hpp"

using Ionflux::ObjectBase::pack;
using Ionflux::ObjectBase::packObj;
using Ionflux::ObjectBase::unpack;
using Ionflux::ObjectBase::unpackObj;

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

IFLogMessageClassInfo::IFLogMessageClassInfo()
{
	name = "IFLogMessage";
	desc = "Log message";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFLogMessageClassInfo::~IFLogMessageClassInfo()
{
}

// public member constants
const std::string IFLogMessage::TEXT_ASSERTION = "ASSERTION FAILED";
const std::string IFLogMessage::TEXT_SILENT = "";
const std::string IFLogMessage::TEXT_ERROR_CRITICAL = "CRITICAL ERROR";
const std::string IFLogMessage::TEXT_ERROR = "ERROR";
const std::string IFLogMessage::TEXT_WARNING = "WARNING";
const std::string IFLogMessage::TEXT_WARNING_OPT = "WARNING";
const std::string IFLogMessage::TEXT_INFO = "";
const std::string IFLogMessage::TEXT_INFO_OPT = "";
const std::string IFLogMessage::TEXT_DEBUG = "DEBUG";
const std::string IFLogMessage::TEXT_DEBUG_OPT = "DEBUG";
const std::string IFLogMessage::TEXT_DEBUG_INSANE = "DEBUG";
const std::string IFLogMessage::TEXT_ALL = "";

// run-time type information instance constants
const IFLogMessageClassInfo IFLogMessage::iFLogMessageClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFLogMessage::CLASS_INFO = &IFLogMessage::iFLogMessageClassInfo;

IFLogMessage::IFLogMessage()
: level(VL_INFO), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFLogMessage::IFLogMessage(const std::string& initMessage, 
Ionflux::ObjectBase::IFVerbosityLevel initLevel, const 
Ionflux::ObjectBase::IFObject* initSource, const std::string& 
initFunctionName)
: message(initMessage), level(initLevel), source(initSource), 
sourceFunctionName(initFunctionName)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFLogMessage::~IFLogMessage()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::ObjectBase::IFObject* 
IFLogMessage::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFLogMessage* newObject = new IFLogMessage();
	if (newObject == 0)
	{
		cerr << IFLogMessage("Could not allocate object instance.", 
			VL_ERROR, 0, "IFObject::create") << endl;
		return 0;
	}
	if (parentObject != 0)
		parentObject->addLocalRef(newObject);
	return newObject;
}

Ionflux::ObjectBase::IFObject* IFLogMessage::copy() const
{
	IFGuard functionGuard(guardMutex);
	IFLogMessage* newLogMessage = new IFLogMessage();
	*newLogMessage = *this;
	return newLogMessage;
}

Ionflux::ObjectBase::IFLogMessage& IFLogMessage::operator=(const 
Ionflux::ObjectBase::IFLogMessage& otherLogMessage)
{
	IFGuard functionGuard(guardMutex);
	message = otherLogMessage.getMessage();
	level = otherLogMessage.getLevel();
	source = otherLogMessage.getSource();
	sourceFunctionName = otherLogMessage.getSourceFunctionName();
	return *this;
}

Ionflux::ObjectBase::IFObject& IFLogMessage::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	IFGuard functionGuard(guardMutex);
	const IFLogMessage* otherLogMessage = dynamic_cast<const 
	IFLogMessage*>(&otherObject);
	if (otherLogMessage != 0)
		*this = *otherLogMessage;
	else
		cerr << "[IFLogMessage::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << endl;
	return *this;
}

std::string 
IFLogMessage::getLevelString(Ionflux::ObjectBase::IFVerbosityLevel 
otherLevel)
{
	string result;
	if (otherLevel == VL_ASSERTION)
		result = TEXT_ASSERTION;
	else
	if (otherLevel == VL_ERROR_CRITICAL)
		result = TEXT_ERROR_CRITICAL;
	else
	if (otherLevel == VL_ERROR)
		result = TEXT_ERROR;
	else
	if (otherLevel == VL_WARNING)
		result = TEXT_WARNING;
	else
	if (otherLevel == VL_WARNING_OPT)
		result = TEXT_WARNING_OPT;
	else
	if (otherLevel == VL_INFO)
		result = TEXT_INFO;
	else
	if (otherLevel == VL_INFO_OPT)
		result = TEXT_INFO_OPT;
	else
	if (otherLevel == VL_DEBUG)
		result = TEXT_DEBUG;
	else
	if (otherLevel == VL_DEBUG_OPT)
		result = TEXT_DEBUG_OPT;
	else
	if (otherLevel == VL_DEBUG_INSANE)
		result = TEXT_DEBUG_INSANE;
	return result;
}

Ionflux::ObjectBase::IFVerbosityLevel 
IFLogMessage::getLevelFromString(const std::string& levelString)
{
	IFVerbosityLevel result = VL_INFO;
	if (levelString == "VL_ASSERTION")
		result = VL_ASSERTION;
	else
	if (levelString == "VL_SILENT")
		result = VL_SILENT;
	else
	if (levelString == "VL_ERROR_CRITICAL")
		result = VL_ERROR_CRITICAL;
	else
	if (levelString == "VL_ERROR")
		result = VL_ERROR;
	else
	if (levelString == "VL_WARNING")
		result = VL_WARNING;
	else
	if (levelString == "VL_WARNING_OPT")
		result = VL_WARNING_OPT;
	else
	if (levelString == "VL_INFO")
		result = VL_INFO;
	else
	if (levelString == "VL_INFO_OPT")
		result = VL_INFO_OPT;
	else
	if (levelString == "VL_DEBUG")
		result = VL_DEBUG;
	else
	if (levelString == "VL_DEBUG_OPT")
		result = VL_DEBUG_OPT;
	else
	if (levelString == "VL_DEBUG_INSANE")
		result = VL_DEBUG_INSANE;
	else
	if (levelString == "VL_ALL")
		result = VL_ALL;
	return result;
}

std::string IFLogMessage::getString() const
{
	IFGuard functionGuard(guardMutex);
	ostringstream state;
	if ((source != 0)
		|| (sourceFunctionName.size() > 0))
	{
		state << "[";
		if (source != 0)
		{
			state << source->getClassName();
			string objectID = source->getID();
			if (objectID.size() > 0)
				state << "{" << objectID << "}";
			if (sourceFunctionName.size() > 0)
				state << "::";
		}
		state << sourceFunctionName << "] ";
	}
	string levelText = getLevelString(level);
	if (levelText.size() > 0)
		state << levelText << ": ";
	state << message;
	return state.str();
}

void IFLogMessage::setMessage(const std::string& newMessage)
{
	IFGuard propertyGuard(guardMutex);
	message = newMessage;
}

std::string IFLogMessage::getMessage() const
{
	IFGuard propertyGuard(guardMutex);
	return message;
}

void IFLogMessage::setLevel(Ionflux::ObjectBase::IFVerbosityLevel newLevel)
{
	IFGuard propertyGuard(guardMutex);
	level = newLevel;
}

Ionflux::ObjectBase::IFVerbosityLevel IFLogMessage::getLevel() const
{
	IFGuard propertyGuard(guardMutex);
	return level;
}

void IFLogMessage::setSource(const Ionflux::ObjectBase::IFObject* 
newSource)
{
	IFGuard propertyGuard(guardMutex);
	source = newSource;
}

const Ionflux::ObjectBase::IFObject* IFLogMessage::getSource() const
{
	IFGuard propertyGuard(guardMutex);
	return source;
}

void IFLogMessage::setSourceFunctionName(const std::string& 
newSourceFunctionName)
{
	IFGuard propertyGuard(guardMutex);
	sourceFunctionName = newSourceFunctionName;
}

std::string IFLogMessage::getSourceFunctionName() const
{
	IFGuard propertyGuard(guardMutex);
	return sourceFunctionName;
}

bool IFLogMessage::serialize(std::string& target) const
{
	if (!IFObject::serialize(target))
		return false;
	pack(message, target);
	pack(level, target);
	pack(sourceFunctionName, target);
	return true;
}

int IFLogMessage::deserialize(const std::string& source, int offset)
{
	offset = IFObject::deserialize(source, offset);
	if (offset < 0)
		return -1;
	// message
    offset = unpack(source, message, offset);
	if (offset < 0)
	{
        std::ostringstream status;
		status << "[IFLogMessage::deserialize] "
			"Could not deserialize property 'message'.";
        throw Ionflux::ObjectBase::IFError(status.str());
	}
	// level
    offset = unpack(source, level, offset);
	if (offset < 0)
	{
        std::ostringstream status;
		status << "[IFLogMessage::deserialize] "
			"Could not deserialize property 'level'.";
        throw Ionflux::ObjectBase::IFError(status.str());
	}
	// sourceFunctionName
    offset = unpack(source, sourceFunctionName, offset);
	if (offset < 0)
	{
        std::ostringstream status;
		status << "[IFLogMessage::deserialize] "
			"Could not deserialize property 'sourceFunctionName'.";
        throw Ionflux::ObjectBase::IFError(status.str());
	}
	return offset;
}

}

}

/** \file IFLogMessage.cpp
 * \brief Log message implementation.
 */
