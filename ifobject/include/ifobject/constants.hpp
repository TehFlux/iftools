#ifndef IONFLUX_OBJECT_CONSTANTS
#define IONFLUX_OBJECT_CONSTANTS
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2013 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * constants.hpp                 Constants.
 * ==========================================================================
 *
 * This file is part of Ionflux Object Base System.
 * 
 * Ionflux Object Base System is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the 
 * License, or (at your option) any later version.
 * 
 * Ionflux Object Base System is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Object Base System; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <vector>
#include <sstream>
#include "ifobject/types.hpp"
#include "ifobject/IFError.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/// Default size for read buffers.
const unsigned int READ_BUFFER_SIZE = 4096;

/// Default coordinate separator.
const std::string DEFAULT_COORD_SEPARATOR = ",";

/// Default indentation width.
const unsigned int DEFAULT_INDENT_WIDTH = 2;

/// XML element name: vector of integer
const std::string XML_ELEMENT_NAME_INT_VECTOR = "intv";
/// XML element name: vector of unsigned integer
const std::string XML_ELEMENT_NAME_UINT_VECTOR = "uintv";
/// XML element name: vector of double
const std::string XML_ELEMENT_NAME_DOUBLE_VECTOR = "doublev";
/// XML element name: vector of color set
const std::string XML_ELEMENT_NAME_COLOR_SET_VECTOR = "colorsetv";
/// XML element name: vector of vector 2 set
const std::string XML_ELEMENT_NAME_VECTOR2_SET_VECTOR = "vector2setv";

/// Directory separator.
const unsigned char DIR_SEPARATOR = '/';

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
