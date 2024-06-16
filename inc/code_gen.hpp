#ifndef CODE_GEN_HPP
#define CODE_GEN_HPP

#include <iostream>
#include <filesystem>

#include <string>
#include <vector>

#include "nodes.hpp"

struct ASTNode;
struct ProgramNode;

class CodeGenerator {
	private:
		std::string _outputFile;
		std::vector<ProgramNode*> _parsedPrograms;
	public:
		CodeGenerator( std::string );
		~CodeGenerator();

		void	addProgram( ProgramNode* );

		void	writeFullProgramCode();
		void	nodeHandler( ASTNode* );
		// void	writeProgramNode( ASTNode* );
		// void	writeBlockNode( ASTNode* );
		// void	writeBoxNode( ASTNode* );
		void	writeFuncDeclNode( ASTNode* );
		void	writeFuncCallNode( ASTNode* );
		void	writeConditionNode( ASTNode* );
		void	writeIfStatementNode( ASTNode* );
		void	writeWhileLoopNode( ASTNode* );
		void	writeForLoopNode( ASTNode* );
		void	writeBinOpNode( ASTNode* );
		void	writeUnaryOpNode( ASTNode* );
		void	writeVarDeclNode( ASTNode* );
		void	writeAssignNode( ASTNode* );
		void	writeLiteralNode( ASTNode* );
		void	writeIdentifierNode( ASTNode* );
		void	writeReturnNode( ASTNode* );
};

#endif