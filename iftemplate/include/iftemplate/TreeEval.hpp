#ifndef IONFLUX_TEMPLATE_TREEEVAL
#define IONFLUX_TEMPLATE_TREEEVAL
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeEval.hpp                    Tree expression evaluator (header).
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

#include <string>
#include "iftemplate/types.hpp"
#include "iftemplate/treetypes.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

class Tree;
class Node;

/// Class information for class TreeEval.
class TreeEvalClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TreeEvalClassInfo();
		/// Destructor.
		virtual ~TreeEvalClassInfo();
};

/** Tree expression evaluator.
 * \ingroup iftemplate
 *
 * Evaluates expressions in which tree paths are used as variables.
 */
class TreeEval
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
		/** Perform calculation.
		 *
		 * Performs a calculation using the specified unary operator.
		 *
		 * \param op1 operand.
		 * \param result data entry to store the result in.
		 * \param op unary operator.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool calculate(Ionflux::Template::DataEntry& op1, 
		Ionflux::Template::DataEntry& result, const std::string& op);
		
		/** Perform calculation.
		 *
		 * Performs a calculation using the specified binary operator.
		 *
		 * \param op1 first operand.
		 * \param op2 second operand.
		 * \param result data entry to store the result in.
		 * \param op binary operator.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool calculate(Ionflux::Template::DataEntry& op1, 
		Ionflux::Template::DataEntry& op2, Ionflux::Template::DataEntry& result, 
		const std::string& op);
		
		/** Unwind operator stack.
		 *
		 * Unwinds an operator stack by processing the topmost element, or all
		 * operators until either the stack is empty or a left parenthesis is 
		 * found. The result of the operation is put on top of the value 
		 * stack.
		 *
		 * \param ops operator stack.
		 * \param values value stack.
		 * \param temps tree in which to store temporary values.
		 * \param unwindPar whether to unwind the stack until it is empty or a 
		 * left parenthesis is found.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool unwindOpStack(Ionflux::Template::TreeExprElementStack& ops, 
		Ionflux::Template::TreeExprElementStack& values, Ionflux::Template::Tree&
		temps, bool unwindPar = false);
		
	public:
		/// Token type: operators.
		static const Ionflux::Template::TokenType TT_OPERATOR;
		/// Token type: tree path (excluding parentheses).
		static const Ionflux::Template::TokenType TT_TREEPATH_NP;
		/// Token type: parenthesis (left).
		static const Ionflux::Template::TokenType TT_PAR_LEFT;
		/// Token type: parenthesis (right).
		static const Ionflux::Template::TokenType TT_PAR_RIGHT;
		/// Class information instance.
		static const TreeEvalClassInfo treeEvalClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new TreeEval object.
		 */
		TreeEval();
		
		/** Constructor.
		 *
		 * Construct new TreeEval object.
		 *
		 * \param other Other object.
		 */
		TreeEval(const Ionflux::Template::TreeEval& other);
		
		/** Destructor.
		 *
		 * Destruct TreeEval object.
		 */
		virtual ~TreeEval();
		
		/** Parse tree expression.
		 *
		 * Parse a tree expression into tree expression elements.
		 *
		 * \param treeExpr tree expression.
		 * \param elements vector in which to store tree expression elements.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool parseTreeExpr(const std::string& treeExpr, 
		Ionflux::Template::TreeExprElementVector& elements);
		
		/** Evaluate tree expression.
		 *
		 * Evaluates a tree expression for a specified tree and a set of tree 
		 * expression elements. Pass \c true to \c createPath to create tree 
		 * paths on the fly if it they do not already exist.
		 *
		 * \param tree tree for which the expression should be evaluated.
		 * \param elements vector in which to store tree expression elements.
		 * \param result where to store the result of the evaluation.
		 * \param createPath whether to create the path if it does not already 
		 * exist.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool eval(Ionflux::Template::Tree* tree, 
		Ionflux::Template::TreeExprElementVector& elements, 
		Ionflux::Template::Node& result, bool createPath);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::TreeEval& operator=(const 
		Ionflux::Template::TreeEval& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::TreeEval* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::TreeEval* upcast(Ionflux::ObjectBase::IFObject*
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Template::TreeEval* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
};

}

}

/** \file TreeEval.hpp
 * \brief Tree expression evaluator (header).
 */
#endif
