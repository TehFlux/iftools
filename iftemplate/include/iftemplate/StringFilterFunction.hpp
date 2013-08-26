#ifndef IONFLUX_TEMPLATE_STRINGFILTERFUNCTION
#define IONFLUX_TEMPLATE_STRINGFILTERFUNCTION
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilterFunction.hpp        String filter function (header).
 * =========================================================================
 * 
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include "iftemplate/StringManipulator.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class StringFilterFunction.
class StringFilterFunctionClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		StringFilterFunctionClassInfo();
		/// Destructor.
		virtual ~StringFilterFunctionClassInfo();
};

/** String filter function.
 * \ingroup iftemplate
 *
 * A string filter function that is part of a string filter.
 */
class StringFilterFunction
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// name of the filter function.
		std::string func;
		/// Arguments.
		std::vector<std::string> args;
		/// string manipulator.
		Ionflux::Template::StringManipulator::StringManipulator* manip;
		
	public:
		/// Class information instance.
		static const StringFilterFunctionClassInfo stringFilterFunctionClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new StringFilterFunction object.
		 */
		StringFilterFunction();
		
		/** Constructor.
		 *
		 * Construct new StringFilterFunction object.
		 *
		 * \param other Other object.
		 */
		StringFilterFunction(const Ionflux::Template::StringFilterFunction& other);
		
		/** Constructor.
		 *
		 * Construct new StringFilterFunction object.
		 *
		 * \param initFunc name of the filter function.
		 * \param initManip string manipulator.
		 * \param initArgs arguments.
		 */
		StringFilterFunction(const std::string& initFunc, 
		Ionflux::Template::StringManipulator::StringManipulator* initManip = 0, 
		Ionflux::ObjectBase::StringVector* initArgs = 0);
		
		/** Destructor.
		 *
		 * Destruct StringFilterFunction object.
		 */
		virtual ~StringFilterFunction();
		
		/** Set argument.
		 *
		 * Set the argument with the specified index.
		 *
		 * \param index index.
		 * \param newArg argument.
		 */
		virtual void setArgument(unsigned int index, const std::string& newArg);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::StringFilterFunction& operator=(const 
		Ionflux::Template::StringFilterFunction& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::StringFilterFunction* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::StringFilterFunction* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Template::StringFilterFunction* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new StringFilterFunction object.
		 *
		 * \param initFunc name of the filter function.
		 * \param initManip string manipulator.
		 * \param initArgs arguments.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::StringFilterFunction* create(const std::string&
		initFunc, Ionflux::Template::StringManipulator::StringManipulator* 
		initManip = 0, Ionflux::ObjectBase::StringVector* initArgs = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get name of the filter function.
		 *
		 * \return Current value of name of the filter function.
		 */
		virtual std::string getFunc() const;
		
		/** Set name of the filter function.
		 *
		 * Set new value of name of the filter function.
		 *
		 * \param newFunc New value of name of the filter function.
		 */
		virtual void setFunc(const std::string& newFunc);
		
		/** Get number of arguments.
		 *
		 * \return Number of arguments.
		 */
		virtual unsigned int getNumArguments() const;
		
		/** Get argument.
		 *
		 * Get the argument at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Argument at specified index.
		 */
		virtual std::string getArgument(unsigned int elementIndex = 0) const;
		
		/** Find argument.
		 *
		 * Find the specified occurence of a argument.
		 *
		 * \param needle Argument to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the argument, or -1 if the argument cannot be found.
		 */
		virtual int findArgument(const std::string& needle, unsigned int 
		occurence = 1) const;
        
		/** Get arguments.
		 *
		 * \return arguments.
		 */
		virtual std::vector<std::string>& getArguments();
		
		/** Add argument.
		 *
		 * Add a argument.
		 *
		 * \param addElement Argument to be added.
		 */
		virtual void addArgument(const std::string& addElement);
		
		/** Create argument.
		 *
		 * Create a new argument which is managed by the argument set.
		 *
		 * \return New argument.
		 */
		virtual const std::string& addArgument();
		
		/** Add arguments.
		 *
		 * Add arguments from a argument vector.
		 *
		 * \param newArguments arguments.
		 */
		virtual void addArguments(std::vector<std::string>& newArguments);
		
		/** Add arguments.
		 *
		 * Add arguments from a argument set.
		 *
		 * \param newArguments arguments.
		 */
		virtual void addArguments(Ionflux::Template::StringFilterFunction* 
		newArguments);
		
		/** Remove argument.
		 *
		 * Remove a argument.
		 *
		 * \param removeElement Argument to be removed.
		 */
		virtual void removeArgument(const std::string& removeElement);
		
		/** Remove argument.
		 *
		 * Remove a argument.
		 *
		 * \param removeIndex Argument to be removed.
		 */
		virtual void removeArgumentIndex(unsigned int removeIndex);
		
		/** Clear arguments.
		 *
		 * Clear all arguments.
		 */
		virtual void clearArguments();
		
		/** Get string manipulator.
		 *
		 * \return Current value of string manipulator.
		 */
		virtual Ionflux::Template::StringManipulator::StringManipulator* 
		getManip() const;
		
		/** Set string manipulator.
		 *
		 * Set new value of string manipulator.
		 *
		 * \param newManip New value of string manipulator.
		 */
		virtual void 
		setManip(Ionflux::Template::StringManipulator::StringManipulator* 
		newManip);
};

}

}

/** \file StringFilterFunction.hpp
 * \brief String filter function (header).
 */
#endif
