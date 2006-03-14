#ifndef IONFLUX_TOOLS_CAIRO_RADIALGRADIENT
#define IONFLUX_TOOLS_CAIRO_RADIALGRADIENT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoRadialGradient.hpp                Cairo radial gradient.
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

/** Cairo radial gradient.
 * \ingroup cairo
 *
 * Radial gradient for use with the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class RadialGradient
: public Gradient
{
	private:
		
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new RadialGradient object.
		 */
		RadialGradient();
		
		/** Constructor.
		 *
		 * Construct new RadialGradient object.
		 *
		 * \param initGradient Cairo radial gradient.
		 */
		RadialGradient(const RadialGradient& initGradient);
		
		/** Constructor.
		 *
		 * Construct new RadialGradient object.
		 *
		 * \param initGradient Cairo radial gradient.
		 */
		RadialGradient(cairo_pattern_t* initGradient);
		
		/** Constructor.
		 *
		 * Construct new RadialGradient object.
		 *
		 * \param cx0 Cx0.
		 * \param cy0 Cy0.
		 * \param radius0 Radius0.
		 * \param cx1 Cx1.
		 * \param cy1 Cy1.
		 * \param radius1 Radius1.
		 */
		RadialGradient(double cx0, double cy0, double radius0, double cx1, double
		cy1, double radius1);
		
		/** Destructor.
		 *
		 * Destruct RadialGradient object.
		 */
		virtual ~RadialGradient();
		
		/** Assignment operator.
		 *
		 * Assign a pattern to another pattern.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual RadialGradient& operator=(const RadialGradient& newCairoPattern);
		
		/** Assignment operator.
		 *
		 * Assign a cairo pattern to this pattern object.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual RadialGradient& operator=(cairo_pattern_t* newCairoPattern);
};

}

}

}

/** \file CairoRadialGradient.hpp
 * \brief Cairo radial gradient header.
 */
#endif
