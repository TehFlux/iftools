/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * cairo.cpp                  Cairo test.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <iostream>
#include <string>
#include "ionflux/CairoCanvas.hpp"
#include "ionflux/CairoImageSurface.hpp"
#include "ionflux/CairoLinearGradient.hpp"
#include "ionflux/CLArgs.hpp"

using namespace std;
using namespace Ionflux::Tools;
using namespace Ionflux::Tools::Cairo;

void draw(CairoCanvas& cairo)
{
	LinearGradient gradient(300.0, 0.0, 300.0, 400.0);
	gradient.addColorStop(0.0, COLOR_GREY_20);
	gradient.addColorStop(1.0, COLOR_GREY_80);
	cairo.rectangle(0.0, 0.0, 600.0, 400.0);
	cairo.setSource(gradient);
	cairo.fill();
	cairo.save();
	cairo.translate(0.5, 0.5);
	cairo.drawRectangle(100.0, 100.0, 400.0, 200.0, 
		1.0, &COLOR_BLUEVIOLET, &COLOR_MIDNIGHTBLUE);
	cairo.drawCircle(300.0, 200.0, 50.0, 
		2.0, &COLOR_FIREBRICK, &COLOR_DODGERBLUE);
	double width;
	double height;
	cairo.getTextSize("Miep", width, height, "Verdana bold", 30.0);
	// ----- DEBUG ----- //
	cerr << "[draw] DEBUG: Text size: " << width << " x " << height << endl;
	// ----- DEBUG ----- */
	cairo.drawRectangle(100.0, 100.0, width, height, 
		1.0, &COLOR_MAGENTA, &COLOR_NONE);
	cairo.drawText(100.0, 100.0, "Miep", "Verdana bold", 30.0, &COLOR_GREEN);
	cairo.restore();
}

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLParams params;
	args.getParams(params);
	if (params.size() < 1)
	{
		cerr << "Usage: cairo <file name>" << endl;
		return 0;
	}
	string pngFilename = params[0];
	ImageSurface surface(CAIRO_FORMAT_ARGB32, 600, 400);
	CairoCanvas cairo(surface);
	draw(cairo);
	cairo.showPage();
	surface.writeToPng(pngFilename);
	return 0;
}

/** \file cairo.cpp
 * \brief Cairo test.
 */
