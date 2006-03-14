/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Path.cpp                        Cairo path.
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

#include "ionflux/CairoPath.hpp"
#include "ionflux/CairoPathIterator.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

Path::Path()
: cairoPath(0)
{
	// TODO: Nothing ATM. ;-)
}

Path::Path(const Path& initPath)
: cairoPath(0)
{
	setCairoPath(initPath.getCairoPath());
}

Path::Path(cairo_path_t* initPath)
{
	setCairoPath(initPath);
}

Path::~Path()
{
	clearPathData();
	if (cairoPath != 0)
		cairo_path_destroy(cairoPath);
}

void Path::initPathData()
{
	if (cairoPath == 0)
		return;
	clearPathData();
	PathData* newData;
	int i = 0;
	while (i < cairoPath->num_data)
	{
		newData = new PathData(&cairoPath->data[i]);
		pool.addObject(newData);
		newData->ref();
		pathData.push_back(newData);
		i += (newData->getNumPoints() + 1);
	}
}

void Path::clearPathData()
{
	if (pathData.size() == 0)
		return;
	PathData* theData;
	for (unsigned int i = 0; i < pathData.size(); i++)
	{
		theData = pathData[i];
		if (theData != 0)
			theData->unref();
	}
	pathData.clear();
}

void Path::destroy()
{
	cairo_path_destroy(cairoPath);
}

cairo_status_t Path::getStatus()
{
	if (cairoPath != 0)
		return cairoPath->status;
	return CAIRO_STATUS_SUCCESS;
}

cairo_path_data_t* Path::getData()
{
	if (cairoPath != 0)
		return cairoPath->data;
	return 0;
}

PathData* Path::getDataElement(unsigned int elementIndex)
{
	if ((elementIndex >= 0) && (elementIndex < pathData.size()))
		return pathData[elementIndex];
	return 0;
}

unsigned int Path::getNumData()
{
	return pathData.size();
}

PathIterator Path::begin()
{
	return PathIterator(*this, 0);
}

PathIterator Path::end()
{
	return PathIterator(*this, getNumData());
}

Path& Path::operator=(const Path& newCairoPath)
{
	setCairoPath(newCairoPath.getCairoPath());
	return *this;
}

Path& Path::operator=(cairo_path_t* newCairoPath)
{
	setCairoPath(newCairoPath);
	return *this;
}

void Path::setCairoPath(cairo_path_t* newCairoPath)
{
	clearPathData();
	cairoPath = newCairoPath;
	initPathData();
}

cairo_path_t* Path::getCairoPath() const
{
	return cairoPath;
}

}

}

}

/** \file CairoPath.cpp
 * \brief Cairo path implementation.
 */
