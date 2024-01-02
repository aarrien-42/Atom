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
}

/*-DESTRUCTOR-*/

Lexer::~Lexer() {}

/*-METHODS-*/

std::vector<Token>	Lexer::getTokens() { return _tokens; }

void				Lexer::setToken( std::string& buffer , TokenType tokenType ) {
	Token token = {._type = tokenType, ._value = buffer};

	static const std::vector<std::string> keywords = { KEYWORD_IF, KEYWORD_ELSE, KEYWORD_IF_ELSE, KEYWORD_WHILE, KEYWORD_FOR, KEYWORD_VARIABLE, KEYWORD_PRINT, KEYWORD_RETURN };
	static const std::vector<std::string> operators = { OPERATOR_PLUS, OPERATOR_MINUS, OPERATOR_MULTIPLY, OPERATOR_DIVIDE, OPERATOR_MODULO, OPERATOR_ASSIGN };
	static const std::vector<std::string> comparisons = { COMPARISON_EQUAL, COMPARISON_NOT_EQUAL, COMPARISON_LESS, COMPARISON_LESS_EQUAL, COMPARISON_GREATER, COMPARISON_GREATER_EQUAL};
	static const std::vector<std::string> logicals = { LOGICAL_AND, LOGICAL_OR };
	static const std::vector<std::string> bitwises = { BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT };
	static const std::vector<std::string> parenthesis = { LEFT_PAREN, RIGHT_PAREN };
	static const std::vector<std::string> braces = { LEFT_BRACE, RIGHT_BRACE };

	// TODO: check for: identifier, variable, whitespace

	if (isStringInVector(buffer, keywords))
		token._type = keyword;
	else if (isStringInVector(buffer, operators))
		token._type = operation;
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
			setToken(buffer, identifier);
		} else if (isdigit(peek())) {
			// digit
			while (peek() != 0 && isdigit(peek()))
				buffer.push_back(consume());
			setToken(buffer, literal);
		} else if (std::string("\'\"").find(peek()) != std::string::npos) {
			// quotes
			currentChar = peek();
			buffer.push_back(consume());
			while (peek() != 0 && peek() != currentChar)
				buffer.push_back(consume());
			if (peek() == currentChar)
				buffer.push_back(consume());
			setToken(buffer, literal);
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
		} else if (std::string("\n").find(peek()) != std::string::npos) {
			// new line
			buffer.push_back(consume());
			setToken(buffer, enter);
		} else if (std::string("\t").find(peek()) != std::string::npos) {
			// tab
			while (peek() == '\t')
				buffer.push_back(consume());	
			setToken(buffer, tab);
		} else {
			if (std::string(WHITESPACE).find(peek()) == std::string::npos)
				exitError(E_UNKNOWN_CHAR, std::to_string(peek()));
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
			case literal:
				type = "literal"; break;
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
			case tab:
				type = "tab"; break;
			case comment:
				type = "comment"; break;
			case whitespace:
				type = "whitespace"; break;
			default:
				type = "unknown";
		}
		std::cout << "[" << type << " " << (it->_value == "\n" ? "\\n" : it->_value) << "] ";
		if (it->_value == "\n")
			std::cout << "\n";
	}
	std::cout << std::endl;
}
