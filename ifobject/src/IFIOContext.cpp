/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFIOContext.cpp                 I/O Context (implementation).
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

#include "ifobject/IFIOContext.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "ifobject/utf8.hpp"
#include "ifobject/IFError.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

IFIOContextClassInfo::IFIOContextClassInfo()
{
	name = "IFIOContext";
	desc = "I/O Context";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

IFIOContextClassInfo::~IFIOContextClassInfo()
{
}

// run-time type information instance constants
const IFIOContextClassInfo IFIOContext::iFIOContextClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFIOContext::CLASS_INFO = &IFIOContext::iFIOContextClassInfo;

IFIOContext::IFIOContext()
: inputStream(0), outputStream(0), poMapSerialized(0), poMapCurrent(0), inputStreamType(Ionflux::ObjectBase::STREAM_TYPE_UNDEFINED), outputStreamType(Ionflux::ObjectBase::STREAM_TYPE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFIOContext::IFIOContext(const Ionflux::ObjectBase::IFIOContext& other)
: inputStream(0), outputStream(0), poMapSerialized(0), poMapCurrent(0), inputStreamType(Ionflux::ObjectBase::STREAM_TYPE_UNDEFINED), outputStreamType(Ionflux::ObjectBase::STREAM_TYPE_UNDEFINED)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

IFIOContext::~IFIOContext()
{
	clear();
}

void IFIOContext::clearInputStream()
{
	if (inputStream != 0)
	{
	    closeInputStream();
	    delete inputStream;
	}
	inputStream = 0;
	inputStreamType = STREAM_TYPE_UNDEFINED;
}

void IFIOContext::clearOutputStream()
{
	if (outputStream != 0)
	{
	    closeOutputStream();
	    delete outputStream;
	}
	outputStream = 0;
	outputStreamType = STREAM_TYPE_UNDEFINED;
}

void IFIOContext::clearStreams()
{
	clearInputStream();
	clearOutputStream();
}

void IFIOContext::clearMaps()
{
	if (poMapSerialized != 0)
	    delete poMapSerialized;
	poMapSerialized = 0;
	if (poMapCurrent != 0)
	    delete poMapCurrent;
	poMapCurrent = 0;
}

void IFIOContext::clear()
{
	clearStreams();
	clearMaps();
}

void IFIOContext::initMaps()
{
	clearMaps();
	poMapSerialized = 
	    Ionflux::ObjectBase::create<Ionflux::ObjectBase::PointerOffsetMap>(
	        this, "initMaps", "pointer/offset map (serialized)");
	poMapCurrent = 
	    Ionflux::ObjectBase::create<Ionflux::ObjectBase::PointerOffsetMap>(
	        this, "initMaps", "pointer/offset map (serialized)");
}

void IFIOContext::flushOutputStream()
{
	if (outputStream != 0)
	    outputStream->flush();
}

void IFIOContext::closeInputStream()
{
	if ((inputStream != 0) 
	    && (inputStreamType == Ionflux::ObjectBase::STREAM_TYPE_FILE))
	{
	    std::ifstream* s0 = checkedDynamicCast<std::ifstream>(
	            inputStream, this, "closeInputStream", "input stream", 
	            "std::ifstream");
	    s0->close();
	}
}

void IFIOContext::closeOutputStream()
{
	if ((outputStream != 0) 
	    && (outputStreamType == Ionflux::ObjectBase::STREAM_TYPE_FILE))
	{
	    std::ofstream* s0 = checkedDynamicCast<std::ofstream>(
	            outputStream, this, "closeOutputStream", "output stream", 
	            "std::ofstream");
	    s0->close();
	}
}

void IFIOContext::closeStreams()
{
	closeInputStream();
	closeOutputStream();
}

void IFIOContext::begin()
{
	initMaps();
}

void IFIOContext::finish()
{
	flushOutputStream();
}

void IFIOContext::openFileForOutput(const std::string& fileName)
{
	clearOutputStream();
	outputStream = new std::ofstream(fileName.c_str(), 
	    std::ios_base::out | std::ios_base::binary);
	if (outputStream == 0)
	{
	    throw IFError(getErrorString(
	        "Could not allocate output stream.", "openFileForOutput"));
	}
	if (!outputStream->good())
	{
	    std::ostringstream status;
	    status << "Could not open file '" << fileName << "' for writing.";
	    throw IFError(getErrorString(status.str(), 
	        "openFileForOutput"));
	}
	outputStreamType = STREAM_TYPE_FILE;
}

void IFIOContext::openFileForInput(const std::string& fileName)
{
	clearInputStream();
	inputStream = new std::ifstream(fileName.c_str(), 
	    std::ios_base::in | std::ios_base::binary);
	if (inputStream == 0)
	{
	    throw IFError(getErrorString(
	        "Could not allocate input stream.", "openFileForInput"));
	}
	if (!inputStream->good())
	{
	    std::ostringstream status;
	    status << "Could not open file '" << fileName << "' for reading.";
	    throw IFError(getErrorString(status.str(), 
	        "openFileForInput"));
	}
	inputStreamType = STREAM_TYPE_FILE;
}

void IFIOContext::setStringBufferOutput()
{
	clearOutputStream();
	outputStream = new std::ostringstream;
	if (outputStream == 0)
	{
	    throw IFError(getErrorString(
	        "Could not allocate output stream.", "setStringBufferOutput"));
	}
	outputStreamType = STREAM_TYPE_STRING;
}

void IFIOContext::setStringBufferInput(const std::string& data)
{
	clearInputStream();
	inputStream = new std::istringstream(data);
	if (inputStream == 0)
	{
	    throw IFError(getErrorString(
	        "Could not allocate input stream.", "setStringBufferInput"));
	}
	inputStreamType = STREAM_TYPE_STRING;
}

void IFIOContext::getStringBufferOutputValue(std::string& target)
{
	if (outputStreamType != STREAM_TYPE_STRING)
	{
	    throw IFError(getErrorString(
	        "Output stream has incompatible type.", 
	        "getStringBufferOutputValue"));
	}
	std::ostringstream* s0 = checkedDynamicCast<std::ostringstream>(
	        outputStream, this, "getStringBufferOutputValue", "output stream",
	
        "std::ostringstream");
	target.assign(s0->str());
}

std::string IFIOContext::getStringBufferOutputValue0()
{
	std::string result;
	getStringBufferOutputValue(result);
	return result;
}

void IFIOContext::getStringBufferInputValue(std::string& target)
{
	if (inputStreamType != STREAM_TYPE_STRING)
	{
	    throw IFError(getErrorString(
	        "Output stream has incompatible type.", 
	        "getStringBufferInputValue"));
	}
	std::istringstream* s0 = checkedDynamicCast<std::istringstream>(
	        inputStream, this, "getStringBufferInputValue", "input stream", 
	        "std::istringstream");
	target.assign(s0->str());
}

std::string IFIOContext::getStringBufferInputValue0()
{
	std::string result;
	getStringBufferInputValue(result);
	return result;
}

Ionflux::ObjectBase::DataSize IFIOContext::readFromInputStream(std::string&
target, Ionflux::ObjectBase::DataSize numBytes, 
Ionflux::ObjectBase::DataSize offset)
{
	if (inputStream == 0)
	    return DATA_SIZE_INVALID;
	return readFromStream(*inputStream, target, numBytes, offset);
}

Ionflux::ObjectBase::DataSize IFIOContext::writeToOutputStream(const 
std::string& source, Ionflux::ObjectBase::DataSize offset)
{
	if (outputStream == 0)
	    return 0;
	return writeToStream(*outputStream, source, offset);
}

Ionflux::ObjectBase::DataSize IFIOContext::getInputStreamSize()
{
	if (inputStream != 0)
	{
	    std::streampos p0 = inputStream->tellg();
	    inputStream->seekg(0, inputStream->end);
	    std::streampos p1 = inputStream->tellg();
	    inputStream->seekg(p0);
	    return p1;
	}
	return DATA_SIZE_INVALID;
}

Ionflux::ObjectBase::DataSize IFIOContext::getOutputStreamSize()
{
	if (outputStream != 0)
	{
	    std::streampos p0 = outputStream->tellp();
	    outputStream->seekp(0, outputStream->end);
	    std::streampos p1 = outputStream->tellp();
	    outputStream->seekp(p0);
	    return p1;
	}
	return DATA_SIZE_INVALID;
}

Ionflux::ObjectBase::DataSize 
IFIOContext::getSerializedOffset(Ionflux::ObjectBase::GenericPointer p)
{
	nullPointerCheck(poMapSerialized, this, 
	    "getSerializedOffset", "Pointer/offset map (serialized)");
	return checkedLookup(*poMapSerialized, p, this, 
    "getSerializedOffset", "Offset (serialized)");;
}

void IFIOContext::setSerializedOffset(Ionflux::ObjectBase::GenericPointer 
p, Ionflux::ObjectBase::DataSize offset)
{
	nullPointerCheck(poMapSerialized, this, 
	    "setSerializedOffset", "Pointer/offset map (serialized)");
	(*poMapSerialized)[p] = offset;
}

Ionflux::ObjectBase::DataSize 
IFIOContext::getCurrentOffset(Ionflux::ObjectBase::GenericPointer p)
{
	nullPointerCheck(poMapCurrent, this, 
	    "getCurrentOffset", "Pointer/offset map (current)");
	return checkedLookup(*poMapCurrent, p, this, 
    "getCurrentOffset", "Offset (current)");;
}

void IFIOContext::setCurrentOffset(Ionflux::ObjectBase::GenericPointer p, 
Ionflux::ObjectBase::DataSize offset)
{
	nullPointerCheck(poMapCurrent, this, 
	    "setCurrentOffset", "Pointer/offset map (current)");
	(*poMapCurrent)[p] = offset;
}

void IFIOContext::printDebugInfo(bool inputStreamVerbose, bool 
outputStreamVerbose, bool poMapSerializedVerbose, bool poMapCurrentVerbose)
{
	std::cout << "input: " 
	    << getStreamTypeValueString(inputStreamType) << std::endl;
	if (inputStreamVerbose 
	    && (inputStream != 0))
	{
	    std::string data;
	    readFromInputStream(data, DATA_SIZE_INVALID, 0);
	    std::cout << "  size = " << data.size() << std::endl 
	        << "  data:" << std::endl;
	    std::cout << Ionflux::ObjectBase::utf8MakeNiceHexForData(data) 
	        << std::endl;
	}
	std::cout << "output: " 
	    << getStreamTypeValueString(outputStreamType) << std::endl;
	if (outputStreamVerbose 
	    && (outputStream != 0))
	{
	    std::cout << "  size = " << getOutputStreamSize() << std::endl;
	    if (outputStreamType == STREAM_TYPE_STRING)
	    {
	        std::string data;
	        getStringBufferOutputValue(data);
	        std::cout << "  data:" << std::endl;
	        std::cout << utf8MakeNiceHexForData(data) << std::endl;
	    }
	}
	std::cout << "pointer/offset map (serialized): ";
	if (poMapSerialized != 0)
	{
	    std::cout << "size = " << poMapSerialized->size() << std::endl;
	    if (poMapSerializedVerbose)
	    {
	        Ionflux::ObjectBase::DataSize k = 0;
	        for (Ionflux::ObjectBase::PointerOffsetMap::const_iterator i = 
	            poMapSerialized->begin(); i != poMapSerialized->end(); i++)
	        {
	            std::cout << "  [" << std::setw(3) << std::setfill('0') 
	                << std::right << k << "] " << (*i).first << " -> " 
	                << (*i).second << std::endl;
	            k++;
	        }
	    }
	} else
	    std::cout << "<null>"<< std::endl;
	std::cout << "pointer/offset map (current): ";
	if (poMapCurrent != 0)
	{
	    std::cout << "size = " << poMapCurrent->size() << std::endl;
	    if (poMapCurrentVerbose)
	    {
	        Ionflux::ObjectBase::DataSize k = 0;
	        for (Ionflux::ObjectBase::PointerOffsetMap::const_iterator i = 
	            poMapCurrent->begin(); i != poMapCurrent->end(); i++)
	        {
	            std::cout << "  [" << std::setw(3) << std::setfill('0') 
	                << std::right << k << "] " << (*i).first << " -> " 
	                << (*i).second << std::endl;
	            k++;
	        }
	    }
	} else
	    std::cout << "<null>"<< std::endl;
}

std::string IFIOContext::getValueString() const
{
	std::ostringstream status;
	status << "input: " 
	    << Ionflux::ObjectBase::getStreamTypeValueString(inputStreamType) 
	    << ", output: " 
	    << Ionflux::ObjectBase::getStreamTypeValueString(outputStreamType);
	return status.str();
}

void IFIOContext::setInputStream(std::istream* newInputStream)
{
	inputStream = newInputStream;
}

std::istream* IFIOContext::getInputStream() const
{
    return inputStream;
}

void IFIOContext::setOutputStream(std::ostream* newOutputStream)
{
	outputStream = newOutputStream;
}

std::ostream* IFIOContext::getOutputStream() const
{
    return outputStream;
}

void IFIOContext::setPoMapSerialized(Ionflux::ObjectBase::PointerOffsetMap*
newPoMapSerialized)
{
	poMapSerialized = newPoMapSerialized;
}

Ionflux::ObjectBase::PointerOffsetMap* IFIOContext::getPoMapSerialized() 
const
{
    return poMapSerialized;
}

void IFIOContext::setPoMapCurrent(Ionflux::ObjectBase::PointerOffsetMap* 
newPoMapCurrent)
{
	poMapCurrent = newPoMapCurrent;
}

Ionflux::ObjectBase::PointerOffsetMap* IFIOContext::getPoMapCurrent() const
{
    return poMapCurrent;
}

void IFIOContext::setInputStreamType(Ionflux::ObjectBase::StreamTypeID 
newInputStreamType)
{
	inputStreamType = newInputStreamType;
}

Ionflux::ObjectBase::StreamTypeID IFIOContext::getInputStreamType() const
{
    return inputStreamType;
}

void IFIOContext::setOutputStreamType(Ionflux::ObjectBase::StreamTypeID 
newOutputStreamType)
{
	outputStreamType = newOutputStreamType;
}

Ionflux::ObjectBase::StreamTypeID IFIOContext::getOutputStreamType() const
{
    return outputStreamType;
}

Ionflux::ObjectBase::IFIOContext& IFIOContext::operator=(const 
Ionflux::ObjectBase::IFIOContext& other)
{
    if (this == &other)
        return *this;
    // NOTE: IFIOContext should not be copied.
	return *this;
}

Ionflux::ObjectBase::IFIOContext* IFIOContext::copy() const
{
    IFIOContext* newIFIOContext = create();
    *newIFIOContext = *this;
    return newIFIOContext;
}

Ionflux::ObjectBase::IFIOContext* 
IFIOContext::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<IFIOContext*>(other);
}

Ionflux::ObjectBase::IFIOContext* 
IFIOContext::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    IFIOContext* newObject = new IFIOContext();
    if (newObject == 0)
    {
        throw IFError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int IFIOContext::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file IFIOContext.cpp
 * \brief I/O Context implementation.
 */
