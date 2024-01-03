#include "nodes.hpp"

BlockNode::BlockNode() : ASTNode(Block) {
	
}

FuncDeclNode::FuncDeclNode( Parser& parser ) : ASTNode(FuncDecl), body(nullptr) {
	std::cout << "FUNCTION DECLARED\n";
	functionName = parser.peek().value;
}

FuncCallNode::FuncCallNode() : ASTNode(FuncCall) {

}

IfStatementNode::IfStatementNode() : ASTNode(IfStatement), condition(nullptr), ifBranch(nullptr), elseBranch(nullptr) {

}

WhileLoopNode::WhileLoopNode() : ASTNode(WhileLoop), condition(nullptr), body(nullptr) {

}

ForLoopNode::ForLoopNode() : ASTNode(ForLoop), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {

}

BinOpNode::BinOpNode() : ASTNode(BinOp), leftOperand(nullptr), rightOperand(nullptr) {

}

VarDeclNode::VarDeclNode() : ASTNode(VarDecl), initialValue(nullptr) {

}

AssignNode::AssignNode() : ASTNode(Assign), value(nullptr) {

}

LiteralNode::LiteralNode() : ASTNode(Literal) {

}

IdentifierNode::IdentifierNode() : ASTNode(Identifier) {

}

ReturnNode::ReturnNode() : ASTNode(Return), returnValue(nullptr) {

}
