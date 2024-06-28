#ifndef CODE_GEN_HPP
#define CODE_GEN_HPP

#include <filesystem>
#include <iostream>
#include <cstdlib>

#include <string>
#include <vector>

#include "nodes.hpp"

struct ASTNode;
struct ProgramNode;
struct FuncDeclNode;
struct FuncCallNode;
struct ConditionNode;
struct IfStatementNode;
struct WhileLoopNode;
struct ForLoopNode;
struct BinOpNode;
struct UnaryOpNode;
struct VarDeclNode;
struct AssignNode;
struct LiteralNode;
struct IdentifierNode;
struct ReturnNode;

class CodeGeneratorManager {
    private:
        std::string _assemblyCodeFileName;
        std::string _outputFileName;
        std::ofstream _outCodeFile;
        std::vector<ProgramNode*> _parsedPrograms;
    public:
        CodeGeneratorManager( std::string );
        ~CodeGeneratorManager();

        void addProgram( ProgramNode* );

        void writeFullProgramCode();
        void nodeHandler( ASTNode* );
        // void writeProgramNode( ASTNode* );
        // void writeBlockNode( ASTNode* );
        // void writeBoxNode( ASTNode* );
        void writeFuncDeclNode( FuncDeclNode* );
        void writeFuncCallNode( FuncCallNode* );
        void writeConditionNode( ConditionNode* );
        void writeIfStatementNode( IfStatementNode* );
        void writeWhileLoopNode( WhileLoopNode* );
        void writeForLoopNode( ForLoopNode* );
        void writeBinOpNode( BinOpNode* );
        void writeUnaryOpNode( UnaryOpNode* );
        void writeVarDeclNode( VarDeclNode* );
        void writeAssignNode( AssignNode* );
        void writeLiteralNode( LiteralNode* );
        void writeIdentifierNode( IdentifierNode* );
        void writeReturnNode( ReturnNode* );

        void assembleAndLink();
};

#endif