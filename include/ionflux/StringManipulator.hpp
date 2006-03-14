#ifndef IONFLUX_TOOLS_STRINGMANIPULATOR
#define IONFLUX_TOOLS_STRINGMANIPULATOR
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringManipulator.hpp                    String manipulators.
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
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <ionflux/tools.hpp>

namespace Ionflux
{

namespace Tools
{

/** String manipulator.
 * \ingroup strfilt
 *
 * This is an abstract base class to encapsulate an object that manipulates 
 * byte strings (i.e. generates one string from another string). String 
 * manipulators can thus be used as function objects for constructing string 
 * filters.
 *
 * Each string manipulator should have an unique name by which it can be 
 * identified in a set of string manipulators. This name can be obtained with
 * the getName() function.
 */
class StringManipulator
{
	public:
		/** Constructor.
		 *
		 * Construct new StringManipulator object.
		 */
		StringManipulator() { };
		
		/** Destructor.
		 *
		 * Destruct StringManipulator object.
		 */
		virtual ~StringManipulator() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0) = 0;
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName() = 0;
		
};

/** Convert a string to uppercase.
 * \ingroup strfilt
 *
 * uppercase[(n)]\n
 * n - apply to first n characters only (optional).
 */
class StringUppercase
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringUppercase() { };
		
		/// Destructor.
		virtual ~StringUppercase() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Convert a string to lowercase.
 * \ingroup strfilt
 *
 * lowercase[(n)]\n
 * n - apply to first n characters only (optional).
 */
class StringLowercase
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringLowercase() { };
		
		/// Destructor.
		virtual ~StringLowercase() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Erase a substring.
 * \ingroup strfilt
 *
 * erase(s)\n
 * s - Substring to be erased.
 */
class StringErase
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringErase() { };
		
		/// Destructor.
		virtual ~StringErase() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Replace a substring with another string.
 * \ingroup strfilt
 *
 * replace(s, r)\n
 * s - Substring to be replaced.\n
 * r - Replacement string.
 */
class StringReplace
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringReplace() { };
		
		/// Destructor.
		virtual ~StringReplace() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Remove whitespace from boths ends of a string.
 * \ingroup strfilt
 *
 * trim\n
 * (no arguments)
 */
class StringTrim
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringTrim() { };
		
		/// Destructor.
		virtual ~StringTrim() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Remove whitespace from the beginning of a string.
 * \ingroup strfilt
 *
 * ltrim\n
 * (no arguments)
 */
class StringLTrim
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringLTrim() { };
		
		/// Destructor.
		virtual ~StringLTrim() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Remove whitespace from the end of a string.
 * \ingroup strfilt
 *
 * rtrim\n
 * (no arguments)
 */
class StringRTrim
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringRTrim() { };
		
		/// Destructor.
		virtual ~StringRTrim() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Truncate a string, appending optional dots.
 * \ingroup strfilt
 *
 * truncate(l, [d])\n
 * l - Length to truncate string to.\n
 * d - Dot string to be appended (optional)
 *
 * Note: The total length of the string will always be l, whether a dot 
 * string is specified or not.
 */
class StringTruncate
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringTruncate() { };
		
		/// Destructor.
		virtual ~StringTruncate() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Center a string using specified padding.
 * \ingroup strfilt
 *
 * center(w, p, c)\n
 * w - Center width.\n
 * p - Right/left padding.\n
 * c - Padding used for centering.
 */
class StringCenter
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringCenter() { };
		
		/// Destructor.
		virtual ~StringCenter() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Move a substring.
 * \ingroup strfilt
 *
 * move(s, l, p)\n
 * s - Start position of the substring.\n
 * l - Length of the substring.\n
 * p - Target position (&lt;number&gt;|front|back).
 */
class StringMove
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringMove() { };
		
		/// Destructor.
		virtual ~StringMove() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Append to string.
 * \ingroup strfilt
 *
 * append(s)\n
 * s - String to append.
 */
class StringAppend
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringAppend() { };
		
		/// Destructor.
		virtual ~StringAppend() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Insert a string.
 * \ingroup strfilt
 *
 * insert(s, p)\n
 * s - String to insert.\n
 * p - Target position (&lt;number&gt;|front|back).
 */
class StringInsert
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringInsert() { };
		
		/// Destructor.
		virtual ~StringInsert() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Format a number.
 * \ingroup strfilt
 *
 * numformat(d, p, t)\n
 * d - Decimals.\n
 * p - Decimal separator.\n
 * t - Thousands separator.
 */
class StringNumFormat
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringNumFormat() { };
		
		/// Destructor.
		virtual ~StringNumFormat() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Replace characters (translate).
 * \ingroup strfilt
 *
 * translate(s, t)\n
 * s - Source characters.\n
 * t - Target characters.
 */
class StringTranslate
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringTranslate() { };
		
		/// Destructor.
		virtual ~StringTranslate() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Extract substring (substr).
 * \ingroup strfilt
 *
 * substr(s, n)\n
 * s - Start position.\n
 * n - Number of characters.
 */
class StringSubstr
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringSubstr() { };
		
		/// Destructor.
		virtual ~StringSubstr() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Pad left (lpad).
 * \ingroup strfilt
 *
 * lpad(p, n)\n
 * p - Pad character.\n
 * n - Field width.
 */
class StringLPad
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringLPad() { };
		
		/// Destructor.
		virtual ~StringLPad() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Pad right (rpad).
 * \ingroup strfilt
 *
 * rpad(p, n)\n
 * p - Pad character.\n
 * n - Field width.
 */
class StringRPad
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringRPad() { };
		
		/// Destructor.
		virtual ~StringRPad() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** Soft word wrap (swrap).
 * \ingroup strfilt
 *
 * swrap(n, [p], [t])\n
 * n - Line width.\n
 * p - Prefix (optional).\n
 * t - Line terminator (optional).
 */
class StringSWrap
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringSWrap() { };
		
		/// Destructor.
		virtual ~StringSWrap() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** XML escape (xmlescape).
 * \ingroup strfilt
 *
 * xmlescape\n
 * (no arguments)
 */
class StringXMLEscape
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringXMLEscape() { };
		
		/// Destructor.
		virtual ~StringXMLEscape() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

/** URL encode (urlencode).
 * \ingroup strfilt
 *
 * xmlescape\n
 * (no arguments)
 */
class StringURLEncode
: public StringManipulator
{
	public:
		/// Name of this string manipulator.
		static const std::string STRINGMANIP_NAME;
		
		/// Constructor.
		StringURLEncode() { };
		
		/// Destructor.
		virtual ~StringURLEncode() { };
		
		/** Process bytes.
		 *
		 * Processes a byte string and returns the result.
		 *
		 * \param bytes The bytes to process.
		 * \param args Arguments for the manipulator.
		 *
		 * \return The result of applying the string manipulator to \c bytes.
		 */
		virtual std::string process(const std::string& bytes, 
			std::vector<std::string>* args = 0);
		
		/** Get name.
		 *
		 * \return Name of the string manipulator.
		 */
		virtual std::string getName();
		
};

}

}

/** \file StringManipulator.hpp
 * \brief String manipulators header.
 */
#endif
