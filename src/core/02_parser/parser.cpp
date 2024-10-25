#include "parser.hpp"

/*-CONSTRUCTOR-*/

ParserManager::ParserManager( const std::vector<Token>& tokens, std::string fileName ) : _tokens(tokens), _index(0) {
    _tree = new ProgramNode(*this, fileName);

    ConfigManager::getInstance().printDebug("\nPROGRAM ABSTRACT SINTAX TREE:\n", BOLDMAGENTA);
    ASTPrinter::printNode(_tree);
}

/*-DESTRUCTOR-*/

ParserManager::~ParserManager() {
    ConfigManager::getInstance().printDebug("\nDELETE ABSTRACT SINTAX TREE:\n", BOLDMAGENTA);

    for (Function* function : _functions) {
        delete function;
    }
    _tree->deleteNode();
}

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
