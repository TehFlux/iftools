#ifndef IONFLUX_OBJECT_IFEXAMPLECLASS
#define IONFLUX_OBJECT_IFEXAMPLECLASS
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFExampleClass.hpp              Example class (header).
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

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "ifobject/IFObject.hpp"

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

namespace Example
{

// events used by IFExampleClass
class IFExampleEvent;

typedef std::map<int, int> FooMap;
typedef sigc::signal<void, const Ionflux::Example::IFExampleEvent&> 
IFExampleSignal;
 
/** A blupp object.
 * \ingroup ifobject
 */
struct Blupp
{
	/// Foo value.
	int foo;
	/// Bar value.
	int bar;
};
 
/** A blah object.
 * \ingroup ifobject
 */
struct Blah
{
	/// Baz value.
	double baz;
	/// Baf value.
	double baf;
	/// Some flag.
	static const int SOME_FLAG;
};

/// Signal connections for IFExampleSignal.
struct IFExampleSignalConnections
{
	/// Signal connection: first signal
	sigc::connection signalFirstConnection;
	/// Signal connection: second signal
	sigc::connection signalSecondConnection;
};

/// Class information for class IFExampleClass.
class IFExampleClassClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFExampleClassClassInfo();
		/// Destructor.
		virtual ~IFExampleClassClassInfo() { };
};

/** Example class.
 * \ingroup ifobject
 *
 * This is an example class used to demonstrate features of the Ionflux 
 * Object Base System.
 */
class IFExampleClass
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Miepness of the object.
		double miep;
		/// Some numeric value.
		int someValue;
		/// Some byte string.
		std::string someText;
		/// A read-only property.
		double roProp;
		/// Special Blah object.
		Blah* specialBlah;
		/// Blupp vector.
		std::vector<Blupp*> blupps;
		/// Blah map.
		std::map<std::string, Blah*> blahs;
		/// Signal: first signal.
		IFExampleSignal signalFirst;
		/// Signal wrapper: first signal.
		Ionflux::ObjectBase::IFSignal* signalFirstWrapper;
		/// Signal: second signal.
		IFExampleSignal signalSecond;
		/// Signal wrapper: second signal.
		Ionflux::ObjectBase::IFSignal* signalSecondWrapper;
		/// Unique ID.
		static const std::string SOME_UID;
		
		/** Do stuff..
		 *
		 * Does some stuff.
		 *
		 * \param foo A number to do stuff with.
		 * \param bar A character to do stuff with.
		 *
		 * \return The result of doing stuff.
		 */
		virtual int doStuff(int foo, char bar = 'x');
		
	public:
		/// Module name.
		static const std::string MODULE_NAME;
		/// Module version.
		static const unsigned int MODULE_VERSION;
		/// Signal type: example.
		static const SignalType SIGNAL_TYPE_EXAMPLE;
		/// Signal name: first.
		static const std::string SIGNAL_NAME_FIRST;
		/// Signal name: second.
		static const std::string SIGNAL_NAME_SECOND;
		
		/** Constructor.
		 *
		 * Construct new IFExampleClass object.
		 */
		IFExampleClass();
		
		/** Constructor.
		 *
		 * Construct new IFExampleClass object.
		 *
		 * \param initMiep Initial miepness.
		 */
		IFExampleClass(double initMiep);
		
		/** Destructor.
		 *
		 * Destruct IFExampleClass object.
		 */
		virtual ~IFExampleClass();
		
		/** Create event: example.
		 * 
		 * Create and initialize a 'example' event.
		 * 
		 * \return New event, or 0 if an error occured.
		 */
		IFExampleEvent* createExampleEvent();
		
		/** Do nothing..
		 *
		 * Does nothing.
		 */
		virtual void doNothing() const;
		
		/** Needs implementation..
		 *
		 * This function must be implemented by a derived class.
		 */
		virtual void needsImplementation() = 0;
		
		/** Set some numeric value.
		 *
		 * Set new value of some numeric value.
		 *
		 * \param newSomeValue New value of some numeric value.
		 */
		virtual void setSomeValue(int newSomeValue);
		
		/** Get some numeric value.
		 *
		 * \return Current value of some numeric value.
		 */
		virtual int getSomeValue() const;
		
		/** Set some byte string.
		 *
		 * Set new value of some byte string.
		 *
		 * \param newSomeText New value of some byte string.
		 */
		virtual void setSomeText(const std::string& newSomeText);
		
		/** Get some byte string.
		 *
		 * \return Current value of some byte string.
		 */
		virtual std::string getSomeText() const;
		
		/** Get a read-only property.
		 *
		 * \return Current value of a read-only property.
		 */
		virtual double getRoProp() const;
		
		/** Set special Blah object.
		 *
		 * Set new value of special Blah object.
		 *
		 * \param newSpecialBlah New value of special Blah object.
		 */
		virtual void setSpecialBlah(Blah* newSpecialBlah);
		
		/** Get special Blah object.
		 *
		 * \return Current value of special Blah object.
		 */
		virtual Blah* getSpecialBlah() const;
		
		/** Get number of blupps.
		 *
		 * \return Number of blupps.
		 */
		virtual unsigned int getNumBlupps() const;
		
		/** Get blupp.
		 *
		 * Get the blupp at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Blupp at specified index.
		 */
		virtual Blupp* getBlupp(unsigned int elementIndex = 0) const;
		
		/** Get blupp vector.
		 *
		 * \return blupp vector.
		 */
		virtual std::vector<Blupp*>& getBlupps();
		
		/** Add blupp.
		 *
		 * Add a blupp.
		 *
		 * \param addElement Blupp to be added.
		 */
		virtual void addBlupp(Blupp* addElement);
		
		/** Remove blupp.
		 *
		 * Remove a blupp.
		 *
		 * \param removeElement Blupp to be removed.
		 */
		virtual void removeBlupp(Blupp* removeElement);
		
		/** Clear blupps.
		 *
		 * Clear all blupps.
		 */
		virtual void clearBlupps();
		
		/** Get number of blahs.
		 *
		 * \return Number of blahs.
		 */
		virtual unsigned int getNumBlahs() const;
		
		/** Get blah.
		 *
		 * Get the blah with the specified key.
		 *
		 * \param elementKey Element key.
		 *
		 * \return Blah with specified key.
		 */
		virtual Blah* getBlah(const std::string& elementKey) const;
		
		/** Get blah map.
		 *
		 * \return blah map.
		 */
		virtual std::map<std::string, Blah*>& getBlahs();
		
		/** Add blah.
		 *
		 * Add a blah.
		 *
		 * \param elementKey Element key.
		 * \param addElement Blah to be added.
		 */
		virtual void addBlah(const std::string& elementKey, Blah* addElement);
		
		/** Remove blah.
		 *
		 * Remove the blah with the specified key.
		 *
		 * \param elementKey Element key.
		 */
		virtual void removeBlah(const std::string& elementKey);
		
		/** Clear blahs.
		 *
		 * Clear all blahs.
		 */
		virtual void clearBlahs();
		
		/** Get signal: first signal.
		 *
		 * Get the signal for the first signal event.
		 *
		 * \return Signal for the first signal event.
		 */
		virtual IFExampleSignal& getSignalFirst();
		
		/** Get signal wrapper: first signal.
		 *
		 * Get the signal for the first signal event.
		 *
		 * \return Signal for the first signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalFirstWrapper();

		
		/** Get signal: second signal.
		 *
		 * Get the signal for the second signal event.
		 *
		 * \return Signal for the second signal event.
		 */
		virtual IFExampleSignal& getSignalSecond();
		
		/** Get signal wrapper: second signal.
		 *
		 * Get the signal for the second signal event.
		 *
		 * \return Signal for the second signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalSecondWrapper();

};

}

}

/** \file IFExampleClass.hpp
 * \brief Example class (header).
 */
#endif
