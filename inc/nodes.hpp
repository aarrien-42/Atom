#ifndef NODES_HPP
#define NODES_HPP

	#include <iostream>
	#include <vector>
	#include "parser.hpp"

	enum NodeType {
		Program,
		Block,
		FuncDecl,
		FuncCall,
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

	struct ASTNode {
		NodeType					type;

		ASTNode(NodeType t) : type(t) {}
	};

	struct BlockNode : public ASTNode {
		std::vector<ASTNode>		statements;

		BlockNode();
	};

	struct FuncDeclNode : public ASTNode {
		std::string					functionName;
		std::vector<std::string>	parameters;
		ASTNode						*body;

		FuncDeclNode( Parser& );
	};

	struct FuncCallNode : public ASTNode {
		std::string					functionName;
		std::vector<ASTNode*>		parameters;

		FuncCallNode();
	};

	struct IfStatementNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					ifBranch;
		ASTNode*					elseBranch;

		IfStatementNode();
	};

	struct WhileLoopNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					body;

		WhileLoopNode();
	};

	struct ForLoopNode : public ASTNode {
		ASTNode* initialization;
		ASTNode* condition;
		ASTNode* iteration;
		ASTNode* body;

		ForLoopNode();
	};

	struct BinOpNode : public ASTNode {
		std::string					operation;
		ASTNode*					leftOperand;
		ASTNode*					rightOperand;

		BinOpNode();
	};

	struct VarDeclNode : public ASTNode { // number or string literals
		std::string					name;
		ASTNode*					initialValue;

		VarDeclNode();
	};

	struct AssignNode : public ASTNode {
		std::string					variableName;
		ASTNode*					value;

		AssignNode();
	};

	struct LiteralNode : public ASTNode {
		std::string					value;

		LiteralNode();
	};

	struct IdentifierNode : public ASTNode {
		std::string					name;

		IdentifierNode();
	};

	struct ReturnNode : public ASTNode {
		ASTNode*					returnValue;

		ReturnNode();
	};

#endif