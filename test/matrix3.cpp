/* ==========================================================================
 * Ionflux SVG Chart Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * matrix3.cpp                     Matrix (R3 x R3) test.
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
#include "ionflux/Matrix3.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	cout << "Matrix (R3 x R3) test." << endl;
	/* Sample matrix from Bronstein, Taschenbuch der Mathematik, p. 282
	   M1^-1:
	   ( 2,  8, -21,
	    -1, -5,  13,
		 0,  1,  -2 ) */
	Matrix3 m1(
		3.0, 5.0, 1.0,
		2.0, 4.0, 5.0,
		1.0, 2.0, 2.0);
	cout << "M1:" << endl << m1.toString() << endl;
	Matrix3 m1inv = m1;
	m1inv.invert();
	cout << "M1^-1:" << endl << m1inv.toString() << endl;
	Matrix3 m2 = m1 * m1inv;
	cout << "M1 * M1^-1:" << endl << m2.toString() << endl;
	Matrix3 id;
	return 0;
}

/** \file matrix3.cpp
 * \brief Matrix (R3 x R3) test.
 */
