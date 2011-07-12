#ifndef IONFLUX_OBJECT_CACHE_HELPERS
#define IONFLUX_OBJECT_CACHE_HELPERS
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * cachehelpers.hpp              Cache helpers.
 * ==========================================================================
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

namespace Ionflux
{

namespace ObjectBase
{

class IFCacheEntryCompareByHits
{
    public:
        IFCacheEntryCompareByHits() { }
        bool operator()(const Ionflux::ObjectBase::IFCacheEntry* e0, 
            const Ionflux::ObjectBase::IFCacheEntry* e1) 
        {
            return e0->hits < e1->hits;
        }
};

class IFCacheEntryCompareByHTime
{
    public:
        IFCacheEntryCompareByHTime() { }
        bool operator()(const Ionflux::ObjectBase::IFCacheEntry* e0, 
            const Ionflux::ObjectBase::IFCacheEntry* e1) 
        {
            return e0->hTime < e1->hTime;
        }
};

}

}

/** \file cachehelpers.hpp
 * \brief Cache helpers.
 */
#endif
