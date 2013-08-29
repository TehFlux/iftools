/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFCache.i                       Cache (interface).
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
%{
#include "ifobject/IFCache.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFCacheClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFCacheClassInfo();
        virtual ~IFCacheClassInfo();
};

class IFCache
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::ObjectBase::CachePolicy POLICY_KEEP_RECENT;
		static const Ionflux::ObjectBase::CachePolicy POLICY_KEEP_MOST_HITS;
        
        IFCache();
        IFCache(Ionflux::ObjectBase::UInt64 initMaxSize, bool 
        initAllowZeroSize = false, Ionflux::ObjectBase::CachePolicy 
        initPolicy = POLICY_KEEP_MOST_HITS);
        virtual ~IFCache();
        virtual std::string getString() const;
        virtual void clear();
        virtual void reset(Ionflux::ObjectBase::UInt64 hits = 0);
        virtual unsigned int getNumEntries() const;
        virtual bool isFull(Ionflux::ObjectBase::UInt64 offset = 0) const;
        virtual bool itemExists(const std::string& itemID);
        virtual Ionflux::ObjectBase::UInt64 getHits(const std::string& 
        itemID);
        virtual Ionflux::ObjectBase::IFObject* getItem(const std::string& 
        itemID);
        virtual bool removeItem(const std::string& itemID);
        virtual void cleanup();
        virtual void cleanup(Ionflux::ObjectBase::UInt64 minSize);
        virtual void addItem(const std::string& itemID, 
        Ionflux::ObjectBase::IFObject* item, Ionflux::ObjectBase::UInt64 
        hits = 0);
        virtual void getItems(Ionflux::ObjectBase::IFObjectVector& target);
        virtual void getItemIDs(Ionflux::ObjectBase::StringVector& target);
        virtual std::string getDebugInfo();
        static void initEntry(Ionflux::ObjectBase::IFCacheEntry& entry, 
        Ionflux::ObjectBase::IFObject* item = 0, const std::string& itemID 
        = "", Ionflux::ObjectBase::UInt64 cTime = 0, 
        Ionflux::ObjectBase::UInt64 hTime = 0, Ionflux::ObjectBase::UInt64 
        hits = 0);
		static Ionflux::ObjectBase::IFCache* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMaxSize(Ionflux::ObjectBase::UInt64 newMaxSize);
        virtual Ionflux::ObjectBase::UInt64 getMaxSize() const;
        virtual Ionflux::ObjectBase::UInt64 getCurrentSize() const;
        virtual void setAllowZeroSize(bool newAllowZeroSize);
        virtual bool getAllowZeroSize() const;
        virtual void setPolicy(Ionflux::ObjectBase::CachePolicy newPolicy);
        virtual Ionflux::ObjectBase::CachePolicy getPolicy() const;
};

}

}
