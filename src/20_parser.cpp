#include "parser.hpp"

/*-CONSTRUCTOR-*/

ParserManager::ParserManager( const std::vector<Token>& tokens, std::string fileName ) : _tokens(tokens), _index(0) {
    _tree = new ProgramNode(*this, fileName);

    std::cout << "\nPROGRAM ABSTRACT SINTAX TREE:\n\n";
    _tree->printNode();
}

/*-DESTRUCTOR-*/

ParserManager::~ParserManager() {}

/*-METHODS-*/

ProgramNode* ParserManager::getProgram() { return _tree; }

Token ParserManager::peek( int pos ) {
    if (_index + pos < _tokens.size())
        return _tokens.at(_index + pos);
    return Token();
}

Token ParserManager::consume() {
    Token currentToken = peek();
    _index++;
    return currentToken;
}

void ParserManager::printTree() {
    
}
