#ifndef IONFLUX_TEMPLATE_CONFIGTYPES
#define IONFLUX_TEMPLATE_CONFIGTYPES
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * configtypes.hpp                     Types used by Config (header).
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
#include <string>
#include "iftemplate/treetypes.hpp"

namespace Ionflux
{

namespace Template
{

/// Configuration option.
struct ConfigOption
{
	/// option key
	std::string key;
	/// option value
	std::string value;
};

/// Configuration line.
struct ConfigLine
{
	/** Configuration option.
	 *
	 * If this line is a comment, option.key will be set to 
	 * \c '&lt;comment&gt;' and option.value to the verbatim text of the line 
	 * (excluding line terminators).
	 */
	Ionflux::Template::ConfigOption option;
	/// Line type.
	int type;
	/// Line type: Invalid option.
	static const int CL_INVALID;
	/// Line type: Configuration option.
	static const int CL_OPTION;
	/// Line type: Comment.
	static const int CL_COMMENT;
	/// Line type: Blank.
	static const int CL_BLANK;
	/// Line type: Nested configuration.
	static const int CL_NESTED;
	/// Line type: Root data.
	static const int CL_ROOT_DATA;
};

/** Configuration tree entry.
 *
 * Maps a line of a configuration file to a tree data entry (if available).
 *
 * \note If the configuration line represents a comment, the node of the data 
 * entry is set to 0.
 */
struct ConfigTreeEntry
{
	/// Configuration file line.
	Ionflux::Template::ConfigLine line;
	/// Data entry corresponding to the configuration line.
	Ionflux::Template::DataEntry data;
};

/// Vector of configuration tree entries.
typedef std::vector<Ionflux::Template::ConfigTreeEntry> ConfigTreeEntryVector;

}

}

/** \file configtypes.hpp
 * \brief Types used by Config (header).
 */
#endif
