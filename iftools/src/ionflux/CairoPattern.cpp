/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoPattern.cpp                     Cairo pattern.
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

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

Pattern::Pattern()
: cairoPattern(0)
{
	// TODO: Nothing ATM. ;-)
}

Pattern::Pattern(const Pattern& initPattern)
{
	setCairoPattern(initPattern.getCairoPattern());
}

Pattern::Pattern(cairo_pattern_t* initPattern)
{
	setCairoPattern(initPattern);
}

Pattern::~Pattern()
{
	if (cairoPattern != 0)
		destroy();
	cairoPattern = 0;
}

void Pattern::reference()
{
	cairo_pattern_reference(cairoPattern);
}

void Pattern::destroy()
{
	cairo_pattern_destroy(cairoPattern);
}

cairo_status_t Pattern::status()
{
	return cairo_pattern_status(cairoPattern);
}

void Pattern::setMatrix(const cairo_matrix_t* matrix)
{
	cairo_pattern_set_matrix(cairoPattern, matrix);
}

void Pattern::getMatrix(cairo_matrix_t* matrix)
{
	cairo_pattern_get_matrix(cairoPattern, matrix);
}

void Pattern::setMatrix(const Matrix& matrix)
{
	cairo_matrix_t cairoMatrix;
	matrix.toCairoMatrix(cairoMatrix);
	setMatrix(&cairoMatrix);
}

void Pattern::getMatrix(Matrix& matrix)
{
	cairo_matrix_t cairoMatrix;
	getMatrix(&cairoMatrix);
	matrix = cairoMatrix;
}

Pattern& Pattern::operator=(const Pattern& newCairoPattern)
{
	setCairoPattern(newCairoPattern.getCairoPattern());
	return *this;
}

Pattern& Pattern::operator=(cairo_pattern_t* newCairoPattern)
{
	setCairoPattern(newCairoPattern);
	return *this;
}

void Pattern::setCairoPattern(cairo_pattern_t* newCairoPattern)
{
	if (cairoPattern != 0)
		destroy();
	cairoPattern = newCairoPattern;
	if (cairoPattern != 0)
		reference();
}

cairo_pattern_t* Pattern::getCairoPattern() const
{
	return cairoPattern;
}

}

}

}

/** \file CairoPattern.cpp
 * \brief Cairo pattern implementation.
 */
