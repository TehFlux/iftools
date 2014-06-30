#ifndef IONFLUX_TEMPLATE_CHARTYPEMAP
#define IONFLUX_TEMPLATE_CHARTYPEMAP
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CharTypeMap.hpp                 Character type lookup map (header).
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

#include "iftemplate/types.hpp"
#include "iftemplate/TokenTypeMap.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class CharTypeMap.
class CharTypeMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CharTypeMapClassInfo();
		/// Destructor.
		virtual ~CharTypeMapClassInfo();
};

/** Character type lookup map.
 * \ingroup iftemplate
 *
 * A lookup map for mapping bytes to character types.
 */
class CharTypeMap
: public Ionflux::Template::TokenTypeMap
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const CharTypeMapClassInfo charTypeMapClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new CharTypeMap object.
		 */
		CharTypeMap();
		
		/** Constructor.
		 *
		 * Construct new CharTypeMap object.
		 *
		 * \param other Other object.
		 */
		CharTypeMap(const Ionflux::Template::CharTypeMap& other);
		
		/** Destructor.
		 *
		 * Destruct CharTypeMap object.
		 */
		virtual ~CharTypeMap();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::CharTypeMap& operator=(const 
		Ionflux::Template::CharTypeMap& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::CharTypeMap* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::CharTypeMap* 
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
		static Ionflux::Template::CharTypeMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file CharTypeMap.hpp
 * \brief Character type lookup map (header).
 */
#endif
