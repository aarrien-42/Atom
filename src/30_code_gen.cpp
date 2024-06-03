#include "code_gen.hpp"

/*-CONSTRUCTOR-*/

CodeGenerator::CodeGenerator( std::string outputFile ) : _outputFile(outputFile) {
	
}

/*-DESTRUCTOR-*/

CodeGenerator::~CodeGenerator() {
	for (ProgramNode* program : _parsedPrograms) {
		delete program;
	}
}

/*-METHODS-*/

void	CodeGenerator::addProgram( ProgramNode* program ) {
	_parsedPrograms.push_back(program);
}

void	CodeGenerator::writeFullProgramCode() {
	std::ofstream outDataFile("asm/data.asm", std::ios::out | std::ios::trunc);
	std::ofstream outCodeFile("asm/code.asm", std::ios::out | std::ios::trunc);
	
	if (outDataFile.is_open() && outCodeFile.is_open()) {
		/*-DATA-*/
		outDataFile << "section .data\n";

		/*-CODE-*/
		outCodeFile << "%include 'data.asm'\n\nsection .text\n  global _start\n\n";
		for (size_t progCount = 0; progCount < _parsedPrograms.size(); progCount++) {
			nodeHandler(_parsedPrograms[progCount]);
		}
	}
}

void	CodeGenerator::nodeHandler( ASTNode* node ) {
	switch (node->getType()) {
		case NodeType::Program:
			
			break;
		case NodeType::Block: break;
		case NodeType::Box: break;
		case NodeType::FuncDecl:
			writeFuncDeclNode(node);
			break;
		case NodeType::FuncCall:
			writeFuncCallNode(node);
			break;
		case NodeType::Condition:
			writeConditionNode(node);
			break;
		case NodeType::IfStatement:
			writeIfStatementNode(node);
			break;
		case NodeType::WhileLoop:
			writeWhileLoopNode(node);
			break;
		case NodeType::ForLoop:
			writeForLoopNode(node);
			break;
		case NodeType::BinOp:
			writeBinOpNode(node);
			break;
		case NodeType::UnaryOp:
			writeUnaryOpNode(node);
			break;
		case NodeType::VarDecl:
			writeVarDeclNode(node);
			break;
		case NodeType::Assign:
			writeAssignNode(node);
			break;
		case NodeType::Literal:
			writeLiteralNode(node);
			break;
		case NodeType::Identifier:
			writeIdentifierNode(node);
			break;
		case NodeType::Return:
			writeReturnNode(node);
			break;
	}
}

void	CodeGenerator::writeProgramNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeFuncDeclNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeFuncCallNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeConditionNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeIfStatementNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeWhileLoopNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeForLoopNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeBinOpNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeUnaryOpNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeVarDeclNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeAssignNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeLiteralNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeIdentifierNode( ASTNode* node ) {
	(void)node;
}

void	CodeGenerator::writeReturnNode( ASTNode* node ) {
	(void)node;
}

