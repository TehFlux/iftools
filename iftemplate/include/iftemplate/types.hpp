#ifndef IONFLUX_TEMPLATE_TYPES
#define IONFLUX_TEMPLATE_TYPES
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * types.hpp                     Types.
 * =========================================================================
 *
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
#include <vector>
#include <string>
#include <set>
#include <map>
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace Template
{

class Node;
class StringFilterFunction;
class File;

namespace StringManipulator
{

class StringManipulator;

}

/// Token type ID.
typedef int TokenTypeID;
/// Node ID.
typedef int NodeID;
/// Node data type ID.
typedef int NodeDataTypeID;
/// Node UID assignment mode.
typedef int NodeUIDMode;
/// Node traversal mode.
typedef int NodeTraversalMode;
/// Node indexing mode.
typedef int NodeIndexMode;

/// Token type.
struct TokenType
{
	/// Numeric token type ID.
	TokenTypeID typeID;
	/// Valid characters for this token type.
	std::string validChars;
	/** Whether to invert the matching behavior.
	 *
	 * Set the invert flag if you want a token type to match any character 
	 * except those specified in validChars.
	 */
	bool invert;
	/** Maximum characters a token of this type can have.
	 *
	 * Set this to 0 (zero) or less to match any amount of characters.
	 */
	int maxChars;
};

/// Token.
struct Token
{
	/// Numeric token type ID.
	int typeID;
	/// Token value.
	std::string value;
};

/// Vector of pointers to token type.
typedef std::vector<Ionflux::Template::TokenType*> TokenTypePtrVector;
/// Vector of token type.
typedef std::vector<Ionflux::Template::TokenType> TokenTypeVector;
/// Vector of node.
typedef std::vector<Ionflux::Template::Node*> NodeVector;

/// Name to Node map.
typedef std::map<std::string, Ionflux::Template::Node*> NodeNameMap;

/// Node reference type ID.
typedef int NodeRefTypeID;

/// Vector of string manipulators.
typedef std::vector<Ionflux::Template::StringManipulator::StringManipulator*> 
    StringManipulatorVector;
/// Vector of string filter functions.
typedef std::vector<Ionflux::Template::StringFilterFunction*> 
    StringFilterFunctionVector;

/// String manipulator by name map.
typedef std::map<std::string, 
    Ionflux::Template::StringManipulator::StringManipulator*> 
    StringManipulatorNameMap;

/// Vector of command line parameters.
typedef std::vector<std::string> CLParams;

/// Command line option.
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

/// Vector of command line options.
typedef std::vector<Ionflux::Template::CLOption*> CLOptionVector;

/// Acceptable command line option.
struct CLAcceptableOption
{
	/// Option identifier.
	std::string option;
	/// Whether this option can have a value.
	bool acceptValue;
};

/// Vector of acceptable command line options.
typedef std::vector<Ionflux::Template::CLAcceptableOption*> 
    CLAcceptableOptionVector;

class DateTime;

/// Time ticks.
typedef Ionflux::ObjectBase::Int64 TimeTicks;
//// Year.
typedef Ionflux::ObjectBase::Int64 Year;

/** Daylight saving time switching rule.
 *
 * Use this to specify a general rule on when to switch between daylight 
 * saving time and normal time.
 *
 * \note Switching times are specified in the time currently in effect at the 
 * time of switching, i.e. normal local time for DSR_TO_DST and local daylight 
 * saving time for DSR_TO_NORMAL.
 */
struct DSTSwitchingRule
{
	/// Switching rule type: To DST.
	static const int DSR_TYPE_TO_DST = 0;
	/// Switching rule type: To normal.
	static const int DSR_TYPE_TO_NORMAL = 1;
	/// Switching rule type.
	int type;
	/// Month (1...12).
	int month;
	/// Day of week (0...6 where 0 = Sunday).
	int weekDay;
	/** Week of month (1...5).
	 *
	 * 1 means the first week the specified day of week occurs in.\n
	 * 2...4 means the n-th week the specified day of week occurs in.\n
	 * 5 means the last week the specified day of week occurs in.
	 */
	int week;
	/// Hour (0...23).
	int hour;
	/// Minute (0...59).
	int minute;
	/// Second (0...59).
	int second;
};

class TimeZone;

/// Vector of time zones (constant).
typedef std::vector<const Ionflux::Template::TimeZone*> TimeZoneConstVector;

/// Vector of files.
typedef std::vector<Ionflux::Template::File> FileVector;

}

}

/** \file types.hpp
 * \brief Types (header).
 */
#endif
