/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DateTime.i                      Date and time (interface).
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
%{
#include "iftemplate/DateTime.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TimeZone;

class DateTimeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DateTimeClassInfo();
        virtual ~DateTimeClassInfo();
};

class DateTime
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const std::string TIMESTAMP_DATE_SEP;
		static const std::string TIMESTAMP_TIME_SEP;
		static const std::string TIMESTAMP_DATETIME_SEP;
		static const int NUM_DAYS[];
		static const int LEAP_MONTH;
		static const Ionflux::Template::TimeTicks POSIX_EPOCH;
		static const Ionflux::Template::TimeTicks TICKS_400Y;
		static const Ionflux::Template::TimeTicks TICKS_100Y;
		static const Ionflux::Template::TimeTicks TICKS_4Y;
		static const Ionflux::Template::TimeTicks TICKS_3Y;
		static const Ionflux::Template::TimeTicks TICKS_1Y;
		static const Ionflux::Template::TimeTicks TICKS_1D;
		static const Ionflux::Template::TimeTicks REF_SUNDAY;
		static const char* WEEKDAY_NAME[7];
		static const char* WEEKDAY_NAME_SHORT[7];
		static const char* MONTH_NAME[12];
		static const char* MONTH_NAME_SHORT[12];
		static const Ionflux::Template::TimeZone TZ_UTC;
		static const Ionflux::Template::TimeZone TZ_UTC_P0100;
		static const Ionflux::Template::TimeZone TZ_UTC_P0200;
		static const Ionflux::Template::TimeZone TZ_UTC_P0300;
		static const Ionflux::Template::TimeZone TZ_UTC_P0330;
		static const Ionflux::Template::TimeZone TZ_UTC_P0400;
		static const Ionflux::Template::TimeZone TZ_UTC_P0430;
		static const Ionflux::Template::TimeZone TZ_UTC_P0500;
		static const Ionflux::Template::TimeZone TZ_UTC_P0530;
		static const Ionflux::Template::TimeZone TZ_UTC_P0545;
		static const Ionflux::Template::TimeZone TZ_UTC_P0600;
		static const Ionflux::Template::TimeZone TZ_UTC_P0630;
		static const Ionflux::Template::TimeZone TZ_UTC_P0700;
		static const Ionflux::Template::TimeZone TZ_UTC_P0800;
		static const Ionflux::Template::TimeZone TZ_UTC_P0900;
		static const Ionflux::Template::TimeZone TZ_UTC_P0930;
		static const Ionflux::Template::TimeZone TZ_UTC_P1000;
		static const Ionflux::Template::TimeZone TZ_UTC_P1100;
		static const Ionflux::Template::TimeZone TZ_UTC_P1200;
		static const Ionflux::Template::TimeZone TZ_UTC_M0100;
		static const Ionflux::Template::TimeZone TZ_UTC_M0200;
		static const Ionflux::Template::TimeZone TZ_UTC_M0300;
		static const Ionflux::Template::TimeZone TZ_UTC_M0400;
		static const Ionflux::Template::TimeZone TZ_UTC_M0500;
		static const Ionflux::Template::TimeZone TZ_UTC_M0600;
		static const Ionflux::Template::TimeZone TZ_UTC_M0700;
		static const Ionflux::Template::TimeZone TZ_UTC_M0800;
		static const Ionflux::Template::TimeZone TZ_UTC_M0900;
		static const Ionflux::Template::TimeZone TZ_UTC_M1000;
		static const Ionflux::Template::TimeZone TZ_UTC_M1100;
		static const Ionflux::Template::TimeZone TZ_UTC_M1200;
		static const Ionflux::Template::TimeZone TZ_GMT;
		static const Ionflux::Template::TimeZone TZ_EUROPE_WESTERN;
		static const Ionflux::Template::TimeZone TZ_EUROPE_CENTRAL;
		static const Ionflux::Template::TimeZone TZ_EUROPE_EASTERN;
		static const Ionflux::Template::TimeZone TZ_UK;
		static const Ionflux::Template::TimeZone TZ_USA_EASTERN;
		static const Ionflux::Template::TimeZone TZ_USA_CENTRAL;
		static const Ionflux::Template::TimeZone TZ_USA_MOUNTAIN;
		static const Ionflux::Template::TimeZone TZ_USA_PACIFIC;
		static const Ionflux::Template::TimeZone TZ_USA_ALASKA;
		static const Ionflux::Template::TimeZone TZ_RUSSIA_WESTERN;
		static const Ionflux::Template::TimeZone TZ_EGYPT;
        
        DateTime();
		DateTime(const Ionflux::Template::DateTime& other);
        DateTime(Ionflux::Template::TimeTicks initTime);
        DateTime(struct tm initTime);
        DateTime(const std::string& initTime);
        DateTime(Ionflux::Template::Year initYear, int initMonth, int 
        initDay, int initHour, int initMinute, int initSecond);
        virtual ~DateTime();
        virtual void setTimePosix(time_t newTime);
        virtual void setTimeTicks(Ionflux::Template::TimeTicks newTime);
        virtual void setTime(struct tm newTime);
        virtual void setTime(const std::string& newTime);
        virtual void setTime(const Ionflux::Template::DateTime& newTime);
        virtual void setTime(Ionflux::Template::Year newYear, int newMonth,
        int newDay, int newHour, int newMinute, int newSecond);
        virtual void setLocalTime(const Ionflux::Template::DateTime& 
        newTime, bool newDSTState);
        virtual void setLocalTime(const std::string& newTime, bool 
        newDSTState);
        virtual void setLocalTime(Ionflux::Template::Year newYear, int 
        newMonth, int newDay, int newHour, int newMinute, int newSecond, 
        bool newDSTState);
        virtual void setLocalTime(const Ionflux::Template::DateTime& 
        newTime);
        virtual void setLocalTime(const std::string& newTime);
        virtual void setLocalTime(Ionflux::Template::Year newYear, int 
        newMonth, int newDay, int newHour, int newMinute, int newSecond);
        virtual void setHMS(int newHour, int newMinute, int newSecond);
        virtual void setHMS(const std::string& newTime);
        virtual void setHMS(const Ionflux::Template::DateTime& sourceTime);
        virtual void setLocalHMS(int newHour, int newMinute, int newSecond,
        bool newDSTState);
        virtual void setLocalHMS(const std::string& newTime, bool 
        newDSTState);
        virtual void setLocalHMS(const Ionflux::Template::DateTime& 
        sourceTime, bool newDSTState);
        virtual void setLocalHMS(int newHour, int newMinute, int 
        newSecond);
        virtual void setLocalHMS(const std::string& newTime);
        virtual void setLocalHMS(const Ionflux::Template::DateTime& 
        sourceTime);
        virtual Ionflux::Template::DateTime& 
        shift(Ionflux::Template::TimeTicks shiftSeconds);
        virtual Ionflux::Template::TimeTicks diff(const 
        Ionflux::Template::DateTime& diffTime);
        virtual void setTimeZone(const std::string& newTimeZone);
        virtual int compareHMS(int otherHour, int otherMinute, int 
        otherSecond);
        virtual int compareHMS(const Ionflux::Template::DateTime& 
        otherTime);
        virtual int compareHMS(const std::string& otherTime);
        virtual int compareDay(const Ionflux::Template::DateTime& 
        otherTime);
        virtual Ionflux::Template::DateTime getUTC();
        virtual time_t getTimePosix() const;
        virtual std::string getTimestamp();
        virtual std::string getHMS();
        virtual std::string getDayOfWeekName() const;
        virtual std::string getDayOfWeekShortName() const;
        virtual std::string getMonthName() const;
        virtual std::string getMonthShortName() const;
        virtual std::string getTimeZoneName() const;
        virtual std::string getTimeZoneAliases() const;
        virtual bool isDST() const;
        virtual int getUTCOffset() const;
        virtual std::string getRFCTimestamp() const;
        virtual Ionflux::Template::DateTime& 
        operator+=(Ionflux::Template::TimeTicks seconds);
        virtual Ionflux::Template::DateTime& 
        operator-=(Ionflux::Template::TimeTicks seconds);
        virtual Ionflux::Template::TimeTicks operator-(const 
        Ionflux::Template::DateTime& diffTime) const;
        virtual bool operator==(const Ionflux::Template::DateTime& 
        compTime) const;
        virtual bool operator!=(const Ionflux::Template::DateTime& 
        compTime) const;
        virtual bool operator>(const Ionflux::Template::DateTime& compTime)
        const;
        virtual bool operator<(const Ionflux::Template::DateTime& compTime)
        const;
        virtual bool operator>=(const Ionflux::Template::DateTime& 
        compTime) const;
        virtual bool operator<=(const Ionflux::Template::DateTime& 
        compTime) const;
        static Ionflux::Template::Year 
        countLeapYears(Ionflux::Template::Year limit);
        static bool isLeapYear(Ionflux::Template::Year checkYear);
        static Ionflux::Template::DateTime getNth(Ionflux::Template::Year 
        targetYear, int targetMonth, int targetWeekDay, int n);
        static bool isTime(const std::string& checkTime);
        static bool isDate(const std::string& checkDate);
        static bool isDatetime(const std::string& checkDatetime);
		virtual Ionflux::Template::DateTime* copy() const;
		static Ionflux::Template::DateTime* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Template::DateTime* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::Template::DateTime* create(Ionflux::Template::TimeTicks 
		initTime, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::DateTime* create(struct tm initTime, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::DateTime* create(const std::string& initTime, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::DateTime* create(Ionflux::Template::Year 
		initYear, int initMonth, int initDay, int initHour, int initMinute, int 
		initSecond, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual Ionflux::Template::TimeTicks getTicks() const;
        virtual void setTimeZone(Ionflux::Template::TimeZone* newTimeZone);
        virtual Ionflux::Template::TimeZone* getTimeZone() const;
        virtual Ionflux::Template::Year getYear() const;
        virtual int getMonth() const;
        virtual int getDay() const;
        virtual int getHour() const;
        virtual int getMinute() const;
        virtual int getSecond() const;
        virtual int getWeekDay() const;
        virtual int getYearDay() const;
};

}

}
