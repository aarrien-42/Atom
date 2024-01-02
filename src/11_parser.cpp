#include "parser.hpp"

/*-CONSTRUCTOR-*/

Parser::Parser( const std::vector<Token>& tokens ) : _tokens(tokens) {
	while (!peek().value.empty()) {
		Token currentToken = consume();
		std::cout << "value = [" << currentToken.value << "]" << std::endl;
	}
}

/*-DESTRUCTOR-*/

Parser::~Parser() {}

/*-METHODS-*/

ProgramNode	Parser::getTree() { return _tree; }

Token		Parser::peek() {
	if (_index < _tokens.size())
		return _tokens.at(_index);
	return Token();
}

Token		Parser::consume() {
	Token currentToken = peek();
	_index++;
	return currentToken;
}
