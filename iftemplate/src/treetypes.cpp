/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * treetypes.cpp                  Types used by Tree (implementation).
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
#include "iftemplate/treetypes.hpp"

namespace Ionflux
{

namespace Template
{

const int TreeExprElement::TE_INVALID = 0;
const int TreeExprElement::TE_CONST = 1;
const int TreeExprElement::TE_VAR = 2;
const int TreeExprElement::TE_OP = 3;

}

}

/** \file treetypes.cpp
 * \brief Types used by Tree (implementation).
 */
