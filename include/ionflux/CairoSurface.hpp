#ifndef IONFLUX_TOOLS_CAIRO_SURFACE
#define IONFLUX_TOOLS_CAIRO_SURFACE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoSurface.hpp                       Cairo surface.
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

#include "cairo.h"
#include "ionflux/ManagedObject.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** Cairo surface.
 * \ingroup cairo
 *
 * Base class for the Cairo vector graphics API surface types (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class Surface
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Cairo surface.
		cairo_surface_t* cairoSurface;
		
	public:
		/** Constructor.
		 *
		 * Construct new Surface object.
		 */
		Surface();
		
		/** Constructor.
		 *
		 * Construct new Surface object.
		 *
		 * \param initSurface Cairo surface.
		 */
		Surface(const Surface& initSurface);
		
		/** Constructor.
		 *
		 * Construct new Surface object.
		 *
		 * \param initSurface Cairo surface.
		 */
		Surface(cairo_surface_t* initSurface);
		
		/** Destructor.
		 *
		 * Destruct Surface object.
		 */
		virtual ~Surface();
		
		/** Surface similar.
		 *
		 * Surface similar
		 *
		 * \param content Content.
		 * \param width Width.
		 * \param height Height.
		 *
		 * \return .
		 */
		virtual cairo_surface_t* createSimilar(cairo_content_t content, 
		int width, int height);
		
		/** Surface.
		 *
		 * Surface
		 */
		virtual void reference();
		
		/** Surface.
		 *
		 * Surface
		 */
		virtual void destroy();
		
		/** Surface.
		 *
		 * Surface
		 */
		virtual void finish();
		
		/** Surface user data.
		 *
		 * Surface user data
		 *
		 * \param key Key.
		 *
		 * \return .
		 */
		virtual void* getUserData(const cairo_user_data_key_t* key);
		
		/** Surface user data.
		 *
		 * Surface user data
		 *
		 * \param key Key.
		 * \param user_data User_data.
		 * \param destroy Destroy.
		 *
		 * \return .
		 */
		virtual cairo_status_t setUserData(const cairo_user_data_key_t* key, 
		void* user_data, cairo_destroy_func_t destroy);
		
		/** Surface device offset.
		 *
		 * Surface device offset
		 *
		 * \param x_offset X_offset.
		 * \param y_offset Y_offset.
		 */
		virtual void setDeviceOffset(double x_offset, double y_offset);
		
		/** Assignment operator.
		 *
		 * Assign a surface to another surface.
		 *
		 * \param newCairoSurface Cairo surface.
		 *
		 * \return The object itself.
		 */
		virtual Surface& operator=(const Surface& newCairoSurface);
		
		/** Assignment operator.
		 *
		 * Assign a cairo surface to this surface object.
		 *
		 * \param newCairoSurface Cairo surface.
		 *
		 * \return The object itself.
		 */
		virtual Surface& operator=(cairo_surface_t* newCairoSurface);
		
		/** Set cairo surface.
		 *
		 * Set new value of cairo surface.
		 *
		 * \param newCairoSurface New value of cairo surface.
		 */
		virtual void setCairoSurface(cairo_surface_t* newCairoSurface);
		
		/** Get cairo surface.
		 *
		 * \return Current value of cairo surface.
		 */
		virtual cairo_surface_t* getCairoSurface() const;
};

}

}

}

/** \file CairoSurface.hpp
 * \brief Cairo surface header.
 */
#endif
