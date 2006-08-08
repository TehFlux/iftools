/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Message.cpp                    Network message.
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

#include "ionflux/Message.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const std::string Message::DEFAULT_MAGIC_WORD = "IFTM";
const int Message::DEFAULT_PROTOCOL_VERSION = 0;
const int Message::UID_NOT_SET = -1;
const int Message::TYPE_NOT_SET = -1;
const int Message::FLAG_COMPRESS = 1;
const int Message::HEADER_SIZE = 40;
const unsigned int Message::DEFAULT_MAX_SIZE = 10485760L;

Message::Message()
: magicWord(DEFAULT_MAGIC_WORD), protocolVersion(DEFAULT_PROTOCOL_VERSION), 
  protocolVersionLower(DEFAULT_PROTOCOL_VERSION), 
  protocolVersionUpper(DEFAULT_PROTOCOL_VERSION), 
  uid(UID_NOT_SET), type(TYPE_NOT_SET), flags(0), size(0), checksum(""),
  username(""), userSecret(""), sessionSecret(""), serialized(""), target(0),
  maxSize(DEFAULT_MAX_SIZE)
{
	root.node->setAutoCreate(true);
	root.node->setIndexMode(Node::INDEX_MODE_NODE);
}

Message::~Message()
{
	clearAll();
}

void Message::clearData()
{
	uid = UID_NOT_SET;
	type = TYPE_NOT_SET;
	flags = 0;
	size = 0;
	checksum = "";
	serialized = "";
	clear();
}

void Message::clearAll()
{
	clearData();
	magicWord = DEFAULT_MAGIC_WORD;
	protocolVersion = DEFAULT_PROTOCOL_VERSION;
	protocolVersionUpper = DEFAULT_PROTOCOL_VERSION;
	protocolVersionLower = DEFAULT_PROTOCOL_VERSION;
	for (unsigned int i = 0; i < username.size(); i++)
		username[i] = '\0';
	username = "";
	for (unsigned int i = 0; i < userSecret.size(); i++)
		userSecret[i] = '\0';
	userSecret = "";
	for (unsigned int i = 0; i < sessionSecret.size(); i++)
		sessionSecret[i] = '\0';
	sessionSecret = "";
}

void Message::serialize(std::string &buffer)
{
	ostringstream status;
	buffer = "";
	buffer.append(magicWord);
	buffer.append(packInt(protocolVersion));
	buffer.append(4, '\0');
	buffer.append(packInt(uid));
	buffer.append(packInt(type));
	buffer.append(packInt(flags));
	buffer.append(20, '\0');
	string data;
	if (!log.assert(root.node != 0, 
			"[Message::serialize] Root node is null."))
		return;
	root.node->serialize(data);
	if ((flags & FLAG_COMPRESS) != 0)
	{
		string compressedData;
		bz2Compress(data, compressedData);
		buffer.append(compressedData);
	} else
		buffer.append(data);
	size = buffer.size();
	buffer.replace(magicWord.size() + 4, 4, packInt(size));
	string secrets = username + userSecret + sessionSecret;
	checksum = sha1(buffer + secrets);
	for (unsigned int i = 0; i < secrets.size(); i++)
		secrets[i] = '\0';
	buffer.replace(magicWord.size() + 20, 20, checksum);
}

bool Message::unpack()
{
	ostringstream status;
	if ((serialized.size() == 0) || (size == 0))
	{
		log.msg("[Message::unpack] ERROR: Cannot unpack message: "
			"Message data buffer is empty, or message has zero size.",
			log.VL_ERROR);
		return false;
	}
	if (serialized.size() < size)
	{
		status.str("");
		status << "[Message::unpack] ERROR: Cannot unpack message: " 
			<< getNumBytesMissing() << " bytes missing.";
		log.msg(status.str(), log.VL_ERROR);
		return false;
	}
	if (size < (magicWord.size() + HEADER_SIZE))
	{
		status.str("");
		status << "[Message::unpack] ERROR: Cannot unpack message: " 
			"Message size less than header size (message size: " << size 
			<< ", header size: " << (magicWord.size() + HEADER_SIZE) << ", "
			"magic word size: " << magicWord.size() << ").";
		log.msg(status.str(), log.VL_ERROR);
		return false;
	}
	status.str("");
	status << "[Message::unpack] DEBUG: magicWord = " 
		<< makeReadable(magicWord, ".") << "/" << makeHex(magicWord);
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	status.str("");
	status << "[Message::unpack] DEBUG: protocolVersion = " 
		<< protocolVersion;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	status.str("");
	status << "[Message::unpack] DEBUG: size = " << size;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	unsigned int currentPos = magicWord.size() + 8;
	// Extract UID.
	uid = unpackInt(serialized.substr(currentPos, 4));
	status.str("");
	status << "[Message::unpack] DEBUG: UID = " << uid;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	currentPos += 4;
	// Extract message type ID.
	type = unpackInt(serialized.substr(currentPos, 4));
	status.str("");
	status << "[Message::unpack] DEBUG: type = " << type;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	currentPos += 4;
	// Extract flags.
	flags = unpackInt(serialized.substr(currentPos, 4));
	status.str("");
	status << "[Message::unpack] DEBUG: flags = " << flags;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	currentPos += 4;
	// Extract checksum.
	checksum = serialized.substr(currentPos, 20);
	string checksumZero(20, '\0');
	serialized.replace(currentPos, 20, checksumZero);
	status.str("");
	status << "[Message::unpack] DEBUG: checksum = " << makeHex(checksum);
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	currentPos += 20;
	// Verify checksum.
	string secrets = username + userSecret + sessionSecret;
	string calculatedChecksum = sha1(serialized.substr(0, size) + secrets);
	if (calculatedChecksum == checksum)
		log.msg("[Message::unpack] DEBUG: Checksum OK. :-)", 
			log.VL_DEBUG_INSANE);
	else
	{
		status.str("");
		status << "[Message::unpack] WARNING: Cannot unpack message: " 
			"Checksum error. (calculated checksum: " 
			<< makeHex(calculatedChecksum) << ").";
		log.msg(status.str(), log.VL_WARNING);
		return false;
	}
	// Extract data.
	unsigned int dataSize = size - magicWord.size() - HEADER_SIZE;
	string data = serialized.substr(currentPos, dataSize);
	for (unsigned int i = 0; i < secrets.size(); i++)
		secrets[i] = '\0';
	bool unpackResult = false;
	if (!log.assert(root.node != 0, "[Message::unpack] Root node is null."))
		return false;
	if ((flags & FLAG_COMPRESS) != 0)
	{
		string decompressedData;
		if (!bz2Decompress(data, decompressedData))
		{
			log.msg("[Message::unpack] WARNING: Data decompression failed.", 
				log.VL_WARNING);
			return false;
		}
		unpackResult = root.node->unpack(decompressedData, 0, 
			decompressedData.size());
	} else
		unpackResult = root.node->unpack(data, 0, data.size());
	if (!unpackResult)
	{
		log.msg("[Message::unpack] WARNING: Data unpacking failed.", 
			log.VL_WARNING);
		return false;
	}
	if (target != 0)
		target->dump(*this);
	return true;
}

bool Message::append(const std::string& bytes)
{
	ostringstream status;
	serialized.append(bytes);
	unsigned int bytesAvailable = serialized.size();
	unsigned int processed = 0;
	while (processed < bytesAvailable)
	{
		if (serialized.size() >= magicWord.size())
		{
			/// Check magic word.
			string testMagicWord = serialized.substr(0, magicWord.size());
			if (testMagicWord != magicWord)
			{
				status.str("");
				status << "[Message::append] WARNING: Received invalid "
					"message data: Magic word does not match. (magic word: " 
					<< makeReadable(magicWord, ".") << "/" 
					<< makeHex(magicWord) << ", found: " 
					<< makeReadable(testMagicWord, ".") << "/"
					<< makeHex(testMagicWord) << ").";
				log.msg(status.str(), log.VL_WARNING);
				serialized = "";
				return false;
			}
		}
		if (serialized.size() >= (magicWord.size() + 4))
		{
			/// Check protocol version.
			protocolVersion = unpackInt(serialized.substr(
				magicWord.size(), 4));
			if ((protocolVersion < protocolVersionLower) 
				|| (protocolVersion > protocolVersionUpper))
			{
				status.str("");
				status << "[Message::append] WARNING: Received invalid "
					"message data: Protocol version not in acceptable range. "
					"(acceptable: " << protocolVersionLower << "/" 
					<< protocolVersionUpper << ", found: " << protocolVersion 
					<< ").";
				log.msg(status.str(), log.VL_WARNING);
				serialized = "";
				return false;
			}
		}
		if (serialized.size() >= (magicWord.size() + 8))
		{
			/// Extract size.
			size = unpackInt(serialized.substr(magicWord.size() + 4, 4));
			if (size > maxSize)
			{
				status.str("");
				status << "[Message::append] WARNING: Received invalid "
					"message data: Message too large. (maximum size: " 
					<< maxSize << ", message size: " << size << ").";
				log.msg(status.str(), log.VL_WARNING);
				serialized = "";
				size = 0;
				return false;
			}
		}
		if ((size != 0) && (serialized.size() >= size) 
			&& (size >= (magicWord.size() + HEADER_SIZE)))
		{
			/// Unpack message.
			if (!unpack())
			{
				log.msg("[Message::append] WARNING: Could not unpack "
					"message.", log.VL_WARNING);
				serialized = "";
				size = 0;
				return false;
			}
			processed += size;
			if (serialized.size() > size)
				serialized.erase(0, size);
			else
				serialized = "";
			size = 0;
		} else
			processed = bytesAvailable;
	}
	return true;
}

void Message::dump(const std::string& bytes)
{
	append(bytes);
}

void Message::setMagicWord(const std::string &newMagicWord)
{
	magicWord = newMagicWord;
}

void Message::setProtocolVersion(int newProtocolVersion)
{
	protocolVersion = newProtocolVersion;
}

void Message::setAcceptableProtocolVersion(int newProtocolVersionLower, 
	int newProtocolVersionUpper)
{
	protocolVersionLower = newProtocolVersionLower;
	protocolVersionUpper = newProtocolVersionUpper;
}

void Message::setUID(int newUID)
{
	uid = newUID;
}

void Message::setType(int newType)
{
	type = newType;
}

void Message::setFlags(unsigned int newFlags)
{
	flags = newFlags;
}

void Message::setUsername(const std::string &newUsername)
{
	username = newUsername;
}

void Message::setUserSecret(const std::string &newUserSecret)
{
	userSecret = newUserSecret;
}

void Message::setSessionSecret(const std::string &newSessionSecret)
{
	sessionSecret = newSessionSecret;
}

void Message::setTarget(MessageDump *newTarget)
{
	target = newTarget;
}

void Message::setMaxSize(unsigned int newMaxSize)
{
	maxSize = newMaxSize;
}

std::string Message::getMagicWord()
{
	return magicWord;
}

int Message::getProtocolVersion()
{
	return protocolVersion;
}

int Message::getUID()
{
	return uid;
}

int Message::getType()
{
	return type;
}

unsigned int Message::getFlags()
{
	return flags;
}

unsigned int Message::getSize()
{
	return size;
}

std::string Message::getUsername()
{
	return username;
}

void Message::getUserSecret(std::string &userSecretBuffer)
{
	userSecretBuffer = userSecret;
}

void Message::getSessionSecret(std::string &sessionSecretBuffer)
{
	sessionSecretBuffer = sessionSecret;
}

unsigned int Message::getNumBytesMissing()
{
	return size - serialized.size();
}

unsigned int Message::getMaxSize()
{
	return maxSize;
}

}

}

/** \file Message.cpp
 * \brief Network message implementation.
 */
