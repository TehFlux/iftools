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






































