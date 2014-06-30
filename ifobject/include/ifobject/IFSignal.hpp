#ifndef IONFLUX_OBJECT_IFSIGNAL
#define IONFLUX_OBJECT_IFSIGNAL
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFSignal.hpp                    Signal (header).
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

/// Class information for class IFSignal.
class IFSignalClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFSignalClassInfo();
		/// Destructor.
		virtual ~IFSignalClassInfo();
};

/** Signal.
 * \ingroup ifobject
 *
 * A signal. The purpose of this class is to make signals available for 
 * handling by code which is aware of features of the Ionflux Object Base 
 * System, but not of the actual mechanism which is used for implementing 
 * signals.
 */
class IFSignal
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Signal.
		Ionflux::ObjectBase::IFSignalBase signal;
		/// Signal type.
		Ionflux::ObjectBase::IFSignalType type;
		/// Signal name.
		std::string name;
		
	public:
		/// Class information instance.
		static const IFSignalClassInfo iFSignalClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFSignal object.
		 */
		IFSignal();
		
		/** Constructor.
		 *
		 * Construct new IFSignal object.
		 *
		 * \param initSignal Initial signal.
		 * \param initType Initial signal type.
		 * \param initName Initial signal name.
		 */
		IFSignal(Ionflux::ObjectBase::IFSignalBase initSignal, 
		Ionflux::ObjectBase::IFSignalType initType, std::string initName);
		
		/** Destructor.
		 *
		 * Destruct IFSignal object.
		 */
		virtual ~IFSignal();
		
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
		 * \param otherSignal Test module.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFSignal& operator=(const 
		Ionflux::ObjectBase::IFSignal& otherSignal);
		
		/** Assignment operator.
		 *
		 * Assignment operator.
		 *
		 * \param otherObject IFObject.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFObject& operator=(const 
		Ionflux::ObjectBase::IFObject& otherObject);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation of the object.
		 */
		virtual std::string getString() const;
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get signal.
		 *
		 * \return Current value of signal.
		 */
		virtual Ionflux::ObjectBase::IFSignalBase getSignal() const;
		
		/** Get signal type.
		 *
		 * \return Current value of signal type.
		 */
		virtual Ionflux::ObjectBase::IFSignalType getType() const;
		
		/** Get signal name.
		 *
		 * \return Current value of signal name.
		 */
		virtual std::string getName() const;
};

}

}

/** \file IFSignal.hpp
 * \brief Signal (header).
 */
#endif
