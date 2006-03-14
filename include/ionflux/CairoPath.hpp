#ifndef IONFLUX_TOOLS_CAIRO_PATH
#define IONFLUX_TOOLS_CAIRO_PATH
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Path.hpp                          Cairo path.
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
#include "ionflux/ObjectPool.hpp"
#include "ionflux/CairoPathIterator.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

class PathIterator;

/** Cairo path.
 * \ingroup cairo
 *
 * A path in the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class Path
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Object pool.
		Ionflux::Tools::ObjectPool pool;
		/// Path data.
		std::vector<PathData*> pathData;
		/// Cairo path.
		cairo_path_t* cairoPath;
		
		/** Initialize path data.
		 *
		 * Initialize the path data vector
		 */
		virtual void initPathData();
		
		/** Clear path data.
		 *
		 * Clear the path data vector
		 */
		virtual void clearPathData();
		
	public:
		
		/** Constructor.
		 *
		 * Construct new Path object.
		 */
		Path();
		
		/** Constructor.
		 *
		 * Construct new Path object.
		 *
		 * \param initPath Cairo path.
		 */
		Path(const Path& initPath);
		
		/** Constructor.
		 *
		 * Construct new Path object.
		 *
		 * \param initPath Cairo path.
		 */
		Path(cairo_path_t* initPath);
		
		/** Destructor.
		 *
		 * Destruct Path object.
		 */
		virtual ~Path();
		
		/** Destroy.
		 *
		 * Destroy path
		 */
		virtual void destroy();
		
		/** Get status.
		 *
		 * Get status
		 *
		 * \return Status.
		 */
		virtual cairo_status_t getStatus();
		
		/** Get data.
		 *
		 * Get data
		 *
		 * \return Path data.
		 */
		virtual cairo_path_data_t* getData();
		
		/** Get data element.
		 *
		 * Get the data element with the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Path data element, or 0 if the element with the specified 
		 * index doesn't exist..
		 */
		virtual PathData* getDataElement(unsigned int elementIndex);
		
		/** Get number of data elements.
		 *
		 * Get number of data elements
		 *
		 * \return Number of data elements.
		 */
		virtual unsigned int getNumData();
		
		/** Begin.
		 *
		 * Return an iterator to the beginning of the path element list.
		 *
		 * \return .
		 */
		virtual PathIterator begin();
		
		/** End.
		 *
		 * Return an iterator to the end of the path element list.
		 *
		 * \return .
		 */
		virtual PathIterator end();
		
		/** Assignment operator.
		 *
		 * Assign a path to another path.
		 *
		 * \param newCairoPath Cairo path.
		 *
		 * \return The object itself.
		 */
		virtual Path& operator=(const Path& newCairoPath);
		
		/** Assignment operator.
		 *
		 * Assign a cairo path to this path object.
		 *
		 * \param newCairoPath Cairo path.
		 *
		 * \return The object itself.
		 */
		virtual Path& operator=(cairo_path_t* newCairoPath);
		
		/** Set cairo path.
		 *
		 * Set new value of cairo path.
		 *
		 * \param newCairoPath New value of cairo path.
		 */
		virtual void setCairoPath(cairo_path_t* newCairoPath);
		
		/** Get cairo path.
		 *
		 * \return Current value of cairo path.
		 */
		virtual cairo_path_t* getCairoPath() const;
};

}

}

}

/** \file CairoPath.hpp
 * \brief Cairo path header.
 */
#endif
