#ifndef IONFLUX_TOOLS_DATETIME
#define IONFLUX_TOOLS_DATETIME
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DateTime.hpp                    Date and time wrapper.
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

#include <time.h>
#ifdef HAVE_INTTYPES
	#include <inttypes.h>
#else
	#include <stdint.h>
#endif
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "ionflux/tools.hpp"
#include "ionflux/TimeZone.hpp"

namespace Ionflux
{

namespace Tools
{

class TimeZone;

/** \addtogroup datetime Date and time
 *
 * Tools for handling date and time.
 *
 * @{
 */

/// UTC seconds since 0001-01-01 00:00:00.
typedef int64_t TimeTicks;
/// Year.
typedef int64_t Year;

/** Date and Time.
 *
 * Date and time wrapper with various manipulation and conversion facilities.
 */
class DateTime
{
	protected:
		/// Number of UTC seconds since 0001-01-01 00:00:00.
		TimeTicks ticks;
		/// Timestamp (string representation, "YYYY-MM-DD HH:MM:SS").
		std::string timestamp;
		/// Local time zone.
		const TimeZone *timeZone;
		/// Broken down time: Year.
		Year year;
		/// Broken down time: Month (1...12).
		int month;
		/// Broken down time: Day of month (1...31).
		int day;
		/// Broken down time: Hour (0...23).
		int hour;
		/// Broken down time: Minute (0...59).
		int minute;
		/// Broken down time: Second (0...59).
		int second;
		/// Broken down time: Day of week (0...6, where 0 = Sunday).
		int weekDay;
		/// Broken down time: Day of year (1...366).
		int yearDay;
		/// Broken down time: DST flag.
		bool dstState;
		/// Broken down time: UTC offset (minutes).
		int utcOffset;
		/// Time zone memory management flag.
		bool manageTimeZone;
		/// Vector of default time zones.
		std::vector<const TimeZone *> defaultTimeZones;
		
		/** Parse a timestamp.
		 *
		 * Parse a timestamp in string representation ("YYYY-MM-DD HH:MM:SS").
		 *
		 * \param source Timestamp.
		 */
		virtual void parseTimestamp(const std::string &source);
		
		/** Create a timestamp.
		 *
		 * Create a timestamp in string representation ("YYYY-MM-DD HH:MM:SS").
		 *
		 * \sa getTimestamp()
		 *
		 * \return Timestamp.
		 */
		virtual std::string createTimestamp();
		
		/// Update ticks from broken down calendar time.
		virtual void updateTicks();
		
		/** Update broken down calendar time from ticks.
		 *
		 * Updates the broken down calendar time from the UTC ticks. An 
		 * additional offset may be specified to calculate local time.
		 *
		 * \param tickOffset Tick offset.
		 */
		virtual void updateBrokenDownTime(int tickOffset);
		
		/// Initialize default time zones.
		virtual void initTimeZones();
		
	public:
		/// Timestamp date separator.
		static const std::string TIMESTAMP_DATE_SEP;
		/// Timestamp time separator.
		static const std::string TIMESTAMP_TIME_SEP;
		/// Timestamp datetime separator.
		static const std::string TIMESTAMP_DATETIME_SEP;
		/** Number of days up to the beginning of the first day of month 
		 * j + 1 for non-leap years (NUM_DAYS[0...11]) and leap years 
		 * (NUM_DAYS[12...23]). */
		static const int NUM_DAYS[];
		/// Leap month.
		static const int LEAP_MONTH;
		/// Start tick count for POSIX epoch.
		static const TimeTicks POSIX_EPOCH;
		/// Leap year neutral tick step: 400 years.
		static const TimeTicks TICKS_400Y;
		/// Leap year neutral tick step: 100 years.
		static const TimeTicks TICKS_100Y;
		/// Leap year neutral tick step: 4 years.
		static const TimeTicks TICKS_4Y;
		/// Leap year neutral tick step: 3 years.
		static const TimeTicks TICKS_3Y;
		/// Leap year neutral tick step: 1 year.
		static const TimeTicks TICKS_1Y;
		/// Ticks per day.
		static const TimeTicks TICKS_1D;
		/// Reference ticks of a sunday.
		static const TimeTicks REF_SUNDAY;
		/// Weekday names.
		static const char *WEEKDAY_NAME[];
		/// Weekday names (short).
		static const char *WEEKDAY_NAME_SHORT[];
		/// Month names.
		static const char *MONTH_NAME[];
		/// Month names (short).
		static const char *MONTH_NAME_SHORT[];
		/// Time zone: UTC.
		static const TimeZone TZ_UTC;
		/// Time zone: UTC+0100.
		static const TimeZone TZ_UTC_P0100;
		/// Time zone: UTC+0200.
		static const TimeZone TZ_UTC_P0200;
		/// Time zone: UTC+0300.
		static const TimeZone TZ_UTC_P0300;
		/// Time zone: UTC+0330.
		static const TimeZone TZ_UTC_P0330;
		/// Time zone: UTC+0400.
		static const TimeZone TZ_UTC_P0400;
		/// Time zone: UTC+0430.
		static const TimeZone TZ_UTC_P0430;
		/// Time zone: UTC+0500.
		static const TimeZone TZ_UTC_P0500;
		/// Time zone: UTC+0530.
		static const TimeZone TZ_UTC_P0530;
		/// Time zone: UTC+0545.
		static const TimeZone TZ_UTC_P0545;
		/// Time zone: UTC+0600.
		static const TimeZone TZ_UTC_P0600;
		/// Time zone: UTC+0630.
		static const TimeZone TZ_UTC_P0630;
		/// Time zone: UTC+0700.
		static const TimeZone TZ_UTC_P0700;
		/// Time zone: UTC+0800.
		static const TimeZone TZ_UTC_P0800;
		/// Time zone: UTC+0900.
		static const TimeZone TZ_UTC_P0900;
		/// Time zone: UTC+0930.
		static const TimeZone TZ_UTC_P0930;
		/// Time zone: UTC+1000.
		static const TimeZone TZ_UTC_P1000;
		/// Time zone: UTC+1100.
		static const TimeZone TZ_UTC_P1100;
		/// Time zone: UTC+1100.
		static const TimeZone TZ_UTC_P1200;
		/// Time zone: UTC-0100.
		static const TimeZone TZ_UTC_M0100;
		/// Time zone: UTC-0200.
		static const TimeZone TZ_UTC_M0200;
		/// Time zone: UTC-0300.
		static const TimeZone TZ_UTC_M0300;
		/// Time zone: UTC-0400.
		static const TimeZone TZ_UTC_M0400;
		/// Time zone: UTC-0500.
		static const TimeZone TZ_UTC_M0500;
		/// Time zone: UTC-0600.
		static const TimeZone TZ_UTC_M0600;
		/// Time zone: UTC-0700.
		static const TimeZone TZ_UTC_M0700;
		/// Time zone: UTC-0800.
		static const TimeZone TZ_UTC_M0800;
		/// Time zone: UTC-0900.
		static const TimeZone TZ_UTC_M0900;
		/// Time zone: UTC-1000.
		static const TimeZone TZ_UTC_M1000;
		/// Time zone: UTC-1100.
		static const TimeZone TZ_UTC_M1100;
		/// Time zone: UTC-1100.
		static const TimeZone TZ_UTC_M1200;
		/// Time zone: GMT.
		static const TimeZone TZ_GMT;
		/// Time zone: Europe/Western (WET/WEST).
		static const TimeZone TZ_EUROPE_WESTERN;
		/// Time zone: Europe/Central (CET/CEST).
		static const TimeZone TZ_EUROPE_CENTRAL;
		/// Time zone: Europe/Eastern (EET/EEST).
		static const TimeZone TZ_EUROPE_EASTERN;
		/// Time zone: United Kingdom (WET/BST).
		static const TimeZone TZ_UK;
		/// Time zone: USA/Eastern (EST/EDT).
		static const TimeZone TZ_USA_EASTERN;
		/// Time zone: USA/Central (CST/CDT).
		static const TimeZone TZ_USA_CENTRAL;
		/// Time zone: USA/Mountain (MST/MDT).
		static const TimeZone TZ_USA_MOUNTAIN;
		/// Time zone: USA/Pacific (PST/PDT).
		static const TimeZone TZ_USA_PACIFIC;
		/// Time zone: USA/Alaska (AKST/AKDT).
		static const TimeZone TZ_USA_ALASKA;
		/// Time zone: Russia/Western (UTC+03).
		static const TimeZone TZ_RUSSIA_WESTERN;
		/// Time zone: Egypt (UTC+02).
		static const TimeZone TZ_EGYPT;
		
		/** Constructor.
		 *
		 * Construct new DateTime object which will be initialized with the 
		 * current local time.
		 */
		DateTime();
		
		/** Constructor.
		 *
		 * Construct new DateTime object which will be initialized with the
		 * POSIX timestamp passed as an argument.
		 *
		 * \param initTime POSIX timestamp.
		 */
		DateTime(time_t initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object which will be initialized with the
		 * UTC seconds passed as an argument.
		 *
		 * \param initTime Number of UTC seconds since 0001-01-01 00:00:00.
		 */
		DateTime(TimeTicks initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object which will be initialized with the
		 * broken down calendar time passed as an argument.
		 *
		 * \param initTime Broken down calendar time.
		 */
		DateTime(struct tm initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object which will be initialized with the
		 * timestamp (string representation, "YYYY-MM-DD HH:MM:SS") passed as 
		 * an argument.
		 *
		 * \param initTime Timestamp.
		 */
		DateTime(const std::string &initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object which will be initialized with 
		 * another DateTime object.
		 *
		 * \param initTime DateTime object.
		 */
		DateTime(const DateTime &initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object which will be initialized with 
		 * the specified date and time.
		 *
		 * \param initYear Year.
		 * \param initMonth Month (1...12).
		 * \param initDay Day of month (1...31).
		 * \param initHour Hour (0...23).
		 * \param initMinute (0...59).
		 * \param initSecond (0...59).
		 */
		DateTime(int initYear, int initMonth, int initDay, int initHour, 
			int initMinute, int initSecond);
		
		/** Destructor.
		 *
		 * Destruct DateTime object.
		 */
		virtual ~DateTime();
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 *
		 * \param newTime POSIX timestamp.
		 *
		 * \sa setLocalTime()
		 */
		virtual void setTime(time_t newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 *
		 * \param newTime Number of UTC seconds since 0001-01-01 00:00:00.
		 *
		 * \sa setLocalTime()
		 */
		virtual void setTime(TimeTicks newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 *
		 * \param newTime Broken down calendar time.
		 *
		 * \sa setLocalTime()
		 */
		virtual void setTime(tm newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 *
		 * \param newTime Timestamp.
		 *
		 * \sa setLocalTime()
		 */
		virtual void setTime(const std::string &newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 *
		 * \param newTime DateTime object.
		 *
		 * \sa setLocalTime()
		 */
		virtual void setTime(const DateTime &newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 *
		 * \param newYear Year.
		 * \param newMonth Month (1...12).
		 * \param newDay Day of month (1...31).
		 * \param newHour Hour (0...23).
		 * \param newMinute (0...59).
		 * \param newSecond (0...59).
		 *
		 * \sa setLocalTime()
		 */
		virtual void setTime(int newYear, int newMonth, int newDay, 
			int newHour, int newMinute, int newSecond);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 *
		 * \note The source datetime will be treated as local time, regardless 
		 * of its time zone setting. If you want to set local time from 
		 * another equivalent local time (i.e. both times represent the same 
		 * UTC time), you should use standard assignment or setTime() instead 
		 * of this function.
		 *
		 * \param newTime Source datetime.
		 * \param newDSTState Whether this local time represents daylight 
		 * saving time.
		 *
		 * \sa setTimeZone() setTime()
		 */
		virtual void setLocalTime(const DateTime &newTime, bool newDSTState);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 *
		 * \param newTime Timestamp.
		 * \param newDSTState Whether this local time represents daylight 
		 * saving time.
		 *
		 * \sa setTimeZone()
		 */
		virtual void setLocalTime(const std::string &newTime, bool newDSTState);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 *
		 * \param newYear Year.
		 * \param newMonth Month (1...12).
		 * \param newDay Day of month (1...31).
		 * \param newHour Hour (0...23).
		 * \param newMinute (0...59).
		 * \param newSecond (0...59).
		 * \param newDSTState Whether this local time represents daylight 
		 * saving time.
		 *
		 * \sa setTimeZone()
		 */
		virtual void setLocalTime(int newYear, int newMonth, int newDay, 
			int newHour, int newMinute, int newSecond, bool newDSTState);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 *
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled). The source datetime will be treated as local time, 
		 * regardless of its time zone setting. If you want to set local time 
		 * from another equivalent local time (i.e. both times represent the 
		 * same UTC time), you should use standard assignment or setTime() 
		 * instead of this function.
		 *
		 * \param newTime Source datetime.
		 *
		 * \sa setTimeZone() setTime() TimeZone::localIsDST()
		 */
		virtual void setLocalTime(const DateTime &newTime);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 *
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param newTime Timestamp.
		 *
		 * \sa setTimeZone() TimeZone::localIsDST()
		 */
		virtual void setLocalTime(const std::string &newTime);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 *
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param newYear Year.
		 * \param newMonth Month (1...12).
		 * \param newDay Day of month (1...31).
		 * \param newHour Hour (0...23).
		 * \param newMinute (0...59).
		 * \param newSecond (0...59).
		 *
		 * \sa setTimeZone() TimeZone::localIsDST()
		 */
		virtual void setLocalTime(int newYear, int newMonth, int newDay, 
			int newHour, int newMinute, int newSecond);
		
		/** Set time of day.
		 *
		 * Sets the time of day (UTC).
		 *
		 * \param newHour Hour (0...23).
		 * \param newMinute (0...59).
		 * \param newSecond (0...59).
		 */
		virtual void setHMS(int newHour, int newMinute, int newSecond);
		
		/** Set time of day.
		 *
		 * Sets the time of day (UTC).
		 *
		 * \param newTime Time of day (string representation, "HH[:MM[:SS]]").
		 */
		virtual void setHMS(const std::string &newTime);
		
		/** Set time of day.
		 *
		 * Sets the time of day (UTC).
		 *
		 * \param sourceTime DateTime to set the time of day from.
		 */
		virtual void setHMS(const DateTime &sourceTime);
		
		/** Set time of day.
		 *
		 * Sets the time of day (local time).
		 *
		 * \param newHour Hour (0...23).
		 * \param newMinute (0...59).
		 * \param newSecond (0...59).
		 * \param newDSTState Whether this local time represents daylight 
		 * saving time.
		 *
		 * \sa setTimeZone() setHMS()
		 */
		virtual void setLocalHMS(int newHour, int newMinute, int newSecond, 
			bool newDSTState);
		
		/** Set time of day.
		 *
		 * Sets the time of day (local time).
		 *
		 * \param newTime Time of day (string representation, "HH[:MM[:SS]]").
		 * \param newDSTState Whether this local time represents daylight 
		 * saving time.
		 *
		 * \sa setTimeZone() setHMS()
		 */
		virtual void setLocalHMS(const std::string &newTime, bool newDSTState);
		
		/** Set time of day.
		 *
		 * Sets the time of day (local time).
		 *
		 * \param sourceTime DateTime to set the time of day from.
		 * \param newDSTState Whether this local time represents daylight 
		 * saving time.
		 *
		 * \sa setTimeZone() setHMS()
		 */
		virtual void setLocalHMS(const DateTime &sourceTime, bool newDSTState);
		
		/** Set time of day.
		 *
		 * Sets the time of day (local time).
		 *
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param newHour Hour (0...23).
		 * \param newMinute (0...59).
		 * \param newSecond (0...59).
		 *
		 * \sa setTimeZone() setHMS() TimeZone::localIsDST()
		 */
		virtual void setLocalHMS(int newHour, int newMinute, int newSecond);
		
		/** Set time of day.
		 *
		 * Sets the time of day (local time).
		 *
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param newTime Time of day (string representation, "HH[:MM[:SS]]").
		 *
		 * \sa setTimeZone() setHMS() TimeZone::localIsDST()
		 */
		virtual void setLocalHMS(const std::string &newTime);
		
		/** Set time of day.
		 *
		 * Sets the time of day (local time).
		 *
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param sourceTime DateTime to set the time of day from.
		 *
		 * \sa setTimeZone() setHMS() TimeZone::localIsDST()
		 */
		virtual void setLocalHMS(const DateTime &sourceTime);
		
		/** Create broken down calendar time.
		 *
		 * Creates a broken down calendar time from a POSIX timestamp.
		 *
		 * \note This is not thread-safe on systems that do not provide 
		 * localtime_r (i.e. win32).
		 *
		 * \deprecated You should not use this, since this function may not be 
		 * thread-safe on all systems. Besides, struct tm is obsolete and 
		 * inconsistent. Use getYear(), getMonth(), getDay() etc. instead. 
		 * This function is provided for backward compatibility only.
		 */
		static void makeBrokenTime(time_t *source, tm *target);
		
		/** Count leap years.
		 *
		 * Count the number of leap years from 0001-01-01 00:00:00 up to
		 * January 1st, 00:00:00 of the specified year.
		 *
		 * \param limit Limit for counting leap years.
		 *
		 * \return Number of leap years up to specified year.
		 */
		static Year countLeapYears(Year limit);
		
		/** Check leap year status.
		 *
		 * Returns \c true if the specified year is a leap year.
		 *
		 * \param checkYear Year.
		 *
		 * \return \c true if specified year is a leap year, \c false 
		 * otherwise.
		 */
		static bool isLeapYear(Year checkYear);
		
		/** Get n-th occurence of a day of week in a month.
		 *
		 * Returns the UTC DateTime of the start (00:00:00) of the n-th 
		 * occurrence of the specified day of week in the specified month of 
		 * the specified year. If this day is not present in the requested 
		 * month, the last occurence of that day in the specified month is 
		 * returned. You can use this to get the last occurence of any day of 
		 * week within a month by setting n to 5;
		 *
		 * \param targetYear Year.
		 * \param targetMonth Month (1...12).
		 * \param targetWeekDay Day of week (0...6, where 0 = Sunday).
		 * \param n Occurrence count of day of week in specified month (1...5)
		 *
		 * \return Datetime of n-th occurence of specified day of week..
		 */
		static DateTime getNth(Year targetYear, int targetMonth, 
			int targetWeekDay, int n);
		
		/** Shift DateTime.
		 *
		 * Shifts a DateTime by a specified amount of seconds. (This may be 
		 * used for TimeZone transformations or DateTime arithmetic.)
		 *
		 * \param shiftSeconds Amount of seconds to shift this DateTime.
		 *
		 * \return Datetime shifted by specified amount of seconds.
		 */
		virtual DateTime &shift(int shiftSeconds);
		
		/** Calculate DateTime difference.
		 *
		 * Calculate the difference (in seconds) of two DateTime objects.
		 *
		 * \param diffTime DateTime to substract.
		 *
		 * \return Difference of the datetimes, in seconds.
		 */
		virtual TimeTicks diff(const DateTime &diffTime) const;
		
		/** Set time zone.
		 *
		 * Sets the time zone of the local time to specified TimeZone object.
		 *
		 * \param newTimeZone Time zone.
		 * \param newManage Whether allocated memory for the TimeZone object 
		 * should be managed.
		 */
		virtual void setTimeZone(const TimeZone *newTimeZone, bool newManage);
		
		/** Set time zone.
		 *
		 * Sets the time zone of the local time by alias name. If no time zone 
		 * of the specified alias name is found, UTC is assumed.
		 *
		 * \param newTimeZone Time zone alias name.
		 */
		virtual void setTimeZone(const std::string &newTimeZone);
		
		/** Compare time of day.
		 *
		 * Compares time of day (HH:MM:SS) only, without respect to time zone 
		 * or DST offsets.
		 *
		 * \param otherHour Hour (0...23).
		 * \param otherMinute (0...59).
		 * \param otherSecond (0...59).
		 *
		 * \return 0 if the times of day are equal, -1 if the time of day of 
		 * this object is less than, +1 if it is greater than the time of day 
		 * of the argument.
		 */
		virtual int compareHMS(int otherHour, int otherMinute, int otherSecond);
		
		/** Compare time of day.
		 *
		 * Compares time of day (HH:MM:SS) only, without respect to time zone 
		 * or DST offsets.
		 *
		 * \param otherTime DateTime to compare this object with.
		 *
		 * \return 0 if the times of day are equal, -1 if the time of day of 
		 * this object is less than, +1 if it is greater than the time of day 
		 * of the argument.
		 */
		virtual int compareHMS(const DateTime &otherTime);
		
		/** Compare time of day.
		 *
		 * Compares time of day (HH:MM:SS) only, without respect to time zone 
		 * or DST offsets.
		 *
		 * \param otherTime Time of day to compare this object with (string 
		 * representation, "HH[:MM[:SS]]").
		 *
		 * \return 0 if the times of day are equal, -1 if the time of day of 
		 * this object is less than, +1 if it is greater than the time of day 
		 * of the argument.
		 */
		virtual int compareHMS(const std::string &otherTime);
		
		/** Compare day.
		 *
		 * Compares day to that of another Datetime.
		 *
		 * \param otherTime DateTime to compare this object with.
		 *
		 * \return 0 if the days are equal, -1 if the day of this object is 
		 * less than, +1 if it is greater than the day of the argument.
		 */
		virtual int compareDay(const DateTime &otherTime);
		
		/** Check time.
		 *
		 * Check whether the specified string represents a time of day (i.e. 
		 * has the format"HH[:MM[:SS]]"). Range checks are performed for 
		 * hours, minutes and seconds.
		 *
		 * \param checkTime String to be checked.
		 *
		 * \return \c true if \c checkTime represents a time of day, \c false 
		 * otherwise.
		 */
		static bool isTime(const std::string &checkTime);
		
		/** Check date.
		 *
		 * Check whether the specified string represents a date (i.e. has the 
		 * format "YYYY-MM-DD"). Range checks are performed for month and day, 
		 * however, it is not checked whether the specified day is actually 
		 * a valid date.
		 *
		 * \param checkDate String to be checked.
		 *
		 * \return \c true if \c checkDate represents a date, \c false 
		 * otherwise.
		 */
		static bool isDate(const std::string &checkDate);
		
		/** Check datetime.
		 *
		 * Check whether the specified string represents a datetime (i.e. 
		 * has the format "YYYY-MM-DD[ HH[:MM[:SS]]]"). Range checks are 
		 * performed for hours, minutes, seconds, month and day, however, it 
		 * is not checked whether the specified datetime is actually a valid 
		 * date.
		 *
		 * \param checkDatetime String to be checked.
		 *
		 * \return \c true if \c checkDatetime represents a datetime, \c false 
		 * otherwise.
		 */
		static bool isDatetime(const std::string &checkDatetime);
		
		/** Get UTC representation.
		 *
		 * Get an UTC representation of a datetime.
		 *
		 * \return UTC datetime.
		 */
		virtual DateTime getUTC();
		
		/** Get UTC seconds.
		 *
		 * Get datetime as number of UTC seconds since 0001-01-01 00:00:00 
		 * (not counting leap seconds).
		 *
		 * \return UTC seconds since 0001-01-01 00:00:00.
		 */
		virtual TimeTicks getTicks() const;
		
		/** Get POSIX timestamp.
		 *
		 * Get datetime as POSIX timestamp, i.e. number of seconds since the 
		 * beginning of the POSIX epoch.
		 *
		 * \deprecated You should not use this, since the range of POSIX 
		 * timestamps is limited to the years 1970 to 2038. Use getTicks() 
		 * instead. This function is provided for backward compatibility only.
		 *
		 * \return POSIX timestamp.
		 */
		virtual time_t getTime() const;
		
		/** Get broken down calendar time.
		 *
		 * \note This is not thread-safe on systems that do not provide 
		 * localtime_r (i.e. win32).
		 *
		 * \deprecated You should not use this, since this function may not be 
		 * thread-safe on all systems. Besides, struct tm is obsolete and 
		 * inconsistent. Use getYear(), getMonth(), getDay() etc. instead. 
		 * This function is provided for backward compatibility only.
		 *
		 * \return Broken down time.
		 */
		virtual tm getBrokenTime() const;
		
		/** Get timestamp.
		 *
		 * Get timestamp in string representation ("YYYY-MM-DD HH:MM:SS").
		 *
		 * \return Timestamp.
		 */
		virtual std::string getTimestamp();
		
		/** Get time of day.
		 * 
		 * Get time of day in string representation ("HH:MM:SS").
		 *
		 * \return Time of day.
		 */
		virtual std::string getHMS();
		
		/** Get year.
		 *
		 * \return Year.
		 */
		virtual Year getYear() const;
		
		/** Get month.
		 *
		 * \return Month (1...12).
		 */
		virtual int getMonth() const;
		
		/** Get day.
		 *
		 * \return Day of month (1...31).
		 */
		virtual int getDay() const;
		
		/** Get hour.
		 *
		 * \return Hour (0...23).
		 */
		virtual int getHour() const;
		
		/** Get minute.
		 *
		 * \return Minute (0...59).
		 */
		virtual int getMinute() const;
		
		/** Get second.
		 *
		 * \return Second (0...59).
		 */
		virtual int getSecond() const;
		
		/** Get day of week.
		 *
		 * \return Day of week (0...6, where 0 = Sunday).
		 */
		virtual int getDayOfWeek() const;
		
		/** Get day of year.
		 *
		 * \return Day of year (1...366).
		 */
		virtual int getDayOfYear() const;
		
		/** Get day of week name.
		 *
		 * \return Name of day of week.
		 */
		virtual std::string getDayOfWeekName() const;
		
		/** Get short day of week name.
		 *
		 * \return Short name of day of week.
		 */
		virtual std::string getDayOfWeekShortName() const;
		
		/** Get month name.
		 *
		 * \return Month name.
		 */
		virtual std::string getMonthName() const;
		
		/** Get month short name.
		 *
		 * \return Month short name.
		 */
		virtual std::string getMonthShortName() const;
		
		/** Get time zone.
		 *
		 * \return Time zone object used by this datetime, or 0 if no time 
		 * zone has been specified.
		 */
		virtual const TimeZone *getTimeZone() const;
		
		/** Get name of time zone.
		 *
		 * \return Time zone (short) name, including DST distinctions if 
		 * available.
		 */
		virtual std::string getTimeZoneName() const;
		
		/** Get time zone aliases.
		 *
		 * Get a colon (':') separated list of all recognized time zone 
		 * alias names. These are the names you can use to set the time zone 
		 * with setTimeZone().
		 *
		 * \return Colon (':') separated list of time zone alias names.
		 */
		virtual std::string getTimeZoneAliases() const;
		
		/** Get DST state.
		 *
		 * \return \c true if this datetime represents DST in the current time 
		 * zone, \c false otherwise.
		 */
		virtual bool isDST() const;
		
		/** Get UTC offset.
		 *
		 * \return UTC offset, in minutes.
		 */
		virtual int getUTCOffset() const;
		
		/** Get RFC 822 timestamp.
		 *
		 * \return RFC 822 timestamp.
		 */
		virtual std::string getRFCTimestamp() const;
		
		/// Assignment operator.
		virtual DateTime& operator=(const DateTime &newTime);
		
		/// Add operator.
		virtual DateTime& operator+=(TimeTicks seconds);
		
		/// Substract operator.
		virtual DateTime& operator-=(TimeTicks seconds);
		
		/// Substract operator.
		virtual TimeTicks operator-(const DateTime &diffTime) const;
		
		/// Comparison operator.
		virtual bool operator==(const DateTime &compTime) const;
		
		/// Comparison operator.
		virtual bool operator>(const DateTime &compTime) const;
		
		/// Comparison operator.
		virtual bool operator<(const DateTime &compTime) const;
		
		/// Comparison operator.
		virtual bool operator>=(const DateTime &compTime) const;
		
		/// Comparison operator.
		virtual bool operator<=(const DateTime &compTime) const;
};

/// @}

}

}

/** \file DateTime.hpp
 * \brief Date and time wrapper header.
 */
#endif
