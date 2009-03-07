#ifndef IONFLUX_OBJECT_IFLOGMESSAGE
#define IONFLUX_OBJECT_IFLOGMESSAGE
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFLogMessage.hpp                Log message (header).
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

namespace Ionflux
{

namespace ObjectBase
{

/// Class information for class IFLogMessage.
class IFLogMessageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFLogMessageClassInfo();
		/// Destructor.
		virtual ~IFLogMessageClassInfo();
};

/** Log message.
 * \ingroup ifobject
 *
 * A message which provides information about what is going on and may be 
 * logged by a logging facility.
 */
class IFLogMessage
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// The message.
		std::string message;
		/// Verbosity level.
		Ionflux::ObjectBase::IFVerbosityLevel level;
		/// Source object.
		const Ionflux::ObjectBase::IFObject* source;
		/// Source function name.
		std::string sourceFunctionName;
		
	public:
		/// Verbosity level text: assertion.
		static const std::string TEXT_ASSERTION;
		/// Verbosity level text: silent.
		static const std::string TEXT_SILENT;
		/// Verbosity level text: critical error.
		static const std::string TEXT_ERROR_CRITICAL;
		/// Verbosity level text: error.
		static const std::string TEXT_ERROR;
		/// Verbosity level text: warning.
		static const std::string TEXT_WARNING;
		/// Verbosity level text: optional warning.
		static const std::string TEXT_WARNING_OPT;
		/// Verbosity level text: info.
		static const std::string TEXT_INFO;
		/// Verbosity level text: optional info.
		static const std::string TEXT_INFO_OPT;
		/// Verbosity level text: debug.
		static const std::string TEXT_DEBUG;
		/// Verbosity level text: optional debug.
		static const std::string TEXT_DEBUG_OPT;
		/// Verbosity level text: insane debug.
		static const std::string TEXT_DEBUG_INSANE;
		/// Verbosity level text: all.
		static const std::string TEXT_ALL;
		/// Class information instance.
		static const IFLogMessageClassInfo iFLogMessageClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFLogMessage object.
		 */
		IFLogMessage();
		
		/** Constructor.
		 *
		 * Construct new IFLogMessage object.
		 *
		 * \param initMessage Initial message.
		 * \param initLevel Initial verbosity level.
		 * \param initSource Initial source object.
		 * \param initFunctionName Initial source function name.
		 */
		IFLogMessage(const std::string& initMessage, 
		Ionflux::ObjectBase::IFVerbosityLevel initLevel = 
		Ionflux::ObjectBase::VL_INFO, const Ionflux::ObjectBase::IFObject* 
		initSource = 0, const std::string& initFunctionName = "");
		
		/** Destructor.
		 *
		 * Destruct IFLogMessage object.
		 */
		virtual ~IFLogMessage();
		
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
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Copy of the object.
		 */
		virtual Ionflux::ObjectBase::IFObject* copy() const;
		
		/** Assignment operator.
		 *
		 * Assignment operator.
		 *
		 * \param otherLogMessage LogMessage.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFLogMessage& operator=(const 
		Ionflux::ObjectBase::IFLogMessage& otherLogMessage);
		
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
		
		/** Get string representation of verbosity level.
		 *
		 * Get a string representation of the verbosity level of the message.
		 *
		 * \param otherLevel Verbosity level.
		 *
		 * \return String representation of the verbosity level.
		 */
		static std::string getLevelString(Ionflux::ObjectBase::IFVerbosityLevel 
		otherLevel);
		
		/** Get verbosity level from string representation.
		 *
		 * Get the verbosity level corresponding to the string representation.
		 *
		 * \param levelString Verbosity level string representation.
		 *
		 * \return Verbosity level corresponding to the string representation.
		 */
		static Ionflux::ObjectBase::IFVerbosityLevel getLevelFromString(const 
		std::string& levelString);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation of the object.
		 */
		virtual std::string getString() const;
		
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
		 * \return offset of remaining data, or -1 if an error occured.
		 *
		 * \sa serialize()
		 */
		virtual int deserialize(const std::string& source, int offset = 0);
		
		/** Set the message.
		 *
		 * Set new value of the message.
		 *
		 * \param newMessage New value of the message.
		 */
		virtual void setMessage(const std::string& newMessage);
		
		/** Get the message.
		 *
		 * \return Current value of the message.
		 */
		virtual std::string getMessage() const;
		
		/** Set verbosity level.
		 *
		 * Set new value of verbosity level.
		 *
		 * \param newLevel New value of verbosity level.
		 */
		virtual void setLevel(Ionflux::ObjectBase::IFVerbosityLevel newLevel);
		
		/** Get verbosity level.
		 *
		 * \return Current value of verbosity level.
		 */
		virtual Ionflux::ObjectBase::IFVerbosityLevel getLevel() const;
		
		/** Set source object.
		 *
		 * Set new value of source object.
		 *
		 * \param newSource New value of source object.
		 */
		virtual void setSource(const Ionflux::ObjectBase::IFObject* newSource);
		
		/** Get source object.
		 *
		 * \return Current value of source object.
		 */
		virtual const Ionflux::ObjectBase::IFObject* getSource() const;
		
		/** Set source function name.
		 *
		 * Set new value of source function name.
		 *
		 * \param newSourceFunctionName New value of source function name.
		 */
		virtual void setSourceFunctionName(const std::string& 
		newSourceFunctionName);
		
		/** Get source function name.
		 *
		 * \return Current value of source function name.
		 */
		virtual std::string getSourceFunctionName() const;
};

}

}

/** \file IFLogMessage.hpp
 * \brief Log message (header).
 */
#endif
