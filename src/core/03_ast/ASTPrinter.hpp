#pragma once

#include "nodes.hpp"

struct ProgramNode;
struct BlockNode;
struct BoxNode;
struct FuncCallNode;
struct FuncDeclNode;
struct ConditionNode;
struct ForLoopNode;
struct IfStatementNode;
struct WhileLoopNode;
struct BinOpNode;
struct UnaryOpNode;
struct AssignNode;
struct IdentifierNode;
struct LiteralNode;
struct VarDeclNode;
struct ReturnNode;

class ASTPrinter {
    public:
        static void printNode(ASTNode* node, size_t level = 0);
    private:
        static void printProgramNode(ProgramNode* node, size_t level = 0);
        static void printBlockNode(BlockNode* node, size_t level = 0);
        static void printBoxNode(BoxNode* node, size_t level = 0);
        static void printFuncDeclNode(FuncDeclNode* node, size_t level = 0);
        static void printFuncCallNode(FuncCallNode* node, size_t level = 0);
        static void printConditionNode(ConditionNode* node, size_t level = 0);
        static void printIfStatementNode(IfStatementNode* node, size_t level = 0);
        static void printWhileLoopNode(WhileLoopNode* node, size_t level = 0);
        static void printForLoopNode(ForLoopNode* node, size_t level = 0);
        static void printBinOpNode(BinOpNode* node, size_t level = 0);
        static void printUnaryOpNode(UnaryOpNode* node, size_t level = 0);
        static void printVarDeclNode(VarDeclNode* node, size_t level = 0);
        static void printAssignNode(AssignNode* node, size_t level = 0);
        static void printLiteralNode(LiteralNode* node, size_t level = 0);
        static void printIdentifierNode(IdentifierNode* node, size_t level = 0);
        static void printReturnNode(ReturnNode* node, size_t level = 0);
};