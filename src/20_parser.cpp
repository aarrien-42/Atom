#include "parser.hpp"

/*-CONSTRUCTOR-*/

Parser::Parser( const std::vector<Token>& tokens, std::string fileName ) : _tokens(tokens), _index(0) {
    _tree = new ProgramNode(*this, fileName);

    std::cout << "\nPROGRAM ABSTRACT SINTAX TREE:\n\n";
    _tree->printNode();
}

/*-DESTRUCTOR-*/

Parser::~Parser() {}

/*-METHODS-*/

ProgramNode* Parser::getProgram() { return _tree; }

Token Parser::peek( int pos ) {
    if (_index + pos < _tokens.size())
        return _tokens.at(_index + pos);
    return Token();
}

Token Parser::consume() {
    Token currentToken = peek();
    _index++;
    return currentToken;
}

void Parser::printTree() {
    
}