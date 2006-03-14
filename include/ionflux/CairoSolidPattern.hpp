#ifndef IONFLUX_TOOLS_CAIRO_SOLIDPATTERN
#define IONFLUX_TOOLS_CAIRO_SOLIDPATTERN
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoSolidPattern.hpp                  Cairo solid pattern.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/color.hpp"
#include "ionflux/CairoPattern.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** Cairo solid pattern.
 * \ingroup cairo
 *
 * Solid pattern for use with the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class SolidPattern
: public Pattern
{
	private:
		
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new SolidPattern object.
		 */
		SolidPattern();
		
		/** Constructor.
		 *
		 * Construct new SolidPattern object.
		 *
		 * \param initPattern Cairo solid pattern.
		 */
		SolidPattern(const SolidPattern& initPattern);
		
		/** Constructor.
		 *
		 * Construct new SolidPattern object.
		 *
		 * \param initPattern Cairo solid pattern.
		 */
		SolidPattern(cairo_pattern_t* initPattern);
		
		/** Constructor.
		 *
		 * Construct new SolidPattern object.
		 *
		 * \param color Color.
		 */
		SolidPattern(const Ionflux::Tools::Color& color);
		
		/** Constructor.
		 *
		 * Construct new SolidPattern object.
		 *
		 * \param red Red.
		 * \param green Green.
		 * \param blue Blue.
		 */
		SolidPattern(double red, double green, double blue);
		
		/** Constructor.
		 *
		 * Construct new SolidPattern object.
		 *
		 * \param red Red.
		 * \param green Green.
		 * \param blue Blue.
		 * \param alpha Alpha.
		 */
		SolidPattern(double red, double green, double blue, double alpha);
		
		/** Destructor.
		 *
		 * Destruct SolidPattern object.
		 */
		virtual ~SolidPattern();
		
		/** Assignment operator.
		 *
		 * Assign a pattern to another pattern.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual SolidPattern& operator=(const SolidPattern& newCairoPattern);
		
		/** Assignment operator.
		 *
		 * Assign a cairo pattern to this pattern object.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual SolidPattern& operator=(cairo_pattern_t* newCairoPattern);
};

}

}

}

/** \file CairoSolidPattern.hpp
 * \brief Cairo solid pattern header.
 */
#endif
