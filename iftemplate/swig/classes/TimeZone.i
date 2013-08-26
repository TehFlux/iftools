/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TimeZone.i                      Time zone (interface).
 * =========================================================================

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
%{
#include "iftemplate/TimeZone.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TimeZoneClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TimeZoneClassInfo();
        virtual ~TimeZoneClassInfo();
};

class TimeZone
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EUROPE_WESTERN;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EUROPE_WESTERN;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EUROPE_CENTRAL;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EUROPE_CENTRAL;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EUROPE_EASTERN;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EUROPE_EASTERN;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_USA;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_USA;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_DST_EGYPT;
		static const Ionflux::Template::DSTSwitchingRule DSR_TO_NORMAL_EGYPT;
        
        TimeZone();
		TimeZone(const Ionflux::Template::TimeZone& other);
        TimeZone(int initOffset);
        TimeZone(int initOffset, const Ionflux::Template::DSTSwitchingRule&
        initToDST, const Ionflux::Template::DSTSwitchingRule& 
        initToNormal);
        TimeZone(int initOffset, const std::string& initNameNormal, const 
        std::string& initNameDST, const std::string& initShortNameNormal, 
        const std::string& initShortNameDST, const std::string& 
        initAliases);
        TimeZone(int initOffset, const Ionflux::Template::DSTSwitchingRule&
        initToDST, const Ionflux::Template::DSTSwitchingRule& initToNormal,
        const std::string& initNameNormal, const std::string& initNameDST, 
        const std::string& initShortNameNormal, const std::string& 
        initShortNameDST, const std::string& initAliases);
        virtual ~TimeZone();
        virtual void setDSTRules(const Ionflux::Template::DSTSwitchingRule&
        newToDST, const Ionflux::Template::DSTSwitchingRule& newToNormal);
        virtual bool isDST(const Ionflux::Template::DateTime& utcDT) const;
        virtual bool localIsDST(const Ionflux::Template::DateTime& localDT)
        const;
        virtual int getCurrentOffset(const Ionflux::Template::DateTime& 
        utcDT) const;
        virtual const Ionflux::Template::DSTSwitchingRule* getDSTRule(bool 
        ruleFlag) const;
        virtual Ionflux::Template::DateTime 
        getSwitchDT(Ionflux::Template::Year year, const 
        Ionflux::Template::DSTSwitchingRule& rule) const;
        virtual bool hasAlias(const std::string& checkAlias) const;
        virtual void enableDST(bool enableFlag);
		virtual Ionflux::Template::TimeZone* copy() const;
		static Ionflux::Template::TimeZone* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Template::TimeZone* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::Template::TimeZone* create(int initOffset, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::TimeZone* create(int initOffset, const 
		Ionflux::Template::DSTSwitchingRule& initToDST, const 
		Ionflux::Template::DSTSwitchingRule& initToNormal, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::TimeZone* create(int initOffset, const 
		std::string& initNameNormal, const std::string& initNameDST, const 
		std::string& initShortNameNormal, const std::string& initShortNameDST, 
		const std::string& initAliases, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Template::TimeZone* create(int initOffset, const 
		Ionflux::Template::DSTSwitchingRule& initToDST, const 
		Ionflux::Template::DSTSwitchingRule& initToNormal, const std::string& 
		initNameNormal, const std::string& initNameDST, const std::string& 
		initShortNameNormal, const std::string& initShortNameDST, const 
		std::string& initAliases, Ionflux::ObjectBase::IFObject* parentObject = 
		0);
        virtual void setOffset(int newOffset);
        virtual int getOffset() const;
        virtual void setNameNormal(const std::string& newNameNormal);
        virtual std::string getNameNormal() const;
        virtual void setNameDST(const std::string& newNameDST);
        virtual std::string getNameDST() const;
        virtual void setShortNameNormal(const std::string& 
        newShortNameNormal);
        virtual std::string getShortNameNormal() const;
        virtual void setShortNameDST(const std::string& newShortNameDST);
        virtual std::string getShortNameDST() const;
        virtual void setAliases(const std::string& newAliases);
        virtual std::string getAliases() const;
};

}

}
