/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoSurfacePattern.cpp              Cairo surface pattern.
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

#include "ionflux/CairoSurfacePattern.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

SurfacePattern::SurfacePattern()
{
	cairoPattern = 0;
}

SurfacePattern::SurfacePattern(const SurfacePattern& initPattern)
{
	setCairoPattern(initPattern.getCairoPattern());
}

SurfacePattern::SurfacePattern(cairo_pattern_t* initPattern)
{
	setCairoPattern(initPattern);
}

SurfacePattern::SurfacePattern(cairo_surface_t* surface)
{
	cairoPattern = cairo_pattern_create_for_surface(surface);
}

SurfacePattern::~SurfacePattern()
{
	if (cairoPattern != 0)
		destroy();
	cairoPattern = 0;
}

void SurfacePattern::setExtend(cairo_extend_t extend)
{
	cairo_pattern_set_extend(cairoPattern, extend);
}

cairo_extend_t SurfacePattern::getExtend()
{
	return cairo_pattern_get_extend(cairoPattern);
}

void SurfacePattern::setFilter(cairo_filter_t filter)
{
	cairo_pattern_set_filter(cairoPattern, filter);
}

cairo_filter_t SurfacePattern::getFilter()
{
	return cairo_pattern_get_filter(cairoPattern);
}

SurfacePattern& SurfacePattern::operator=(const SurfacePattern& 
newCairoPattern)
{
	setCairoPattern(newCairoPattern.getCairoPattern());
	return *this;
}

SurfacePattern& SurfacePattern::operator=(cairo_pattern_t* newCairoPattern)
{
	setCairoPattern(newCairoPattern);
	return *this;
}

}

}

}

/** \file CairoSurfacePattern.cpp
 * \brief Cairo surface pattern implementation.
 */
