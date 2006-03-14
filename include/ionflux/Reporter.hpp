#ifndef IONFLUX_TOOLS_REPORTER
#define IONFLUX_TOOLS_REPORTER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Reporter.hpp                 Console output/logging facility.
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
#include <sstream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include "ionflux/tools.hpp"
#include "ionflux/ByteDump.hpp"
#include "ionflux/DateTime.hpp"
#include "ionflux/Node.hpp"
#undef assert

namespace Ionflux
{

namespace Tools
{

class Node;

/** \addtogroup outplog Output/Logging facilities
 *
 * Tools for console output, error reporting and handling of logfiles.
 *
 * @{
 */

/** Reporter.
 *
 * Allows console output and logging at configurable verbosity and log 
 * levels.
 *
 * The Reporter::VL_INFO and Reporter::VL_INFO_OPT verbosity levels are 
 * special in that messages on these levels will be written to standard 
 * output (cout). Messages on all other levels will be written to standard 
 * error output (cerr).
 */
class Reporter
{
	protected:
		/// The current verbosity level.
		int verbosityLevel;
		/// The current log level.
		int logLevel;
		/// The path where log files should be stored.
		std::string logFilePath;
		/// The log file prefix
		std::string logFilePrefix;
		/// The log file suffix
		std::string logFileSuffix;
		/// Which timestamps should be used for console output
		bool consoleTimestamp[2];
		/// Which timestamps should be used for console output
		bool logTimestamp[2];
		/// Whether missing line terminators should be added
		bool addLineTerm;
		/// Whether to disable timestamps completely
		bool disableTimestamps;
		/// Optional target to redirect console output to.
		ByteDump *dump;
		/// Optional Reporter to redirect output to.
		Reporter *target;
		/// Compress logfiles flag.
		bool compressLogs;
		/// Datetime of last log entry.
		DateTime lastLogTime;
		/// File name of last log entry.
		std::string lastLogName;
		
	public:
		/// Default log file suffix.
		static const std::string DEFAULT_LOGFILE_SUFFIX;
		/// Default log path.
		static const std::string DEFAULT_LOG_PATH;
		/** Verbosity/Log level: Assertion.
		 *
		 * Assertions are output regardless of the log level settings, because 
		 * they usually indicate that something is seriously wrong with the 
		 * program.
		 */
		static const int VL_ASSERT; 
		/// Verbosity/Log level: Don't output any messages at all.
		static const int VL_NONE; 
		/// Verbosity/Log level: Output critical errors only.
		static const int VL_ERROR_CRIT;
		/// Verbosity/Log level: Include (normal) errors.
		static const int VL_ERROR;
		/// Verbosity/Log level: Include warnings.
		static const int VL_WARNING;
		/// Verbosity/Log level: Include optional warnings (pedantic mode ;-)).
		static const int VL_WARNING_OPT;
		/// Verbosity/Log level: Include informational messages.
		static const int VL_INFO;
		/// Verbosity/Log level: Include optional informational messages.
		static const int VL_INFO_OPT;
		/// Verbosity/Log level: Include debug messages.
		static const int VL_DEBUG;
		/// Verbosity/Log level: Include optional debug messages.
		static const int VL_DEBUG_OPT;
		/// Verbosity/Log level: Include insanely detailed debug messages.
		static const int VL_DEBUG_INSANE;
		/// Verbosity/Log level: Output all messages.
		static const int VL_ALL;
		
		/** Constructor.
		 *
		 * Construct new Reporter object.
		 */
		Reporter();
		
		/** Constructor.
		 *
		 * Construct new Reporter object.
		 *
		 * \param initVerbosityLevel Verbosity level.
		 * \param initLogLevel Log level.
		 * \param initLogPath Path where log files should be stored.
		 * \param initLogPrefix Prefix for log file names.
		 * \param initLogSuffix Suffix for log file names.
		 * \param initConsoleTimestamp Timestamp options for console output.
		 * \param initLogTimestamp Timestamp options for log file output.
		 */
		Reporter(int initVerbosityLevel, int initLogLevel, 
			const std::string& initLogPath, const std::string& initLogPrefix, 
			const std::string& initLogSuffix, bool initConsoleTimestamp[], 
			bool initLogTimestamp[]);
		
		/** Destructor.
		 *
		 * Destruct Reporter object.
		 */
		virtual ~Reporter();
		
		/** Set configuration.
		 *
		 * Sets the output/logging configuration from a configuration node.
		 *
		 * \param config Configuration node.
		 */
		virtual void setConfig(Node &config);
		
		/** Set verbosity level.
		 *
		 * Sets the verbosity level for console messages.
		 *
		 * \param level The new verbosity level. Should be one of the 
		 * constants defined in Reporter.
		 */
		virtual void setVerbosityLevel(int level);
		
		/** Get verbosity level.
		 *
		 * Get the current verbosity level.
		 *
		 * \note If the reporter object is redirected, this will return the 
		 * current verbosity level of the target.
		 *
		 * \return Current verbosity level.
		 */
		virtual int getVerbosityLevel();
		
		/** Set log level.
		 *
		 * Sets the log level for messages written to the logfile.
		 *
		 * \param level The new log level. Should be one of the 
		 * constants defined in Reporter.
		 */
		virtual void setLogLevel(int level);
		
		/** Get log level.
		 *
		 * Get the current log level.
		 *
		 * \note If the reporter object is redirected, this will return the 
		 * current log level of the target.
		 *
		 * \return Current log level.
		 */
		virtual int getLogLevel();
		
		/** Set log file path.
		 *
		 * Sets the path where log files should be stored.
		 *
		 * \param path The new log file path.
		 */
		virtual void setLogFilePath(const std::string &path);
		
		/** Get log file path.
		 *
		 * Get the current log file path.
		 *
		 * \return Current log file path.
		 */
		virtual std::string getLogFilePath();
		
		/** Set log file prefix.
		 *
		 * Sets the prefix to be prepended to log file names. This should be 
		 * something unique to the application or module you wish to create 
		 * logs for. Otherwise log data for different applications might get 
		 * written to the same file.
		 *
		 * \param prefix The new log file prefix.
		 */
		virtual void setLogFilePrefix(const std::string &prefix);
		
		/** Get log file prefix.
		 *
		 * Get the current log file prefix.
		 *
		 * \return Current log file prefix.
		 */
		virtual std::string getLogFilePrefix();
		
		/** Set log file suffix.
		 *
		 * Sets the suffix to be appended to log file names.
		 *
		 * \param suffix The new log file suffix.
		 */
		virtual void setLogFileSuffix(const std::string &suffix);
		
		/** Get log file prefix.
		 *
		 * Get the current log file suffix.
		 *
		 * \return Current log file suffix.
		 */
		virtual std::string getLogFileSuffix();
		
		/** Set timestamp options.
		 *
		 * Use this function to specify which timestamps you want to have in 
		 * your console output or logs. Each parameter is an array of two 
		 * booleans. Set the first value to 'true' to enable date timestamps,
		 * use the second value for time timestamps. Any combination is 
		 * possible, while it doesn't necessarily have to make sense. ;-)\n
		 * Default is no timestamps for console output and time timestamps for 
		 * logfile output.
		 *
		 * \param console Timestamp options for console output.
		 * \param log Timestamp options for logfile output.
		 */
		virtual void setTimestamps(bool console[], bool log[]);
		
		/** Submit message for output/logging.
		 *
		 * Use this function to submit a message for console output or 
		 * logging. The Reporter class will then do all the rest. :-)
		 *
		 * \param message The message to be written to the console or a 
		 * logfile.
		 * \param level The log/verbosity level of the message. Should be one 
		 * of the constants defined in Reporter.
		 */
		virtual void msg(const std::string& message, int level);
		
		/** Submit message for output/logging.
		 *
		 * Use this function to submit a message for console output or 
		 * logging. The Reporter class will then do all the rest. :-)\n
		 * This function allows you to override the default line termination 
		 * setting.
		 *
		 * \param message The message to be written to the console or a 
		 * logfile.
		 * \param level The log/verbosity level of the message. Should be one 
		 * of the constants defined in Reporter.
		 * \param lineTerm Whether to add missing line terminators.
		 */
		virtual void msg(const std::string& message, int level, bool lineTerm);
		
		/** Submit message for output/logging.
		 *
		 * Use this function to submit a message for console output or 
		 * logging. The Reporter class will then do all the rest. :-)\n
		 * This function allows you to override the default line termination 
		 * setting and the default timestamp settings.
		 *
		 * \param message The message to be written to the console or a 
		 * logfile.
		 * \param level The log/verbosity level of the message. Should be one 
		 * of the constants defined in Reporter.
		 * \param lineTerm Whether to add missing line terminators.
		 * \param timeStamp Whether to disable timestamps for this message.
		 */
		virtual void msg(const std::string& message, int level, bool lineTerm, 
			bool timeStamp);
		
		/** Assertion.
		 *
		 * Perform an assertion check. If the check fails (i.e., \c assertExpr 
		 * evaluates to \c false), the message is passed to the output 
		 * facility, otherwise no action is taken.
		 *
		 * \param assertExpr Assertion to be evaluated.
		 * \param message Message associated with a failed assertion.
		 *
		 * \return Value of the assertion expression \c assertExpr.
		 */
		virtual bool assert(bool assertExpr, const std::string& message);
		
		/** Create a timestamp.
		 *
		 * Creates a timestamp using the specified options.
		 *
		 * \param useDate Include current date in timestamp.
		 * \param useTime Include current time in timestamp.
		 * \param dateSep Separator for date elements.
		 * \param dateTimeSep Separator between date and time.
		 * \param timeSep Separator for time elements.
		 * \param dt Datetime to be used for the time stamp.
		 *
		 * \return Timestamp.
		 */
		static std::string createTimestamp(bool useDate, bool useTime, 
			const std::string& dateSep, const std::string& dateTimeSep, 
			const std::string& timeSep, DateTime &dt);
		
		/** Write a message to a logfile.
		 *
		 * Writes the message to specified logfile.
		 *
		 * \param fileName File name of the logfile.
		 * \param message The message to be written to the logfile.
		 */
		virtual void writeLogMessage(const std::string& fileName, 
			const std::string& message);
		
		/** Get numerical verbosity level.
		 *
		 * Translates a verbosity or log level identified by a string to its 
		 * numerical counterpart which is used by Reporter functions.
		 *
		 * \param level The string representation of the verbosity/log level.
		 *
		 * \return Verbosity/log level.
		 */
		virtual int getLevel(const std::string& level);
		
		/** Set line terminator option.
		 *
		 * Use this function to set whether line terminators should be 
		 * appended to messages lacking them.\n
		 * Default is to append missing line terminators ('true').
		 *
		 * \param status Whether missing line terminators should be added.
		 */
		virtual void setAddLineTerm(bool status);
		
		/** Set redirection target.
		 *
		 * Set a target Reporter object for output redirection. This 
		 * effectively bypasses all log level settings of the redirecting 
		 * object.
		 *
		 * \param newTarget Target the output should be redirected to.
		 */
		virtual void redirect(Reporter *newTarget);
		
		/** Set byte dump.
		 *
		 * Use this function to specify a byte dump. All console output 
		 * will be redirected to the byte dump instead of being output to the 
		 * console. You can pass null to this function disable the 
		 * redirection.
		 *
		 * \param newDump Target for output redirection.
		 */
		virtual void setDump(ByteDump *newDump);
		
		/** Set logfile compression flag.
		 *
		 * Sets the logfile compression flag. If set to \c true, logfiles 
		 * will be compressed at the end of a day.
		 *
		 * \param newCompressLogs Whether to compress logfiles.
		 */
		virtual void setCompressLogs(bool newCompressLogs);
		
		/** Get logfile compression flag.
		 *
		 * \return \c true if logfile compression is enabled, \c false 
		 * otherwise.
		 */
		virtual bool getCompressLogs();
		
};

/// @}

}

}

/** \file Reporter.hpp
 * \brief Console output/logging facility header.
 */
#endif
