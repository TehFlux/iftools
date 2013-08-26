%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <std/std_stack.i>
%include <exception.i>
%module IFTemplate
%import "ifobject/ifobject.i"
%{
#include "ifobject/ifobjectbase.hpp"
#include "iftemplate/iftemplate.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $function
    } catch(Ionflux::Template::IFTemplateError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::ObjectBase::IFError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

namespace Ionflux
{

namespace Template
{

// types.hpp

class Node;
class StringFilterFunction;

namespace StringManipulator
{

class StringManipulator;

}

typedef int TokenTypeID;
typedef int NodeID;
typedef int NodeDataTypeID;
typedef int NodeUIDMode;
typedef int NodeIndexMode;

struct TokenType
{
	TokenTypeID typeID;
	std::string validChars;
	bool invert;
	int maxChars;
};

struct Token
{
	int typeID;
	std::string value;
};

typedef std::vector<Ionflux::Template::TokenType*> TokenTypePtrVector;
typedef std::vector<Ionflux::Template::TokenType> TokenTypeVector;
typedef std::vector<Ionflux::Template::Node*> NodeVector;

typedef std::map<std::string, Ionflux::Template::Node*> NodeNameMap;

typedef int NodeRefTypeID;

typedef std::vector<Ionflux::Template::StringManipulator::StringManipulator*> 
    StringManipulatorVector;
typedef std::vector<Ionflux::Template::StringFilterFunction*> 
    StringFilterFunctionVector;

typedef std::map<std::string, 
    Ionflux::Template::StringManipulator::StringManipulator*> 
    StringManipulatorNameMap;

typedef std::vector<std::string> CLParams;

struct CLOption
{
	std::string option;
	std::string value;
	bool splittable;
};

typedef std::vector<Ionflux::Template::CLOption*> CLOptionVector;

struct CLAcceptableOption
{
	std::string option;
	bool acceptValue;
};

typedef std::vector<Ionflux::Template::CLAcceptableOption*> 
    CLAcceptableOptionVector;

class DateTime;

typedef Ionflux::ObjectBase::Int64 TimeTicks;
typedef Ionflux::ObjectBase::Int64 Year;

struct DSTSwitchingRule
{
	static const int DSR_TYPE_TO_DST = 0;
	static const int DSR_TYPE_TO_NORMAL = 1;
	int type;
	int month;
	int weekDay;
	int week;
	int hour;
	int minute;
	int second;
};

class TimeZone;
class File;

typedef std::vector<const Ionflux::Template::TimeZone*> TimeZoneConstVector;
typedef std::vector<Ionflux::Template::File> FileVector;

// treetypes.hpp

class Node;
class Tree;

typedef std::vector<Ionflux::Template::NodeReference> NodeRefVector;

struct DataEntry
{
	Ionflux::Template::Node* node;
	unsigned int index;
	bool subscript;
};

struct TreePath
{
	Ionflux::Template::Tree* tree;
	Ionflux::Template::NodeVector nodes;
	int subscript;
	bool explicitSubscript;
};

struct TreeExprElement
{
	int type;
	std::string value;
	Ionflux::Template::DataEntry data;
	bool unary;
	static const int TE_INVALID;
	static const int TE_CONST;
	static const int TE_VAR;
	static const int TE_OP;
};

typedef std::vector<Ionflux::Template::TreeExprElement> TreeExprElementVector;
typedef std::stack<Ionflux::Template::TreeExprElement> TreeExprElementStack;

// configtypes.hpp

struct ConfigOption
{
	std::string key;
	std::string value;
};

struct ConfigLine
{
	Ionflux::Template::ConfigOption option;
	int type;
	static const int CL_INVALID;
	static const int CL_OPTION;
	static const int CL_COMMENT;
	static const int CL_BLANK;
	static const int CL_NESTED;
	static const int CL_ROOT_DATA;
};

struct ConfigTreeEntry
{
	Ionflux::Template::ConfigLine line;
	Ionflux::Template::DataEntry data;
};

typedef std::vector<Ionflux::Template::ConfigTreeEntry> ConfigTreeEntryVector;

// templatetypes.hpp

class StringFilter;

struct TemplateVar
{
	Ionflux::Template::DataEntry data;
	Ionflux::Template::StringFilter* filter;
};

typedef std::vector<Ionflux::Template::TemplateVar> TemplateVarVector;

struct TemplateElement
{
	int type;
	Ionflux::ObjectBase::StringVector params;
	Ionflux::Template::TemplateVarVector vars;
	Ionflux::ObjectBase::IntVector refs;
	
	static const int TE_INVALID = -1;
	static const int TE_CDATA = 0;
	static const int TE_VAR = 1;
	static const int TE_FOREACH = 2;
	static const int TE_FOREACH_ELSE = 3;
	static const int TE_FOREACH_END = 4;
	static const int TE_IF = 5;
	static const int TE_IF_ELSE = 6;
	static const int TE_IF_END = 7;
	static const int TE_FIRST = 8;
	static const int TE_FIRST_END = 9;
	static const int TE_MID = 10;
	static const int TE_MID_END = 11;
	static const int TE_LAST = 12;
	static const int TE_LAST_END = 13;
	static const int TE_SINGLE = 14;
	static const int TE_SINGLE_END = 15;
	static const int TE_NOTLAST = 16;
	static const int TE_NOTLAST_END = 17;
	static const int TE_NOTFIRST = 18;
	static const int TE_NOTFIRST_END = 19;
	static const int TE_NOTMID = 20;
	static const int TE_NOTMID_END = 21;
	static const int TE_NOTSINGLE = 22;
	static const int TE_NOTSINGLE_END = 23;
	static const int TE_INCLUDE = 24;
	static const int TE_SWRAP = 25;
	static const int TE_SWRAP_END = 26;
	static const int TE_SECTION = 27;
	static const int TE_SECTION_END = 28;
	static const int TE_REF = 29;
	static const int TE_IMPORT = 30;
};

typedef std::vector<Ionflux::Template::TemplateElement*> 
    TemplateElementVector;

struct TagNestingLevel
{
	unsigned int tagForeach;
	unsigned int tagIf;
	unsigned int tagFirst;
	unsigned int tagMid;
	unsigned int tagLast;
	unsigned int tagSingle;
	unsigned int tagNotFirst;
	unsigned int tagNotMid;
	unsigned int tagNotLast;
	unsigned int tagNotSingle;
	unsigned int tagSWrap;
	unsigned int tagSection;
	unsigned int tagRef;
	unsigned int all;
	
	TagNestingLevel();
};

struct TemplateSection
{
	unsigned int first;
	unsigned int last;
};

typedef std::map<std::string, Ionflux::Template::TemplateSection> 
    TemplateSectionMap;

typedef int RepositoryEntryTypeID;

}

}

%template(TokenTypePtrVector) std::vector<Ionflux::Template::TokenType*>;
%template(TokenTypeVector) std::vector<Ionflux::Template::TokenType>;
%template(NodeRefVector) std::vector<Ionflux::Template::NodeReference>;
%template(TreeExprElementVector) std::vector<Ionflux::Template::TreeExprElement>;
%template(TreeExprElementStack) std::stack<Ionflux::Template::TreeExprElement>;
%template(ConfigTreeEntryVector) std::vector<Ionflux::Template::ConfigTreeEntry>;
%template(StringManipulatorVector) std::vector<Ionflux::Template::StringManipulator::StringManipulator*>;
%template(StringFilterFunctionVector) std::vector<Ionflux::Template::StringFilterFunction*>;
%template(StringManipulatorNameMap) std::map<std::string, Ionflux::Template::StringManipulator::StringManipulator*>;
%template(CLParams) std::vector<std::string>;
%template(CLOptionVector) std::vector<Ionflux::Template::CLOption*>;
%template(CLAcceptableOptionVector) std::vector<Ionflux::Template::CLAcceptableOption*>;
%template(TimeZoneConstVector) std::vector<const Ionflux::Template::TimeZone*>;
%template(FileVector) std::vector<Ionflux::Template::File*>;
%template(TemplateVarVector) std::vector<Ionflux::Template::TemplateVar>;
%template(TemplateElementVector) std::vector<Ionflux::Template::TemplateElement*>;
%template(TemplateSectionMap) std::map<std::string, Ionflux::Template::TemplateSection>;

namespace Ionflux
{

namespace Template
{

// constants.hpp

const TokenTypeID TT_ID_INVALID = -1;
const TokenTypeID TT_ID_NONE = 0;
const TokenTypeID TT_ID_ANYTHING = 1;
const TokenTypeID TT_ID_USERTYPE = 100;

const TokenType TT_INVALID = { TT_ID_INVALID, "", false, 0 };
const TokenType TT_NONE = { TT_ID_NONE, "", false, 0 };
const TokenType TT_QUOTED = { 2, "", false, 0 };
const TokenType TT_ESCAPED = { 3, "", false, 0 };
const TokenType TT_WHITESPACE = { 4, " \t", false, 0 };
const TokenType TT_LINETERM = { 5, "\n\r", false, 1 };
const TokenType TT_IDENTIFIER = { 6, 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", 
	false, 0 };
const TokenType TT_NUMBER = { 7, "0123456789", false, 0 };
const TokenType TT_ALPHA = { 8, 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 
	false, 0 };
const TokenType TT_DEFAULT_SEP = { 7, "_-.", false, 0 };

const Token TOK_INVALID = {TT_ID_INVALID, ""};
const Token TOK_NONE = {TT_ID_NONE, ""};

const std::string QUOTE_CHARS = "\"'";
const char ESCAPE_CHAR = '\\';

const int DIR_BUFFER_SIZE = 1024;
const int DIR_BUFFER_SIZE_MAX = 65536;
const char DIR_SEPARATOR = '/';
const char FILE_EXT_SEPARATOR = '.';

const std::string TEMPLATE_FILE_EXT = ".tpl";
const std::string TEMPLATE_MODULE_SEP = ".";
const std::string DEFAULT_TEMPLATE_PATH_SEP = ":";

// utils.hpp

int unpackInt(const std::string& bytes);
bool unpackBool(const std::string& bytes);
std::string nodeRefTypeToString(Ionflux::Template::NodeRefTypeID t);
int getOpPrecedence(const std::string &op, bool unary = false);
bool hasType(const Ionflux::Template::Token& t, 
    Ionflux::Template::TokenTypeID typeID);
bool isValid(const Ionflux::Template::Token& t);
bool isNonEmpty(const Ionflux::Template::Token& t);
Ionflux::Template::TokenType createTokenType(
    Ionflux::Template::TokenTypeID typeID, const std::string& validChars, 
    bool invert, int maxChars, bool userType = true);
std::string urlEncode(const std::string& bytes);
std::string urlDecode(const std::string& bytes);
bool readDir(const std::string &dirName, 
    Ionflux::ObjectBase::StringVector& target, 
	bool prependDirName = false, bool recursive = false);
std::string getCurrentDir();
bool getFileList(const Ionflux::ObjectBase::StringVector& pathList, 
	Ionflux::ObjectBase::StringVector& target, bool recursive = false);

}

}

// Classes


%{
#include "iftemplate/IFTemplateError.hpp"
%}

namespace Ionflux
{

namespace Template
{

class IFTemplateError
: public std::exception
{
    public:
        
        IFTemplateError();
		IFTemplateError(const Ionflux::Template::IFTemplateError& other);
        IFTemplateError(const std::string& initReason);
        virtual ~IFTemplateError() throw();
        virtual std::string getString() const;
        virtual const char* what() const throw();
		virtual Ionflux::Template::IFTemplateError* copy() const;
        virtual void setReason(const std::string& newReason);
        virtual std::string getReason() const;
};

}

}


%{
#include "iftemplate/TokenTypeMap.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TokenTypeMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TokenTypeMapClassInfo();
        virtual ~TokenTypeMapClassInfo();
};

class TokenTypeMap
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const unsigned int TYPE_MAP_SIZE;
        
        TokenTypeMap();
		TokenTypeMap(const Ionflux::Template::TokenTypeMap& other);
        virtual ~TokenTypeMap();
        virtual void addTokenType(const Ionflux::Template::TokenType& 
        newTokenType);
        virtual void removeTokenType(const Ionflux::Template::TokenType& 
        removeTokenType);
        virtual Ionflux::Template::TokenType getTokenType(unsigned char 
        testChar) const;
        virtual void addTokenTypeAnything(const 
        Ionflux::Template::TokenType& newTokenType);
        virtual void clear();
        virtual unsigned int getNumTokenTypes() const;
        virtual std::string getString() const;
		virtual Ionflux::Template::TokenTypeMap* copy() const;
		static Ionflux::Template::TokenTypeMap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::TokenTypeMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}


%{
#include "iftemplate/CharTypeMap.hpp"
%}

namespace Ionflux
{

namespace Template
{

class CharTypeMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CharTypeMapClassInfo();
        virtual ~CharTypeMapClassInfo();
};

class CharTypeMap
: public Ionflux::Template::TokenTypeMap
{
    public:
        
        CharTypeMap();
		CharTypeMap(const Ionflux::Template::CharTypeMap& other);
        virtual ~CharTypeMap();
		virtual Ionflux::Template::CharTypeMap* copy() const;
		static Ionflux::Template::CharTypeMap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::CharTypeMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}


%{
#include "iftemplate/Tokenizer.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TokenTypeMap;

class TokenizerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TokenizerClassInfo();
        virtual ~TokenizerClassInfo();
};

class Tokenizer
: public Ionflux::ObjectBase::IFObject
{
    public:
        Ionflux::Template::TokenType TT_ANYTHING;
        
        Tokenizer();
		Tokenizer(const Ionflux::Template::Tokenizer& other);
        Tokenizer(const std::string& initInput);
        Tokenizer(const Ionflux::Template::TokenTypeVector& 
        initTokenTypes);
        Tokenizer(const Ionflux::Template::TokenTypeVector& initTokenTypes,
        const std::string& initInput);
        virtual ~Tokenizer();
        virtual void clearTokenTypes();
        virtual void useDefaultTokenTypes();
        virtual void setTokenTypes(const 
        Ionflux::Template::TokenTypeVector& newTokenTypes);
        virtual void addTokenType(const Ionflux::Template::TokenType& 
        newTokenType);
        virtual void addTokenTypes(const 
        Ionflux::Template::TokenTypeVector& newTokenTypes);
        virtual void setInput(const std::string& newInput);
        virtual Ionflux::Template::Token getNextToken(const 
        Ionflux::Template::TokenTypeMap& otherMap);
        virtual Ionflux::Template::Token getNextToken();
        virtual Ionflux::Template::Token getCurrentToken();
        virtual Ionflux::Template::TokenTypeID getCurrentTokenType();
        virtual void reset();
        virtual void setTokenTypeAnything();
        virtual void setExtractQuoted(bool newExtractQuoted);
        virtual void setExtractEscaped(bool newExtractEscaped);
        virtual unsigned int getCurrentPos();
        virtual unsigned int getCurrentTokenPos();
        virtual char getQuoteChar();
        virtual std::string getString() const;
		virtual Ionflux::Template::Tokenizer* copy() const;
		static Ionflux::Template::Tokenizer* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::Tokenizer* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setTypeMap(Ionflux::Template::TokenTypeMap* 
        newTypeMap);
        virtual Ionflux::Template::TokenTypeMap* getTypeMap() const;
};

}

}


%{
#include "iftemplate/NodeDump.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Node;

class NodeDumpClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeDumpClassInfo();
        virtual ~NodeDumpClassInfo();
};

class NodeDump
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        NodeDump();
		NodeDump(const Ionflux::Template::NodeDump& other);
        virtual ~NodeDump();
        virtual void dump(Ionflux::Template::Node* node) = 0;
		static Ionflux::Template::NodeDump* upcast(Ionflux::ObjectBase::IFObject*
		other);
};

}

}


%{
#include "iftemplate/Node.hpp"
%}

namespace Ionflux
{

namespace Template
{

class NodeDump;

class NodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeClassInfo();
        virtual ~NodeClassInfo();
};

class Node
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::NodeID ID_NOT_SET;
		static const Ionflux::Template::NodeDataTypeID DATA_BLOB;
		static const Ionflux::Template::NodeDataTypeID DATA_INT;
		static const Ionflux::Template::NodeDataTypeID DATA_DOUBLE;
		static const Ionflux::Template::NodeUIDMode UID_MODE_NONE;
		static const Ionflux::Template::NodeUIDMode UID_MODE_NODE;
		static const Ionflux::Template::NodeUIDMode UID_MODE_TREE;
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_INORDER;
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_PREORDER;
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_POSTORDER;
		static const unsigned int HEADER_SIZE;
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_NONE;
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_NODE;
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_TREE;
		static const unsigned int MAX_ID_INDEX_SIZE;
        
        Node();
		Node(const Ionflux::Template::Node& other);
        Node(Ionflux::Template::Node* initParent);
        Node(Ionflux::Template::Node* initParent, Ionflux::Template::NodeID
        initID, const std::string& initName = "", 
        Ionflux::Template::NodeDataTypeID initDataType = DATA_BLOB);
        virtual ~Node();
        virtual int addData(const std::string& newData);
        virtual int addData(int newData);
        virtual int addData(double newData);
        virtual bool setBlob(unsigned int dataIndex, const std::string& 
        newData);
        virtual bool setData(unsigned int dataIndex, const std::string& 
        newData);
        virtual bool setData(unsigned int dataIndex, int newData);
        virtual bool setData(unsigned int dataIndex, unsigned int newData);
        virtual bool setData(unsigned int dataIndex, double newData);
        virtual bool setData(const std::string& newData);
        virtual bool setData(int newData);
        virtual bool setData(unsigned int newData);
        virtual bool setData(double newData);
        virtual std::string getData(unsigned int dataIndex) const;
        virtual std::string getBlob(unsigned int dataIndex) const;
        virtual int getInt(unsigned int dataIndex) const;
        virtual double getDouble(unsigned int dataIndex) const;
        virtual bool removeData(unsigned int dataIndex);
        virtual bool clearData(bool recursive);
        virtual Ionflux::Template::Node* addChild(Ionflux::Template::NodeID
        childID = ID_NOT_SET, const std::string& childName = "");
        virtual void addChild(Ionflux::Template::Node* newChild);
        virtual Ionflux::Template::Node* findChild(int searchID, bool 
        recursive = false, unsigned int level = 0);
        virtual Ionflux::Template::Node* findChild(const std::string& 
        searchName, bool recursive = false, unsigned int level = 0);
        virtual Ionflux::Template::Node* findChild(int searchID, bool 
        recursive = false) const;
        virtual Ionflux::Template::Node* findChild(const std::string& 
        searchName, bool recursive = false) const;
        virtual Ionflux::Template::Node* getChild(unsigned int childIndex) 
        const;
        virtual bool removeChild(unsigned int childIndex);
        virtual bool removeChild(Ionflux::Template::Node* targetNode, bool 
        recursive = false);
        virtual void removeAllChildren(bool recursive = false);
        virtual bool setChild(unsigned int childIndex, 
        Ionflux::Template::Node* newChild);
        virtual int getChildIndex(Ionflux::Template::Node* targetNode);
        virtual unsigned int printDebugInfo(int targetLevel, int 
        callingLevel, int parentID, int childID);
        virtual unsigned int printDebugInfo(int targetLevel);
        virtual int getUID(bool treeUID);
        virtual void traverse(Ionflux::Template::NodeDump* target, 
        Ionflux::Template::NodeTraversalMode order);
        virtual void serialize(std::string& target);
        virtual bool unpack(const std::string& serialized, unsigned int 
        blockStart, unsigned int blockSize);
        virtual void convertToNativeType();
        virtual void clearNameIndex();
        virtual void clearIDIndex();
        virtual void clearIndexes();
        virtual Ionflux::Template::Node* copy(Ionflux::Template::Node& 
        target, unsigned int maxDepth = 0, unsigned int currentDepth = 0) 
        const;
        virtual std::string getData() const;
        virtual std::string getBlob() const;
        virtual int getInt() const;
        virtual double getDouble() const;
        virtual unsigned int getNumData() const;
        virtual unsigned int getNumChildren(bool recursive = false) const;
        virtual std::string getPath();
        virtual void clear();
        virtual Ionflux::Template::Node& merge(Ionflux::Template::Node& 
        sourceNode, bool replace = false, unsigned int maxDepth = 0, 
        unsigned int currentDepth = 0);
        virtual bool combine(unsigned int from, unsigned int to, 
        Ionflux::Template::Node& target);
        virtual std::string toConfig(const std::string& indent = "  ", 
        unsigned int level = 0);
		virtual Ionflux::Template::Node* copy() const;
		static Ionflux::Template::Node* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::Node* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Template::Node* create(Ionflux::Template::Node* 
		initParent, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::Node* create(Ionflux::Template::Node* 
		initParent, Ionflux::Template::NodeID initID, const std::string& initName
		= "", Ionflux::Template::NodeDataTypeID initDataType = DATA_BLOB, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNodeID(Ionflux::Template::NodeID newNodeID);
        virtual Ionflux::Template::NodeID getNodeID() const;
        virtual void setNodeName(const std::string& newNodeName);
        virtual std::string getNodeName() const;
        virtual void setDataType(Ionflux::Template::NodeDataTypeID 
        newDataType);
        virtual Ionflux::Template::NodeDataTypeID getDataType() const;
        virtual void setParent(Ionflux::Template::Node* newParent);
        virtual Ionflux::Template::Node* getParent() const;
        virtual void setMaxUID(Ionflux::Template::NodeID newMaxUID);
        virtual Ionflux::Template::NodeID getMaxUID() const;
        virtual void setUidMode(Ionflux::Template::NodeUIDMode newUidMode);
        virtual Ionflux::Template::NodeUIDMode getUidMode() const;
        virtual void setAutoCreate(bool newAutoCreate);
        virtual bool getAutoCreate() const;
        virtual void setIndexMode(Ionflux::Template::NodeIndexMode 
        newIndexMode);
        virtual Ionflux::Template::NodeIndexMode getIndexMode() const;
};

}

}


%{
#include "iftemplate/NodeReference.hpp"
%}

namespace Ionflux
{

namespace Template
{

class NodeReferenceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeReferenceClassInfo();
        virtual ~NodeReferenceClassInfo();
};

class NodeReference
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::NodeRefTypeID TYPE_INVALID;
		static const Ionflux::Template::NodeRefTypeID TYPE_NAME;
		static const Ionflux::Template::NodeRefTypeID TYPE_ID;
		static const Ionflux::Template::NodeRefTypeID TYPE_PATH;
		static const Ionflux::Template::NodeRefTypeID TYPE_EMPTY;
        
        NodeReference();
		NodeReference(const Ionflux::Template::NodeReference& other);
        NodeReference(const std::string& refExpr);
        virtual ~NodeReference();
        virtual void clear();
        virtual void setFromRef(const std::string& refExpr);
        virtual bool isSubscript() const;
        virtual std::string getValueString() const;
        virtual void printDebugInfo() const;
		virtual Ionflux::Template::NodeReference* copy() const;
		static Ionflux::Template::NodeReference* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::NodeReference* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setValue(const std::string& newValue);
        virtual std::string getValue() const;
        virtual void setType(Ionflux::Template::NodeRefTypeID newType);
        virtual Ionflux::Template::NodeRefTypeID getType() const;
        virtual void setSubscript(bool newSubscript);
        virtual bool getSubscript() const;
};

}

}


%{
#include "iftemplate/TreeResolver.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Tree;

class TreeResolverClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TreeResolverClassInfo();
        virtual ~TreeResolverClassInfo();
};

class TreeResolver
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_RES_OPERATOR;
		static const Ionflux::Template::TokenType TT_SUB_LEFT;
		static const Ionflux::Template::TokenType TT_SUB_RIGHT;
		static const Ionflux::Template::TokenType TT_RES_PAR_LEFT;
		static const Ionflux::Template::TokenType TT_RES_PAR_RIGHT;
        
        TreeResolver();
		TreeResolver(const Ionflux::Template::TreeResolver& other);
        virtual ~TreeResolver();
        static bool parseTreePath(const std::string& treePathExpr, 
        Ionflux::Template::NodeRefVector& nodeRefs);
        static bool createTreePath(Ionflux::Template::Tree* tree, 
        Ionflux::Template::NodeRefVector& nodeRefs, 
        Ionflux::Template::TreePath& treePath, bool createPath, bool 
        nodesOnly = false);
		virtual Ionflux::Template::TreeResolver* copy() const;
		static Ionflux::Template::TreeResolver* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::TreeResolver* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}


%{
#include "iftemplate/TreeEval.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Tree;
class Node;

class TreeEvalClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TreeEvalClassInfo();
        virtual ~TreeEvalClassInfo();
};

class TreeEval
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_OPERATOR;
		static const Ionflux::Template::TokenType TT_TREEPATH_NP;
		static const Ionflux::Template::TokenType TT_PAR_LEFT;
		static const Ionflux::Template::TokenType TT_PAR_RIGHT;
        
        TreeEval();
		TreeEval(const Ionflux::Template::TreeEval& other);
        virtual ~TreeEval();
        static bool parseTreeExpr(const std::string& treeExpr, 
        Ionflux::Template::TreeExprElementVector& elements);
        static bool eval(Ionflux::Template::Tree* tree, 
        Ionflux::Template::TreeExprElementVector& elements, 
        Ionflux::Template::Node& result, bool createPath);
		virtual Ionflux::Template::TreeEval* copy() const;
		static Ionflux::Template::TreeEval* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Template::TreeEval* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
};

}

}


%{
#include "iftemplate/Tree.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Node;

class TreeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TreeClassInfo();
        virtual ~TreeClassInfo();
};

class Tree
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Tree();
		Tree(const Ionflux::Template::Tree& other);
        Tree(Ionflux::Template::Node* initRoot0);
        virtual ~Tree();
        virtual void initRoot();
        virtual void clear();
        virtual unsigned int getNumNodes();
        virtual Ionflux::Template::Node* findNode(int nodeID);
        virtual Ionflux::Template::Node* findNode(const std::string& 
        nodeName);
        virtual Ionflux::Template::DataEntry resolve(const std::string& 
        treePathExpr, bool createPath = false, bool nodesOnly = false);
        virtual bool eval(const std::string& treeExpr, 
        Ionflux::Template::Node& result, bool createPath);
        virtual void writeToFile(const std::string& fileName);
        virtual void readFromFile(const std::string& fileName);
        virtual void printDebugInfo();
		virtual Ionflux::Template::Tree* copy() const;
		static Ionflux::Template::Tree* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::Tree* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setRoot(Ionflux::Template::Node* newRoot);
        virtual Ionflux::Template::Node* getRoot() const;
};

}

}


%{
#include "iftemplate/Config.hpp"
%}

namespace Ionflux
{

namespace Template
{

class ConfigClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConfigClassInfo();
        virtual ~ConfigClassInfo();
};

class Config
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Config();
		Config(const Ionflux::Template::Config& other);
        virtual ~Config();
        virtual void clear();
        virtual bool readConfig(const std::string& configFile);
        virtual void writeConfig(const std::string& configFile);
        virtual void writeConfig();
        virtual std::string get(const std::string& key);
        virtual void set(const std::string& key, const std::string& value);
		virtual Ionflux::Template::Config* copy() const;
		static Ionflux::Template::Config* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::Config* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}


%{
#include "iftemplate/ConfigTree.hpp"
%}

namespace Ionflux
{

namespace Template
{

class ConfigTreeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConfigTreeClassInfo();
        virtual ~ConfigTreeClassInfo();
};

class ConfigTree
: virtual public Ionflux::Template::Tree, virtual public 
Ionflux::Template::Config, virtual public Ionflux::Template::NodeDump
{
    public:
		static const Ionflux::Template::TokenType TT_COMMENT;
		static const Ionflux::Template::TokenType TT_ASSIGN;
		static const Ionflux::Template::TokenType TT_MULTILINE;
		static const Ionflux::Template::TokenType TT_TREEPATH;
		static const Ionflux::Template::TokenType TT_NESTED_OPEN;
		static const Ionflux::Template::TokenType TT_NESTED_CLOSE;
		static const Ionflux::Template::TokenType TT_VERBATIM_OPEN;
		static const Ionflux::Template::TokenType TT_VERBATIM_CLOSE;
		static const std::string AUTO_INSERT_MARKER;
		static const std::string SPECIAL_VALUE_CHARS;
        
        ConfigTree();
		ConfigTree(const Ionflux::Template::ConfigTree& other);
        virtual ~ConfigTree();
        virtual void clear();
        virtual void parseConfig(const std::string& configData, unsigned 
        int lineOffset = 0);
        virtual bool readConfig(const std::string& configFile);
        virtual void writeConfig(const std::string& configFile);
        virtual void writeConfig();
        virtual std::string get(const std::string& key);
        virtual void set(const std::string& key, const std::string& value);
        virtual void dump(Ionflux::Template::Node* node);
        static std::string escapeValue(const std::string& value);
		virtual Ionflux::Template::ConfigTree* copy() const;
		static Ionflux::Template::ConfigTree* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::ConfigTree* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}


%{
#include "iftemplate/StringManipulator.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringManipulatorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringManipulatorClassInfo();
        virtual ~StringManipulatorClassInfo();
};

class StringManipulator
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        StringManipulator();
		StringManipulator(const Ionflux::Template::StringManipulator::StringManipulator& other);
        virtual ~StringManipulator();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string operator()(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringManipulator* copy() 
		const;
		static Ionflux::Template::StringManipulator::StringManipulator* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringManipulator* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringFilterFunction.hpp"
%}

namespace Ionflux
{

namespace Template
{

class StringFilterFunctionClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringFilterFunctionClassInfo();
        virtual ~StringFilterFunctionClassInfo();
};

class StringFilterFunction
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        StringFilterFunction();
		StringFilterFunction(const Ionflux::Template::StringFilterFunction& other);
        StringFilterFunction(const std::string& initFunc, 
        Ionflux::Template::StringManipulator::StringManipulator* initManip 
        = 0, Ionflux::ObjectBase::StringVector* initArgs = 0);
        virtual ~StringFilterFunction();
        virtual void setArgument(unsigned int index, const std::string& 
        newArg);
		virtual Ionflux::Template::StringFilterFunction* copy() const;
		static Ionflux::Template::StringFilterFunction* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringFilterFunction* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::StringFilterFunction* create(const std::string&
		initFunc, Ionflux::Template::StringManipulator::StringManipulator* 
		initManip = 0, Ionflux::ObjectBase::StringVector* initArgs = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFunc(const std::string& newFunc);
        virtual std::string getFunc() const;        
        virtual unsigned int getNumArguments() const;
        virtual std::string getArgument(unsigned int elementIndex = 0) 
        const;
		virtual int findArgument(const std::string& needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<std::string>& getArguments();
        virtual void addArgument(const std::string& addElement);
		virtual const std::string& addArgument();
		virtual void addArguments(std::vector<std::string>& newArguments);
		virtual void addArguments(Ionflux::Template::StringFilterFunction* 
		newArguments);        
        virtual void removeArgument(const std::string& removeElement);
		virtual void removeArgumentIndex(unsigned int removeIndex);
		virtual void clearArguments();
        virtual void 
        setManip(Ionflux::Template::StringManipulator::StringManipulator* 
        newManip);
        virtual Ionflux::Template::StringManipulator::StringManipulator* 
        getManip() const;
};

}

}


%{
#include "iftemplate/StringFilter.hpp"
%}

namespace Ionflux
{

namespace Template
{

class StringFilterFunction;

class StringFilterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringFilterClassInfo();
        virtual ~StringFilterClassInfo();
};

class StringFilter
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_FUNC_SEP;
		static const Ionflux::Template::TokenType TT_FUNC_BRACKET_LEFT;
		static const Ionflux::Template::TokenType TT_FUNC_BRACKET_RIGHT;
		static const Ionflux::Template::TokenType TT_FUNC_ARG_SEP;
        
        StringFilter();
		StringFilter(const Ionflux::Template::StringFilter& other);
        StringFilter(const std::string& initFilter);
        virtual ~StringFilter();
        virtual void addDefaultManipulators();
        virtual std::string apply(const std::string& bytes);
        virtual void updateIndices();
        virtual void printDebugInfo();
		virtual Ionflux::Template::StringFilter* copy() const;
		static Ionflux::Template::StringFilter* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringFilter* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::StringFilter* create(const std::string& 
		initFilter, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFilter(const std::string& newFilter);
        virtual std::string getFilter() const;        
        virtual unsigned int getNumFunctions() const;
        virtual Ionflux::Template::StringFilterFunction* 
        getFunction(unsigned int elementIndex = 0) const;
		virtual int findFunction(Ionflux::Template::StringFilterFunction* needle,
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::Template::StringFilterFunction*>& 
        getFunctions();
        virtual void addFunction(Ionflux::Template::StringFilterFunction* 
        addElement);        
        virtual void 
        removeFunction(Ionflux::Template::StringFilterFunction* 
        removeElement);
		virtual void removeFunctionIndex(unsigned int removeIndex);
		virtual void clearFunctions();        
        virtual unsigned int getNumManipulators() const;
        virtual Ionflux::Template::StringManipulator::StringManipulator* 
        getManipulator(unsigned int elementIndex = 0) const;
		virtual int 
		findManipulator(Ionflux::Template::StringManipulator::StringManipulator* 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::Template::StringManipulator::StringManipulator*>&
        getManipulators();
        virtual void 
        addManipulator(Ionflux::Template::StringManipulator::StringManipulator*
        addElement);        
        virtual void 
        removeManipulator(Ionflux::Template::StringManipulator::StringManipulator*
        removeElement);
		virtual void removeManipulatorIndex(unsigned int removeIndex);
		virtual void clearManipulators();
};

}

}


%{
#include "iftemplate/Template.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TemplateRepository;

class TemplateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TemplateClassInfo();
        virtual ~TemplateClassInfo();
};

class Template
: public Ionflux::Template::Tree
{
    public:
		static const std::string ITERATION_COUNTER;
		static const std::string NUM_ITERATIONS;
		static const std::string CONDITION_NODE;
		static const Ionflux::Template::TokenType TT_TEMPLATE_TAG_OPEN;
		static const Ionflux::Template::TokenType TT_TEMPLATE_TAG_CLOSE;
		static const Ionflux::Template::TokenType TT_VAR_MARKER;
		static const Ionflux::Template::TokenType TT_COMMENT;
		static const Ionflux::Template::TokenType TT_TREEPATH;
		static const Ionflux::Template::TokenType TT_END_TAG_MARKER;
		static const Ionflux::Template::TokenType TT_OPERATOR_NSO;
		static const std::string TAG_FOREACH;
		static const std::string TAG_FOREACH_ELSE;
		static const std::string TAG_FOREACH_IN;
		static const std::string TAG_IF;
		static const std::string TAG_IF_ELSE;
		static const std::string TAG_FIRST;
		static const std::string TAG_MID;
		static const std::string TAG_LAST;
		static const std::string TAG_SINGLE;
		static const std::string TAG_NOTFIRST;
		static const std::string TAG_NOTMID;
		static const std::string TAG_NOTLAST;
		static const std::string TAG_NOTSINGLE;
		static const std::string TAG_INCLUDE;
		static const std::string TAG_IMPORT;
		static const std::string TAG_SWRAP;
		static const std::string TAG_SECTION;
		static const std::string TAG_REF;
		static const std::string SWRAP_DEFAULT_LINE_WIDTH;
		static const std::string SWRAP_DEFAULT_LINE_TERM;
		static const unsigned int DEFAULT_MAX_NESTING_DEPTH;
        
        Template();
		Template(const Ionflux::Template::Template& other);
        Template(const std::string& templateInput, Ionflux::Template::Node*
        initRoot = 0, Ionflux::Template::TemplateRepository* initRepository
        = 0);
        virtual ~Template();
        virtual void readTemplate(const std::string& templateFileName, 
        Ionflux::Template::TemplateElementVector& target);
        virtual void readTemplate(const std::string& templateFileName);
        virtual void setTemplate(const std::string& newTemplate, 
        Ionflux::Template::TemplateElementVector& target);
        virtual void setTemplate(const std::string& newTemplate);
        virtual void setTemplateModule(const std::string& modulePath, 
        Ionflux::Template::TemplateElementVector& target);
        virtual void setTemplateModule(const std::string& modulePath);
        virtual std::string process(const std::string& newTemplate = "", 
        Ionflux::Template::Node* newConfig = 0);
        virtual std::string processModule(const std::string& modulePath, 
        Ionflux::Template::Node* newConfig = 0);
        virtual void printElementDebugInfo();
		virtual Ionflux::Template::Template* copy() const;
		static Ionflux::Template::Template* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Template::Template* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::Template::Template* create(const std::string& 
		templateInput, Ionflux::Template::Node* initRoot = 0, 
		Ionflux::Template::TemplateRepository* initRepository = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMaxNestingDepth(unsigned int newMaxNestingDepth);
        virtual unsigned int getMaxNestingDepth() const;
        virtual void setRepository(Ionflux::Template::TemplateRepository* 
        newRepository);
        virtual Ionflux::Template::TemplateRepository* getRepository() 
        const;
};

}

}


%{
#include "iftemplate/CLArgs.hpp"
%}

namespace Ionflux
{

namespace Template
{

class CLArgsClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CLArgsClassInfo();
        virtual ~CLArgsClassInfo();
};

class CLArgs
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_OPTION;
		static const Ionflux::Template::TokenType TT_ASSIGN;
		static const Ionflux::Template::CLOption OPTION_NOT_SET;
        
        CLArgs();
		CLArgs(const Ionflux::Template::CLArgs& other);
        CLArgs(int argc, char** argv);
        virtual ~CLArgs();
        virtual void clearAcceptableOptions();
        virtual void clearOptions();
        virtual void clearParams();
        virtual void setArgs(int argc, char** argv);
        virtual void setArgs(const Ionflux::ObjectBase::StringVector& 
        newArgs);
        virtual Ionflux::Template::CLOption* getOption(const std::string& 
        searchOption);
        virtual bool isSet(const std::string& checkOption);
        virtual void getParams(Ionflux::Template::CLParams& target);
        virtual void addAcceptableOption(const std::string& newOption, bool
        newAcceptValue);
        virtual Ionflux::Template::CLAcceptableOption* 
        getAcceptableOption(const std::string& searchOption);
        virtual bool isAcceptable(const std::string& checkOption);
        virtual bool acceptsValue(const std::string& checkOption);
        virtual Ionflux::ObjectBase::StringVector& getInvalidOptions();
        virtual bool optionsOK();
        virtual void printDebugInfo();
		virtual Ionflux::Template::CLArgs* copy() const;
		static Ionflux::Template::CLArgs* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::CLArgs* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setCheckOptions(bool newCheckOptions);
        virtual bool getCheckOptions() const;
};

}

}


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


%{
#include "iftemplate/DateTime.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TimeZone;

class DateTimeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DateTimeClassInfo();
        virtual ~DateTimeClassInfo();
};

class DateTime
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const std::string TIMESTAMP_DATE_SEP;
		static const std::string TIMESTAMP_TIME_SEP;
		static const std::string TIMESTAMP_DATETIME_SEP;
		static const int NUM_DAYS[];
		static const int LEAP_MONTH;
		static const Ionflux::Template::TimeTicks POSIX_EPOCH;
		static const Ionflux::Template::TimeTicks TICKS_400Y;
		static const Ionflux::Template::TimeTicks TICKS_100Y;
		static const Ionflux::Template::TimeTicks TICKS_4Y;
		static const Ionflux::Template::TimeTicks TICKS_3Y;
		static const Ionflux::Template::TimeTicks TICKS_1Y;
		static const Ionflux::Template::TimeTicks TICKS_1D;
		static const Ionflux::Template::TimeTicks REF_SUNDAY;
		static const char* WEEKDAY_NAME[7];
		static const char* WEEKDAY_NAME_SHORT[7];
		static const char* MONTH_NAME[12];
		static const char* MONTH_NAME_SHORT[12];
		static const Ionflux::Template::TimeZone TZ_UTC;
		static const Ionflux::Template::TimeZone TZ_UTC_P0100;
		static const Ionflux::Template::TimeZone TZ_UTC_P0200;
		static const Ionflux::Template::TimeZone TZ_UTC_P0300;
		static const Ionflux::Template::TimeZone TZ_UTC_P0330;
		static const Ionflux::Template::TimeZone TZ_UTC_P0400;
		static const Ionflux::Template::TimeZone TZ_UTC_P0430;
		static const Ionflux::Template::TimeZone TZ_UTC_P0500;
		static const Ionflux::Template::TimeZone TZ_UTC_P0530;
		static const Ionflux::Template::TimeZone TZ_UTC_P0545;
		static const Ionflux::Template::TimeZone TZ_UTC_P0600;
		static const Ionflux::Template::TimeZone TZ_UTC_P0630;
		static const Ionflux::Template::TimeZone TZ_UTC_P0700;
		static const Ionflux::Template::TimeZone TZ_UTC_P0800;
		static const Ionflux::Template::TimeZone TZ_UTC_P0900;
		static const Ionflux::Template::TimeZone TZ_UTC_P0930;
		static const Ionflux::Template::TimeZone TZ_UTC_P1000;
		static const Ionflux::Template::TimeZone TZ_UTC_P1100;
		static const Ionflux::Template::TimeZone TZ_UTC_P1200;
		static const Ionflux::Template::TimeZone TZ_UTC_M0100;
		static const Ionflux::Template::TimeZone TZ_UTC_M0200;
		static const Ionflux::Template::TimeZone TZ_UTC_M0300;
		static const Ionflux::Template::TimeZone TZ_UTC_M0400;
		static const Ionflux::Template::TimeZone TZ_UTC_M0500;
		static const Ionflux::Template::TimeZone TZ_UTC_M0600;
		static const Ionflux::Template::TimeZone TZ_UTC_M0700;
		static const Ionflux::Template::TimeZone TZ_UTC_M0800;
		static const Ionflux::Template::TimeZone TZ_UTC_M0900;
		static const Ionflux::Template::TimeZone TZ_UTC_M1000;
		static const Ionflux::Template::TimeZone TZ_UTC_M1100;
		static const Ionflux::Template::TimeZone TZ_UTC_M1200;
		static const Ionflux::Template::TimeZone TZ_GMT;
		static const Ionflux::Template::TimeZone TZ_EUROPE_WESTERN;
		static const Ionflux::Template::TimeZone TZ_EUROPE_CENTRAL;
		static const Ionflux::Template::TimeZone TZ_EUROPE_EASTERN;
		static const Ionflux::Template::TimeZone TZ_UK;
		static const Ionflux::Template::TimeZone TZ_USA_EASTERN;
		static const Ionflux::Template::TimeZone TZ_USA_CENTRAL;
		static const Ionflux::Template::TimeZone TZ_USA_MOUNTAIN;
		static const Ionflux::Template::TimeZone TZ_USA_PACIFIC;
		static const Ionflux::Template::TimeZone TZ_USA_ALASKA;
		static const Ionflux::Template::TimeZone TZ_RUSSIA_WESTERN;
		static const Ionflux::Template::TimeZone TZ_EGYPT;
        
        DateTime();
		DateTime(const Ionflux::Template::DateTime& other);
        DateTime(Ionflux::Template::TimeTicks initTime);
        DateTime(struct tm initTime);
        DateTime(const std::string& initTime);
        DateTime(Ionflux::Template::Year initYear, int initMonth, int 
        initDay, int initHour, int initMinute, int initSecond);
        virtual ~DateTime();
        virtual void setTimePosix(time_t newTime);
        virtual void setTimeTicks(Ionflux::Template::TimeTicks newTime);
        virtual void setTime(struct tm newTime);
        virtual void setTime(const std::string& newTime);
        virtual void setTime(const Ionflux::Template::DateTime& newTime);
        virtual void setTime(Ionflux::Template::Year newYear, int newMonth,
        int newDay, int newHour, int newMinute, int newSecond);
        virtual void setLocalTime(const Ionflux::Template::DateTime& 
        newTime, bool newDSTState);
        virtual void setLocalTime(const std::string& newTime, bool 
        newDSTState);
        virtual void setLocalTime(Ionflux::Template::Year newYear, int 
        newMonth, int newDay, int newHour, int newMinute, int newSecond, 
        bool newDSTState);
        virtual void setLocalTime(const Ionflux::Template::DateTime& 
        newTime);
        virtual void setLocalTime(const std::string& newTime);
        virtual void setLocalTime(Ionflux::Template::Year newYear, int 
        newMonth, int newDay, int newHour, int newMinute, int newSecond);
        virtual void setHMS(int newHour, int newMinute, int newSecond);
        virtual void setHMS(const std::string& newTime);
        virtual void setHMS(const Ionflux::Template::DateTime& sourceTime);
        virtual void setLocalHMS(int newHour, int newMinute, int newSecond,
        bool newDSTState);
        virtual void setLocalHMS(const std::string& newTime, bool 
        newDSTState);
        virtual void setLocalHMS(const Ionflux::Template::DateTime& 
        sourceTime, bool newDSTState);
        virtual void setLocalHMS(int newHour, int newMinute, int 
        newSecond);
        virtual void setLocalHMS(const std::string& newTime);
        virtual void setLocalHMS(const Ionflux::Template::DateTime& 
        sourceTime);
        virtual Ionflux::Template::DateTime& 
        shift(Ionflux::Template::TimeTicks shiftSeconds);
        virtual Ionflux::Template::TimeTicks diff(const 
        Ionflux::Template::DateTime& diffTime);
        virtual void setTimeZone(const std::string& newTimeZone);
        virtual int compareHMS(int otherHour, int otherMinute, int 
        otherSecond);
        virtual int compareHMS(const Ionflux::Template::DateTime& 
        otherTime);
        virtual int compareHMS(const std::string& otherTime);
        virtual int compareDay(const Ionflux::Template::DateTime& 
        otherTime);
        virtual Ionflux::Template::DateTime getUTC();
        virtual time_t getTimePosix() const;
        virtual std::string getTimestamp();
        virtual std::string getHMS();
        virtual std::string getDayOfWeekName() const;
        virtual std::string getDayOfWeekShortName() const;
        virtual std::string getMonthName() const;
        virtual std::string getMonthShortName() const;
        virtual std::string getTimeZoneName() const;
        virtual std::string getTimeZoneAliases() const;
        virtual bool isDST() const;
        virtual int getUTCOffset() const;
        virtual std::string getRFCTimestamp() const;
        virtual Ionflux::Template::DateTime& 
        operator+=(Ionflux::Template::TimeTicks seconds);
        virtual Ionflux::Template::DateTime& 
        operator-=(Ionflux::Template::TimeTicks seconds);
        virtual Ionflux::Template::TimeTicks operator-(const 
        Ionflux::Template::DateTime& diffTime) const;
        virtual bool operator==(const Ionflux::Template::DateTime& 
        compTime) const;
        virtual bool operator!=(const Ionflux::Template::DateTime& 
        compTime) const;
        virtual bool operator>(const Ionflux::Template::DateTime& compTime)
        const;
        virtual bool operator<(const Ionflux::Template::DateTime& compTime)
        const;
        virtual bool operator>=(const Ionflux::Template::DateTime& 
        compTime) const;
        virtual bool operator<=(const Ionflux::Template::DateTime& 
        compTime) const;
        static Ionflux::Template::Year 
        countLeapYears(Ionflux::Template::Year limit);
        static bool isLeapYear(Ionflux::Template::Year checkYear);
        static Ionflux::Template::DateTime getNth(Ionflux::Template::Year 
        targetYear, int targetMonth, int targetWeekDay, int n);
        static bool isTime(const std::string& checkTime);
        static bool isDate(const std::string& checkDate);
        static bool isDatetime(const std::string& checkDatetime);
		virtual Ionflux::Template::DateTime* copy() const;
		static Ionflux::Template::DateTime* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Template::DateTime* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::Template::DateTime* create(Ionflux::Template::TimeTicks 
		initTime, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::DateTime* create(struct tm initTime, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::DateTime* create(const std::string& initTime, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::DateTime* create(Ionflux::Template::Year 
		initYear, int initMonth, int initDay, int initHour, int initMinute, int 
		initSecond, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual Ionflux::Template::TimeTicks getTicks() const;
        virtual void setTimeZone(Ionflux::Template::TimeZone* newTimeZone);
        virtual Ionflux::Template::TimeZone* getTimeZone() const;
        virtual Ionflux::Template::Year getYear() const;
        virtual int getMonth() const;
        virtual int getDay() const;
        virtual int getHour() const;
        virtual int getMinute() const;
        virtual int getSecond() const;
        virtual int getWeekDay() const;
        virtual int getYearDay() const;
};

}

}


%{
#include "iftemplate/File.hpp"
%}

namespace Ionflux
{

namespace Template
{

class FileClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FileClassInfo();
        virtual ~FileClassInfo();
};

class File
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        File();
		File(const Ionflux::Template::File& other);
        File(const std::string& initFullName);
        virtual ~File();
        virtual void update();
        virtual bool isValid() const;
        virtual bool isDir() const;
        virtual void readDir(bool recursive = false, unsigned int maxDepth 
        = 0, unsigned int depth = 0);
        virtual std::string getValueString() const;
		virtual Ionflux::Template::File* copy() const;
		static Ionflux::Template::File* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::File* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Template::File* create(const std::string& initFullName, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual Ionflux::ObjectBase::UInt64 getFileSize() const;
        virtual time_t getAccessTime() const;
        virtual time_t getModTime() const;
        virtual time_t getChangeTime() const;
        virtual void setName(const std::string& newName);
        virtual std::string getName() const;
        virtual void setPath(const std::string& newPath);
        virtual std::string getPath() const;
        virtual void setFullName(const std::string& newFullName);
        virtual std::string getFullName() const;
        virtual std::string getBaseName() const;
        virtual std::string getExtension() const;        
        virtual unsigned int getNumFiles() const;
        virtual Ionflux::Template::File* getFile(unsigned int elementIndex 
        = 0) const;
		virtual int findFile(Ionflux::Template::File* needle, unsigned int 
		occurence = 1) const;
};

}

}


%{
#include "iftemplate/TemplateRepository.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Node;

class TemplateRepositoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TemplateRepositoryClassInfo();
        virtual ~TemplateRepositoryClassInfo();
};

class TemplateRepository
: public Ionflux::Template::Tree
{
    public:
		static const Ionflux::Template::RepositoryEntryTypeID ENTRY_TYPE_FILE;
		static const Ionflux::Template::RepositoryEntryTypeID ENTRY_TYPE_DATA;
        
        TemplateRepository();
		TemplateRepository(const Ionflux::Template::TemplateRepository& other);
        virtual ~TemplateRepository();
        virtual void addTemplatePaths(const 
        Ionflux::ObjectBase::StringVector& newPaths);
        virtual void addTemplatePaths(const std::string& newPaths, const 
        std::string& separator = DEFAULT_TEMPLATE_PATH_SEP);
        virtual void addModule(const std::string& modulePath, 
        Ionflux::Template::RepositoryEntryTypeID typeID, const std::string&
        data);
        virtual void scanFile(Ionflux::Template::File& file, const 
        std::string& modulePrefix = "", bool addRootModule = false);
        virtual void scanPath(const std::string& dirPath);
        virtual void update();
        virtual void addTemplateData(const std::string& modulePath, const 
        std::string& templateData);
        virtual std::string getTemplateData(const std::string& modulePath, 
        bool removeTrailingNewLine = true);
        static std::string getModulePath(const std::string& modulePrefix, 
        const std::string& moduleName);
		virtual Ionflux::Template::TemplateRepository* copy() const;
		static Ionflux::Template::TemplateRepository* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::TemplateRepository* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumTemplatePaths() const;
        virtual std::string getTemplatePath(unsigned int elementIndex = 0) 
        const;
		virtual int findTemplatePath(const std::string& needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<std::string>& getTemplatePaths();
        virtual void addTemplatePath(const std::string& addElement);        
        virtual void removeTemplatePath(std::string removeElement);
		virtual void removeTemplatePathIndex(unsigned int removeIndex);
		virtual void clearTemplatePaths();
};

}

}


%{
#include "iftemplate/StringTrim.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringTrimClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringTrimClassInfo();
        virtual ~StringTrimClassInfo();
};

class StringTrim
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringTrim();
		StringTrim(const Ionflux::Template::StringManipulator::StringTrim& other);
        virtual ~StringTrim();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringTrim* copy() const;
		static Ionflux::Template::StringManipulator::StringTrim* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringTrim* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringSWrap.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringSWrapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringSWrapClassInfo();
        virtual ~StringSWrapClassInfo();
};

class StringSWrap
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringSWrap();
		StringSWrap(const Ionflux::Template::StringManipulator::StringSWrap& other);
        virtual ~StringSWrap();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringSWrap* copy() const;
		static Ionflux::Template::StringManipulator::StringSWrap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringSWrap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringUppercase.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringUppercaseClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringUppercaseClassInfo();
        virtual ~StringUppercaseClassInfo();
};

class StringUppercase
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringUppercase();
		StringUppercase(const Ionflux::Template::StringManipulator::StringUppercase& other);
        virtual ~StringUppercase();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringUppercase* copy() 
		const;
		static Ionflux::Template::StringManipulator::StringUppercase* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringUppercase* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringLowercase.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringLowercaseClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringLowercaseClassInfo();
        virtual ~StringLowercaseClassInfo();
};

class StringLowercase
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringLowercase();
		StringLowercase(const Ionflux::Template::StringManipulator::StringLowercase& other);
        virtual ~StringLowercase();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringLowercase* copy() 
		const;
		static Ionflux::Template::StringManipulator::StringLowercase* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringLowercase* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringErase.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringEraseClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringEraseClassInfo();
        virtual ~StringEraseClassInfo();
};

class StringErase
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringErase();
		StringErase(const Ionflux::Template::StringManipulator::StringErase& other);
        virtual ~StringErase();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringErase* copy() const;
		static Ionflux::Template::StringManipulator::StringErase* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringErase* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringAppend.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringAppendClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringAppendClassInfo();
        virtual ~StringAppendClassInfo();
};

class StringAppend
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringAppend();
		StringAppend(const Ionflux::Template::StringManipulator::StringAppend& other);
        virtual ~StringAppend();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringAppend* copy() const;
		static Ionflux::Template::StringManipulator::StringAppend* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringAppend* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringInsert.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringInsertClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringInsertClassInfo();
        virtual ~StringInsertClassInfo();
};

class StringInsert
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringInsert();
		StringInsert(const Ionflux::Template::StringManipulator::StringInsert& other);
        virtual ~StringInsert();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringInsert* copy() const;
		static Ionflux::Template::StringManipulator::StringInsert* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringInsert* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringNumFormat.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringNumFormatClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringNumFormatClassInfo();
        virtual ~StringNumFormatClassInfo();
};

class StringNumFormat
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringNumFormat();
		StringNumFormat(const Ionflux::Template::StringManipulator::StringNumFormat& other);
        virtual ~StringNumFormat();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringNumFormat* copy() 
		const;
		static Ionflux::Template::StringManipulator::StringNumFormat* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringNumFormat* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringTranslate.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringTranslateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringTranslateClassInfo();
        virtual ~StringTranslateClassInfo();
};

class StringTranslate
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringTranslate();
		StringTranslate(const Ionflux::Template::StringManipulator::StringTranslate& other);
        virtual ~StringTranslate();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringTranslate* copy() 
		const;
		static Ionflux::Template::StringManipulator::StringTranslate* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringTranslate* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringSubstr.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringSubstrClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringSubstrClassInfo();
        virtual ~StringSubstrClassInfo();
};

class StringSubstr
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringSubstr();
		StringSubstr(const Ionflux::Template::StringManipulator::StringSubstr& other);
        virtual ~StringSubstr();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringSubstr* copy() const;
		static Ionflux::Template::StringManipulator::StringSubstr* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringSubstr* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringRPad.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringRPadClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringRPadClassInfo();
        virtual ~StringRPadClassInfo();
};

class StringRPad
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringRPad();
		StringRPad(const Ionflux::Template::StringManipulator::StringRPad& other);
        virtual ~StringRPad();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringRPad* copy() const;
		static Ionflux::Template::StringManipulator::StringRPad* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringRPad* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringLPad.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringLPadClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringLPadClassInfo();
        virtual ~StringLPadClassInfo();
};

class StringLPad
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringLPad();
		StringLPad(const Ionflux::Template::StringManipulator::StringLPad& other);
        virtual ~StringLPad();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringLPad* copy() const;
		static Ionflux::Template::StringManipulator::StringLPad* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringLPad* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringXMLEscape.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringXMLEscapeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringXMLEscapeClassInfo();
        virtual ~StringXMLEscapeClassInfo();
};

class StringXMLEscape
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringXMLEscape();
		StringXMLEscape(const Ionflux::Template::StringManipulator::StringXMLEscape& other);
        virtual ~StringXMLEscape();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringXMLEscape* copy() 
		const;
		static Ionflux::Template::StringManipulator::StringXMLEscape* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringXMLEscape* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


%{
#include "iftemplate/StringURLEncode.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringURLEncodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringURLEncodeClassInfo();
        virtual ~StringURLEncodeClassInfo();
};

class StringURLEncode
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringURLEncode();
		StringURLEncode(const Ionflux::Template::StringManipulator::StringURLEncode& other);
        virtual ~StringURLEncode();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringURLEncode* copy() 
		const;
		static Ionflux::Template::StringManipulator::StringURLEncode* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringURLEncode* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}


