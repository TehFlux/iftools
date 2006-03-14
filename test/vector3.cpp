/* ==========================================================================
 * Ionflux SVG Chart Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * vector3.cpp                     Vector (R3) test.
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

#include <iostream>
#include <string>
#include "ionflux/Vector3.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	cout << "Vector (R3) test." << endl;
	Vector3 a(1.1, 2.3, 3.5);
	Vector3 b(4.5, 5.6, 6.9);
	Vector3 c;
	double s = 7.2;
	cout << "  a = " << a.toString() << endl
		<< "  b = " << b.toString() << endl
		<< "  s = " << s << endl;
	cout << "Vector operations:" << endl;
	c = a + b;
	cout << "  a + b = " << c.toString() << endl;
	c = a - b;
	cout << "  a - b = " << c.toString() << endl;
	c = s * a;
	cout << "  s * a = " << c.toString() << endl;
	cout << "  a * b = " << (a * b) << endl;
	return 0;
}

/** \file vector3.cpp
 * \brief Vector (R3) test.
 */
