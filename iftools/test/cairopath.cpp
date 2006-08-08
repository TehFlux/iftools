/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * cairopath.cpp                  Cairo path test.
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

using namespace std;
using namespace Ionflux::Tools;
using namespace Ionflux::Tools::Cairo;

void createPath(CairoCanvas& cairo)
{
	cairo.moveTo(10.0, 10.0);
	cairo.lineTo(10.0, 60.0);
	cairo.lineTo(60.0, 60.0);
	cairo.lineTo(60.0, 10.0);
	cairo.closePath();
}

int main(int argc, char* argv[])
{
	ImageSurface surface(CAIRO_FORMAT_ARGB32, 600, 400);
	CairoCanvas cairo(surface);
	createPath(cairo);
	Path path;
	cairo.copyPath(path);
	cairo_path_data_type_t type;
	for (PathIterator i = path.begin(); i != path.end(); i++)
	{
		type = (*i).getType();
		if (type == CAIRO_PATH_MOVE_TO)
		{
			cout << "CAIRO_PATH_MOVE_TO: (" << (*i).getPoint().x << ", " 
				<< (*i).getPoint().y << ")" << endl;
		} else
		if (type == CAIRO_PATH_LINE_TO)
		{
			cout << "CAIRO_PATH_LINE_TO: (" << (*i).getPoint().x << ", " 
				<< (*i).getPoint().y << ")" << endl;
		} else
		if (type == CAIRO_PATH_CURVE_TO)
		{
			cout << "CAIRO_PATH_CURVE_TO: (" << (*i).getPoint(0).x << ", " 
				<< (*i).getPoint(0).y << "), (" << (*i).getPoint(1).x << ", " 
				<< (*i).getPoint(1).y << "), (" << (*i).getPoint(2).x << ", " 
				<< (*i).getPoint(2).y << ")" << endl;
		} else
		if (type == CAIRO_PATH_CLOSE_PATH)
			cout << "CAIRO_PATH_CLOSE_PATH" << endl;
		else
			cout << "(unknown path element)" << endl;
	}
	return 0;
}

/** \file cairopath.cpp
 * \brief Cairo path test.
 */
