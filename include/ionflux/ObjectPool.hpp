#ifndef IONFLUX_TOOLS_OBJECTPOOL
#define IONFLUX_TOOLS_OBJECTPOOL
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ObjectPool.hpp                    Object pool.
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

#include <string>
#include <iostream>
#include <vector>
#include "ionflux/ManagedObject.hpp"
#include "ionflux/Reporter.hpp"

namespace Ionflux
{

namespace Tools
{

/** Object pool.
 * \ingroup memmgmt
 *
 * A pool of reference counted objects. The purpose of the pool is to 
 * delete objects at the end of the lifetime, or on a forced cleanup of the
 * pool, if they are not needed anymore. An object managed by the pool will
 * be deleted if its reference count is zero upon cleanup of the pool.
 * 
 * \note To avoid confusion, pools are not intended for explicitly managed 
 * objects, that is, objects which have their parent memory management flag
 * set to \c true. Such objects will never be added to a pool and a warning
 * message may be issued if an attempt is made to add an explicitly managed
 * object to a pool.
 */
class ObjectPool
{
	private:
		
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Objects managed by the pool.
		std::map<ManagedObject*, bool> objects;
		/// Watch mode flag.
		bool watchMode;
		
		/** Unreference all objects.
		 *
		 * Remove the reference held by the pool for all objects.
		 */
		virtual void unrefAll();
		
		/** Remove unused objects.
		 *
		 * Remove all objects for which the reference count has dropped to 
		 * zero (or to specified value).
		 *
		 * \param threshold Threshold.
		 */
		virtual void removeUnused(unsigned int threshold = 0);
		
	public:
		
		/** Constructor.
		 *
		 * Construct new ObjectPool object.
		 */
		ObjectPool();
		
		/** Destructor.
		 *
		 * Destruct ObjectPool object.
		 */
		virtual ~ObjectPool();
		
		/** Find object.
		 *
		 * Check whether an object is in the pool.
		 *
		 * \param searchObject Managed object.
		 *
		 * \return \c true if the specified object is in the pool, \c false 
		 * otherwise.
		 */
		virtual bool findObject(ManagedObject* searchObject);
		
		/** Add object.
		 *
		 * Add an object to the pool.
		 * 
		 * \note This function will make sure that the object to be added to 
		 * the pool is not yet managed explicitly by another object. In this 
		 * case, the object will not be added and the function will return \c 
		 * false. The pool will reference the object, but it will not alter 
		 * the management flag for the object. Thus, objects may be added to 
		 * several pools.
		 *
		 * \param newObject Object to be added to the pool.
		 *
		 * \return \c true if this object will be managed by the pool after the 
		 * call, \c false otherwise.
		 */
		virtual bool addObject(ManagedObject* newObject);
		
		/** Remove object.
		 *
		 * Remove an object from the pool.
		 *
		 * \param rmObject Object to be removed from the pool.
		 */
		virtual void removeObject(ManagedObject* rmObject);
		
		/** Cleanup pool.
		 *
		 * Clean up the pool. All objects that are not in use by any object 
		 * (besides the pool itself) are removed from the pool and deleted.
		 */
		virtual void cleanup();
		
		/** Clear pool.
		 *
		 * Clear the pool. All objects in the pool will be unreferenced and 
		 * removed from the pool. Objects will also be deleted if their 
		 * reference count is zero.
		 */
		virtual void clear();
		
		/** Get Console output/logging facility.
		 *
		 * The console output/logging facility used by this object.
		 *
		 * \return Console output/logging facility.
		 */
		virtual Ionflux::Tools::Reporter& getLog();
		
		/** Set watch mode flag.
		 *
		 * Set new value of watch mode flag.
		 *
		 * \param newWatchMode New value of watch mode flag.
		 */
		virtual void setWatchMode(bool newWatchMode);
		
		/** Get watch mode flag.
		 *
		 * \return Current value of watch mode flag.
		 */
		virtual bool getWatchMode() const;
};

}

}

/** \file ObjectPool.hpp
 * \brief Object pool header.
 */
#endif
