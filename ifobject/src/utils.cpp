/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.cpp                 Utility functions (implementation).
 * ==========================================================================
 *
 * This file is part of Ionflux Object Base System.
 * 
 * Ionflux Object Base System is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the 
 * License, or (at your option) any later version.
 * 
 * Ionflux Object Base System is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Object Base System; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "sha1.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/IFObject.hpp"
#include "ifobject/IFMMEvent.hpp"
#include "ifobject/IFLogMessage.hpp"
#include "ifobject/IFError.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

bool readFile(const std::string& fileName, std::string& target, 
    Ionflux::ObjectBase::IFObject* logTarget)
{
	ifstream inFile(fileName.c_str());
    if (!inFile)
    {
        if (logTarget != 0)
        {
            ostringstream message;
            message << "Could not open file '" << fileName << "'.";
            logTarget->log(IFLogMessage(message.str(), VL_ERROR, 0, 
                "readFile"));
        }
        return false;
    }
	char *buffer = new char[READ_BUFFER_SIZE];
	int bytesRead;
	inFile.read(buffer, READ_BUFFER_SIZE);
	bytesRead = inFile.gcount();
    target = "";
	while (bytesRead > 0)
	{
		target.append(buffer, bytesRead);
		inFile.read(buffer, READ_BUFFER_SIZE);
		bytesRead = inFile.gcount();
	}
	delete[] buffer;
    return true;
}

bool writeFile(const std::string& fileName, const std::string& data, 
	char writeMode)
{
	if (fileName == "")
		return false;
	ofstream outputFileStream;
	if (writeMode == 'a')
		outputFileStream.open(fileName.c_str(), ios_base::app);
	else
		outputFileStream.open(fileName.c_str(), ios_base::out);
	if (!outputFileStream)
	{
	    std::ostringstream status;
		status << "[writeFile] Could not write to file '" 
			<< fileName << "'";
	    throw IFError(status.str());
	}
	outputFileStream.write(data.c_str(), data.size());
	// outputFileStream.flush();
	return true;
}

void explode(const std::string& bytes, const std::string& splitString, 
	std::vector<std::string>& result)
{
	result.clear();
	if ((bytes.size() == 0) 
        || (splitString.size() == 0))
		return;
	string::size_type currentPos = 0;
	string::size_type nextPos;
	while ((currentPos < bytes.size()) 
		&& ((nextPos = bytes.find(splitString, currentPos)) != string::npos))
	{
		if ((nextPos - currentPos) > 0)
			result.push_back(bytes.substr(currentPos, nextPos - currentPos));
		else
			result.push_back("");
		currentPos = nextPos + 1;
	}
	result.push_back(bytes.substr(currentPos, bytes.size() - currentPos));
}

bool isOneOf(char c, const std::string& testChars, bool invert)
{
    if (invert)
        return !isOneOf(c, testChars, false);
	if (testChars.size() == 0)
		return false;
	if (testChars.find_first_of(c) == string::npos)
		return false;
	return true;
}

bool isNumber(const std::string &bytes)
{
	if (bytes.size() == 0)
		return false;
	bool result = true;
	unsigned int i = 0;
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], "0123456789"));
		i++;
	}
	return result;
}

bool isInteger(const std::string &bytes)
{
	if (bytes.size() == 0)
		return false;
	bool result = true;
	unsigned int i = 0;
	// Check signum.
	if ((bytes.size() > 1) && isOneOf(bytes[i], "+-"))
		i++;
	// Check integer part.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], "0123456789"));
		i++;
	}
	return result;
}

bool isFloat(const std::string &bytes)
{
	if (bytes.size() == 0)
		return false;
	const string numbers = "0123456789";
	const string dots = ".";
	const string exponent = "eE";
	const string signum = "+-";
	unsigned int i = 0;
	if (bytes.size() == 1)
		return isOneOf(bytes[0], numbers);
	// Check signum.
	if (isOneOf(bytes[i], signum))
		i++;
	bool result = true;
	// Check integer part.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], numbers));
		i++;
	}
	/* Accept dot if it is either preceded by a number (thus i > 1) 
	   or the next character is a number. */
	if (isOneOf(bytes[i - 1], dots) 
		&& ((i > 1) || ((i < bytes.size()) && isOneOf(bytes[i], numbers))))
		result = true;
	// Check decimal part.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], numbers));
		i++;
	}
	if (isOneOf(bytes[i - 1], exponent))
		result = true;
	// Check signum of exponent.
	if ((i < bytes.size()) && isOneOf(bytes[i], signum))
		i++;
	// Check exponent.
	while (result && (i < bytes.size()))
	{
		result = (result && isOneOf(bytes[i], numbers));
		i++;
	}
	return result;
}

bool isIdentifier(const std::string &bytes)
{
	const string identifierChars = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
	bool result = true;
	for (unsigned int i = 0; i < bytes.size(); i++)
		result = (result && isOneOf(bytes[i], identifierChars));
	return result;
}

std::string toUpper(const std::string &text, unsigned int numChars, 
	unsigned int offset)
{
	ostringstream result;
	char currentChar;
	if (numChars == 0)
		numChars = text.size();
	unsigned int count = 0;
	for (unsigned int i = 0; i < text.size(); i++)
	{
		if ((i >= offset) && (count < numChars))
		{
			currentChar = static_cast<char>(toupper(text[i]));
			count++;
		} else
			currentChar = text[i];
		result << currentChar;
	}
	return result.str();
}

std::string toLower(const std::string &text, unsigned int numChars, 
	unsigned int offset)
{
	ostringstream result;
	char currentChar;
	if (numChars == 0)
		numChars = text.size();
	unsigned int count = 0;
	for (unsigned int i = 0; i < text.size(); i++)
	{
		if ((i >= offset) && (count < numChars))
		{
			currentChar = static_cast<char>(tolower(text[i]));
			count++;
		} else
			currentChar = text[i];
		result << currentChar;
	}
	return result.str();
}

bool toBool(const std::string &bytes)
{
    std::string v0 = toLower(bytes);
    if ((v0 == "true") 
        || (v0 == "yes") 
        || (v0 == "1") 
        || (v0 == "on"))
        return true;
    return false;
}

double toFloat(const std::string& bytes)
{
	if (bytes.size() == 0)
		return 0.;
	const std::string numbers = "0123456789";
	const std::string dots = ".";
	const std::string exponent = "eE";
	const std::string signum = "+-";
	unsigned int i = 0;
	if (bytes.size() == 1)
	{
	    if (isOneOf(bytes[0], numbers))
	        return static_cast<double>(strtol(bytes.c_str(), 0, 10));
	}
	// Check signum.
	double sig0 = 1.;
	if (isOneOf(bytes[i], signum))
	{
	    if (bytes[i] == '-')
	        sig0 = -1.;
		i++;
	}
	bool result = true;
	// Check integer part.
	std::string int0;
	while (result && (i < bytes.size()))
	{
	    if (!isOneOf(bytes[i], numbers))
	        result = false;
	    else
	        int0.append(1, bytes[i]);
		i++;
	}
	double int1 = 0.;
	if (int0.size() > 0)
	    int1 = static_cast<double>(strtol(int0.c_str(), 0, 10));
	/* Accept dot if it is either preceded by a number (thus i > 1) 
	   or the next character is a number. */
	if (isOneOf(bytes[i - 1], dots) 
		&& ((i > 1) || ((i < bytes.size()) && isOneOf(bytes[i], numbers))))
		result = true;
	// Check fraction part.
	std::string frac0;
	while (result && (i < bytes.size()))
	{
	    if (!isOneOf(bytes[i], numbers))
	        result = false;
	    else
	        frac0.append(1, bytes[i]);
		i++;
	}
	double frac1 = 0.;
	if (frac0.size() > 0)
	    frac1 = static_cast<double>(strtol(frac0.c_str(), 0, 10));
	if (isOneOf(bytes[i - 1], exponent))
		result = true;
	if (!result)
	    // Best guess.
	    return sig0 * (int1 + pow(10., -1. * frac0.size()) * frac1);
	// Check signum of exponent.
	double expSig0 = 1.;
	if ((i < bytes.size()) && isOneOf(bytes[i], signum))
	{
	    if (bytes[i] == '-')
	        expSig0 = -1.;
		i++;
	}
	// Check exponent.
	std::string exp0;
	while (result && (i < bytes.size()))
	{
	    if (!isOneOf(bytes[i], numbers))
	        result = false;
	    else
	        exp0.append(1, bytes[i]);
		i++;
	}
	double exp1 = 0.;
	if (exp0.size() > 0)
	    exp1 = static_cast<double>(strtol(exp0.c_str(), 0, 10));
	return sig0 * (int1 + pow(10., -1. * frac0.size()) * frac1) 
	    * pow(10., expSig0 * exp1);
}

std::string trim(const std::string& bytes, bool leftTrim, bool rightTrim)
{
	if (bytes.size() == 0)
		return "";
	int from = 0;
	int to = bytes.size() - 1;
	static const string trimChars = " \t\r\n";
	if (leftTrim)
		while ((from <= to)
			&& isOneOf(bytes[from], trimChars))
			from++;
	if (rightTrim)
		while ((to >= from)
			&& isOneOf(bytes[to], trimChars))
			to--;
	string result;
	for (int i = from; i <= to; i++)
		result.append(1, bytes[i]);
	return result;
}

bool hasPrefix(const std::string& bytes, const std::string& prefix, 
    bool ignoreCase)
{
    std::string checkBytes;
    std::string checkPrefix;
    if (ignoreCase)
    {
        checkBytes = toLower(bytes);
        checkPrefix = toLower(prefix);
    } else
    {
        checkBytes = bytes;
        checkPrefix = prefix;
    }
    if (checkBytes.size() < checkPrefix.size())
        return false;
    if (checkBytes.substr(0, checkPrefix.size()) == checkPrefix)
        return true;
    return false;
}

bool hasPrefix(const std::string& bytes, const std::vector<std::string>& 
    prefixes, bool ignoreCase)
{
    std::vector<std::string>::const_iterator i = prefixes.begin();
    while (i != prefixes.end())
    {
        if (hasPrefix(bytes, *i, ignoreCase))
            return true;
        i++;
    }
    return false;
}

Ionflux::ObjectBase::UInt64 getTimeTicks()
{
    timeval t0;
    if (::gettimeofday(&t0, 0) == -1)
        throw IFError("[getTimeTicks] Failed to get time value!");
    UInt64 ct = static_cast<UInt64>(t0.tv_sec)
        * 1000000 + t0.tv_usec;
    return ct;
}

std::string makeHex(const std::string& inputData)
{
    std::ostringstream buffer;
	buffer << uppercase << right << setfill('0') << hex;
	for (unsigned int i = 0; i < inputData.size(); i++)
		buffer << setw(2) << int(static_cast<unsigned char>(inputData[i]));
	return buffer.str();
}

std::string makeReadable(const std::string& inputData, 
	const std::string& replacement)
{
    std::ostringstream buffer;
	unsigned char currentChar;
	for (unsigned int i = 0; i < inputData.size(); i++)
	{
		currentChar = static_cast<unsigned char>(inputData[i]);
		if ((currentChar >= 32) && (currentChar <= 126))
		{
			buffer << inputData[i];
		} else
		{
			buffer << replacement;
		}
	}
	return buffer.str();
}

std::string makeNiceHex(const std::string& hex, const std::string& readable, 
	int bytesPerLine, int groupBytes, bool showPos)
{
    std::ostringstream buffer;
	string paddedHex(hex);
	string paddedReadable(readable);
	if ((paddedHex.size() % 2) != 0)
		paddedHex.append(" ");
	while (((paddedHex.size() / 2) % bytesPerLine) != 0)
		paddedHex.append("  ");
	unsigned int bytes = paddedHex.size() / 2;
	while (paddedReadable.size() < bytes)
		paddedReadable.append(" ");
	int readablePos = 0;
	int lineNum = 0;
	for (unsigned int i = 0; i < bytes; i++)
	{
		if (((i % bytesPerLine) == 0) 
		    && (lineNum > 0))
		{
		    buffer << "\n";
		}
		buffer << paddedHex.substr(2 * i, 2) << " ";
		if ((((i + 1) % groupBytes) == 0) 
		    && (((i + 1) % bytesPerLine) != 0))
		{
			buffer << " ";
		}
		if (((i + 1) % bytesPerLine) == 0)
		{
			buffer << " " << paddedReadable.substr(
			    readablePos, bytesPerLine);
			if (showPos)
			    buffer << "  " << (i + 1);
			readablePos += bytesPerLine;
			lineNum++;
		}
	}
	return buffer.str();
}

std::string parseHex(const std::string &inputData)
{
	int currentByte;
	std::string result;
	for (unsigned int i = 0; i < (inputData.size() / 2); i++)
	{
		currentByte = strtol(inputData.substr(2 * i, 2).c_str(), 0, 16);
		result.append(1, static_cast<char>(currentByte));
	}
	return result;
}

std::string sha1(const std::string& secret, bool hexOut)
{
	sha1_context ctx;
	unsigned char sha1sum[20];
	char *buffer = new char[secret.size()];
	memcpy(reinterpret_cast<void *>(buffer), 
		reinterpret_cast<const void *>(secret.c_str()), secret.size());
	::sha1_starts(&ctx);
	::sha1_update(&ctx, reinterpret_cast<uint8 *>(buffer), secret.size());
	::sha1_finish(&ctx, sha1sum);
	delete[] buffer;
	if (hexOut)
		return makeHex(string(reinterpret_cast<const char*>(sha1sum), 20));
	return string(reinterpret_cast<const char*>(sha1sum), 20);
}

std::string hmac(const std::string& key, const std::string& message, 
    bool hexOut)
{
    const unsigned int blockSize = 64;
    std::string tKey(key);
    if (tKey.size() > blockSize)
        tKey = sha1(tKey);
    if (tKey.size() < blockSize)
        tKey.append(blockSize - tKey.size(), '\x0');
    std::string oKey;
    std::string iKey;
    for (unsigned int i = 0; i < blockSize; i++)
    {
        oKey.append(1, tKey[i] ^ '\x5c');
        iKey.append(1, tKey[i] ^ '\x36');
    }
    std::string t0(iKey);
    t0.append(message);
    std::string result(oKey);
    result.append(sha1(t0));
    return sha1(result, hexOut);
}

void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::IntVector& target, 
    const std::string& separator)
{
    StringVector parts0;
    explode(data, ",", parts0);
    for (StringVector::const_iterator i = parts0.begin(); 
        i != parts0.end(); i++)
        target.push_back(strtol((*i).c_str(), 0, 10));
}

void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::UIntVector& target, 
    const std::string& separator)
{
    StringVector parts0;
    explode(data, ",", parts0);
    for (StringVector::const_iterator i = parts0.begin(); 
        i != parts0.end(); i++)
        target.push_back(strtol((*i).c_str(), 0, 10));
}

void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::DoubleVector& target, 
    const std::string& separator)
{
    StringVector parts0;
    explode(data, ",", parts0);
    for (StringVector::const_iterator i = parts0.begin(); 
        i != parts0.end(); i++)
        target.push_back(toFloat(trim(*i)));
}

void addValues(Ionflux::ObjectBase::IntVector& target, 
    unsigned int numValues, 
    int v0, int v1, int v2, int v3, 
    int v4, int v5, int v6, int v7, 
    int v8, int v9, int v10, int v11, 
    int v12, int v13, int v14, int v15)
{
    if (numValues > 0)
        target.push_back(v0);
    if (numValues > 1)
        target.push_back(v1);
    if (numValues > 2)
        target.push_back(v2);
    if (numValues > 3)
        target.push_back(v3);
    if (numValues > 4)
        target.push_back(v4);
    if (numValues > 5)
        target.push_back(v5);
    if (numValues > 6)
        target.push_back(v6);
    if (numValues > 7)
        target.push_back(v7);
    if (numValues > 8)
        target.push_back(v8);
    if (numValues > 9)
        target.push_back(v9);
    if (numValues > 10)
        target.push_back(v10);
    if (numValues > 11)
        target.push_back(v11);
    if (numValues > 12)
        target.push_back(v12);
    if (numValues > 13)
        target.push_back(v13);
    if (numValues > 14)
        target.push_back(v14);
    if (numValues > 15)
        target.push_back(v15);
}

void addValues(Ionflux::ObjectBase::UIntVector& target, 
    unsigned int numValues, 
    unsigned int v0, unsigned int v1, 
    unsigned int v2, unsigned int v3, 
    unsigned int v4, unsigned int v5, 
    unsigned int v6, unsigned int v7, 
    unsigned int v8, unsigned int v9, 
    unsigned int v10, unsigned int v11, 
    unsigned int v12, unsigned int v13, 
    unsigned int v14, unsigned int v15)
{
    if (numValues > 0)
        target.push_back(v0);
    if (numValues > 1)
        target.push_back(v1);
    if (numValues > 2)
        target.push_back(v2);
    if (numValues > 3)
        target.push_back(v3);
    if (numValues > 4)
        target.push_back(v4);
    if (numValues > 5)
        target.push_back(v5);
    if (numValues > 6)
        target.push_back(v6);
    if (numValues > 7)
        target.push_back(v7);
    if (numValues > 8)
        target.push_back(v8);
    if (numValues > 9)
        target.push_back(v9);
    if (numValues > 10)
        target.push_back(v10);
    if (numValues > 11)
        target.push_back(v11);
    if (numValues > 12)
        target.push_back(v12);
    if (numValues > 13)
        target.push_back(v13);
    if (numValues > 14)
        target.push_back(v14);
    if (numValues > 15)
        target.push_back(v15);
}

void addValues(Ionflux::ObjectBase::DoubleVector& target, 
    unsigned int numValues, 
    double v0, double v1, double v2, double v3, 
    double v4, double v5, double v6, double v7, 
    double v8, double v9, double v10, double v11, 
    double v12, double v13, double v14, double v15)
{
    if (numValues > 0)
        target.push_back(v0);
    if (numValues > 1)
        target.push_back(v1);
    if (numValues > 2)
        target.push_back(v2);
    if (numValues > 3)
        target.push_back(v3);
    if (numValues > 4)
        target.push_back(v4);
    if (numValues > 5)
        target.push_back(v5);
    if (numValues > 6)
        target.push_back(v6);
    if (numValues > 7)
        target.push_back(v7);
    if (numValues > 8)
        target.push_back(v8);
    if (numValues > 9)
        target.push_back(v9);
    if (numValues > 10)
        target.push_back(v10);
    if (numValues > 11)
        target.push_back(v11);
    if (numValues > 12)
        target.push_back(v12);
    if (numValues > 13)
        target.push_back(v13);
    if (numValues > 14)
        target.push_back(v14);
    if (numValues > 15)
        target.push_back(v15);
}

std::string getIndent(unsigned int level, unsigned int indentWidth, 
    char indentChar)
{
    return std::string(level * indentWidth, indentChar);
}

std::string escape(const std::string &source, const std::string& escapeWhat)
{
	if (source.size() == 0)
		return "";
	std::string result;
	for (unsigned int i = 0; i < source.size(); i++)
	{
		if (isOneOf(source[i], escapeWhat))
			result.append(1, '\\');
		result.append(1, source[i]);
	}
	return result;
}

std::string mmTypeIDGetString(Ionflux::ObjectBase::MMEventTypeID typeID)
{
    if (typeID == IFMMEvent::TYPE_UNDEFINED)
        return "UNDEFINED";
    if (typeID == IFMMEvent::TYPE_CREATE)
        return "CREATE";
    if (typeID == IFMMEvent::TYPE_DELETE)
        return "DELETE";
    if (typeID == IFMMEvent::TYPE_ADD_REF)
        return "ADD_REF";
    if (typeID == IFMMEvent::TYPE_REMOVE_REF)
        return "REMOVE_REF";
    if (typeID == IFMMEvent::TYPE_ADD_LOCAL_REF)
        return "ADD_LOCAL_REF";
    if (typeID == IFMMEvent::TYPE_REMOVE_LOCAL_REF)
        return "REMOVE_LOCAL_REF";
    return "<unknown>";
}

std::string getTimestamp()
{
    time_t t0;
    ::time(&t0);
    tm* t1 = ::localtime(&t0);
    char buf[256];
    size_t s0 = ::strftime(buf, 256, "%Y-%m-%d %H:%M:%S", t1);
    if (s0 == 0)
        throw IFError("[getTimeStamp] Could not create timestamp.");
    return std::string(buf, s0);
}

std::string appendDirSeparator(const std::string& path, 
	unsigned char separator)
{
	string result = path;
	if ((result.size() > 0)
		&& (result[result.size() - 1] != separator))
		result.append(1, separator);
	return result;
}

std::string prependDirSeparator(const std::string& path, 
	unsigned char separator)
{
	string result;
	if ((path.size() == 0)
		|| (path[0] != separator))
		result.append(1, separator);
	result.append(path);
	return result;
}

Ionflux::ObjectBase::LineBuffer createLineBuffer(
    const Ionflux::ObjectBase::StringVector& data)
{
    int n0 = data.size();
    LineBuffer result;
    result.data = new char*[n0];
    Ionflux::ObjectBase::nullPointerCheck(result.data, 
        "createLineBuffer", "Line buffer");
    for (int i = 0; i < n0; i++)
    {
        std::string cl = data[i];
        int n1 = cl.size() + 1;
        char* cd = new char[n1];
        if (cd == 0)
        {
            result.size = i;
            cleanupLineBuffer(result);
            std::ostringstream status;
            status << "[createLineBuffer] "
                "Could not allocate buffer for line #" << i << ".";
            throw IFError(status.str());
        }
        ::strncpy(cd, cl.c_str(), n1);
        result.data[i] = cd;
    }
    result.size = n0;
    return result;
}

Ionflux::ObjectBase::LineBuffer createLineBuffer(const std::string& data)
{
    StringVector sv;
    explode(data, "\n", sv);
    return createLineBuffer(sv);
}

void cleanupLineBuffer(Ionflux::ObjectBase::LineBuffer& lineBuffer)
{
    if (lineBuffer.data != 0)
    {
        for (int i = 0; i < lineBuffer.size; i++)
        {
            char* cd = lineBuffer.data[i];
            delete[] cd;
            lineBuffer.data[i] = 0;
        }
        delete[] lineBuffer.data;
    }
    lineBuffer.data = 0;
    lineBuffer.size = 0;
}

void getStringVector(const Ionflux::ObjectBase::LineBuffer& lineBuffer, 
    Ionflux::ObjectBase::StringVector& target)
{
    for (int i = 0; i < lineBuffer.size; i++)
    {
        if (lineBuffer.data[i] != 0)
            target.push_back(std::string(lineBuffer.data[i]));
    }
}

Ionflux::ObjectBase::LineBufferConst createLineBufferConst(
    const Ionflux::ObjectBase::LineBuffer& lineBuffer)
{
    LineBufferConst result;
    result.data = 0;
    result.size = 0;
    if (lineBuffer.size == 0)
        return result;
    result.data = new const char*[lineBuffer.size];
    Ionflux::ObjectBase::nullPointerCheck(result.data, 
        "createLineBufferConst", "Line buffer");
    if (lineBuffer.data != 0)
    {
        for (int i = 0; i < lineBuffer.size; i++)
            result.data[i] = lineBuffer.data[i];
    }
    result.size = lineBuffer.size;
    return result;
}

void cleanupLineBuffer(Ionflux::ObjectBase::LineBufferConst& lineBuffer)
{
    if (lineBuffer.data != 0)
        delete[] lineBuffer.data;
    lineBuffer.data = 0;
    lineBuffer.size = 0;
}

std::string getErrorString(const std::string& message, 
    const std::string& source, 
    const Ionflux::ObjectBase::IFObject* sourceObj)
{
    if (sourceObj != 0)
        return sourceObj->getErrorString(message, source);
    std::ostringstream status;
    status << "[" << source << "] " << message;
    return status.str();
}

Ionflux::ObjectBase::DataSize readFromStream(std::istream& s, 
    std::string& target, Ionflux::ObjectBase::DataSize numBytes, 
    Ionflux::ObjectBase::DataSize offset)
{
    if (offset != DATA_SIZE_INVALID)
    {
        s.seekg(offset);
        if (!s.good())
        {
            std::ostringstream status;
            status << "[readFromStream] " 
                "Invalid stream offset: " << offset;
            throw IFError(status.str());
        }
    }
    Ionflux::ObjectBase::DataSize bytesLeft = 0;
    std::streampos p0 = s.tellg();
    s.seekg(0, s.end);
    std::streampos p1 = s.tellg();
    s.seekg(p0);
    if (p1 > p0)
        bytesLeft = p1 - p0;
    else
        bytesLeft = 0;
    if ((numBytes == DATA_SIZE_INVALID) 
        || (numBytes > bytesLeft))
        numBytes = bytesLeft;
    if (numBytes == 0)
        return 0;
    char* buffer = new char[numBytes];
    if (buffer == 0)
    {
        throw IFError("[readFromStream] "
            "Could not allocate read buffer.");
    }
    s.read(buffer, numBytes);
    if (s.fail() || s.bad())
    {
        std::ostringstream status;
        status << "[readFromStream] " 
            "Could not read from stream (numBytes = " 
            << numBytes;
        if (offset != DATA_SIZE_INVALID)
            status << ", offset = " << offset;
        status << ").";
        throw IFError(status.str());
    }
    target.assign(buffer, numBytes);
    delete[] buffer;
    return numBytes;
}

Ionflux::ObjectBase::DataSize writeToStream(std::ostream& s, 
    const std::string& source, Ionflux::ObjectBase::DataSize offset)
{
    if (offset != DATA_SIZE_INVALID)
    {
        s.seekp(offset);
        if (s.fail() || s.bad())
        {
            std::ostringstream status;
            status << "[writeToStream] " 
                "Invalid stream offset: " << offset;
            throw IFError(status.str());
        }
    }
    s.write(source.c_str(), source.size());
    if (s.fail() || s.bad())
    {
        std::ostringstream status;
        status << "[writeToStream] " 
            "Could not write to stream";
        if (offset != DATA_SIZE_INVALID)
            status << " (offset = " << offset;
        status << ").";
        throw IFError(status.str());
    }
    return source.size();
}

std::string getStreamTypeValueString(Ionflux::ObjectBase::StreamTypeID t)
{
    if (t == Ionflux::ObjectBase::STREAM_TYPE_UNDEFINED)
        return "undefined";
    else
    if (t == Ionflux::ObjectBase::STREAM_TYPE_FILE)
        return "file";
        else
    if (t == Ionflux::ObjectBase::STREAM_TYPE_STRING)
        return "string";
    return "<unknown>";
}

std::string getBooleanValueString(bool v)
{
    if (v)
        return "true";
    return "false";
}

}

}

/** \file utils.cpp
 * \brief Utility functions (implementation).
 */
