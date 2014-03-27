/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TimeZone.cpp                    Time zone (implementation).
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

#include "iftemplate/TimeZone.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

TimeZoneClassInfo::TimeZoneClassInfo()
{
	name = "TimeZone";
	desc = "Time zone";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TimeZoneClassInfo::~TimeZoneClassInfo()
{
}

// public member constants
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_DST_EUROPE_WESTERN = {
	Ionflux::Template::DSTSwitchingRule::DSR_TYPE_TO_DST, 
        3, 0, 5, 1, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EUROPE_WESTERN = {
	Ionflux::Template::DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 
	    10, 0, 5, 2, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_DST_EUROPE_CENTRAL = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 
	    3, 0, 5, 2, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EUROPE_CENTRAL = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 
	    10, 0, 5, 3, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_DST_EUROPE_EASTERN = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 
	    3, 0, 5, 3, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EUROPE_EASTERN = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 
	    10, 0, 5, 4, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_DST_USA = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 
	    3, 0, 2, 2, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_NORMAL_USA = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 
	    11, 0, 1, 2, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_DST_EGYPT = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 
	    4, 5, 5, 0, 0, 0 };
const Ionflux::Template::DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EGYPT = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 
	    10, 5, 1, 0, 0, 0 };

// run-time type information instance constants
const TimeZoneClassInfo TimeZone::timeZoneClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TimeZone::CLASS_INFO = &TimeZone::timeZoneClassInfo;

TimeZone::TimeZone()
: useDST(false), offset(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(const Ionflux::Template::TimeZone& other)
: useDST(false), offset(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TimeZone::TimeZone(int initOffset)
: useDST(false), offset(initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(int initOffset, const 
Ionflux::Template::DSTSwitchingRule& initToDST, const 
Ionflux::Template::DSTSwitchingRule& initToNormal)
: useDST(true), toDST(initToDST), toNormal(initToNormal), 
offset(initOffset)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(int initOffset, const std::string& initNameNormal, const
std::string& initNameDST, const std::string& initShortNameNormal, const 
std::string& initShortNameDST, const std::string& initAliases)
: useDST(true), offset(initOffset), nameNormal(initNameNormal), 
nameDST(initNameDST), shortNameNormal(initShortNameNormal), 
shortNameDST(initShortNameDST), aliases(initAliases)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(int initOffset, const 
Ionflux::Template::DSTSwitchingRule& initToDST, const 
Ionflux::Template::DSTSwitchingRule& initToNormal, const std::string& 
initNameNormal, const std::string& initNameDST, const std::string& 
initShortNameNormal, const std::string& initShortNameDST, const 
std::string& initAliases)
: useDST(true), toDST(initToDST), toNormal(initToNormal), 
offset(initOffset), nameNormal(initNameNormal), nameDST(initNameDST), 
shortNameNormal(initShortNameNormal), shortNameDST(initShortNameDST), 
aliases(initAliases)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TimeZone::~TimeZone()
{
	// TODO: Nothing ATM. ;-)
}

void TimeZone::setDSTRules(const Ionflux::Template::DSTSwitchingRule& 
newToDST, const Ionflux::Template::DSTSwitchingRule& newToNormal)
{
	toDST = newToDST;
	toNormal = newToNormal;
	useDST = true;
}

bool TimeZone::isDST(const Ionflux::Template::DateTime& utcDT) const
{
	if (useDST)
	{
	    DateTime toDstDT = getSwitchDT(utcDT.getYear(), toDST);
	    DateTime toNormalDT = getSwitchDT(utcDT.getYear(), toNormal);
	    if ((utcDT >= toDstDT) && (utcDT < toNormalDT))
	        return true;
	}
	return false;
}

bool TimeZone::localIsDST(const Ionflux::Template::DateTime& localDT) const
{
	DateTime toDstDT = getSwitchDT(localDT.getYear(), toDST);
	DateTime toNormalDT = getSwitchDT(localDT.getYear(), toNormal);
	// Calculate the UTC datetimes for both possible cases.
	DateTime utcNormal = localDT - static_cast<TimeTicks>(offset * 60);
	DateTime utcDST = localDT - static_cast<TimeTicks>((offset + 1) * 60);
	/* The idea goes as follows: If utcDST is greater than or equal to 
	   toDstDT, utcNormal will be greater as well. Likewise, if utcNormal is 
	   less than toNormalDT, utcDST will be less as well. So, if the condition
	
   evaluates to 'true', we can safely assume that the local datetime 
	   represents DST. (However, in the case of the one local hour that occurs
	
   as normal time as well as as DST, the second subcondition will always 
	   evaluate to 'false', thus normal time is preferred over DST in that 
	   case.) */
	if ((utcDST >= toDstDT) && (utcNormal < toNormalDT))
	    return true;
	return false;
}

int TimeZone::getCurrentOffset(const Ionflux::Template::DateTime& utcDT) 
const
{
	int currentOffset = offset;
	if (useDST)
	{
	    DateTime toDstDT = getSwitchDT(utcDT.getYear(), toDST);
	    DateTime toNormalDT = getSwitchDT(utcDT.getYear(), toNormal);
	    /* <---- DEBUG ----- //
	    std::cerr << "[TimeZone::getCurrentOffset] DEBUG: " 
	        << "toDstDT = " << toDstDT.getTimestamp() << ", "
	        << "toNormalDT = " << toNormalDT.getTimestamp() << ", "
	        << "utcDT = " << utcDT.getTimestamp()
	        << std::endl;
	    // ----- DEBUG ----> */
	    if ((utcDT >= toDstDT) && (utcDT < toNormalDT))
	        currentOffset += 60;
	}
	return currentOffset;
}

const Ionflux::Template::DSTSwitchingRule* TimeZone::getDSTRule(bool 
ruleFlag) const
{
	if (useDST)
	{
	    if (ruleFlag)
	        return &toDST;
	    else
	        return &toNormal;
	}
	return 0;
}

Ionflux::Template::DateTime TimeZone::getSwitchDT(Ionflux::Template::Year 
year, const Ionflux::Template::DSTSwitchingRule& rule) const
{
	DateTime result(DateTime::getNth(year, rule.month, rule.weekDay, 
	    rule.week));
	int currentOffset = offset;
	if (rule.type == DSTSwitchingRule::DSR_TYPE_TO_NORMAL)
	    currentOffset += 60;
	result += ((rule.hour * 60 + rule.minute - currentOffset) * 60 
	    + rule.second);
	return result;
}

bool TimeZone::hasAlias(const std::string& checkAlias) const
{
	string tmpAliases(":");
	string tmpCheckAlias(":");
	tmpAliases.append(aliases + ":");
	tmpCheckAlias.append(checkAlias + ":");
	if (tmpAliases.find(tmpCheckAlias) != string::npos)
	    return true;
	return false;
}

void TimeZone::enableDST(bool enableFlag)
{
	useDST = enableFlag;
}

void TimeZone::setOffset(int newOffset)
{
	offset = newOffset;
}

int TimeZone::getOffset() const
{
    return offset;
}

void TimeZone::setNameNormal(const std::string& newNameNormal)
{
	nameNormal = newNameNormal;
}

std::string TimeZone::getNameNormal() const
{
    return nameNormal;
}

void TimeZone::setNameDST(const std::string& newNameDST)
{
	nameDST = newNameDST;
}

std::string TimeZone::getNameDST() const
{
    return nameDST;
}

void TimeZone::setShortNameNormal(const std::string& newShortNameNormal)
{
	shortNameNormal = newShortNameNormal;
}

std::string TimeZone::getShortNameNormal() const
{
    return shortNameNormal;
}

void TimeZone::setShortNameDST(const std::string& newShortNameDST)
{
	shortNameDST = newShortNameDST;
}

std::string TimeZone::getShortNameDST() const
{
    return shortNameDST;
}

void TimeZone::setAliases(const std::string& newAliases)
{
	aliases = newAliases;
}

std::string TimeZone::getAliases() const
{
    return aliases;
}

Ionflux::Template::TimeZone& TimeZone::operator=(const 
Ionflux::Template::TimeZone& other)
{
    useDST = other.useDST;
    toDST = other.toDST;
    toNormal = other.toNormal;
    offset = other.offset;
    nameNormal = other.nameNormal;
    nameDST = other.nameDST;
    shortNameNormal = other.shortNameNormal;
    shortNameDST = other.shortNameDST;
    aliases = other.aliases;
	return *this;
}

Ionflux::Template::TimeZone* TimeZone::copy() const
{
    TimeZone* newTimeZone = create();
    *newTimeZone = *this;
    return newTimeZone;
}

Ionflux::Template::TimeZone* 
TimeZone::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TimeZone*>(other);
}

Ionflux::Template::TimeZone* 
TimeZone::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TimeZone* newObject = new TimeZone();
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::TimeZone* TimeZone::create(int initOffset, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    TimeZone* newObject = new TimeZone(initOffset);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::TimeZone* TimeZone::create(int initOffset, const 
Ionflux::Template::DSTSwitchingRule& initToDST, const 
Ionflux::Template::DSTSwitchingRule& initToNormal, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    TimeZone* newObject = new TimeZone(initOffset, initToDST, 
    initToNormal);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::TimeZone* TimeZone::create(int initOffset, const 
std::string& initNameNormal, const std::string& initNameDST, const 
std::string& initShortNameNormal, const std::string& initShortNameDST, 
const std::string& initAliases, Ionflux::ObjectBase::IFObject* 
parentObject)
{
    TimeZone* newObject = new TimeZone(initOffset, initNameNormal, 
    initNameDST, initShortNameNormal, initShortNameDST, initAliases);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::TimeZone* TimeZone::create(int initOffset, const 
Ionflux::Template::DSTSwitchingRule& initToDST, const 
Ionflux::Template::DSTSwitchingRule& initToNormal, const std::string& 
initNameNormal, const std::string& initNameDST, const std::string& 
initShortNameNormal, const std::string& initShortNameDST, const 
std::string& initAliases, Ionflux::ObjectBase::IFObject* parentObject)
{
    TimeZone* newObject = new TimeZone(initOffset, initToDST, initToNormal,
    initNameNormal, initNameDST, initShortNameNormal, initShortNameDST, 
    initAliases);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file TimeZone.cpp
 * \brief Time zone implementation.
 */
