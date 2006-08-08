#ifndef IONFLUX_TOOLS_CLARGS
#define IONFLUX_TOOLS_CLARGS
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CLArgs.hpp                    Command line argument parser.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <iostream>
#include <vector>
#include "ionflux/Reporter.hpp"
#include "ionflux/Tokenizer.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup cmdline Command line parsing
 *
 * Command line parsing.
 *
 * @{
 */

/// Vector of command line parameters.
typedef std::vector<std::string> CLParams;

/** Command line option.
 *
 * A command line option, consisting of the option identifier and an optional 
 * value.
 */
struct CLOption
{
	/// Option identifier.
	std::string option;
	/// Option value.
	std::string value;
	/** Splittable flag.
	 *
	 * If set to \c true, the option identifier may be considered to consist 
	 * of several concatenated single-character options. If set to \c false, 
	 * the option must be treated as one multi-character option.
	 */
	bool splittable;
};

/** Acceptable command line option.
 *
 * A command line option that is accepted by the parser.
 */
struct CLAcceptableOption
{
	/// Option identifier.
	std::string option;
	/// Whether this option can have a value.
	bool acceptValue;
};

/** Command line argument parser.
 *
 * A command line argument parser which recognizes the following types of 
 * options and parameters:
 *
 * \c -o Single-character option (switch).\n
 * \c --option Multi-character option (switch).\n
 * \c -o \c &lt;value&gt; Single-character option with value.\n
 * \c --option \c &lt;value&gt; Multi-character option with value.\n
 * \c -abc Concatenated single-character options (multiple switches).\n
 * \c -abc \c &lt;value&gt; Concatenated single-character options with value.\n
 * \c option=&lt;value&gt; Assignment option.\n
 * \c &lt;parameter&gt; Command line parameter.
 */
class CLArgs
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Command line arguments.
		std::vector<std::string> args;
		/// Command line options.
		std::vector<CLOption *> options;
		/// Command line parameters.
		CLParams params;
		/// Acceptable command line options.
		std::vector<CLAcceptableOption *> acceptable;
		/// Check options flag.
		bool checkOptions;
		/// Invalid options.
		std::vector<std::string> invalidOptions;
		
		/** Add option.
		 *
		 * Adds an option if it is acceptable.
		 *
		 * \note If the option cannot be added, it will be deleted. You should 
		 * therefore not use the pointer again if addOption() returns 
		 * \c false.
		 *
		 * \param newOption Command line option.
		 *
		 * \return \c true if the option was added successfully, \c false if 
		 * the option could not be added and has been deleted.
		 */
		virtual bool addOption(CLOption *newOption);
		
		/// Parse command line arguments.
		virtual void parse();
		
	public:
		/// Token type: Option marker.
		static const TokenType TT_OPTION;
		/// Token type: Assignment operator.
		static const TokenType TT_ASSIGN;
		/// Option: Not set.
		static const CLOption OPTION_NOT_SET;
		
		/** Constructor.
		 *
		 * Construct new CLArgs object.
		 */
		CLArgs();
		
		/** Constructor.
		 *
		 * Construct new CLArgs object.
		 *
		 * \param argc Number of arguments.
		 * \param argv Argument vector.
		 */
		CLArgs(int argc, char *argv[]);
		
		/** Destructor.
		 *
		 * Destruct CLArgs object.
		 */
		virtual ~CLArgs();
		
		/** Set command line arguments.
		 *
		 * Sets the command line arguments in the standard format.
		 *
		 * \param argc Number of arguments.
		 * \param argv Argument vector.
		 */
		virtual void setArgs(int argc, char *argv[]);
		
		/** Get an option.
		 *
		 * Get an option.
		 *
		 * \param searchOption Option to be returned.
		 *
		 * \return Pointer to an option, or 0 if the specified option is not 
		 * set.
		 */
		virtual CLOption *getOption(const std::string &searchOption);
		
		/** Check whether an option is set.
		 *
		 * Returns \c true if the specified option is set, \c false otherwise.
		 *
		 * \param checkOption Option to be checked.
		 *
		 * \return \c true if the specified option is set, \c false otherwise.
		 */
		virtual bool isSet(const std::string &checkOption);
		
		/** Get parameters.
		 *
		 * Get command line parameters (values passed on the command line that 
		 * do not qualify as options).
		 *
		 * \param target Where to store the command line parameters.
		 */
		virtual void getParams(CLParams &target);
		
		/** Set option checking status.
		 *
		 * Sets whether the parser should reject options that are not 
		 * explicitly set as acceptable.
		 *
		 * \param newCheckOptions Whether the parser should reject options not 
		 * set as acceptable.
		 */
		virtual void setCheckOptions(bool newCheckOptions);
		
		/** Add acceptable option.
		 *
		 * Adds an option to the list of options accepted by the command line 
		 * parser.
		 *
		 * \note You must set acceptable options before handing the command 
		 * line arguments to the parser, i.e. call addAcceptableOption() for 
		 * each acceptable option before calling setArgs().
		 *
		 * \param newOption Option identifier.
		 * \param newAcceptValue Whether the option can accept a value.
		 */
		virtual void addAcceptableOption(const std::string &newOption, 
			bool newAcceptValue);
		
		/** Get option checking status.
		 *
		 * Returns the option checking status.
		 *
		 * \return \c true if the parser rejects options that are not 
		 * explicitly set as acceptable, \c false otherwise.
		 *
		 * \sa addAcceptableOption()
		 */
		virtual bool getCheckOptions();
		
		/** Get acceptable option record.
		 *
		 * Get an acceptable option record.
		 *
		 * \param searchOption Option identifier.
		 *
		 * \return A pointer to an acceptable option record, or 0 if the 
		 * specified option is not found.
		 */
		virtual CLAcceptableOption *getAcceptableOption(
			const std::string &searchOption);
		
		/** Check for acceptable option.
		 *
		 * Checks whether an option should be accepted by the parser.
		 *
		 * \param checkOption Option identifier.
		 *
		 * \return \c true if the option is acceptable, \c false otherwise.
		 */
		virtual bool isAcceptable(const std::string &checkOption);
		
		/** Check for acceptable option value.
		 *
		 * Checks whether an option accepts a value.
		 *
		 * \param checkOption Option identifier.
		 *
		 * \return \c true if the option accepts a value, \c false 
		 * otherwise.
		 */
		virtual bool acceptsValue(const std::string &checkOption);
		
		/** Get invalid options.
		 *
		 * Get invalid options that have been encountered by the parser.
		 *
		 * \return Reference to the vector of invalid option identifiers.
		 *
		 * \sa optionsOK()
		 */
		virtual std::vector<std::string> &getInvalidOptions();
		
		/** Get option validation status.
		 *
		 * \return \c true if all options are acceptable, \c false otherwise.
		 *
		 * \sa getInvalidOptions()
		 */
		virtual bool optionsOK();
		
		/// Clears the list of acceptable command line options.
		virtual void clearAcceptableOptions();
		
		/// Clears the list of command line options.
		virtual void clearOptions();
		
		/// Clears the list of command line parameters.
		virtual void clearParams();
		
		/// Print debug information.
		virtual void printDebugInfo();
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog();
};

/// @}

}

}

/** \file CLArgs.hpp
 * \brief Command line argument parser header.
 */
#endif
