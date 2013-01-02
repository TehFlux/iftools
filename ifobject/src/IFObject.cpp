/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFObject.cpp                    Object (implementation).
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

#include "ifobject/IFObject.hpp"
#include "ifobject/IFMutex.hpp"
#include "ifobject/IFLogMessage.hpp"
#include "ifobject/IFSignal.hpp"
#include "ifobject/IFObjectEvent.hpp"
#include <climits>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "ifobject/IFError.hpp"
#include "ifobject/xmlutils.hpp"
#include "ifobject/xmlutils_private.hpp"
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

// structure constants

// operation info records
Ionflux::ObjectBase::IFOpInfo IFObjectClassInfo::OP_INFO_LOG;

IFObjectClassInfo::IFObjectClassInfo()
{
	name = "IFObject";
	desc = "Object";
	Ionflux::ObjectBase::IFOpParamInfo currentParam;
	OP_INFO_LOG.name = "log";
	currentParam.type = Ionflux::ObjectBase::IFObject::CLASS_INFO;
	currentParam.name = "logObject";
	currentParam.desc = "Object to be logged";
	currentParam.optional = false;
	currentParam.defaultValue = 0;
	OP_INFO_LOG.paramInfo.push_back(currentParam);
	opInfo = new IFOpNameInfoMap();
	(*opInfo)[OP_INFO_LOG.name] = &OP_INFO_LOG;
}

IFObjectClassInfo::~IFObjectClassInfo()
{
	delete opInfo;
}

// public member constants
const std::string IFObject::LITERAL_PREFIX = "%%";
const std::string IFObject::LITERAL_SEPARATOR = ":";
const std::string IFObject::ENCODING_RAW = "raw";
const std::string IFObject::ENCODING_UTF8 = "utf8";
const std::string IFObject::ENCODING_BASE64 = "base64";
const Ionflux::ObjectBase::UInt64 IFObject::DEFAULT_SIZE = 1;
const std::string IFObject::XML_ELEMENT_NAME = "object";
const IFIDNum IFObject::ID_NUM_UNDEFINED = -1;

// signal type and instance name constants
const Ionflux::ObjectBase::IFSignalType IFObject::SIGNAL_TYPE_OBJECT = 
	"bool,const Ionflux::ObjectBase::IFObjectEvent&";
const std::string IFObject::SIGNAL_NAME_OBJECT_CHANGED = "object_changed";
const std::string IFObject::SIGNAL_NAME_OBJECT_ID_NUM_CHANGED = "object_id_num_changed";
const std::string IFObject::SIGNAL_NAME_OBJECT_ID_CHANGED = "object_id_changed";

// run-time type information instance constants
const IFObjectClassInfo IFObject::iFObjectClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFObject::CLASS_INFO = &IFObject::iFObjectClassInfo;

IFObject::IFObject()
: idNum(ID_NUM_UNDEFINED), refData(0), guardMutex(0), logTarget(0), signalObjectChangedWrapper(0), signalObjectIDNumChangedWrapper(0), signalObjectIDChangedWrapper(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	/* NOTE: Creating IFObjects here will cause an infinite loop. 
	         (Don't do it.) */
	refData = new IFRefCountData();
	if (refData == 0)
	{
		std::cerr << "[IFObject::IFObject] ERROR: "
			"Could not allocate reference count data structure "
			"(this is bad, exiting)." << std::endl;
		exit(-1);
	}
	refData->refCount = 0;
}

IFObject::~IFObject()
{
	removeAllLocalRefs();
	delete refData;
	refData = 0;
}

bool IFObject::opLog(Ionflux::ObjectBase::IFObject* logObject, 
Ionflux::ObjectBase::IFObjectVector* target)
{
	if (logObject != 0)
		log(*logObject);
	return true;
}

bool IFObject::opLog(Ionflux::ObjectBase::IFObject* logObject, 
Ionflux::ObjectBase::IFObjectVector* target) const
{
	if (logObject != 0)
		log(*logObject);
	return true;
}

bool IFObject::opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
	const Ionflux::ObjectBase::IFObjectVector* params, 
	Ionflux::ObjectBase::IFObjectVector* target)
{
	const IFOpInfo* opInfo = theClass->getOpInfo(opName);
	if (opInfo == 0)
	{
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
	if (opName == "log")
		return opLog(
			checkedParams[0], 
			target);
	ostringstream state;
	state << "Failed to dispatch operation '"
		<< opName << "' for some unknown reason (this should not happen).";
	log(IFLogMessage(state.str(), VL_ERROR, 
		this, "opDispatch"));
	return false;
}

bool IFObject::opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
	const Ionflux::ObjectBase::IFObjectVector* params, 
	Ionflux::ObjectBase::IFObjectVector* target) const
{
	const IFOpInfo* opInfo = theClass->getOpInfo(opName);
	if (opInfo == 0)
	{
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
	if (opName == "log")
		return opLog(
			checkedParams[0], 
			target);
	ostringstream state;
	state << "Failed to dispatch operation '"
		<< opName << "' (this is probably because there is no const "
		"implementation available for the operation, but the object on "
		"which the operation has been called is const).";
	log(IFLogMessage(state.str(), VL_ERROR, 
		this, "opDispatch"));
	return false;
}

IFObjectEvent* IFObject::createObjectEvent()
{
	IFObjectEvent* event = new IFObjectEvent();
	if (event == 0)
	{
		log(IFLogMessage("Could not allocate event.", 
			VL_ASSERTION, this, "createObjectEvent"));
		return 0;
	}
	addLocalRef(event);
	return event;
}

const Ionflux::ObjectBase::IFClassInfo* IFObject::getClass() const
{
	// TODO: Implementation.
	return theClass;
}

std::string IFObject::getClassName() const
{
	const IFClassInfo* theClassInfo = getClass();
	if (theClassInfo != 0)
		return theClassInfo->getName();
	return "";
}

std::string IFObject::getClassDesc() const
{
	const IFClassInfo* theClassInfo = getClass();
	if (theClassInfo != 0)
		return theClassInfo->getDesc();
	return "";
}

void IFObject::setID(const Ionflux::ObjectBase::IFObjectID& newID)
{
	IFObjectEvent* event = createObjectEvent();
	event->setType(IFObjectEvent::TYPE_OBJECT_ID_CHANGED);
	event->setSource(this);
	event->setOldID(id);
	event->setNewID(newID);
	id = newID;
	signalObjectIDChanged.emit(*event);
	removeLocalRef(event);
}

Ionflux::ObjectBase::IFObjectID IFObject::getID() const
{
	// TODO: Implementation.
	return id;
}

void IFObject::setIDNum(Ionflux::ObjectBase::IFIDNum newIDNum)
{
	IFObjectEvent* event = createObjectEvent();
	event->setType(IFObjectEvent::TYPE_OBJECT_ID_NUM_CHANGED);
	event->setSource(this);
	event->setOldIDNum(idNum);
	event->setNewIDNum(newIDNum);
	idNum = newIDNum;
	signalObjectIDNumChanged.emit(*event);
	removeLocalRef(event);
}

Ionflux::ObjectBase::IFIDNum IFObject::getIDNum() const
{
	// TODO: Implementation.
	return idNum;
}

 IFObject::operator std::string() const
{
	// TODO: Implementation.
	return getString();
}

void IFObject::getLiteral(std::string& target, const std::string& encoding)
const
{
	ostringstream state;
	state << LITERAL_PREFIX << getClassName() << LITERAL_SEPARATOR;
	std::string buffer;
	serialize(buffer);
	std::string encoded;
	if (encoding == ENCODING_UTF8)
	{
		state << ENCODING_UTF8 << LITERAL_SEPARATOR;
		for (unsigned int i = 0; i < buffer.size(); i++)
		{
			IFUniChar currentChar = static_cast<IFUniChar>(
			    static_cast<unsigned char>(buffer[i]));
			encoded.append(uniCharToUTF8(currentChar));
		}
	} else
	if (encoding == ENCODING_BASE64)
	{
		state << ENCODING_UTF8 << LITERAL_SEPARATOR;
		base64::encode(buffer, encoded);
	} else
	{
		state << ENCODING_RAW << LITERAL_SEPARATOR;
		encoded = buffer;
	}
	UInt32 encodedSize = encoded.size();
	state << encodedSize << LITERAL_SEPARATOR 
		<< encoded;
	target = state.str();
}

std::string IFObject::getLiteral2(const std::string& encoding) const
{
	std::string result;
	getLiteral(result, encoding);
	return result;
}

bool IFObject::initFromLiteral(const std::string& source)
{
	unsigned int pos = 0;
	ostringstream status;
	// check prefix
	if (source.size() < LITERAL_PREFIX.size())
	{
		status << "Literal prefix is missing (literal: '" << source 
			<< "').";
		log(IFLogMessage(status.str(), VL_ERROR, this, "initFromLiteral"));
		return false;
	}
	std::string sourcePrefix = source.substr(0, LITERAL_PREFIX.size());
	if (sourcePrefix != LITERAL_PREFIX)
	{
		status << "Literal prefix not found (found: '" << sourcePrefix 
			<< "', expected: '" << LITERAL_PREFIX << "').";
		log(IFLogMessage(status.str(), VL_ERROR, this, "initFromLiteral"));
		return false;
	}
	pos += LITERAL_PREFIX.size();
	// parse literal
	std::string className;
	std::string encoding;
	std::string rawEncodedSize;
	std::string encodedData;
	unsigned int encodedSize = 0;
	std::string parseError;
	/* state:
		0 - extract class name
		1 - extract encoding
		2 - extract encoded size
		3 - extract encoded data
	   -1 - parse error
	   -2 - finished (correct data)
	   -3 - finished (class mismatch)
	 */
	int state = 0;
	unsigned char currentChar = 0;
	while ((state >= 0)
		&& (pos < source.size()))
	{
		currentChar = source[pos];
		if (state == 0)
		{
			// extract class name
			if (currentChar == LITERAL_SEPARATOR[0])
			{
				if ((className != theClass->getName())
					&& (!theClass->isDerivedFrom(className)))
					state = -3;
				else
					state = 1;
			} else
			if (((currentChar >= 'A') 
					&& (currentChar <= 'Z'))
				|| ((currentChar >= 'a') 
					&& (currentChar <= 'z'))
				|| ((currentChar >= '0') 
					&& (currentChar <= '9'))
				|| (currentChar == '_'))
				className.append(1, currentChar);
			else
			{
				parseError = "invalid character in class name";
				state = -1;
			}
		} else
		if (state == 1)
		{
			// extract encoding
			if (currentChar == LITERAL_SEPARATOR[0])
				state = 2;
			else
			if (((currentChar >= 'a') 
					&& (currentChar <= 'z'))
				|| ((currentChar >= '0') 
					&& (currentChar <= '9'))
				|| (currentChar == '_'))
				encoding.append(1, currentChar);
			else
			{
				parseError = "invalid character in encoding";
				state = -1;
			}
		} else
		if (state == 2)
		{
			// extract encoded size
			if (currentChar == LITERAL_SEPARATOR[0])
			{
				encodedSize = strtol(rawEncodedSize.c_str(), 0, 10);
				state = 3;
			} else
			if ((currentChar >= '0') 
					&& (currentChar <= '9'))
				rawEncodedSize.append(1, currentChar);
			else
			{
				parseError = "invalid character in encoded size";
				state = -1;
			}
		} else
		if (state == 3)
		{
			// extract encoded data
			if (encodedData.size() < encodedSize)
				encodedData.append(1, currentChar);
			else
				state = -2;
		}
		pos++;
	}
	// check for errors
	if (state == -1)
	{
		status << "Parse error: " << parseError << " ('" 
			<< currentChar << "' at position " << pos 
			<< " in literal '";
		if (source.size() > 512)
			status << source.substr(0, 512) << "...";
		else
			status << source;
		status << "').";
		log(IFLogMessage(status.str(), VL_ERROR, this, "initFromLiteral"));
		return false;
	}
	if (state == -3)
	{
		status << "Not a literal of class " << theClass->getName() 
			<< " (literal: '";
		if (source.size() > 512)
			status << source.substr(0, 512) << "...";
		else
			status << source;
		status << "').";
		log(IFLogMessage(status.str(), VL_WARNING_OPT, this, 
			"initFromLiteral"));
		return false;
	}
	// verify size of encoded data
	if (encodedData.size() != encodedSize)
	{
		status << "Size mismatch for encoded data (extracted: " 
			<< encodedData.size() << " bytes, expected: " 
			<< encodedSize << " bytes, literal: '";
		if (source.size() > 512)
			status << source.substr(0, 512) << "...";
		else
			status << source;
		status << "').";
		log(IFLogMessage(status.str(), VL_WARNING_OPT, this, 
			"initFromLiteral"));
		return false;
	}
	// decode data
	std::string decodedData;
	if (encoding == ENCODING_RAW)
		decodedData = encodedData;
	else
	if (encoding == ENCODING_UTF8)
	{
		std::vector<IFUniChar> decodeTemp;
		if (!utf8ToUniChar(encodedData, decodeTemp))
		{
			status << "Error while decoding UTF-8 data (literal: '";
			if (source.size() > 512)
				status << source.substr(0, 512) << "...";
			else
				status << source;
			status << "').";
			log(IFLogMessage(status.str(), VL_ERROR, this, 
				"initFromLiteral"));
			return false;
		}
		for (unsigned int i = 0; i < decodeTemp.size(); i++)
		{
			if (decodeTemp[i] > 0xff)
			{
				status << "Invalid byte value " << decodeTemp[i] 
					<< " (literal: '";
				if (source.size() > 512)
					status << source.substr(0, 512) << "...";
				else
					status << source;
				status << "').";
				log(IFLogMessage(status.str(), VL_ERROR, this, 
					"initFromLiteral"));
				return false;
			}
			decodedData.append(1, static_cast<unsigned char>(decodeTemp[i]));
		}
	} else
	if (encoding == ENCODING_BASE64)
	{
		if (!base64::decode(encodedData, decodedData))
		{
			status << "Error while decoding base64 data (literal: '";
			if (source.size() > 512)
				status << source.substr(0, 512) << "...";
			else
				status << source;
			status << "').";
			log(IFLogMessage(status.str(), VL_ERROR, this, 
				"initFromLiteral"));
			return false;
		}
	} else
	{
		status << "Unknown encoding '" << encoding 
			<< "' (literal: '";
		if (source.size() > 512)
			status << source.substr(0, 512) << "...";
		else
			status << source;
		status << "').";
		log(IFLogMessage(status.str(), VL_ERROR, this, 
			"initFromLiteral"));
		return false;
	}
	// deserialize the object
	if (deserialize(decodedData) == -1)
	{
		status << "Deserialization failed (literal: '";
		if (source.size() > 512)
			status << source.substr(0, 512) << "...";
		else
			status << source;
		status << "').";
		log(IFLogMessage(status.str(), VL_ERROR, this, 
			"initFromLiteral"));
		return false;
	}
	return true;
}

Ionflux::ObjectBase::IFObject* IFObject::copy() const
{
	log(IFLogMessage("Copy operation not implemented.", 
		VL_ERROR, this, "copy"));
	return 0;
}

Ionflux::ObjectBase::IFObject* 
IFObject::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFObject* newObject = new IFObject();
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

bool IFObject::doOp(const Ionflux::ObjectBase::IFOpName& opName, const 
Ionflux::ObjectBase::IFObjectVector* params, 
Ionflux::ObjectBase::IFObjectVector* target)
{
	opDispatch(opName, params, target);
	return false;
}

bool IFObject::doOp(const Ionflux::ObjectBase::IFOpName& opName, const 
Ionflux::ObjectBase::IFObjectVector* params, 
Ionflux::ObjectBase::IFObjectVector* target) const
{
	// TODO: Implementation.
	return opDispatch(opName, params, target);;
}

Ionflux::ObjectBase::IFObject& IFObject::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	log(IFLogMessage("Assignment operator not implemented.", 
		VL_ERROR, this, "operator="));
	return *this;
}

void IFObject::log(const Ionflux::ObjectBase::IFObject& logObject)
{
	if (logTarget == 0)
		cout << logObject << endl;
	else
		logTarget->log(logObject);
}

void IFObject::log()
{
	log(*this);
}

void IFObject::log(const Ionflux::ObjectBase::IFObject& logObject) const
{
	if (logTarget == 0)
		cout << logObject << endl;
	else
		logTarget->log(logObject);
}

void IFObject::log() const
{
	log(*this);
}

bool IFObject::assert0(bool assertion, const Ionflux::ObjectBase::IFObject&
logObject)
{
	if (!assertion)
		log(logObject);
	return assertion;
}

bool IFObject::assert0(bool assertion, const Ionflux::ObjectBase::IFObject&
logObject) const
{
	if (!assertion)
		log(logObject);
	return assertion;
}

bool IFObject::addRef() const
{
	if (refData->refCount < UINT_MAX)
		refData->refCount++;
	else
	{
		log(IFLogMessage("Reference count overflow.", 
			VL_ERROR, this, "addRef"));
		return false;
	}
	return true;
}

bool IFObject::removeRef() const
{
	if (refData->refCount > 0)
		refData->refCount--;
	else
	{
		log(IFLogMessage("Attempt to remove reference for object "
			"with zero references.", VL_ERROR, this, "removeRef"));
		return false;
	}
	return true;
}

unsigned int IFObject::getNumRefs() const
{
	// TODO: Implementation.
	return refData->refCount;
}

bool IFObject::addLocalRef(Ionflux::ObjectBase::IFObject* refTarget) const
{
	if (refTarget == 0)
	{
		log(IFLogMessage("Attempt to add reference to null object.", 
			VL_ERROR, this, "addLocalRef"));
		return false;
	}
	IFObjectRefMap::iterator i = refData->refMap.find(refTarget);
	IFObjectRefInfo* refInfo = 0;
	if ((i != refData->refMap.end())
		&& ((*i).second != 0))
		refInfo = (*i).second;
	else
	{
		refInfo = new IFObjectRefInfo();
		if (refInfo == 0)
		{
			log(IFLogMessage("Could not allocate "
				"object reference info.", VL_ASSERTION, this, 
				"addLocalRef"));
			return false;
		}
		refInfo->refCount = 0;
		refData->refMap[refTarget] = refInfo;
	}
	if (!refTarget->addRef())
	{
		ostringstream state;
		state << "Could not add reference to object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			VL_ERROR, this, "addLocalRef"));
		return false;
	}
	if (refInfo->refCount < UINT_MAX)
		refInfo->refCount++;
	else
	{
		log(IFLogMessage("Local reference count overflow.", 
			VL_ERROR, this, "addLocalRef"));
		refTarget->removeRef();
		return false;
	}
	/* ----- DEBUG ----- //
	ostringstream state;
	state << "Added local reference to object '" 
		<< refTarget->getString() << "'.";
	log(IFLogMessage(state.str(), 
		VL_DEBUG_INSANE, this, "addLocalRef"));
	// ----- DEBUG ----- */
	return true;
}

bool IFObject::removeLocalRef(Ionflux::ObjectBase::IFObject* refTarget) 
const
{
	if (refTarget == 0)
	{
		log(IFLogMessage("Attempt to remove reference to null object.", 
			VL_ERROR, this, "removeLocalRef"));
		return false;
	}
	IFObjectRefMap::iterator i = refData->refMap.find(refTarget);
	IFObjectRefInfo* refInfo = 0;
	if ((i != refData->refMap.end())
		&& ((*i).second != 0))
		refInfo = (*i).second;
	if ((refInfo == 0)
		|| (refInfo->refCount == 0))
	{
		ostringstream state;
		state << "Could not remove local reference to object '" 
			<< refTarget->getString() << "': No local references found.";
		log(IFLogMessage(state.str(), 
			VL_ERROR, this, "removeLocalRef"));
		return false;
	}
	if (refInfo->refCount > 0)
		refInfo->refCount--;
	else
	{
		log(IFLogMessage("Attempt to remove local reference for object "
			"with zero local references.", VL_ERROR, this, 
			"removeLocalRef"));
		return false;
	}
	if (refInfo->refCount == 0)
	{
		refData->refMap[refTarget] = 0;
		delete refInfo;
		refInfo = 0;
		refData->refMap.erase(i);
		/* ----- DEBUG ----- //
		ostringstream state;
		state << "Removed local reference info for object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			VL_DEBUG_INSANE, this, "removeLocalRef"));
		// ----- DEBUG ----- */
	}
	if (!refTarget->removeRef())
	{
		ostringstream state;
		state << "Could not remove reference to object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			VL_ERROR, this, "removeLocalRef"));
		return false;
	}
	if (refTarget->getNumRefs() == 0)
	{
		/* ----- DEBUG ----- //
		ostringstream state;
		state << "Deleting object '" << refTarget->getString() 
			<< "' since there are no more references.";
		log(IFLogMessage(state.str(), 
			VL_DEBUG_INSANE, this, "removeLocalRef"));
		// ----- DEBUG ----- */
		delete refTarget;
		refTarget = 0;
	}
	/* ----- DEBUG ----- //
	if (refTarget != 0)
	{
		ostringstream state;
		state << "Removed local reference to object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			VL_DEBUG_INSANE, this, "removeLocalRef"));
	}
	// ----- DEBUG ----- */
	return true;
}

bool IFObject::removeAllLocalRefs() const
{
	IFObjectRefInfo* refInfo = 0;
	IFObjectRefMap::iterator i;
	IFObject* refTarget = 0;
	bool result = true;
	for (i = refData->refMap.begin(); i != refData->refMap.end(); i++)
	{
		refTarget = (*i).first;
		refInfo = (*i).second;
		if ((refInfo != 0)
			&& (refTarget != 0))
		{
			while (refInfo->refCount > 0)
			{
				if (!refTarget->removeRef())
				{
					ostringstream state;
					state << "Could not remove reference to object '" 
						<< refTarget->getString() << "'.";
					log(IFLogMessage(state.str(), 
						VL_ERROR, this, "removeAllLocalRefs"));
					result = false;
				}
				refInfo->refCount--;
				if (refTarget->getNumRefs() == 0)
				{
					/* ----- DEBUG ----- //
					ostringstream state;
					state << "Deleting object '" << refTarget->getString() 
						<< "' since there are no more references.";
					log(IFLogMessage(state.str(), 
						VL_DEBUG_INSANE, this, 
							"removeAllLocalRefs"));
					// ----- DEBUG ----- */
					delete refTarget;
					refTarget = 0;
				}
				/* ----- DEBUG ----- //
				if (refTarget != 0)
				{
					ostringstream state;
					state << "Removed local reference to object '" 
						<< refTarget->getString() << "'.";
					log(IFLogMessage(state.str(), 
						VL_DEBUG_INSANE, this, 
							"removeAllLocalRefs"));
				}
				// ----- DEBUG ----- */
			}
			refData->refMap[refTarget] = 0;
			delete refInfo;
			refInfo = 0;
		}
	}
	refData->refMap.clear();
	return result;
}

unsigned int IFObject::getNumLocalRefs(Ionflux::ObjectBase::IFObject* 
refTarget) const
{
	if (refTarget == 0)
	{
		log(IFLogMessage("Attempt to get reference count for null object.", 
			VL_ERROR, this, "removeLocalRef"));
		return false;
	}
	IFObjectRefMap::iterator i = refData->refMap.find(refTarget);
	IFObjectRefInfo* refInfo = 0;
	if ((i != refData->refMap.end())
		&& ((*i).second != 0))
		refInfo = (*i).second;
	if ((refInfo == 0)
		|| (refInfo->refCount == 0))
		return 0;
	return refInfo->refCount;
}

void IFObject::setGuardEnabled(bool newGuardState)
{
	if (newGuardState)
	{
		if (guardMutex != 0)
			return;
		guardMutex = new Ionflux::ObjectBase::IFMutex(IFMutex::TYPE_RECURSIVE);
		if (guardMutex == 0)
			log(IFLogMessage("Could not allocate guard mutex.", 
				VL_ASSERTION, this, "setGuardEnabled"));
		addLocalRef(guardMutex);
	} else
	{
		if (guardMutex != 0)
		{
			removeLocalRef(guardMutex);
			guardMutex = 0;
		}
	}
}

bool IFObject::getGuardEnabled()
{
	if (guardMutex != 0)
		return true;
	return false;
}

bool IFObject::lock() const
{
	if (guardMutex != 0)
		return guardMutex->lock();
	return true;
}

bool IFObject::tryLock() const
{
	if (guardMutex != 0)
		return guardMutex->tryLock();
	return true;
}

bool IFObject::unlock() const
{
	if (guardMutex != 0)
		return guardMutex->unlock();
	return true;
}

Ionflux::ObjectBase::UInt64 IFObject::getSize() const
{
	// TODO: Implementation.
	return DEFAULT_SIZE;
}

std::string IFObject::getXMLElementName() const
{
	// TODO: Implementation.
	return XML_ELEMENT_NAME;
}

void IFObject::getXMLChildData(std::string& target, unsigned int 
indentLevel) const
{
	// TODO: Implementation.
}

std::string IFObject::getXMLChildData0(std::string& target, unsigned int 
indentLevel) const
{
	std::string cd;
	getXMLChildData(cd, indentLevel);
	return cd;
}

std::string IFObject::getXMLAttributeData() const
{
	std::ostringstream result;
	std::string id0 = getID();
	if (id0.size() > 0)
	    result << "name=\"" << XMLUtils::xmlEscape(id0) << "\"";
	return result.str();
}

void IFObject::getXML(std::string& target, unsigned int indentLevel) const
{
	std::ostringstream xmlData;
	std::string iws = getIndent(indentLevel);
	std::string en = getXMLElementName();
	xmlData << iws << "<" << en;
	std::string xa = getXMLAttributeData();
	if (xa.size() > 0)
	    xmlData << " " << xa;
	std::string cd;
	getXMLChildData(cd, indentLevel + 1);
	if (cd.size() == 0)
	    xmlData << " />";
	else
	    xmlData << ">\n" << cd << "\n" << iws << "</" << en << ">";
	target.append(xmlData.str());
}

std::string IFObject::getXML0(unsigned int indentLevel) const
{
	std::string xmlData;
	getXML(xmlData, indentLevel);
	return xmlData;
}

void IFObject::writeToXMLFile(const std::string& fileName) const
{
	std::ofstream f0;
	f0.open(fileName.c_str(), ios_base::out);
	if (!f0)
	{
	    std::ostringstream status;
	    status << "Could not write to file' " << fileName << "'";
	    throw IFError(status.str());
	}
	std::string xmlData;
	getXML(xmlData);
	f0.write(xmlData.c_str(), xmlData.size());
}

void IFObject::loadFromXMLFile(const std::string& fileName)
{
	Ionflux::ObjectBase::XMLUtils::loadFromFile(fileName, *this, 
	    getXMLElementName());
}

std::string IFObject::getValueString() const
{
	// TODO: Implementation.
	return "";
}

std::string IFObject::getIDString() const
{
	std::ostringstream status;
	status << getClassName();
	std::string s0 = getID();
	int id0 = getIDNum();
	if ((s0.size() > 0) || (id0 != ID_NUM_UNDEFINED))
	{
	    status << "{";
	    bool first = true;
	    if (s0.size() > 0)
	    {
	        status << s0;
	        first = false;
	    }
	    if (id0 != ID_NUM_UNDEFINED)
	    {
	        if (!first)
	            status << ", ";
	        status << id0;
	    }
	    status << "}";
	}
	return status.str();;
}

std::string IFObject::getString() const
{
	std::ostringstream status;
	status << getIDString();
	std::string s0 = getValueString();
	if (s0.size() > 0)
	    status << "[" << s0 << "]";
	return status.str();
}

void IFObject::setLogTarget(Ionflux::ObjectBase::IFObject* newLogTarget)
{
	if (logTarget == newLogTarget)
		return;
    if (newLogTarget != 0)
        addLocalRef(newLogTarget);
	if (logTarget != 0)
		removeLocalRef(logTarget);
	logTarget = newLogTarget;
}

Ionflux::ObjectBase::IFObject* IFObject::getLogTarget() const
{
	return logTarget;
}

bool IFObject::serialize(std::string& target) const
{
	pack(id, target);
	pack(idNum, target);
	return true;
}

int IFObject::deserialize(const std::string& source, int offset)
{
	offset = unpack(source, id, offset);
	if (offset < 0)
	{
		ostringstream state;
		state << "Could not deserialize variable 'id'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
        return false;
	}
	offset = unpack(source, idNum, offset);
	if (offset < 0)
	{
		ostringstream state;
		state << "Could not deserialize variable 'idNum'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
        return false;
	}
	return offset;
}

IFObjectSignal& IFObject::getSignalObjectChanged()
{
	return signalObjectChanged;
}

Ionflux::ObjectBase::IFSignal* IFObject::getSignalObjectChangedWrapper()
{
	if (signalObjectChangedWrapper == 0)
	{
		signalObjectChangedWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalObjectChanged, SIGNAL_TYPE_OBJECT, 
			SIGNAL_NAME_OBJECT_CHANGED);
		if (signalObjectChangedWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				VL_ASSERTION, this, 
				"getSignalObjectChangedWrapper"));
		addLocalRef(signalObjectChangedWrapper);
	}
	return signalObjectChangedWrapper;
}

IFObjectSignal& IFObject::getSignalObjectIDNumChanged()
{
	return signalObjectIDNumChanged;
}

Ionflux::ObjectBase::IFSignal* IFObject::getSignalObjectIDNumChangedWrapper()
{
	if (signalObjectIDNumChangedWrapper == 0)
	{
		signalObjectIDNumChangedWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalObjectIDNumChanged, SIGNAL_TYPE_OBJECT, 
			SIGNAL_NAME_OBJECT_ID_NUM_CHANGED);
		if (signalObjectIDNumChangedWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				VL_ASSERTION, this, 
				"getSignalObjectIDNumChangedWrapper"));
		addLocalRef(signalObjectIDNumChangedWrapper);
	}
	return signalObjectIDNumChangedWrapper;
}

IFObjectSignal& IFObject::getSignalObjectIDChanged()
{
	return signalObjectIDChanged;
}

Ionflux::ObjectBase::IFSignal* IFObject::getSignalObjectIDChangedWrapper()
{
	if (signalObjectIDChangedWrapper == 0)
	{
		signalObjectIDChangedWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalObjectIDChanged, SIGNAL_TYPE_OBJECT, 
			SIGNAL_NAME_OBJECT_ID_CHANGED);
		if (signalObjectIDChangedWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				VL_ASSERTION, this, 
				"getSignalObjectIDChangedWrapper"));
		addLocalRef(signalObjectIDChangedWrapper);
	}
	return signalObjectIDChangedWrapper;
}

std::ostream& operator<<(std::ostream& outputStream, const 
Ionflux::ObjectBase::IFObject& source)
{
	// TODO: Implementation.
	return outputStream << source.getString();
}

}

}

/** \file IFObject.cpp
 * \brief Object implementation.
 */
