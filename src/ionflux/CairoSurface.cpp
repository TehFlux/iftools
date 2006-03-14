/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoSurface.cpp                     Cairo surface.
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

#include "ionflux/CairoSurface.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

Surface::Surface()
: cairoSurface(0)
{
	// TODO: Nothing ATM. ;-)
}

Surface::Surface(const Surface& initSurface)
{
	setCairoSurface(initSurface.getCairoSurface());
}

Surface::Surface(cairo_surface_t* initSurface)
{
	setCairoSurface(initSurface);
}

Surface::~Surface()
{
	if (cairoSurface != 0)
		destroy();
	cairoSurface = 0;
}

cairo_surface_t* Surface::createSimilar(cairo_content_t content, int width, 
int height)
{
	return cairo_surface_create_similar(cairoSurface, content, width, height);
}

void Surface::reference()
{
	cairo_surface_reference(cairoSurface);
}

void Surface::destroy()
{
	cairo_surface_destroy(cairoSurface);
}

void Surface::finish()
{
	cairo_surface_finish(cairoSurface);
}

void* Surface::getUserData(const cairo_user_data_key_t* key)
{
	return cairo_surface_get_user_data(cairoSurface, key);
}

cairo_status_t Surface::setUserData(const cairo_user_data_key_t* key, void*
user_data, cairo_destroy_func_t destroy)
{
	return cairo_surface_set_user_data(cairoSurface, key, user_data, destroy);
}

void Surface::setDeviceOffset(double x_offset, double y_offset)
{
	cairo_surface_set_device_offset(cairoSurface, x_offset, y_offset);
}

Surface& Surface::operator=(const Surface& newCairoSurface)
{
	setCairoSurface(newCairoSurface.getCairoSurface());
	return *this;
}

Surface& Surface::operator=(cairo_surface_t* newCairoSurface)
{
	setCairoSurface(newCairoSurface);
	return *this;
}

void Surface::setCairoSurface(cairo_surface_t* newCairoSurface)
{
	if (cairoSurface != 0)
		destroy();
	cairoSurface = newCairoSurface;
	if (cairoSurface != 0)
		reference();
}

cairo_surface_t* Surface::getCairoSurface() const
{
	return cairoSurface;
}

}

}

}

/** \file CairoSurface.cpp
 * \brief Cairo surface implementation.
 */
