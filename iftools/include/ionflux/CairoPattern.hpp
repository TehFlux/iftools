#ifndef IONFLUX_TOOLS_CAIRO_PATTERN
#define IONFLUX_TOOLS_CAIRO_PATTERN
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoPattern.hpp                       Cairo pattern.
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

#include "cairo.h"
#include "ionflux/ManagedObject.hpp"
#include "ionflux/CairoMatrix.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** Cairo pattern.
 * \ingroup cairo
 *
 * Base class for the Cairo vector graphics API pattern types (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class Pattern
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Cairo pattern.
		cairo_pattern_t* cairoPattern;
		
	public:
		/** Constructor.
		 *
		 * Construct new Pattern object.
		 */
		Pattern();
		
		/** Constructor.
		 *
		 * Construct new Pattern object.
		 *
		 * \param initPattern Cairo pattern.
		 */
		Pattern(const Pattern& initPattern);
		
		/** Constructor.
		 *
		 * Construct new Pattern object.
		 *
		 * \param initPattern Cairo pattern.
		 */
		Pattern(cairo_pattern_t* initPattern);
		
		/** Destructor.
		 *
		 * Destruct Pattern object.
		 */
		virtual ~Pattern();
		
		/** Pattern.
		 *
		 * Pattern
		 */
		virtual void reference();
		
		/** Pattern.
		 *
		 * Pattern
		 */
		virtual void destroy();
		
		/** Pattern.
		 *
		 * Pattern
		 *
		 * \return .
		 */
		virtual cairo_status_t status();
		
		/** Pattern matrix.
		 *
		 * Pattern matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void setMatrix(const cairo_matrix_t* matrix);
		
		/** Pattern matrix.
		 *
		 * Pattern matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void getMatrix(cairo_matrix_t* matrix);
		
		/** Pattern matrix.
		 *
		 * Pattern matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void setMatrix(const Matrix& matrix);
		
		/** Pattern matrix.
		 *
		 * Pattern matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void getMatrix(Matrix& matrix);
		
		/** Assignment operator.
		 *
		 * Assign a pattern to another pattern.
		 *
		 * \param newCairoPattern Cairo pattern.
		 *
		 * \return The object itself.
		 */
		virtual Pattern& operator=(const Pattern& newCairoPattern);
		
		/** Assignment operator.
		 *
		 * Assign a cairo pattern to this pattern object.
		 *
		 * \param newCairoPattern Cairo pattern.
		 *
		 * \return The object itself.
		 */
		virtual Pattern& operator=(cairo_pattern_t* newCairoPattern);
		
		/** Set cairo pattern.
		 *
		 * Set new value of cairo pattern.
		 *
		 * \param newCairoPattern New value of cairo pattern.
		 */
		virtual void setCairoPattern(cairo_pattern_t* newCairoPattern);
		
		/** Get cairo pattern.
		 *
		 * \return Current value of cairo pattern.
		 */
		virtual cairo_pattern_t* getCairoPattern() const;
};

}

}

}

/** \file CairoPattern.hpp
 * \brief Cairo pattern header.
 */
#endif
