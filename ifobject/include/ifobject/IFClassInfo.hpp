#ifndef IONFLUX_OBJECT_IFCLASSINFO
#define IONFLUX_OBJECT_IFCLASSINFO
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFClassInfo.hpp                 Class information (header).
 * =========================================================================
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

#include <string>
#include <vector>
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace ObjectBase
{

class IFClassInfo;

typedef std::vector<const Ionflux::ObjectBase::IFClassInfo*> IFClassInfoVector;
 
/** Operation parameter info.
 * \ingroup ifobject
 */
struct IFOpParamInfo
{
	/// Type.
	const Ionflux::ObjectBase::IFClassInfo* type;
	/// Name.
	std::string name;
	/// Description.
	std::string desc;
	/// Whether the parameter is optional.
	bool optional;
	/// Default value.
	const Ionflux::ObjectBase::IFObject* defaultValue;
};
 
/** Operation result info.
 * \ingroup ifobject
 */
struct IFOpResultInfo
{
	/// Type.
	const Ionflux::ObjectBase::IFClassInfo* type;
	/// Description.
	std::string desc;
};
 
/** Operation info.
 * \ingroup ifobject
 */
struct IFOpInfo
{
	/// Operation name.
	Ionflux::ObjectBase::IFOpName name;
	/// Operation parameter information.
	Ionflux::ObjectBase::IFOpParamInfoVector paramInfo;
	/// Operation result information.
	Ionflux::ObjectBase::IFOpResultInfoVector resultInfo;
};

/** Class information.
 * \ingroup ifobject
 *
 * This class provides run-time type information for IFObject based types.
 */
class IFClassInfo
{
	private:
		
	protected:
		/// base class type information.
		IFClassInfoVector baseClassInfo;
		/// Information on supported operations.
		Ionflux::ObjectBase::IFOpNameInfoMap* opInfo;
		/// class name.
		std::string name;
		/// class description.
		std::string desc;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new IFClassInfo object.
		 */
		IFClassInfo();
		
		/** Destructor.
		 *
		 * Destruct IFClassInfo object.
		 */
		virtual ~IFClassInfo();
		
		/** Get number of base classes.
		 *
		 * Get the number of base classes.
		 *
		 * \return Number of base classes.
		 */
		virtual int getNumBaseClasses() const;
		
		/** Get base class information.
		 *
		 * Get the class information record for the base class with the 
		 * specified index.
		 *
		 * \param index Index.
		 *
		 * \return Base class information record, or 0 if the index is out of 
		 * range.
		 */
		virtual const Ionflux::ObjectBase::IFClassInfo* getBaseClassInfo(unsigned
		int index) const;
		
		/** Derived class check.
		 *
		 * Check whether the class is derived from the specified class by 
		 * searching base class records recursively. If \c recursive is set to
		 * \c false, the search will be restricted to direct base classes.
		 *
		 * \param searchClass Base class to search for.
		 * \param recursive Whether to search recursively.
		 *
		 * \return \c true if the class is a base class of the specified class, 
		 * \c false otherwise.
		 */
		virtual bool isDerivedFrom(const Ionflux::ObjectBase::IFClassInfo* 
		searchClass, bool recursive = true) const;
		
		/** Base class check.
		 *
		 * Check whether the class is a base class of the specified class by 
		 * searching base class records recursively. If \c recursive is set to
		 * \c false, the search will be restricted to direct subclasses.
		 *
		 * \param checkClass Class to be checked.
		 * \param recursive Whether to search recursively.
		 *
		 * \return \c true if the class is a base class of the specified class, 
		 * \c false otherwise.
		 */
		virtual bool isBaseOf(const Ionflux::ObjectBase::IFClassInfo* checkClass,
		bool recursive = true) const;
		
		/** Get operation info records.
		 *
		 * Get information about supported operations. The result is a map of 
		 * operation names to operation information records.
		 *
		 * \param target Where to store the information info records.
		 */
		virtual void getOpInfo(Ionflux::ObjectBase::IFOpNameInfoMap& target) 
		const;
		
		/** Get operation info record.
		 *
		 * Get the information record for an operation by name.
		 *
		 * \param opName Operation name.
		 *
		 * \return Operation info record, or 0 if the operation is not 
		 * supported..
		 */
		virtual const Ionflux::ObjectBase::IFOpInfo* getOpInfo(const 
		Ionflux::ObjectBase::IFOpName& opName) const;
		
		/** Get class name.
		 *
		 * \return Current value of class name.
		 */
		virtual std::string getName() const;
		
		/** Get class description.
		 *
		 * \return Current value of class description.
		 */
		virtual std::string getDesc() const;
};

}

}

/** \file IFClassInfo.hpp
 * \brief Class information (header).
 */
#endif
