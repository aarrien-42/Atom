#ifndef PARSER_HPP
#define PARSER_HPP

	#include <iostream>
	#include <vector>
	#include "lexer.hpp"
	#include "utils.hpp"

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

	struct ASTNode {
		NodeType					type;

		ASTNode(NodeType t) : type(t) {}
	};

	struct BlockNode : public ASTNode {
		std::vector<ASTNode>		statements;

		BlockNode() : ASTNode(Block) {

		}
	};

	struct FuncDeclNode : public ASTNode {
		std::string					functionName;
		std::vector<std::string>	parameters;
		ASTNode						*body;

		FuncDeclNode() : ASTNode(FuncDecl), body(nullptr) {}
	};

	struct FuncCallNode : public ASTNode {
		std::string					functionName;
		std::vector<ASTNode*>		parameters;

		FuncCallNode() : ASTNode(FuncCall) {}
	};

	struct IfStatementNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					ifBranch;
		ASTNode*					elseBranch;

		IfStatementNode() : ASTNode(IfStatement), condition(nullptr), ifBranch(nullptr), elseBranch(nullptr) {}
	};

	struct WhileLoopNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					body;

		WhileLoopNode() : ASTNode(WhileLoop), condition(nullptr), body(nullptr) {}
	};

	struct ForLoopNode : public ASTNode {
		ASTNode* initialization;
		ASTNode* condition;
		ASTNode* iteration;
		ASTNode* body;

		ForLoopNode() : ASTNode(ForLoop), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {}
	};

	struct BinOpNode : public ASTNode {
		std::string					operation;
		ASTNode*					leftOperand;
		ASTNode*					rightOperand;

		BinOpNode() : ASTNode(BinOp), leftOperand(nullptr), rightOperand(nullptr) {}
	};

	struct VarDeclNode : public ASTNode { // number or string literals
		std::string					name;
		ASTNode*					initialValue;

		VarDeclNode() : ASTNode(VarDecl), initialValue(nullptr) {}
	};

	struct AssignNode : public ASTNode {
		std::string					variableName;
		ASTNode*					value;

		AssignNode() : ASTNode(Assign), value(nullptr) {}
	};

	struct LiteralNode : public ASTNode {
		std::string					value;

		LiteralNode() : ASTNode(Literal) {}
	};

	struct IdentifierNode : public ASTNode {
		std::string					name;

		IdentifierNode() : ASTNode(Identifier) {}
	};

	struct ReturnNode : public ASTNode {
		ASTNode*					returnValue;

		ReturnNode() : ASTNode(Return), returnValue(nullptr) {}
	};

	struct Token;

	class Parser {
		private:
			std::vector<ASTNode>	_tree;
			std::vector<Token>		_tokens;
			size_t					_index;
		public:
			Parser( const std::vector<Token>& );
			~Parser();

			std::vector<ASTNode>	getTree();

			Token					peek();
			Token					consume();
	};

#endif