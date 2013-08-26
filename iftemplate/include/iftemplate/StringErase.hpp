#ifndef IONFLUX_TEMPLATE_STRINGERASE
#define IONFLUX_TEMPLATE_STRINGERASE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringErase.hpp                 String manipulator: erase (header).
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
#include "iftemplate/StringManipulator.hpp"

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

/// Class information for class StringErase.
class StringEraseClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		StringEraseClassInfo();
		/// Destructor.
		virtual ~StringEraseClassInfo();
};

/** String manipulator: erase.
 * \ingroup iftemplate
 *
 * String manipulator that erases a substring.
 * 
 * erase(s)
 * s - Substring to be erased.
 */
class StringErase
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
	private:
		
	protected:
		
	public:
		/// .
		static const std::string STRINGMANIP_NAME;
		/// Class information instance.
		static const StringEraseClassInfo stringEraseClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new StringErase object.
		 */
		StringErase();
		
		/** Constructor.
		 *
		 * Construct new StringErase object.
		 *
		 * \param other Other object.
		 */
		StringErase(const Ionflux::Template::StringManipulator::StringErase& other);
		
		/** Destructor.
		 *
		 * Destruct StringErase object.
		 */
		virtual ~StringErase();
		
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
		virtual Ionflux::Template::StringManipulator::StringErase& 
		operator=(const Ionflux::Template::StringManipulator::StringErase& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::StringManipulator::StringErase* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::StringManipulator::StringErase* 
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
		static Ionflux::Template::StringManipulator::StringErase* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}

/** \file StringErase.hpp
 * \brief String manipulator: erase (header).
 */
#endif
