#ifndef IONFLUX_TOOLS_CAIRO_IMAGESURFACE
#define IONFLUX_TOOLS_CAIRO_IMAGESURFACE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoImageSurface.hpp                  Cairo image surface.
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

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** Cairo image surface.
 * \ingroup cairo
 *
 * Image surface for the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class ImageSurface
: public Surface
{
	private:
		
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new ImageSurface object.
		 */
		ImageSurface();
		
		/** Constructor.
		 *
		 * Construct new ImageSurface object.
		 *
		 * \param initSurface Cairo image surface.
		 */
		ImageSurface(const ImageSurface& initSurface);
		
		/** Constructor.
		 *
		 * Construct new ImageSurface object.
		 *
		 * \param initSurface Cairo image surface.
		 */
		ImageSurface(cairo_surface_t* initSurface);
		
		/** Constructor.
		 *
		 * Construct new ImageSurface object.
		 *
		 * \param format Format.
		 * \param width Width.
		 * \param height Height.
		 */
		ImageSurface(cairo_format_t format, int width, int height);
		
		/** Constructor.
		 *
		 * Construct new ImageSurface object.
		 *
		 * \param data Data.
		 * \param format Format.
		 * \param width Width.
		 * \param height Height.
		 * \param stride Stride.
		 */
		ImageSurface(unsigned char* data, cairo_format_t format, int width, int 
		height, int stride);
		
		/** Constructor.
		 *
		 * Construct new ImageSurface object.
		 *
		 * \param pngFilename Filename of a PNG file.
		 */
		ImageSurface(const std::string& pngFilename);
		
		/** Constructor.
		 *
		 * Construct new ImageSurface object.
		 *
		 * \param pngReadFunc Read function for PNG stream.
		 * \param closure Closure.
		 */
		ImageSurface(cairo_read_func_t pngReadFunc, void* closure);
		
		/** Destructor.
		 *
		 * Destruct ImageSurface object.
		 */
		virtual ~ImageSurface();
		
		/** Write to png.
		 *
		 * Write to png
		 *
		 * \param pngFilename Filename of a PNG file.
		 *
		 * \return .
		 */
		virtual cairo_status_t writeToPng(const std::string& pngFilename);
		
		/** Write to png stream.
		 *
		 * Write to png stream
		 *
		 * \param write_func Write_func.
		 * \param closure Closure.
		 *
		 * \return .
		 */
		virtual cairo_status_t writeToPngStream(cairo_write_func_t write_func, 
		void* closure);
		
		/** Get width.
		 *
		 * Get width
		 *
		 * \return .
		 */
		virtual int getWidth();
		
		/** Get height.
		 *
		 * Get height
		 *
		 * \return .
		 */
		virtual int getHeight();
		
		/** Assignment operator.
		 *
		 * Assign a surface to another surface.
		 *
		 * \param newCairoSurface Cairo image surface.
		 *
		 * \return The object itself.
		 */
		virtual ImageSurface& operator=(const ImageSurface& newCairoSurface);
		
		/** Assignment operator.
		 *
		 * Assign a cairo surface to this surface object.
		 *
		 * \param newCairoSurface Cairo image surface.
		 *
		 * \return The object itself.
		 */
		virtual ImageSurface& operator=(cairo_surface_t* newCairoSurface);
};

}

}

}

/** \file CairoImageSurface.hpp
 * \brief Cairo image surface header.
 */
#endif
