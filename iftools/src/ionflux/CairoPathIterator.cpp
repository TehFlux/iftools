/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PathIterator.cpp                Cairo path iterator.
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

#include "ionflux/CairoPathIterator.hpp"
#include "ionflux/CairoPath.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

PathIterator::PathIterator()
: path(0), elementIndex(0)
{
	// TODO: Nothing ATM. ;-)
}

PathIterator::PathIterator(const PathIterator& initPathIterator)
: path(0), elementIndex(0)
{
	*this = initPathIterator;
}

PathIterator::PathIterator(Path& initPath, unsigned int initIndex)
: path(&initPath), elementIndex(initIndex)
{
	// TODO: Nothing ATM. ;-)
}

PathIterator::~PathIterator()
{
	// TODO: Nothing ATM. ;-)
}

PathData& PathIterator::operator*()
{
	return *path->getDataElement(elementIndex);
}

PathData& PathIterator::operator++()
{
	elementIndex++;
	return *path->getDataElement(elementIndex);
}

PathData& PathIterator::operator++(int dummy)
{
	elementIndex++;
	return *path->getDataElement(elementIndex);
}

PathData& PathIterator::operator--()
{
	elementIndex--;
	return *path->getDataElement(elementIndex);
}

PathData& PathIterator::operator--(int dummy)
{
	elementIndex--;
	return *path->getDataElement(elementIndex);
}

bool PathIterator::operator==(const PathIterator& other)
{
	if ((other.getPath() == path)
		&& (other.getElementIndex() == elementIndex))
		return true;
	return false;
}

bool PathIterator::operator!=(const PathIterator& other)
{
	return !(*this == other);
}

PathIterator& PathIterator::operator=(const PathIterator& newPathIterator)
{
	setPath(newPathIterator.getPath());
	setElementIndex(newPathIterator.getElementIndex());
	return *this;
}

void PathIterator::setPath(Path* newPath)
{
	path = newPath;
}

void PathIterator::setElementIndex(unsigned int newElementIndex)
{
	elementIndex = newElementIndex;
}

Path* PathIterator::getPath() const
{
	return path;
}

unsigned int PathIterator::getElementIndex() const
{
	return elementIndex;
}

}

}

}

/** \file CairoPathIterator.cpp
 * \brief Cairo path iterator implementation.
 */
