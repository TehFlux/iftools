/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoGradient.cpp                    Cairo gradient.
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

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

Gradient::Gradient()
{
	cairoPattern = 0;
}

Gradient::Gradient(const Gradient& initGradient)
{
	setCairoPattern(initGradient.getCairoPattern());
}

Gradient::Gradient(cairo_pattern_t* initGradient)
{
	setCairoPattern(initGradient);
}

Gradient::~Gradient()
{
	if (cairoPattern != 0)
		destroy();
	cairoPattern = 0;
}

void Gradient::addColorStopRgb(double offset, double red, double green, 
double blue)
{
	cairo_pattern_add_color_stop_rgb(cairoPattern, offset, red, green, blue);
}

void Gradient::addColorStopRgba(double offset, double red, double green, 
double blue, double alpha)
{
	cairo_pattern_add_color_stop_rgba(cairoPattern, offset, red, green, blue, 
	alpha);
}

void Gradient::addColorStop(double offset, const Ionflux::Tools::Color& 
color)
{
	addColorStopRgba(offset, color.red, color.green, color.blue, color.alpha);
}

Gradient& Gradient::operator=(const Gradient& newCairoPattern)
{
	setCairoPattern(newCairoPattern.getCairoPattern());
	return *this;
}

Gradient& Gradient::operator=(cairo_pattern_t* newCairoPattern)
{
	setCairoPattern(newCairoPattern);
	return *this;
}

}

}

}

/** \file CairoGradient.cpp
 * \brief Cairo gradient implementation.
 */
