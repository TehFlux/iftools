/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ManagedObject.cpp               Managed object.
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

#include "ionflux/ManagedObject.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

ManagedObjectClassInfo::ManagedObjectClassInfo()
{
	name = "ManagedObject";
	desc = "Managed object";
}

const ManagedObjectClassInfo ManagedObject::managedObjectClassInfo;
const ClassInfo* ManagedObject::CLASS_INFO = 
	&ManagedObject::managedObjectClassInfo;

ManagedObject::ManagedObject()
: managed(false), refCount(0)
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
}

ManagedObject::~ManagedObject()
{
	if (refCount > 0)
	{
		string plural;
		if (refCount > 1)
			plural = "s";
		cerr << "[ManagedObject::~ManagedObject] WARNING: "
			"Destroying object with " << refCount << " reference" << plural 
			<< "." << endl;
	}
}

bool ManagedObject::setManaged(bool newManage)
{
	if (managed && newManage)
	{
		cerr << "[ManagedObject::setManaged] WARNING: Attempt to set "
			"management flag on an object which is already managed by another "
			"parent." << endl;
		return false;
	}
	managed = newManage;
	return true;
}

bool ManagedObject::isManaged()
{
	return managed;
}

unsigned int ManagedObject::ref()
{
	refCount++;
	return refCount;
}

unsigned int ManagedObject::unref()
{
	if (refCount == 0)
	{
		cerr << "[ManagedObject::unref] WARNING: Attempt to "
			"unreference object with zero references." << endl;
	} else
		refCount--;
	return refCount;
}

unsigned int ManagedObject::getRefCount()
{
	return refCount;
}

}

}

/** \file ManagedObject.cpp
 * \brief Managed object implementation.
 */
