#ifndef IONFLUX_TOOLS_CAIRO_PATHITERATOR
#define IONFLUX_TOOLS_CAIRO_PATHITERATOR
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PathIterator.hpp                  Cairo path iterator.
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

#include "ionflux/CairoPathData.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

class Path;

/** Cairo path iterator.
 * \ingroup cairo
 *
 * Iterator for a path in the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class PathIterator
{
	private:
		
	protected:
		/// Path.
		Path* path;
		/// Element index.
		unsigned int elementIndex;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new PathIterator object.
		 */
		PathIterator();
		
		/** Constructor.
		 *
		 * Construct new PathIterator object.
		 *
		 * \param initPathIterator Cairo path iterator.
		 */
		PathIterator(const PathIterator& initPathIterator);
		
		/** Constructor.
		 *
		 * Construct new PathIterator object.
		 *
		 * \param initPath Cairo path.
		 * \param initIndex Element index.
		 */
		PathIterator(Path& initPath, unsigned int initIndex = 0);
		
		/** Destructor.
		 *
		 * Destruct PathIterator object.
		 */
		virtual ~PathIterator();
		
		/** Dereference.
		 *
		 * Dereference operator.
		 *
		 * \return Path data.
		 */
		virtual PathData& operator*();
		
		/** Increment.
		 *
		 * Increment operator.
		 *
		 * \return Path data.
		 */
		virtual PathData& operator++();
		
		/** Increment.
		 *
		 * Increment operator.
		 *
		 * \param dummy Postfix operator dummy argument.
		 *
		 * \return Path data.
		 */
		virtual PathData& operator++(int dummy);
		
		/** Decrement.
		 *
		 * Decrement operator.
		 *
		 * \return Path data.
		 */
		virtual PathData& operator--();
		
		/** Decrement.
		 *
		 * Decrement operator.
		 *
		 * \param dummy Postfix operator dummy argument.
		 *
		 * \return Path data.
		 */
		virtual PathData& operator--(int dummy);
		
		/** Comparison.
		 *
		 * Comparison operator.
		 *
		 * \param other Cairo path iterator.
		 *
		 * \return \c true if the path iterators are equal, \c false otherwise.
		 */
		virtual bool operator==(const PathIterator& other);
		
		/** Comparison.
		 *
		 * Comparison operator.
		 *
		 * \param other Cairo path iterator.
		 *
		 * \return \c true if the path iterators are not equal, \c false 
		 * otherwise.
		 */
		virtual bool operator!=(const PathIterator& other);
		
		/** Assignment operator.
		 *
		 * Assign a path iterator to another path iterator.
		 *
		 * \param newPathIterator Cairo path iterator.
		 *
		 * \return The object itself.
		 */
		virtual PathIterator& operator=(const PathIterator& newPathIterator);
		
		/** Set path.
		 *
		 * Set new value of path.
		 *
		 * \param newPath New value of path.
		 */
		virtual void setPath(Path* newPath);
		
		/** Set element index.
		 *
		 * Set new value of element index.
		 *
		 * \param newElementIndex New value of element index.
		 */
		virtual void setElementIndex(unsigned int newElementIndex);
		
		/** Get path.
		 *
		 * \return Current value of path.
		 */
		virtual Path* getPath() const;
		
		/** Get element index.
		 *
		 * \return Current value of element index.
		 */
		virtual unsigned int getElementIndex() const;
};

}

}

}

/** \file CairoPathIterator.hpp
 * \brief Cairo path iterator header.
 */
#endif
