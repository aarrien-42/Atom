#include "code_gen.hpp"

/*-CONSTRUCTOR-*/

CodeGeneratorManager::CodeGeneratorManager( std::string outputFile ) : _outputFile(outputFile) {
}

/*-DESTRUCTOR-*/

CodeGeneratorManager::~CodeGeneratorManager() {
    for (ProgramNode* program : _parsedPrograms) {
        delete program;
    }
}

/*-METHODS-*/

void CodeGeneratorManager::addProgram( ProgramNode* program ) {
    _parsedPrograms.push_back(program);
}

void CodeGeneratorManager::writeFullProgramCode() {
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

void CodeGeneratorManager::nodeHandler( ASTNode* node ) {
    std::cout << "Node type = " << node->getType() << std::endl;
    switch (node->getType()) {
        case NodeType::Program: {
            ProgramNode* programNode = dynamic_cast<ProgramNode*>(node);
            for (ASTNode* function : programNode->functions) {
                nodeHandler(function);
            }
            break;
        }
        case NodeType::Block: {
            BlockNode* programNode = dynamic_cast<BlockNode*>(node);
            for (ASTNode* statement : programNode->statements) {
                nodeHandler(statement);
            }
            break;
        }
        case NodeType::Box: {
            break;
        }
        case NodeType::FuncDecl: {
            writeFuncDeclNode(node);
            break;
        }
        case NodeType::FuncCall: {
            writeFuncCallNode(node);
            break;
        }
        case NodeType::Condition: {
            writeConditionNode(node);
            break;
        }
        case NodeType::IfStatement: {
            writeIfStatementNode(node);
            break;
        }
        case NodeType::WhileLoop: {
            writeWhileLoopNode(node);
            break;
        }
        case NodeType::ForLoop: {
            writeForLoopNode(node);
            break;
        }
        case NodeType::BinOp: {
            writeBinOpNode(node);
            break;
        }
        case NodeType::UnaryOp: {
            writeUnaryOpNode(node);
            break;
        }
        case NodeType::VarDecl: {
            writeVarDeclNode(node);
            break;
        }
        case NodeType::Assign: {
            writeAssignNode(node);
            break;
        }
        case NodeType::Literal: {
            writeLiteralNode(node);
            break;
        }
        case NodeType::Identifier: {
            writeIdentifierNode(node);
            break;
        }
        case NodeType::Return: {
            writeReturnNode(node);
            break;
        }
    }
}

void    CodeGeneratorManager::writeFuncDeclNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeFuncCallNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeConditionNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeIfStatementNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeWhileLoopNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeForLoopNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeBinOpNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeUnaryOpNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeVarDeclNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeAssignNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeLiteralNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeIdentifierNode( ASTNode* node ) {
    (void)node;
}

void    CodeGeneratorManager::writeReturnNode( ASTNode* node ) {
    (void)node;
}

