/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PathData.cpp                    Cairo path data.
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

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

PathData::PathData()
: cairoPathData(0), managePathData(false)
{
	setType(CAIRO_PATH_MOVE_TO);
}

PathData::PathData(const PathData& initPathData)
: cairoPathData(0), managePathData(false)
{
	setCairoPathData(initPathData.getCairoPathData(), false);
}

PathData::PathData(cairo_path_data_t* initPathData, bool 
initManagePathData)
: cairoPathData(0), managePathData(false)
{
	setCairoPathData(initPathData, initManagePathData);
}

PathData::PathData(cairo_path_data_type_t initPathDataType)
: cairoPathData(0), managePathData(false)
{
	setType(initPathDataType);
}

PathData::~PathData()
{
	if ((cairoPathData != 0) && managePathData)
		delete[] cairoPathData;
	cairoPathData = 0;
}

cairo_path_data_type_t PathData::getType()
{
	if (cairoPathData != 0)
		return cairoPathData->header.type;
	/* Note: This is phony, since this path data object might actually be 
	   uninitialized. */
	cerr << "[PathData::getType] WARNING: Request for type, "
		"but path data is uninitialized." << endl;
	setType(CAIRO_PATH_MOVE_TO);
	return CAIRO_PATH_MOVE_TO;
}

void PathData::setType(cairo_path_data_type_t newType)
{
	if ((cairoPathData != 0) 
		&& managePathData
		&& (newType != getType()))
		delete[] cairoPathData;
	else
	if ((cairoPathData != 0)
		&& (newType == getType()))
		return;
	else
	if ((cairoPathData == 0) || !managePathData)
	{
		unsigned int numPoints = 0;
		if ((newType == CAIRO_PATH_MOVE_TO)
			|| (newType == CAIRO_PATH_LINE_TO))
			numPoints = 1;
		else
		if (newType == CAIRO_PATH_CURVE_TO)
			numPoints = 3;
		else
		if (newType == CAIRO_PATH_CLOSE_PATH)
			numPoints = 0;
		cairoPathData = new cairo_path_data_t[numPoints + 1];
		cairoPathData[0].header.type = newType;
		for (unsigned int i = 0; i < numPoints; i++)
		{
			cairoPathData[i + 1].point.x = 0.0;
			cairoPathData[i + 1].point.y = 0.0;
		}
		managePathData = true;
	}
}

unsigned int PathData::getNumPoints()
{
	if (cairoPathData != 0)
	{
		if ((cairoPathData->header.type == CAIRO_PATH_MOVE_TO)
			|| (cairoPathData->header.type == CAIRO_PATH_LINE_TO))
			return 1;
		else
		if (cairoPathData->header.type == CAIRO_PATH_CURVE_TO)
			return 3;
		else
		if (cairoPathData->header.type == CAIRO_PATH_CLOSE_PATH)
			return 0;
	}
	return 0;
}

Point PathData::getPoint(unsigned int pointIndex)
{
	Point result;
	if ((cairoPathData != 0) && (pointIndex < getNumPoints()))
	{
		result.x = cairoPathData[pointIndex + 1].point.x;
		result.y = cairoPathData[pointIndex + 1].point.y;
	} else
	{
		result.x = 0.0;
		result.y = 0.0;
	}
	return result;
}

void PathData::setPoint(const Point& source, unsigned int pointIndex)
{
	if ((cairoPathData != 0) && (pointIndex < getNumPoints()))
	{
		cairoPathData[pointIndex + 1].point.x = source.x;
		cairoPathData[pointIndex + 1].point.y = source.y;
	}
}

void PathData::setCairoPathData(cairo_path_data_t* newCairoPathData, bool 
newManagePathData)
{
	if ((cairoPathData != 0) && managePathData)
		delete[] cairoPathData;
	cairoPathData = newCairoPathData;
	managePathData = newManagePathData;
}

cairo_path_data_t* PathData::getCairoPathData() const
{
	return cairoPathData;
}

PathData& PathData::operator=(const PathData& newCairoPathData)
{
	setCairoPathData(newCairoPathData.getCairoPathData(), false);
	return *this;
}

PathData& PathData::operator=(cairo_path_data_t* newCairoPathData)
{
	setCairoPathData(newCairoPathData, false);
	return *this;
}

void PathData::setManagePathData(bool newManagePathData)
{
	managePathData = newManagePathData;
}

bool PathData::getManagePathData() const
{
	return managePathData;
}

}

}

}

/** \file CairoPathData.cpp
 * \brief Cairo path data implementation.
 */
