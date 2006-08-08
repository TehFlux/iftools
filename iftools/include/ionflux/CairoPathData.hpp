#ifndef IONFLUX_TOOLS_CAIRO_PATHDATA
#define IONFLUX_TOOLS_CAIRO_PATHDATA
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PathData.hpp                      Cairo path data.
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
#include "ionflux/CairoMatrix.hpp"
#include "ionflux/ManagedObject.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** Cairo path data.
 * \ingroup cairo
 *
 * Data element of a path in the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class PathData
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Cairo path data.
		cairo_path_data_t* cairoPathData;
		/// Cairo path data management flag.
		bool managePathData;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new PathData object.
		 */
		PathData();
		
		/** Constructor.
		 *
		 * Construct new PathData object.
		 *
		 * \param initPathData Cairo path data.
		 */
		PathData(const PathData& initPathData);
		
		/** Constructor.
		 *
		 * Construct new PathData object.
		 *
		 * \param initPathData Cairo path data.
		 * \param initManagePathData Cairo path data management flag.
		 */
		PathData(cairo_path_data_t* initPathData, bool initManagePathData = 
		false);
		
		/** Constructor.
		 *
		 * Construct new PathData object.
		 *
		 * \param initPathDataType Cairo path data type.
		 */
		PathData(cairo_path_data_type_t initPathDataType);
		
		/** Destructor.
		 *
		 * Destruct PathData object.
		 */
		virtual ~PathData();
		
		/** Get type.
		 *
		 * Get the type of this path element.
		 *
		 * \return Path data type.
		 */
		virtual cairo_path_data_type_t getType();
		
		/** Set type.
		 *
		 * Set the type of this path element.
		 *
		 * \param newType Path data type.
		 */
		virtual void setType(cairo_path_data_type_t newType);
		
		/** Get number of points.
		 *
		 * Get the number of points for this path element.
		 *
		 * \return Number of points.
		 */
		virtual unsigned int getNumPoints();
		
		/** Get point.
		 *
		 * Get the point with the specified index.
		 *
		 * \param pointIndex Point index.
		 *
		 * \return Point.
		 */
		virtual Point getPoint(unsigned int pointIndex = 0);
		
		/** Set point.
		 *
		 * Set the point with the specified index.
		 *
		 * \param source Point.
		 * \param pointIndex Point index.
		 */
		virtual void setPoint(const Point& source, unsigned int pointIndex = 0);
		
		/** Set cairo path data.
		 *
		 * Set the cairo path data.
		 *
		 * \param newCairoPathData Cairo Path data.
		 * \param newManagePathData Cairo Path data management flag.
		 */
		virtual void setCairoPathData(cairo_path_data_t* newCairoPathData, bool 
		newManagePathData = false);
		
		/** Get cairo path data.
		 *
		 * Get the cairo path data.
		 *
		 * \return Cairo path data.
		 */
		virtual cairo_path_data_t* getCairoPathData() const;
		
		/** Assignment operator.
		 *
		 * Assign a path data to another path data.
		 *
		 * \param newCairoPathData Cairo path data.
		 *
		 * \return The object itself.
		 */
		virtual PathData& operator=(const PathData& newCairoPathData);
		
		/** Assignment operator.
		 *
		 * Assign a cairo path to this path object.
		 * 
		 * \note By default, the cairo path data will not be managed by this 
		 * object.
		 *
		 * \param newCairoPathData Cairo path data.
		 *
		 * \return The object itself.
		 */
		virtual PathData& operator=(cairo_path_data_t* newCairoPathData);
		
		/** Set cairo path data management flag.
		 *
		 * Set new value of cairo path data management flag.
		 *
		 * \param newManagePathData New value of cairo path data management flag.
		 */
		virtual void setManagePathData(bool newManagePathData);
		
		/** Get cairo path data management flag.
		 *
		 * \return Current value of cairo path data management flag.
		 */
		virtual bool getManagePathData() const;
};

}

}

}

/** \file CairoPathData.hpp
 * \brief Cairo path data header.
 */
#endif
