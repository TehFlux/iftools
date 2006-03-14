#ifndef IONFLUX_TOOLS_MESSAGE
#define IONFLUX_TOOLS_MESSAGE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Message.hpp                    Network message.
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

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "ionflux/tools.hpp"
#include "ionflux/Reporter.hpp"
#include "ionflux/Tree.hpp"
#include "ionflux/MessageDump.hpp"

namespace Ionflux
{

namespace Tools
{

class MessageDump;

/** Message.
 * \ingroup network
 *
 * A message which can encapsulate and serialize arbitrary data, to be sent 
 * over a network supporting byte streams or packets. Facilities are provided 
 * for integrity verification, compression and simple message authentication.
 *
 * To create a serialized message, initialize the message as necessary, then 
 * call Message::serialize().
 *
 * To create messages out of a stream of serialized messages, set a handler 
 * with Message::setTarget(), then pass bytes from the stream to 
 * Message::dump(). The handler will be called whenever a complete message has 
 * arrived and has been parsed successfully.
 *
 * Simple authentication on a per-message basis will be performed if you set 
 * the username, user secret and session secret to non-empty values. All of 
 * these fields are optional; however, for authentication to succeed, the 
 * fields must be set to the same values for the sender and receiver of a 
 * message.
 */
class Message
: public Tree
{
	protected:
		/// Magic word.
		std::string magicWord;
		/// Protocol version.
		int protocolVersion;
		/// Acceptable protocol version range: lower boundary.
		int protocolVersionLower;
		/// Acceptable protocol version range: upper boundary.
		int protocolVersionUpper;
		/// Message UID.
		int uid;
		/// Message type.
		int type;
		/// Message flags.
		unsigned int flags;
		/// Size of serialized message.
		unsigned int size;
		/// Checksum buffer.
		std::string checksum;
		/// Username (used for authentication).
		std::string username;
		/// User secret (used for authentication).
		std::string userSecret;
		/// Session secret (used for authentication).
		std::string sessionSecret;
		/// Serialization buffer.
		std::string serialized;
		/// Target for completed messages.
		MessageDump *target;
		/// Maximum size.
		unsigned int maxSize;
		
		/** Unpack message.
		 *
		 * Unpack a message from the data stored in the serialization buffer.
		 *
		 * \return \c true on success, \c false if the message could not be 
		 * unpacked.
		 */
		virtual bool unpack();
		
	public:
		/// Default magic word.
		static const std::string DEFAULT_MAGIC_WORD;
		/// Default protocol version.
		static const int DEFAULT_PROTOCOL_VERSION;
		/// UID: Not set.
		static const int UID_NOT_SET;
		/// Type: Not set.
		static const int TYPE_NOT_SET;
		/// Flag: Compress message.
		static const int FLAG_COMPRESS;
		/// Message header size (excluding the magic word).
		static const int HEADER_SIZE;
		/// Default maximum message size.
		static const unsigned int DEFAULT_MAX_SIZE;
		
		/** Constructor.
		 *
		 * Construct new Message object.
		 */
		Message();
		
		/** Destructor.
		 *
		 * Destruct Message object.
		 */
		virtual ~Message();
		
		/** Clear data.
		 *
		 * Clears internal data of this message. Persistent properties, such 
		 * as the magic word, protocol version and user/session data will not 
		 * be reset.
		 *
		 * \sa clearAll()
		 */
		virtual void clearData();
		
		/** Clear everything.
		 *
		 * Clears all internal state, including otherwise persistent 
		 * properties.
		 *
		 * \sa clearData()
		 */
		virtual void clearAll();
		
		/** Serialize.
		 *
		 * Serialize the message. The result will be ready to be sent over a 
		 * network and may be re-assembled into a message object using dump().
		 *
		 * \param buffer Where to store the serialized message.
		 *
		 * \sa dump(), append()
		 */
		virtual void serialize(std::string &buffer);
		
		/** Append bytes.
		 *
		 * Pass a string of bytes to be processed as part of a serialized 
		 * message.
		 *
		 * \param bytes The bytes to be appended.
		 *
		 * \return \c true if the bytes could be processed as part of a valid 
		 * message, \c false if an error occured.
		 *
		 * \sa serialize(), dump()
		 */
		virtual bool append(const std::string& bytes);
		
		/** Dump bytes.
		 *
		 * Pass a string of bytes to be processed as part of a serialized 
		 * message.
		 *
		 * \note If you need information on whether the dumped bytes are part 
		 * of a valid message, you should use append() instead.
		 *
		 * \param bytes The bytes to be dumped.
		 *
		 * \sa serialize(), append()
		 */
		virtual void dump(const std::string& bytes);
		
		/** Set magic word.
		 *
		 * Sets the magic word. This should be a short string (2-4 bytes) 
		 * specific to your protocol. It will be used to determine ad-hoc 
		 * whether incoming data might be part of a valid message.
		 *
		 * \param newMagicWord The magic word.
		 */
		virtual void setMagicWord(const std::string &newMagicWord);
		
		/** Set protocol version number.
		 *
		 * Sets the protocol version number. Incoming data will be accepted 
		 * only if the protocol version number is contained within the range 
		 * of acceptable protocol version numbers.
		 *
		 * \param newProtocolVersion Protocol version.
		 *
		 * \sa setAcceptableProtocolVersion()
		 */
		virtual void setProtocolVersion(int newProtocolVersion);
		
		/** Set acceptable protocol version number range.
		 *
		 * Sets the upper and lower limit of acceptable protocol version 
		 * numbers for creating messages from a stream of serialized messages. 
		 * If messages arrive that have version numbers outside the specified 
		 * range, they will be ignored. Messages with acceptable version 
		 * numbers will be parsed and passed to the handler on completion.
		 *
		 * \param newProtocolVersionLower Lower boundary of acceptable version 
		 * number range.
		 * \param newProtocolVersionUpper Upper boundary of acceptable version 
		 * number range.
		 *
		 * \sa setProtocolVersion(), dump(), setTarget()
		 */
		virtual void setAcceptableProtocolVersion(int newProtocolVersionLower, 
			int newProtocolVersionUpper);
		
		/** Set UID.
		 *
		 * Set the UID of his message. This should be a number unique to a 
		 * session or connection.
		 *
		 * \param newUID Message UID.
		 */
		virtual void setUID(int newUID);
		
		/** Set message type.
		 *
		 * Set the numerical type ID of the message. This makes sense only if 
		 * your protocol distingusihes several different message types. You 
		 * may also use this for error message codes.
		 *
		 * \param newType Message type ID.
		 */
		virtual void setType(int newType);
		
		/** Set flags.
		 *
		 * Set additional flags to be sent along with the message. It is 
		 * possible to combine several flags using the "|" (OR) operator.
		 *
		 * Note: Set Message::FLAG_COMPRESS to compress message data using 
		 * bzip2.
		 *
		 * \param newFlags Flags.
		 */
		virtual void setFlags(unsigned int newFlags);
		
		/** Set username.
		 *
		 * Set the username to be used for message authentication.
		 *
		 * \param newUsername Username.
		 */
		virtual void setUsername(const std::string &newUsername);
		
		/** Set user secret.
		 *
		 * Set the user secret to be used for message authentication.
		 *
		 * \param newUserSecret User secret.
		 */
		virtual void setUserSecret(const std::string &newUserSecret);
		
		/** Set session secret.
		 *
		 * Set the session secret to be used for message authentication.
		 *
		 * Note: As the name implies, you should not reuse this secret across 
		 * sessions or connections. The best candidate for a session secret is 
		 * a random string of a fixed length, generated on a new connection 
		 * and passed to the peer in one of the first few messages.
		 *
		 * \param newSessionSecret Session secret.
		 */
		virtual void setSessionSecret(const std::string &newSessionSecret);
		
		/** Set target.
		 *
		 * Set the target that should be noified on completion of a message.
		 *
		 * \param newTarget Message target.
		 */
		virtual void setTarget(MessageDump *newTarget);
		
		/** Set maximum message size.
		 *
		 * Set the maximum allowed size for a single message, in bytes.
		 *
		 * \param newMaxSize Maximum message size (bytes).
		 */
		virtual void setMaxSize(unsigned int newMaxSize);
		
		/** Get magic word.
		 *
		 * \return The magic word.
		 */
		virtual std::string getMagicWord();
		
		/** Get protocol version.
		 *
		 * \return Protocol version.
		 */
		virtual int getProtocolVersion();
		
		/** Get UID.
		 *
		 * \return Message UID.
		 */
		virtual int getUID();
		
		/** Get message type.
		 *
		 * \return Message type ID.
		 */
		virtual int getType();
		
		/** Get flags.
		 *
		 * \return Flags.
		 */
		virtual unsigned int getFlags();
		
		/** Get size.
		 *
		 * \return Size of serialized message data.
		 */
		virtual unsigned int getSize();
		
		/** Get username.
		 *
		 * \return Username.
		 */
		virtual std::string getUsername();
		
		/** Get user secret.
		 *
		 * Copies the user secret to a specified buffer.
		 *
		 * \param userSecretBuffer Where to store the user secret.
		 */
		virtual void getUserSecret(std::string &userSecretBuffer);
		
		/** Get session secret.
		 *
		 * Copies the session secret to a specified buffer.
		 *
		 * \param sessionSecretBuffer Where to store the session secret.
		 */
		virtual void getSessionSecret(std::string &sessionSecretBuffer);
		
		/** Get number of missing bytes.
		 *
		 * Get the number of serialized bytes required to complete the 
		 * message. Use dump() to append additional bytes to the message. If 
		 * the message is complete or invalid, this function returns 0.
		 *
		 * \note Even if you supply the correct amount of bytes, the message 
		 * might still not be complete due to invalid or corrupted data or an 
		 * invalid protocol version. You should rely on the callback facility 
		 * provided by setTarget() to determine whether a message is actually 
		 * complete and valid.
		 *
		 * \return Number of bytes missing.
		 *
		 * \sa setTarget()
		 */
		virtual unsigned int getNumBytesMissing();
		
		/** Get maximum message size.
		 *
		 * \return Maximum allowed size of serialized message, in bytes.
		 */
		virtual unsigned int getMaxSize();
};

}

}

/** \file Message.hpp
 * \brief Network message header.
 */
#endif
