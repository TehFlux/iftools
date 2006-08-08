/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoImageSurface.cpp                Cairo image surface.
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

#include "ionflux/CairoImageSurface.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

ImageSurface::ImageSurface()
{
	cairoSurface = 0;
}

ImageSurface::ImageSurface(const ImageSurface& initSurface)
{
	setCairoSurface(initSurface.getCairoSurface());
}

ImageSurface::ImageSurface(cairo_surface_t* initSurface)
{
	setCairoSurface(initSurface);
}

ImageSurface::ImageSurface(cairo_format_t format, int width, int height)
{
	cairoSurface = cairo_image_surface_create(format, width, height);
}

ImageSurface::ImageSurface(unsigned char* data, cairo_format_t format, int 
width, int height, int stride)
{
	cairoSurface = cairo_image_surface_create_for_data(data, 
		format, width, height, stride);
}

ImageSurface::ImageSurface(const std::string& pngFilename)
{
	cairoSurface = cairo_image_surface_create_from_png(pngFilename.c_str());
}

ImageSurface::ImageSurface(cairo_read_func_t pngReadFunc, void* closure)
{
	cairoSurface = cairo_image_surface_create_from_png_stream(pngReadFunc, 
		closure);
}

ImageSurface::~ImageSurface()
{
	if (cairoSurface != 0)
		destroy();
	cairoSurface = 0;
}

cairo_status_t ImageSurface::writeToPng(const std::string& pngFilename)
{
	return cairo_surface_write_to_png(cairoSurface, pngFilename.c_str());
}

cairo_status_t ImageSurface::writeToPngStream(cairo_write_func_t 
write_func, void* closure)
{
	return cairo_surface_write_to_png_stream(cairoSurface, write_func, closure);
}

int ImageSurface::getWidth()
{
	return cairo_image_surface_get_width(cairoSurface);
}

int ImageSurface::getHeight()
{
	return cairo_image_surface_get_height(cairoSurface);
}

ImageSurface& ImageSurface::operator=(const ImageSurface& newCairoSurface)
{
	setCairoSurface(newCairoSurface.getCairoSurface());
	return *this;
}

ImageSurface& ImageSurface::operator=(cairo_surface_t* newCairoSurface)
{
	setCairoSurface(newCairoSurface);
	return *this;
}

}

}

}

/** \file CairoImageSurface.cpp
 * \brief Cairo image surface implementation.
 */
