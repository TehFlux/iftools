#ifndef IONFLUX_TOOLS_TIMEZONE
#define IONFLUX_TOOLS_TIMEZONE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TimeZone.hpp                    Time zone.
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
#include "ionflux/DateTime.hpp"

namespace Ionflux
{

namespace Tools
{

class DateTime;

/** UTC seconds since 0001-01-01 00:00:00.
 * \ingroup datetime
 */
typedef int64_t TimeTicks;
/** Year.
 * \ingroup datetime
 */
typedef int64_t Year;

/** Daylight saving time switching rule.
 * \ingroup datetime
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
	static const int DSR_TYPE_TO_DST;
	/// Switching rule type: To normal.
	static const int DSR_TYPE_TO_NORMAL;
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

/** Time zone.
 * \ingroup datetime
 *
 * Provides information required for the time zone transformation of 
 * datetimes, such as UTC offset and DST switching rules.
 */
class TimeZone
{
	protected:
		/// UTC offset (minutes).
		int offset;
		/// DST flag (true if DST rules are defined).
		bool useDST;
		/// Rule for switching to DST.
		DSTSwitchingRule toDST;
		/// Rule for switching to normal time.
		DSTSwitchingRule toNormal;
		/// Name of the time zone (normal time).
		std::string nameNormal;
		/// Name of the time zone (DST).
		std::string nameDST;
		/// Short name of the time zone (normal time).
		std::string shortNameNormal;
		/// Short name of the time zone (DST).
		std::string shortNameDST;
		/// Alias names for the time zone.
		std::string aliases;
		
	public:
		/// DST switching rule: Europe/Western (to DST).
		static const DSTSwitchingRule DSR_TO_DST_EUROPE_WESTERN;
		/// DST switching rule: Europe/Western (to normal).
		static const DSTSwitchingRule DSR_TO_NORMAL_EUROPE_WESTERN;
		/// DST switching rule: Europe/Central (to DST).
		static const DSTSwitchingRule DSR_TO_DST_EUROPE_CENTRAL;
		/// DST switching rule: Europe/Central (to normal).
		static const DSTSwitchingRule DSR_TO_NORMAL_EUROPE_CENTRAL;
		/// DST switching rule: Europe/Eastern (to DST).
		static const DSTSwitchingRule DSR_TO_DST_EUROPE_EASTERN;
		/// DST switching rule: Europe/Eastern (to normal).
		static const DSTSwitchingRule DSR_TO_NORMAL_EUROPE_EASTERN;
		/// DST switching rule: USA (to DST).
		static const DSTSwitchingRule DSR_TO_DST_USA;
		/// DST switching rule: USA (to normal).
		static const DSTSwitchingRule DSR_TO_NORMAL_USA;
		/// DST switching rule: Egypt (to DST).
		static const DSTSwitchingRule DSR_TO_DST_EGYPT;
		/// DST switching rule: Egypt (to normal).
		static const DSTSwitchingRule DSR_TO_NORMAL_EGYPT;
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 */
		TimeZone();
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset UTC offset (minutes).
		 */
		TimeZone(int initOffset);
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset UTC offset (minutes).
		 * \param initNameNormal Time zone name (normal time).
		 * \param initNameDST Time zone name (DST).
		 * \param initShortNameNormal Time zone short name (normal time).
		 * \param initShortNameDST Time zone short name (DST).
		 * \param initAliases Time zone alias names.
		 */
		TimeZone(int initOffset,
			const std::string &initNameNormal, 
			const std::string &initNameDST,
			const std::string &initShortNameNormal, 
			const std::string &initShortNameDST, 
			const std::string &initAliases);
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset UTC offset (minutes).
		 * \param initToDST Rule for switching to DST.
		 * \param initToNormal Rule for switching to normal time.
		 */
		TimeZone(int initOffset, 
			const DSTSwitchingRule &initToDST, 
			const DSTSwitchingRule &initToNormal);
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset UTC offset (minutes).
		 * \param initToDST Rule for switching to DST.
		 * \param initToNormal Rule for switching to normal time.
		 * \param initNameNormal Time zone name (normal time).
		 * \param initNameDST Time zone name (DST).
		 * \param initShortNameNormal Time zone short name (normal time).
		 * \param initShortNameDST Time zone short name (DST).
		 * \param initAliases Time zone alias names.
		 */
		TimeZone(int initOffset, 
			const DSTSwitchingRule &initToDST, 
			const DSTSwitchingRule &initToNormal, 
			const std::string &initNameNormal, 
			const std::string &initNameDST,
			const std::string &initShortNameNormal, 
			const std::string &initShortNameDST, 
			const std::string &initAliases);
		
		/** Destructor.
		 *
		 * Destruct TimeZone object.
		 */
		virtual ~TimeZone();
		
		/** Set UTC offset.
		 *
		 * Sets the UTC offset of the time zone (normal time).
		 *
		 * \param newOffset UTC offset (minutes).
		 */
		virtual void setOffset(int newOffset);
		
		/** Set time zone name (normal time).
		 *
		 * Set a name for this time zone during normal time (e.g. 
		 * "Central European Time").
		 *
		 * \param newNameNormal Time zone name (normal time).
		 */
		virtual void setNameNormal(const std::string &newNameNormal);
		
		/** Set time zone name (DST).
		 *
		 * Set a name for this time zone during DST (e.g. 
		 * "Central European Summer Time").
		 *
		 * \param newNameDST Time zone name (DST).
		 */
		virtual void setNameDST(const std::string &newNameDST);
		
		/** Set time zone name (normal time).
		 *
		 * Set a short name for this time zone during normal time (e.g. 
		 * "CET").
		 *
		 * \param newNameNormal Time zone name (normal time).
		 */
		virtual void setShortNameNormal(const std::string &newNameNormal);
		
		/** Set time zone name (DST).
		 *
		 * Set a name for this time zone during DST (e.g. "CEST").
		 *
		 * \param newNameDST Time zone name (DST).
		 */
		virtual void setShortNameDST(const std::string &newNameDST);
		
		/** Set time zone alias names.
		 *
		 * Set alias names for this time zone. This is a colon (':') separated 
		 * list of names that may be used to refer to this time zone.
		 *
		 * \note It is useful if this is set to a list of names of major 
		 * cities in the time zone (e.g. "Amsterdam:Paris:Berlin:..."), or an 
		 * instructive name specifying the geographical region where the time 
		 * zone applies (e.g. "Central Europe").
		 *
		 * \param newAliases Colon (':') separated list of alias names.
		 */
		virtual void setAliases(const std::string &newAliases);
		
		/** Set DST switching rules.
		 *
		 * Sets the daylight saving time switching rules.
		 *
		 * \param newToDST Rule for switching to DST.
		 * \param newToNormal Rule for switching to normal time.
		 */
		virtual void setDSTRules(const DSTSwitchingRule &newToDST, 
			const DSTSwitchingRule &newToNormal);
		
		/** Get current DST state (UTC).
		 *
		 * Get current DST state of an UTC datetime in the local time zone.
		 *
		 * \note This function is meant for time zone conversion only. If you 
		 * require this function for a local time instead of UTC, you should 
		 * use the function DateTime::isDST() instead.
		 *
		 * \param utcDT DateTime object.
		 *
		 * \return \c true if the specified UTC DateTime represents daylight 
		 * saving time in the local time zone, \c false otherwise.
		 */
		virtual bool isDST(const DateTime &utcDT) const;
		
		/** Get current DST state (local time).
		 *
		 * Get current DST state of a local time.
		 *
		 * \note DST state for local time is ambiguous during one hour of the 
		 * year, i.e. when switching from DST to normal time occurs. This 
		 * function will prefer normal time to DST in this case. Likewise, 
		 * there is one hour during the year that is skipped, i.e. when 
		 * switching from normal time to DST occurs. Datetimes in the range 
		 * of this hour are not valid. If an invalid datetime is specified, 
		 * the behavior is undefined. Also note that the timezone of 
		 * \c localDT, if set at all, will be ignored. Whatever time is 
		 * stored in \c localDT will be treated as local time in the time zone 
		 * of the TimeZone object.
		 *
		 * \param localDT DateTime object.
		 *
		 * \return \c true if the specified DateTime represents daylight 
		 * saving time, \c false otherwise.
		 */
		virtual bool localIsDST(const DateTime &localDT) const;
		
		/** Get current UTC offset.
		 *
		 * Get the UTC offset, in minutes, corrected for DST, for the local 
		 * time corresponding to the specified UTC DateTime.
		 *
		 * \note This function is meant for time zone conversion only. If you 
		 * require this function for a local time instead of UTC, you should 
		 * use the function DateTime::getUTCOffset() instead.
		 *
		 * \param utcDT DateTime object.
		 *
		 * \return The current UTC offset, in minutes.
		 */
		virtual int getCurrentOffset(const DateTime &utcDT) const;
		
		/** Get DST rule.
		 *
		 * Return one of the DST rules for this time zone.\n
		 *
		 * \param ruleFlag Which rule to return.
		 *
		 * \return The rule for switching to DST if \c true is passed, the
		 * rule for switching to normal time if \c false is passed and 0 if 
		 * no rules are defined.
		 */
		virtual const DSTSwitchingRule *getDSTRule(bool ruleFlag) const;
		
		/** Get switch date.
		 *
		 * Creates an exact switch date (UTC) from a DST switching rule for
		 * the specified year.
		 *
		 * \param year The year which to apply the DST switching rule to.
		 * \param rule The DST switching rule to apply.
		 *
		 * \return Datetime where the switching from or to DST occurs.
		 */
		DateTime getSwitchDT(Year year, const DSTSwitchingRule &rule) const;
		
		/** Get UTC offset.
		 *
		 * \return Nominal UTC offset of this time zone, in minutes.
		 */
		virtual int getOffset() const;
		
		/** Get time zone name (normal time).
		 *
		 * \return The name of the time zone when normal time is in effect.
		 */
		virtual std::string getNameNormal() const;
		
		/** Get time zone name (DST).
		 *
		 * \return The name of the time zone when DST is in effect.
		 */
		virtual std::string getNameDST() const;
		
		/** Get time zone name (normal time).
		 *
		 * \return The name of the time zone when normal time is in effect.
		 */
		virtual std::string getShortNameNormal() const;
		
		/** Get time zone name (DST).
		 *
		 * \return The name of the time zone when DST is in effect.
		 */
		virtual std::string getShortNameDST() const;
		
		/** Get time zone alias names.
		 *
		 * \return Colon (':') separated list of alias names for this time 
		 * zone.
		 */
		virtual std::string getAliases() const;
		
		/** Check alias name.
		 *
		 * Checks whether this time zone has a specified alias name.
		 *
		 * \return \c true if this time zone has the specified alias name, 
		 * \c false otherwise.
		 */
		virtual bool hasAlias(const std::string &checkAlias) const;
		
		/** Enable or disable DST.
		 *
		 * Sets whether to apply daylight saving time switching rules. Passing
		 * \c true enables DST (if rules are defined), passing \c false 
		 * disables DST.
		 *
		 * \param enableFlag New DST state.
		 */
		virtual void enableDST(bool enableFlag);
};

}

}

/** \file TimeZone.hpp
 * \brief Time zone header.
 */
#endif
