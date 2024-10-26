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
    Unknown
};

struct ASTNode {
        private:
            NodeType type;
        public:
        ASTNode(NodeType t) : type(t) {}
        virtual ~ASTNode() {}

        virtual void deleteNode() = 0;

        NodeType getType() { return type; }
};
