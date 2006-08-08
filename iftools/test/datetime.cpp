/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * datetime.cpp                  DateTime test.
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

#include <iostream>
#include <string>
#include "ionflux/DateTime.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	string testTimestamp = "2004-02-05 10:30:00";
	int nthWeekDay = -1;
	int n = -1;
	string timeZoneLocation = "UTC";
	if (argc == 0)
	{
		cout << "datetime <test date> [<time zone location>] "
			    "[<day of week> <n>]" << endl
			 << "test date - A timestamp for which to test DateTime features."
			 << endl
			 << "time zone location - Time zone location name." << endl
			 << "day of week - Day of week for occurence testing (0...6, where"
			 	" 0 = Sunday)." << endl
			 << "n - Find n-th occurence of day of week (0...5, where 5 ="
			 	" last occurence).";
	}
	if (argc >= 2)
		testTimestamp = argv[1];
	if (argc >= 3)
	{
		timeZoneLocation = argv[2];
	}
	if (argc >= 5)
	{
		nthWeekDay = strtol(argv[3], 0, 10);
		n = strtol(argv[4], 0, 10);
	}
	time_t now = time(0);
	DateTime posixEpoch(1970, 1, 1, 0, 0, 0);
	DateTime testDT(testTimestamp);
	DateTime localTestDT(testTimestamp);
	localTestDT.setTimeZone(timeZoneLocation);
	DateTime nowDT(now);
	DateTime localDT(now);
	localDT.setTimeZone(timeZoneLocation);
	/* ----- //
	TimeTicks TICKS_1Y = (365 + DateTime::countLeapYears(2)) * 24 * 60 * 60;
	cout << "Ticks per 1 Years:          " << TICKS_1Y << endl;
	// ----- */
	cout << "Tick count for POSIX epoch:            " << posixEpoch.getTicks() 
		 << endl;
	cout << "Tick count for now:                    " << nowDT.getTicks() 
		 << endl;
	cout << "Tick count for test datetime:          " << testDT.getTicks() 
		 << endl;
	cout << "POSIX time (calculated):               " << (nowDT - posixEpoch) 
		 << endl;
	cout << "POSIX time (from time()):              " << now << endl;
	cout << "Tick error:                            " << (now - (nowDT 
		 - posixEpoch)) << endl;
	cout << "Day of week for POSIX epoch:           " 
		 << posixEpoch.getDayOfWeek() << " (" << posixEpoch.getDayOfWeekName() 
		 << ")" << endl;
	cout << "Day of week for now (UTC):             " << nowDT.getDayOfWeek() 
		 << " (" << nowDT.getDayOfWeekName() << ")" << endl;
	cout << "Day of week for now (local):           " << localDT.getDayOfWeek() 
		 << " (" << localDT.getDayOfWeekName() << ")" << endl;
	cout << "Day of week for test datetime (UTC):   " << testDT.getDayOfWeek() 
		 << " (" << testDT.getDayOfWeekName() << ")" << endl;
	cout << "Day of week for test datetime (local): " 
		 << localTestDT.getDayOfWeek() << " (" 
		 << localTestDT.getDayOfWeekName() << ")" << endl;
	cout << "Day of year for POSIX epoch:           " 
		 << posixEpoch.getDayOfYear() << endl;
	cout << "Day of year for now:                   " << nowDT.getDayOfYear() 
	     << endl;
	cout << "Day of year for test datetime:         " << testDT.getDayOfYear() 
	     << endl;
	cout << "Timestamp for POSIX epoch:             " 
		 << posixEpoch.getTimestamp() << endl;
	cout << "Timestamp for now (UTC):               " << nowDT.getTimestamp() 
		 << endl;
	cout << "Timestamp for now (local):             " << localDT.getTimestamp() 
		 << " " << localDT.getTimeZoneName() << endl;
	cout << "Timestamp for test datetime (UTC):     " << testDT.getTimestamp() 
		 << endl;
	cout << "Timestamp for test datetime (local):   " 
		 << localTestDT.getTimestamp() << " " << localTestDT.getTimeZoneName() 
		 << endl;
	if ((nthWeekDay >= 0) && (n > 0))
	{
		ostringstream status;
		if (n == 1)
			status << "First occurrence";
		else
		if (n >= 5)
			status << "Last occurence";
		else
			status << "Occurence #" << n;
		cout << status.str() << " of " 
			<< DateTime::WEEKDAY_NAME[nthWeekDay] << " in " 
			<< DateTime::MONTH_NAME[testDT.getMonth() - 1] << " " 
			<< testDT.getYear() << ": " << DateTime::getNth(testDT.getYear(),
				testDT.getMonth(), nthWeekDay, n).getTimestamp().substr(0, 10) 
			<< endl;
	}
	return 0;
}

/** \file datetime.cpp
 * \brief DateTime test.
 */
