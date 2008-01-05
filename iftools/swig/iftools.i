%include <std_string.i>
%include <std_map.i>
%include <std_vector.i>
%module IFTools
%{
#include "ClassInfo.hpp"
#include "Object.hpp"
#include "ManagedObject.hpp"
#include "Utf8TokenTypeMap.hpp"
#include "Utf8Tokenizer.hpp"
#include "NodeDump.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include "Config.hpp"
#include "ConfigTree.hpp"
#include "Template.hpp"
%}

namespace Ionflux
{

namespace Tools
{

class ClassInfo
{
	public:
		ClassInfo();
		virtual ~ClassInfo();
		virtual std::string getName() const;
		virtual std::string getDesc() const;
};

class ObjectClassInfo
: public ClassInfo
{
	public:
		ObjectClassInfo();
		virtual ~ObjectClassInfo();
};

class Object
{
	public:
		Object();
		virtual ~Object();
		virtual const ClassInfo* getClass() const;
		virtual std::string getClassName() const;
		virtual std::string getClassDesc() const;
};

class ManagedObjectClassInfo
: public ClassInfo
{
	public:
		ManagedObjectClassInfo();
		virtual ~ManagedObjectClassInfo();
};

class ManagedObject
: public Ionflux::Tools::Object
{
	public:
		ManagedObject();
		virtual ~ManagedObject();
		virtual bool setManaged(bool newManage);
		virtual bool isManaged();
		virtual unsigned int ref();
		virtual unsigned int unref();
		virtual unsigned int getRefCount();
};

struct Utf8TokenType;

typedef std::map<unsigned int, Ionflux::Tools::Utf8TokenType*> ImplTokenTypeMap;

struct Utf8TokenType
{
	int typeID;
	std::string validChars;
	unsigned int maxChars;
	static const int USERTYPE_ID;
	static const int INVALID_ID;
	static const int EMPTY_ID;
};

class Utf8TokenTypeMapClassInfo
: public Ionflux::Tools::ClassInfo
{
	public:
		Utf8TokenTypeMapClassInfo();
		virtual ~Utf8TokenTypeMapClassInfo();
};

class Utf8TokenTypeMap
: public Ionflux::Tools::ManagedObject
{
	public:
		Utf8TokenTypeMap();
		virtual ~Utf8TokenTypeMap();
		virtual void clear();
		virtual unsigned int getNumTokenTypes();
		virtual void addTokenType(const Utf8TokenType& newTokenType);
		virtual void removeTokenType(const Utf8TokenType& removeTokenType);
		virtual void setDefaultTokenType(const Utf8TokenType& 
		newDefaultTokenType);
		virtual Utf8TokenType getTokenType(unsigned int testChar);
		static bool isValid(const Utf8TokenType& checkTokenType);
};

struct Utf8Token
{
	int typeID;
	std::string value;
};

class Utf8TokenizerClassInfo
: public Ionflux::Tools::ClassInfo
{
	public:
		Utf8TokenizerClassInfo();
		virtual ~Utf8TokenizerClassInfo();
};

class Utf8Tokenizer
: public Ionflux::Tools::ManagedObject
{
	public:
		static const Utf8TokenType TT_INVALID;
		static const Utf8TokenType TT_NONE;
		static const Utf8TokenType TT_DEFAULT;
		static const Utf8TokenType TT_QUOTED;
		static const Utf8TokenType TT_ESCAPED;
		static const Utf8TokenType TT_LINEAR_WHITESPACE;
		static const Utf8TokenType TT_LINETERM;
		static const Utf8TokenType TT_IDENTIFIER;
		static const Utf8TokenType TT_NUMBER;
		static const Utf8TokenType TT_ALPHA;
		static const Utf8TokenType TT_DEFAULT_SEP;
		static const Utf8TokenType TT_LATIN;
		static const Utf8Token TOK_INVALID;
		static const Utf8Token TOK_NONE;
		static const std::string QUOTE_CHARS;
		static const unsigned int ESCAPE_CHAR;
		
		Utf8Tokenizer();
		Utf8Tokenizer(const std::string& initInput);
		Utf8Tokenizer(const std::vector<Utf8TokenType>& initTokenTypes, const 
		std::string& initInput = "");
		virtual ~Utf8Tokenizer();
		virtual void reset();
		virtual void clearTokenTypes();
		virtual void useDefaultTokenTypes();
		virtual void addDefaultTokenType();
		virtual void setTokenTypes(const std::vector<Utf8TokenType>& 
		newTokenTypes);
		virtual void addTokenTypes(const std::vector<Utf8TokenType>& 
		newTokenTypes);
		virtual void addTokenType(const Utf8TokenType& newTokenType);
		virtual void setInput(const std::string& newInput);
		virtual void setInput(const std::vector<unsigned int>& newInput);
		virtual Utf8Token getNextToken(Utf8TokenTypeMap* otherTypeMap = 0);
		virtual Utf8Token getCurrentToken();
		virtual int getCurrentTokenType();
		virtual unsigned int getCurrentPos();
		virtual unsigned int getCurrentTokenPos();
		virtual unsigned int getQuoteChar();
		static bool isValid(const Utf8Token& checkToken);
		virtual void setExtractQuoted(bool newExtractQuoted);
		virtual bool getExtractQuoted() const;
		virtual void setExtractEscaped(bool newExtractEscaped);
		virtual bool getExtractEscaped() const;
};

class Node;

class NodeDump
{
	public:
		virtual ~NodeDump();
		virtual void dump(Node *node) = 0;
};

class Node
{
	public:
		static const int NODE_ID_NOT_SET;
		static const int NODE_DATA_BLOB;
		static const int NODE_DATA_INT;
		static const int NODE_DATA_DOUBLE;
		static const int UID_MODE_NONE;
		static const int UID_MODE_NODE;
		static const int UID_MODE_TREE;
		static const int TRAVERSAL_INORDER;
		static const int TRAVERSAL_PREORDER;
		static const int TRAVERSAL_POSTORDER;
		static const unsigned int NODE_HEADER_SIZE;
		static const int INDEX_MODE_NONE;
		static const int INDEX_MODE_NODE;
		static const int INDEX_MODE_TREE;
		static const unsigned int MAX_ID_INDEX_SIZE;
		
		Node();
		Node(Node &sourceNode);
		Node(Node *initParent, int initID);
		Node(Node *initParent, int initID, const std::string &initName);
		Node(Node *initParent, int initID, const std::string &initName, 
			int initDataType);
		Node(Node *initParent, int initID, const std::string &initName, 
			int initDataType, bool initManaged);
		virtual ~Node();
		virtual void setID(int newID);
		virtual void setName(const std::string &newName);
		virtual void setParent(Node *newParent);
		virtual void setDataType(int newDataType);
		virtual int addData(const std::string &newData);
		virtual int addData(int newData);
		virtual int addData(double newData);
		virtual bool setBlob(unsigned int dataIndex, 
			const std::string &newData);
		virtual bool setData(unsigned int dataIndex, 
			const std::string &newData);
		virtual bool setData(unsigned int dataIndex, int newData);
		virtual bool setData(unsigned int dataIndex, unsigned int newData);
		virtual bool setData(unsigned int dataIndex, double newData);
		virtual bool setData(const std::string &newData);
		virtual bool setData(int newData);
		virtual bool setData(unsigned int newData);
		virtual bool setData(double newData);
		virtual std::string getData(unsigned int dataIndex);
		virtual std::string getBlob(unsigned int dataIndex);
		virtual int getInt(unsigned int dataIndex);
		virtual double getDouble(unsigned int dataIndex);
		virtual bool removeData(unsigned int dataIndex);
		virtual void clearData(bool recursive);
		virtual Node *addChild(int childID = NODE_ID_NOT_SET, 
			const std::string& childName = "");
		virtual void addChild(Node *newChild, bool newManage);
		virtual Node *findChild(int searchID, bool recursive = false);
		virtual Node *findChild(const std::string &searchName, 
			bool recursive = false);
		virtual Node *getChild(unsigned int childIndex);
		virtual unsigned int getNumChildren(bool recursive);
		virtual bool removeChild(unsigned int childIndex);
		virtual bool removeChild(Node *targetNode, bool recursive);
		virtual void removeAllChildren(bool recursive);
		virtual bool setChild(unsigned int childIndex, Node *newChild, 
			bool newManage);
		virtual void removeManagedChildren();
		virtual int getChildIndex(Node *targetNode);
		virtual unsigned int printDebugInfo(int targetLevel, int callingLevel, 
			int parentID, int childID);
		virtual unsigned int printDebugInfo(int targetLevel);
		virtual int getUID(bool treeUID);
		virtual void setUIDMode(int newUIDMode);
		virtual void setAutoCreate(bool newAutoCreate);
		virtual void setIndexMode(int newIndexMode);
		virtual void traverse(NodeDump *target, int order);
		virtual void serialize(std::string &target);
		virtual bool unpack(const std::string &serialized, 
			unsigned int blockStart, unsigned int blockSize);
		virtual void convertToNativeType();
		virtual void clearNameIndex();
		virtual void clearIDIndex();
		virtual void clearIndexes();
		virtual void copy(Ionflux::Tools::Node& target, 
			unsigned int maxDepth = 0, unsigned int currentDepth = 0);
		virtual bool getAutoCreate();
		virtual int getUIDMode();
		virtual int getIndexMode();
		virtual int getID();
		virtual std::string getName();
		virtual int getDataType();
		virtual std::string getData();
		virtual std::string getBlob();
		virtual int getInt();
		virtual double getDouble();
		virtual unsigned int getNumData();
		virtual unsigned int getNumChildren();
		virtual Node *getParent();
		virtual std::string getPath();
		virtual void clear();
		virtual Node& merge(Node &sourceNode, bool replace = false, 
			unsigned int maxDepth = 0, unsigned int currentDepth = 0);
		bool combine(unsigned int from, unsigned int to, Node &target);
		std::string toConfig(const std::string& indent = "", 
			unsigned int level = 0);
		void setManaged(bool newManaged);
		bool isManaged();
		// virtual Reporter &getLog();
};

class Tree;

struct DataEntry
{
	Node *node;
	unsigned int index;
	bool subscript;
};

struct TreePath
{
	Tree *tree;
	std::vector<Node *> nodes;
	int subscript;
	bool explicitSubscript;
};

struct TreeExprElement
{
	int type;
	std::string value;
	DataEntry data;
	bool unary;
	static const int TE_INVALID;
	static const int TE_CONST;
	static const int TE_VAR;
	static const int TE_OP;
};

class Tree
{
	public:
		Tree();
		Tree(Node *initRoot, bool initManage);
		virtual ~Tree();
		virtual Node *findNode(int nodeID);
		virtual Node *findNode(const std::string &nodeName);
		virtual DataEntry resolve(const std::string &treePathExpr, 
			bool createPath, bool nodesOnly = false);
		virtual void setRoot(Node *newRoot, bool newManage);
		virtual void writeToFile(const std::string &fileName);
		virtual void readFromFile(const std::string &fileName);
		virtual bool eval(const std::string &treeExpr, Node &result, 
			bool createPath);
		virtual void printDebugInfo();
		virtual Node *getRoot();
		virtual int getNumNodes();
		virtual void clear();
		// virtual Reporter &getLog();
};

struct ConfigOption
{
	std::string key;
	std::string value;
};

struct ConfigLine
{
	ConfigOption option;
	int type;
	static const int CL_INVALID;
	static const int CL_OPTION;
	static const int CL_COMMENT;
	static const int CL_BLANK;
	static const int CL_NESTED;
	static const int CL_ROOT_DATA;
};

class Config
{
	public:
		Config();
		virtual ~Config();
		virtual void clear() = 0;
		virtual void readConfig(const std::string& configFile) = 0;
		virtual void writeConfig(const std::string& configFile) = 0;
		virtual void writeConfig() = 0;
		virtual std::string get(const std::string& key) = 0;
		virtual void set(const std::string& key, const std::string& value) = 0;
};

struct ConfigTreeEntry
{
	ConfigLine line;
	DataEntry data;
};

class ConfigTree
: public Tree, public Config, public NodeDump
{
	public:
		static const TokenType TT_COMMENT;
		static const TokenType TT_ASSIGN;
		static const TokenType TT_MULTILINE;
		static const TokenType TT_TREEPATH;
		static const TokenType TT_NESTED_OPEN;
		static const TokenType TT_NESTED_CLOSE;
		static const std::string AUTO_INSERT_MARKER;
		static const std::string SPECIAL_VALUE_CHARS;
		
		ConfigTree();
		virtual ~ConfigTree();
		virtual void clear();
		virtual void parseConfig(const std::string& configData);
		virtual void readConfig(const std::string& configFile);
		virtual void writeConfig(const std::string& configFile);
		virtual void writeConfig();
		virtual std::string get(const std::string& key);
		virtual void set(const std::string& key, const std::string& value);
		virtual void dump(Node *node);
		static std::string escapeValue(const std::string& value);
};

class Template
: public Tree
{
	public:
		Template();
		virtual ~Template();
		virtual void readTemplate(const std::string& templateFileName);
		virtual void setTemplate(const std::string& newTemplate);
		virtual std::string process(const std::string& newTemplate = "",
			Node* newConfig = 0);
		virtual void setMaxNestingDepth(unsigned int newMaxNestingDepth);
		virtual unsigned int getMaxNestingDepth();
};

}

}
