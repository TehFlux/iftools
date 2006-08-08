#ifndef IONFLUX_TOOLS_CAIRO_SURFACEPATTERN
#define IONFLUX_TOOLS_CAIRO_SURFACEPATTERN
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoSurfacePattern.hpp                Cairo surface pattern.
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

#include "ionflux/CairoPattern.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** Cairo surface pattern.
 * \ingroup cairo
 *
 * Surface pattern for use with the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class SurfacePattern
: public Pattern
{
	private:
		
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new SurfacePattern object.
		 */
		SurfacePattern();
		
		/** Constructor.
		 *
		 * Construct new SurfacePattern object.
		 *
		 * \param initPattern Cairo surface pattern.
		 */
		SurfacePattern(const SurfacePattern& initPattern);
		
		/** Constructor.
		 *
		 * Construct new SurfacePattern object.
		 *
		 * \param initPattern Cairo surface pattern.
		 */
		SurfacePattern(cairo_pattern_t* initPattern);
		
		/** Constructor.
		 *
		 * Construct new SurfacePattern object.
		 *
		 * \param surface Surface.
		 */
		SurfacePattern(cairo_surface_t* surface);
		
		/** Destructor.
		 *
		 * Destruct SurfacePattern object.
		 */
		virtual ~SurfacePattern();
		
		/** Pattern extend.
		 *
		 * Pattern extend
		 *
		 * \param extend Extend.
		 */
		virtual void setExtend(cairo_extend_t extend);
		
		/** Pattern extend.
		 *
		 * Pattern extend
		 *
		 * \return .
		 */
		virtual cairo_extend_t getExtend();
		
		/** Pattern filter.
		 *
		 * Pattern filter
		 *
		 * \param filter Filter.
		 */
		virtual void setFilter(cairo_filter_t filter);
		
		/** Pattern filter.
		 *
		 * Pattern filter
		 *
		 * \return .
		 */
		virtual cairo_filter_t getFilter();
		
		/** Assignment operator.
		 *
		 * Assign a pattern to another pattern.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual SurfacePattern& operator=(const SurfacePattern& newCairoPattern);
		
		/** Assignment operator.
		 *
		 * Assign a cairo pattern to this pattern object.
		 *
		 * \param newCairoPattern Cairo solid pattern.
		 *
		 * \return The object itself.
		 */
		virtual SurfacePattern& operator=(cairo_pattern_t* newCairoPattern);
};

}

}

}

/** \file CairoSurfacePattern.hpp
 * \brief Cairo surface pattern header.
 */
#endif
