#ifndef IONFLUX_TEMPLATE_DATETIME
#define IONFLUX_TEMPLATE_DATETIME
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DateTime.hpp                    Date and time (header).
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
#include <ctime>
#include "iftemplate/constants.hpp"
#include "iftemplate/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

class TimeZone;

/// Class information for class DateTime.
class DateTimeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		DateTimeClassInfo();
		/// Destructor.
		virtual ~DateTimeClassInfo();
};

/** Date and time.
 * \ingroup iftemplate
 *
 * Date and time type with various manipulation and conversion facilities.
 */
class DateTime
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Broken down time: DST flag.
		bool dstState;
		/// Broken down time: UTC offset (minutes).
		int utcOffset;
		/// Timestamp (string representation, "YYYY-MM-DD HH:MM:SS").
		std::string timestamp;
		/// Default time zones.
		Ionflux::Template::TimeZoneConstVector defaultTimeZones;
		/// Number of UTC seconds since 0001-01-01 00:00:00.
		Ionflux::Template::TimeTicks ticks;
		/// time zone.
		Ionflux::Template::TimeZone* timeZone;
		/// Broken down time: year.
		Ionflux::Template::Year year;
		/// Broken down time: month.
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
		
		/** Parse a timestamp.
		 *
		 * Parse a timestamp in string representation ("YYYY-MM-DD HH:MM:SS").
		 *
		 * \param source timestamp.
		 */
		virtual void parseTimestamp(const std::string& source);
		
		/** Create a timestamp.
		 *
		 * Create a timestamp in string representation ("YYYY-MM-DD 
		 * HH:MM:SS").
		 * 
		 * \sa getTimestamp()
		 *
		 * \return Timestamp.
		 */
		virtual std::string createTimestamp();
		
		/** Update ticks from broken down calendar time.
		 *
		 * Update ticks from broken down calendar time.
		 */
		virtual void updateTicks();
		
		/** Update broken down calendar time from ticks.
		 *
		 * Updates the broken down calendar time from the UTC ticks. An 
		 * additional offset may be specified to calculate local time.
		 *
		 * \param tickOffset tick offset.
		 */
		virtual void updateBrokenDownTime(int tickOffset);
		
		/** Initialize default time zones.
		 *
		 * Initialize default time zones.
		 */
		virtual void initTimeZones();
		
	public:
		/// Timestamp date separator.
		static const std::string TIMESTAMP_DATE_SEP;
		/// Timestamp time separator.
		static const std::string TIMESTAMP_TIME_SEP;
		/// Timestamp date/time separator.
		static const std::string TIMESTAMP_DATETIME_SEP;
		/// Number of days up to the beginning of the first day of month j + 1 for non-leap years (NUM_DAYS[0...11]) and leap years (NUM_DAYS[12...23]).
		static const int NUM_DAYS[];
		/// Leap month.
		static const int LEAP_MONTH;
		/// Start tick count for POSIX epoch.
		static const Ionflux::Template::TimeTicks POSIX_EPOCH;
		/// Leap year neutral tick step: 400 years.
		static const Ionflux::Template::TimeTicks TICKS_400Y;
		/// Leap year neutral tick step: 100 years.
		static const Ionflux::Template::TimeTicks TICKS_100Y;
		/// Leap year neutral tick step: 4 years.
		static const Ionflux::Template::TimeTicks TICKS_4Y;
		/// Leap year neutral tick step: 3 years.
		static const Ionflux::Template::TimeTicks TICKS_3Y;
		/// Leap year neutral tick step: 1 year.
		static const Ionflux::Template::TimeTicks TICKS_1Y;
		/// Time ticks per day.
		static const Ionflux::Template::TimeTicks TICKS_1D;
		/// Reference tick value of a Sunday.
		static const Ionflux::Template::TimeTicks REF_SUNDAY;
		/// Weekday names.
		static const char* WEEKDAY_NAME[7];
		/// Weekday names (short).
		static const char* WEEKDAY_NAME_SHORT[7];
		/// Month names.
		static const char* MONTH_NAME[12];
		/// Month names (short).
		static const char* MONTH_NAME_SHORT[12];
		/// Time zone: UTC.
		static const Ionflux::Template::TimeZone TZ_UTC;
		/// Time zone: UTC+0100.
		static const Ionflux::Template::TimeZone TZ_UTC_P0100;
		/// Time zone: UTC+0200.
		static const Ionflux::Template::TimeZone TZ_UTC_P0200;
		/// Time zone: UTC+0300.
		static const Ionflux::Template::TimeZone TZ_UTC_P0300;
		/// Time zone: UTC+0330.
		static const Ionflux::Template::TimeZone TZ_UTC_P0330;
		/// Time zone: UTC+0400.
		static const Ionflux::Template::TimeZone TZ_UTC_P0400;
		/// Time zone: UTC+0430.
		static const Ionflux::Template::TimeZone TZ_UTC_P0430;
		/// Time zone: UTC+0500.
		static const Ionflux::Template::TimeZone TZ_UTC_P0500;
		/// Time zone: UTC+0530.
		static const Ionflux::Template::TimeZone TZ_UTC_P0530;
		/// Time zone: UTC+0545.
		static const Ionflux::Template::TimeZone TZ_UTC_P0545;
		/// Time zone: UTC+0600.
		static const Ionflux::Template::TimeZone TZ_UTC_P0600;
		/// Time zone: UTC+0630.
		static const Ionflux::Template::TimeZone TZ_UTC_P0630;
		/// Time zone: UTC+0700.
		static const Ionflux::Template::TimeZone TZ_UTC_P0700;
		/// Time zone: UTC+0800.
		static const Ionflux::Template::TimeZone TZ_UTC_P0800;
		/// Time zone: UTC+0900.
		static const Ionflux::Template::TimeZone TZ_UTC_P0900;
		/// Time zone: UTC+0930.
		static const Ionflux::Template::TimeZone TZ_UTC_P0930;
		/// Time zone: UTC+1000.
		static const Ionflux::Template::TimeZone TZ_UTC_P1000;
		/// Time zone: UTC+1100.
		static const Ionflux::Template::TimeZone TZ_UTC_P1100;
		/// Time zone: UTC+1200.
		static const Ionflux::Template::TimeZone TZ_UTC_P1200;
		/// Time zone: UTC-0100.
		static const Ionflux::Template::TimeZone TZ_UTC_M0100;
		/// Time zone: UTC-0200.
		static const Ionflux::Template::TimeZone TZ_UTC_M0200;
		/// Time zone: UTC-0300.
		static const Ionflux::Template::TimeZone TZ_UTC_M0300;
		/// Time zone: UTC-0400.
		static const Ionflux::Template::TimeZone TZ_UTC_M0400;
		/// Time zone: UTC-0500.
		static const Ionflux::Template::TimeZone TZ_UTC_M0500;
		/// Time zone: UTC-0600.
		static const Ionflux::Template::TimeZone TZ_UTC_M0600;
		/// Time zone: UTC-0700.
		static const Ionflux::Template::TimeZone TZ_UTC_M0700;
		/// Time zone: UTC-0800.
		static const Ionflux::Template::TimeZone TZ_UTC_M0800;
		/// Time zone: UTC-0900.
		static const Ionflux::Template::TimeZone TZ_UTC_M0900;
		/// Time zone: UTC-1000.
		static const Ionflux::Template::TimeZone TZ_UTC_M1000;
		/// Time zone: UTC-1100.
		static const Ionflux::Template::TimeZone TZ_UTC_M1100;
		/// Time zone: UTC-1200.
		static const Ionflux::Template::TimeZone TZ_UTC_M1200;
		/// Time zone: GMT.
		static const Ionflux::Template::TimeZone TZ_GMT;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_EUROPE_WESTERN;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_EUROPE_CENTRAL;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_EUROPE_EASTERN;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_UK;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_USA_EASTERN;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_USA_CENTRAL;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_USA_MOUNTAIN;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_USA_PACIFIC;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_USA_ALASKA;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_RUSSIA_WESTERN;
		/// Time zone:.
		static const Ionflux::Template::TimeZone TZ_EGYPT;
		/// Class information instance.
		static const DateTimeClassInfo dateTimeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new DateTime object.
		 */
		DateTime();
		
		/** Constructor.
		 *
		 * Construct new DateTime object.
		 *
		 * \param other Other object.
		 */
		DateTime(const Ionflux::Template::DateTime& other);
		
		/** Constructor.
		 *
		 * Construct new DateTime object.
		 *
		 * \param initTime Time tick value.
		 */
		DateTime(Ionflux::Template::TimeTicks initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object.
		 *
		 * \param initTime Broken down calendar time.
		 */
		DateTime(struct tm initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object.
		 *
		 * \param initTime Timestamp.
		 */
		DateTime(const std::string& initTime);
		
		/** Constructor.
		 *
		 * Construct new DateTime object.
		 *
		 * \param initYear year.
		 * \param initMonth month (1...12).
		 * \param initDay day of month (1...31).
		 * \param initHour hour (0...23).
		 * \param initMinute minute (0...59).
		 * \param initSecond second (0...59).
		 */
		DateTime(Ionflux::Template::Year initYear, int initMonth, int initDay, 
		int initHour, int initMinute, int initSecond);
		
		/** Destructor.
		 *
		 * Destruct DateTime object.
		 */
		virtual ~DateTime();
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 * 
		 * \sa setLocalTime()
		 *
		 * \param newTime POSIX time.
		 */
		virtual void setTimePosix(time_t newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 * 
		 * \sa setLocalTime()
		 *
		 * \param newTime Time ticks.
		 */
		virtual void setTimeTicks(Ionflux::Template::TimeTicks newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 * 
		 * \sa setLocalTime()
		 *
		 * \param newTime Broken down calendar time.
		 */
		virtual void setTime(struct tm newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 * 
		 * \sa setLocalTime()
		 *
		 * \param newTime Timestamp.
		 */
		virtual void setTime(const std::string& newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 * 
		 * \sa setLocalTime()
		 *
		 * \param newTime Datetime object.
		 */
		virtual void setTime(const Ionflux::Template::DateTime& newTime);
		
		/** Set time.
		 *
		 * Set the date and time (UTC) represented by this DateTime object.
		 * 
		 * \sa setLocalTime()
		 *
		 * \param newYear year.
		 * \param newMonth month (1...12).
		 * \param newDay day of month (1...31).
		 * \param newHour hour (0...23).
		 * \param newMinute minute (0...59).
		 * \param newSecond second (0...59).
		 */
		virtual void setTime(Ionflux::Template::Year newYear, int newMonth, int 
		newDay, int newHour, int newMinute, int newSecond);
		
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
		 * \sa setTimeZone() setTime()
		 *
		 * \param newTime Datetime object.
		 * \param newDSTState Whether this local time represents daylight saving 
		 * time.
		 */
		virtual void setLocalTime(const Ionflux::Template::DateTime& newTime, 
		bool newDSTState);
		
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
		 * \sa setTimeZone() setTime()
		 *
		 * \param newTime Timestamp.
		 * \param newDSTState Whether this local time represents daylight saving 
		 * time.
		 */
		virtual void setLocalTime(const std::string& newTime, bool newDSTState);
		
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
		 * \sa setTimeZone() setTime()
		 *
		 * \param newYear year.
		 * \param newMonth month (1...12).
		 * \param newDay day of month (1...31).
		 * \param newHour hour (0...23).
		 * \param newMinute minute (0...59).
		 * \param newSecond second (0...59).
		 * \param newDSTState Whether this local time represents daylight saving 
		 * time.
		 */
		virtual void setLocalTime(Ionflux::Template::Year newYear, int newMonth, 
		int newDay, int newHour, int newMinute, int newSecond, bool newDSTState);
		
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
		 * \sa setTimeZone() setTime() TimeZone::localIsDST()
		 *
		 * \param newTime Datetime object.
		 */
		virtual void setLocalTime(const Ionflux::Template::DateTime& newTime);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 * 
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 * 
		 * \sa setTimeZone() setTime() TimeZone::localIsDST()
		 *
		 * \param newTime Timestamp.
		 */
		virtual void setLocalTime(const std::string& newTime);
		
		/** Set local time.
		 *
		 * Set the local date and time represented by this DateTime object.
		 * 
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 * 
		 * \sa setTimeZone() setTime() TimeZone::localIsDST()
		 *
		 * \param newYear year.
		 * \param newMonth month (1...12).
		 * \param newDay day of month (1...31).
		 * \param newHour hour (0...23).
		 * \param newMinute minute (0...59).
		 * \param newSecond second (0...59).
		 */
		virtual void setLocalTime(Ionflux::Template::Year newYear, int newMonth, 
		int newDay, int newHour, int newMinute, int newSecond);
		
		/** Set time of day.
		 *
		 * Set the time of day (UTC).
		 *
		 * \param newHour hour (0...23).
		 * \param newMinute minute (0...59).
		 * \param newSecond second (0...59).
		 */
		virtual void setHMS(int newHour, int newMinute, int newSecond);
		
		/** Set time of day.
		 *
		 * Set the time of day (UTC).
		 *
		 * \param newTime Timestamp ("HH[:MM[:SS]]").
		 */
		virtual void setHMS(const std::string& newTime);
		
		/** Set time of day.
		 *
		 * Set the time of day (UTC).
		 *
		 * \param sourceTime Datetime object.
		 */
		virtual void setHMS(const Ionflux::Template::DateTime& sourceTime);
		
		/** Set time of day.
		 *
		 * Set the time of day (local time).
		 *
		 * \param newHour hour (0...23).
		 * \param newMinute minute (0...59).
		 * \param newSecond second (0...59).
		 * \param newDSTState Whether this local time represents daylight saving 
		 * time.
		 */
		virtual void setLocalHMS(int newHour, int newMinute, int newSecond, bool 
		newDSTState);
		
		/** Set time of day.
		 *
		 * Set the time of day (local time).
		 *
		 * \param newTime Timestamp ("HH[:MM[:SS]]").
		 * \param newDSTState Whether this local time represents daylight saving 
		 * time.
		 */
		virtual void setLocalHMS(const std::string& newTime, bool newDSTState);
		
		/** Set time of day.
		 *
		 * Set the time of day (local time).
		 *
		 * \param sourceTime Datetime object.
		 * \param newDSTState Whether this local time represents daylight saving 
		 * time.
		 */
		virtual void setLocalHMS(const Ionflux::Template::DateTime& sourceTime, 
		bool newDSTState);
		
		/** Set time of day.
		 *
		 * Set the time of day (local time).
		 * 
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param newHour hour (0...23).
		 * \param newMinute minute (0...59).
		 * \param newSecond second (0...59).
		 */
		virtual void setLocalHMS(int newHour, int newMinute, int newSecond);
		
		/** Set time of day.
		 *
		 * Set the time of day (local time).
		 * 
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param newTime Timestamp ("HH[:MM[:SS]]").
		 */
		virtual void setLocalHMS(const std::string& newTime);
		
		/** Set time of day.
		 *
		 * Set the time of day (local time).
		 * 
		 * \note This function will attempt to determine the DST state 
		 * automatically. Note that DST state is ambiguous during one hour of 
		 * the year (see TimeZone::localIsDST() for details on how this case 
		 * is handled).
		 *
		 * \param sourceTime Datetime object.
		 */
		virtual void setLocalHMS(const Ionflux::Template::DateTime& sourceTime);
		
		/** Shift Datetime.
		 *
		 * Shift a DateTime by a specified amount of seconds. (This may be 
		 * used for TimeZone transformations or DateTime arithmetic.)
		 *
		 * \param shiftSeconds Amount of seconds to shift this DateTime.
		 *
		 * \return Datetime shifted by specified amount of seconds.
		 */
		virtual Ionflux::Template::DateTime& shift(Ionflux::Template::TimeTicks 
		shiftSeconds);
		
		/** Calculate DateTime difference.
		 *
		 * Calculate the difference (in seconds) of two DateTime objects.
		 *
		 * \param diffTime DateTime to substract.
		 *
		 * \return Difference of the datetimes, in seconds.
		 */
		virtual Ionflux::Template::TimeTicks diff(const 
		Ionflux::Template::DateTime& diffTime);
		
		/** Set time zone.
		 *
		 * Sets the time zone of the local time by alias name. If no time zone
		 * of the specified alias name is found, UTC is assumed.
		 *
		 * \param newTimeZone Time zone alias name.
		 */
		virtual void setTimeZone(const std::string& newTimeZone);
		
		/** Compare time of day.
		 *
		 * Compare time of day (HH:MM:SS) only, without respect to time zone 
		 * or DST offsets.
		 *
		 * \param otherHour Hour (0...23).
		 * \param otherMinute Minute (0...59).
		 * \param otherSecond Second (0...59).
		 *
		 * \return 0 if the times of day are equal, -1 if the time of day of this
		 * object is less than, +1 if it is greater than the time of day of the 
		 * argument.
		 */
		virtual int compareHMS(int otherHour, int otherMinute, int otherSecond);
		
		/** Compare time of day.
		 *
		 * Compare time of day (HH:MM:SS) only, without respect to time zone 
		 * or DST offsets.
		 *
		 * \param otherTime DateTime to compare this object with.
		 *
		 * \return 0 if the times of day are equal, -1 if the time of day of this
		 * object is less than, +1 if it is greater than the time of day of the 
		 * argument.
		 */
		virtual int compareHMS(const Ionflux::Template::DateTime& otherTime);
		
		/** Compare time of day.
		 *
		 * Compare time of day (HH:MM:SS) only, without respect to time zone 
		 * or DST offsets.
		 *
		 * \param otherTime Timestamp ("HH[:MM[:SS]]").
		 *
		 * \return 0 if the times of day are equal, -1 if the time of day of this
		 * object is less than, +1 if it is greater than the time of day of the 
		 * argument.
		 */
		virtual int compareHMS(const std::string& otherTime);
		
		/** Compare day.
		 *
		 * Compare day to that of another Datetime.
		 *
		 * \param otherTime DateTime to compare this object with.
		 *
		 * \return 0 if the days are equal, -1 if the day of this object is less 
		 * than, +1 if it is greater than the day of the argument.
		 */
		virtual int compareDay(const Ionflux::Template::DateTime& otherTime);
		
		/** Get UTC representation.
		 *
		 * Get an UTC representation of this datetime.
		 *
		 * \return UTC datetime.
		 */
		virtual Ionflux::Template::DateTime getUTC();
		
		/** Get POSIX time.
		 *
		 * Get datetime as POSIX time, i.e. number of seconds since the 
		 * beginning of the POSIX epoch.
		 *
		 * \return POSIX time.
		 */
		virtual time_t getTimePosix() const;
		
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
		
		/** Get day of week name.
		 *
		 * Get day of week name.
		 *
		 * \return Name of day of week.
		 */
		virtual std::string getDayOfWeekName() const;
		
		/** Get day of week short name.
		 *
		 * Get day of week short name.
		 *
		 * \return Short name of day of week.
		 */
		virtual std::string getDayOfWeekShortName() const;
		
		/** Get month name.
		 *
		 * Get month name.
		 *
		 * \return Name of month.
		 */
		virtual std::string getMonthName() const;
		
		/** Get month short name.
		 *
		 * Get month short name.
		 *
		 * \return Short name of month.
		 */
		virtual std::string getMonthShortName() const;
		
		/** Get name of time zone.
		 *
		 * Get the short name of the time zone, including DST distinctions, if
		 * available.
		 *
		 * \return Name of time zone.
		 */
		virtual std::string getTimeZoneName() const;
		
		/** Get time zone aliases.
		 *
		 * Get a colon (':') separated list of all recognized time zone alias 
		 * names. These are the names you can use to set the time zone with 
		 * setTimeZone().
		 *
		 * \return Colon (':') separated list of time zone alias names.
		 */
		virtual std::string getTimeZoneAliases() const;
		
		/** Get DST state.
		 *
		 * Get DST state.
		 *
		 * \return \c true if this datetime represents DST in the current time 
		 * zone, \c false otherwise.
		 */
		virtual bool isDST() const;
		
		/** Get UTC offset.
		 *
		 * Get UTC offset.
		 *
		 * \return UTC offset, in minutes.
		 */
		virtual int getUTCOffset() const;
		
		/** Get RFC 822 timestamp.
		 *
		 * Get RFC 822 timestamp.
		 *
		 * \return RFC 822 timestamp.
		 */
		virtual std::string getRFCTimestamp() const;
		
		/** Add operator.
		 *
		 * Add time ticks to the datetime object.
		 *
		 * \param seconds time offset.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::DateTime& 
		operator+=(Ionflux::Template::TimeTicks seconds);
		
		/** Subtract operator.
		 *
		 * Subtract time ticks from the datetime object.
		 *
		 * \param seconds time offset.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::DateTime& 
		operator-=(Ionflux::Template::TimeTicks seconds);
		
		/** Subtract operator.
		 *
		 * Calculate the time difference (in seconds) between datetime 
		 * objects.
		 *
		 * \param diffTime datetime object.
		 *
		 * \return Difference between datetime objects (in seconds).
		 */
		virtual Ionflux::Template::TimeTicks operator-(const 
		Ionflux::Template::DateTime& diffTime) const;
		
		/** Comparison operator: equal.
		 *
		 * Compare datetime objects.
		 *
		 * \param compTime datetime object.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::Template::DateTime& compTime) 
		const;
		
		/** Comparison operator: not equal.
		 *
		 * Compare datetime objects.
		 *
		 * \param compTime datetime object.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::Template::DateTime& compTime) 
		const;
		
		/** Comparison operator: greater than.
		 *
		 * Compare datetime objects.
		 *
		 * \param compTime datetime object.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator>(const Ionflux::Template::DateTime& compTime) 
		const;
		
		/** Comparison operator: less than.
		 *
		 * Compare datetime objects.
		 *
		 * \param compTime datetime object.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator<(const Ionflux::Template::DateTime& compTime) 
		const;
		
		/** Comparison operator: greater than or equal.
		 *
		 * Compare datetime objects.
		 *
		 * \param compTime datetime object.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator>=(const Ionflux::Template::DateTime& compTime) 
		const;
		
		/** Comparison operator: less than or equal.
		 *
		 * Compare datetime objects.
		 *
		 * \param compTime datetime object.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator<=(const Ionflux::Template::DateTime& compTime) 
		const;
		
		/** Count leap years.
		 *
		 * Count the number of leap years from 0001-01-01 00:00:00 up to 
		 * January 1st, 00:00:00 of the specified year.
		 *
		 * \param limit Limit for counting leap years.
		 *
		 * \return Number of leap years up to specified year.
		 */
		static Ionflux::Template::Year countLeapYears(Ionflux::Template::Year 
		limit);
		
		/** Check leap year status.
		 *
		 * Check whether the specified year is a leap year.
		 *
		 * \param checkYear Year.
		 *
		 * \return \c true if specified year is a leap year, \c false otherwise.
		 */
		static bool isLeapYear(Ionflux::Template::Year checkYear);
		
		/** Get n-th occurence of a day of week in a month.
		 *
		 * Returns the UTC DateTime of the start (00:00:00) of the n-th 
		 * occurrence of the specified day of week in the specified month of 
		 * the specified year. If this day is not present in the requested 
		 * month, the last occurence of that day in the specified month is 
		 * returned. You can use this to get the last occurence of any day of 
		 * week within a month by setting n to 5.
		 *
		 * \param targetYear Year.
		 * \param targetMonth Month (1...12).
		 * \param targetWeekDay Day of week (0...6, where 0 = Sunday).
		 * \param n Occurrence count of day of week in specified month (1...5).
		 *
		 * \return Datetime of n-th occurence of specified day of week.
		 */
		static Ionflux::Template::DateTime getNth(Ionflux::Template::Year 
		targetYear, int targetMonth, int targetWeekDay, int n);
		
		/** Check time.
		 *
		 * Check whether the specified string represents a time of day (i.e. 
		 * has the format"HH[:MM[:SS]]"). Range checks are performed for 
		 * hours, minutes and seconds.
		 *
		 * \param checkTime string to be checked.
		 *
		 * \return \c true if \c checkTime represents a time of day, \c false 
		 * otherwise.
		 */
		static bool isTime(const std::string& checkTime);
		
		/** Check date.
		 *
		 * Check whether the specified string represents a date (i.e. has the 
		 * format "YYYY-MM-DD"). Range checks are performed for month and day,
		 * however, it is not checked whether the specified day is actually a 
		 * valid date.
		 *
		 * \param checkDate string to be checked.
		 *
		 * \return \c true if \c checkDate represents a date, \c false otherwise.
		 */
		static bool isDate(const std::string& checkDate);
		
		/** Check datetime.
		 *
		 * Check whether the specified string represents a datetime (i.e. has 
		 * the format "YYYY-MM-DD[ HH[:MM[:SS]]]"). Range checks are performed
		 * for hours, minutes, seconds, month and day, however, it is not 
		 * checked whether the specified datetime is actually a valid date.
		 *
		 * \param checkDatetime string to be checked.
		 *
		 * \return \c true if \c checkDate represents a datetime, \c false 
		 * otherwise.
		 */
		static bool isDatetime(const std::string& checkDatetime);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::DateTime& operator=(const 
		Ionflux::Template::DateTime& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::DateTime* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::DateTime* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::Template::DateTime* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new DateTime object.
		 *
		 * \param initTime Time tick value.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::DateTime* create(Ionflux::Template::TimeTicks 
		initTime, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new DateTime object.
		 *
		 * \param initTime Broken down calendar time.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::DateTime* create(struct tm initTime, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new DateTime object.
		 *
		 * \param initTime Timestamp.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::DateTime* create(const std::string& initTime, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new DateTime object.
		 *
		 * \param initYear year.
		 * \param initMonth month (1...12).
		 * \param initDay day of month (1...31).
		 * \param initHour hour (0...23).
		 * \param initMinute minute (0...59).
		 * \param initSecond second (0...59).
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::DateTime* create(Ionflux::Template::Year 
		initYear, int initMonth, int initDay, int initHour, int initMinute, int 
		initSecond, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get number of UTC seconds since 0001-01-01 00:00:00.
		 *
		 * \return Current value of number of UTC seconds since 0001-01-01 
		 * 00:00:00.
		 */
		virtual Ionflux::Template::TimeTicks getTicks() const;
		
		/** Get time zone.
		 *
		 * \return Current value of time zone.
		 */
		virtual Ionflux::Template::TimeZone* getTimeZone() const;
		
		/** Set time zone.
		 *
		 * Set new value of time zone.
		 *
		 * \param newTimeZone New value of time zone.
		 */
		virtual void setTimeZone(Ionflux::Template::TimeZone* newTimeZone);
		
		/** Get broken down time: year.
		 *
		 * \return Current value of broken down time: year.
		 */
		virtual Ionflux::Template::Year getYear() const;
		
		/** Get broken down time: month.
		 *
		 * \return Current value of broken down time: month.
		 */
		virtual int getMonth() const;
		
		/** Get broken down time: Day of month (1...31).
		 *
		 * \return Current value of broken down time: Day of month (1...31).
		 */
		virtual int getDay() const;
		
		/** Get broken down time: Hour (0...23).
		 *
		 * \return Current value of broken down time: Hour (0...23).
		 */
		virtual int getHour() const;
		
		/** Get broken down time: Minute (0...59).
		 *
		 * \return Current value of broken down time: Minute (0...59).
		 */
		virtual int getMinute() const;
		
		/** Get broken down time: Second (0...59).
		 *
		 * \return Current value of broken down time: Second (0...59).
		 */
		virtual int getSecond() const;
		
		/** Get broken down time: Day of week (0...6, where 0 = Sunday).
		 *
		 * \return Current value of broken down time: Day of week (0...6, where 0
		 * = Sunday).
		 */
		virtual int getWeekDay() const;
		
		/** Get broken down time: Day of year (1...366).
		 *
		 * \return Current value of broken down time: Day of year (1...366).
		 */
		virtual int getYearDay() const;
};

}

}

/** \file DateTime.hpp
 * \brief Date and time (header).
 */
#endif
