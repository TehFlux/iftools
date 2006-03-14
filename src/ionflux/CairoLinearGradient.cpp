/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoLinearGradient.cpp              Cairo linear gradient.
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

#include "ionflux/CairoLinearGradient.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

LinearGradient::LinearGradient()
{
	cairoPattern = 0;
}

LinearGradient::LinearGradient(const LinearGradient& initGradient)
{
	setCairoPattern(initGradient.getCairoPattern());
}

LinearGradient::LinearGradient(cairo_pattern_t* initGradient)
{
	setCairoPattern(initGradient);
}

LinearGradient::LinearGradient(double x0, double y0, double x1, double y1)
{
	cairoPattern = cairo_pattern_create_linear(x0, y0, x1, y1);
}

LinearGradient::~LinearGradient()
{
	if (cairoPattern != 0)
		destroy();
	cairoPattern = 0;
}

LinearGradient& LinearGradient::operator=(const LinearGradient& 
newCairoPattern)
{
	setCairoPattern(newCairoPattern.getCairoPattern());
	return *this;
}

LinearGradient& LinearGradient::operator=(cairo_pattern_t* newCairoPattern)
{
	setCairoPattern(newCairoPattern);
	return *this;
}

}

}

}

/** \file CairoLinearGradient.cpp
 * \brief Cairo linear gradient implementation.
 */
