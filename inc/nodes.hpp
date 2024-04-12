#ifndef NODES_HPP
#define NODES_HPP

	#include <iostream>
	#include <vector>
	#include "parser.hpp"

	enum NodeType {
		Program,
		Block,
		Box,
		FuncDecl,		// <func>:
		FuncCall,		// <func>(<p1>, <p2>)
		Condition,		// (<left><comparator><right>)
		IfStatement,	// i. (<condition>)
		WhileLoop,		// w. (<condition>)
		ForLoop,		// f. (<assign>, <condition>, <operation>)
		BinOp,			// <left><operator><right>
		UnaryOp,		// <left><operator>
		VarDecl,		// v. <var>
		Assign,			// <var> = <?>
		Literal,		// "42" or 42
		Identifier,		// <var>
		Return,			// r. <value>
	};

	class Parser;

/*-MAIN-*/

	struct ASTNode {
		private:
			NodeType					type;

		public:
			ASTNode(NodeType t) : type(t) {}
			virtual ~ASTNode() {}

			NodeType getType() { return type; }
	};

/*-BLOCK-*/

// Description: Stores a chunk of lines or statements
// Data: Function or Conditional content
	struct BlockNode : public ASTNode {
		std::vector<ASTNode*>		statements;

		BlockNode( Parser&, size_t );
		~BlockNode() {
			for (ASTNode* statement : statements)
				delete statement;
		}

		void	print() {
			//for (ASTNode* statement : statements)
				//print(*statement);
		}
	};

// Description: Stores smaller chunks of data
// Data: Node between parenthsis (normally used in operations)
	struct BoxNode : public ASTNode {
		ASTNode*	node;

		BoxNode( Parser& );
		~BoxNode() { delete node; }
	};

/*-FUNCTION-*/

// Description: Function declaration node
// Data: Name, parameters and body (normally a BlockNode)
	struct FuncDeclNode : public ASTNode {
		std::string					functionName;
		std::vector<ASTNode*>		parameters;
		ASTNode*					body;

		FuncDeclNode( Parser& );
		~FuncDeclNode() {
			for (ASTNode* param : parameters)
				delete param;
			delete body;
		}
	};

// Description: Function call node
// Data: Name and parameters (normally LiteralNode)
	struct FuncCallNode : public ASTNode {
		std::string					functionName;
		std::vector<ASTNode*>		parameters;

		FuncCallNode( Parser& );
		~FuncCallNode() {
			for (ASTNode* param : parameters)
				delete param;
		}
	};

/*-CONDITIONAL-*/

// Description: Condition node
// Data: Comparation (<, >, ==, etc.) and nodes to be compared
	struct ConditionNode : public ASTNode {
		std::string					comparation;
		ASTNode*					leftComp;
		ASTNode*					rightComp;

		ConditionNode( Parser& );
		~ConditionNode() { delete leftComp; delete rightComp; }
	};

// Description: If statement node
// Data: Condition (ConditionNode), body (BlockNode) and optional if and else branches
	struct IfStatementNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					body;
		ASTNode*					ifBranch; // not above condition so else if
		ASTNode*					elseBranch; // just in case there's an else

		IfStatementNode( Parser& );
		~IfStatementNode() { delete condition; delete body; delete ifBranch; delete elseBranch; }
	};

// Description: While loop node
// Data: Condition (ConditionNode) and body (BlockNode)
	struct WhileLoopNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					body;

		WhileLoopNode( Parser& );
		~WhileLoopNode() { delete condition; delete body; }
	};

// Description: For loop node
// Data: Initialization (VarDeclNode or AssignNode), condition (ConditionNode), iteration (BinOpNode) and body (BlockNode)
	struct ForLoopNode : public ASTNode {
		ASTNode*					initialization;
		ASTNode*					condition;
		ASTNode*					iteration;
		ASTNode*					body;

		ForLoopNode( Parser& );
		~ForLoopNode() { delete initialization; delete condition; delete iteration; delete body; }
	};

/*-OPERATION-*/

// Description: Binary (pair) operation node
// Data: Operation (+, -, *, /, %, etc.) and two operands
	struct BinOpNode : public ASTNode {
		std::string					operation;
		ASTNode*					leftOp;
		ASTNode*					rightOp;

		BinOpNode( Parser& );
		~BinOpNode() { delete leftOp; delete rightOp; }
	};

// Description: Unary operation node
// Data: Operation (++, --, etc.) and an operand
	struct UnaryOpNode : public ASTNode {
		std::string	operation;
		ASTNode*	operand;

		UnaryOpNode( Parser& );
		~UnaryOpNode() { delete operand; }
	};

/*-VARAIBLE-*/

// Description: Variable declaration node
// Data: Name and initial value (normally a number or string literal)
	struct VarDeclNode : public ASTNode {
		std::string					name;
		ASTNode*					initialValue;

		VarDeclNode( Parser& );
		~VarDeclNode() { delete initialValue; }
	};

// Description: Variable assignation node
// Data: Variable name and new value
	struct AssignNode : public ASTNode {
		std::string					variableName;
		ASTNode*					value;

		AssignNode( Parser& );
		~AssignNode() { delete value; }
	};

// Description: Literal node
// Data: Value, could be a string or a number (either way it saves as a string)
	struct LiteralNode : public ASTNode {
		std::string					value;

		LiteralNode( Parser& );
	};

// Description: Identifier node
// Data: Name of the variable to identify
	struct IdentifierNode : public ASTNode {
		std::string					name;

		IdentifierNode( Parser& );
	};

/*-RETURN-*/

// Description: Return node
// Data: Return value (normally a literal)
	struct ReturnNode : public ASTNode {
		ASTNode*					returnValue;

		ReturnNode( Parser& );
		~ReturnNode() { delete returnValue; }
	};

#endif