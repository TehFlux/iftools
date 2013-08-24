#ifndef IONFLUX_TEMPLATE_TIMEZONE
#define IONFLUX_TEMPLATE_TIMEZONE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TimeZone.hpp                    Time zone (header).
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
#include "iftemplate/DateTime.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class TimeZone.
class TimeZoneClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TimeZoneClassInfo();
		/// Destructor.
		virtual ~TimeZoneClassInfo();
};

/** Time zone.
 * \ingroup iftemplate
 *
 * Provides information required for the time zone transformation of 
 * datetimes, such as UTC offset and DST switching rules.
 */
class TimeZone
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// DST flag (true if DST rules are defined).
		bool useDST;
		/// Rule for switching to DST.
		Ionflux::Template::DSTSwitchingRule toDST;
		/// Rule for switching to normal time.
		Ionflux::Template::DSTSwitchingRule toNormal;
		/// UTC offset (minutes).
		int offset;
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
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EUROPE_WESTERN;
		/// DST switching rule: Europe/Western (to normal).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EUROPE_WESTERN;
		/// DST switching rule: Europe/central (to DST).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EUROPE_CENTRAL;
		/// DST switching rule: Europe/central (to normal).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EUROPE_CENTRAL;
		/// DST switching rule: Europe/eastern (to DST).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EUROPE_EASTERN;
		/// DST switching rule: Europe/eastern (to normal).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EUROPE_EASTERN;
		/// DST switching rule: USA (to DST).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_USA;
		/// DST switching rule: USA (to normal).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_USA;
		/// DST switching rule: Egypt (to DST).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EGYPT;
		/// DST switching rule: Egypt (to normal).
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EGYPT;
		/// Class information instance.
		static const TimeZoneClassInfo timeZoneClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 */
		TimeZone();
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param other Other object.
		 */
		TimeZone(const Ionflux::Template::TimeZone& other);
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset offset.
		 */
		TimeZone(int initOffset);
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset offset.
		 * \param initToDST switching rule (to DST).
		 * \param initToNormal switching rule (to normal time).
		 */
		TimeZone(int initOffset, const Ionflux::Template::DSTSwitchingRule& 
		initToDST, const Ionflux::Template::DSTSwitchingRule& initToNormal);
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset offset.
		 * \param initNameNormal time zone name (normal time).
		 * \param initNameDST time zone name (DST).
		 * \param initShortNameNormal time zone short name (normal time).
		 * \param initShortNameDST time zone short name (DST).
		 * \param initAliases time zone alias names.
		 */
		TimeZone(int initOffset, const std::string& initNameNormal, const 
		std::string& initNameDST, const std::string& initShortNameNormal, const 
		std::string& initShortNameDST, const std::string& initAliases);
		
		/** Constructor.
		 *
		 * Construct new TimeZone object.
		 *
		 * \param initOffset offset.
		 * \param initToDST switching rule (to DST).
		 * \param initToNormal switching rule (to normal time).
		 * \param initNameNormal time zone name (normal time).
		 * \param initNameDST time zone name (DST).
		 * \param initShortNameNormal time zone short name (normal time).
		 * \param initShortNameDST time zone short name (DST).
		 * \param initAliases time zone alias names.
		 */
		TimeZone(int initOffset, const Ionflux::Template::DSTSwitchingRule& 
		initToDST, const Ionflux::Template::DSTSwitchingRule& initToNormal, const
		std::string& initNameNormal, const std::string& initNameDST, const 
		std::string& initShortNameNormal, const std::string& initShortNameDST, 
		const std::string& initAliases);
		
		/** Destructor.
		 *
		 * Destruct TimeZone object.
		 */
		virtual ~TimeZone();
		
		/** Set DST switching rules.
		 *
		 * Sets the daylight saving time switching rules.
		 *
		 * \param newToDST Rule for switching to DST.
		 * \param newToNormal Rule for switching to normal time.
		 */
		virtual void setDSTRules(const Ionflux::Template::DSTSwitchingRule& 
		newToDST, const Ionflux::Template::DSTSwitchingRule& newToNormal);
		
		/** Get current DST state (UTC).
		 *
		 * Get current DST state of an UTC datetime in this time zone.
		 * 
		 * \note This function is meant for time zone conversion only. If you 
		 * require this function for a local time instead of UTC, you should 
		 * use the function DateTime::isDST() instead.
		 *
		 * \param utcDT datetime object.
		 *
		 * \return \c true if the specified UTC datetime represents daylight 
		 * saving time in this time zone, \c false otherwise.
		 */
		virtual bool isDST(const Ionflux::Template::DateTime& utcDT) const;
		
		/** Get current DST state (local time).
		 *
		 * Get current DST state of a local datetime in this time zone.
		 * 
		 * \note DST state for local time is ambiguous during one hour of the 
		 * year, i.e. when switching from DST to normal time occurs. This 
		 * function will prefer normal time to DST in this case. Likewise, 
		 * there is one hour during the year that is skipped, i.e. when 
		 * switching from normal time to DST occurs. Datetimes in the range of
		 * this hour are not valid. If an invalid datetime is specified, the 
		 * behavior is undefined. Also note that the timezone of \c localDT, 
		 * if set at all, will be ignored. Whatever time is stored in \c 
		 * localDT will be treated as local time in the time zone of the 
		 * TimeZone object.
		 *
		 * \param localDT datetime object.
		 *
		 * \return \c true if the specified local datetime represents daylight 
		 * saving time in this time zone, \c false otherwise.
		 */
		virtual bool localIsDST(const Ionflux::Template::DateTime& localDT) 
		const;
		
		/** Get current UTC offset.
		 *
		 * Get the UTC offset, in minutes, corrected for DST, for the local 
		 * time corresponding to the specified UTC DateTime.
		 * 
		 * \note This function is meant for time zone conversion only. If you 
		 * require this function for a local time instead of UTC, you should 
		 * use the function DateTime::getUTCOffset() instead.
		 *
		 * \param utcDT datetime object.
		 *
		 * \return The current UTC offset, in minutes.
		 */
		virtual int getCurrentOffset(const Ionflux::Template::DateTime& utcDT) 
		const;
		
		/** Get DST rule.
		 *
		 * Return one of the DST rules for this time zone.
		 *
		 * \param ruleFlag Which rule to return.
		 *
		 * \return The rule for switching to DST if \c true is passed, the rule 
		 * for switching to normal time if \c false is passed and 0 if no rules 
		 * are defined.
		 */
		virtual const Ionflux::Template::DSTSwitchingRule* getDSTRule(bool 
		ruleFlag) const;
		
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
		virtual Ionflux::Template::DateTime getSwitchDT(Ionflux::Template::Year 
		year, const Ionflux::Template::DSTSwitchingRule& rule) const;
		
		/** Check alias name.
		 *
		 * Checks whether this time zone has a specified alias name.
		 *
		 * \param checkAlias alias name.
		 *
		 * \return \c true if this time zone has the specified alias name, \c 
		 * false otherwise.
		 */
		virtual bool hasAlias(const std::string& checkAlias) const;
		
		/** Enable or disable DST.
		 *
		 * Sets whether to apply daylight saving time switching rules. Passing
		 * \c true enables DST (if rules are defined), passing \c false 
		 * disables DST.
		 *
		 * \param enableFlag New DST state.
		 */
		virtual void enableDST(bool enableFlag);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::TimeZone& operator=(const 
		Ionflux::Template::TimeZone& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::TimeZone* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::TimeZone* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::Template::TimeZone* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new TimeZone object.
		 *
		 * \param initOffset offset.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::TimeZone* create(int initOffset, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new TimeZone object.
		 *
		 * \param initOffset offset.
		 * \param initToDST switching rule (to DST).
		 * \param initToNormal switching rule (to normal time).
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::TimeZone* create(int initOffset, const 
		Ionflux::Template::DSTSwitchingRule& initToDST, const 
		Ionflux::Template::DSTSwitchingRule& initToNormal, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new TimeZone object.
		 *
		 * \param initOffset offset.
		 * \param initNameNormal time zone name (normal time).
		 * \param initNameDST time zone name (DST).
		 * \param initShortNameNormal time zone short name (normal time).
		 * \param initShortNameDST time zone short name (DST).
		 * \param initAliases time zone alias names.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::TimeZone* create(int initOffset, const 
		std::string& initNameNormal, const std::string& initNameDST, const 
		std::string& initShortNameNormal, const std::string& initShortNameDST, 
		const std::string& initAliases, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new TimeZone object.
		 *
		 * \param initOffset offset.
		 * \param initToDST switching rule (to DST).
		 * \param initToNormal switching rule (to normal time).
		 * \param initNameNormal time zone name (normal time).
		 * \param initNameDST time zone name (DST).
		 * \param initShortNameNormal time zone short name (normal time).
		 * \param initShortNameDST time zone short name (DST).
		 * \param initAliases time zone alias names.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::TimeZone* create(int initOffset, const 
		Ionflux::Template::DSTSwitchingRule& initToDST, const 
		Ionflux::Template::DSTSwitchingRule& initToNormal, const std::string& 
		initNameNormal, const std::string& initNameDST, const std::string& 
		initShortNameNormal, const std::string& initShortNameDST, const 
		std::string& initAliases, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
		
		/** Get uTC offset (minutes).
		 *
		 * \return Current value of uTC offset (minutes).
		 */
		virtual int getOffset() const;
		
		/** Set uTC offset (minutes).
		 *
		 * Set new value of uTC offset (minutes).
		 *
		 * \param newOffset New value of uTC offset (minutes).
		 */
		virtual void setOffset(int newOffset);
		
		/** Get name of the time zone (normal time).
		 *
		 * \return Current value of name of the time zone (normal time).
		 */
		virtual std::string getNameNormal() const;
		
		/** Set name of the time zone (normal time).
		 *
		 * Set new value of name of the time zone (normal time).
		 *
		 * \param newNameNormal New value of name of the time zone (normal time).
		 */
		virtual void setNameNormal(const std::string& newNameNormal);
		
		/** Get name of the time zone (DST).
		 *
		 * \return Current value of name of the time zone (DST).
		 */
		virtual std::string getNameDST() const;
		
		/** Set name of the time zone (DST).
		 *
		 * Set new value of name of the time zone (DST).
		 *
		 * \param newNameDST New value of name of the time zone (DST).
		 */
		virtual void setNameDST(const std::string& newNameDST);
		
		/** Get short name of the time zone (normal time).
		 *
		 * \return Current value of short name of the time zone (normal time).
		 */
		virtual std::string getShortNameNormal() const;
		
		/** Set short name of the time zone (normal time).
		 *
		 * Set new value of short name of the time zone (normal time).
		 *
		 * \param newShortNameNormal New value of short name of the time zone 
		 * (normal time).
		 */
		virtual void setShortNameNormal(const std::string& newShortNameNormal);
		
		/** Get short name of the time zone (DST).
		 *
		 * \return Current value of short name of the time zone (DST).
		 */
		virtual std::string getShortNameDST() const;
		
		/** Set short name of the time zone (DST).
		 *
		 * Set new value of short name of the time zone (DST).
		 *
		 * \param newShortNameDST New value of short name of the time zone (DST).
		 */
		virtual void setShortNameDST(const std::string& newShortNameDST);
		
		/** Get alias names for the time zone.
		 *
		 * \return Current value of alias names for the time zone.
		 */
		virtual std::string getAliases() const;
		
		/** Set alias names for the time zone.
		 *
		 * Set new value of alias names for the time zone.
		 *
		 * \param newAliases New value of alias names for the time zone.
		 */
		virtual void setAliases(const std::string& newAliases);
};

}

}

/** \file TimeZone.hpp
 * \brief Time zone (header).
 */
#endif
