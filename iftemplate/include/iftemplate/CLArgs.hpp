#ifndef IONFLUX_TEMPLATE_CLARGS
#define IONFLUX_TEMPLATE_CLARGS
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CLArgs.hpp                      Command line argument parser (header).
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
#include "iftemplate/constants.hpp"
#include "iftemplate/types.hpp"
#include "iftemplate/Tokenizer.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class CLArgs.
class CLArgsClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CLArgsClassInfo();
		/// Destructor.
		virtual ~CLArgsClassInfo();
};

/** Command line argument parser.
 * \ingroup iftemplate
 *
 * A command line argument parser which recognizes the following types of 
 * options and parameters:
 * 
 * \c -o Single-character option (switch)
 * \c --option Multi-character option (switch)
 * \c -o \c &lt;value&gt; Single-character option with value
 * \c --option \c &lt;value&gt; Multi-character option with value
 * \c -abc Concatenated single-character options (multiple switches)
 * \c -abc \c &lt;value&gt; Concatenated single-character options with 
 * value
 * \c option=&lt;value&gt; Assignment option
 * \c &lt;parameter&gt; Command line parameter
 */
class CLArgs
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Command line arguments.
		Ionflux::ObjectBase::StringVector args;
		/// Command line options.
		Ionflux::Template::CLOptionVector options;
		/// Command line parameters.
		Ionflux::Template::CLParams params;
		/// Acceptable command line options.
		Ionflux::Template::CLAcceptableOptionVector acceptable;
		/// Invalid options.
		Ionflux::ObjectBase::StringVector invalidOptions;
		/// Check options flag.
		bool checkOptions;
		
		/** Add option.
		 *
		 * Adds an option if it is acceptable.
		 * 
		 * \note If the option cannot be added, it will be deleted. You should
		 * therefore not use the pointer again if addOption() returns \c 
		 * false.
		 *
		 * \param newOption command line option.
		 *
		 * \return \c true if the option was added successfully, \c false ifthe 
		 * opt ion could not be added and has been deleted..
		 */
		virtual bool addOption(Ionflux::Template::CLOption* newOption);
		
		/** Parse command line arguments.
		 *
		 * Parse command line arguments.
		 */
		virtual void parse();
		
	public:
		/// Token type: option marker.
		static const Ionflux::Template::TokenType TT_OPTION;
		/// Token type: assignment operator.
		static const Ionflux::Template::TokenType TT_ASSIGN;
		/// Option: Not set..
		static const Ionflux::Template::CLOption OPTION_NOT_SET;
		/// Class information instance.
		static const CLArgsClassInfo cLArgsClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new CLArgs object.
		 */
		CLArgs();
		
		/** Constructor.
		 *
		 * Construct new CLArgs object.
		 *
		 * \param other Other object.
		 */
		CLArgs(const Ionflux::Template::CLArgs& other);
		
		/** Constructor.
		 *
		 * Construct new CLArgs object.
		 *
		 * \param argc number of arguments.
		 * \param argv argument vector.
		 */
		CLArgs(int argc, char** argv);
		
		/** Destructor.
		 *
		 * Destruct CLArgs object.
		 */
		virtual ~CLArgs();
		
		/** Clear acceptable options.
		 *
		 * Clear the list of acceptable command line options.
		 */
		virtual void clearAcceptableOptions();
		
		/** Clear options.
		 *
		 * Clear the list of command line options.
		 */
		virtual void clearOptions();
		
		/** Clear params.
		 *
		 * Clear the list of command line parameters.
		 */
		virtual void clearParams();
		
		/** Set command line arguments.
		 *
		 * Set the command line arguments in the standard format.
		 *
		 * \param argc number of arguments.
		 * \param argv argument vector.
		 */
		virtual void setArgs(int argc, char** argv);
		
		/** Set command line arguments.
		 *
		 * Set the command line arguments from a string vector.
		 *
		 * \param newArgs command line arguments.
		 */
		virtual void setArgs(const Ionflux::ObjectBase::StringVector& newArgs);
		
		/** Get option.
		 *
		 * Get an option.
		 * 
		 * \note The option is managed by the CLArgs object.
		 *
		 * \param searchOption option to be returned.
		 *
		 * \return Pointer to an option, or 0 if the specified option is not set.
		 */
		virtual Ionflux::Template::CLOption* getOption(const std::string& 
		searchOption);
		
		/** Check whether an option is set.
		 *
		 * Check whether an option is set.
		 *
		 * \param checkOption option to be checked.
		 *
		 * \return \c true if the specified option is set, \c false otherwise.
		 */
		virtual bool isSet(const std::string& checkOption);
		
		/** Get parameters.
		 *
		 * Get command line parameters (values passed on the command line that
		 * do not qualify as options).
		 *
		 * \param target where to store the command line parameters.
		 */
		virtual void getParams(Ionflux::Template::CLParams& target);
		
		/** Add acceptable option.
		 *
		 * Adds an option to the list of options accepted by the command line 
		 * parser.
		 * 
		 * \note You must set acceptable options before handing the command 
		 * line arguments to the parser, i.e. call addAcceptableOption() for 
		 * each acceptable option before calling setArgs().
		 *
		 * \param newOption option identifier.
		 * \param newAcceptValue whether the option can accept a value.
		 */
		virtual void addAcceptableOption(const std::string& newOption, bool 
		newAcceptValue);
		
		/** Get acceptable option.
		 *
		 * Get an acceptable option record.
		 *
		 * \param searchOption option identifier.
		 *
		 * \return pointer to an acceptable option record, or 0 if the specified 
		 * option is not found.
		 */
		virtual Ionflux::Template::CLAcceptableOption* getAcceptableOption(const 
		std::string& searchOption);
		
		/** Check for acceptable option.
		 *
		 * Checks whether an option should be accepted by the parser.
		 *
		 * \param checkOption option to be checked.
		 *
		 * \return \c true if the specified option is acceptable, \c false 
		 * otherwise.
		 */
		virtual bool isAcceptable(const std::string& checkOption);
		
		/** Check for acceptable option value.
		 *
		 * Checks whether an option accepts a value.
		 *
		 * \param checkOption option to be checked.
		 *
		 * \return \c true if the specified option accepts a value, \c false 
		 * otherwise.
		 */
		virtual bool acceptsValue(const std::string& checkOption);
		
		/** Get invalid options.
		 *
		 * Get the invalid options that have been encountered by the parser.
		 *
		 * \return reference to the vector of invalid option identifiers.
		 */
		virtual Ionflux::ObjectBase::StringVector& getInvalidOptions();
		
		/** Get option validation status.
		 *
		 * Check whether all options are acceptable.
		 * 
		 * \sa getInvalidOptions()
		 *
		 * \return \c true if all options are acceptable, \c false otherwise.
		 */
		virtual bool optionsOK();
		
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
		virtual Ionflux::Template::CLArgs& operator=(const 
		Ionflux::Template::CLArgs& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::CLArgs* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::CLArgs* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
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
		static Ionflux::Template::CLArgs* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get check options flag.
		 *
		 * \return Current value of check options flag.
		 */
		virtual bool getCheckOptions() const;
		
		/** Set check options flag.
		 *
		 * Set new value of check options flag.
		 *
		 * \param newCheckOptions New value of check options flag.
		 */
		virtual void setCheckOptions(bool newCheckOptions);
};

}

}

/** \file CLArgs.hpp
 * \brief Command line argument parser (header).
 */
#endif
