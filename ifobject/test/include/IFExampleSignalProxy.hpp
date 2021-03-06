#ifndef IONFLUX_EXAMPLE_IFEXAMPLESIGNALPROXY
#define IONFLUX_EXAMPLE_IFEXAMPLESIGNALPROXY
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFExampleSignalProxy.hpp        Proxy for the 'example' signal (header).
 * =========================================================================
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

#include "test/include/IFExampleClass.hpp"
#include "ifobject/IFSignal.hpp"

namespace Ionflux
{

namespace Example
{

/// Class information for class IFExampleSignalProxy.
class IFExampleSignalProxyClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFExampleSignalProxyClassInfo();
		/// Destructor.
		virtual ~IFExampleSignalProxyClassInfo();
};

/** Proxy for the 'example' signal.
 * \ingroup ifobject
 *
 * Proxy for the 'example' signal. This can be used to connect an object to
 * a signal without knowing anything about the implementation of the signal
 * mechanism.
 */
class IFExampleSignalProxy
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Signal connection.
		sigc::connection signalConnection;
		
	public:
		/// Class information instance.
		static const IFExampleSignalProxyClassInfo iFExampleSignalProxyClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFExampleSignalProxy object.
		 */
		IFExampleSignalProxy();
		
		/** Destructor.
		 *
		 * Destruct IFExampleSignalProxy object.
		 */
		virtual ~IFExampleSignalProxy();
		
		/** Handler for the 'example' signal.
		 *
		 * Handle the 'example' signal. Override this method in a derived 
		 * class to implement custom behavior.
		 *
		 * \param param0 signal parameter #0.
		 */
		virtual void onIFExampleSignal(const Ionflux::Example::IFExampleEvent& 
		param0);
		
		/** Connect signal.
		 *
		 * Connect a signal to the specified action.
		 *
		 * \param target Target signal.
		 * \param action Action to which the signal should be connected.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool connect(Ionflux::ObjectBase::IFSignal* target, int action);
		
		/** Disconnect signal.
		 *
		 * Disconnect the signal.
		 */
		virtual void disconnect();
		
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
		 * \param otherSignalProxy .
		 *
		 * \return The object itself.
		 */
		virtual IFExampleSignalProxy& operator=(const IFExampleSignalProxy& 
		otherSignalProxy);
		
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
};

}

}

/** \file IFExampleSignalProxy.hpp
 * \brief Proxy for the 'example' signal (header).
 */
#endif
