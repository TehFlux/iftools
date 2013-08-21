/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFObject.i                      Object (interface).
 * =========================================================================

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
%{
#include "ifobject/IFObject.hpp"
%}

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
{

namespace ObjectBase
{

class IFSignal;

}

}

namespace Ionflux
{

namespace ObjectBase
{

class IFMutex;
class IFMMEvent;
class IFMMEventHandler;
// events used by IFObject
class IFObjectEvent;

typedef sigc::signal<bool, const Ionflux::ObjectBase::IFObjectEvent&> 
IFObjectSignal;


 
struct IFObjectRefInfo
{
    unsigned int refCount;
};
 
struct IFRefCountData
{
    IFObjectRefMap refMap;
    unsigned int refCount;
    bool mmDebug;
};

struct IFObjectSignalConnections
{
    sigc::connection signalObjectChangedConnection;
    sigc::connection signalObjectIDNumChangedConnection;
    sigc::connection signalObjectIDChangedConnection;
};

class IFObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFObjectClassInfo();
        virtual ~IFObjectClassInfo();
};

class IFObject
{
    public:
		static const std::string LITERAL_PREFIX;
		static const std::string LITERAL_SEPARATOR;
		static const std::string ENCODING_RAW;
		static const std::string ENCODING_UTF8;
		static const std::string ENCODING_BASE64;
		static const Ionflux::ObjectBase::UInt64 DEFAULT_SIZE;
		static const std::string XML_ELEMENT_NAME;
		static const IFIDNum ID_NUM_UNDEFINED;
        static const Ionflux::ObjectBase::IFSignalType SIGNAL_TYPE_OBJECT;
        static const std::string SIGNAL_NAME_OBJECT_CHANGED;
        static const std::string SIGNAL_NAME_OBJECT_ID_NUM_CHANGED;
        static const std::string SIGNAL_NAME_OBJECT_ID_CHANGED;
        
        IFObject();
        virtual ~IFObject();        
        IFObjectEvent* createObjectEvent();
        virtual const Ionflux::ObjectBase::IFClassInfo* getClass() const;
        virtual std::string getClassName() const;
        virtual std::string getClassDesc() const;
        virtual void setID(const Ionflux::ObjectBase::IFObjectID& newID);
        virtual Ionflux::ObjectBase::IFObjectID getID() const;
        virtual void setIDNum(Ionflux::ObjectBase::IFIDNum newIDNum);
        virtual Ionflux::ObjectBase::IFIDNum getIDNum() const;
        virtual  operator std::string() const;
        virtual void getLiteral(std::string& target, const std::string& 
        encoding = ENCODING_UTF8) const;
        virtual std::string getLiteral2(const std::string& encoding = 
        ENCODING_UTF8) const;
        virtual bool initFromLiteral(const std::string& source);
        virtual Ionflux::ObjectBase::IFObject* copy() const;
        static Ionflux::ObjectBase::IFObject* 
        create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual bool doOp(const Ionflux::ObjectBase::IFOpName& opName, 
        const Ionflux::ObjectBase::IFObjectVector* params = 0, 
        Ionflux::ObjectBase::IFObjectVector* target = 0);
        virtual bool doOp(const Ionflux::ObjectBase::IFOpName& opName, 
        const Ionflux::ObjectBase::IFObjectVector* params = 0, 
        Ionflux::ObjectBase::IFObjectVector* target = 0) const;
        virtual void log(const Ionflux::ObjectBase::IFObject& logObject);
        virtual void log();
        virtual void log(const Ionflux::ObjectBase::IFObject& logObject) 
        const;
        virtual void log() const;
        virtual bool assert0(bool assertion, const 
        Ionflux::ObjectBase::IFObject& logObject);
        virtual bool assert0(bool assertion, const 
        Ionflux::ObjectBase::IFObject& logObject) const;
        virtual bool addRef() const;
        virtual bool removeRef() const;
        virtual unsigned int getNumRefs() const;
        virtual bool addLocalRef(Ionflux::ObjectBase::IFObject* refTarget) 
        const;
        virtual bool removeLocalRef(Ionflux::ObjectBase::IFObject* 
        refTarget) const;
        virtual bool removeAllLocalRefs() const;
        virtual unsigned int getNumLocalRefs(Ionflux::ObjectBase::IFObject*
        refTarget) const;
        virtual void setGuardEnabled(bool newGuardState);
        virtual bool getGuardEnabled();
        virtual bool lock() const;
        virtual bool tryLock() const;
        virtual bool unlock() const;
        virtual Ionflux::ObjectBase::UInt64 getSize() const;
        virtual std::string getXMLElementName() const;
        virtual void getXMLChildData(std::string& target, unsigned int 
        indentLevel = 0) const;
        virtual std::string getXMLChildData0(std::string& target, unsigned 
        int indentLevel = 0) const;
        virtual std::string getXMLAttributeData() const;
        virtual void getXML(std::string& target, unsigned int indentLevel =
        0) const;
        virtual std::string getXML0(unsigned int indentLevel = 0) const;
        virtual void writeToXMLFile(const std::string& fileName) const;
        virtual void loadFromXMLFile(const std::string& fileName);
        virtual std::string getValueString() const;
        virtual void setMMDebug(bool newFlag = true);
        virtual bool mmDebugEnabled();
        virtual void handleMMEvent(const Ionflux::ObjectBase::IFMMEvent& 
        event) const;
        virtual std::string getIDString() const;
        virtual std::string getErrorString(const std::string& message, 
        const std::string& source = "") const;
        virtual std::string getString() const;
        virtual bool serialize(std::string& target) const;
        virtual int deserialize(const std::string& source, int offset = 0);
        virtual void setLogTarget(Ionflux::ObjectBase::IFObject* 
        newLogTarget);
        virtual Ionflux::ObjectBase::IFObject* getLogTarget() const;
        virtual IFObjectSignal& getSignalObjectChanged();
        virtual Ionflux::ObjectBase::IFSignal* getSignalObjectChangedWrapper();
        virtual IFObjectSignal& getSignalObjectIDNumChanged();
        virtual Ionflux::ObjectBase::IFSignal* getSignalObjectIDNumChangedWrapper();
        virtual IFObjectSignal& getSignalObjectIDChanged();
        virtual Ionflux::ObjectBase::IFSignal* getSignalObjectIDChangedWrapper();
};

std::ostream& operator<<(std::ostream& outputStream, const 
Ionflux::ObjectBase::IFObject& source);

}

}
