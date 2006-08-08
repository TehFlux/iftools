#ifndef IONFLUX_TOOLS_EMAILADDRESS
#define IONFLUX_TOOLS_EMAILADDRESS
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * EMailAddress.hpp                  EMail address.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/tools.hpp"
#include "ionflux/ManagedObject.hpp"
#include "ionflux/StringManipulator.hpp"

namespace Ionflux
{

namespace Tools
{

/// A mailbox (see RFC 2822).
struct Mailbox
{
	/// Display name.
	std::string displayName;
	/// Address.
	std::string address;
	/// Local part.
	std::string localPart;
	/// Domain.
	std::string domain;
};

/** EMail address.
 * \ingroup general
 *
 * An email address, as defined in RFC 2822.
 */
class EMailAddress
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Validity flag.
		bool validAddress;
		/// Mailboxes which are part of this address.
		std::vector<Mailbox> mailboxes;
		/// Unparsed address.
		std::string rawAddress;
		/// Display name (mailbox or group).
		std::string displayName;
		
	public:
		/// Token type: Atom text.
		static const Ionflux::Tools::TokenType TT_ATOM_TEXT;
		/// Token type: Special.
		static const Ionflux::Tools::TokenType TT_SPECIAL;
		/// Token type: Folding whitespace.
		static const Ionflux::Tools::TokenType TT_FWS;
		
		/** Constructor.
		 *
		 * Construct new EMailAddress object.
		 */
		EMailAddress();
		
		/** Constructor.
		 *
		 * Construct new EMailAddress object.
		 *
		 * \param initAddress EMail address.
		 */
		EMailAddress(const EMailAddress& initAddress);
		
		/** Constructor.
		 *
		 * Construct new EMailAddress object.
		 *
		 * \param initRawAddress Unparsed address.
		 */
		EMailAddress(const std::string& initRawAddress);
		
		/** Destructor.
		 *
		 * Destruct EMailAddress object.
		 */
		virtual ~EMailAddress();
		
		/** Clear.
		 *
		 * Reset all fields.
		 */
		virtual void clear();
		
		/** Parse email address.
		 *
		 * Parse an email address.
		 *
		 * \param newRawAddress Unparsed email address.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool parse(const std::string& newRawAddress = "");
		
		/** Validate address.
		 *
		 * Check whether this email address is valid.
		 *
		 * \return \c true if the email address is valid, \c false otherwise.
		 */
		virtual bool isValid() const;
		
		/** Get mailboxes.
		 *
		 * Get the mailboxes which are part of this address.
		 *
		 * \return Mailboxes.
		 */
		virtual const std::vector<Mailbox>& getMailboxes() const;
		
		/** Get number of mailboxes.
		 *
		 * Get the number of mailboxes which are part of this address.
		 *
		 * \return Number of mailboxes.
		 */
		virtual unsigned int getNumMailboxes() const;
		
		/** Get mailbox.
		 *
		 * Get the mailbox with specified index.
		 *
		 * \param mailboxIndex Mailbox index.
		 *
		 * \return Mailbox with specified index, or an empty mailbox if mailbox
		 * with specified index does not exist.
		 */
		virtual Mailbox getMailbox(unsigned int mailboxIndex = 0) const;
		
		/** Assignment operator.
		 *
		 * Assign one EMailAddress to another EMailAddress.
		 *
		 * \param newEMailAddress EMailAddress.
		 */
		virtual EMailAddress& operator=(const EMailAddress& newEMailAddress);
		
		/** Assignment operator.
		 *
		 * Assign a string to an EMailAddress.
		 *
		 * \param newRawAddress Unparsed email address.
		 */
		virtual EMailAddress& operator=(const std::string& newRawAddress);
		
		/** Print debug information.
		 *
		 * Print useful information for debugging purposes.
		 */
		virtual void printDebugInfo() const;
		
		/** Set unparsed address.
		 *
		 * Set new value of unparsed address.
		 *
		 * \param newRawAddress New value of unparsed address.
		 */
		virtual void setRawAddress(const std::string& newRawAddress);
		
		/** Set display name (mailbox or group).
		 *
		 * Set new value of display name (mailbox or group).
		 *
		 * \param newDisplayName New value of display name (mailbox or group).
		 */
		virtual void setDisplayName(const std::string& newDisplayName);
		
		/** Get unparsed address.
		 *
		 * \return Current value of unparsed address.
		 */
		virtual std::string getRawAddress() const;
		
		/** Get display name (mailbox or group).
		 *
		 * \return Current value of display name (mailbox or group).
		 */
		virtual std::string getDisplayName() const;
};

}

}

/** \file EMailAddress.hpp
 * \brief EMail address header.
 */
#endif
