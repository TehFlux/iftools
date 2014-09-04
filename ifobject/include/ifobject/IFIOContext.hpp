#ifndef IONFLUX_OBJECT_IFIOCONTEXT
#define IONFLUX_OBJECT_IFIOCONTEXT
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFIOContext.hpp                 I/O Context (header).
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

#include <iostream>
#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/// Class information for class IFIOContext.
class IFIOContextClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFIOContextClassInfo();
		/// Destructor.
		virtual ~IFIOContextClassInfo();
};

/** I/O Context.
 * \ingroup ifvg
 *
 * A context that collects data that is used for serializing and 
 * deserializing data.
 */
class IFIOContext
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// input stream.
		std::istream* inputStream;
		/// output stream.
		std::ostream* outputStream;
		/// Pointer/offset map (serialized).
		Ionflux::ObjectBase::PointerOffsetMap* poMapSerialized;
		/// Pointer/offset map (current).
		Ionflux::ObjectBase::PointerOffsetMap* poMapCurrent;
		/// input stream type.
		Ionflux::ObjectBase::StreamTypeID inputStreamType;
		/// output stream type.
		Ionflux::ObjectBase::StreamTypeID outputStreamType;
		
		/** Set input stream type.
		 *
		 * Set new value of input stream type.
		 *
		 * \param newInputStreamType New value of input stream type.
		 */
		virtual void setInputStreamType(Ionflux::ObjectBase::StreamTypeID 
		newInputStreamType);
		
		/** Set output stream type.
		 *
		 * Set new value of output stream type.
		 *
		 * \param newOutputStreamType New value of output stream type.
		 */
		virtual void setOutputStreamType(Ionflux::ObjectBase::StreamTypeID 
		newOutputStreamType);
		
	public:
		/// Class information instance.
		static const IFIOContextClassInfo iFIOContextClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFIOContext object.
		 */
		IFIOContext();
		
		/** Constructor.
		 *
		 * Construct new IFIOContext object.
		 *
		 * \param other Other object.
		 */
		IFIOContext(const Ionflux::ObjectBase::IFIOContext& other);
		
		/** Destructor.
		 *
		 * Destruct IFIOContext object.
		 */
		virtual ~IFIOContext();
		
		/** Clear input stream.
		 *
		 * Clear the input stream and release all associated resources.
		 */
		virtual void clearInputStream();
		
		/** Clear output stream.
		 *
		 * Clear the output stream and release all associated resources.
		 */
		virtual void clearOutputStream();
		
		/** Clear streams.
		 *
		 * Clear the input/output streams and release all associated 
		 * resources.
		 */
		virtual void clearStreams();
		
		/** Clear maps.
		 *
		 * Clear the pointer/offset maps and release all associated resources.
		 */
		virtual void clearMaps();
		
		/** Clear.
		 *
		 * Clear the I/O context and release all associated resources.
		 */
		virtual void clear();
		
		/** Initialize maps.
		 *
		 * Initialize the pointer/offset maps.
		 */
		virtual void initMaps();
		
		/** Flush output stream.
		 *
		 * Flush the output stream.
		 */
		virtual void flushOutputStream();
		
		/** Close input stream.
		 *
		 * Close the input stream.
		 */
		virtual void closeInputStream();
		
		/** Close output stream.
		 *
		 * Close the output stream.
		 */
		virtual void closeOutputStream();
		
		/** Close streams.
		 *
		 * Close the input/output streams.
		 */
		virtual void closeStreams();
		
		/** Begin I/O operation.
		 *
		 * Begin a new I/O operation, i.e. a serialization or deserialization.
		 * This should be called before such an operation to ensure that the 
		 * I/O context is in the correct state.
		 */
		virtual void begin();
		
		/** Finish I/O operation.
		 *
		 * Finish the current I/O operation, i.e. a serialization or 
		 * deserialization. This should be called before such an operation to 
		 * ensure that I/O buffers are flushed.
		 */
		virtual void finish();
		
		/** Open file for output.
		 *
		 * Open the specified file for output.
		 *
		 * \param fileName file name.
		 */
		virtual void openFileForOutput(const std::string& fileName);
		
		/** Open file for input.
		 *
		 * Open the specified file for input.
		 *
		 * \param fileName file name.
		 */
		virtual void openFileForInput(const std::string& fileName);
		
		/** Set string buffer for output.
		 *
		 * Set a string buffer for output.
		 */
		virtual void setStringBufferOutput();
		
		/** Set string buffer for input.
		 *
		 * Set a string buffer for input.
		 *
		 * \param data input data.
		 */
		virtual void setStringBufferInput(const std::string& data);
		
		/** Get output string buffer value.
		 *
		 * Get the value of the output string buffer.
		 *
		 * \param target where to store the data.
		 */
		virtual void getStringBufferOutputValue(std::string& target);
		
		/** Get output string buffer value.
		 *
		 * Get the value of the output string buffer.
		 *
		 * \return value of the output string buffer.
		 */
		virtual std::string getStringBufferOutputValue0();
		
		/** Get input string buffer value.
		 *
		 * Get the value of the input string buffer.
		 *
		 * \param target where to store the data.
		 */
		virtual void getStringBufferInputValue(std::string& target);
		
		/** Get input string buffer value.
		 *
		 * Get the value of the input string buffer.
		 *
		 * \return value of the input string buffer.
		 */
		virtual std::string getStringBufferInputValue0();
		
		/** Read data from input stream.
		 *
		 * Read data from the input stream.
		 *
		 * \param target where to store the data.
		 * \param numBytes number of bytes to read.
		 * \param offset offset.
		 *
		 * \return number of bytes read.
		 */
		virtual Ionflux::ObjectBase::DataSize readFromInputStream(std::string& 
		target, Ionflux::ObjectBase::DataSize numBytes = 
		Ionflux::ObjectBase::DATA_SIZE_INVALID, Ionflux::ObjectBase::DataSize 
		offset = Ionflux::ObjectBase::DATA_SIZE_INVALID);
		
		/** Write data to output stream.
		 *
		 * Write data to the output stream.
		 *
		 * \param source source data.
		 * \param offset offset.
		 *
		 * \return number of bytes written.
		 */
		virtual Ionflux::ObjectBase::DataSize writeToOutputStream(const 
		std::string& source, Ionflux::ObjectBase::DataSize offset = 
		Ionflux::ObjectBase::DATA_SIZE_INVALID);
		
		/** Get input stream size.
		 *
		 * Get the size of the input stream.
		 *
		 * \return size of the input stream (in bytes).
		 */
		virtual Ionflux::ObjectBase::DataSize getInputStreamSize();
		
		/** Get output stream size.
		 *
		 * Get the size of the output stream.
		 *
		 * \return size of the output stream (in bytes).
		 */
		virtual Ionflux::ObjectBase::DataSize getOutputStreamSize();
		
		/** Get serialized offset.
		 *
		 * Get the serialized offset for the specified pointer.
		 *
		 * \param p pointer.
		 *
		 * \return serialized offset for the specified pointer.
		 */
		virtual Ionflux::ObjectBase::DataSize 
		getSerializedOffset(Ionflux::ObjectBase::GenericPointer p);
		
		/** Set serialized offset.
		 *
		 * Set the serialized offset for the specified pointer.
		 *
		 * \param p pointer.
		 * \param offset offset.
		 */
		virtual void setSerializedOffset(Ionflux::ObjectBase::GenericPointer p, 
		Ionflux::ObjectBase::DataSize offset);
		
		/** Get current offset.
		 *
		 * Get the current offset for the specified pointer.
		 *
		 * \param p pointer.
		 *
		 * \return current offset for the specified pointer.
		 */
		virtual Ionflux::ObjectBase::DataSize 
		getCurrentOffset(Ionflux::ObjectBase::GenericPointer p);
		
		/** Set current offset.
		 *
		 * Set the current offset for the specified pointer.
		 *
		 * \param p pointer.
		 * \param offset offset.
		 */
		virtual void setCurrentOffset(Ionflux::ObjectBase::GenericPointer p, 
		Ionflux::ObjectBase::DataSize offset);
		
		/** Print debug information.
		 *
		 * Print debug information for the I/O context.
		 *
		 * \param inputStreamVerbose show verbose information on input stream.
		 * \param outputStreamVerbose show verbose information on output stream.
		 * \param poMapSerializedVerbose show verbose information on 
		 * pointer/offset map (serialized).
		 * \param poMapCurrentVerbose show verbose information on pointer/offset 
		 * map (current).
		 */
		virtual void printDebugInfo(bool inputStreamVerbose = false, bool 
		outputStreamVerbose = false, bool poMapSerializedVerbose = false, bool 
		poMapCurrentVerbose = false);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFIOContext& operator=(const 
		Ionflux::ObjectBase::IFIOContext& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::ObjectBase::IFIOContext* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::ObjectBase::IFIOContext* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::ObjectBase::IFIOContext* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get input stream.
		 *
		 * \return Current value of input stream.
		 */
		virtual std::istream* getInputStream() const;
		
		/** Set input stream.
		 *
		 * Set new value of input stream.
		 *
		 * \param newInputStream New value of input stream.
		 */
		virtual void setInputStream(std::istream* newInputStream);
		
		/** Get output stream.
		 *
		 * \return Current value of output stream.
		 */
		virtual std::ostream* getOutputStream() const;
		
		/** Set output stream.
		 *
		 * Set new value of output stream.
		 *
		 * \param newOutputStream New value of output stream.
		 */
		virtual void setOutputStream(std::ostream* newOutputStream);
		
		/** Get pointer/offset map (serialized).
		 *
		 * \return Current value of pointer/offset map (serialized).
		 */
		virtual Ionflux::ObjectBase::PointerOffsetMap* getPoMapSerialized() 
		const;
		
		/** Set pointer/offset map (serialized).
		 *
		 * Set new value of pointer/offset map (serialized).
		 *
		 * \param newPoMapSerialized New value of pointer/offset map 
		 * (serialized).
		 */
		virtual void setPoMapSerialized(Ionflux::ObjectBase::PointerOffsetMap* 
		newPoMapSerialized);
		
		/** Get pointer/offset map (current).
		 *
		 * \return Current value of pointer/offset map (current).
		 */
		virtual Ionflux::ObjectBase::PointerOffsetMap* getPoMapCurrent() const;
		
		/** Set pointer/offset map (current).
		 *
		 * Set new value of pointer/offset map (current).
		 *
		 * \param newPoMapCurrent New value of pointer/offset map (current).
		 */
		virtual void setPoMapCurrent(Ionflux::ObjectBase::PointerOffsetMap* 
		newPoMapCurrent);
		
		/** Get input stream type.
		 *
		 * \return Current value of input stream type.
		 */
		virtual Ionflux::ObjectBase::StreamTypeID getInputStreamType() const;
		
		/** Get output stream type.
		 *
		 * \return Current value of output stream type.
		 */
		virtual Ionflux::ObjectBase::StreamTypeID getOutputStreamType() const;
};

}

}

/** \file IFIOContext.hpp
 * \brief I/O Context (header).
 */
#endif
