%include <std_string.i>
%include <std_map.i>
%include <std_vector.i>
%module IFObjectBase
%{
#include "ifobject/ifobjectbase.hpp"
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
typedef int MMEventTypeID;

struct LineBuffer
{
    char** data;
    int size;
};

struct LineBufferConst
{
    const char** data;
    int size;
};

// utf8.hpp

std::string uniCharToUTF8(IFUniChar uniChar);
bool utf8ToUniChar(const std::string& bytes, IFUniChar& target);
void uniCharToUTF8(const std::vector<IFUniChar>& uniChars, 
	std::string& target);
unsigned int utf8GetSize(unsigned char byte);
bool utf8ToUniChar(const std::string& bytes, 
	std::vector<IFUniChar>& target);
unsigned int utf8GetSize(const std::string& bytes);

// constants.hpp

const unsigned int READ_BUFFER_SIZE = 4096;
const std::string DEFAULT_COORD_SEPARATOR = ",";
const unsigned int DEFAULT_INDENT_WIDTH = 2;
const std::string XML_ELEMENT_NAME_INT_VECTOR = "intv";
const std::string XML_ELEMENT_NAME_UINT_VECTOR = "uintv";
const std::string XML_ELEMENT_NAME_DOUBLE_VECTOR = "doublev";
const std::string XML_ELEMENT_NAME_COLOR_SET_VECTOR = "colorsetv";
const std::string XML_ELEMENT_NAME_VECTOR2_SET_VECTOR = "vector2setv";
const unsigned char DIR_SEPARATOR = '/';

// utils.hpp

bool readFile(const std::string& fileName, std::string& target, 
    Ionflux::ObjectBase::IFObject* logTarget = 0);
void explode(const std::string& bytes, const std::string& splitString, 
	std::vector<std::string>& result);
bool isOneOf(char c, const std::string& testChars, bool invert = false);
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
std::string makeHex(const std::string& inputData);
std::string makeReadable(const std::string& inputData, 
	const std::string& replacement);
std::string makeNiceHex(const std::string& hex, const std::string& readable, 
	int bytesPerLine, int groupBytes);
std::string parseHex(const std::string& inputData);
std::string sha1(const std::string& secret, bool hexOut = false);
std::string hmac(const std::string& key, const std::string& message, 
    bool hexOut = false);
void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::IntVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);
void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::UIntVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);
void vectorFromList(const std::string& data, 
    Ionflux::ObjectBase::DoubleVector& target, 
    const std::string& separator = DEFAULT_COORD_SEPARATOR);
std::string getIndent(unsigned int level = 0, 
    unsigned int indentWidth = DEFAULT_INDENT_WIDTH, 
    char indentChar = ' ');
std::string escape(const std::string &source, 
	const std::string& escapeWhat = " '\"");
std::string mmTypeIDGetString(Ionflux::ObjectBase::MMEventTypeID typeID);
std::string getTimestamp();
std::string appendDirSeparator(const std::string& path, 
	unsigned char separator = DIR_SEPARATOR);
std::string prependDirSeparator(const std::string& path, 
	unsigned char separator = DIR_SEPARATOR);
Ionflux::ObjectBase::LineBuffer createLineBuffer(
    const Ionflux::ObjectBase::StringVector& data);
Ionflux::ObjectBase::LineBuffer createLineBuffer(const std::string& data);
void cleanupLineBuffer(Ionflux::ObjectBase::LineBuffer& lineBuffer);
void getStringVector(const Ionflux::ObjectBase::LineBuffer& lineBuffer, 
    Ionflux::ObjectBase::StringVector& target);
Ionflux::ObjectBase::LineBufferConst createLineBufferConst(
    const Ionflux::ObjectBase::LineBuffer& lineBuffer);
void cleanupLineBuffer(Ionflux::ObjectBase::LineBufferConst& lineBuffer);

// xmlutils.hpp

namespace XMLUtils
{

std::string getAttrValue(const std::string& fileName, 
    const std::string& elementName, const std::string& elementID, 
    const std::string& attrName);
void getAttrValues(const std::string& fileName, 
    const std::string& elementName, const std::string& attrName, 
    const Ionflux::ObjectBase::StringVector& elementIDs, 
    Ionflux::ObjectBase::StringVector& target);
std::string xmlEscape(const std::string& bytes);
void setFromXML(const std::string& data, 
    Ionflux::ObjectBase::IntVector& v);
std::string getXML0(const Ionflux::ObjectBase::IntVector& v, 
    const std::string& name = "", unsigned int indentLevel = 0, 
    const std::string& attributes = "");
std::string getXML0(const Ionflux::ObjectBase::UIntVector& v, 
    const std::string& name = "", unsigned int indentLevel = 0, 
    const std::string& attributes = "");
std::string getXML0(const Ionflux::ObjectBase::DoubleVector& v, 
    const std::string& name = "", unsigned int indentLevel = 0, 
    const std::string& attributes = "");

}

}

}


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
        0, const std::string& attributes = "") const;
        virtual std::string getXML0(unsigned int indentLevel = 0, const 
        std::string& attributes = "") const;
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
        virtual unsigned int getMemSize() const;
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
        virtual bool serialize(std::string& target) const;
        virtual int deserialize(const std::string& source, int offset = 0);
        virtual void setLogTarget(Ionflux::ObjectBase::IFObject* 
        newLogTarget);
        virtual Ionflux::ObjectBase::IFObject* getLogTarget() const;
        %extend {
            std::string __str__()
            {
                return $self->getString();
            }
        }
};

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
		virtual unsigned int getMemSize() const;
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


%{
#include "ifobject/IFMMEvent.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFMMEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFMMEventClassInfo();
        virtual ~IFMMEventClassInfo();
};

class IFMMEvent
: public IFObject
{
    public:
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_UNDEFINED;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_CREATE;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_DELETE;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_ADD_REF;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_REMOVE_REF;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_ADD_LOCAL_REF;
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_REMOVE_LOCAL_REF;
        
        IFMMEvent();
		IFMMEvent(const Ionflux::ObjectBase::IFMMEvent& other);
        IFMMEvent(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
        Ionflux::ObjectBase::IFObject* initObject, unsigned int 
        initObjectRefCount = 0, const Ionflux::ObjectBase::IFObject* 
        initParentObject = 0);
        virtual ~IFMMEvent();
        virtual bool operator==(const Ionflux::ObjectBase::IFMMEvent& 
        other) const;
        virtual bool operator!=(const Ionflux::ObjectBase::IFMMEvent& 
        other) const;
        virtual std::string getValueString() const;
		virtual Ionflux::ObjectBase::IFMMEvent* copy() const;
		static Ionflux::ObjectBase::IFMMEvent* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::ObjectBase::IFMMEvent* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::ObjectBase::IFMMEvent* 
		create(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
		Ionflux::ObjectBase::IFObject* initObject, unsigned int 
		initObjectRefCount = 0, const Ionflux::ObjectBase::IFObject* 
		initParentObject = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setTypeID(Ionflux::ObjectBase::MMEventTypeID 
        newTypeID);
        virtual Ionflux::ObjectBase::MMEventTypeID getTypeID() const;
        virtual void setObject(const Ionflux::ObjectBase::IFObject* 
        newObject);
        virtual const Ionflux::ObjectBase::IFObject* getObject() const;
        virtual void setObjectRefCount(unsigned int newObjectRefCount);
        virtual unsigned int getObjectRefCount() const;
        virtual void setParentObject(const Ionflux::ObjectBase::IFObject* 
        newParentObject);
        virtual const Ionflux::ObjectBase::IFObject* getParentObject() 
        const;
};

}

}


%{
#include "ifobject/IFMMEventHandler.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFMMEvent;

class IFMMEventHandlerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFMMEventHandlerClassInfo();
        virtual ~IFMMEventHandlerClassInfo();
};

class IFMMEventHandler
: public IFObject
{
    public:
        
        IFMMEventHandler();
		IFMMEventHandler(const Ionflux::ObjectBase::IFMMEventHandler& other);
        IFMMEventHandler(Ionflux::ObjectBase::IFMMEventHandler* initTarget,
        const std::string& initLogFileName = "", bool initSilentFlag = 
        true);
        virtual ~IFMMEventHandler();
        virtual void clearLogFile() const;
        virtual void handleMMEvent(const Ionflux::ObjectBase::IFMMEvent& 
        event) const;
        virtual std::string getValueString() const;
        static Ionflux::ObjectBase::IFMMEventHandler* getInstance();
        static void cleanup();
		virtual Ionflux::ObjectBase::IFMMEventHandler* copy() const;
		static Ionflux::ObjectBase::IFMMEventHandler* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::ObjectBase::IFMMEventHandler* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::ObjectBase::IFMMEventHandler* 
		create(Ionflux::ObjectBase::IFMMEventHandler* initTarget, const 
		std::string& initLogFileName = "", bool initSilentFlag = true, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setTarget(Ionflux::ObjectBase::IFMMEventHandler* 
        newTarget);
        virtual Ionflux::ObjectBase::IFMMEventHandler* getTarget() const;
        virtual void setLogFileName(const std::string& newLogFileName);
        virtual std::string getLogFileName() const;
        virtual void setSilentFlag(bool newSilentFlag);
        virtual bool getSilentFlag() const;
};

}

}


%{
#include "ifobject/IFXMLObjectFactory.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

class IFXMLObjectFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFXMLObjectFactoryClassInfo();
        virtual ~IFXMLObjectFactoryClassInfo();
};

class IFXMLObjectFactory
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        IFXMLObjectFactory();
		IFXMLObjectFactory(const Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory& other);
        virtual ~IFXMLObjectFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::ObjectBase::IFObject& target) const;
        virtual Ionflux::ObjectBase::IFObject* createObject() const;
        virtual std::string getValueString() const;
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* copy() const;
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumFactories() const;
        virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
        getFactory(unsigned int elementIndex = 0) const;
		virtual int 
		findFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* needle, 
		unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>& 
        getFactories();
        virtual void 
        addFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
        addElement);
		virtual Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* addFactory();
		virtual void 
		addFactories(std::vector<Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory*>&
		newFactories);
		virtual void 
		addFactories(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		newFactories);        
        virtual void 
        removeFactory(Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
        removeElement);
		virtual void removeFactoryIndex(unsigned int removeIndex);
		virtual void clearFactories();
};

}

}

}


%template(StringVector) std::vector<std::string>;
%template(DoubleVector) std::vector<double>;
%template(IntVector) std::vector<int>;
%template(UIntVector) std::vector<unsigned int>;
