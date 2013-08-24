/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * templatetypes.cpp              Types used by Template (implementation).
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
#include "iftemplate/templatetypes.hpp"

namespace Ionflux
{

namespace Template
{

TagNestingLevel::TagNestingLevel()
: tagForeach(0), tagIf(0), tagFirst(0), tagMid(0), tagLast(0), tagSingle(0), 
  tagNotFirst(0), tagNotMid(0), tagNotLast(0), tagNotSingle(0), tagSWrap(0), 
  tagSection(0), tagRef(0), all(0)
{
	// Nothing to do here.
}

}

}

/** \file templatetypes.cpp
 * \brief Types used by Template (implementation).
 */
