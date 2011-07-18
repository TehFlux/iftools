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
        $$function
    } catch(Ionflux::ObjectBase::IFError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

namespace Ionflux
{

namespace ObjectBase
{

// types.hpp

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

// utf8.hpp

std::string uniCharToUTF8(IFUniChar uniChar, 
	const Ionflux::ObjectBase::IFObject* logTarget = 0);
bool utf8ToUniChar(const std::string& bytes, IFUniChar& target, 
	const Ionflux::ObjectBase::IFObject* logTarget = 0);
void uniCharToUTF8(const std::vector<IFUniChar>& uniChars, 
	std::string& target,
	const Ionflux::ObjectBase::IFObject* logTarget = 0);
unsigned int utf8GetSize(unsigned char byte, 
	const Ionflux::ObjectBase::IFObject* logTarget = 0);
bool utf8ToUniChar(const std::string& bytes, 
	std::vector<IFUniChar>& target,
	const Ionflux::ObjectBase::IFObject* logTarget = 0);
unsigned int utf8GetSize(const std::string& bytes, 
	const Ionflux::ObjectBase::IFObject* logTarget = 0);

// utility.hpp

const unsigned int READ_BUFFER_SIZE = 4096;
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

$IFClassInfo

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
                return $$self->getString();
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

$IFError
$IFCache

%template(StringVector) std::vector<std::string>;
%template(DoubleVector) std::vector<double>;
%template(IntVector) std::vector<int>;
%template(UIntVector) std::vector<unsigned int>;
