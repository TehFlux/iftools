/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Reporter.cpp                 Console output/logging facility.
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

#include "ionflux/Reporter.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const std::string Reporter::DEFAULT_LOGFILE_SUFFIX = ".log";
const std::string Reporter::DEFAULT_LOG_PATH = "logs";

const int Reporter::VL_ASSERT = -20;
const int Reporter::VL_NONE = 0;
const int Reporter::VL_ERROR_CRIT = 20;
const int Reporter::VL_ERROR = 40;
const int Reporter::VL_WARNING = 60;
const int Reporter::VL_WARNING_OPT = 80;
const int Reporter::VL_INFO = 100;
const int Reporter::VL_INFO_OPT = 120;
const int Reporter::VL_DEBUG = 140;
const int Reporter::VL_DEBUG_OPT = 160;
const int Reporter::VL_DEBUG_INSANE = 180;
const int Reporter::VL_ALL = 500;

Reporter::Reporter()
: verbosityLevel(Reporter::VL_INFO), logLevel(Reporter::VL_WARNING),
  logFilePath(""), logFilePrefix(""), logFileSuffix(DEFAULT_LOGFILE_SUFFIX), 
  addLineTerm(true), disableTimestamps(false), dump(0), target(0), 
  compressLogs(false), lastLogName("")
{
		consoleTimestamp[0] = false;
		consoleTimestamp[1] = false;
		logTimestamp[0] = false;
		logTimestamp[1] = true;
		setLogFilePath(DEFAULT_LOG_PATH);
}

Reporter::Reporter(int initVerbosityLevel, int initLogLevel, 
	const std::string& initLogPath, const std::string& initLogPrefix, 
	const std::string& initLogSuffix, bool initConsoleTimestamp[], 
	bool initLogTimestamp[])
: verbosityLevel(initVerbosityLevel), logLevel(initLogLevel),
  logFilePath(""), logFilePrefix(initLogPrefix), logFileSuffix(initLogSuffix), 
  addLineTerm(true), disableTimestamps(false), dump(0), target(0),
  compressLogs(false), lastLogName("")
{
	consoleTimestamp[0] = initConsoleTimestamp[0];
	consoleTimestamp[1] = initConsoleTimestamp[1];
	logTimestamp[0] = initLogTimestamp[0];
	logTimestamp[1] = initLogTimestamp[1];
	setLogFilePath(initLogPath);
}

Reporter::~Reporter()
{
	// TODO: Nothing ATM. :-)
}

void Reporter::setConfig(Node &config)
{
	verbosityLevel = getLevel(config["verbosityLevel"].getData());
	logLevel = getLevel(config["logLevel"].getData());
	string consoleDateStamp = config["consoleDateStamp"].getData();
	string consoleTimeStamp = config["consoleTimeStamp"].getData();
	consoleTimestamp[0] = toBool(consoleDateStamp);
	consoleTimestamp[1] = toBool(consoleTimeStamp);
	string logDateStamp = config["logDateStamp"].getData();
	string logTimeStamp = config["logTimeStamp"].getData();
	logTimestamp[0] = toBool(logDateStamp);
	logTimestamp[1] = toBool(logTimeStamp);
	setLogFilePath(config["logFilePath"].getData());
	logFilePrefix = config["logFilePrefix"].getData();
	logFileSuffix = config["logFileSuffix"].getData();
	compressLogs = toBool(config["compressLogs"].getData());
}

void Reporter::setVerbosityLevel(int level)
{
	verbosityLevel = level;
}

int Reporter::getVerbosityLevel()
{
	if (target != 0)
		return target->getVerbosityLevel();
	return verbosityLevel;
}

void Reporter::setLogLevel(int level)
{
	logLevel = level;
}

int Reporter::getLogLevel()
{
	if (target != 0)
		return target->getLogLevel();
	return logLevel;
}

void Reporter::setLogFilePath(const std::string &path)
{
	logFilePath = path;
	// Add slash if not present.
	if ((logFilePath.size() > 0)
		&& (logFilePath[logFilePath.size() - 1] != 
			Ionflux::Tools::DIR_SEPARATOR))
		logFilePath.append(1, Ionflux::Tools::DIR_SEPARATOR);
}

std::string Reporter::getLogFilePath()
{
	return logFilePath;
}

void Reporter::setLogFilePrefix(const std::string &prefix)
{
	logFilePrefix = prefix;
}

std::string Reporter::getLogFilePrefix()
{
	return logFilePrefix;
}

void Reporter::setLogFileSuffix(const std::string &suffix)
{
	logFileSuffix = suffix;
}

std::string Reporter::getLogFileSuffix()
{
	return logFileSuffix;
}

void Reporter::setTimestamps(bool console[], bool log[])
{
	consoleTimestamp[0] = console[0];
	consoleTimestamp[1] = console[1];
	logTimestamp[0] = log[0];
	logTimestamp[1] = log[1];
}

void Reporter::msg(const std::string& message, int level, bool lineTerm)
{
	bool status = addLineTerm;
	setAddLineTerm(lineTerm);
	msg(message, level);
	setAddLineTerm(status);
}

void Reporter::msg(const std::string& message, int level, bool lineTerm, 
	bool timeStamp)
{
	bool status = addLineTerm;
	disableTimestamps = timeStamp;
	setAddLineTerm(lineTerm);
	msg(message, level);
	setAddLineTerm(status);
	disableTimestamps = false;
}

void Reporter::msg(const std::string& message, int level)
{
	if (message == "")
		return;
	if (target != 0)
	{
		target->msg(message, level);
		return;
	}
	string timestamp = "";
	string lineTerm = "";
	DateTime now;
	// Add line terminator if not present
	if ((message.substr(message.size() - 1, 1) != "\n") && addLineTerm)
		lineTerm.append("\n");
	if (level <= verbosityLevel)
	{
		// Add optional timestamp
		if ((consoleTimestamp[0] || consoleTimestamp[1]) 
			&& !disableTimestamps)
		{
			timestamp.append("[");
			timestamp.append(createTimestamp(consoleTimestamp[0],
				consoleTimestamp[1], "-", " ", ":", now));
			timestamp.append("] ");
		}
		if (dump == 0)
		{
			if ((level == VL_INFO) || (level == VL_INFO_OPT))
				cout << timestamp << message << lineTerm;
			else
			{
				cerr << timestamp << message << lineTerm;
				if (level <= VL_ERROR)
					cerr.flush();
			}
		} else
			dump->dump(timestamp + message + lineTerm);
	}
	if (level <= logLevel)
	{
		timestamp = "";
		string fileNameTimestamp = createTimestamp(true, false, 
			"-", "_", "-", now);
		// Add optional timestamp.
		if ((logTimestamp[0] || logTimestamp[1])
			&& !disableTimestamps)
		{
			timestamp.append("[");
			timestamp.append(createTimestamp(logTimestamp[0],
				logTimestamp[1], "-", " ", ":", now));
			timestamp.append("] ");
		}
		string fileName = logFilePath
			+ logFilePrefix
			+ "_" + fileNameTimestamp
			+ logFileSuffix;
		string logMessage = timestamp + message + lineTerm;
		writeLogMessage(fileName, logMessage);
		if (compressLogs 
			&& (now.compareDay(lastLogTime) > 0)
			&& (lastLogName.size() > 0))
		{
			string logData = readFile(lastLogName);
			string compressed;
			if (bz2Compress(logData, compressed))
				if(writeFile(lastLogName + ".bz2", compressed, 'w'))
					unlink(lastLogName.c_str());
		}
		lastLogTime = now;
		lastLogName = fileName;
	}
}

bool Reporter::assert(bool assertExpr, const std::string& message)
{
	if (!assertExpr)
		msg(string("Assertion failed: ") + message, VL_ASSERT);
	return assertExpr;
}

void Reporter::writeLogMessage(const std::string& fileName, 
	const std::string& message)
{
	if (fileName.size() == 0)
		return;
	ofstream logfile(fileName.c_str(), ios_base::app);
	logfile << message;
	logfile.flush();
}

std::string Reporter::createTimestamp(bool useDate, bool useTime, 
	const std::string& dateSep, const std::string& dateTimeSep, 
	const std::string& timeSep, DateTime &dt)
{
	ostringstream timestamp;
	timestamp << right << setfill('0');
	if (useDate)
	{
		timestamp << dt.getYear() << dateSep << setw(2)
			<< dt.getMonth() << dateSep << setw(2) << dt.getDay();
		if (useTime)
			timestamp << dateTimeSep;
	}
	if (useTime)
	{
		timestamp << setw(2) << dt.getHour() << timeSep << setw(2)
			<< dt.getMinute() << timeSep << setw(2) << dt.getSecond();
	}
	return timestamp.str();
}

int Reporter::getLevel(const std::string& level)
{
	// Default is to display all messages.
	int result = VL_ALL;
	if (level == "VL_NONE")
	{
		result = VL_NONE;
	} else
	if (level == "VL_ERROR_CRIT")
	{
		result = VL_ERROR_CRIT;
	} else
	if (level == "VL_ERROR")
	{
		result = VL_ERROR;
	} else
	if (level == "VL_WARNING")
	{
		result = VL_WARNING;
	} else
	if (level == "VL_WARNING_OPT")
	{
		result = VL_WARNING_OPT;
	} else
	if (level == "VL_INFO")
	{
		result = VL_INFO;
	} else
	if (level == "VL_INFO_OPT")
	{
		result = VL_INFO_OPT;
	} else
	if (level == "VL_DEBUG")
	{
		result = VL_DEBUG;
	} else
	if (level == "VL_DEBUG_OPT")
	{
		result = VL_DEBUG_OPT;
	} else
	if (level == "VL_DEBUG_INSANE")
	{
		result = VL_DEBUG_INSANE;
	}
	return result;
}

void Reporter::setAddLineTerm(bool status)
{
	addLineTerm = status;
}

void Reporter::redirect(Reporter *newTarget)
{
	target = newTarget;
}

void Reporter::setDump(ByteDump *newDump)
{
	dump = newDump;
}

void Reporter::setCompressLogs(bool newCompressLogs)
{
	compressLogs = newCompressLogs;
}

bool Reporter::getCompressLogs()
{
	return compressLogs;
}

}

}

/** \file Reporter.cpp
 * \brief Console output/logging facility implementation.
 */
