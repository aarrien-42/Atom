#include "parser.hpp"

/*-CONSTRUCTOR-*/

Parser::Parser( const std::vector<Token>& tokens ) : _tokens(tokens), _index(0) {
	currentTabs = 0;
	currentLine = 0;

	while (!peek().value.empty()) {
		if (peek().type == tab) {
			currentTabs = consume().value.size();
		} else if (peek().type == enter) {
			currentLine++;
			consume();
		} else {
			if (peek().type == identifier && getStrEndChar(peek().value) == ':') {
				_tree.push_back(FuncDeclNode(*this));
			} else if (currentTabs == 0) {
				std::cerr << "Any program needs to be inside a function\n";
			}
			//Token currentToken = consume();
			//std::cout << "value = [" << currentToken.value << "]" << "Tabs = " << currentTabs << " Line = " << currentLine << std::endl;
		}
	}
}

/*-DESTRUCTOR-*/

Parser::~Parser() {}

/*-METHODS-*/

std::vector<ASTNode>	Parser::getTree() { return _tree; }

Token					Parser::peek( size_t pos ) {
	if (_index + pos < _tokens.size())
		return _tokens.at(_index + pos);
	return Token();
}

Token					Parser::consume() {
	Token currentToken = peek();
	_index++;
	return currentToken;
}
