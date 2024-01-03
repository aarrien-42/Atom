#include "parser.hpp"

/*-CONSTRUCTOR-*/

Parser::Parser( const std::vector<Token>& tokens ) : _tokens(tokens), _index(0) {
	size_t	currentTabs = 0;

	while (!peek().value.empty()) {
		if (peek().type == tab) {
			currentTabs = consume().value.size();
		} else {
			std::cout << "end = " << getStrEndChar(peek().value) << "\n";

			Token currentToken = consume();
			std::cout << "value = [" << currentToken.value << "]" << "currentTabs = " << currentTabs << std::endl;
		}
		
	}
}

/*-DESTRUCTOR-*/

Parser::~Parser() {}

/*-METHODS-*/

std::vector<ASTNode>	Parser::getTree() { return _tree; }

Token					Parser::peek() {
	if (_index < _tokens.size())
		return _tokens.at(_index);
	return Token();
}

Token					Parser::consume() {
	Token currentToken = peek();
	_index++;
	return currentToken;
}
