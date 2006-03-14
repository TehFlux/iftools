/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoSolidPattern.cpp                Cairo solid pattern.
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

#include "ionflux/CairoSolidPattern.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

SolidPattern::SolidPattern()
{
	cairoPattern = 0;
}

SolidPattern::SolidPattern(const SolidPattern& initPattern)
{
	setCairoPattern(initPattern.getCairoPattern());
}

SolidPattern::SolidPattern(cairo_pattern_t* initPattern)
{
	setCairoPattern(initPattern);
}

SolidPattern::SolidPattern(const Ionflux::Tools::Color& color)
{
	cairoPattern = cairo_pattern_create_rgba(color.red, color.green, 
		color.blue, color.alpha);
}

SolidPattern::SolidPattern(double red, double green, double blue)
{
	cairoPattern = cairo_pattern_create_rgb(red, green, blue);
}

SolidPattern::SolidPattern(double red, double green, double blue, double 
alpha)
{
	cairoPattern = cairo_pattern_create_rgba(red, green, blue, alpha);
}

SolidPattern::~SolidPattern()
{
	if (cairoPattern != 0)
		destroy();
	cairoPattern = 0;
}

SolidPattern& SolidPattern::operator=(const SolidPattern& newCairoPattern)
{
	setCairoPattern(newCairoPattern.getCairoPattern());
	return *this;
}

SolidPattern& SolidPattern::operator=(cairo_pattern_t* newCairoPattern)
{
	setCairoPattern(newCairoPattern);
	return *this;
}

}

}

}

/** \file CairoSolidPattern.cpp
 * \brief Cairo solid pattern implementation.
 */
