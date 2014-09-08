#ifndef IONFLUX_OBJECT_IFOBJECT
#define IONFLUX_OBJECT_IFOBJECT
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFObject.hpp                    Object (header).
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

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include "sigc++/connection.h"
#include "ifobject/serialize.hpp"
#include "ifobject/log.hpp"
#include "ifobject/utf8.hpp"
#include "libb64.hpp"
#include "ifobject/IFClassInfo.hpp"
#include <iostream>

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
{

namespace ObjectBase
{

class IFSignal;

}

}

namespace Ionflux
{

namespace ObjectBase
{

class IFMutex;
class IFMMEvent;
class IFMMEventHandler;
// events used by IFObject
class IFObjectEvent;

typedef sigc::signal<bool, const Ionflux::ObjectBase::IFObjectEvent&> 
IFObjectSignal;

/** \addtogroup ifobject Ionflux Object Base System
 *
 * Classes implementing the core functionality of the Ionflux Object Base 
 * System.
 *
 * @{
 */
 
/** Object reference information.
 */
struct IFObjectRefInfo
{
	/// Reference count.
	unsigned int refCount;
};
 
/** Reference counting data.
 */
struct IFRefCountData
{
	/// Local reference map.
	IFObjectRefMap refMap;
	/// Reference count.
	unsigned int refCount;
	/// memory management debugging flag.
	bool mmDebug;
};

/// Signal connections for IFObjectSignal.
struct IFObjectSignalConnections
{
	/// Signal connection: object changed signal
	sigc::connection signalObjectChangedConnection;
	/// Signal connection: object ID number changed signal
	sigc::connection signalObjectIDNumChangedConnection;
	/// Signal connection: object ID changed signal
	sigc::connection signalObjectIDChangedConnection;
};

/// Class information for class IFObject.
class IFObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	protected:
		// Operation info: log.
		static Ionflux::ObjectBase::IFOpInfo OP_INFO_LOG;
		
	public:
		/// Constructor.
		IFObjectClassInfo();
		/// Destructor.
		virtual ~IFObjectClassInfo();
};

/** Object.
 *
 * Base class for all objects.
 */
class IFObject
{
	private:
		
	protected:
		/// Class info.
		const Ionflux::ObjectBase::IFClassInfo* theClass;
		/// Object ID.
		Ionflux::ObjectBase::IFObjectID id;
		/// ID number.
		Ionflux::ObjectBase::IFIDNum idNum;
		/// Reference counting data.
		Ionflux::ObjectBase::IFRefCountData* refData;
		/// Guard mutex.
		Ionflux::ObjectBase::IFMutex* guardMutex;
		/// Log target.
		Ionflux::ObjectBase::IFObject* logTarget;
		/// Signal: object changed signal.
		IFObjectSignal signalObjectChanged;
		/// Signal wrapper: object changed signal.
		Ionflux::ObjectBase::IFSignal* signalObjectChangedWrapper;
		/// Signal: object ID number changed signal.
		IFObjectSignal signalObjectIDNumChanged;
		/// Signal wrapper: object ID number changed signal.
		Ionflux::ObjectBase::IFSignal* signalObjectIDNumChangedWrapper;
		/// Signal: object ID changed signal.
		IFObjectSignal signalObjectIDChanged;
		/// Signal wrapper: object ID changed signal.
		Ionflux::ObjectBase::IFSignal* signalObjectIDChangedWrapper;
		
		/** Operation proxy: log.
		 *
		 * Proxy for the 'log' operation.
		 *
		 * \param logObject Object to be logged.
		 * \param target Where to store the result.
		 */
		bool opLog(Ionflux::ObjectBase::IFObject* logObject, 
		Ionflux::ObjectBase::IFObjectVector* target = 0);

		/** Operation proxy: log.
		 *
		 * Proxy for the 'log' operation.
		 *
		 * \param logObject Object to be logged.
		 * \param target Where to store the result.
		 */
		bool opLog(Ionflux::ObjectBase::IFObject* logObject, 
		Ionflux::ObjectBase::IFObjectVector* target = 0) const;
		
		/** Operation dispatch.
		 *
		 * Default function used for dispatching operations.
		 *
		 * \param opName Operation name.
		 * \param params Parameters.
		 * \param target Where to store the result.
		 */
		bool opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
			const Ionflux::ObjectBase::IFObjectVector* params = 0, 
			Ionflux::ObjectBase::IFObjectVector* target = 0);
		
		/** Operation dispatch.
		 *
		 * Default function used for dispatching operations.
		 *
		 * \param opName Operation name.
		 * \param params Parameters.
		 * \param target Where to store the result.
		 */
		bool opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
			const Ionflux::ObjectBase::IFObjectVector* params = 0, 
			Ionflux::ObjectBase::IFObjectVector* target = 0) const;
		
	public:
		/// object literal prefix.
		static const std::string LITERAL_PREFIX;
		/// object literal separator.
		static const std::string LITERAL_SEPARATOR;
		/// encoding: raw.
		static const std::string ENCODING_RAW;
		/// encoding: UTF-8.
		static const std::string ENCODING_UTF8;
		/// encoding: base64.
		static const std::string ENCODING_BASE64;
		/// Default object size.
		static const Ionflux::ObjectBase::UInt64 DEFAULT_SIZE;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		/// ID number: undefined.
		static const IFIDNum ID_NUM_UNDEFINED;
		/// Signal type: object.
		static const Ionflux::ObjectBase::IFSignalType SIGNAL_TYPE_OBJECT;
		/// Signal name: object_changed.
		static const std::string SIGNAL_NAME_OBJECT_CHANGED;
		/// Signal name: object_id_num_changed.
		static const std::string SIGNAL_NAME_OBJECT_ID_NUM_CHANGED;
		/// Signal name: object_id_changed.
		static const std::string SIGNAL_NAME_OBJECT_ID_CHANGED;
		/// Class information instance.
		static const IFObjectClassInfo iFObjectClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFObject object.
		 */
		IFObject();
		
		/** Destructor.
		 *
		 * Destruct IFObject object.
		 */
		virtual ~IFObject();
		
		/** Create event: object.
		 * 
		 * Create and initialize a 'object' event.
		 * 
		 * \return New event, or 0 if an error occured.
		 */
		IFObjectEvent* createObjectEvent();
		
		/** Get class information.
		 *
		 * Get the class information.
		 *
		 * \return The class information, or 0 if no class information exists for
		 * this class.
		 */
		virtual const Ionflux::ObjectBase::IFClassInfo* getClass() const;
		
		/** Get class name.
		 *
		 * Get the class name
		 *
		 * \return The class name.
		 */
		virtual std::string getClassName() const;
		
		/** Get class description.
		 *
		 * Get the class description
		 *
		 * \return The class description.
		 */
		virtual std::string getClassDesc() const;
		
		/** Set object ID.
		 *
		 * Set the object ID
		 *
		 * \param newID Object ID.
		 */
		virtual void setID(const Ionflux::ObjectBase::IFObjectID& newID);
		
		/** Get object ID.
		 *
		 * Get the object ID
		 *
		 * \return The object ID.
		 */
		virtual Ionflux::ObjectBase::IFObjectID getID() const;
		
		/** Set ID number.
		 *
		 * Set the ID number
		 *
		 * \param newIDNum ID number.
		 */
		virtual void setIDNum(Ionflux::ObjectBase::IFIDNum newIDNum);
		
		/** Get ID number.
		 *
		 * Get the ID number
		 *
		 * \return The ID number.
		 */
		virtual Ionflux::ObjectBase::IFIDNum getIDNum() const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation of the object.
		 */
		virtual  operator std::string() const;
		
		/** Get literal representation.
		 *
		 * Get a literal representation of the object. This is a string 
		 * representation which contains the persistent state of the object, 
		 * so it may be used to restore the state to an unititialized object. 
		 * It also identifies the type of object which the literal represents.
		 *
		 * \param target where to store the literal.
		 * \param encoding encoding to be used.
		 */
		virtual void getLiteral(std::string& target, const std::string& encoding 
		= ENCODING_UTF8) const;
		
		/** Get literal representation.
		 *
		 * Get a literal representation of the object. This is a string 
		 * representation which contains the persistent state of the object, 
		 * so it may be used to restore the state to an unititialized object. 
		 * It also identifies the type of object which the literal represents.
		 *
		 * \param encoding encoding to be used.
		 *
		 * \return Object literal.
		 */
		virtual std::string getLiteral2(const std::string& encoding = 
		ENCODING_UTF8) const;
		
		/** Initialize from literal representation.
		 *
		 * Initialize the object from a literal representation. The object 
		 * must be an instance of the class or a class derived from the class 
		 * specified in the literal for this to work.
		 *
		 * \param source literal representation of an object.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool initFromLiteral(const std::string& source);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Copy of the object.
		 */
		virtual Ionflux::ObjectBase::IFObject* copy() const;
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added to
		 * the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance, or 0 if an error occurs.
		 */
		static Ionflux::ObjectBase::IFObject* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Perform operation.
		 *
		 * Perform an operation on the object. This provides a very general 
		 * mechanism to let the object perform an operation. Other objects may
		 * be passed for use in the operation in the parameter vector. Results
		 * are stored in the target vector, if it is specified. The operation 
		 * is identified by a name (a string, usually).
		 *
		 * \param opName Operation name.
		 * \param params Parameters.
		 * \param target Where to store the result.
		 *
		 * \return \c true if the operation succeded, \c false otherwise.
		 */
		virtual bool doOp(const Ionflux::ObjectBase::IFOpName& opName, const 
		Ionflux::ObjectBase::IFObjectVector* params = 0, 
		Ionflux::ObjectBase::IFObjectVector* target = 0);
		
		/** Perform operation.
		 *
		 * Perform an operation on the object. This provides a very general 
		 * mechanism to let the object perform an operation. Other objects may
		 * be passed for use in the operation in the parameter vector. Results
		 * are stored in the target vector, if it is specified. The operation 
		 * is identified by a name (a string, usually).
		 *
		 * \param opName Operation name.
		 * \param params Parameters.
		 * \param target Where to store the result.
		 *
		 * \return \c true if the operation succeded, \c false otherwise.
		 */
		virtual bool doOp(const Ionflux::ObjectBase::IFOpName& opName, const 
		Ionflux::ObjectBase::IFObjectVector* params = 0, 
		Ionflux::ObjectBase::IFObjectVector* target = 0) const;
		
		/** Assignment operator.
		 *
		 * Assignment operator.
		 *
		 * \param otherObject Object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFObject& operator=(const 
		Ionflux::ObjectBase::IFObject& otherObject);
		
		/** Log object.
		 *
		 * Log an object. If no log target has been set, the default 
		 * implementation just writes the string representation of the object 
		 * to standard output. If a log target has been set, the log() 
		 * function of the target will be called.
		 *
		 * \param logObject Object to be logged.
		 */
		virtual void log(const Ionflux::ObjectBase::IFObject& logObject);
		
		/** Log object.
		 *
		 * Causes the object to log itself.
		 */
		virtual void log();
		
		/** Log object.
		 *
		 * Log an object. If no log target has been set, the default 
		 * implementation just writes the string representation of the object 
		 * to standard output. If a log target has been set, the log() 
		 * function of the target will be called.
		 *
		 * \param logObject Object to be logged.
		 */
		virtual void log(const Ionflux::ObjectBase::IFObject& logObject) const;
		
		/** Log object.
		 *
		 * Causes the object to log itself.
		 */
		virtual void log() const;
		
		/** Check assertion.
		 *
		 * Log the specified object if the assertion evaluates to \c false.
		 *
		 * \param assertion Assertion to be checked.
		 * \param logObject Object to be logged.
		 *
		 * \return Value of the assertion.
		 */
		virtual bool assert0(bool assertion, const Ionflux::ObjectBase::IFObject&
		logObject);
		
		/** Check assertion.
		 *
		 * Log the specified object if the assertion evaluates to \c false.
		 *
		 * \param assertion Assertion to be checked.
		 * \param logObject Object to be logged.
		 *
		 * \return Value of the assertion.
		 */
		virtual bool assert0(bool assertion, const Ionflux::ObjectBase::IFObject&
		logObject) const;
		
		/** Add reference.
		 *
		 * Add a reference for the object.
		 *
		 * \return \c true on success \c false otherwise.
		 */
		virtual bool addRef() const;
		
		/** Remove reference.
		 *
		 * Remove a reference for the object.
		 *
		 * \return \c true on success \c false otherwise.
		 */
		virtual bool removeRef() const;
		
		/** Get number of references.
		 *
		 * Get the number of references for the object.
		 *
		 * \return Number of references.
		 */
		virtual unsigned int getNumRefs() const;
		
		/** Add local reference.
		 *
		 * Add a local reference for the target object.
		 *
		 * \param refTarget Target object.
		 *
		 * \return \c true on success \c false otherwise..
		 */
		virtual bool addLocalRef(Ionflux::ObjectBase::IFObject* refTarget) const;
		
		/** Remove local reference.
		 *
		 * Remove a local reference for the target object.
		 *
		 * \param refTarget Target object.
		 *
		 * \return \c true on success \c false otherwise..
		 */
		virtual bool removeLocalRef(Ionflux::ObjectBase::IFObject* refTarget) 
		const;
		
		/** Remove all local references.
		 *
		 * Remove all local references for other objects.
		 *
		 * \return \c true on success \c false otherwise..
		 */
		virtual bool removeAllLocalRefs() const;
		
		/** Get number of local references.
		 *
		 * Get the number of local referenced for the object.
		 *
		 * \param refTarget Target object.
		 *
		 * \return number of local references for the object.
		 */
		virtual unsigned int getNumLocalRefs(Ionflux::ObjectBase::IFObject* 
		refTarget) const;
		
		/** Set guard state.
		 *
		 * Enable or disable object locking. If set to \c true, access to the 
		 * object in a multi-threaded application will be protected by a guard
		 * mutex, if the implementation of the object supports it. Otherwise, 
		 * the object must be protected by other means.
		 * 
		 * \note By default, calls to lock(), unlock() or tryLock() will not 
		 * do anything if guards have not been enabled using this function.
		 *
		 * \param newGuardState Guard state.
		 */
		virtual void setGuardEnabled(bool newGuardState);
		
		/** Get guard state.
		 *
		 * Get the current guard state for the object.
		 *
		 * \return \c true if guards and locking are enabled, \c false otherwise.
		 */
		virtual bool getGuardEnabled();
		
		/** Lock.
		 *
		 * Lock the object. This may be necessary for using certain member 
		 * functions which are not thread safe.
		 * 
		 * \note Locking must be enabled using setGuardEnabled() for this 
		 * function to have an effect. If guards are disabled, the function 
		 * will always return \c true.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool lock() const;
		
		/** Try to lock.
		 *
		 * Try to lock the object. This may be necessary for using certain 
		 * member functions which are not thread safe.
		 * 
		 * \note Locking must be enabled using setGuardEnabled() for this 
		 * function to have an effect. If guards are disabled, the function 
		 * will always return \c true.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool tryLock() const;
		
		/** Unlock.
		 *
		 * Unlock the object. This may be necessary for using certain member 
		 * functions which are not thread safe.
		 * 
		 * \note Locking must be enabled using setGuardEnabled() for this 
		 * function to have an effect. If guards are disabled, the function 
		 * will always return \c true.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool unlock() const;
		
		/** Get size.
		 *
		 * Get the size of the object.
		 * 
		 * \note This will always yield DEFAULT_SIZE unless overridden by 
		 * derived classes.
		 *
		 * \return Size of the object.
		 */
		virtual Ionflux::ObjectBase::UInt64 getSize() const;
		
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \return XML element name.
		 */
		virtual std::string getXMLElementName() const;
		
		/** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 */
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		
		/** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 *
		 * \return XML child data.
		 */
		virtual std::string getXMLChildData0(std::string& target, unsigned int 
		indentLevel = 0) const;
		
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \return XML attribute data.
		 */
		virtual std::string getXMLAttributeData() const;
		
		/** Get XML representation.
		 *
		 * Get an XML representation of the object
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 * \param attributes Additional attributes for the element.
		 */
		virtual void getXML(std::string& target, unsigned int indentLevel = 0, 
		const std::string& attributes = "") const;
		
		/** Get XML representation.
		 *
		 * Get an XML representation of the object
		 *
		 * \param indentLevel Indentation level.
		 * \param attributes Additional attributes for the element.
		 *
		 * \return XML representation.
		 */
		virtual std::string getXML0(unsigned int indentLevel = 0, const 
		std::string& attributes = "") const;
		
		/** Write object data to XML file.
		 *
		 * Write the object data to an XML file.
		 *
		 * \param fileName file name.
		 */
		virtual void writeToXMLFile(const std::string& fileName) const;
		
		/** Load object data from file.
		 *
		 * Load object data from an XML file.
		 *
		 * \param fileName File name.
		 */
		virtual void loadFromXMLFile(const std::string& fileName);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation of the value of the object.
		 */
		virtual std::string getValueString() const;
		
		/** Set memory management debugging flag.
		 *
		 * Set the memory management debugging flag.
		 *
		 * \param newFlag memory management debugging flag.
		 */
		virtual void setMMDebug(bool newFlag = true);
		
		/** Get memory management debugging flag.
		 *
		 * Get the memory management debugging flag.
		 *
		 * \return memory management debugging flag.
		 */
		virtual bool mmDebugEnabled();
		
		/** Handle memory management event.
		 *
		 * Handle memory management event.
		 *
		 * \param event event.
		 */
		virtual void handleMMEvent(const Ionflux::ObjectBase::IFMMEvent& event) 
		const;
		
		/** Get ID string.
		 *
		 * Get a string identifying the object.
		 *
		 * \return ID string.
		 */
		virtual std::string getIDString() const;
		
		/** Get error string.
		 *
		 * Get an error string. The error string includes a string 
		 * representation of the object, an error message and optionally the 
		 * source of the error (e.g. a function name).
		 *
		 * \param message error message.
		 * \param source error source.
		 *
		 * \return String representation of the object.
		 */
		virtual std::string getErrorString(const std::string& message, const 
		std::string& source = "") const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation of the object.
		 */
		virtual std::string getString() const;
		
		/** Get XML object factory.
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \return XML object factory singleton.
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Serialize.
		 *
		 * Serialize the object. This creates a string which contains data 
		 * from which the internal state of the object (as supported 
		 * by serialization) can be restored using deserialize().
		 *
		 * \param target where to store the result
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(std::string& target) const;
		
		/** Deserialize.
		 *
		 * Initialize the object from a serialized representation of its 
		 * internal state. The serialized representation can be obtained 
		 * using serialize().
		 *
		 * \param source serialized data buffer
		 * \param offset position where to start deserialization
		 *
		 * \return offset of remaining data, or DATA_SIZE_INVALID if an error occured.
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset = 0);
		
		/** Serialize.
		 *
		 * Serialize the object to a stream.
		 *
		 * \param target target stream
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(std::ostream& target) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \param source source stream
		 * \param offset stream position from where to start deserialization
		 *
		 * \return offset of remaining data
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get log target.
		 *
		 * \return Current value of log target.
		 */
		virtual Ionflux::ObjectBase::IFObject* getLogTarget() const;
		
		/** Set log target.
		 *
		 * Set new value of log target.
		 *
		 * \param newLogTarget New value of log target.
		 */
		virtual void setLogTarget(Ionflux::ObjectBase::IFObject* newLogTarget);
		
		/** Get signal: object changed signal.
		 *
		 * Get the signal for the object changed signal event.
		 *
		 * \return Signal for the object changed signal event.
		 */
		virtual IFObjectSignal& getSignalObjectChanged();
		
		/** Get signal wrapper: object changed signal.
		 *
		 * Get the signal for the object changed signal event.
		 *
		 * \return Signal for the object changed signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalObjectChangedWrapper();
		
		/** Get signal: object ID number changed signal.
		 *
		 * Get the signal for the object ID number changed signal event.
		 *
		 * \return Signal for the object ID number changed signal event.
		 */
		virtual IFObjectSignal& getSignalObjectIDNumChanged();
		
		/** Get signal wrapper: object ID number changed signal.
		 *
		 * Get the signal for the object ID number changed signal event.
		 *
		 * \return Signal for the object ID number changed signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalObjectIDNumChangedWrapper();
		
		/** Get signal: object ID changed signal.
		 *
		 * Get the signal for the object ID changed signal event.
		 *
		 * \return Signal for the object ID changed signal event.
		 */
		virtual IFObjectSignal& getSignalObjectIDChanged();
		
		/** Get signal wrapper: object ID changed signal.
		 *
		 * Get the signal for the object ID changed signal event.
		 *
		 * \return Signal for the object ID changed signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalObjectIDChangedWrapper();
};

/** Output operator.
 *
 * Output operator
 *
 * \param outputStream Output stream.
 * \param source Source object.
 *
 * \return Output stream.
 */
std::ostream& operator<<(std::ostream& outputStream, const 
Ionflux::ObjectBase::IFObject& source);

/// @}


}

}

/** \file IFObject.hpp
 * \brief Object (header).
 */
#endif
