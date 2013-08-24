/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * configtypes.cpp                  Types used by Config (implementation).
 * =========================================================================
 *
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
#include "iftemplate/configtypes.hpp"

namespace Ionflux
{

namespace Template
{

const int ConfigLine::CL_INVALID = 0;
const int ConfigLine::CL_OPTION = 1;
const int ConfigLine::CL_COMMENT = 2;
const int ConfigLine::CL_BLANK = 3;
const int ConfigLine::CL_NESTED = 4;
const int ConfigLine::CL_ROOT_DATA = 5;

}

}

/** \file configtypes.cpp
 * \brief Types used by Config (implementation).
 */
