#ifndef IONFLUX_TOOLS_GTKCAIROAREA
#define IONFLUX_TOOLS_GTKCAIROAREA
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * GtkCairoArea.hpp                  GTK+/Cairo drawing area.
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

#include "gtkmm/drawingarea.h"
#include "gdk/gdkx.h"
#include "ionflux/ObjectPool.hpp"
#include "ionflux/CairoCanvas.hpp"

namespace Ionflux
{

namespace Tools
{

/** GTK+/Cairo drawing area.
 * \ingroup general
 *
 * A drawing area for GTK+ using Cairo.
 */
class GtkCairoArea
: public Gtk::DrawingArea
{
	private:
		
	protected:
		/// Object pool.
		ObjectPool pool;
		/// Graphics context.
		Glib::RefPtr<Gdk::GC> theGC;
		/// Color: black.
		Gdk::Color black;
		/// Cairo canvas.
		Ionflux::Tools::CairoCanvas* cairoCanvas;
		
		/** Event handler: realize.
		 *
		 * Handler for the realize event.
		 */
		virtual void on_realize();
		
		/** Event handler: expose.
		 *
		 * Handler for the expose event.
		 *
		 * \param event Event.
		 */
		virtual bool on_expose_event(GdkEventExpose* event);
		
		/** Paint widget.
		 *
		 * Paint the widget.
		 */
		virtual bool paint();
		
	public:
		/** Constructor.
		 *
		 * Construct new GtkCairoArea object.
		 */
		GtkCairoArea();
		
		/** Constructor.
		 *
		 * Construct new GtkCairoArea object.
		 *
		 * \param initCairoCanvas Cairo canvas.
		 */
		GtkCairoArea(CairoCanvas* initCairoCanvas);
		
		/** Destructor.
		 *
		 * Destruct GtkCairoArea object.
		 */
		virtual ~GtkCairoArea();
		
		/** Set cairo canvas.
		 *
		 * Set new value of cairo canvas.
		 *
		 * \param newCairoCanvas New value of cairo canvas.
		 */
		virtual void setCairoCanvas(Ionflux::Tools::CairoCanvas* newCairoCanvas);
		
		/** Get cairo canvas.
		 *
		 * \return Current value of cairo canvas.
		 */
		virtual Ionflux::Tools::CairoCanvas* getCairoCanvas() const;
};

}

}

/** \file GtkCairoArea.hpp
 * \brief GTK+/Cairo drawing area header.
 */
#endif
