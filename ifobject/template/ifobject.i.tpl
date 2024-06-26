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

/* HACK: This is necessary so that SWIG knows about the integer types 
         but unfortunately platform dependent (and the SWIG stdint.i gets 
         it wrong). */
typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;
typedef long int                int64_t;
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long int       uint64_t;

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

typedef UInt64 DataSize;

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

typedef void* GenericPointer;

typedef std::map<Ionflux::ObjectBase::GenericPointer, 
    Ionflux::ObjectBase::UInt64> PointerOffsetMap;
typedef std::map<Ionflux::ObjectBase::UInt64, 
    Ionflux::ObjectBase::GenericPointer> OffsetPointerMap;
typedef std::map<Ionflux::ObjectBase::GenericPointer, 
    Ionflux::ObjectBase::GenericPointer> PointerPointerMap;

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

typedef int StreamTypeID;

// utf8.hpp

std::string uniCharToUTF8(IFUniChar uniChar);
bool utf8ToUniChar(const std::string& bytes, IFUniChar& target);
void uniCharToUTF8(const std::vector<IFUniChar>& uniChars, 
	std::string& target);
unsigned int utf8GetSize(unsigned char byte);
bool utf8ToUniChar(const std::string& bytes, 
	std::vector<IFUniChar>& target);
unsigned int utf8GetSize(const std::string& bytes);
void utf8MakeReadable(const std::string& inputData, 
	Ionflux::ObjectBase::UniCharVector& target, 
	Ionflux::ObjectBase::IFUniChar replacement = 46);
std::string utf8MakeNiceHex(const std::string& hex, 
    const Ionflux::ObjectBase::UniCharVector& readable, 
    int bytesPerLine = 20, int groupBytes = 10);
std::string utf8MakeNiceHexForData(const std::string& data, 
    int bytesPerLine = 20, int groupBytes = 10);

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
const Ionflux::ObjectBase::DataSize DATA_SIZE_INVALID = 0xffffffffffffffffULL;
const Ionflux::ObjectBase::StreamTypeID STREAM_TYPE_UNDEFINED = 0;
const Ionflux::ObjectBase::StreamTypeID STREAM_TYPE_FILE = 1;
const Ionflux::ObjectBase::StreamTypeID STREAM_TYPE_STRING = 2;

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
void addValues(Ionflux::ObjectBase::IntVector& target, 
    unsigned int numValues, 
    int v0 = 0, int v1 = 0, int v2 = 0, int v3 = 0, 
    int v4 = 0, int v5 = 0, int v6 = 0, int v7 = 0, 
    int v8 = 0, int v9 = 0, int v10 = 0, int v11 = 0, 
    int v12 = 0, int v13 = 0, int v14 = 0, int v15 = 0);
void addValues(Ionflux::ObjectBase::UIntVector& target, 
    unsigned int numValues, 
    unsigned int v0 = 0, unsigned int v1 = 0, 
    unsigned int v2 = 0, unsigned int v3 = 0, 
    unsigned int v4 = 0, unsigned int v5 = 0, 
    unsigned int v6 = 0, unsigned int v7 = 0, 
    unsigned int v8 = 0, unsigned int v9 = 0, 
    unsigned int v10 = 0, unsigned int v11 = 0, 
    unsigned int v12 = 0, unsigned int v13 = 0, 
    unsigned int v14 = 0, unsigned int v15 = 0);
void addValues(Ionflux::ObjectBase::DoubleVector& target, 
    unsigned int numValues, 
    double v0 = 0., double v1 = 0., double v2 = 0., double v3 = 0., 
    double v4 = 0., double v5 = 0., double v6 = 0., double v7 = 0., 
    double v8 = 0., double v9 = 0., double v10 = 0., double v11 = 0., 
    double v12 = 0., double v13 = 0., double v14 = 0., double v15 = 0.);
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
std::string getErrorString(const std::string& message, 
    const std::string& source = "", 
    const Ionflux::ObjectBase::IFObject* sourceObj = 0);
std::string getStreamTypeValueString(Ionflux::ObjectBase::StreamTypeID t);
std::string getBooleanValueString(bool v);

template<class T>
std::string getValueStringVec(const T& v, const std::string& sep = ", ")
{
    std::ostringstream status;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (i > 0)
            status << sep;
        status << v[i];
    }
    return status.str();
}

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
                return $$self->getString();
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

%template(getValueStringVecString) getValueStringVec<StringVector>;
%template(getValueStringVecDouble) getValueStringVec<DoubleVector>;
%template(getValueStringVecInt) getValueStringVec<IntVector>;
%template(getValueStringVecUInt) getValueStringVec<UIntVector>;

}

}

$IFError
$IFCache
$IFMMEvent
$IFMMEventHandler
$IFXMLObjectFactory
$IFIOContext

%template(StringVector) std::vector<std::string>;
%template(DoubleVector) std::vector<double>;
%template(IntVector) std::vector<int>;
%template(UIntVector) std::vector<unsigned int>;
