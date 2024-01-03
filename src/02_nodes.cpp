#include "nodes.hpp"

/*-BLOCK-*/

BlockNode::BlockNode( Parser& parser, size_t blockInitTab ) : ASTNode(Block) {
	std::cout << "BLOCK CREATED\n";
	do {
		if (parser.peek().type == enter) {
			parser.consume();
			if (parser.peek().type == tab)
				parser.currentTabs = parser.consume().value.size();
			else
				parser.currentTabs = 0;
		} else if (parser.peek().type == tab) {
			parser.currentTabs = parser.consume().value.size();
		} else {
			std::cout << "Inside block = " << parser.peek().value << " type = " << parser.peek().type << std::endl;
			// block body check
			parser.consume();
		}
	} while (!parser.peek().value.empty() && parser.currentTabs > blockInitTab);
}

/*-FUNCTION-*/

FuncDeclNode::FuncDeclNode( Parser& parser ) : ASTNode(FuncDecl), body(nullptr) {
	std::cout << "FUNCTION DECLARED\n";
	functionName = parser.consume().value;
	std::cout << "	name = " << functionName << std::endl;
	if (parser.peek().type != enter) {

	} else {
		parser.consume();
		body = new BlockNode(parser, parser.currentTabs);
	}
}

FuncCallNode::FuncCallNode( Parser& parser ) : ASTNode(FuncCall) {
	(void)parser;
}

/*-CONDITIONAL-*/

IfStatementNode::IfStatementNode( Parser& parser ) : ASTNode(IfStatement), condition(nullptr), ifBranch(nullptr), elseBranch(nullptr) {
	(void)parser;
}

WhileLoopNode::WhileLoopNode( Parser& parser ) : ASTNode(WhileLoop), condition(nullptr), body(nullptr) {
	(void)parser;
}

ForLoopNode::ForLoopNode( Parser& parser ) : ASTNode(ForLoop), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
	(void)parser;
}

/*-OPERATION-*/

BinOpNode::BinOpNode( Parser& parser ) : ASTNode(BinOp), leftOp(nullptr), rightOp(nullptr) {
	(void)parser;
}

/*-VARAIBLE-*/

VarDeclNode::VarDeclNode( Parser& parser ) : ASTNode(VarDecl), initialValue(nullptr) {
	(void)parser;
}

AssignNode::AssignNode( Parser& parser ) : ASTNode(Assign), value(nullptr) {
	(void)parser;
}

LiteralNode::LiteralNode( Parser& parser ) : ASTNode(Literal) {
	(void)parser;
}

IdentifierNode::IdentifierNode( Parser& parser ) : ASTNode(Identifier) {
	(void)parser;
}

/*-RETURN-*/

ReturnNode::ReturnNode( Parser& parser ) : ASTNode(Return), returnValue(nullptr) {
	(void)parser;
}
