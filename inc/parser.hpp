#ifndef PARSER_HPP
#define PARSER_HPP

	#include <iostream>
	#include <vector>
	#include "lexer.hpp"

	enum NodeType {
		Program,
		Block,
		Function,
		Condition,
		Variable,
		BinaryOp,
		Print,
		Return,
	};

	struct ASTNode {
		NodeType					type;
	};

	struct BlockNode : public ASTNode {
		std::vector<ASTNode>		statements;
	};

	struct FunctionDeclarationNode : public ASTNode {
		std::string					functionName;
		std::vector<std::string>	parameters;
		ASTNode						*body;
	};

	struct FunctionCallNode : public ASTNode {
		std::string					functionName;
		std::vector<ASTNode*>	parameters;
	};

	struct IfStatementNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					ifBranch;
		ASTNode*					elseBranch;
	};

	struct WhileLoopNode : public ASTNode {
		ASTNode*					condition;
		ASTNode*					body;
	};

	struct BinaryOperationNode : public ASTNode {
		std::string					operation;
		ASTNode*					leftOperand;
		ASTNode*					rightOperand;
	};

	struct VariableDeclarationNode : public ASTNode { // number or string literals
		std::string					name;
		ASTNode*					initialValue;
	};

	struct AssignamentNode : public ASTNode {
		std::string					variableName;
		ASTNode*					value;
	};

	struct LiteralNode : public ASTNode {
		std::string					value;
	};

	struct IdentifierNode : public ASTNode {
		std::string					name;
	};

	struct ReturnNode : public ASTNode {
		ASTNode*					returnValue;
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