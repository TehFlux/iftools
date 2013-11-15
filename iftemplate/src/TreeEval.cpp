/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeEval.cpp                    Tree expression evaluator 
 * (implementation).
 * =========================================================================
 * 
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

#include "iftemplate/TreeEval.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stack>
#include "ifobject/utils.hpp"
#include "iftemplate/IFTemplateError.hpp"
#include "iftemplate/constants.hpp"
#include "iftemplate/Tree.hpp"
#include "iftemplate/Node.hpp"
#include "iftemplate/Tokenizer.hpp"
#include "iftemplate/utils.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

TreeEvalClassInfo::TreeEvalClassInfo()
{
	name = "TreeEval";
	desc = "Tree expression evaluator";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TreeEvalClassInfo::~TreeEvalClassInfo()
{
}

// public member constants
const Ionflux::Template::TokenType TreeEval::TT_OPERATOR = { TT_ID_USERTYPE + 201, "+-*/=<>&|!~%^", false, 0 };
const Ionflux::Template::TokenType TreeEval::TT_TREEPATH_NP = { TT_ID_USERTYPE + 202, ".[]", false, 0 };
const Ionflux::Template::TokenType TreeEval::TT_PAR_LEFT = { TT_ID_USERTYPE + 203, "(", false, 1 };
const Ionflux::Template::TokenType TreeEval::TT_PAR_RIGHT = { TT_ID_USERTYPE + 204, ")", false, 1 };

// run-time type information instance constants
const TreeEvalClassInfo TreeEval::treeEvalClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TreeEval::CLASS_INFO = &TreeEval::treeEvalClassInfo;

TreeEval::TreeEval()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TreeEval::TreeEval(const Ionflux::Template::TreeEval& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TreeEval::~TreeEval()
{
	// TODO: Nothing ATM. ;-)
}

bool TreeEval::calculate(Ionflux::Template::DataEntry& op1, 
Ionflux::Template::DataEntry& result, const std::string& op)
{
	if ((op1.node == 0) || (result.node == 0))
	    throw IFTemplateError("[TreeEval::calculate] "
	        "One of the nodes is null.");
	// Convert operand to its native data type.
	Node opConv1;
	opConv1.setAutoCreate(true);
	opConv1.setDataType(op1.node->getDataType());
	opConv1.setBlob(0, op1.node->getBlob(op1.index));
	opConv1.convertToNativeType();
	if (opConv1.getDataType() == Node::DATA_INT)
	{
	    result.node->setDataType(Node::DATA_INT);
	    int resInt = opConv1.getInt();
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Applying UNARY operator " << op 
	        << " to INT " << resInt << "." << endl;
	    // ----- DEBUG ----- */
	    if (op == "++")
	        resInt++;
	    else
	    if (op == "--")
	        resInt--;
	    else
	    if (op == "~")
	        resInt = ~resInt;
	    else
	    if (op == "!")
	        resInt = !resInt;
	    else
	    if (op == "-")
	        resInt = -resInt;
	    else
	    {
	        // <---- DEBUG ----- //
	        std::cout << "[TreeEval::calculate] WARNING: Operator '" << op 
	            << "' not implemented for type INT." << std::endl;
	        // ----- DEBUG ----> */
	    }
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Setting result to " << resInt 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    result.node->setData(0, resInt);
	} else
	if (opConv1.getDataType() == Node::DATA_DOUBLE)
	{
	    result.node->setDataType(Node::DATA_DOUBLE);
	    double resDouble = opConv1.getDouble();
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Applying UNARY operator " << op 
	        << " to DOUBLE " << resDouble << "." << endl;
	    // ----- DEBUG ----- */
	    if (op == "++")
	        resDouble++;
	    else
	    if (op == "--")
	        resDouble--;
	    else
	    if (op == "!")
	        resDouble = !resDouble;
	    else
	    if (op == "-")
	        resDouble = -resDouble;
	    else
	    {
	        // <---- DEBUG ----- //
	        std::cout << "[TreeEval::calculate] WARNING: Operator '" << op 
	        << "' not implemented for type DOUBLE." << std::endl;
	        // ----- DEBUG ----> */
	    }
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Setting result to " << resDouble 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    result.node->setData(0, resDouble);
	} else
	{
	    result.node->setDataType(Node::DATA_BLOB);
	    string resBlob = opConv1.getBlob();
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Applying UNARY operator " << op 
	        << " to BLOB " << resBlob << "." << endl;
	    // ----- DEBUG ----- */
	    if (op == "~")
	        for (unsigned int i = 0; i < resBlob.size(); i++)
	            resBlob[i] = ~resBlob[i];
	    else
	    {
	        // <---- DEBUG ----- //
	        std::cout << "[TreeEval::calculate] WARNING: Operator '" << op 
	        << "' not implemented for type BLOB." << std::endl;
	        // ----- DEBUG ----> */
	    }
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Setting result to " << resBlob 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    result.node->setData(0, resBlob);
	}
	return true;
}

bool TreeEval::calculate(Ionflux::Template::DataEntry& op1, 
Ionflux::Template::DataEntry& op2, Ionflux::Template::DataEntry& result, 
const std::string& op)
{
	if ((op1.node == 0) || (op2.node == 0) || (result.node == 0))
	    throw IFTemplateError("[TreeEval::calculate] "
	        "One of the nodes is null.");
	// Convert operands to their native data types.
	Node opConv1;
	opConv1.setAutoCreate(true);
	opConv1.setDataType(op1.node->getDataType());
	opConv1.setBlob(0, op1.node->getBlob(op1.index));
	opConv1.convertToNativeType();
	Node opConv2;
	opConv2.setAutoCreate(true);
	opConv2.setDataType(op2.node->getDataType());
	opConv2.setBlob(0, op2.node->getBlob(op2.index));
	opConv2.convertToNativeType();
	if ((opConv1.getDataType() == Node::DATA_INT)
	    && (opConv2.getDataType() == Node::DATA_INT))
	{
	    result.node->setDataType(Node::DATA_INT);
	    int resInt = 0;
	    int op1Int = opConv1.getInt();
	    int op2Int = opConv2.getInt();
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Applying BINARY operator " << op 
	        << " to INT " << op1Int << ", INT " << op2Int << "." << endl;
	    // ----- DEBUG ----- */
	    if (op == "*")
	        resInt = op1Int * op2Int;
	    else
	    if (op == "/")
	        resInt = op1Int / op2Int;
	    else
	    if (op == "%")
	        resInt = op1Int % op2Int;
	    else
	    if (op == "+")
	        resInt = op1Int + op2Int;
	    else
	    if (op == "-")
	        resInt = op1Int - op2Int;
	    else
	    if (op == "<<")
	        resInt = op1Int << op2Int;
	    else
	    if (op == ">>")
	        resInt = op1Int >> op2Int;
	    else
	    if (op == "<")
	        resInt = op1Int < op2Int;
	    else
	    if (op == "<=")
	        resInt = op1Int <= op2Int;
	    else
	    if (op == ">")
	        resInt = op1Int > op2Int;
	    else
	    if (op == ">=")
	        resInt = op1Int >= op2Int;
	    else
	    if (op == "==")
	        resInt = op1Int == op2Int;
	    else
	    if (op == "!=")
	        resInt = op1Int != op2Int;
	    else
	    if (op == "&")
	        resInt = op1Int & op2Int;
	    else
	    if (op == "^")
	        resInt = op1Int ^ op2Int;
	    else
	    if (op == "|")
	        resInt = op1Int | op2Int;
	    else
	    if (op == "&&")
	        resInt = op1Int && op2Int;
	    else
	    if (op == "||")
	        resInt = op1Int || op2Int;
	    else
	    {
	        // <---- DEBUG ----- //
	        std::cout << "[TreeEval::calculate] WARNING: Operator '" << op 
	            << "' not implemented for types INT/INT." << std::endl;
	        // ----- DEBUG ----> */
	    }
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Setting result to " << resInt 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    result.node->setData(0, resInt);
	} else
	if (((opConv1.getDataType() == Node::DATA_DOUBLE)
	        && (opConv2.getDataType() == Node::DATA_DOUBLE))
	    || ((opConv1.getDataType() == Node::DATA_INT)
	        && (opConv2.getDataType() == Node::DATA_DOUBLE))
	    || ((opConv1.getDataType() == Node::DATA_DOUBLE)
	        && (opConv2.getDataType() == Node::DATA_INT)))
	{
	    result.node->setDataType(Node::DATA_DOUBLE);
	    double resDouble = 0;
	    double op1Double;
	    if (opConv1.getDataType() == Node::DATA_DOUBLE)
	        op1Double = opConv1.getDouble();
	    else
	        op1Double = opConv1.getInt();
	    double op2Double;
	    if (opConv2.getDataType() == Node::DATA_DOUBLE)
	        op2Double = opConv2.getDouble();
	    else
	        op2Double = opConv2.getInt();
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Applying BINARY operator " << op 
	        << " to DOUBLE " << op1Double << ", DOUBLE " << op2Double 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    if (op == "*")
	        resDouble = op1Double * op2Double;
	    else
	    if (op == "/")
	        resDouble = op1Double / op2Double;
	    else
	    if (op == "+")
	        resDouble = op1Double + op2Double;
	    else
	    if (op == "-")
	        resDouble = op1Double - op2Double;
	    else
	    if (op == "<")
	        resDouble = op1Double < op2Double;
	    else
	    if (op == "<=")
	        resDouble = op1Double <= op2Double;
	    else
	    if (op == ">")
	        resDouble = op1Double > op2Double;
	    else
	    if (op == ">=")
	        resDouble = op1Double >= op2Double;
	    else
	    if (op == "==")
	        resDouble = op1Double == op2Double;
	    else
	    if (op == "!=")
	        resDouble = op1Double != op2Double;
	    else
	    if (op == "&&")
	        resDouble = op1Double && op2Double;
	    else
	    if (op == "||")
	        resDouble = op1Double || op2Double;
	    else
	    {
	        // <---- DEBUG ----- //
	        std::cout << "[TreeEval::calculate] WARNING: Operator '" << op 
	            << "' not implemented for types DOUBLE/INT or DOUBLE/DOUBLE." 
	            << std::endl;
	        // ----- DEBUG ----> */
	    }
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Setting result to " << resDouble 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    result.node->setData(0, resDouble);
	} else
	{
	    result.node->setDataType(Node::DATA_INT);
	    string resBlob;
	    int resInt = 0;
	    bool useBlob = false;
	    string op1Blob = opConv1.getData();
	    string op2Blob = opConv2.getData();
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Applying BINARY operator " << op 
	        << " to BLOB " << op1Blob << ", DOUBLE " << op2Blob 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    if (op == "+")
	    {
	        result.node->setDataType(Node::DATA_BLOB);
	        resBlob = op1Blob + op2Blob;
	        useBlob = true;
	    } else
	    if (op == "<")
	        resInt = op1Blob < op2Blob;
	    else
	    if (op == "<=")
	        resInt = op1Blob <= op2Blob;
	    else
	    if (op == ">")
	        resInt = op1Blob > op2Blob;
	    else
	    if (op == ">=")
	        resInt = op1Blob >= op2Blob;
	    else
	    if (op == "==")
	        resInt = op1Blob == op2Blob;
	    else
	    if (op == "!=")
	        resInt = op1Blob != op2Blob;
	    else
	    {
	        // <---- DEBUG ----- //
	        std::cout << "[TreeEval::calculate] WARNING: Operator '" << op 
	            << "' not implemented for types BLOB/INT, BLOB/DOUBLE or "
	            "BLOB/BLOB." << std::endl;
	        // ----- DEBUG ----> */
	    }
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::calculate] Setting result to " << resBlob 
	        << "." << endl;
	    // ----- DEBUG ----- */
	    if (!useBlob)
	        result.node->setData(0, resInt);
	    else
	        result.node->setData(0, resBlob);
	}
	return true;
}

bool TreeEval::unwindOpStack(Ionflux::Template::TreeExprElementStack& ops, 
Ionflux::Template::TreeExprElementStack& values, Ionflux::Template::Tree& 
temps, bool unwindPar)
{
	bool error = false;
	DataEntry op1;
	DataEntry op2;
	op1.node = 0;
	op1.index = 0;
	op2.node = 0;
	op2.index = 0;
	TreeExprElement resElement;
	resElement.type = TreeExprElement::TE_VAR;
	resElement.value = "";
	resElement.data.node = 0;
	resElement.data.index = 0;
	resElement.unary = false;
	bool processed = false;
	while(!error && !ops.empty() 
	    && (ops.top().value[0] != TT_PAR_LEFT.validChars[0])
	    && (!processed || unwindPar))
	{
	    // Allocate a temporary node for the result.
	    resElement.data.node = temps.getRoot()->addChild();
	    resElement.data.index = 0;
	    if (resElement.data.node == 0)
	        error = true;
	    else
	        resElement.data.node->setAutoCreate(true);
	    // Process operator.
	    if (!error && ops.top().unary)
	    {
	        // Process unary operator.
	        if (!values.empty())
	        {
	            op1 = values.top().data;
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::unwindOpStack] Operand #1 = " 
	                << values.top().data.node->getData() << "." << endl;
	            // ----- DEBUG ----- */
	            values.pop();
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::unwindOpStack] Processing UNARY operator "
	
                << ops.top().value << "." << endl;
	            // ----- DEBUG ----- */
	            if (!calculate(op1, resElement.data, ops.top().value))
	                error = true;
	            values.push(resElement);
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::unwindOpStack] Pushed result on stack: VAR
	" 
	                << values.top().data.node->getData() << "." << endl;
	            // ----- DEBUG ----- */
	        } else
	            error = true;
	    } else
	    if (!error)
	    {
	        // Process binary operator.
	        if (!values.empty())
	            op2 = values.top().data;
	        else
	            error = true;
	        /* ----- DEBUG ----- //
	        cout << "[TreeEval::unwindOpStack] Operand #2 = " 
	            << values.top().data.node->getData() << "." << endl;
	        // ----- DEBUG ----- */
	        values.pop();
	        if (!values.empty())
	            op1 = values.top().data;
	        else
	            error = true;
	        /* ----- DEBUG ----- //
	        cout << "[TreeEval::unwindOpStack] Operand #1 = " 
	            << values.top().data.node->getData() << "." << endl;
	        // ----- DEBUG ----- */
	        values.pop();
	        if (!error)
	        {
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::unwindOpStack] Processing BINARY operator 
	" 
	                << ops.top().value << "." << endl;
	            // ----- DEBUG ----- */
	            if (!calculate(op1, op2, resElement.data, ops.top().value))
	                error = true;
	            values.push(resElement);
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::unwindOpStack] Pushed result on stack: VAR
	" 
	                << values.top().data.node->getData() << "." << endl;
	            // ----- DEBUG ----- */
	        }
	    }
	    ops.pop();
	    processed = true;
	}
	if (unwindPar && !ops.empty())
	{
	    // Remove left parenthesis.
	    ops.pop();
	}
	return !error;
}

bool TreeEval::parseTreeExpr(const std::string& treeExpr, 
Ionflux::Template::TreeExprElementVector& elements)
{
	elements.clear();
	Tokenizer tok;
	tok.addTokenType(TT_OPERATOR);
	tok.addTokenType(TT_TREEPATH_NP);
	tok.addTokenType(TT_PAR_LEFT);
	tok.addTokenType(TT_PAR_RIGHT);
	tok.setExtractQuoted(true);
	tok.setInput(treeExpr);
	bool isConstant = false;
	bool error = false;
	string errorReason = "";
	TreeExprElement currentElement;
	currentElement.type = TreeExprElement::TE_INVALID;
	currentElement.value = "";
	currentElement.data.node = 0;
	currentElement.data.index = 0;
	currentElement.unary = false;
	Token currentToken = tok.getNextToken();
	while ((currentToken.typeID != TT_NONE.typeID) 
	    && (currentToken.typeID != TT_INVALID.typeID)
	    && !error)
	{
	    // Skip leading whitespace.
	    while ((currentToken.typeID == TT_WHITESPACE.typeID)
	        || (currentToken.typeID == TT_LINETERM.typeID))
	        currentToken = tok.getNextToken();
	    if (currentToken.typeID == TT_QUOTED.typeID)
	    {
	        // Handle quoted constant.
	        currentElement.type = TreeExprElement::TE_CONST;
	        currentElement.value = currentToken.value;
	        elements.push_back(currentElement);
	        // Reset element.
	        currentElement.type = TreeExprElement::TE_INVALID;
	        currentElement.value = "";
	        currentToken = tok.getNextToken();
	    } else
	    if ((currentToken.typeID == TT_TREEPATH_NP.typeID)
	        || (currentToken.typeID == TT_IDENTIFIER.typeID))
	    {
	        // Handle treepath (variable) or unquoted numeric constant.
	        isConstant = true;
	        while (((currentToken.typeID == TT_TREEPATH_NP.typeID)
	            || (currentToken.typeID == TT_IDENTIFIER.typeID)
	            || (currentToken.typeID == TT_QUOTED.typeID)
	            || (currentToken.typeID == TT_PAR_LEFT.typeID)
	            || (!isConstant 
	                && (currentToken.typeID == TT_PAR_RIGHT.typeID))))
	        {
	            currentElement.value.append(currentToken.value);
	            /* Check whether this is NOT a constant.
	               The check is not done if it is already known that this 
	               element is not a constant. Otherwise, this element does 
	               not qualify as a constant if all of the following is true:
	                 1) Element is not an integer.
	                 2) Element is not a float.
	                 3) Element is not '.' (meaning it might still grow into 
	                    a float without integer part after more tokens are 
	                    appended).
	               This is somewhat unelegant, but should do the job. */
	            if (isConstant 
	                && !Ionflux::ObjectBase::isInteger(currentElement.value) 
	                && !Ionflux::ObjectBase::isFloat(currentElement.value)
	                && (currentElement.value != ".")) 
	                isConstant = false;
	            currentToken = tok.getNextToken();
	        }
	        /* Constant or variable, which is it?
	           We rely on the judgement of the previous tests but filter 
	           the case that the current element value is '.'. */
	        if (!isConstant || (currentElement.value == "."))
	            currentElement.type = TreeExprElement::TE_VAR;
	        else
	            currentElement.type = TreeExprElement::TE_CONST;
	        elements.push_back(currentElement);
	        // Reset element.
	        currentElement.type = TreeExprElement::TE_INVALID;
	        currentElement.value = "";
	    } else
	    if ((currentToken.typeID == TT_OPERATOR.typeID)
	        || (currentToken.typeID == TT_PAR_LEFT.typeID)
	        || (currentToken.typeID == TT_PAR_RIGHT.typeID))
	    {
	        // Handle operator.
	        currentElement.value = currentToken.value;
	        currentElement.type = TreeExprElement::TE_OP;
	        elements.push_back(currentElement);
	        // Reset element.
	        currentElement.type = TreeExprElement::TE_INVALID;
	        currentElement.value = "";
	        currentToken = tok.getNextToken();
	    } else
	    {
	        error = true;
	        errorReason = "Unexpected token.";
	    }
	}
	if (currentToken.typeID == TT_INVALID.typeID)
	{
	    error = true;
	    errorReason = "Invalid Token.";
	}
	if (error)
	{
	    ostringstream status;
	    string ws;
	    int errPos = tok.getCurrentTokenPos();
	    if (errPos > 0)
	        ws.append(errPos, ' ');
	    status.str("");
	    status << "[TreeEval::parse] Parse error at position " 
	        << errPos << ":" << endl << treeExpr << endl << ws << "^" << endl
	        << "(" << errorReason << ")";
	    throw IFTemplateError(status.str());
	}
	return !error;
}

bool TreeEval::eval(Ionflux::Template::Tree* tree, 
Ionflux::Template::TreeExprElementVector& elements, 
Ionflux::Template::Node& result, bool createPath)
{
	Ionflux::ObjectBase::nullPointerCheck(tree, 
	    "TreeResolver::eval", "Tree");
	result.clear();
	if (elements.size() == 0)
	    return true;
	bool error = false;
	string errorReason = "";
	TreeExprElement currentElement;
	TreeExprElement prevElement;
	currentElement.type = TreeExprElement::TE_INVALID;
	currentElement.value = "";
	currentElement.data.node = 0;
	currentElement.data.index = 0;
	currentElement.unary = false;
	prevElement = currentElement;
	unsigned int elementIndex = 0;
	stack<TreeExprElement> ops;
	stack<TreeExprElement> values;
	/* <---- DEBUG ----- //
	//Node* r0 = Node::create();
	Tree* temps0 = Tree::create();
	temps0->setID("temps0");
	std::cerr << "[TreeEval::eval] DEBUG: "
	    "Created tree " << temps0->getIDString() << "(p = " << temps0 
	    << ", root = " << temps0->getRoot() << ")" << std::endl;
	delete temps0;
	// ----- DEBUG ----- */
	Tree* temps = Tree::create();
	temps->getRoot()->setAutoCreate(true);
	temps->getRoot()->setUidMode(Node::UID_MODE_TREE);
	Node* tempsRoot = temps->getRoot();
	/* <---- DEBUG ----- //
	temps->setID("eval");
	std::cerr << "[TreeEval::eval] DEBUG: "
	    "Created tree " << temps << " (root = " 
	    << tempsRoot << ")" << std::endl;
	// ----- DEBUG ----- */
	/* <---- DEBUG ----- //
	std::cerr << "[TreeEval::eval] DEBUG: "
	    "Local references [" << temps << " -> root] = " 
	    << temps.getNumLocalRefs(tempsRoot) << std::endl;
	// ----- DEBUG ----- */
	TreeExprElement resElement;
	resElement.type = TreeExprElement::TE_VAR;
	resElement.value = "";
	resElement.data.node = 0;
	resElement.data.index = 0;
	resElement.unary = false;
	while (!error && (elementIndex < elements.size()))
	{
	    currentElement = elements[elementIndex];
	    if (currentElement.type == TreeExprElement::TE_CONST)
	    {
	        /* Handle constant.
	           Allocate a temporary node for the constant. */
	        resElement.data.node = tempsRoot->addChild();
	        resElement.data.index = 0;
	        if (resElement.data.node != 0)
	        {
	            resElement.data.node->setData(0, currentElement.value);
	            values.push(resElement);
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::eval] Pushed on VALUE stack: CONST " 
	                << currentElement.value << endl;
	            // ----- DEBUG ----- */
	        } else
	        {
	            error = true;
	            errorReason = "Could not allocate temporary "
	                "node for constant.";
	        }
	    } else
	    if (currentElement.type == TreeExprElement::TE_VAR)
	    {
	        // Handle variable.
	        currentElement.data = tree->resolve(currentElement.value, 
	            createPath);
	        if (currentElement.data.node == 0)
	        {
	            error = true;
	            errorReason = "Could not resolve node '" 
	                + currentElement.value + "'.";
	        }
	        values.push(currentElement);
	        /* ----- DEBUG ----- //
	        cout << "[TreeEval::eval] Pushed on VALUE stack: VAR " 
	            << currentElement.value << endl;
	        // ----- DEBUG ----- */
	    } else
	    if (currentElement.type == TreeExprElement::TE_OP)
	    {
	        // Handle operators.
	        if (((currentElement.value == "+") 
	            || (currentElement.value == "-"))
	            && ((prevElement.type == TreeExprElement::TE_INVALID)
	                || ((prevElement.type == TreeExprElement::TE_OP)
	                    && (prevElement.value[0] != 
	TT_PAR_RIGHT.validChars[0]))))
	        {
	            /* This is an operator '+' or '-' following either no element 
	               or another operator, but not a closing parenthesis. Thus, 
	               this should be a unary operator. */
	            currentElement.unary = true;
	        } else
	            currentElement.unary = false;
	        if (currentElement.value[0] == TT_PAR_RIGHT.validChars[0])
	        {
	            /* Unwind the operator stack if current operator is a right 
	               parenthesis. */
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::eval] Unwinding OPERATOR stack..." << 
	endl;
	            // ----- DEBUG ----- */
	            if (!unwindOpStack(ops, values, *temps, true))
	            {
	                error = true;
	                errorReason = "Unwind stack failed.";
	            }
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::eval] Top of VALUE stack after "
	                "unwinding: " << values.top().data.node->getData() 
	                << "." << endl;
	            // ----- DEBUG ----- */
	        } else
	        if (!ops.empty() 
	                && (ops.top().value[0] != TT_PAR_LEFT.validChars[0])
	                && (currentElement.value[0] != TT_PAR_LEFT.validChars[0])
	                && (getOpPrecedence(currentElement.value, 
	currentElement.unary) 
	                    <= getOpPrecedence(ops.top().value, ops.top().unary)))
	        {
	            /* Unwind the operator stack if:
	                 1) Stack is not empty.
	                 2) Element on top of stack is not a left parenthesis.
	                 3) Current element is not a left parenthesis.
	                 4) Precedence of current element is equal or less than 
	                    that of element on top of stack. */
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::eval] Unwinding OPERATOR stack..." << 
	endl;
	            // ----- DEBUG ----- */
	            if (!unwindOpStack(ops, values, *temps))
	            {
	                error = true;
	                errorReason = "Unwind stack failed.";
	            }
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::eval] Top of VALUE stack after "
	                "unwinding: " << values.top().data.node->getData() 
	                << "." << endl;
	            // ----- DEBUG ----- */
	        }
	        if (currentElement.value[0] != TT_PAR_RIGHT.validChars[0])
	        {
	            ops.push(currentElement);
	            /* ----- DEBUG ----- //
	            cout << "[TreeEval::eval] Pushed on OPERATOR stack: OP " 
	                << currentElement.value << endl;
	            // ----- DEBUG ----- */
	        }
	    } else
	    {
	        error = true;
	        errorReason = "Invalid element.";
	    }
	    prevElement = currentElement;
	    elementIndex++;
	}
	/* <---- DEBUG ----- //
	std::cerr << "[TreeEval::eval] DEBUG: "
	    "(2) Local references [" << temps << " -> root] = " 
	    << temps->getNumLocalRefs(tempsRoot) << std::endl;
	// ----- DEBUG ----- */
	if (!error)
	{
	    /* ----- DEBUG ----- //
	    cout << "[TreeEval::eval] Unwinding OPERATOR stack..." << endl;
	    // ----- DEBUG ----- */
	    if (!unwindOpStack(ops, values, *temps, true))
	    {
	        error = true;
	        errorReason = "Unwind stack failed.";
	    } else
	    if (values.top().data.node != 0)
	    {
	        /* ----- DEBUG ----- //
	        cout << "[TreeEval::eval] Top of VALUE stack after "
	            "unwinding: " << values.top().data.node->getData() 
	            << "." << endl;
	        // ----- DEBUG ----- */
	        result = *values.top().data.node;
	        /* ----- DEBUG ----- //
	        cout << "[TreeEval::eval] Result: " 
	            << result.getData() << "." << endl;
	        // ----- DEBUG ----- */
	    } else
	    {
	        error = true;
	        errorReason = "Result node on stack is null.";
	    }
	}
	if (error)
	{
	    std::ostringstream status;
	    status << "[TreeEval::eval] Parse error at element '" 
	        << currentElement.value << "'. (" << errorReason << ")";
	    throw IFTemplateError(status.str());
	}
	/* <---- DEBUG ----- //
	std::cerr << "[TreeEval::eval] DEBUG: "
	    " (3) Local references [" << temps << " -> root] = " 
	    << temps->getNumLocalRefs(tempsRoot) << std::endl;
	// ----- DEBUG ----- */
	delete temps;
	temps = 0;
	return !error;
}

Ionflux::Template::TreeEval& TreeEval::operator=(const 
Ionflux::Template::TreeEval& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::TreeEval* TreeEval::copy() const
{
    TreeEval* newTreeEval = create();
    *newTreeEval = *this;
    return newTreeEval;
}

Ionflux::Template::TreeEval* 
TreeEval::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TreeEval*>(other);
}

Ionflux::Template::TreeEval* 
TreeEval::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TreeEval* newObject = new TreeEval();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file TreeEval.cpp
 * \brief Tree expression evaluator implementation.
 */
