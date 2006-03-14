/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ObjectPool.cpp                  Object pool.
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

#include "ionflux/ObjectPool.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

ObjectPool::ObjectPool()
: watchMode(false)
{
	// TODO: Nothing ATM. ;-)
}

ObjectPool::~ObjectPool()
{
	clear();
}

void ObjectPool::unrefAll()
{
	map<ManagedObject*, bool>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++)
		if ((*i).first != 0)
			(*i).first->unref();
}

void ObjectPool::removeUnused(unsigned int threshold)
{
	map<ManagedObject*, bool>::iterator i;
	vector<ManagedObject*> keep;
	ManagedObject* currentObject = 0;
	ostringstream state;
	for (i = objects.begin(); i != objects.end(); i++)
	{
		currentObject = (*i).first;
		if (currentObject->getRefCount() > threshold)
		{
			keep.push_back(currentObject);
			// ----- DEBUG ----- //
			state.str("");
			state << "[ObjectPool::removeUnused] DEBUG: "
				"Object " << currentObject << " (" 
				<< currentObject->getClassName() << ") will be kept.";
			log.msg(state.str(), log.VL_DEBUG_INSANE);
			// ----- DEBUG ----- */
		} else
		{
			// ----- DEBUG ----- //
			state.str("");
			state << "[ObjectPool::removeUnused] DEBUG: "
				"Object " << currentObject << " (" 
				<< currentObject->getClassName() << ") will be deleted.";
			log.msg(state.str(), log.VL_DEBUG_INSANE);
			// ----- DEBUG ----- */
			if (threshold > 0)
				currentObject->unref();
			delete currentObject;
		}
	}
	objects.clear();
	for (vector<ManagedObject*>::iterator k = keep.begin(); 
		k != keep.end(); k++)
		objects[*k] = true;
}

bool ObjectPool::findObject(ManagedObject* searchObject)
{
	map<ManagedObject*, bool>::const_iterator i = objects.find(searchObject);
	if (i != objects.end())
		return true;
	return false;
}

bool ObjectPool::addObject(ManagedObject* newObject)
{
	if (newObject == 0)
	{
		log.msg("[ObjectPool::addObject] WARNING: Attempt to add null pointer "
			"(ignored).", log.VL_WARNING);
		return false;
	}
	if (newObject->isManaged())
	{
		log.msg("[ObjectPool::addObject] WARNING: Attempt to add an object "
			"which is already managed by another parent object (ignored).", 
			log.VL_WARNING);
		return false;
	}
	ostringstream state;
	if (findObject(newObject))
	{
		// ----- DEBUG ----- //
		state.str("");
		state << "[ObjectPool::addObject] DEBUG: "
			"Object " << newObject << " (" << newObject->getClassName() 
			<< ") is already in the pool.";
		log.msg(state.str(), log.VL_DEBUG_INSANE);
		return false;
		// ----- DEBUG ----- */
	}
	// ----- DEBUG ----- //
	state.str("");
	state << "[ObjectPool::addObject] DEBUG: "
		"Adding object " << newObject << " (" 
		<< newObject->getClassName() << ").";
	log.msg(state.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	newObject->ref();
	objects[newObject] = true;
	return true;
}

void ObjectPool::removeObject(ManagedObject* rmObject)
{
	if (rmObject == 0)
	{
		log.msg("[ObjectPool::addObject] WARNING: Attempt to remove null "
			"pointer (ignored).", log.VL_WARNING);
		return;
	}
	map<ManagedObject*, bool>::iterator i = objects.find(rmObject);
	if (i != objects.end())
	{
		// ----- DEBUG ----- //
		ostringstream state;
		state.str("");
		state << "[ObjectPool::removeObject] DEBUG: "
			"Removing object " << rmObject << " (" 
			<< rmObject->getClassName() << ").";
		log.msg(state.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		(*i).first->unref();
		if ((*i).first->getRefCount() == 0)
			delete (*i).first;
		objects.erase(i);
	}
}

void ObjectPool::cleanup()
{
	unsigned int objectsLeft = 0;
	unsigned int prevObjectsLeft = objects.size();
	while (objectsLeft < prevObjectsLeft)
	{
		prevObjectsLeft = objects.size();
		removeUnused(1);
		objectsLeft = objects.size();
	}
}

void ObjectPool::clear()
{
	unsigned int objectsLeft = 0;
	unsigned int prevObjectsLeft = objects.size();
	while (objectsLeft < prevObjectsLeft)
	{
		prevObjectsLeft = objects.size();
		removeUnused(1);
		objectsLeft = objects.size();
	}
	if (watchMode && (objectsLeft > 0))
	{
		ostringstream state;
		state.str("");
		state << "[ObjectPool::clear] WARNING: (Watch mode) "
			"The following objects have not been deleted:";
		for (map<ManagedObject*, bool>::iterator i = objects.begin(); 
			i != objects.end(); i++)
			state << endl << "  " << (*i).first << " (" 
				<< (*i).first->getClassName() << ").";
		log.msg(state.str(), log.VL_WARNING);
	}
	unrefAll();
	objects.clear();
}

Ionflux::Tools::Reporter& ObjectPool::getLog()
{
	return log;
}

void ObjectPool::setWatchMode(bool newWatchMode)
{
	watchMode = newWatchMode;
}

bool ObjectPool::getWatchMode() const
{
	return watchMode;
}

}

}

/** \file ObjectPool.cpp
 * \brief Object pool implementation.
 */
