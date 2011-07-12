/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFCache.cpp                     Cache (implementation).
 * =========================================================================
 * 
 * This file is part of Ionflux Object Base System.
 * 
 * Ionflux Object Base System is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the 
 * License, or (at your option) any later version.
 * 
 * Ionflux Object Base System is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Object Base System; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifobject/IFCache.hpp"
#include "ifobject/IFLogMessage.hpp"
#include "ifobject/utility.hpp"
#include "ifobject/IFError.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

IFCacheClassInfo::IFCacheClassInfo()
{
	name = "IFCache";
	desc = "Cache";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFCacheClassInfo::~IFCacheClassInfo()
{
}

// run-time type information instance constants
const IFCacheClassInfo IFCache::iFCacheClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFCache::CLASS_INFO = &IFCache::iFCacheClassInfo;

IFCache::IFCache()
: maxSize(0), currentSize(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFCache::~IFCache()
{
	clear();
}

Ionflux::ObjectBase::IFCacheEntry* IFCache::getEntry(const 
Ionflux::ObjectBase::IFObjectID& itemID)
{
	std::map<std::string, Ionflux::ObjectBase::IFCacheEntry*>::iterator i = 
	idMap.find(itemID);
	if (i != idMap.end())
	    return (*i).second;
	return 0;
}

void IFCache::hit(Ionflux::ObjectBase::IFCacheEntry* entry)
{
	if (entry == 0)
	    return;
	entry->hits++;
	entry->hTime = getTimeTicks();
}

std::string IFCache::getString() const
{
	// TODO: Implementation.
	return IFObject::getString();
}

void IFCache::clear()
{
	items.clear();
	std::vector<Ionflux::ObjectBase::IFCacheEntry*>::iterator i;
	for (i = items.begin(); i != items.end(); i++)
	{
	    IFCacheEntry* e0 = *i;
	    if (e0->item != 0)
	    {
	        currentSize -= e0->item->getSize();
	        removeLocalRef(e0->item);
	        e0->item = 0;
	    }
	    delete e0;
	}
	idMap.clear();
}

void IFCache::reset(Ionflux::ObjectBase::UInt64 hits)
{
	UInt64 hTime = getTimeTicks();
	std::vector<Ionflux::ObjectBase::IFCacheEntry*>::iterator i;
	for (i = items.begin(); i != items.end(); i++)
	{
	    IFCacheEntry* e0 = *i;
	    e0->hits = hits;
	    e0->hTime = hTime;
	}
}

unsigned int IFCache::getNumEntries() const
{
	// TODO: Implementation.
	return idMap.size();
}

bool IFCache::isFull(Ionflux::ObjectBase::UInt64 offset) const
{
	if (maxSize == 0)
	    return false;
	return (currentSize + offset) <= maxSize;
}

bool IFCache::itemExists(const std::string& itemID)
{
	IFCacheEntry* e0 = getEntry(itemID);
	if (e0 != 0)
	    return true;
	return false;
}

Ionflux::ObjectBase::UInt64 IFCache::getHits(const std::string& itemID)
{
	IFCacheEntry* e0 = getEntry(itemID);
	if (e0 != 0)
	    return e0->hits;
	return 0;
}

Ionflux::ObjectBase::IFObject* IFCache::getItem(const std::string& itemID)
{
	IFCacheEntry* e0 = getEntry(itemID);
	if (e0 == 0)
	    return 0;
	hit(e0);
	return e0->item;
}

bool IFCache::removeItem(const std::string& itemID)
{
	if (!itemExists(itemID))
	    return false;
	std::map<std::string, Ionflux::ObjectBase::IFCacheEntry*>::iterator i = 
	idMap.find(itemID);
	IFCacheEntry* e0 = (*i).second;
	std::vector<Ionflux::ObjectBase::IFCacheEntry*>::iterator j = 
	std::find(items.begin(), items.end(), e0);
	idMap.erase(i);
	items.erase(j);
	if (e0->item != 0)
	{
	    currentSize -= e0->item->getSize();
	    removeLocalRef(e0->item);
	    e0->item = 0;
	}
	delete e0;
	return true;
}

void IFCache::cleanup()
{
	if (items.size() == 0)
	    return;
	std::sort(items.begin(), items.end(), IFCacheEntryCompareByHits());
	IFCacheEntry* e0 = items[0];
	UInt64 ch = e0->hits;
	UInt64 hitsMin = ch;
	std::vector<IFCacheEntry*> candidates;
	candidates.push_back(e0);
	unsigned int i = 1;
	// Get entries with the same number of hits as the first one.
	while ((ch == hitsMin) 
	    && (i < items.size()))
	{
	    e0 = items[i];
	    ch = e0->hits;
	    if (ch == hitsMin)
	        candidates.push_back(e0);
	    i++;
	}
	std::sort(candidates.begin(), candidates.end(), 
	    IFCacheEntryCompareByHTime());
	e0 = candidates[0];
	// <---- DEBUG ----- //
	std::ostringstream status;
	status << "Removing object (id = '" << e0->itemID << "', hits = " 
	    << e0->hits << ", cTime = " << e0->cTime << ", hTime = " 
	    << e0->hTime << ").";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "cleanup"));
	// ----- DEBUG ----> */
	removeItem(e0->itemID);
}

void IFCache::cleanup(Ionflux::ObjectBase::UInt64 minSize)
{
	if ((maxSize == 0) 
	    || (minSize == 0))
	    return;
	if (minSize > maxSize)
	{
	    std::ostringstream status;
	    status << "[IFCache.cleanup] Size to be cleaned up is larger "
	        "than maximum cache size (minSize = " << minSize 
	        << ", maxSize = " << maxSize << ")!";
	    throw IFError(status.str());
	}
	while ((items.size() > 0) 
	    && ((maxSize - currentSize) < minSize))
	    cleanup();
}

void IFCache::addItem(const std::string& itemID, 
Ionflux::ObjectBase::IFObject* item, Ionflux::ObjectBase::UInt64 hits)
{
	if (item == 0)
	    throw IFError("[IFCache.addItem] " 
	        "Attempt to add null item!");
	std::ostringstream status;
	if (itemExists(itemID))
	{
	    status << "[IFCache.addItem] Item exists (id ='"
	        << itemID << "')!";
	    throw IFError(status.str());
	}
	// Make sure the item fits within the cache.
	UInt64 is0 = item->getSize();
	if (maxSize > 0)
	{
	    if (is0 > maxSize)
	    {
	        status << "[IFCache.addItem] Item does not fit into "
	            "cache (id ='" << itemID << "', size = " << is0 
	            << ")!";
	        throw IFError(status.str());
	    }
	    if (isFull(is0))
	        cleanup(is0);
	}
	// Create a new cache entry.
	IFCacheEntry* e0 = new IFCacheEntry();
	if (e0 == 0)
	    throw IFError("[IFCache.addItem] " 
	        "Could not allocate cache entry!");
	initEntry(*e0, item, itemID, 0, 0, hits);
	// <---- DEBUG ----- //
	status << "Adding object (id = '" << e0->itemID << "', hits = " 
	    << e0->hits << ", cTime = " << e0->cTime << ", hTime = " 
	    << e0->hTime << ").";
	log(IFLogMessage(status.str(), VL_DEBUG, this, "addItem"));
	// ----- DEBUG ----> */
	addLocalRef(item);
	idMap[itemID] = e0;
	items.push_back(e0);
	currentSize += is0;
}

void IFCache::getItems(Ionflux::ObjectBase::IFObjectVector& target)
{
	std::vector<Ionflux::ObjectBase::IFCacheEntry*>::iterator i;
	for (i = items.begin(); i != items.end(); i++)
	    target.push_back((*i)->item);
}

void IFCache::getItemIDs(Ionflux::ObjectBase::StringVector& target)
{
	std::vector<Ionflux::ObjectBase::IFCacheEntry*>::iterator i;
	for (i = items.begin(); i != items.end(); i++)
	    target.push_back((*i)->itemID);
}

std::string IFCache::getDebugInfo()
{
	std::ostringstream status;
	status << "IFCache[" << endl
	    << "  maxSize     = " << maxSize << endl 
	    << "  currentSize = " << currentSize << endl
	    << "  numItems    = " << items.size() << endl
	    << "  entries:" << endl;
	if (items.size() == 0)
	    status << "    <none>" << endl;
	else
	{
	    std::sort(items.begin(), items.end(), IFCacheEntryCompareByHTime());
	    std::sort(items.begin(), items.end(), IFCacheEntryCompareByHits());
	    unsigned int k = 1;
	    std::vector<Ionflux::ObjectBase::IFCacheEntry*>::iterator i;
	    for (i = items.begin(); i != items.end(); i++)
	    {
	        IFCacheEntry* e0 = *i;
	        status << "    #" << setw(3) << setfill('0') << k << ": id = '" 
	            << e0->itemID << "', hits = " << e0->hits << ", cTime = " 
	            << e0->cTime << ", hTime = " << e0->hTime << ")" << endl;
	        k++;
	    }
	}
	status << "]";
	return status.str();
}

void IFCache::initEntry(Ionflux::ObjectBase::IFCacheEntry& entry, 
Ionflux::ObjectBase::IFObject* item, const std::string& itemID, 
Ionflux::ObjectBase::UInt64 cTime, Ionflux::ObjectBase::UInt64 hTime, 
Ionflux::ObjectBase::UInt64 hits)
{
	entry.item = item;
	entry.itemID = itemID;
	if (cTime == 0)
	    entry.cTime = getTimeTicks();
	else
	    entry.cTime = cTime;
	if (hTime == 0)
	    entry.hTime = getTimeTicks();
	else
	    entry.hTime = hTime;
	entry.hits = hits;
}

void IFCache::setMaxSize(Ionflux::ObjectBase::UInt64 newMaxSize)
{
	maxSize = newMaxSize;
}

Ionflux::ObjectBase::UInt64 IFCache::getMaxSize() const
{
	return maxSize;
}

Ionflux::ObjectBase::UInt64 IFCache::getCurrentSize() const
{
	return currentSize;
}

}

}

/** \file IFCache.cpp
 * \brief Cache implementation.
 */
