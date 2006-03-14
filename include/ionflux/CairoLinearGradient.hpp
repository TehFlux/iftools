#ifndef IONFLUX_TOOLS_CAIRO_LINEARGRADIENT
#define IONFLUX_TOOLS_CAIRO_LINEARGRADIENT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoLinearGradient.hpp                Cairo linear gradient.
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

#include "ionflux/CairoGradient.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** Cairo linear gradient.
 * \ingroup cairo
 *
 * Linear gradient for use with the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class LinearGradient
: public Gradient
{
	private:
		
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new LinearGradient object.
		 */
		LinearGradient();
		
		/** Constructor.
		 *
		 * Construct new LinearGradient object.
		 *
		 * \param initGradient Cairo linear gradient.
		 */
		LinearGradient(const LinearGradient& initGradient);
		
		/** Constructor.
		 *
		 * Construct new LinearGradient object.
		 *
		 * \param initGradient Cairo linear gradient.
		 */
		LinearGradient(cairo_pattern_t* initGradient);
		
		/** Constructor.
		 *
		 * Construct new LinearGradient object.
		 *
		 * \param x0 X0.
		 * \param y0 Y0.
		 * \param x1 X1.
		 * \param y1 Y1.
		 */
		LinearGradient(double x0, double y0, double x1, double y1);
		
		/** Destructor.
		 *
		 * Destruct LinearGradient object.
		 */
		virtual ~LinearGradient();
		
		/** Assignment operator.
		 *
		 * Assign a pattern to another pattern.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual LinearGradient& operator=(const LinearGradient& newCairoPattern);
		
		/** Assignment operator.
		 *
		 * Assign a cairo pattern to this pattern object.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual LinearGradient& operator=(cairo_pattern_t* newCairoPattern);
};

}

}

}

/** \file CairoLinearGradient.hpp
 * \brief Cairo linear gradient header.
 */
#endif
