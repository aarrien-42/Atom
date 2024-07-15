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

struct Function {
    std::string name;
    std::vector<std::string> variables;

    Function( std::string functionName ) { name = functionName; }

    void addVariable( std::string variableName ) { variables.push_back(variableName); }
};

class ParserManager {
    private:
        ProgramNode* _tree;
        std::vector<Token> _tokens;
        size_t _index;

        std::vector<Function*> _functions;
    public:
        ParserManager( const std::vector<Token>&, std::string );
        ~ParserManager();

        ProgramNode* getProgram();

        Token peek( int pos = 0 );
        Token consume();

        Function* addFunction( std::string functionName ) {
            Function* function = new Function(functionName);
            _functions.push_back(function);
            return function;
        }

        Function* getFunction( std::string functionName ) {
            for (Function* function : _functions) {
                if (function->name == functionName) {
                    return function;
                }
            }
            return (nullptr);
        }

        void printTree();
};

#endif