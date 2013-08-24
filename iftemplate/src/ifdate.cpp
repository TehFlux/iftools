/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifdate.cpp                  World clock and datetime utility.
 * ==========================================================================
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

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ifobject/utils.hpp"
#include "iftemplate/CLArgs.hpp"
#include "iftemplate/DateTime.hpp"

using namespace std;
using namespace Ionflux::Template;
using namespace Ionflux::ObjectBase;

// Application version number.
const std::string APP_VERSION = "1.0.0";

void printHelp()
{
	cout << 
"Usage: ifdate <option> ...\n"
"Options:\n"
"  -h, --help      Print this help.\n"
"  -v, --version   Print version information.\n"
"  -a, --aliases   Print a list of recognized time zone alias names.\n"
"  -l <location>   Set time zone location (or alias name).\n"
"  -t <ticks>      Use time ticks (UTC seconds since 0001-01-01 00:00:00, not\n" 
"                  counting leap seconds) instead of current time.\n"
"  -p <posixtime>  Use POSIX timestamp instead of current time.\n"
"  -s <timestamp>  Use timestamp (YYYY-MM-DD HH:MM:SS) instead of current time.\n"
"  -L, --local     Treat timestamp as local time instead of UTC.\n"
"  -d, --dst       Force timestamp to be treated as daylight saving time (DST).\n"
"                  (Using this may result in invalid datetimes.)\n"
"  -o posix        Output POSIX timestamp.\n"
"     ticks        Output time ticks.\n"
"     timestamp    Output timestamp (default)."
	<< endl;
}

void printVersion()
{
	cout << "ifdate " << APP_VERSION << endl
		<< "Copyright (c) 2004 Joern P. Meier (mail@ionflux.org)" << endl
		<< "This is free software; see the source for copying conditions. " 
		   "There is NO" << endl
		<< "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
		<< "PARTICULAR PURPOSE." << endl;
}

int main(int argc, char* argv[])
{
	CLArgs args;
	args.addAcceptableOption("h", false);
	args.addAcceptableOption("help", false);
	args.addAcceptableOption("v", false);
	args.addAcceptableOption("version", false);
	args.addAcceptableOption("a", false);
	args.addAcceptableOption("aliases", false);
	args.addAcceptableOption("l", true);
	args.addAcceptableOption("L", false);
	args.addAcceptableOption("local", false);
	args.addAcceptableOption("d", false);
	args.addAcceptableOption("dst", false);
	args.addAcceptableOption("t", true);
	args.addAcceptableOption("p", true);
	args.addAcceptableOption("s", true);
	args.addAcceptableOption("o", true);
	args.setArgs(argc, argv);
	if (!args.optionsOK())
	{
		for (unsigned int i = 0; i < args.getInvalidOptions().size(); i++)
			cout << "Option not recognized: '" << args.getInvalidOptions()[i] 
				<< "'" << endl;
	}
	if (args.isSet("v") || args.isSet("version"))
	{
		printVersion();
		return 0;
	}
	if (args.isSet("h") || args.isSet("help") 
		|| (args.isSet("p") && args.isSet("s"))
		|| (args.isSet("p") && args.isSet("t"))
		|| (args.isSet("t") && args.isSet("s")))
	{
		printHelp();
		return 0;
	}
	DateTime now;
	if (args.isSet("a") || args.isSet("aliases"))
	{
		vector<string> aliases;
		string aliasTmp = now.getTimeZoneAliases();
		explode(aliasTmp, ":", aliases);
		sort(aliases.begin(), aliases.end());
		for (unsigned int i = 0; i < aliases.size(); i++)
			cout << aliases[i] << endl;
		return 0;
	}
	CLOption* locationOpt = args.getOption("l");
	CLOption* ticksOpt = args.getOption("t");
	CLOption* posixOpt = args.getOption("p");
	CLOption* timestampOpt = args.getOption("s");
	CLOption* outputOpt = args.getOption("o");
	CLOption* localOpt = args.getOption("L");
	if (localOpt == 0)
		localOpt = args.getOption("local");
	CLOption *dstOpt = args.getOption("d");
	if (dstOpt == 0)
		dstOpt = args.getOption("dst");
	std::string timeZoneLocation = "UTC";
	if (locationOpt != 0)
		timeZoneLocation = locationOpt->value;
	if (posixOpt != 0)
		now.setTimePosix(static_cast<time_t>(
			strtol(posixOpt->value.c_str(), 0, 10)));
	if (ticksOpt != 0)
		now.setTimeTicks(static_cast<TimeTicks>(
			strtoll(ticksOpt->value.c_str(), 0, 10)));
	now.setTimeZone(timeZoneLocation);
	if (timestampOpt != 0)
	{
		if (localOpt == 0)
			now.setTime(timestampOpt->value);
		else
		{
			if (dstOpt == 0)
				now.setLocalTime(timestampOpt->value);
			else
				now.setLocalTime(timestampOpt->value, true);
		}
	}
	if ((outputOpt == 0) || (outputOpt->value == "timestamp"))
	{
		cout << now.getTimestamp() << " " << now.getTimeZoneName() << endl;
	} else
	if (outputOpt->value == "posix")
		cout << now.getTimePosix() << endl;
	else
	if (outputOpt->value == "ticks")
		cout << now.getTicks() << endl;
	else
		cout << "Unknown output option." << endl;
	return 0;
}

/** \file ifdate.cpp
 * \brief World clock and datetime utility.
 */
