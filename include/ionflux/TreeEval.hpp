#ifndef IONFLUX_TOOLS_TREEEVAL
#define IONFLUX_TOOLS_TREEEVAL
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeEval.hpp                        Tree expression evaluator.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <ionflux/tools.hpp>
#include <ionflux/Tokenizer.hpp>
#include <ionflux/Tree.hpp>
#include <ionflux/TreeResolver.hpp>

namespace Ionflux
{

namespace Tools
{

class Tree;
struct DataEntry;
struct TreeExprElement;

/** Tree expression evaluator.
 * \ingroup datahand
 *
 * Evaluates expressions in which tree paths are used as variables.
 */
class TreeEval
{
	protected:
		/** Perform calculation.
		 *
		 * Performs a calculation using the specified unary operator.
		 *
		 * \param op1 Operand.
		 * \param result Data entry to store the result in.
		 * \param op Unary operator.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool calculate(DataEntry &op1, DataEntry &result, 
			const std::string &op);
		
		/** Perform calculation.
		 *
		 * Performs a calculation using the specified binary operator.
		 *
		 * \param op1 First operand.
		 * \param op2 Second operand.
		 * \param result Data entry to store the result in.
		 * \param op Unary operator.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool calculate(DataEntry &op1, DataEntry &op2, 
			DataEntry &result, const std::string &op);
		
		/** Unwind operator stack.
		 *
		 * Unwinds an operator stack by processing the topmost element, or 
		 * all operators until either the stack is empty or a left 
		 * parenthesis is found. The result of the operation is put on 
		 * top of the value stack.
		 *
		 * \param ops Operator stack.
		 * \param values Value stack.
		 * \param temps Tree in which to store temporary values.
		 * \param unwindPar Whether to unwind the stack until it is empty or 
		 * a left parenthesis is found.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool unwindOpStack(std::stack<TreeExprElement> &ops, 
			std::stack<TreeExprElement> &values, Tree &temps, 
			bool unwindPar = false);
		
	public:
		/// Token type: Operators.
		static const TokenType TT_OPERATOR;
		/// Token type: Tree path (excluding parentheses).
		static const TokenType TT_TREEPATH_NP;
		/// Token type: Parenthesis (left).
		static const TokenType TT_PAR_LEFT;
		/// Token type: Parenthesis (right).
		static const TokenType TT_PAR_RIGHT;
		
		/** Constructor.
		 *
		 * Construct new TreeEval object.
		 */
		TreeEval();
		
		/** Destructor.
		 *
		 * Destruct TreeEval object.
		 */
		virtual ~TreeEval();
		
		/** Parse tree expression.
		 *
		 * Parse a tree expression into tree expression elements.
		 *
		 * \param treeExpr Tree expression.
		 * \param elements Vector in which to store tree expression elements.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool parseTreeExpr(const std::string &treeExpr, 
			std::vector<TreeExprElement> &elements);
		
		/** Evaluate tree expression.
		 *
		 * Evaluates a tree expression for a specified tree and a set of tree 
		 * expression elements. Pass \c true to \c createPath to create tree 
		 * paths on the fly if it they do not already exist.
		 *
		 * \param tree Tree for which the expression should be evaluated.
		 * \param elements Tree expression elements to evaluate.
		 * \param result Where to store the result of the evaluation.
		 * \param createPath Whether to create a path if it does not already 
		 * exist.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool eval(Tree *tree, std::vector<TreeExprElement> &elements, 
			Node &result, bool createPath);
};

}

}

/** \file TreeEval.hpp
 * \brief Tree expression evaluator header.
 */
#endif
