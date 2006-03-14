#ifndef IONFLUX_TOOLS_CAIRO_GRADIENT
#define IONFLUX_TOOLS_CAIRO_GRADIENT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoGradient.hpp                      Cairo gradient.
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

/** Cairo gradient.
 * \ingroup cairo
 *
 * Gradient for use with the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class Gradient
: public Pattern
{
	private:
		
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new Gradient object.
		 */
		Gradient();
		
		/** Constructor.
		 *
		 * Construct new Gradient object.
		 *
		 * \param initGradient Cairo gradient.
		 */
		Gradient(const Gradient& initGradient);
		
		/** Constructor.
		 *
		 * Construct new Gradient object.
		 *
		 * \param initGradient Cairo gradient.
		 */
		Gradient(cairo_pattern_t* initGradient);
		
		/** Destructor.
		 *
		 * Destruct Gradient object.
		 */
		virtual ~Gradient();
		
		/** Pattern color stop rgb.
		 *
		 * Pattern color stop rgb
		 *
		 * \param offset Offset.
		 * \param red Red.
		 * \param green Green.
		 * \param blue Blue.
		 */
		virtual void addColorStopRgb(double offset, double red, double green, 
		double blue);
		
		/** Pattern color stop rgba.
		 *
		 * Pattern color stop rgba
		 *
		 * \param offset Offset.
		 * \param red Red.
		 * \param green Green.
		 * \param blue Blue.
		 * \param alpha Alpha.
		 */
		virtual void addColorStopRgba(double offset, double red, double green, 
		double blue, double alpha);
		
		/** Pattern color stop.
		 *
		 * Pattern color stop
		 *
		 * \param offset Offset.
		 * \param color Color.
		 */
		virtual void addColorStop(double offset, const Ionflux::Tools::Color& 
		color);
		
		/** Assignment operator.
		 *
		 * Assign a pattern to another pattern.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual Gradient& operator=(const Gradient& newCairoPattern);
		
		/** Assignment operator.
		 *
		 * Assign a cairo pattern to this pattern object.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual Gradient& operator=(cairo_pattern_t* newCairoPattern);
};

}

}

}

/** \file CairoGradient.hpp
 * \brief Cairo gradient header.
 */
#endif
