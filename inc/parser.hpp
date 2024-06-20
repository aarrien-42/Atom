#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "utils.hpp"
#include "nodes.hpp"
#include "error.hpp"
#include "config.hpp"

struct Token;
struct ASTNode;
struct ProgramNode;

class ParserManager {
    private:
        ConfigManager& Config;
        
        ProgramNode* _tree;
        std::vector<Token> _tokens;
        size_t _index;
    public:
        ParserManager( const std::vector<Token>&, std::string, ConfigManager& );
        ~ParserManager();

        ProgramNode* getProgram();

        Token peek( int pos = 0);
        Token consume();

        void printTree();
};

#endif