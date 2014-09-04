/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFIOContext.i                   I/O Context (interface).
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
%{
#include "ifobject/IFIOContext.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFIOContextClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFIOContextClassInfo();
        virtual ~IFIOContextClassInfo();
};

class IFIOContext
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        IFIOContext();
		IFIOContext(const Ionflux::ObjectBase::IFIOContext& other);
        virtual ~IFIOContext();
        virtual void clearInputStream();
        virtual void clearOutputStream();
        virtual void clearStreams();
        virtual void clearMaps();
        virtual void clear();
        virtual void initMaps();
        virtual void flushOutputStream();
        virtual void closeInputStream();
        virtual void closeOutputStream();
        virtual void closeStreams();
        virtual void begin();
        virtual void finish();
        virtual void openFileForOutput(const std::string& fileName);
        virtual void openFileForInput(const std::string& fileName);
        virtual void setStringBufferOutput();
        virtual void setStringBufferInput(const std::string& data);
        virtual void getStringBufferOutputValue(std::string& target);
        virtual std::string getStringBufferOutputValue0();
        virtual void getStringBufferInputValue(std::string& target);
        virtual std::string getStringBufferInputValue0();
        virtual Ionflux::ObjectBase::DataSize 
        readFromInputStream(std::string& target, 
        Ionflux::ObjectBase::DataSize numBytes = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID, 
        Ionflux::ObjectBase::DataSize offset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID);
        virtual Ionflux::ObjectBase::DataSize writeToOutputStream(const 
        std::string& source, Ionflux::ObjectBase::DataSize offset = 
        Ionflux::ObjectBase::DATA_SIZE_INVALID);
        virtual Ionflux::ObjectBase::DataSize getInputStreamSize();
        virtual Ionflux::ObjectBase::DataSize getOutputStreamSize();
        virtual Ionflux::ObjectBase::DataSize 
        getSerializedOffset(Ionflux::ObjectBase::GenericPointer p);
        virtual void 
        setSerializedOffset(Ionflux::ObjectBase::GenericPointer p, 
        Ionflux::ObjectBase::DataSize offset);
        virtual Ionflux::ObjectBase::DataSize 
        getCurrentOffset(Ionflux::ObjectBase::GenericPointer p);
        virtual void setCurrentOffset(Ionflux::ObjectBase::GenericPointer 
        p, Ionflux::ObjectBase::DataSize offset);
        virtual void printDebugInfo(bool inputStreamVerbose = false, bool 
        outputStreamVerbose = false, bool poMapSerializedVerbose = false, 
        bool poMapCurrentVerbose = false);
        virtual std::string getValueString() const;
		virtual Ionflux::ObjectBase::IFIOContext* copy() const;
		static Ionflux::ObjectBase::IFIOContext* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::ObjectBase::IFIOContext* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setInputStream(std::istream* newInputStream);
        virtual std::istream* getInputStream() const;
        virtual void setOutputStream(std::ostream* newOutputStream);
        virtual std::ostream* getOutputStream() const;
        virtual void 
        setPoMapSerialized(Ionflux::ObjectBase::PointerOffsetMap* 
        newPoMapSerialized);
        virtual Ionflux::ObjectBase::PointerOffsetMap* getPoMapSerialized()
        const;
        virtual void setPoMapCurrent(Ionflux::ObjectBase::PointerOffsetMap*
        newPoMapCurrent);
        virtual Ionflux::ObjectBase::PointerOffsetMap* getPoMapCurrent() 
        const;
        virtual Ionflux::ObjectBase::StreamTypeID getInputStreamType() 
        const;
        virtual Ionflux::ObjectBase::StreamTypeID getOutputStreamType() 
        const;
};

}

}
