/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * tools.cpp                  Various tools & helper functions
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

#include <cstring>

#include "ionflux/tools.hpp"
#include "ionflux/File.hpp"
#include "ionflux/RegExp.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

std::string makeHex(const std::string& inputData)
{
	ostringstream buffer;
	buffer << uppercase << right << setfill('0') << hex;
	for (unsigned int i = 0; i < inputData.size(); i++)
		buffer << setw(2) << int(static_cast<unsigned char>(inputData[i]));
	return buffer.str();
}

std::string makeReadable(const std::string& inputData, 
	const std::string& replacement)
{
	ostringstream buffer;
	unsigned char currentChar;
	for (unsigned int i = 0; i < inputData.size(); i++)
	{
		currentChar = static_cast<unsigned char>(inputData[i]);
		if (((currentChar >= 32) && (currentChar <= 126))
			|| (currentChar >= 160))
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
	int bytesPerLine, int groupBytes)
{
	ostringstream buffer;
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
	for (unsigned int i = 0; i < bytes; i++)
	{
		buffer << paddedHex.substr(2 * i, 2) << " ";
		if ((((i + 1) % groupBytes) == 0) && (((i + 1) % bytesPerLine) != 0))
			buffer << " ";
		if (((i + 1) % bytesPerLine) == 0)
		{
			buffer << " " << paddedReadable.substr(readablePos, bytesPerLine) << "\n";
			readablePos += bytesPerLine;
		}
	}
	return buffer.str();
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

void explode(const std::string& bytes, const std::string& splitString, 
	std::vector<std::string>& result)
{
	result.clear();
	if ((bytes == "") || (splitString == ""))
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

void explodeQuoted(const std::string& bytes, std::vector<std::string>& result)
{
	result.clear();
	if (bytes.size() == 0)
		return;
	Tokenizer tok;
	tok.setTokenTypeAnything();
	tok.setInput(bytes);
	tok.setExtractQuoted(true);
	Token currentToken = tok.getNextToken();
	string currentElement;
	while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
		&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
	{
		if (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
		{
			result.push_back(currentElement);
			currentElement = "";
		} else
			currentElement.append(currentToken.value);
		currentToken = tok.getNextToken();
	}
	result.push_back(currentElement);
}

bool isOneOf(char c, const std::string& testChars)
{
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

std::string readFile(const std::string& fileName)
{
	if (fileName == "")
		return "";
	ifstream inputFileStream(fileName.c_str());
	if (!inputFileStream)
	{
		cerr << "[readFile] ERROR: Could not read from file '" 
			<< fileName << "'" << endl;
		return "";
	}
	string inputData;
	char *buffer = new char[READ_BUFFER_SIZE];
	int bytesRead;
	inputFileStream.read(buffer, READ_BUFFER_SIZE);
	bytesRead = inputFileStream.gcount();
	while (bytesRead > 0)
	{
		inputData.append(buffer, bytesRead);
		inputFileStream.read(buffer, READ_BUFFER_SIZE);
		bytesRead = inputFileStream.gcount();
	}
	delete[] buffer;
	return inputData;
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
		cerr << "[writeFile] ERROR: Could not write to file '" 
			<< fileName << "'" << endl;
		return false;
	}
	outputFileStream.write(data.c_str(), data.size());
	// outputFileStream.flush();
	return true;
}

bool bz2Compress(const std::string& inputData, std::string &outputBuffer)
{
	bool success = true;
	outputBuffer = "";
	char *compressBuffer = new char[COMPRESS_BUFFER_SIZE];
	char *inputBuffer = new char[inputData.size()];
	memset(compressBuffer, 0, COMPRESS_BUFFER_SIZE);
	memcpy(inputBuffer, inputData.c_str(), inputData.size());
	int bytes = 0;
	bz_stream bzStream;
	bzStream.bzalloc = 0;
	bzStream.bzfree = 0;
	bzStream.opaque = 0;
	bzStream.next_in = inputBuffer;
	bzStream.avail_in = inputData.size();
	bzStream.next_out = compressBuffer;
	bzStream.avail_out = COMPRESS_BUFFER_SIZE;
	int result = BZ2_bzCompressInit(&bzStream, 9, 0, 30);
	if (result != BZ_OK)
	{
		cerr << "[bz2Compress] ERROR: Initialization failed." << endl;
		return false;
	}
	result = BZ2_bzCompress(&bzStream, BZ_FINISH);
	int passCount = 1;
	while (result == BZ_FINISH_OK)
	{
		bytes = COMPRESS_BUFFER_SIZE - bzStream.avail_out;
		if (bytes > 0)
			outputBuffer.append(compressBuffer, bytes);
		bzStream.avail_out = COMPRESS_BUFFER_SIZE;
		bzStream.next_out = compressBuffer;
		result = BZ2_bzCompress(&bzStream, BZ_FINISH);
		passCount++;
	}
	if (result == BZ_STREAM_END)
	{
		bytes = COMPRESS_BUFFER_SIZE - bzStream.avail_out;
		if (bytes > 0)
			outputBuffer.append(compressBuffer, bytes);
	} else
	{
		cerr << "[bz2Compress] ERROR: Compression failed! (" << result 
			<< ")." << endl;
		success = false;
	}
	BZ2_bzCompressEnd(&bzStream);
	delete[] compressBuffer;
	delete[] inputBuffer;
	return success;
}

bool bz2Decompress(const std::string& inputData, std::string &outputBuffer)
{
	bool success = true;
	outputBuffer = "";
	char *compressBuffer = new char[COMPRESS_BUFFER_SIZE];
	char *inputBuffer = new char[inputData.size()];
	memset(compressBuffer, 0, COMPRESS_BUFFER_SIZE);
	memcpy(inputBuffer, inputData.c_str(), inputData.size());
	int bytes = 0;
	bz_stream bzStream;
	bzStream.bzalloc = 0;
	bzStream.bzfree = 0;
	bzStream.opaque = 0;
	bzStream.next_in = inputBuffer;
	bzStream.next_out = compressBuffer;
	bzStream.avail_in = inputData.size();
	bzStream.avail_out = COMPRESS_BUFFER_SIZE;
	int result = BZ2_bzDecompressInit(&bzStream, 0, 0);
	if (result != BZ_OK)
	{
		cerr << "[bz2Decompress] ERROR: Initialization failed." << endl;
		return false;
	}
	result = BZ2_bzDecompress(&bzStream);
	int passCount = 1;
	while (result == BZ_OK)
	{
		bytes = COMPRESS_BUFFER_SIZE - bzStream.avail_out;
		if (bytes > 0)
			outputBuffer.append(compressBuffer, bytes);
		bzStream.avail_out = COMPRESS_BUFFER_SIZE;
		bzStream.next_out = compressBuffer;
		result = BZ2_bzDecompress(&bzStream);
		passCount++;
	}
	if (result == BZ_STREAM_END)
	{
		bytes = COMPRESS_BUFFER_SIZE - bzStream.avail_out;
		if (bytes > 0)
			outputBuffer.append(compressBuffer, bytes);
	} else
	{
		cerr << "[bz2Decompress] ERROR: Decompression failed! (" << result 
			<< ")." << endl;
		success = false;
	}
	BZ2_bzDecompressEnd(&bzStream);
	delete[] compressBuffer;
	delete[] inputBuffer;
	return success;
}

std::string packInt(int data)
{
	int netData = htonl(data);
	string result;
	unsigned char *intByte = reinterpret_cast<unsigned char *>(&netData);
	for (unsigned int i = 0; i < sizeof(int); i++)
		result.append(1, intByte[i]);
	return result;
}

std::string packDouble(double data)
{
	string result;
	unsigned char *doubleByte = reinterpret_cast<unsigned char *>(&data);
	for (unsigned int i = 0; i < sizeof(double); i++)
		result.append(1, doubleByte[i]);
	return result;
}

std::string packBool(bool data)
{
	string result;
	if (data)
		result.append(1, '\xff');
	else
		result.append(1, '\x00');
	return result;
}

int unpackInt(const std::string &data)
{
	int result;
	unsigned char *intByte = reinterpret_cast<unsigned char *>(&result);
	unsigned int currentByte = 0;
	while ((currentByte < data.size()) && (currentByte < sizeof(int)))
	{
		intByte[currentByte] = data[currentByte];
		currentByte++;
	}
	return ntohl(result);
}

double unpackDouble(const std::string &data)
{
	double result;
	unsigned char *doubleByte = reinterpret_cast<unsigned char *>(&result);
	unsigned int currentByte = 0;
	while ((currentByte < data.size()) && (currentByte < sizeof(double)))
	{
		doubleByte[currentByte] = data[currentByte];
		currentByte++;
	}
	return result;
}

bool unpackBool(const std::string &data)
{
	if ((data.size() < 1) || !data[0])
		return false;
	return true;
}

void socketInit()
{
#ifdef HAVE_WINSOCK
	// Winsock requires special treatment.
	WORD versionRequested;
	WSADATA wsaData;
	versionRequested = MAKEWORD(2, 2);
	WSAStartup(versionRequested, &wsaData);
#endif
}

void daemonize()
{
#ifndef NO_FORK
	int forkResult = fork();
	switch(forkResult)
	{
		case -1:
			cout << "[daemonize] ERROR: fork() failed!" << endl;
			return;
		case 0:
			break;
		default:
			_exit(0);
	}
	if (setsid() == -1)
	{
		cout << "[daemonize] ERROR: setsid() failed!" << endl;
		return;
	}
	forkResult = fork();
	switch(forkResult)
	{
		case -1:
			cout << "[daemonize] ERROR: fork() failed!" << endl;
			return;
		case 0:
			break;
		default:
			_exit(0);
	}
	int fd = open(_PATH_DEVNULL, O_RDWR, 0);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if (fd > 2)
			close(fd);
	}
#endif
}

void socketShutdown()
{
#ifdef HAVE_WINSOCK
	WSACleanup();
#endif
}

std::string parseHex(const std::string &inputData)
{
	int currentByte;
	string result;
	for (unsigned int i = 0; i < (inputData.size() / 2); i++)
	{
		currentByte = strtol(inputData.substr(2 * i, 2).c_str(), 0, 16);
		result.append(1, static_cast<char>(currentByte));
	}
	return result;
}

void getPassword(const std::string &prompt, std::string &password)
{
	cerr << prompt;
	termios oldSettings;
	termios newSettings;
	tcgetattr(0, &oldSettings);
	newSettings = oldSettings;
	newSettings.c_lflag &= (~ECHO);
	tcsetattr(0 ,TCSANOW, &newSettings);
	getline(cin, password);
	tcsetattr(0 ,TCSANOW, &oldSettings);
	cerr << endl;
}

void getRandomBytes(std::string &bytes, unsigned int n, MTRand *source)
{
	bytes = "";
	bool manage = false;
	if (source == 0)
	{
		source = new MTRand(time(0));
		manage = true;
	}
	for (unsigned int i = 0; i < n; i++)
		bytes.append(1, static_cast<char>(source->randInt(255)));
	if (manage)
		delete source;
}

void getRandomIdentifier(std::string &bytes, unsigned int n, MTRand *source)
{
	string identifierChars = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
	unsigned int numChars = identifierChars.size();
	bytes = "";
	bool manage = false;
	if (source == 0)
	{
		source = new MTRand(time(0));
		manage = true;
	}
	for (unsigned int i = 0; i < n; i++)
		bytes.append(1, identifierChars[source->randInt(numChars - 1)]);
	if (manage)
		delete source;
}

bool readDir(const std::string &dirName, std::vector<std::string> &target, 
	bool prependDirName, bool recursive)
{
	if (dirName.size() == 0)
		return false;
	DIR *currentDir = opendir(dirName.c_str());
	if (currentDir == 0)
		return false;
	target.clear();
	dirent *currentEntry;
	string entryName;
	string fullPathName;
	string prependName = dirName;
	vector<string> currentDirEntries;
	if (dirName[dirName.size() - 1] != DIR_SEPARATOR)
		prependName.append(1, DIR_SEPARATOR);
	while ((currentEntry = readdir(currentDir)) != 0)
	{
		entryName = currentEntry->d_name;
		if ((entryName != ".") && (entryName != ".."))
		{
			fullPathName = prependName + entryName;
			if (prependDirName)
				target.push_back(fullPathName);
			else
				target.push_back(entryName);
			if (recursive)
			{
				currentDirEntries.clear();
				readDir(fullPathName, currentDirEntries, prependDirName, 
					recursive);
				for (unsigned int i = 0; i < currentDirEntries.size(); i++)
					target.push_back(currentDirEntries[i]);
			}
		}
	}
	closedir(currentDir);
	return true;
}

bool getFileList(const std::vector<std::string>& pathList, 
	std::vector<std::string>& target, bool recursive, 
	const std::string& filterExpr)
{
	File currentFile;
	vector<string> currentDirFiles;
	RegExp* re = 0;
	if (filterExpr.size() > 0)
		re = new RegExp(filterExpr);
	for (unsigned int i = 0; i < pathList.size(); i++)
	{
		currentFile.setFullName(pathList[i]);
		if (currentFile.isDir())
		{
			/* ----- DEBUG ----- //
			cerr << "[getFileList] DEBUG: "
				"Checking for input files in directory '" 
				<< currentFile.getFullName() << "' ..." << endl;
			// ----- DEBUG ----- */
			readDir(currentFile.getFullName(), currentDirFiles, true, false);
			for (unsigned int k = 0; k < currentDirFiles.size(); k++)
			{
				currentFile.setFullName(currentDirFiles[k]);
				if (recursive 
					&& currentFile.isDir())
				{
					vector<string> currentDirPathList;
					currentDirPathList.push_back(currentDirFiles[k]);
					getFileList(currentDirPathList, target, recursive, 
						filterExpr);
				} else
				if (!currentFile.isDir())
				{
					if ((re == 0)
						|| (re->match(currentFile.getName())))
					{
						/* ----- DEBUG ----- //
						cerr << "[getFileList] DEBUG: "
							"Adding file '" << currentDirFiles[k] << "'." 
							<< endl;
						// ----- DEBUG ----- */
						target.push_back(currentDirFiles[k]);
					}
				}
			}
		} else
		{
			if ((re == 0)
				|| (re->match(currentFile.getName())))
			{
				/* ----- DEBUG ----- //
				cerr << "[getFileList] DEBUG: "
					"Adding file '" << currentFile.getFullName() << "'." 
					<< endl;
				// ----- DEBUG ----- */
				target.push_back(currentFile.getFullName());
			}
		}
	}
	if (re != 0)
		delete re;
	return true;
}

std::string getCurrentDir()
{
	int bufferSize = DIR_BUFFER_SIZE;
	char *buf = new char[bufferSize];
	string result;
	char *success = 0;
	while (((success = getcwd(buf, bufferSize)) == 0) 
		&& (bufferSize < DIR_BUFFER_SIZE_MAX))
	{
		delete buf;
		bufferSize *= 2;
		buf = new char[bufferSize];
	}
	if (success != 0)
		result = buf;
	delete buf;
	return result;
}

int getOpPrecedence(const std::string &op, bool unary)
{
	int result = -1;
	if ((op == "++") || (op == "--") || (op == "~") || (op == "!")
		|| (unary && ((op == "+") || (op == "-"))))
		return 10;
	else
	if ((op == "*") || (op == "/") || (op == "%"))
		return 9;
	else
	if ((op == "+") || (op == "-"))
		return 8;
	else
	if ((op == "<<") || (op == ">>"))
		return 7;
	else
	if ((op == "<") || (op == "<=") || (op == ">") || (op == ">="))
		return 6;
	else
	if ((op == "==") || (op == "!="))
		return 5;
	else
	if (op == "&")
		return 4;
	else
	if (op == "^")
		return 3;
	else
	if (op == "|")
		return 2;
	else
	if (op == "&&")
		return 1;
	else
	if (op == "||")
		return 0;
	return result;
}

std::string escape(const std::string &source, const std::string& escapeWhat)
{
	if (source.size() == 0)
		return "";
	string result;
	for (unsigned int i = 0; i < source.size(); i++)
	{
		if (isOneOf(source[i], escapeWhat))
			result.append(1, '\\');
		result.append(1, source[i]);
	}
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

bool toBool(const std::string &text)
{
	string input = toLower(text);
	if ((input == "true") || (input == "yes") || (input == "on"))
		return true;
	return false;
}

unsigned int utf8GetSize(unsigned char byte)
{
	// Somewhat inspired by GLib's gutf8.c. ;-)
	if (byte < 128)
		return 1;
	else
	if ((byte & 0xe0) == 0xc0)
		return 2;
	else
	if ((byte & 0xf0) == 0xe0)
		return 3;
	else
	if ((byte & 0xf8) == 0xf0)
		return 4;
	else
	if ((byte & 0xfc) == 0xf8)
		return 5;
	else
	if ((byte & 0xfe) == 0xfc)
		return 6;
	// ----- DEBUG ----- //
	cerr << "[utf8GetSize] DEBUG: Invalid character size." << endl;
	// ----- DEBUG ----- */
	return 0;
}

unsigned int utf8GetSize(const std::string& bytes)
{
	unsigned int size = bytes.size();
	unsigned int i = 0;
	unsigned int charLen = 0;
	unsigned int result = 0;
	bool error = false;
	while (!error && (i < size))
	{
		charLen = utf8GetSize(bytes[i]);
		if (charLen > 0)
		{
			result++;
			i += charLen;
		} else
			error = true;
	}
	if (error)
		return 0;
	return result;
}

bool utf8ToUInt(const std::string& bytes, unsigned int& target)
{
	unsigned int size = bytes.size();
	target = 0;
	bool result = true;
	if (size == 1)
	{
		if ((bytes[0] >> 7) != 0)
		{
			// ----- DEBUG ----- //
			cerr << "[utf8ToUInt] DEBUG: Invalid single-byte character."
				<< endl;
			// ----- DEBUG ----- */
			result = false;
		} else
			target = bytes[0];
	} else
	{
		unsigned char byte = bytes[0];
		target = ((byte & (0xff >> (size + 1))) << (6 * (size - 1)));
		unsigned int i = 1;
		while (result && (i < size))
		{
			byte = bytes[i];
			if ((byte >> 6) != 2)
			{
				// ----- DEBUG ----- //
				cerr << "[utf8ToUInt] DEBUG: Invalid byte (" 
					<< static_cast<unsigned int>(byte) 
					<< ") in UTF-8 sequence at position " << i << "."
					<< endl;
				// ----- DEBUG ----- */
				result = false;
			} else
				target |= ((byte & 0x3f) << (6 * (size - 1 - i)));
			i++;
		}
	}
	return result;
}

bool utf8ToUInt(const std::string& bytes, std::vector<unsigned int>& target)
{
	unsigned int size = bytes.size();
	unsigned int i = 0;
	unsigned int charSize = 0;
	unsigned int currentChar = 0;
	bool result = true;
	target.clear();
	while (result && (i < size))
	{
		charSize = utf8GetSize(bytes[i]);
		if ((charSize > 0) 
			&& ((i + charSize) <= size)
			&& utf8ToUInt(bytes.substr(i, charSize), currentChar))
			i += charSize;
		else
		{
			// ----- DEBUG ----- //
			cerr << "[utf8ToUInt] DEBUG: Could not convert UTF-8 character "
				"(size = " << charSize << ", position = " << i << ")." 
				<< endl;
			// ----- DEBUG ----- */
			result = false;
		}
		if (result)
			target.push_back(currentChar);
	}
	return result;
}

std::string uintToUtf8(unsigned int uniChar)
{
	string result;
	if (uniChar < 128U)
		result.append(1, static_cast<unsigned char>(uniChar));
	else
	if (uniChar < 2048U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 6) | 0xc0));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
	if (uniChar < 65536U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 12) | 0xe0));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
	if (uniChar < 2097152U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 18) | 0xf0));
		result.append(1, static_cast<unsigned char>(((uniChar >> 12) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
	if (uniChar < 67108864U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 24) | 0xf8));
		result.append(1, static_cast<unsigned char>(((uniChar >> 18) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 12) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) 
			| 0x80));
	} else
	if (uniChar < 2147483648U)
	{
		result.append(1, static_cast<unsigned char>((uniChar >> 30) | 0xfc));
		result.append(1, static_cast<unsigned char>(((uniChar >> 24) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 18) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 12) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>(((uniChar >> 6) & 0x3f) 
			| 0x80));
		result.append(1, static_cast<unsigned char>((uniChar & 0x3f) | 0x80));
	} else
		cerr << "[uintToUtf8] WARNING: Character not representable by UTF-8." 
			<< endl;
	return result;
}

void uintToUtf8(const std::vector<unsigned int>& uniChars, 
	std::string& target)
{
	target = "";
	for (unsigned int i = 0; i < uniChars.size(); i++)
		target.append(uintToUtf8(uniChars[i]));
}

std::string utf8Trim(const std::string& bytes, bool leftTrim, bool rightTrim)
{
	if (bytes.size() == 0)
		return "";
	vector<unsigned int> utfChars;
	if (!utf8ToUInt(bytes, utfChars))
		return "";
	unsigned int from = 0;
	unsigned int to = utfChars.size() - 1;
	static const unsigned int trimChars[] = { 0x9, 0x20, 0xa0, 0x0a, 0x0d };
	if (leftTrim)
		while ((from <= to)
			&& ((utfChars[from] == trimChars[0])
				|| (utfChars[from] == trimChars[1])
				|| (utfChars[from] == trimChars[2])))
			from++;
	if (rightTrim)
		while ((to >= from)
			&& ((utfChars[to] == trimChars[0])
				|| (utfChars[to] == trimChars[1])
				|| (utfChars[to] == trimChars[2])))
			to--;
	vector<unsigned int> utfCharsOut;
	for (unsigned int i = from; i <= to; i++)
		utfCharsOut.push_back(utfChars[i]);
	string result;
	uintToUtf8(utfCharsOut, result);
	return result;
}

bool utf8IsOneOf(unsigned int c, const std::string& testChars)
{
	if (testChars.size() == 0)
		return false;
	vector<unsigned int> uniChars;
	if (!utf8ToUInt(testChars, uniChars))
		return false;
	bool found = false;
	unsigned int i = 0;
	while (!found
		&& (i < uniChars.size()))
	{
		if (uniChars[i] == c)
			found = true;
		i++;
	}
	return found;
}

bool utf8IsOneOf(unsigned int c, const std::vector<unsigned int>& testChars)
{
	if (testChars.size() == 0)
		return false;
	bool found = false;
	unsigned int i = 0;
	while (!found
		&& (i < testChars.size()))
	{
		if (testChars[i] == c)
			found = true;
		i++;
	}
	return found;
}

std::string utf8Escape(const std::string& source)
{
	vector<unsigned int> uniChars;
	if (!utf8ToUInt(source, uniChars))
		return "";
	ostringstream result;
	unsigned int c = 0;
	for (unsigned int i = 0; i < uniChars.size(); i++)
	{
		c = uniChars[i];
		if (c <= 127L)
			result << static_cast<unsigned char>(c);
		else
		if (c <= 65535L)
			result << "\\u" << setw(4) << setfill('0') << right << hex << c;
		else
			result << "\\U" << setw(8) << setfill('0') << right << hex << c;
	}
	return result.str();
}

std::string utf8Unescape(const std::string& source)
{
	unsigned int numChars = source.size();
	unsigned int i = 0;
	unsigned char c = 0;
	static const char ESCAPE_CHAR = '\\';
	static const std::string OCTAL_NUMBERS = "01234567";
	static const std::string HEX_NUMBERS = "0123456789ABCDEFabcdef";
	ostringstream result;
	ostringstream state;
	while (i < numChars)
	{
		c = source[i];
		if ((c != ESCAPE_CHAR) && (c <= 127))
			// Append ASCII character.
			result << c;
		else
		if (c == ESCAPE_CHAR)
		{
			// Escape character found, look at next character.
			i++;
			if (i < numChars)
			{
				c = source[i];
				// Handle single-character escape sequences.
				if (c == 'n')
					result << '\n';
				else
				if (c == 't')
					result << '\t';
				else
				if (c == 'v')
					result << '\v';
				else
				if (c == 'b')
					result << '\b';
				else
				if (c == 'r')
					result << '\r';
				else
				if (c == 'f')
					result << '\f';
				else
				if (c == 'a')
					result << '\a';
				else
				if (c == '\\')
					result << '\\';
				else
				if (c == '?')
					result << '?';
				else
				if (c == '\'')
					result << '\'';
				else
				if (c == '"')
					result << '"';
				else
				if (isOneOf(c, OCTAL_NUMBERS))
				{
					// Octal escape sequence.
					state.str("");
					int count = 0;
					while ((i < numChars)
						&& (count < 3)
						&& (isOneOf(c, OCTAL_NUMBERS)))
					{
						state << c;
						count++;
						i++;
						if (i < numChars)
							c = source[i];
					}
					result << uintToUtf8(strtol(state.str().c_str(), 0, 8));
					i--;
				} else
				if (c == 'x')
				{
					// Hexadecimal escape sequence.
					state.str("");
					i++;
					if (i < numChars)
						c = source[i];
					while ((i < numChars)
						&& (isOneOf(c, HEX_NUMBERS)))
					{
						state << c;
						i++;
						if (i < numChars)
							c = source[i];
					}
					result << uintToUtf8(
						strtol(state.str().c_str(), 0, 16));
					i--;
				} else
				if ((c == 'u') || (c == 'U'))
				{
					// Unicode escape sequence.
					state.str("");
					int count = 0;
					int targetCount = 4;
					if (c == 'U')
						targetCount = 8;
					i++;
					if (i < numChars)
						c = source[i];
					while ((i < numChars)
						&& (isOneOf(c, HEX_NUMBERS)))
					{
						state << c;
						i++;
						count++;
						if (i < numChars)
							c = source[i];
					}
					if (count == targetCount)
						result << uintToUtf8(
							strtol(state.str().c_str(), 0, 16));
					i--;
				} else
					// Unknown escape sequence.
					result << c;
			}
		}
		i++;
	}
	return result.str();
}

std::string quote(const std::string& source, const unsigned char quoteChar)
{
	ostringstream result;
	result << quoteChar << source << quoteChar;
	return result.str();
}

std::string unquote(const std::string& source, 
	const std::string& addQuoteChars)
{
	if ((source.size() < 2)
		|| (source[0] != source[source.size() - 1]))
		// String is not quoted.
		return source;
	string quoteChars = "'\"";
	if (addQuoteChars.size() > 0)
		quoteChars.append(addQuoteChars);
	if (!isOneOf(source[0], quoteChars))
		// Unknown quotes.
		return source;
	if (source.size() == 2)
		return "";
	return source.substr(1, source.size() - 2);
}

std::string trim(const std::string& bytes, bool leftTrim, bool rightTrim)
{
	if (bytes.size() == 0)
		return "";
	unsigned int from = 0;
	unsigned int to = bytes.size() - 1;
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
	for (unsigned int i = from; i <= to; i++)
		result.append(1, bytes[i]);
	return result;
}

const CharTypeMap& getCharTypes()
{
	static CharTypeMap charTypes;
	return charTypes;
}

std::string urlEncode(const std::string& bytes)
{
	const CharTypeMap& charTypes = getCharTypes();
	string result;
	unsigned char c;
	TokenType charType;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
		c = bytes[i];
		charType = charTypes.getTokenType(c);
		if ((charType.typeID == Tokenizer::TT_NUMBER.typeID)
			|| (charType.typeID == Tokenizer::TT_ALPHA.typeID)
			|| (charType.typeID == Tokenizer::TT_DEFAULT_SEP.typeID))
			result.append(1, c);
		else
		if (c == ' ')
			result.append(1, '+');
		else
		{
			result.append(1, '%');
			result.append(toUpper(makeHex(bytes.substr(i, 1))));
		}
	}
	return result;
}

std::string urlDecode(const std::string& bytes)
{
	string result;
	unsigned char c;
	unsigned int i = 0;
	while (i < bytes.size())
	{
		c = bytes[i];
		if (c == '+')
			result.append(1, ' ');
		else
		if ((c == '%') 
			&& ((i + 2) < bytes.size()))
		{
			result.append(parseHex(bytes.substr(i + 1, 2)));
			i += 2;
		}
		else
			result.append(1, c);
		i++;
	}
	return result;
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

bool validatePath(const std::string& path, int mask)
{
	if (path.size() == 0)
		return false;
	vector<string> parts;
	explode(path, string(1, DIR_SEPARATOR), parts);
	bool result = true;
	unsigned int i = 0;
	File file;
	string thePath;
	if (path[0] == DIR_SEPARATOR)
		thePath.append(1, DIR_SEPARATOR);
	while (result && (i < parts.size()))
	{
		thePath.append(parts[i]);
		/* ---- DEBUG ---- //
		cerr << "[validatePath] DEBUG: Checking directory: '"
			<< thePath << "'." << endl;
		// ---- DEBUG ---- */
		file.setFullName(thePath);
		if (!file.isDir() && (mkdir(thePath.c_str(), mask) != 0))
		{
			cerr << "[validatePath] ERROR: "
				"Could not create directory: " << thePath << endl;
			result = false;
		}
		thePath = appendDirSeparator(thePath);
		i++;
	}
	return result;
}

std::string xmlEscape(const std::string& bytes)
{
	string result;
	char byte;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
		byte = bytes[i];
		if (byte == '<')
			result.append("&lt;");
		else
		if (byte == '>')
			result.append("&gt;");
		else
		if (byte == '&')
			result.append("&amp;");
		else
		if (byte == '"')
			result.append("&quot;");
		else
		if (byte == '\'')
			result.append("&apos;");
		else
			result.append(1, byte);
	}
	return result;
}

MTRand& getRandomizer()
{
	static MTRand randomizer(time(0));
	return randomizer;
}

}

}

/** \file tools.cpp
 * \brief Various tools & helper functions implementation.
 */
