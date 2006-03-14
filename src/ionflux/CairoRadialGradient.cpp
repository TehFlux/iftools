/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoRadialGradient.cpp              Cairo radial gradient.
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

#include "ionflux/CairoRadialGradient.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

RadialGradient::RadialGradient()
{
	cairoPattern = 0;
}

RadialGradient::RadialGradient(const RadialGradient& initGradient)
{
	setCairoPattern(initGradient.getCairoPattern());
}

RadialGradient::RadialGradient(cairo_pattern_t* initGradient)
{
	setCairoPattern(initGradient);
}

RadialGradient::RadialGradient(double cx0, double cy0, double radius0, 
double cx1, double cy1, double radius1)
{
	cairoPattern = cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1);
}

RadialGradient::~RadialGradient()
{
	if (cairoPattern != 0)
		destroy();
	cairoPattern = 0;
}

RadialGradient& RadialGradient::operator=(const RadialGradient& 
newCairoPattern)
{
	setCairoPattern(newCairoPattern.getCairoPattern());
	return *this;
}

RadialGradient& RadialGradient::operator=(cairo_pattern_t* newCairoPattern)
{
	setCairoPattern(newCairoPattern);
	return *this;
}

}

}

}

/** \file CairoRadialGradient.cpp
 * \brief Cairo radial gradient implementation.
 */
