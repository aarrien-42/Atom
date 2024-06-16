#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "utils.hpp"
#include "nodes.hpp"
#include "error.hpp"

struct Token;
struct ASTNode;
struct ProgramNode;

class Parser {
    private:
        ProgramNode* _tree;
        std::vector<Token> _tokens;
        size_t _index;
    public:
        Parser( const std::vector<Token>&, std::string fileName );
        ~Parser();

        ProgramNode* getProgram();

        Token peek( int pos = 0);
        Token consume();

        void printTree();
};

#endif