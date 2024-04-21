#include "parser.hpp"

/*-CONSTRUCTOR-*/

Parser::Parser( const std::vector<Token>& tokens ) : _tokens(tokens), _index(0) {
	ASTNode* program = new ProgramNode(*this);

	std::cout << "\nPROGRAM ABSTRACT SINTAX TREE:\n\n";
	program->printNode();
	delete program;
}

/*-DESTRUCTOR-*/

Parser::~Parser() {}

/*-METHODS-*/

std::vector<ASTNode>	Parser::getTree() { return _tree; }

Token					Parser::peek( int pos ) {
	if (_index + pos < _tokens.size())
		return _tokens.at(_index + pos);
	return Token();
}

Token					Parser::consume() {
	Token currentToken = peek();
	_index++;
	return currentToken;
}

void					Parser::printTree() {
	
}
