/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Canvas.cpp                      Drawing canvas.
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

#include "ionflux/Canvas.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

Canvas::Canvas()
{
	// TODO: Nothing ATM. ;-)
}

Canvas::~Canvas()
{
	// TODO: Nothing ATM. ;-)
}

void Canvas::setDefaultStrokeColor(const Color& newDefaultStrokeColor)
{
	defaultStrokeColor = newDefaultStrokeColor;
}

void Canvas::setDefaultFillColor(const Color& newDefaultFillColor)
{
	defaultFillColor = newDefaultFillColor;
}

void Canvas::setDefaultStrokeWidth(double newDefaultStrokeWidth)
{
	defaultStrokeWidth = newDefaultStrokeWidth;
}

void Canvas::setDefaultFontFamily(const std::string& newDefaultFontFamily)
{
	defaultFontFamily = newDefaultFontFamily;
}

void Canvas::setDefaultFontSize(double newDefaultFontSize)
{
	defaultFontSize = newDefaultFontSize;
}

void Canvas::setDefaultTransform(Matrix3* newDefaultTransform)
{
	defaultTransform = newDefaultTransform;
}

Color Canvas::getDefaultStrokeColor() const
{
	return defaultStrokeColor;
}

Color Canvas::getDefaultFillColor() const
{
	return defaultFillColor;
}

double Canvas::getDefaultStrokeWidth() const
{
	return defaultStrokeWidth;
}

std::string Canvas::getDefaultFontFamily() const
{
	return defaultFontFamily;
}

double Canvas::getDefaultFontSize() const
{
	return defaultFontSize;
}

Matrix3* Canvas::getDefaultTransform() const
{
	return defaultTransform;
}

}

}

/** \file Canvas.cpp
 * \brief Drawing canvas implementation.
 */
