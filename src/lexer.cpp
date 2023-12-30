#include "lexer.hpp"

/*-CONSTRUCTOR-*/

Lexer::Lexer( const std::string& fileName ) : _index(0) {
	std::ifstream inputFile(fileName);

	if (!inputFile.is_open())
		exitError(E_FILE_OPEN);

	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	std::string fileContent = buffer.str();

	inputFile.close();

	_sourceFileContent = fileContent;

	tokenize();
	printTokens();
}

/*-DESTRUCTOR-*/

Lexer::~Lexer() {}

/*-METHODS-*/

std::vector<Token>	Lexer::getTokens() { return _tokens; }

char				Lexer::peek() {
	if (_index < _sourceFileContent.size())
		return _sourceFileContent.at(_index);
	return 0;
}

char				Lexer::consume() {
	char currentChar = peek();
	_index++;
	return currentChar;
}

bool				isStringInVector( std::string& buffer , const std::vector<std::string>& vector ) {
	for (std::vector<std::string>::const_iterator it = vector.begin(); it != vector.end(); it++) {
		if (*it == buffer)
			return true;
	}
	return false;
}

void				Lexer::setToken( std::string& buffer ) {
	Token token = {._type = unknown, ._value = buffer};

	static const std::vector<std::string> keywords = { KEYWORD_IF, KEYWORD_ELSE, KEYWORD_IF_ELSE, KEYWORD_WHILE, KEYWORD_FOR, KEYWORD_RETURN };
	static const std::vector<std::string> comparisons = { COMPARISON_EQUAL, COMPARISON_NOT_EQUAL, COMPARISON_LESS, COMPARISON_LESS_EQUAL, COMPARISON_GREATER, COMPARISON_GREATER_EQUAL};
	static const std::vector<std::string> logicals = { LOGICAL_AND, LOGICAL_OR };
	static const std::vector<std::string> bitwises = { BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT };
	static const std::vector<std::string> parenthesis = { LEFT_PAREN, RIGHT_PAREN };
	static const std::vector<std::string> braces = { LEFT_BRACE, RIGHT_BRACE };

	// TODO: check for: identifier, variable, whitespace

	if (isStringInVector(buffer, keywords))
		token._type = keyword;
	else if (isStringInVector(buffer, comparisons))
		token._type = comparison;
	else if (isStringInVector(buffer, logicals))
		token._type = logic;
	else if (isStringInVector(buffer, bitwises))
		token._type = bitwise;
	else if (isStringInVector(buffer, parenthesis))
		token._type = paren;
	else if (isStringInVector(buffer, braces))
		token._type = brace;

	_tokens.push_back(token);
	buffer.clear();
}

void				Lexer::tokenize() {
	std::string	buffer;
	char		currentChar;

	while (peek() != 0) {
		if (isalpha(peek())) {
			// alphanum
			while (peek() != 0 && isalnum(peek()))
				buffer.push_back(consume());
			if (peek() == '.')
				buffer.push_back(consume());
			else if (peek() == ':')
				buffer.push_back(consume());
			setToken(buffer);
		} else if (isdigit(peek())) {
			// digit
			while (peek() != 0 && isdigit(peek()))
				buffer.push_back(consume());
			setToken(buffer);
		} else if (std::string("\'\"").find(peek()) != std::string::npos) {
			// quotes
			currentChar = peek();
			buffer.push_back(consume());
			while (peek() != 0 && peek() != currentChar)
				buffer.push_back(consume());
			if (peek() == currentChar)
				buffer.push_back(consume());
			setToken(buffer);
		} else if (std::string("(){}").find(peek()) != std::string::npos) {
			// parenthesis and braces
			buffer.push_back(consume());
			setToken(buffer);
		} else if (std::string("=!<>+-*/%").find(peek()) != std::string::npos) {
			// operators and comparison
			buffer.push_back(consume());
			if (peek() == '=')
				buffer.push_back(consume());
			setToken(buffer);
		} else {
			consume();
		}
	}
}

void				Lexer::printTokens() {
	for (std::vector<Token>::const_iterator it = _tokens.begin(); it != _tokens.end(); it++) {
		std::string type;

		switch (it->_type) {
			case identifier:
				type = "identifier"; break;
			case variable:
				type = "variable"; break;
			case keyword:
				type = "keyword"; break;
			case operation:
				type = "operation"; break;
			case comparison:
				type = "comparison"; break;
			case logic:
				type = "logic"; break;
			case bitwise:
				type = "bitwise"; break;
			case paren:
				type = "paren"; break;
			case brace:
				type = "brace"; break;
			case enter:
				type = "enter"; break;
			case comment:
				type = "comment"; break;
			case whitespace:
				type = "whitespace"; break;
			default:
				type = "unknown";
		}
		std::cout << "[" << type << " " << it->_value << "] ";
	}
	std::cout << std::endl;
}
