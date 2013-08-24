#ifndef IONFLUX_TEMPLATE_STRINGFILTER
#define IONFLUX_TEMPLATE_STRINGFILTER
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilter.hpp                String filter (header).
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
#include "iftemplate/types.hpp"
#include "iftemplate/Tokenizer.hpp"
#include "iftemplate/StringManipulator.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

class StringFilterFunction;

/// Class information for class StringFilter.
class StringFilterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		StringFilterClassInfo();
		/// Destructor.
		virtual ~StringFilterClassInfo();
};

/** String filter.
 * \ingroup iftemplate
 *
 * A string filter is a set of functions (manipulators) that can be applied
 * to a string to yield another string. String manipulators may take one or
 * more arguments, and they can be stacked. An example of a string filter 
 * expression would be:
 * 
 * <tt>uppercase|remove(' ')</tt>
 * 
 * This filter would first change the string to uppercase and then remove 
 * all spaces.
 * 
 * The general format of a string manipulator is:
 * 
 * <tt>&lt;function&gt; [ '(' [  (&lt;identifier&gt; | (&lt;quote char&gt; 
 * &lt;argument&gt; &lt;quote char&gt;)) [',' | &lt;linear whitespace&gt;]+
 * ]+ ')' ]+</tt>
 * 
 * Where <tt>&lt;quote char&gt;</tt> is either ' or ". String arguments 
 * should always be enclosed in quotes and multiple arguments should be 
 * separated by ','.
 */
class StringFilter
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// tokenizer.
		Ionflux::Template::Tokenizer tok;
		/// string manipulator index.
		Ionflux::Template::StringManipulatorNameMap manipByName;
		/// filter expression.
		std::string filter;
		/// String filter functions.
		std::vector<Ionflux::Template::StringFilterFunction*> functions;
		/// String manipulators.
		std::vector<Ionflux::Template::StringManipulator::StringManipulator*> manipulators;
		
		/** Initialize token types.
		 *
		 * Initialize the token types.
		 */
		virtual void initTokenTypes();
		
		/** Parse filter expression.
		 *
		 * Parse the current filter expression.
		 */
		virtual void parse();
		
		/** Get string manipulator by name.
		 *
		 * Get a string manipulator by name.
		 *
		 * \param manipName string manipulator name.
		 *
		 * \return string manipulator, or 0 if no manipulator with the specified 
		 * name exists.
		 */
		virtual Ionflux::Template::StringManipulator::StringManipulator* 
		getManipulatorByName(const std::string& manipName);
		
	public:
		/// Token type: function separator.
		static const Ionflux::Template::TokenType TT_FUNC_SEP;
		/// Token type: function bracket (left).
		static const Ionflux::Template::TokenType TT_FUNC_BRACKET_LEFT;
		/// Token type: function bracket (right).
		static const Ionflux::Template::TokenType TT_FUNC_BRACKET_RIGHT;
		/// Token type: argument separator.
		static const Ionflux::Template::TokenType TT_FUNC_ARG_SEP;
		/// Class information instance.
		static const StringFilterClassInfo stringFilterClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new StringFilter object.
		 */
		StringFilter();
		
		/** Constructor.
		 *
		 * Construct new StringFilter object.
		 *
		 * \param other Other object.
		 */
		StringFilter(const Ionflux::Template::StringFilter& other);
		
		/** Constructor.
		 *
		 * Construct new StringFilter object.
		 *
		 * \param initFilter string filter expression.
		 */
		StringFilter(const std::string& initFilter);
		
		/** Destructor.
		 *
		 * Destruct StringFilter object.
		 */
		virtual ~StringFilter();
		
		/** Add default string manipulators.
		 *
		 * Add the default string manipulators.
		 */
		virtual void addDefaultManipulators();
		
		/** Apply.
		 *
		 * Apply the string filter to a byte string.
		 *
		 * \param bytes bytes.
		 *
		 * \return the result of applying the string filter.
		 */
		virtual std::string apply(const std::string& bytes);
		
		/** Update indices.
		 *
		 * Update the string manipulator indices.
		 */
		virtual void updateIndices();
		
		/** Print debug information.
		 *
		 * Print debug information.
		 */
		virtual void printDebugInfo();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::StringFilter& operator=(const 
		Ionflux::Template::StringFilter& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::StringFilter* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::StringFilter* 
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
		static Ionflux::Template::StringFilter* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new StringFilter object.
		 *
		 * \param initFilter string filter expression.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::StringFilter* create(const std::string& 
		initFilter, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get filter expression.
		 *
		 * \return Current value of filter expression.
		 */
		virtual std::string getFilter() const;
		
		/** Set filter expression.
		 *
		 * Set new value of filter expression.
		 *
		 * \param newFilter New value of filter expression.
		 */
		virtual void setFilter(const std::string& newFilter);
		
		/** Get number of functions.
		 *
		 * \return Number of functions.
		 */
		virtual unsigned int getNumFunctions() const;
		
		/** Get function.
		 *
		 * Get the function at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Function at specified index.
		 */
		virtual Ionflux::Template::StringFilterFunction* getFunction(unsigned int
		elementIndex = 0) const;
		
		/** Find function.
		 *
		 * Find the specified occurence of a function.
		 *
		 * \param needle Function to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the function, or -1 if the function cannot be found.
		 */
		virtual int findFunction(Ionflux::Template::StringFilterFunction* needle,
		unsigned int occurence = 1) const;
        
		/** Get string filter functions.
		 *
		 * \return string filter functions.
		 */
		virtual std::vector<Ionflux::Template::StringFilterFunction*>& 
		getFunctions();
		
		/** Add function.
		 *
		 * Add a function.
		 *
		 * \param addElement Function to be added.
		 */
		virtual void addFunction(Ionflux::Template::StringFilterFunction* 
		addElement);
		
		/** Remove function.
		 *
		 * Remove a function.
		 *
		 * \param removeElement Function to be removed.
		 */
		virtual void removeFunction(Ionflux::Template::StringFilterFunction* 
		removeElement);
		
		/** Remove function.
		 *
		 * Remove a function.
		 *
		 * \param removeIndex Function to be removed.
		 */
		virtual void removeFunctionIndex(unsigned int removeIndex);
		
		/** Clear functions.
		 *
		 * Clear all functions.
		 */
		virtual void clearFunctions();
		
		/** Get number of manipulators.
		 *
		 * \return Number of manipulators.
		 */
		virtual unsigned int getNumManipulators() const;
		
		/** Get manipulator.
		 *
		 * Get the manipulator at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Manipulator at specified index.
		 */
		virtual Ionflux::Template::StringManipulator::StringManipulator* 
		getManipulator(unsigned int elementIndex = 0) const;
		
		/** Find manipulator.
		 *
		 * Find the specified occurence of a manipulator.
		 *
		 * \param needle Manipulator to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the manipulator, or -1 if the manipulator cannot be 
		 * found.
		 */
		virtual int 
		findManipulator(Ionflux::Template::StringManipulator::StringManipulator* 
		needle, unsigned int occurence = 1) const;
        
		/** Get string manipulators.
		 *
		 * \return string manipulators.
		 */
		virtual 
		std::vector<Ionflux::Template::StringManipulator::StringManipulator*>& 
		getManipulators();
		
		/** Add manipulator.
		 *
		 * Add a manipulator.
		 *
		 * \param addElement Manipulator to be added.
		 */
		virtual void 
		addManipulator(Ionflux::Template::StringManipulator::StringManipulator* 
		addElement);
		
		/** Remove manipulator.
		 *
		 * Remove a manipulator.
		 *
		 * \param removeElement Manipulator to be removed.
		 */
		virtual void 
		removeManipulator(Ionflux::Template::StringManipulator::StringManipulator*
		removeElement);
		
		/** Remove manipulator.
		 *
		 * Remove a manipulator.
		 *
		 * \param removeIndex Manipulator to be removed.
		 */
		virtual void removeManipulatorIndex(unsigned int removeIndex);
		
		/** Clear manipulators.
		 *
		 * Clear all manipulators.
		 */
		virtual void clearManipulators();
};

}

}

/** \file StringFilter.hpp
 * \brief String filter (header).
 */
#endif
