/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TimeZone.cpp                    Time zone.
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

#include "ionflux/TimeZone.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int DSTSwitchingRule::DSR_TYPE_TO_DST = 0;
const int DSTSwitchingRule::DSR_TYPE_TO_NORMAL = 1;

const DSTSwitchingRule TimeZone::DSR_TO_DST_EUROPE_WESTERN = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 3, 0, 5, 1, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EUROPE_WESTERN = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 10, 0, 5, 2, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_DST_EUROPE_CENTRAL = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 3, 0, 5, 2, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EUROPE_CENTRAL = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 10, 0, 5, 3, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_DST_EUROPE_EASTERN = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 3, 0, 5, 3, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EUROPE_EASTERN = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 10, 0, 5, 4, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_DST_USA = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 4, 0, 1, 2, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_NORMAL_USA = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 10, 0, 5, 2, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_DST_EGYPT = {
	DSTSwitchingRule::DSR_TYPE_TO_DST, 4, 5, 5, 0, 0, 0};
const DSTSwitchingRule TimeZone::DSR_TO_NORMAL_EGYPT = {
	DSTSwitchingRule::DSR_TYPE_TO_NORMAL, 10, 5, 1, 0, 0, 0};

TimeZone::TimeZone()
: offset(0), useDST(false), nameNormal(""), nameDST(""), shortNameNormal(""), 
  shortNameDST(""), aliases("")
{
	// TODO: Nothing ATM. ;-)
}

TimeZone::~TimeZone()
{
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(int initOffset)
: offset(initOffset), useDST(false), nameNormal(""), nameDST(""), 
  shortNameNormal(""), shortNameDST(""), aliases("")
{
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(int initOffset, const DSTSwitchingRule &initToDST, 
	const DSTSwitchingRule &initToNormal)
: offset(initOffset), useDST(true), toDST(initToDST), toNormal(initToNormal),
  nameNormal(""), nameDST(""), shortNameNormal(""), shortNameDST(""), 
  aliases("")
{
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(int initOffset, 
	const std::string &initNameNormal, 
	const std::string &initNameDST,
	const std::string &initShortNameNormal, 
	const std::string &initShortNameDST,
	const std::string &initAliases)
: offset(initOffset), useDST(false), nameNormal(initNameNormal), 
  nameDST(initNameDST), shortNameNormal(initShortNameNormal), 
  shortNameDST(initShortNameDST), aliases(initAliases)
{
	// TODO: Nothing ATM. ;-)
}

TimeZone::TimeZone(int initOffset, 
	const DSTSwitchingRule &initToDST, 
	const DSTSwitchingRule &initToNormal, 
	const std::string &initNameNormal, 
	const std::string &initNameDST,
	const std::string &initShortNameNormal, 
	const std::string &initShortNameDST,
	const std::string &initAliases)
: offset(initOffset), useDST(true), toDST(initToDST), toNormal(initToNormal),
  nameNormal(initNameNormal), nameDST(initNameDST), 
  shortNameNormal(initShortNameNormal), shortNameDST(initShortNameDST), 
  aliases(initAliases)
{
	// TODO: Nothing ATM. ;-)
}

DateTime TimeZone::getSwitchDT(Year year, const DSTSwitchingRule &rule) const
{
	DateTime result = DateTime::getNth(year, rule.month, rule.weekDay, 
		rule.week);
	int currentOffset = offset;
	if (rule.type == DSTSwitchingRule::DSR_TYPE_TO_NORMAL)
		currentOffset += 60;
	result += ((rule.hour * 60 + rule.minute - currentOffset) * 60 
		+ rule.second);
	return result;
}

void TimeZone::setOffset(int newOffset)
{
	offset = newOffset;
}

void TimeZone::setNameNormal(const std::string &newNameNormal)
{
	nameNormal = newNameNormal;
}

void TimeZone::setNameDST(const std::string &newNameDST)
{
	nameDST = newNameDST;
}

void TimeZone::setShortNameNormal(const std::string &newNameNormal)
{
	nameNormal = newNameNormal;
}

void TimeZone::setShortNameDST(const std::string &newNameDST)
{
	nameDST = newNameDST;
}

void TimeZone::setAliases(const std::string &newAliases)
{
	aliases = newAliases;
}

void TimeZone::setDSTRules(const DSTSwitchingRule &newToDST, 
	const DSTSwitchingRule &newToNormal)
{
	toDST = newToDST;
	toNormal = newToNormal;
	useDST = true;
}

bool TimeZone::isDST(const DateTime &utcDT) const
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

bool TimeZone::localIsDST(const DateTime &localDT) const
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

int TimeZone::getCurrentOffset(const DateTime &utcDT) const
{
	int currentOffset = offset;
	if (useDST)
	{
		DateTime toDstDT = getSwitchDT(utcDT.getYear(), toDST);
		DateTime toNormalDT = getSwitchDT(utcDT.getYear(), toNormal);
		if ((utcDT >= toDstDT) && (utcDT < toNormalDT))
			currentOffset += 60;
	}
	return currentOffset;
}

const DSTSwitchingRule *TimeZone::getDSTRule(bool ruleFlag) const
{
	if (!useDST)
		return 0;
	if (ruleFlag)
		return &toDST;
	else
		return &toNormal;
}

int TimeZone::getOffset() const
{
	return offset;
}

std::string TimeZone::getNameNormal() const
{
	return nameNormal;
}

std::string TimeZone::getNameDST() const
{
	return nameDST;
}

std::string TimeZone::getShortNameNormal() const
{
	return shortNameNormal;
}

std::string TimeZone::getShortNameDST() const
{
	return shortNameDST;
}

std::string TimeZone::getAliases() const
{
	return aliases;
}

bool TimeZone::hasAlias(const std::string &checkAlias) const
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

}

}

/** \file TimeZone.cpp
 * \brief Time zone implementation.
 */
