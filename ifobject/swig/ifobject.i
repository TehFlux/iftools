%include <std_string.i>
%include <std_map.i>
%include <std_vector.i>
%module IFObjectBase
%{
#include "ifobject/IFObject.hpp"
#include "ifobject/utility.hpp"
#include "ifobject/types.hpp"
#include "ifobject/IFError.hpp"
#include "ifobject/IFCache.hpp"
#include <assert.h>
%}

%exception {
    try
    {
        $function
    } catch(Ionflux::ObjectBase::IFError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

namespace Ionflux
{

namespace ObjectBase
{

// HACK.
typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;
typedef long long int           int64_t;
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long int  uint64_t;

// integers
typedef int8_t Int8;
typedef uint8_t UInt8;
typedef int16_t Int16;
typedef uint16_t UInt16;
typedef int32_t Int32;
typedef uint32_t UInt32;
typedef int64_t Int64;
typedef uint64_t UInt64;

// unicode characters
typedef UInt32 IFUniChar;

// forward declarations
class IFObject;
struct IFObjectRefInfo;
struct IFOpParamInfo;
struct IFOpResultInfo;
struct IFOpInfo;

// other types
typedef std::string IFObjectID;
typedef std::string IFParamID;
typedef int IFIDNum;
typedef int IFEventType;
typedef	std::set<Ionflux::ObjectBase::IFObject*> IFObjectSet;
typedef	std::vector<Ionflux::ObjectBase::IFObject*> IFObjectVector;
typedef std::map<Ionflux::ObjectBase::IFObject*, IFObjectRefInfo*> IFObjectRefMap;
typedef std::string IFSignalType;
typedef int IFMutexType;
typedef int IFAtomic;
typedef std::string IFOpName;
typedef std::vector<IFOpParamInfo> IFOpParamInfoVector;
typedef std::vector<IFOpResultInfo> IFOpResultInfoVector;
typedef std::map<IFOpName, const IFOpInfo*> IFOpNameInfoMap;
typedef std::vector<std::string> StringVector;
typedef std::vector<double> DoubleVector;
typedef std::vector<int> IntVector;
typedef std::vector<unsigned int> UIntVector;

struct IFCacheEntry
{
    std::string itemID;
    Ionflux::ObjectBase::UInt64 cTime;
    Ionflux::ObjectBase::UInt64 hTime;
    Ionflux::ObjectBase::UInt64 hits;
    Ionflux::ObjectBase::IFObject* item;
};

typedef unsigned int CachePolicy;

}

}

/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFClassInfo.i                   Class information (interface).
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
#include "ifobject/IFClassInfo.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFClassInfo;

typedef std::vector<const Ionflux::ObjectBase::IFClassInfo*> IFClassInfoVector;
 
struct IFOpParamInfo
{
    const Ionflux::ObjectBase::IFClassInfo* type;
    std::string name;
    std::string desc;
    bool optional;
    Ionflux::ObjectBase::IFObject* defaultValue;
};
 
struct IFOpResultInfo
{
    const Ionflux::ObjectBase::IFClassInfo* type;
    std::string desc;
};
 
struct IFOpInfo
{
    Ionflux::ObjectBase::IFOpName name;
    Ionflux::ObjectBase::IFOpParamInfoVector paramInfo;
    Ionflux::ObjectBase::IFOpResultInfoVector resultInfo;
};

class IFClassInfo
{
    public:
        
        IFClassInfo();
        virtual ~IFClassInfo();
        virtual int getNumBaseClasses() const;
        virtual const Ionflux::ObjectBase::IFClassInfo* 
        getBaseClassInfo(unsigned int index) const;
        virtual bool isDerivedFrom(const Ionflux::ObjectBase::IFClassInfo* 
        searchClass, bool recursive = true) const;
        virtual bool isBaseOf(const Ionflux::ObjectBase::IFClassInfo* 
        checkClass, bool recursive = true) const;
        virtual bool isDerivedFrom(const std::string& searchClassName, bool
        recursive = true) const;
        virtual void getOpInfo(Ionflux::ObjectBase::IFOpNameInfoMap& 
        target) const;
        virtual const Ionflux::ObjectBase::IFOpInfo* getOpInfo(const 
        Ionflux::ObjectBase::IFOpName& opName) const;
        virtual std::string getName() const;
        virtual std::string getDesc() const;
};

}

}


namespace Ionflux
{

namespace ObjectBase
{

class IFMutex;
class IFObjectEvent;

struct IFObjectRefInfo
{
	unsigned int refCount;
};
 
struct IFRefCountData
{
	IFObjectRefMap refMap;
	unsigned int refCount;
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
		virtual std::string getString() const;
		virtual void getLiteral(std::string& target, const std::string& encoding 
		= ENCODING_UTF8) const;
		virtual bool initFromLiteral(const std::string& source);
		virtual Ionflux::ObjectBase::IFObject* copy() const;
		static Ionflux::ObjectBase::IFObject* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual bool addRef() const;
		virtual bool removeRef() const;
		virtual unsigned int getNumRefs() const;
		virtual bool addLocalRef(Ionflux::ObjectBase::IFObject* refTarget) const;
		virtual bool removeLocalRef(Ionflux::ObjectBase::IFObject* refTarget) 
		const;
		virtual bool removeAllLocalRefs() const;
		virtual void setGuardEnabled(bool newGuardState);
		virtual bool getGuardEnabled();
		virtual bool lock() const;
		virtual bool tryLock() const;
		virtual bool unlock() const;
		virtual Ionflux::ObjectBase::UInt64 getSize() const;
		virtual bool serialize(std::string& target) const;
		virtual int deserialize(const std::string& source, int offset = 0);
		virtual void setLogTarget(Ionflux::ObjectBase::IFObject* newLogTarget);
		virtual Ionflux::ObjectBase::IFObject* getLogTarget() const;
        %extend {
            std::string __str__()
            {
                return $self->getString();
            }
        }
};

void pack(const Ionflux::ObjectBase::IFObject*& source, std::string& 
target, bool append = true);
int unpack(const std::string& source, Ionflux::ObjectBase::IFObject*& 
target, int offset = 0);

const unsigned int READ_BUFFER_SIZE;

bool readFile(const std::string& fileName, std::string& target, 
    Ionflux::ObjectBase::IFObject* logTarget = 0);
void explode(const std::string& bytes, const std::string& splitString, 
	std::vector<std::string>& result);
bool isOneOf(char c, const std::string& testChars);
bool isNumber(const std::string &bytes);
bool isInteger(const std::string &bytes);
bool isFloat(const std::string &bytes);
bool isIdentifier(const std::string &bytes);
std::string toUpper(const std::string &text, unsigned int numChars = 0, 
	unsigned int offset = 0);
std::string toLower(const std::string &text, unsigned int numChars = 0, 
	unsigned int offset = 0);
std::string trim(const std::string& bytes, bool leftTrim = true, 
	bool rightTrim = true);
bool hasPrefix(const std::string& bytes, const std::string& prefix, 
    bool ignoreCase = true);
bool hasPrefix(const std::string& bytes, const std::vector<std::string>& 
    prefixes, bool ignoreCase = true);
Ionflux::ObjectBase::UInt64 getTimeTicks();

}

}

/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFError.i                       Error (interface).
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
#include "ifobject/IFError.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFError
: public std::exception
{
    public:
        
        IFError();
		IFError(const Ionflux::ObjectBase::IFError& other);
        IFError(const std::string& initReason);
        virtual ~IFError() throw();
        virtual std::string getString() const;
        virtual const char* what() const throw();
		virtual Ionflux::ObjectBase::IFError* copy() const;
        virtual void setReason(const std::string& newReason);
        virtual std::string getReason() const;
};

}

}

/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFCache.i                       Cache (interface).
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
#include "ifobject/IFCache.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFCacheClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFCacheClassInfo();
        virtual ~IFCacheClassInfo();
};

class IFCache
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::ObjectBase::CachePolicy POLICY_KEEP_RECENT;
		static const Ionflux::ObjectBase::CachePolicy POLICY_KEEP_MOST_HITS;
        
        IFCache();
        IFCache(Ionflux::ObjectBase::UInt64 initMaxSize, bool 
        initAllowZeroSize = false, Ionflux::ObjectBase::CachePolicy 
        initPolicy = POLICY_KEEP_MOST_HITS);
        virtual ~IFCache();
        virtual std::string getString() const;
        virtual void clear();
        virtual void reset(Ionflux::ObjectBase::UInt64 hits = 0);
        virtual unsigned int getNumEntries() const;
        virtual bool isFull(Ionflux::ObjectBase::UInt64 offset = 0) const;
        virtual bool itemExists(const std::string& itemID);
        virtual Ionflux::ObjectBase::UInt64 getHits(const std::string& 
        itemID);
        virtual Ionflux::ObjectBase::IFObject* getItem(const std::string& 
        itemID);
        virtual bool removeItem(const std::string& itemID);
        virtual void cleanup();
        virtual void cleanup(Ionflux::ObjectBase::UInt64 minSize);
        virtual void addItem(const std::string& itemID, 
        Ionflux::ObjectBase::IFObject* item, Ionflux::ObjectBase::UInt64 
        hits = 0);
        virtual void getItems(Ionflux::ObjectBase::IFObjectVector& target);
        virtual void getItemIDs(Ionflux::ObjectBase::StringVector& target);
        virtual std::string getDebugInfo();
        static void initEntry(Ionflux::ObjectBase::IFCacheEntry& entry, 
        Ionflux::ObjectBase::IFObject* item = 0, const std::string& itemID 
        = "", Ionflux::ObjectBase::UInt64 cTime = 0, 
        Ionflux::ObjectBase::UInt64 hTime = 0, Ionflux::ObjectBase::UInt64 
        hits = 0);
		static Ionflux::ObjectBase::IFCache* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMaxSize(Ionflux::ObjectBase::UInt64 newMaxSize);
        virtual Ionflux::ObjectBase::UInt64 getMaxSize() const;
        virtual Ionflux::ObjectBase::UInt64 getCurrentSize() const;
        virtual void setAllowZeroSize(bool newAllowZeroSize);
        virtual bool getAllowZeroSize() const;
        virtual void setPolicy(Ionflux::ObjectBase::CachePolicy newPolicy);
        virtual Ionflux::ObjectBase::CachePolicy getPolicy() const;
};

}

}


%template(StringVector) std::vector<std::string>;
%template(DoubleVector) std::vector<double>;
%template(IntVector) std::vector<int>;
%template(UIntVector) std::vector<unsigned int>;
