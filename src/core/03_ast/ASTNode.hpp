#pragma once

#include <iostream>
#include <vector>
#include "parser.hpp"
#include "lexer.hpp"
#include "colors.hpp"
#include "config.hpp"

enum NodeType {
    Program,
    Block,
    Box,
    FuncDecl,       // <func>:
    FuncCall,       // <func>(<p1>, <p2>)
    Condition,      // (<left><comparator><right>)
    IfStatement,    // i. (<condition>)
    WhileLoop,      // w. (<condition>)
    ForLoop,        // f. (<assign>, <condition>, <operation>)
    BinOp,          // <left><operator><right>
    UnaryOp,        // <left><operator>
    VarDecl,        // v. <var>
    Assign,         // <var> = <?>
    Literal,        // "42" or 42
    Identifier,     // <var>
    Return,         // r. <value>
};

struct ASTNode {
        private:
            NodeType type;
        protected:
            size_t level;
        public:
        ASTNode(NodeType t, size_t l = 0) : type(t), level(l) {}
        virtual ~ASTNode() {}

        virtual void deleteNode() = 0;

        NodeType getType() { return type; }

        virtual void putSpaces(bool isNode = false) const {
            ConfigManager& Config = ConfigManager::getInstance();
            size_t spaceSize = 2;

            for (size_t i = 0; i < level + !isNode; i++) {
                for (size_t j = 0; j < spaceSize; j++) {
                    Config.printDebug(" ");
                }
            }
        }

        virtual void printNode() const {
            putSpaces(true);
            std::string textColor = getColor(level);
            std::string nodeName;
            switch (type) {
                case NodeType::Program:     nodeName = "ProgramNode";     break;
                case NodeType::Block:       nodeName = "BlockNode";       break;
                case NodeType::Box:         nodeName = "BoxNode";         break;
                case NodeType::FuncDecl:    nodeName = "FuncDeclNode";    break;
                case NodeType::FuncCall:    nodeName = "FuncCallNode";    break;
                case NodeType::Condition:   nodeName = "ConditionNode";   break;
                case NodeType::IfStatement: nodeName = "IfStatementNode"; break;
                case NodeType::WhileLoop:   nodeName = "WhileLoopNode";   break;
                case NodeType::ForLoop:     nodeName = "ForLoopNode";     break;
                case NodeType::BinOp:       nodeName = "BinOpNode";       break;
                case NodeType::UnaryOp:     nodeName = "UnaryOpNode";     break;
                case NodeType::VarDecl:     nodeName = "VarDeclNode";     break;
                case NodeType::Assign:      nodeName = "AssignNode";      break;
                case NodeType::Literal:     nodeName = "LiteralNode";     break;
                case NodeType::Identifier:  nodeName = "IdentifierNode";  break;
                case NodeType::Return:      nodeName = "ReturnNode";      break;
                default: nodeName = "Unknown";
            }
            ConfigManager::getInstance().printDebug("[" + nodeName + "]:\n", textColor);
        }
};
