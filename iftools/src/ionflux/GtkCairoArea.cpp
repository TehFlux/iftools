/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * GtkCairoArea.cpp                GTK+/Cairo drawing area.
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

#include "ionflux/GtkCairoArea.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

GtkCairoArea::GtkCairoArea()
: cairoCanvas(0)
{
	cairoCanvas = new CairoCanvas();
	if (cairoCanvas != 0)
	{
		cairoCanvas->ref();
		pool.addObject(cairoCanvas);
	}
}

GtkCairoArea::GtkCairoArea(CairoCanvas* initCairoCanvas)
: cairoCanvas(0)
{
	if (initCairoCanvas != 0)
	{
		cairoCanvas = initCairoCanvas;
		cairoCanvas->ref();
		pool.addObject(cairoCanvas);
	}
}

GtkCairoArea::~GtkCairoArea()
{
	if (cairoCanvas != 0)
		cairoCanvas->unref();
	cairoCanvas = 0;
}

void GtkCairoArea::on_realize()
{
	Gtk::DrawingArea::on_realize();
	Glib::RefPtr<Gdk::Colormap> colormap = get_default_colormap();
	black = Gdk::Color("black");
	colormap->alloc_color(black);
	Glib::RefPtr<Gdk::Window> window = get_window();
	window->set_background(black);
	window->clear();
}

bool GtkCairoArea::on_expose_event(GdkEventExpose* event)
{
	bool result;
	gint xOffset;
	gint yOffset;
	Glib::RefPtr<Gdk::Window> window = get_window();
	GdkWindow* gdkWindow = window->gobj();
	GdkDrawable* gdkDrawable;
	gdk_window_get_internal_paint_info(gdkWindow, &gdkDrawable,
		&xOffset, &yOffset);
	cairo_t* cairo = gdk_cairo_create(gdkDrawable);
	cairoCanvas->setCairoContext(cairo);
	result = paint();
	cairo_destroy(cairo);
	return result;
}

bool GtkCairoArea::paint()
{
	// TODO: Nothing ATM. ;-)
	return true;
}

void GtkCairoArea::setCairoCanvas(Ionflux::Tools::CairoCanvas* 
newCairoCanvas)
{
	if (cairoCanvas != 0)
		cairoCanvas->unref();
	cairoCanvas = newCairoCanvas;
	if (cairoCanvas != 0)
	{
		cairoCanvas->ref();
		pool.addObject(cairoCanvas);
	}
}

Ionflux::Tools::CairoCanvas* GtkCairoArea::getCairoCanvas() const
{
	return cairoCanvas;
}

}

}

/** \file GtkCairoArea.cpp
 * \brief GTK+/Cairo drawing area implementation.
 */
