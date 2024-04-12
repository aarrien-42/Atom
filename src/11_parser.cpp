#include "parser.hpp"

/*-CONSTRUCTOR-*/

Parser::Parser( const std::vector<Token>& tokens ) : _tokens(tokens), _index(0) {

	while (!peek().value.empty()) {
		if (peek().type == tab || peek().type == enter) {
			consume();
		} else {
			if (peek().type == identifier && getStrEndChar(peek().value) == ':') {
				_tree.push_back(FuncDeclNode(*this));
			}
		}
	}
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
