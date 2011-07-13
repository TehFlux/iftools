#ifndef IONFLUX_OBJECT_IFCACHE
#define IONFLUX_OBJECT_IFCACHE
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFCache.hpp                     Cache (header).
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

#include "ifobject/types.hpp"
#include "ifobject/cachehelpers.hpp"
#include <queue>
#include <vector>
#include <map>
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/// Class information for class IFCache.
class IFCacheClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFCacheClassInfo();
		/// Destructor.
		virtual ~IFCacheClassInfo();
};

/** Cache.
 * \ingroup ifobject
 *
 * A cache for arbitrary objects.
 */
class IFCache
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Item vector.
		std::vector<Ionflux::ObjectBase::IFCacheEntry*> items;
		/// Item ID to entry map.
		std::map<std::string, Ionflux::ObjectBase::IFCacheEntry*> idMap;
		/// Maximum cache size.
		Ionflux::ObjectBase::UInt64 maxSize;
		/// Current cache size.
		Ionflux::ObjectBase::UInt64 currentSize;
		/// Allow zero size items.
		bool allowZeroSize;
		/// Caching policy.
		Ionflux::ObjectBase::CachePolicy policy;
		
		/** Get cache entry.
		 *
		 * Get the cache entry for an item ID.
		 *
		 * \param itemID Item ID.
		 *
		 * \return Cache entry, or 0 if the item with the specified ID is not in 
		 * the cache.
		 */
		virtual Ionflux::ObjectBase::IFCacheEntry* getEntry(const 
		Ionflux::ObjectBase::IFObjectID& itemID);
		
		/** Hit entry.
		 *
		 * Record a hit for the specified entry.
		 *
		 * \param entry Cache entry.
		 */
		virtual void hit(Ionflux::ObjectBase::IFCacheEntry* entry);
		
	public:
		/// Caching policy: Keep most recently used.
		static const Ionflux::ObjectBase::CachePolicy POLICY_KEEP_RECENT;
		/// Caching policy: Keep most hits.
		static const Ionflux::ObjectBase::CachePolicy POLICY_KEEP_MOST_HITS;
		/// Class information instance.
		static const IFCacheClassInfo iFCacheClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFCache object.
		 */
		IFCache();
		
		/** Constructor.
		 *
		 * Construct new IFCache object.
		 *
		 * \param initMaxSize Maximum cache size.
		 * \param initAllowZeroSize Allow zero size items.
		 * \param initPolicy Caching policy.
		 */
		IFCache(Ionflux::ObjectBase::UInt64 initMaxSize, bool initAllowZeroSize =
		false, Ionflux::ObjectBase::CachePolicy initPolicy = 
		POLICY_KEEP_MOST_HITS);
		
		/** Destructor.
		 *
		 * Destruct IFCache object.
		 */
		virtual ~IFCache();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation of the object.
		 */
		virtual std::string getString() const;
		
		/** Clear entries.
		 *
		 * Clear cache entries.
		 */
		virtual void clear();
		
		/** Reset hits.
		 *
		 * Reset the hits for all cache entries. If the optional \c hits 
		 * argument is specified, the hits for all objects will be set to that
		 * value.
		 *
		 * \param hits Number of hits.
		 */
		virtual void reset(Ionflux::ObjectBase::UInt64 hits = 0);
		
		/** Get number of cache entries.
		 *
		 * Get the number of cache entries.
		 *
		 * \return Number of cache entries.
		 */
		virtual unsigned int getNumEntries() const;
		
		/** Check whether the cache is full.
		 *
		 * Returns \c true if the cache has the maximum number of elements. If
		 * \c offset is specified, the function returns \c true if the cache 
		 * would be full after adding elements of that size. If the maximum 
		 * size of the cache is 0, the cache is never considered full.
		 *
		 * \param offset Size offset.
		 *
		 * \return Result of the test.
		 */
		virtual bool isFull(Ionflux::ObjectBase::UInt64 offset = 0) const;
		
		/** Check item.
		 *
		 * Check whether an item with the specified ID exists in the cache. 
		 * This does not record a hit for the item.
		 *
		 * \param itemID Item ID.
		 *
		 * \return \c true if item exists in the cache, \c false otherwise.
		 */
		virtual bool itemExists(const std::string& itemID);
		
		/** Get hits.
		 *
		 * Get the number of hits for an item.
		 *
		 * \param itemID Item ID.
		 *
		 * \return Number of hits for the item.
		 */
		virtual Ionflux::ObjectBase::UInt64 getHits(const std::string& itemID);
		
		/** Get item.
		 *
		 * Get the item with the specified ID from the cache. This also 
		 * records a hit for the item.
		 *
		 * \param itemID Item ID.
		 *
		 * \return The item with the specified ID, or 0 if the item is not 
		 * currently in the cache.
		 */
		virtual Ionflux::ObjectBase::IFObject* getItem(const std::string& 
		itemID);
		
		/** Remove item.
		 *
		 * Remove the item with the specified ID from the cache.
		 *
		 * \param itemID Item ID.
		 *
		 * \return \c true if the item was successfully removed, \c false 
		 * otherwise.
		 */
		virtual bool removeItem(const std::string& itemID);
		
		/** Clean up.
		 *
		 * Find the entry which was hit the longest time ago from the entries 
		 * with the least hits and remove it from the cache.
		 */
		virtual void cleanup();
		
		/** Clean up.
		 *
		 * Remove entries from the cache until at least \c minSize cache units
		 * are free.
		 *
		 * \param minSize Minimum free size.
		 */
		virtual void cleanup(Ionflux::ObjectBase::UInt64 minSize);
		
		/** Add item.
		 *
		 * Add an item to the cache.
		 *
		 * \param itemID Item ID.
		 * \param item Item.
		 * \param hits Initial number of hits.
		 */
		virtual void addItem(const std::string& itemID, 
		Ionflux::ObjectBase::IFObject* item, Ionflux::ObjectBase::UInt64 hits = 
		0);
		
		/** Get items.
		 *
		 * Get all items from the cache.
		 *
		 * \param target Target vector.
		 */
		virtual void getItems(Ionflux::ObjectBase::IFObjectVector& target);
		
		/** Get item IDs.
		 *
		 * Get all item IDs from the cache.
		 *
		 * \param target Target vector.
		 */
		virtual void getItemIDs(Ionflux::ObjectBase::StringVector& target);
		
		/** Get debug info.
		 *
		 * Get information that is useful for debugging.
		 *
		 * \return Debug info.
		 */
		virtual std::string getDebugInfo();
		
		/** Initialize cache entry..
		 *
		 * Initilaize a cache entry.
		 *
		 * \param entry Cache entry.
		 * \param item Item.
		 * \param itemID Item ID.
		 * \param cTime Creation time.
		 * \param hTime Time of last hit.
		 * \param hits Number of hits.
		 */
		static void initEntry(Ionflux::ObjectBase::IFCacheEntry& entry, 
		Ionflux::ObjectBase::IFObject* item = 0, const std::string& itemID = "", 
		Ionflux::ObjectBase::UInt64 cTime = 0, Ionflux::ObjectBase::UInt64 hTime 
		= 0, Ionflux::ObjectBase::UInt64 hits = 0);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * param parentObject Parent object.
		 *
		 * return Pointer to the new instance.
		 */
		static Ionflux::ObjectBase::IFCache* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Set maximum cache size.
		 *
		 * Set new value of maximum cache size.
		 *
		 * \param newMaxSize New value of maximum cache size.
		 */
		virtual void setMaxSize(Ionflux::ObjectBase::UInt64 newMaxSize);
		
		/** Get maximum cache size.
		 *
		 * \return Current value of maximum cache size.
		 */
		virtual Ionflux::ObjectBase::UInt64 getMaxSize() const;
		
		/** Get current cache size.
		 *
		 * \return Current value of current cache size.
		 */
		virtual Ionflux::ObjectBase::UInt64 getCurrentSize() const;
		
		/** Set allow zero size items.
		 *
		 * Set new value of allow zero size items.
		 *
		 * \param newAllowZeroSize New value of allow zero size items.
		 */
		virtual void setAllowZeroSize(bool newAllowZeroSize);
		
		/** Get allow zero size items.
		 *
		 * \return Current value of allow zero size items.
		 */
		virtual bool getAllowZeroSize() const;
		
		/** Set caching policy.
		 *
		 * Set new value of caching policy.
		 *
		 * \param newPolicy New value of caching policy.
		 */
		virtual void setPolicy(Ionflux::ObjectBase::CachePolicy newPolicy);
		
		/** Get caching policy.
		 *
		 * \return Current value of caching policy.
		 */
		virtual Ionflux::ObjectBase::CachePolicy getPolicy() const;
};

}

}

/** \file IFCache.hpp
 * \brief Cache (header).
 */
#endif
