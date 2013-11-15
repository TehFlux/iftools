/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DateTime.cpp                    Date and time (implementation).
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

#include "iftemplate/DateTime.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "ifobject/utils.hpp"
#include "iftemplate/IFTemplateError.hpp"
#include "iftemplate/TimeZone.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

DateTimeClassInfo::DateTimeClassInfo()
{
	name = "DateTime";
	desc = "Date and time";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

DateTimeClassInfo::~DateTimeClassInfo()
{
}

// public member constants
const std::string DateTime::TIMESTAMP_DATE_SEP = "-";
const std::string DateTime::TIMESTAMP_TIME_SEP = ":";
const std::string DateTime::TIMESTAMP_DATETIME_SEP = " ";
const int DateTime::NUM_DAYS[] = {
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
	0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
const int DateTime::LEAP_MONTH = 2;
const Ionflux::Template::TimeTicks DateTime::POSIX_EPOCH = 62135596800LL;
const Ionflux::Template::TimeTicks DateTime::TICKS_400Y = 12622780800LL;
const Ionflux::Template::TimeTicks DateTime::TICKS_100Y = 3155673600LL;
const Ionflux::Template::TimeTicks DateTime::TICKS_4Y = 126230400LL;
const Ionflux::Template::TimeTicks DateTime::TICKS_3Y = 94608000LL;
const Ionflux::Template::TimeTicks DateTime::TICKS_1Y = 31536000LL;
const Ionflux::Template::TimeTicks DateTime::TICKS_1D = 86400LL;
const Ionflux::Template::TimeTicks DateTime::REF_SUNDAY = 63223891200LL;
const char* DateTime::WEEKDAY_NAME[7] = {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", 
	"Saturday" };
const char* DateTime::WEEKDAY_NAME_SHORT[7] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const char* DateTime::MONTH_NAME[12] = {
	"January", "February", "March", "April", "May", "June", "July", "August",
	"September", "October", "November", "December" };
const char* DateTime::MONTH_NAME_SHORT[12] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", 
	"Nov", "Dec" };
const Ionflux::Template::TimeZone DateTime::TZ_UTC = Ionflux::Template::TimeZone(0, "Coordinated Universal Time", 
    "Coordinated Universal Time", "UTC", "UTC", 
    "UTC:+0000:Rabat:Reykjavik:Ouagadougou:Accra:Lome:Yamoussoukro:Bamako:"
    "Monrovia:Freetown:Conakry:Dakar:Banjul:Bissau:Praia:Laayoune");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0100 = Ionflux::Template::TimeZone(60, "Coordinated Universal Time +0100", 
	"Coordinated Universal Time +0100", "+0100", "+0100", 
	"UTC+0100:+0100:Algiers:Tunis:Tripoli:Kinshasa:Luanda:Windhoek:Yaounde:"
	"Bangui:Brazzaville:Libreville:Malabo:Abuja:N'Djamena:Sao Tome:Niamey:"
	"Porto-Novo");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0200 = Ionflux::Template::TimeZone(120, "Coordinated Universal Time +0200", 
	"Coordinated Universal Time +0200", "+0200", "+0200", 
	"UTC+0200:+0200:Amman:Damascus:Beirut:Jerusalem:Pretoria:Lilongwe:Lusaka:"
	"Harare:Kigali:Bujumbura:Gaborone:Maputo:Mbabane:Maseru:Kampala:Khartoum");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0300 = Ionflux::Template::TimeZone(180, "Coordinated Universal Time +0300", 
	"Coordinated Universal Time +0300", "+0300", "+0300", 
	"UTC+0300:+0300:Baghdad:Riyadh:Sanaa:Kuwait:Manama:Doha:Nairobi:Asmara:"
	"Djibouti:Addis Ababa:Mogadishu:Kampala:Dar es Salaam:Antananarivo:"
	"Moroni");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0330 = Ionflux::Template::TimeZone(210, "Coordinated Universal Time +0330", 
	"Coordinated Universal Time +0330", "+0330", "+0330", 
	"UTC+0330:+0330:Tehran");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0400 = Ionflux::Template::TimeZone(240, "Coordinated Universal Time +0400", 
	"Coordinated Universal Time +0400", "+0400", "+0400", 
	"UTC+0400:+0400:Tbilisi:Yerevan:Baku:Abu Dhabi:Muscat:Victoria:"
	"Port Louis:Saint-Denis");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0430 = Ionflux::Template::TimeZone(270, "Coordinated Universal Time +0430", 
	"Coordinated Universal Time +0430", "+0430", "+0430", 
	"UTC+0430:+0430:Kabul:Kandahar");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0500 = Ionflux::Template::TimeZone(300, "Coordinated Universal Time +0500", 
	"Coordinated Universal Time +0500", "+0500", "+0500", 
	"UTC+0500:+0500:Male:Islamabad:Bishkek:Dushanbo:Ashgabat:Tashkent");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0530 = Ionflux::Template::TimeZone(330, "Coordinated Universal Time +0530", 
	"Coordinated Universal Time +0530", "+0530", "+0530", 
	"UTC+0530:+0530:New Delhi:Mumbai:Bombay:Kolkata:Calcutta");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0545 = Ionflux::Template::TimeZone(345, "Coordinated Universal Time +0545", 
	"Coordinated Universal Time +0545", "+0545", "+0545", 
	"UTC+0545:+0545:Kathmandu");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0600 = Ionflux::Template::TimeZone(360, "Coordinated Universal Time +0600", 
	"Coordinated Universal Time +0600", "+0600", "+0600", 
	"UTC+0600:+0600:Colombo:Dhaka:Thimphu:Astana:Omsk:Novosibirsk");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0630 = Ionflux::Template::TimeZone(390, "Coordinated Universal Time +0630", 
	"Coordinated Universal Time +0630", "+0630", "+0630", 
	"UTC+0630:+0630:Rangoon");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0700 = Ionflux::Template::TimeZone(420, "Coordinated Universal Time +0700", 
	"Coordinated Universal Time +0700", "+0700", "+0700", 
	"UTC+0700:+0700:Jakarta:Singapore:Hanoi:Bangkok:Phnom Penh:Vientiane");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0800 = Ionflux::Template::TimeZone(480, "Coordinated Universal Time +0800", 
	"Coordinated Universal Time +0800", "+0800", "+0800", 
	"UTC+0800:+0800:Beijing:Hong Kong:Macau:Shanghai:Taipei:Perth:Dili:"
	"Bandar Seri Begawan:Manila:Ulaanbaatar");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0900 = Ionflux::Template::TimeZone(540, "Coordinated Universal Time +0900", 
	"Coordinated Universal Time +0900", "+0900", "+0900", 
	"UTC+0900:+0900:Tokyo:Pyongyang:Seoul:Koror");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P0930 = Ionflux::Template::TimeZone(570, "Coordinated Universal Time +0930", 
	"Coordinated Universal Time +0930", "+0930", "+0930", 
	"UTC+0930:+0930:Alice Springs");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P1000 = Ionflux::Template::TimeZone(600, "Coordinated Universal Time +1000", 
	"Coordinated Universal Time +1000", "+1000", "+1000", 
	"UTC+1000:+1000:Hobart:Melbourne:Canberra:Sydney:Brisbane:Caims:"
	"Port Moresby:Vladivostok:Saipan:Hagatna");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P1100 = Ionflux::Template::TimeZone(660, "Coordinated Universal Time +1100", 
	"Coordinated Universal Time +1100", "+1100", "+1100", 
	"UTC+1100:+1100:Honiara:Port-Vila:Noumea:Palikir");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_P1200 = Ionflux::Template::TimeZone(720, "Coordinated Universal Time +1200", 
	"Coordinated Universal Time +1200", "+1200", "+1200", 
	"UTC+1200:+1200:Wellington:Auckland:Christchurch:Suva:Funafuti:"
	"Yaren District:Tarawa:Majuro");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0100 = Ionflux::Template::TimeZone(-60, "Coordinated Universal Time -0100", 
	"Coordinated Universal Time -0100", "-0100", "-0100", 
	"UTC-0100:-0100:Praia");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0200 = Ionflux::Template::TimeZone(-120, "Coordinated Universal Time -0200", 
	"Coordinated Universal Time -0200", "-0200", "-0200", 
	"UTC-0200:-0200");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0300 = Ionflux::Template::TimeZone(-180, "Coordinated Universal Time -0300", 
	"Coordinated Universal Time -0300", "-0300", "-0300", 
	"UTC-0300:-0300:Brasilia:Montevideo:Buenos Aires:Paramaribo:French Guiana:"
	"Nuuk");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0400 = Ionflux::Template::TimeZone(-240, "Coordinated Universal Time -0400", 
	"Coordinated Universal Time -0400", "-0400", "-0400", 
	"UTC-0400:-0400:Asuncion:La Paz:Caracas:Port-of-Spain:Georgetown:Santiago:"
	"Santo Domingo:Puerto Rico:Montserrat:Guadeloupe:Martinique:Barbados:"
	"Grenada:Dominica:St. Lucia:Halifax:Stanley");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0500 = Ionflux::Template::TimeZone(-300, "Coordinated Universal Time -0500", 
	"Coordinated Universal Time -0500", "-0500", "-0500", 
	"UTC-0500:-0500:Bogota:Quito:Lima:Panama:Nassau:Havana:Kingston:"
	"Port-au-Prince");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0600 = Ionflux::Template::TimeZone(-360, "Coordinated Universal Time -0600", 
	"Coordinated Universal Time -0600", "-0600", "-0600", 
	"UTC-0600:-0600:San Jose:Managua:Tegucigalpa:San Salvador:Guatemala:"
	"Belmopan");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0700 = Ionflux::Template::TimeZone(-420, "Coordinated Universal Time -0700", 
	"Coordinated Universal Time -0700", "-0700", "-0700", 
	"UTC-0700:-0700");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0800 = Ionflux::Template::TimeZone(-480, "Coordinated Universal Time -0800", 
	"Coordinated Universal Time -0800", "-0800", "-0800", 
	"UTC-0800:-0800");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M0900 = Ionflux::Template::TimeZone(-540, "Coordinated Universal Time -0900", 
	"Coordinated Universal Time -0900", "-0900", "-0900", 
	"UTC-0900:-0900:Adamstown");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M1000 = Ionflux::Template::TimeZone(-600, "Coordinated Universal Time -1000", 
	"Coordinated Universal Time -1000", "-1000", "-1000", 
	"UTC-1000:-1000:Honolulu:Papeete");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M1100 = Ionflux::Template::TimeZone(-660, "Coordinated Universal Time -1100", 
	"Coordinated Universal Time -1100", "-1100", "-1100", 
	"UTC-1100:-1100:Nuku'alofa:Apia:Pago Pago");
const Ionflux::Template::TimeZone DateTime::TZ_UTC_M1200 = Ionflux::Template::TimeZone(-720, "Coordinated Universal Time -1200", 
	"Coordinated Universal Time -1200", "-1200", "-1200", 
	"UTC-1200:-1200");
const Ionflux::Template::TimeZone DateTime::TZ_GMT = Ionflux::Template::TimeZone(0, "Greenwich Mean Time",
	"Greenwich Mean Time", "GMT", "GMT", "GMT");
const Ionflux::Template::TimeZone DateTime::TZ_EUROPE_WESTERN = Ionflux::Template::TimeZone(0, 
	TimeZone::DSR_TO_DST_EUROPE_WESTERN, 
	TimeZone::DSR_TO_NORMAL_EUROPE_WESTERN,
	"Western European Time",
	"Western European Summer Time",
	"WET", "WEST", 
	"WET:Europe/Western:Western Europe:Dublin:Lisbon");
const Ionflux::Template::TimeZone DateTime::TZ_EUROPE_CENTRAL = Ionflux::Template::TimeZone(60, 
	TimeZone::DSR_TO_DST_EUROPE_CENTRAL, 
	TimeZone::DSR_TO_NORMAL_EUROPE_CENTRAL,
	"Central European Time",
	"Central European Summer Time",
	"CET", "CEST", 
	"CET:Europe/Central:Central Europe:Amsterdam:Belgrade:Berlin:Bern:"
	"Bratislava:Brussels:Budapest:Copenhagen:Ljubljana:Luxembourg:"
	"Madrid:Oslo:Paris:Prague:Rome:Sarajevo:Stockholm:Tirana:Valletta:"
	"Vienna:Warsaw:Zagreb");
const Ionflux::Template::TimeZone DateTime::TZ_EUROPE_EASTERN = Ionflux::Template::TimeZone(120, 
	TimeZone::DSR_TO_DST_EUROPE_EASTERN, 
	TimeZone::DSR_TO_NORMAL_EUROPE_EASTERN,
	"Eastern European Time",
	"Eastern European Summer Time",
	"EET", "EEST", 
	"EET:Europe/Eastern:Eastern Europe:Ankara:Athens:Bucharest:Helsinki:"
	"Kiev:Minsk:Nicosia:Riga:Sofia:Tallinn:Vilnius");
const Ionflux::Template::TimeZone DateTime::TZ_UK = Ionflux::Template::TimeZone(0, 
	TimeZone::DSR_TO_DST_EUROPE_WESTERN, 
	TimeZone::DSR_TO_NORMAL_EUROPE_WESTERN,
	"Western European Time",
	"British Summer Time",
	"WET", "BST", 
	"United Kingdom:London");
const Ionflux::Template::TimeZone DateTime::TZ_USA_EASTERN = Ionflux::Template::TimeZone(-300, 
	TimeZone::DSR_TO_DST_USA,
	TimeZone::DSR_TO_NORMAL_USA,
	"Eastern Standard Time",
	"Eastern Daylight Time",
	"EST", "EDT", 
	"EST:USA/Eastern:Eastern USA:Canada/Eastern:Eastern Canada:New York:"
	"Washington, D.C.:Washington DC:Detroit:Cleveland:Columbus:Philadelphia:"
	"Boston:Baltimore:Atlanta:Jacksonville:Toronto:Ottawa:Montreal:Quebec");
const Ionflux::Template::TimeZone DateTime::TZ_USA_CENTRAL = Ionflux::Template::TimeZone(-360, 
	TimeZone::DSR_TO_DST_USA, 
	TimeZone::DSR_TO_NORMAL_USA,
	"Central Standard Time",
	"Central Daylight Time",
	"CST", "CDT", 
	"CST:USA/Central:Central USA:Canada/Central:Central Canada:Chicago:"
	"Dallas:San Antonio:Houston:New Orleans:St. Louis:Milwaukee:Minneapolis:"
	"Winnipeg:Mexico City");
const Ionflux::Template::TimeZone DateTime::TZ_USA_MOUNTAIN = Ionflux::Template::TimeZone(-420, 
	TimeZone::DSR_TO_DST_USA, 
	TimeZone::DSR_TO_NORMAL_USA,
	"Mountain Standard Time",
	"Mountain Daylight Time",
	"MST", "MDT", 
	"MST:USA/Mountain:Mountain USA:Canada/Mountain:Mountain Canada:"
	"Denver:Salt Lake City:Phoenix:El Paso:Edmonton:Calgary");
const Ionflux::Template::TimeZone DateTime::TZ_USA_PACIFIC = Ionflux::Template::TimeZone(-480, 
	TimeZone::DSR_TO_DST_USA, 
	TimeZone::DSR_TO_NORMAL_USA,
	"Pacific Standard Time",
	"Pacific Daylight Time",
	"PST", "PDT", 
	"PST:USA/Pacific:Pacific USA:Canada/Pacific:Pacific Canada:Los Angeles:"
	"Las Vegas:San Francisco:San Diego:Portland:Seattle:Vancouver");
const Ionflux::Template::TimeZone DateTime::TZ_USA_ALASKA = Ionflux::Template::TimeZone(-540, 
	TimeZone::DSR_TO_DST_USA, 
	TimeZone::DSR_TO_NORMAL_USA,
	"Alaska Standard Time",
	"Alaska Daylight Time",
	"AKST", "AKDT", 
	"AKST:USA/Alaska:Alaska USA:Anchorage");
const Ionflux::Template::TimeZone DateTime::TZ_RUSSIA_WESTERN = Ionflux::Template::TimeZone(180, 
	TimeZone::DSR_TO_DST_EUROPE_CENTRAL, 
	TimeZone::DSR_TO_NORMAL_EUROPE_CENTRAL,
	"UTC+03",
	"UTC+04",
	"UTC+03", "UTC+04", 
	"Russia/Western:Western Russia:Moscow");
const Ionflux::Template::TimeZone DateTime::TZ_EGYPT = Ionflux::Template::TimeZone(120, 
	TimeZone::DSR_TO_DST_EGYPT, 
	TimeZone::DSR_TO_NORMAL_EGYPT,
	"UTC+02",
	"UTC+03",
	"UTC+02", "UTC+03", 
	"Cairo");

// run-time type information instance constants
const DateTimeClassInfo DateTime::dateTimeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* DateTime::CLASS_INFO = &DateTime::dateTimeClassInfo;

DateTime::DateTime()
: dstState(false), utcOffset(0), timestamp(""), ticks(0), timeZone(0), year(1), month(1), day(1), hour(0), minute(0), second(0), weekDay(0), yearDay(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTimeZones();
	setTimePosix(time(0));
}

DateTime::DateTime(const Ionflux::Template::DateTime& other)
: dstState(false), utcOffset(0), timestamp(""), ticks(0), timeZone(0), year(1), month(1), day(1), hour(0), minute(0), second(0), weekDay(0), yearDay(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTimeZones();
	setTime(other);
}

DateTime::DateTime(Ionflux::Template::TimeTicks initTime)
: dstState(false), utcOffset(0), timestamp(""), ticks(0), timeZone(0), 
year(1), month(1), day(1), hour(0), minute(0), second(0), weekDay(0), 
yearDay(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTimeZones();
	setTimeTicks(initTime);
}

DateTime::DateTime(struct tm initTime)
: dstState(false), utcOffset(0), timestamp(""), ticks(0), timeZone(0), 
year(1), month(1), day(1), hour(0), minute(0), second(0), weekDay(0), 
yearDay(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTimeZones();
	setTime(initTime);
}

DateTime::DateTime(const std::string& initTime)
: dstState(false), utcOffset(0), timestamp(""), ticks(0), timeZone(0), 
year(1), month(1), day(1), hour(0), minute(0), second(0), weekDay(0), 
yearDay(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTimeZones();
	setTime(initTime);
}

DateTime::DateTime(Ionflux::Template::Year initYear, int initMonth, int 
initDay, int initHour, int initMinute, int initSecond)
: dstState(false), utcOffset(0), timestamp(""), ticks(0), timeZone(0), 
year(1), month(1), day(1), hour(0), minute(0), second(0), weekDay(0), 
yearDay(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTimeZones();
	setTime(initYear, initMonth, initDay, initHour, initMinute, initSecond);
}

DateTime::~DateTime()
{
	// TODO: Nothing ATM. ;-)
}

void DateTime::parseTimestamp(const std::string& source)
{
	if (source.size() == 0)
	    return;
	Ionflux::ObjectBase::StringVector parts;
	Ionflux::ObjectBase::StringVector dateParts;
	Ionflux::ObjectBase::StringVector timeParts;
	Ionflux::ObjectBase::explode(source, " ", parts);
	// Extract date.
	if (parts.size() < 1)
	    return;
	Ionflux::ObjectBase::explode(parts[0], "-", dateParts);
	if (dateParts.size() < 3)
	    return;
	year = ::strtol(dateParts[0].c_str(), 0, 10);
	month = ::strtol(dateParts[1].c_str(), 0, 10);
	day = ::strtol(dateParts[2].c_str(), 0, 10);
	hour = 0;
	minute = 0;
	second = 0;
	timestamp = source;
	// Extract time.
	if (parts.size() < 2)
	    return;
	Ionflux::ObjectBase::explode(parts[1], ":", timeParts);
	if (timeParts.size() < 1)
	    return;
	hour = ::strtol(timeParts[0].c_str(), 0, 10);
	if (timeParts.size() < 2)
	    return;
	minute = ::strtol(timeParts[1].c_str(), 0, 10);
	if (timeParts.size() < 3)
	    return;
	second = ::strtol(timeParts[2].c_str(), 0, 10);
}

std::string DateTime::createTimestamp()
{
	std::ostringstream result;
	result << right << setfill('0') << std::setw(4)
	    << year << TIMESTAMP_DATE_SEP << std::setw(2) 
	    << month << TIMESTAMP_DATE_SEP << std::setw(2) 
	    << day << TIMESTAMP_DATETIME_SEP << std::setw(2) 
	    << hour << TIMESTAMP_TIME_SEP << std::setw(2) 
	    << minute << TIMESTAMP_TIME_SEP << std::setw(2) 
	    << second;
	return result.str();
}

void DateTime::updateTicks()
{
	ticks = 0;
	ticks += (((((year - 1) * 365 + countLeapYears(year) 
	    + NUM_DAYS[month - 1] + day - 1) * 24 + hour) * 60 + minute) 
	    * 60 + second);
	if (isLeapYear(year) && (month > LEAP_MONTH))
	    ticks += TICKS_1D;
	timestamp = "";
	// Normalize the broken down time, set day of week etc.
	updateBrokenDownTime(0);
}

void DateTime::updateBrokenDownTime(int tickOffset)
{
	TimeTicks ticksLeft = ticks + tickOffset;
	TimeTicks num400Y = 0;
	TimeTicks num100Y = 0;
	TimeTicks num4Y = 0;
	TimeTicks num3Y = 0;
	TimeTicks num1Y = 0;
	int leapOffset = 0;
	/* Determine the coefficients of 400, 100, 4, 3 and 1 year intervals that 
	   make up the resulting year. These intervals represent the leap year 
	   cycles and thus each have constant amounts of ticks. */
	num400Y = ticksLeft / TICKS_400Y;
	ticksLeft = ticksLeft % TICKS_400Y;
	num100Y = ticksLeft / TICKS_100Y;
	ticksLeft = ticksLeft % TICKS_100Y;
	num4Y = ticksLeft / TICKS_4Y;
	ticksLeft = ticksLeft % TICKS_4Y;
	num3Y = ticksLeft / TICKS_3Y;
	ticksLeft = ticksLeft % TICKS_3Y;
	num1Y = ticksLeft / TICKS_1Y;
	ticksLeft = ticksLeft % TICKS_1Y;
	year = num400Y * 400 + num100Y * 100 + num4Y * 4 + num3Y * 3 + num1Y + 1;
	/* We have a leap year if this year is the fourth year after a complete 4 
	   year cycle block. That means a three year interval has been matched. 
	   Otherwise, a three year interval will not match. */
	leapOffset = num3Y;
	int checkTicks = 0;
	bool found = false;
	int i = 11;
	/* Determine the month by checking which interval of days fits within the 
	   remaining ticks. */
	while ((i >= 0) && !found)
	{
	    checkTicks = NUM_DAYS[leapOffset * 12 + i] * TICKS_1D;
	    if ((ticksLeft - checkTicks) >= 0)
	    {
	        month = i + 1;
	        ticksLeft -= checkTicks;
	        found = true;
	    }
	    i--;
	}
	// Determine the day of month and day of year.
	day = ticksLeft / TICKS_1D + 1;
	ticksLeft = ticksLeft % TICKS_1D;
	yearDay = NUM_DAYS[leapOffset * 12 + month - 1] + day;
	// Determine the time of day.
	hour = ticksLeft / 3600;
	ticksLeft = ticksLeft % 3600;
	minute = ticksLeft / 60;
	second = ticksLeft % 60;
	// Determine the day of week.
	TimeTicks dayOffset = (ticks + tickOffset - REF_SUNDAY) / TICKS_1D;
	ticksLeft = (ticks + tickOffset - REF_SUNDAY) % TICKS_1D;
	if (ticksLeft < 0)
	    dayOffset--;
	weekDay = dayOffset % 7;
	if (weekDay < 0)
	    weekDay += 7;
	// Another pass might be needed to calculate local time.
	if ((timeZone != 0) && (tickOffset == 0))
	{
	    /* This call requires the broken down time to be plain UTC.
	       We ensure this is the case by having checked tickOffset. */
	    utcOffset = timeZone->getCurrentOffset(*this);
	    if (utcOffset > timeZone->getOffset())
	        dstState = true;
	    /* Recalculate only if this actually is another time zone.
	       (Otherwise this would cause an infinite loop.) */
	    if (utcOffset != 0)
	        updateBrokenDownTime(utcOffset * 60);
	}
	timestamp = "";
}

void DateTime::initTimeZones()
{
	// Add time zones here to make them selectable by alias name.
	defaultTimeZones.push_back(&TZ_UTC);
	defaultTimeZones.push_back(&TZ_GMT);
	defaultTimeZones.push_back(&TZ_EUROPE_WESTERN);
	defaultTimeZones.push_back(&TZ_EUROPE_CENTRAL);
	defaultTimeZones.push_back(&TZ_EUROPE_EASTERN);
	defaultTimeZones.push_back(&TZ_UK);
	defaultTimeZones.push_back(&TZ_USA_EASTERN);
	defaultTimeZones.push_back(&TZ_USA_CENTRAL);
	defaultTimeZones.push_back(&TZ_USA_MOUNTAIN);
	defaultTimeZones.push_back(&TZ_USA_PACIFIC);
	defaultTimeZones.push_back(&TZ_USA_ALASKA);
	defaultTimeZones.push_back(&TZ_RUSSIA_WESTERN);
	defaultTimeZones.push_back(&TZ_EGYPT);
	defaultTimeZones.push_back(&TZ_UTC_P0100);
	defaultTimeZones.push_back(&TZ_UTC_P0200);
	defaultTimeZones.push_back(&TZ_UTC_P0300);
	defaultTimeZones.push_back(&TZ_UTC_P0330);
	defaultTimeZones.push_back(&TZ_UTC_P0400);
	defaultTimeZones.push_back(&TZ_UTC_P0430);
	defaultTimeZones.push_back(&TZ_UTC_P0500);
	defaultTimeZones.push_back(&TZ_UTC_P0530);
	defaultTimeZones.push_back(&TZ_UTC_P0545);
	defaultTimeZones.push_back(&TZ_UTC_P0600);
	defaultTimeZones.push_back(&TZ_UTC_P0630);
	defaultTimeZones.push_back(&TZ_UTC_P0700);
	defaultTimeZones.push_back(&TZ_UTC_P0800);
	defaultTimeZones.push_back(&TZ_UTC_P0900);
	defaultTimeZones.push_back(&TZ_UTC_P0930);
	defaultTimeZones.push_back(&TZ_UTC_P1000);
	defaultTimeZones.push_back(&TZ_UTC_P1100);
	defaultTimeZones.push_back(&TZ_UTC_P1200);
	defaultTimeZones.push_back(&TZ_UTC_M0100);
	defaultTimeZones.push_back(&TZ_UTC_M0200);
	defaultTimeZones.push_back(&TZ_UTC_M0300);
	defaultTimeZones.push_back(&TZ_UTC_M0400);
	defaultTimeZones.push_back(&TZ_UTC_M0500);
	defaultTimeZones.push_back(&TZ_UTC_M0600);
	defaultTimeZones.push_back(&TZ_UTC_M0700);
	defaultTimeZones.push_back(&TZ_UTC_M0800);
	defaultTimeZones.push_back(&TZ_UTC_M0900);
	defaultTimeZones.push_back(&TZ_UTC_M1000);
	defaultTimeZones.push_back(&TZ_UTC_M1100);
	defaultTimeZones.push_back(&TZ_UTC_M1200);
}

void DateTime::setTimePosix(time_t newTime)
{
	ticks = POSIX_EPOCH + newTime;
	updateBrokenDownTime(0);
}

void DateTime::setTimeTicks(Ionflux::Template::TimeTicks newTime)
{
	ticks = newTime;
	updateBrokenDownTime(0);
}

void DateTime::setTime(struct tm newTime)
{
	year = newTime.tm_year + 1900;
	month = newTime.tm_mon + 1;
	day = newTime.tm_mday;
	hour = newTime.tm_hour;
	minute = newTime.tm_min;
	second = newTime.tm_sec;
	updateTicks();
}

void DateTime::setTime(const std::string& newTime)
{
	parseTimestamp(newTime);
	updateTicks();
}

void DateTime::setTime(const Ionflux::Template::DateTime& newTime)
{
	setTimeTicks(newTime.getTicks());
}

void DateTime::setTime(Ionflux::Template::Year newYear, int newMonth, int 
newDay, int newHour, int newMinute, int newSecond)
{
	year = newYear;
	month = newMonth;
	day = newDay;
	hour = newHour;
	minute = newMinute;
	second = newSecond;
	updateTicks();
}

void DateTime::setLocalTime(const Ionflux::Template::DateTime& newTime, 
bool newDSTState)
{
	setLocalTime(newTime.getYear(), newTime.getMonth(), newTime.getDay(),
	    newTime.getHour(), newTime.getMinute(), newTime.getSecond(), 
	    newDSTState);
}

void DateTime::setLocalTime(const std::string& newTime, bool newDSTState)
{
	parseTimestamp(newTime);
	if (timeZone != 0)
	{
	    // Transform to UTC.
	    utcOffset = timeZone->getOffset();
	    dstState = newDSTState;
	    if (dstState)
	        utcOffset += 60;
	    minute -= utcOffset;
	}
	updateTicks();
}

void DateTime::setLocalTime(Ionflux::Template::Year newYear, int newMonth, 
int newDay, int newHour, int newMinute, int newSecond, bool newDSTState)
{
	if (timeZone != 0)
	{
	    // Transform to UTC.
	    utcOffset = timeZone->getOffset();
	    dstState = newDSTState;
	    if (dstState)
	        utcOffset += 60;
	    newMinute -= utcOffset;
	}
	setTime(newYear, newMonth, newDay, newHour, newMinute, newSecond);
}

void DateTime::setLocalTime(const Ionflux::Template::DateTime& newTime)
{
	bool newDSTState = false;
	if (timeZone != 0)
	    newDSTState = timeZone->localIsDST(newTime);
	setLocalTime(newTime, newDSTState);
}

void DateTime::setLocalTime(const std::string& newTime)
{
	bool newDSTState = false;
	DateTime newDT(newTime);
	if (timeZone != 0)
	    newDSTState = timeZone->localIsDST(newTime);
	setLocalTime(newTime, newDSTState);
}

void DateTime::setLocalTime(Ionflux::Template::Year newYear, int newMonth, 
int newDay, int newHour, int newMinute, int newSecond)
{
	bool newDSTState = false;
	DateTime newDT(newYear, newMonth, newDay, newHour, newMinute, newSecond);
	if (timeZone != 0)
	    newDSTState = timeZone->localIsDST(newDT);
	setLocalTime(newDT, newDSTState);
}

void DateTime::setHMS(int newHour, int newMinute, int newSecond)
{
	setTime(getYear(), getMonth(), getDay(), newHour, newMinute, newSecond);
}

void DateTime::setHMS(const std::string& newTime)
{
	Ionflux::ObjectBase::StringVector timeParts;
	Ionflux::ObjectBase::explode(newTime, ":", timeParts);
	int newHour = 0;
	int newMinute = 0;
	int newSecond = 0;
	if (timeParts.size() == 0)
	    return;
	if (timeParts.size() >= 1)
	    newHour = ::strtol(timeParts[0].c_str(), 0, 10);
	if (timeParts.size() >= 2)
	    newMinute = ::strtol(timeParts[1].c_str(), 0, 10);
	if (timeParts.size() >= 3)
	    newSecond = ::strtol(timeParts[2].c_str(), 0, 10);
	setHMS(newHour, newMinute, newSecond);
}

void DateTime::setHMS(const Ionflux::Template::DateTime& sourceTime)
{
	setHMS(sourceTime.getHour(), sourceTime.getMinute(), 
			sourceTime.getSecond());
}

void DateTime::setLocalHMS(int newHour, int newMinute, int newSecond, bool 
newDSTState)
{
	setLocalTime(getYear(), getMonth(), getDay(), newHour, newMinute, 
	    newSecond, newDSTState);
}

void DateTime::setLocalHMS(const std::string& newTime, bool newDSTState)
{
	Ionflux::ObjectBase::StringVector timeParts;
	Ionflux::ObjectBase::explode(newTime, ":", timeParts);
	int newHour = 0;
	int newMinute = 0;
	int newSecond = 0;
	if (timeParts.size() == 0)
	    return;
	if (timeParts.size() >= 1)
	    newHour = strtol(timeParts[0].c_str(), 0, 10);
	if (timeParts.size() >= 2)
	    newMinute = strtol(timeParts[1].c_str(), 0, 10);
	if (timeParts.size() >= 3)
	    newSecond = strtol(timeParts[2].c_str(), 0, 10);
	setLocalHMS(newHour, newMinute, newSecond, newDSTState);
}

void DateTime::setLocalHMS(const Ionflux::Template::DateTime& sourceTime, 
bool newDSTState)
{
	setLocalHMS(sourceTime.getHour(), sourceTime.getMinute(), 
	    sourceTime.getSecond(), newDSTState);
}

void DateTime::setLocalHMS(int newHour, int newMinute, int newSecond)
{
	setLocalTime(getYear(), getMonth(), getDay(), newHour, newMinute, 
	    newSecond);
}

void DateTime::setLocalHMS(const std::string& newTime)
{
	Ionflux::ObjectBase::StringVector timeParts;
	Ionflux::ObjectBase::explode(newTime, ":", timeParts);
	int newHour = 0;
	int newMinute = 0;
	int newSecond = 0;
	if (timeParts.size() == 0)
	    return;
	if (timeParts.size() >= 1)
	    newHour = strtol(timeParts[0].c_str(), 0, 10);
	if (timeParts.size() >= 2)
	    newMinute = strtol(timeParts[1].c_str(), 0, 10);
	if (timeParts.size() >= 3)
	    newSecond = strtol(timeParts[2].c_str(), 0, 10);
	setLocalHMS(newHour, newMinute, newSecond);
}

void DateTime::setLocalHMS(const Ionflux::Template::DateTime& sourceTime)
{
	setLocalHMS(sourceTime.getHour(), sourceTime.getMinute(), 
	    sourceTime.getSecond());
}

Ionflux::Template::DateTime& DateTime::shift(Ionflux::Template::TimeTicks 
shiftSeconds)
{
	setTimeTicks(ticks + shiftSeconds);
	return *this;
}

Ionflux::Template::TimeTicks DateTime::diff(const 
Ionflux::Template::DateTime& diffTime)
{
	// TODO: Implementation.
	return getTicks() - diffTime.getTicks();
}

void DateTime::setTimeZone(const std::string& newTimeZone)
{
	bool found = false;
	unsigned int i = 0;
	const TimeZone *currentTimeZone = 0;
	while (!found && (i < defaultTimeZones.size()))
	{
	    currentTimeZone = defaultTimeZones[i];
	    if ((currentTimeZone != 0) 
	        && currentTimeZone->hasAlias(newTimeZone))
	        found = true;
	    else
	        i++;
	}
	if (found)
	    setTimeZone(currentTimeZone->copy());
}

int DateTime::compareHMS(int otherHour, int otherMinute, int otherSecond)
{
	int thisSecs;
	int otherSecs;
	int result = 0;
	thisSecs = (getHour() * 60 + getMinute()) * 60 + getSecond();
	otherSecs = (otherHour * 60 + otherMinute) * 60 + otherSecond;
	if (thisSecs < otherSecs)
	    result = -1;
	else
	if (thisSecs > otherSecs)
	    result = 1;
	return result;
}

int DateTime::compareHMS(const Ionflux::Template::DateTime& otherTime)
{
	// TODO: Implementation.
	return compareHMS(otherTime.getHour(), otherTime.getMinute(), otherTime.getSecond());
}

int DateTime::compareHMS(const std::string& otherTime)
{
	Ionflux::ObjectBase::StringVector timeParts;
	Ionflux::ObjectBase::explode(otherTime, ":", timeParts);
	int otherHour = 0;
	int otherMinute = 0;
	int otherSecond = 0;
	if (timeParts.size() == 0)
	    return 0;
	if (timeParts.size() >= 1)
	    otherHour = ::strtol(timeParts[0].c_str(), 0, 10);
	if (timeParts.size() >= 2)
	    otherMinute = ::strtol(timeParts[1].c_str(), 0, 10);
	if (timeParts.size() >= 3)
	    otherSecond = ::strtol(timeParts[2].c_str(), 0, 10);
	return compareHMS(otherHour, otherMinute, otherSecond);
}

int DateTime::compareDay(const Ionflux::Template::DateTime& otherTime)
{
	if ((getYear() == otherTime.getYear())
	    && (getYearDay() == otherTime.getYearDay()))
	    return 0;
	// Different years or different days (so different days in any case).
	if (getYear() < otherTime.getYear())
	    return -1;
	if (getYear() > otherTime.getYear())
	    return 1;
	// Same year, but different days.
	if (getYearDay() < otherTime.getYearDay())
	    return -1;
	return 1;
}

Ionflux::Template::DateTime DateTime::getUTC()
{
	DateTime result;
	result.setTimeTicks(getTicks());
	return result;
}

time_t DateTime::getTimePosix() const
{
	// TODO: Implementation.
	return ticks - POSIX_EPOCH;
}

std::string DateTime::getTimestamp()
{
	if (timestamp == "")
	    timestamp = createTimestamp();
	return timestamp;
}

std::string DateTime::getHMS()
{
	// TODO: Implementation.
	return getTimestamp().substr(11, 8);
}

std::string DateTime::getDayOfWeekName() const
{
	// TODO: Implementation.
	return WEEKDAY_NAME[weekDay];
}

std::string DateTime::getDayOfWeekShortName() const
{
	// TODO: Implementation.
	return WEEKDAY_NAME_SHORT[weekDay];
}

std::string DateTime::getMonthName() const
{
	// TODO: Implementation.
	return MONTH_NAME[month - 1];
}

std::string DateTime::getMonthShortName() const
{
	// TODO: Implementation.
	return MONTH_NAME_SHORT[month - 1];
}

std::string DateTime::getTimeZoneName() const
{
	if (timeZone != 0)
	{
	    if (!isDST())
	        return timeZone->getShortNameNormal();
	    else
	        return timeZone->getShortNameDST();
	}
	return "";
}

std::string DateTime::getTimeZoneAliases() const
{
	std::string result;
	const TimeZone* currentTimeZone;
	for (unsigned int i = 0; i < defaultTimeZones.size(); i++)
	{
	    currentTimeZone = defaultTimeZones[i];
	    if (currentTimeZone != 0)
	        result.append(currentTimeZone->getAliases() + ":");
	}
	if (result.size() > 0);
	    result.erase(result.size() - 1, 1);
	return result;
}

bool DateTime::isDST() const
{
	// TODO: Implementation.
	return dstState;
}

int DateTime::getUTCOffset() const
{
	// TODO: Implementation.
	return utcOffset;
}

std::string DateTime::getRFCTimestamp() const
{
	std::ostringstream result;
	result << getDayOfWeekShortName() << ", " << setfill('0') << setw(2)
	    << getDay() << " " << getMonthShortName() << " " << getYear() << " "
	    << setw(2) << getHour() << ":" << setw(2) << getMinute() << ":" 
	    << setw(2) << getSecond();
	string timeZoneName = getTimeZoneName();
	if (timeZoneName.size() > 0)
	    result << " " << timeZoneName;
	else
	    result << " UTC";
	return result.str();
}

Ionflux::Template::DateTime& 
DateTime::operator+=(Ionflux::Template::TimeTicks seconds)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::Template::DateTime& 
DateTime::operator-=(Ionflux::Template::TimeTicks seconds)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::Template::TimeTicks DateTime::operator-(const 
Ionflux::Template::DateTime& diffTime) const
{
	// TODO: Implementation.
	return 0;
}

bool DateTime::operator==(const Ionflux::Template::DateTime& compTime) 
const
{
	// TODO: Implementation.
	return false;
}

bool DateTime::operator!=(const Ionflux::Template::DateTime& compTime) 
const
{
	// TODO: Implementation.
	return !(*this == compTime);
}

bool DateTime::operator>(const Ionflux::Template::DateTime& compTime) const
{
	// TODO: Implementation.
	return false;
}

bool DateTime::operator<(const Ionflux::Template::DateTime& compTime) const
{
	// TODO: Implementation.
	return false;
}

bool DateTime::operator>=(const Ionflux::Template::DateTime& compTime) 
const
{
	// TODO: Implementation.
	return false;
}

bool DateTime::operator<=(const Ionflux::Template::DateTime& compTime) 
const
{
	// TODO: Implementation.
	return false;
}

Ionflux::Template::Year DateTime::countLeapYears(Ionflux::Template::Year 
limit)
{
	Year result;
	result = Year((limit - 1) / 4) - Year((limit - 1) / 100) 
	    + Year((limit - 1) / 400);
	return result;
}

bool DateTime::isLeapYear(Ionflux::Template::Year checkYear)
{
	// TODO: Implementation.
	return ((checkYear % 4) == 0) && (((checkYear % 100) != 0) || ((checkYear % 400) == 0));
}

Ionflux::Template::DateTime DateTime::getNth(Ionflux::Template::Year 
targetYear, int targetMonth, int targetWeekDay, int n)
{
	// Initialize to the first of target month.
	DateTime result(targetYear, targetMonth, 1, 0, 0, 0);
	// Find the first requested day of week of the month.
	int weekDayOffset = targetWeekDay - result.getWeekDay();
	if (weekDayOffset < 0)
	    weekDayOffset += 7;
	/* Find the n-th requested day of week of the month by adding full weeks 
	   to the first. */
	weekDayOffset += (7 * (n - 1));
	result += (weekDayOffset * TICKS_1D);
	// Did we overflow into the next month?
	if ((result.getMonth() > targetMonth) 
	    || ((result.getMonth() == 1) && (targetMonth == 12)))
	{
	    // Sanity check.
	    if ((result.getMonth() > (targetMonth + 1)) 
	        || ((result.getMonth() > 1) && (targetMonth == 12)))
	        cout << "[DateTime::getNth] WARNING: Month overflow > 1 "
	        "(this shouldn't happen!)." << endl;
	    int rDay = result.getDay();
	    /* Reset to the first day of the current month (which is the 
	       requested month plus 1). */
	    result -= ((rDay - 1) * TICKS_1D);
	    // Find the first requested day of week of the month.
	    weekDayOffset = targetWeekDay - result.getWeekDay();
	    if (weekDayOffset < 0)
	        weekDayOffset += 7;
	    /* Find the last requested day of week of the requested month by 
	       substracting a full week from the first requested day of week of 
	       the current month. */
	    weekDayOffset -= 7;
	    result += (weekDayOffset * TICKS_1D);
	}
	return result;
}

bool DateTime::isTime(const std::string& checkTime)
{
	if (checkTime.size() == 0)
	    return false;
	Ionflux::ObjectBase::StringVector timeParts;
	Ionflux::ObjectBase::explode(checkTime, ":", timeParts);
	if ((timeParts.size() < 1) || (timeParts.size() > 3))
	    return false;
	bool result = true;
	unsigned int i = 0;
	while (result && (i < timeParts.size()))
	{
	    if (!Ionflux::ObjectBase::isNumber(timeParts[i]))
	        result = false;
	    else
	        i++;
	}
	if (!result)
	    return false;
	int cHour = 0;
	int cMinute = 0;
	int cSecond = 0;
	cHour = ::strtol(timeParts[0].c_str(), 0, 10);
	if (timeParts.size() > 1)
	    cMinute = ::strtol(timeParts[1].c_str(), 0, 10);
	if (timeParts.size() > 2)
	    cSecond = ::strtol(timeParts[2].c_str(), 0, 10);
	if ((cHour > 23) || (cMinute > 59) || (cSecond > 59))
	    result = false;
	return result;
}

bool DateTime::isDate(const std::string& checkDate)
{
	if (checkDate.size() == 0)
	    return false;
	Ionflux::ObjectBase::StringVector dateParts;
	Ionflux::ObjectBase::explode(checkDate, "-", dateParts);
	if (dateParts.size() != 3)
	    return false;
	bool result = (Ionflux::ObjectBase::isNumber(dateParts[0]) 
	    && Ionflux::ObjectBase::isNumber(dateParts[1]) 
	    && Ionflux::ObjectBase::isNumber(dateParts[2]));
	if (!result)
	    return false;
	int cMonth = ::strtol(dateParts[1].c_str(), 0, 10);
	int cDay = ::strtol(dateParts[2].c_str(), 0, 10);
	if ((cMonth > 12) || (cDay > 31))
	    result = false;
	return result;
}

bool DateTime::isDatetime(const std::string& checkDatetime)
{
	if (checkDatetime.size() == 0)
	    return false;
	Ionflux::ObjectBase::StringVector datetimeParts;
	Ionflux::ObjectBase::explode(checkDatetime, " ", datetimeParts);
	if (datetimeParts.size() < 1)
	    return false;
	if (datetimeParts.size() == 1)
	    return isDate(checkDatetime);
	return (isDate(datetimeParts[0]) && isTime(datetimeParts[1]));
}

Ionflux::Template::TimeTicks DateTime::getTicks() const
{
    return ticks;
}

void DateTime::setTimeZone(Ionflux::Template::TimeZone* newTimeZone)
{
	if (timeZone == newTimeZone)
	    return;
	if (newTimeZone != 0)
	    addLocalRef(newTimeZone);
	if (timeZone != 0)
	{
	    dstState = false;
	    utcOffset = 0;
	    removeLocalRef(timeZone);
	}
	timeZone = newTimeZone;
	updateBrokenDownTime(0);
}

Ionflux::Template::TimeZone* DateTime::getTimeZone() const
{
    return timeZone;
}

Ionflux::Template::Year DateTime::getYear() const
{
    return year;
}

int DateTime::getMonth() const
{
    return month;
}

int DateTime::getDay() const
{
    return day;
}

int DateTime::getHour() const
{
    return hour;
}

int DateTime::getMinute() const
{
    return minute;
}

int DateTime::getSecond() const
{
    return second;
}

int DateTime::getWeekDay() const
{
    return weekDay;
}

int DateTime::getYearDay() const
{
    return yearDay;
}

Ionflux::Template::DateTime& DateTime::operator=(const 
Ionflux::Template::DateTime& other)
{
    setTime(other);
	return *this;
}

Ionflux::Template::DateTime* DateTime::copy() const
{
    DateTime* newDateTime = create();
    *newDateTime = *this;
    return newDateTime;
}

Ionflux::Template::DateTime* 
DateTime::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<DateTime*>(other);
}

Ionflux::Template::DateTime* 
DateTime::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    DateTime* newObject = new DateTime();
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::DateTime* DateTime::create(Ionflux::Template::TimeTicks 
initTime, Ionflux::ObjectBase::IFObject* parentObject)
{
    DateTime* newObject = new DateTime(initTime);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::DateTime* DateTime::create(struct tm initTime, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    DateTime* newObject = new DateTime(initTime);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::DateTime* DateTime::create(const std::string& initTime, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    DateTime* newObject = new DateTime(initTime);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::DateTime* DateTime::create(Ionflux::Template::Year 
initYear, int initMonth, int initDay, int initHour, int initMinute, int 
initSecond, Ionflux::ObjectBase::IFObject* parentObject)
{
    DateTime* newObject = new DateTime(initYear, initMonth, initDay, 
    initHour, initMinute, initSecond);
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

/** \file DateTime.cpp
 * \brief Date and time implementation.
 */
