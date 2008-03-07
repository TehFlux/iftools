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
#include "Auth.hpp"
#include "TimeZone.hpp"
#include "DateTime.hpp"
#include "ByteDump.hpp"
#include "Reporter.hpp"
#include "NodeDump.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include "Config.hpp"
#include "ConfigTree.hpp"
#include "Template.hpp"
#include "TCPSocket.hpp"
#include "MessageDump.hpp"
#include "Message.hpp"
#include "MessageHandler.hpp"
#include "TCPRemotePeer.hpp"
#include "IOHandler.hpp"
#include "IOMultiplexer.hpp"
#include "TCPClient.hpp"
#include "MersenneTwister.h"
%}

class MTRand
{
    public:
        typedef unsigned long uint32;
        
        MTRand(const uint32& oneSeed);
        MTRand(uint32* const bigSeed, uint32 const seedLength = 624);
        MTRand();
        double rand();
        double rand(const double& n);
        double randExc();
        double randExc(const double& n);
        double randDblExc();
        double randDblExc(const double& n);
        uint32 randInt();
        uint32 randInt(const uint32& n);
        double rand53();
        double randNorm(const double& mean = 0.0, 
            const double& variance = 0.0 );
        void seed(const uint32 oneSeed);
        void seed(uint32* const bigSeed, const uint32 seedLength = 624);
        void seed();
        void save(uint32* saveArray) const;
        void load(uint32* const loadArray);
};

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

struct AuthData
{
	std::string username;
	std::string password;
	std::string sessionSecret;
};

class Reporter;

class Auth
{
    public:
        Auth();
        virtual ~Auth();
        virtual bool auth(const std::string &username, 
        const std::string &password) = 0;
        virtual void getSecret(const std::string &username, 
            std::string &secret) = 0;
        virtual Reporter &getLog() = 0;
};

class DateTime;

typedef int64_t TimeTicks;
typedef int64_t Year;

struct DSTSwitchingRule
{
	static const int DSR_TYPE_TO_DST;
	static const int DSR_TYPE_TO_NORMAL;
	int type;
	int month;
	int weekDay;
	int week;
	int hour;
	int minute;
	int second;
};

class TimeZone
{
    public:
        static const DSTSwitchingRule DSR_TO_DST_EUROPE_WESTERN;
        static const DSTSwitchingRule DSR_TO_NORMAL_EUROPE_WESTERN;
        static const DSTSwitchingRule DSR_TO_DST_EUROPE_CENTRAL;
        static const DSTSwitchingRule DSR_TO_NORMAL_EUROPE_CENTRAL;
        static const DSTSwitchingRule DSR_TO_DST_EUROPE_EASTERN;
        static const DSTSwitchingRule DSR_TO_NORMAL_EUROPE_EASTERN;
        static const DSTSwitchingRule DSR_TO_DST_USA;
        static const DSTSwitchingRule DSR_TO_NORMAL_USA;
        static const DSTSwitchingRule DSR_TO_DST_EGYPT;
        static const DSTSwitchingRule DSR_TO_NORMAL_EGYPT;
        
        TimeZone();
        TimeZone(int initOffset);
        TimeZone(int initOffset,
            const std::string &initNameNormal, 
            const std::string &initNameDST,
            const std::string &initShortNameNormal, 
            const std::string &initShortNameDST, 
            const std::string &initAliases);
        TimeZone(int initOffset, 
            const DSTSwitchingRule &initToDST, 
            const DSTSwitchingRule &initToNormal);
        TimeZone(int initOffset, 
            const DSTSwitchingRule &initToDST, 
            const DSTSwitchingRule &initToNormal, 
            const std::string &initNameNormal, 
            const std::string &initNameDST,
            const std::string &initShortNameNormal, 
            const std::string &initShortNameDST, 
            const std::string &initAliases);
        virtual ~TimeZone();
        virtual void setOffset(int newOffset);
        virtual void setNameNormal(const std::string &newNameNormal);
        virtual void setNameDST(const std::string &newNameDST);
        virtual void setShortNameNormal(const std::string &newNameNormal);
        virtual void setShortNameDST(const std::string &newNameDST);
        virtual void setAliases(const std::string &newAliases);
        virtual void setDSTRules(const DSTSwitchingRule &newToDST, 
            const DSTSwitchingRule &newToNormal);
        virtual bool isDST(const DateTime &utcDT) const;
        virtual bool localIsDST(const DateTime &localDT) const;
        virtual int getCurrentOffset(const DateTime &utcDT) const;
        virtual const DSTSwitchingRule *getDSTRule(bool ruleFlag) const;
        DateTime getSwitchDT(Year year, const DSTSwitchingRule &rule) const;
        virtual int getOffset() const;
        virtual std::string getNameNormal() const;
        virtual std::string getNameDST() const;
        virtual std::string getShortNameNormal() const;
        virtual std::string getShortNameDST() const;
        virtual std::string getAliases() const;
        virtual bool hasAlias(const std::string &checkAlias) const;
        virtual void enableDST(bool enableFlag);
};

class DateTime
{
    public:
        static const std::string TIMESTAMP_DATE_SEP;
        static const std::string TIMESTAMP_TIME_SEP;
        static const std::string TIMESTAMP_DATETIME_SEP;
        static const int LEAP_MONTH;
        static const TimeTicks POSIX_EPOCH;
        static const TimeTicks TICKS_400Y;
        static const TimeTicks TICKS_100Y;
        static const TimeTicks TICKS_4Y;
        static const TimeTicks TICKS_3Y;
        static const TimeTicks TICKS_1Y;
        static const TimeTicks TICKS_1D;
        static const TimeTicks REF_SUNDAY;
        static const TimeZone TZ_UTC;
        static const TimeZone TZ_UTC_P0100;
        static const TimeZone TZ_UTC_P0200;
        static const TimeZone TZ_UTC_P0300;
        static const TimeZone TZ_UTC_P0330;
        static const TimeZone TZ_UTC_P0400;
        static const TimeZone TZ_UTC_P0430;
        static const TimeZone TZ_UTC_P0500;
        static const TimeZone TZ_UTC_P0530;
        static const TimeZone TZ_UTC_P0545;
        static const TimeZone TZ_UTC_P0600;
        static const TimeZone TZ_UTC_P0630;
        static const TimeZone TZ_UTC_P0700;
        static const TimeZone TZ_UTC_P0800;
        static const TimeZone TZ_UTC_P0900;
        static const TimeZone TZ_UTC_P0930;
        static const TimeZone TZ_UTC_P1000;
        static const TimeZone TZ_UTC_P1100;
        static const TimeZone TZ_UTC_P1200;
        static const TimeZone TZ_UTC_M0100;
        static const TimeZone TZ_UTC_M0200;
        static const TimeZone TZ_UTC_M0300;
        static const TimeZone TZ_UTC_M0400;
        static const TimeZone TZ_UTC_M0500;
        static const TimeZone TZ_UTC_M0600;
        static const TimeZone TZ_UTC_M0700;
        static const TimeZone TZ_UTC_M0800;
        static const TimeZone TZ_UTC_M0900;
        static const TimeZone TZ_UTC_M1000;
        static const TimeZone TZ_UTC_M1100;
        static const TimeZone TZ_UTC_M1200;
        static const TimeZone TZ_GMT;
        static const TimeZone TZ_EUROPE_WESTERN;
        static const TimeZone TZ_EUROPE_CENTRAL;
        static const TimeZone TZ_EUROPE_EASTERN;
        static const TimeZone TZ_UK;
        static const TimeZone TZ_USA_EASTERN;
        static const TimeZone TZ_USA_CENTRAL;
        static const TimeZone TZ_USA_MOUNTAIN;
        static const TimeZone TZ_USA_PACIFIC;
        static const TimeZone TZ_USA_ALASKA;
        static const TimeZone TZ_RUSSIA_WESTERN;
        static const TimeZone TZ_EGYPT;
        
        DateTime();
        DateTime(TimeTicks initTime);
        DateTime(struct tm initTime);
        DateTime(const std::string &initTime);
        DateTime(const DateTime &initTime);
        DateTime(int initYear, int initMonth, int initDay, int initHour, 
            int initMinute, int initSecond);
        virtual ~DateTime();
        virtual void setTimePosix(time_t newTime);
        virtual void setTimeTicks(TimeTicks newTime);
        virtual void setTime(TimeTicks newTime);
        virtual void setTime(tm newTime);
        virtual void setTime(const std::string &newTime);
        virtual void setTime(const DateTime &newTime);
        virtual void setTime(int newYear, int newMonth, int newDay, 
            int newHour, int newMinute, int newSecond);
        virtual void setLocalTime(const DateTime &newTime, bool newDSTState);
        virtual void setLocalTime(const std::string &newTime, bool newDSTState);
        virtual void setLocalTime(int newYear, int newMonth, int newDay, 
            int newHour, int newMinute, int newSecond, bool newDSTState);
        virtual void setLocalTime(const DateTime &newTime);
        virtual void setLocalTime(const std::string &newTime);
        virtual void setLocalTime(int newYear, int newMonth, int newDay, 
            int newHour, int newMinute, int newSecond);
        virtual void setHMS(int newHour, int newMinute, int newSecond);
        virtual void setHMS(const std::string &newTime);
        virtual void setHMS(const DateTime &sourceTime);
        virtual void setLocalHMS(int newHour, int newMinute, int newSecond, 
            bool newDSTState);
        virtual void setLocalHMS(const std::string &newTime, bool newDSTState);
        virtual void setLocalHMS(const DateTime &sourceTime, bool newDSTState);
        virtual void setLocalHMS(int newHour, int newMinute, int newSecond);
        virtual void setLocalHMS(const std::string &newTime);
        virtual void setLocalHMS(const DateTime &sourceTime);
        static void makeBrokenTime(time_t *source, tm *target);
        static Year countLeapYears(Year limit);
        static bool isLeapYear(Year checkYear);
        static DateTime getNth(Year targetYear, int targetMonth, 
            int targetWeekDay, int n);
        virtual DateTime &shift(int shiftSeconds);
        virtual TimeTicks diff(const DateTime &diffTime) const;
        virtual void setTimeZone(const TimeZone *newTimeZone, bool newManage);
        virtual void setTimeZone(const std::string &newTimeZone);
        virtual int compareHMS(int otherHour, int otherMinute, int otherSecond);
        virtual int compareHMS(const DateTime &otherTime);
        virtual int compareHMS(const std::string &otherTime);
        virtual int compareDay(const DateTime &otherTime);
        static bool isTime(const std::string &checkTime);
        static bool isDate(const std::string &checkDate);
        static bool isDatetime(const std::string &checkDatetime);
        virtual DateTime getUTC();
        virtual TimeTicks getTicks() const;
        virtual time_t getTime() const;
        virtual tm getBrokenTime() const;
        virtual std::string getTimestamp();
        virtual std::string getHMS();
        virtual Year getYear() const;
        virtual int getMonth() const;
        virtual int getDay() const;
        virtual int getHour() const;
        virtual int getMinute() const;
        virtual int getSecond() const;
        virtual int getDayOfWeek() const;
        virtual int getDayOfYear() const;
        virtual std::string getDayOfWeekName() const;
        virtual std::string getDayOfWeekShortName() const;
        virtual std::string getMonthName() const;
        virtual std::string getMonthShortName() const;
        virtual const TimeZone *getTimeZone() const;
        virtual std::string getTimeZoneName() const;
        virtual std::string getTimeZoneAliases() const;
        virtual bool isDST() const;
        virtual int getUTCOffset() const;
        virtual std::string getRFCTimestamp() const;
        virtual DateTime& operator+=(TimeTicks seconds);
        virtual DateTime& operator-=(TimeTicks seconds);
        virtual TimeTicks operator-(const DateTime &diffTime) const;
        virtual bool operator==(const DateTime &compTime) const;
        virtual bool operator>(const DateTime &compTime) const;
        virtual bool operator<(const DateTime &compTime) const;
        virtual bool operator>=(const DateTime &compTime) const;
        virtual bool operator<=(const DateTime &compTime) const;
};

class ByteDump
{
    public:
        virtual ~ByteDump();
        virtual void dump(const std::string &bytes) = 0;
};

class Node;

class Reporter
{
    public:
        static const std::string DEFAULT_LOGFILE_SUFFIX;
        static const std::string DEFAULT_LOG_PATH;
        static const int VL_ASSERT; 
        static const int VL_NONE; 
        static const int VL_ERROR_CRIT;
        static const int VL_ERROR;
        static const int VL_WARNING;
        static const int VL_WARNING_OPT;
        static const int VL_INFO;
        static const int VL_INFO_OPT;
        static const int VL_DEBUG;
        static const int VL_DEBUG_OPT;
        static const int VL_DEBUG_INSANE;
        static const int VL_ALL;
        
        Reporter();
        Reporter(int initVerbosityLevel, int initLogLevel, 
            const std::string& initLogPath, const std::string& initLogPrefix, 
            const std::string& initLogSuffix, bool initConsoleTimestamp[], 
            bool initLogTimestamp[]);
        virtual ~Reporter();
        virtual void setConfig(Node &config);
        virtual void setVerbosityLevel(int level);
        virtual int getVerbosityLevel();
        virtual void setLogLevel(int level);
        virtual int getLogLevel();
        virtual void setLogFilePath(const std::string &path);
        virtual std::string getLogFilePath();
        virtual void setLogFilePrefix(const std::string &prefix);
        virtual std::string getLogFilePrefix();
        virtual void setLogFileSuffix(const std::string &suffix);
        virtual std::string getLogFileSuffix();
        virtual void setTimestamps(bool console[], bool log[]);
        virtual void msg(const std::string& message, int level);
        virtual void msg(const std::string& message, int level, bool lineTerm);
        virtual void msg(const std::string& message, int level, bool lineTerm, 
            bool timeStamp);
        // virtual bool assert(bool assertExpr, const std::string& message);
        static std::string createTimestamp(bool useDate, bool useTime, 
            const std::string& dateSep, const std::string& dateTimeSep, 
            const std::string& timeSep, DateTime &dt);
        virtual void writeLogMessage(const std::string& fileName, 
            const std::string& message);
        virtual int getLevel(const std::string& level);
        virtual void setAddLineTerm(bool status);
        virtual void redirect(Reporter *newTarget);
        virtual void setDump(ByteDump *newDump);
        virtual void setCompressLogs(bool newCompressLogs);
        virtual bool getCompressLogs();
};

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

class TCPSocket
{
    public:
        static const int READ_BUFFER_SIZE;
        static const int DEFAULT_LISTEN_QUEUE;
        
        TCPSocket();
        TCPSocket(int initPort);
        TCPSocket(const std::string& initHost, int initPort);
        virtual ~TCPSocket();
        virtual bool resolve();
        virtual bool connect();
        virtual void close();
        virtual bool bind();
        virtual bool bind(unsigned int newAddress);
        virtual bool listen();
        virtual int accept(sockaddr_in &newAddr, socklen_t &newAddrSize);
        virtual bool accept(TCPSocket &newClientSocket);
        virtual bool readBytes(std::string& bytes);
        virtual bool sendBytes(const std::string& bytes);
        virtual void setRemoteHost(const std::string& newHost);
        virtual void setPort(int newPort);
        virtual void setListenQueue(int newListenQueue);
        virtual void setFD(int newFD);
        virtual void setConnectionState(bool newConnectionState);
        virtual void setBindingState(bool newBindingState);
        virtual void setListeningState(bool newListeningState);
        virtual void setClientIP(const std::string &newClientIP);
        virtual int getPort();
        virtual std::string getRemoteHost();
        virtual int getFD();
        virtual bool isConnected();
        virtual int getListenQueue();
        virtual bool isBound();
        virtual bool isListening();
        virtual std::string getClientIP();
        virtual Reporter &getLog();
};

class Message;

class MessageDump
{
    public:
        virtual ~MessageDump();
        virtual void dump(Message &msg) = 0;
};

class Message
: public Tree
{
	public:
        static const std::string DEFAULT_MAGIC_WORD;
        static const int DEFAULT_PROTOCOL_VERSION;
        static const int UID_NOT_SET;
        static const int TYPE_NOT_SET;
        static const int FLAG_COMPRESS;
        static const int HEADER_SIZE;
        static const unsigned int DEFAULT_MAX_SIZE;
        
        Message();
        virtual ~Message();
        virtual void clearData();
        virtual void clearAll();
        virtual void serialize(std::string &buffer);
        virtual bool append(const std::string& bytes);
        virtual void dump(const std::string& bytes);
        virtual void setMagicWord(const std::string &newMagicWord);
        virtual void setProtocolVersion(int newProtocolVersion);
        virtual void setAcceptableProtocolVersion(int newProtocolVersionLower, 
            int newProtocolVersionUpper);
        virtual void setUID(int newUID);
        virtual void setType(int newType);
        virtual void setFlags(unsigned int newFlags);
        virtual void setUsername(const std::string &newUsername);
        virtual void setUserSecret(const std::string &newUserSecret);
        virtual void setSessionSecret(const std::string &newSessionSecret);
        virtual void setTarget(MessageDump *newTarget);
        virtual void setMaxSize(unsigned int newMaxSize);
        virtual std::string getMagicWord();
        virtual int getProtocolVersion();
        virtual int getUID();
        virtual int getType();
        virtual unsigned int getFlags();
        virtual unsigned int getSize();
        virtual std::string getUsername();
        virtual void getUserSecret(std::string &userSecretBuffer);
        virtual void getSessionSecret(std::string &sessionSecretBuffer);
        virtual unsigned int getNumBytesMissing();
        virtual unsigned int getMaxSize();
};

class TCPRemotePeer;

class MessageHandler
{
    public:
        virtual ~MessageHandler();
        virtual void onMessage(TCPRemotePeer &peer) = 0;
        virtual void onInvalidMessage(TCPRemotePeer &peer) = 0;
};

class TCPRemotePeer
: public MessageDump
{
    public:
        static const int ID_NOT_SET;
        static const int PROTOCOL_STATE_UNDEFINED;
        
        TCPRemotePeer();
        TCPRemotePeer(int initID);
        virtual ~TCPRemotePeer();
        virtual bool receive();
        virtual bool send(const std::string &bytes);
        virtual void setID(int newID);
        virtual void setProtocolState(int newProtocolState);
        virtual void setMessageHandler(MessageHandler *newMessageHandler);
        virtual int getID();
        virtual TCPSocket &getSocket();
        virtual AuthData &getAuthData();
        virtual std::string &getRecvBuf();
        virtual unsigned int removeRecvBytes(unsigned int numBytes);
        virtual void clearRecvBuf();
        virtual int getProtocolState();
        virtual void* getData();
        virtual unsigned int getDataSize();
        virtual Message* getMessage();
        virtual Node* getCache();
        virtual void dump(Message &msg);
};

struct IOEvent
{
	static const int IO_READ;
	static const int IO_WRITE;
	static const int IO_EXCEPT;
    
	IOEvent();
	int fd;
	int type;
	void* data;
	TCPRemotePeer *peer;
};

class IOHandler
{
    public:
        virtual ~IOHandler();
        virtual void onIO(const IOEvent &event) = 0;
};

struct IOEventInfo
{
	IOEvent event;
	IOHandler *handler;
};

class IOMultiplexer
{
    public:
        static const int IOM_TYPE_UNDEFINED;
        static const int IOM_TYPE_SELECT;
        static const int IOM_TYPE_GLIB;
        
        virtual ~IOMultiplexer();
        virtual void registerEvent(IOHandler *handler, IOEvent event) = 0;
        virtual void removeEvent(IOHandler *handler, IOEvent event) = 0;
        virtual void run() = 0;
        virtual void quit() = 0;
        virtual bool isRunning() = 0;
        virtual int getType();
        static void shutdownHandler(int signum);
        virtual Reporter &getLog() = 0;
};

class TCPClient
: public IOHandler
{
	public:
		TCPClient();
		TCPClient(bool initInteractive);
		TCPClient(bool initInteractive, IOMultiplexer *initIomp);
		virtual ~TCPClient();
		virtual void onInput(const std::string &line);
		virtual void run();
		virtual void cleanup();
		virtual bool addConnection(const std::string &host, int port);
		virtual void broadcast(const std::string &bytes);
		virtual void onIO(const IOEvent &event);
		static void shutdownHandler(int signum);
		virtual Reporter &getLog();

};

}

}
