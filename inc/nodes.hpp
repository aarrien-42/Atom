#ifndef NODES_HPP
#define NODES_HPP

	#include <iostream>
	#include <vector>
	#include "parser.hpp"

	enum NodeType {
		Program,
		Block,
		Box,
		FuncDecl,
		FuncCall,
		Condition,
		IfStatement,
		WhileLoop,
		ForLoop,
		BinOp,
		VarDecl,
		Assign,
		Literal,
		Identifier,
		Return,
	};

	class Parser;

/*-MAIN-*/

	struct ASTNode {
		NodeType					type;

		ASTNode(NodeType t) : type(t) {}
		virtual ~ASTNode() {}
	};

/*-BLOCK-*/

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

	struct BoxNode : public ASTNode {
		std::vector<ASTNode*>		operations;

		BoxNode( Parser& );
		~BoxNode() {
			for (ASTNode* op : operations)
				delete op;
		}
	};

/*-FUNCTION-*/

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

	struct ConditionNode : public ASTNode {
		std::string					comparation;
		ASTNode*					leftComp;
		ASTNode*					rightComp;

		ConditionNode( Parser& );
		~ConditionNode() { delete leftComp; delete rightComp; }
	};

	struct IfStatementNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					body;
		ASTNode*					ifBranch;
		ASTNode*					elseBranch;

		IfStatementNode( Parser& );
		~IfStatementNode() { delete condition; delete body; delete ifBranch; delete elseBranch; }
	};

	struct WhileLoopNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					body;

		WhileLoopNode( Parser& );
		~WhileLoopNode() { delete condition; delete body; }
	};

	struct ForLoopNode : public ASTNode {
		ASTNode*					initialization;
		ASTNode*					condition;
		ASTNode*					iteration;
		ASTNode*					body;

		ForLoopNode( Parser& );
		~ForLoopNode() { delete initialization; delete condition; delete iteration; delete body; }
	};

/*-OPERATION-*/

	struct BinOpNode : public ASTNode {
		std::string					operation;
		ASTNode*					leftOp;
		ASTNode*					rightOp;

		BinOpNode( Parser& );
		~BinOpNode() { delete leftOp; delete rightOp; }
	};

/*-VARAIBLE-*/

	struct VarDeclNode : public ASTNode { // number or string literals
		std::string					name;
		ASTNode*					initialValue;

		VarDeclNode( Parser& );
		~VarDeclNode() { delete initialValue; }
	};

	struct AssignNode : public ASTNode {
		std::string					variableName;
		ASTNode*					value;

		AssignNode( Parser& );
		~AssignNode() { delete value; }
	};

	struct LiteralNode : public ASTNode {
		std::string					value;

		LiteralNode( Parser& );
	};

	struct IdentifierNode : public ASTNode {
		std::string					name;

		IdentifierNode( Parser& );
	};

/*-RETURN-*/

	struct ReturnNode : public ASTNode {
		ASTNode*					returnValue;

		ReturnNode( Parser& );
		~ReturnNode() { delete returnValue; }
	};

#endif