#ifndef IONFLUX_TEMPLATE_STRINGMANIPULATOR
#define IONFLUX_TEMPLATE_STRINGMANIPULATOR
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringManipulator.hpp           String manipulator (header).
 * =========================================================================
 * 
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

/// Class information for class StringManipulator.
class StringManipulatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		StringManipulatorClassInfo();
		/// Destructor.
		virtual ~StringManipulatorClassInfo();
};

/** String manipulator.
 * \ingroup iftemplate
 *
 * This is an abstract base class to encapsulate an object that manipulates
 * byte strings (i.e. generates one string from another string). String 
 * manipulators can thus be used as function objects for constructing 
 * string filters.
 * 
 * Each string manipulator should have an unique name by which it can be 
 * identified in a set of string manipulators. This name can be obtained 
 * with the getName() function.
 */
class StringManipulator
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const StringManipulatorClassInfo stringManipulatorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new StringManipulator object.
		 */
		StringManipulator();
		
		/** Constructor.
		 *
		 * Construct new StringManipulator object.
		 *
		 * \param other Other object.
		 */
		StringManipulator(const Ionflux::Template::StringManipulator::StringManipulator& other);
		
		/** Destructor.
		 *
		 * Destruct StringManipulator object.
		 */
		virtual ~StringManipulator();
		
		/** Process byte string.
		 *
		 * Process a byte string.
		 *
		 * \param bytes input bytes.
		 * \param args arguments.
		 *
		 * \return Result of applying the string manipulator to the input bytes.
		 */
		virtual std::string process(const std::string& bytes, 
		Ionflux::ObjectBase::StringVector* args = 0);
		
		/** Process byte string.
		 *
		 * Process a byte string.
		 *
		 * \param bytes input bytes.
		 * \param args arguments.
		 *
		 * \return Result of applying the string manipulator to the input bytes.
		 */
		virtual std::string operator()(const std::string& bytes, 
		Ionflux::ObjectBase::StringVector* args = 0);
		
		/** Get string manipulator name.
		 *
		 * Get the name of the string manipulator.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getManipName();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::StringManipulator::StringManipulator& 
		operator=(const Ionflux::Template::StringManipulator::StringManipulator& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::StringManipulator::StringManipulator* copy() 
		const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::StringManipulator::StringManipulator* 
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
		static Ionflux::Template::StringManipulator::StringManipulator* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}

/** \file StringManipulator.hpp
 * \brief String manipulator (header).
 */
#endif
