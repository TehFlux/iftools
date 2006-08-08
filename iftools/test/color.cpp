/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * color.cpp                  Color test.
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
#include "ionflux/tools.hpp"
#include "ionflux/color.hpp"
#include "ionflux/CLArgs.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLParams params;
	args.getParams(params);
	if (params.size() < 1)
	{
		cerr << "Usage: color <name>" << endl;
		return 0;
	}
	ColorMap colors;
	addBasicColors(colors);
	const Color* color = getByName(params[0], colors);
	if (color == 0)
	{
		cerr << "Unknown color '" << params[0] << "'." << endl;
		return -1;
	}
	Color8bpp color2 = to8bpp(*color);
	cout << color->name << ": " << toHex(*color) 
		<< ", rgb(" << static_cast<int>(color2.red) << ", " 
		<< static_cast<int>(color2.green) << ", "
		<< static_cast<int>(color2.blue) << ")" << endl;
	return 0;
}

/** \file color.cpp
 * \brief Color test.
 */
