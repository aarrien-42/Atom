#include "lexer.hpp"

size_t	currentTabs = 0, currentRow = 1, currentColumn = 1;

/*-CONSTRUCTOR-*/

Lexer::Lexer( const std::string& fileName ) : _index(0) {
	std::ifstream inputFile(fileName);

	if (!inputFile.is_open())
		fileReadError(FileReadError::FILE_OPEN);

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

void				Lexer::setToken( std::string& buffer, TokenType tokenType) {
	Token token = {.type = tokenType, .value = buffer, .tabCount = currentTabs, .row = (tokenType == enter ? 0 : currentRow), .column = (tokenType == enter ? 0 : currentColumn)};

	static const std::vector<std::string> keywords = { KEYWORD_IF, KEYWORD_ELSE, KEYWORD_IF_ELSE, KEYWORD_WHILE, KEYWORD_FOR, KEYWORD_VARIABLE, KEYWORD_PRINT, KEYWORD_RETURN };
	static const std::vector<std::string> operators = { OPERATOR_PLUS, OPERATOR_MINUS, OPERATOR_MULTIPLY, OPERATOR_DIVIDE, OPERATOR_MODULO, OPERATOR_ASSIGN };
	static const std::vector<std::string> comparisons = { COMPARISON_EQUAL, COMPARISON_NOT_EQUAL, COMPARISON_LESS, COMPARISON_LESS_EQUAL, COMPARISON_GREATER, COMPARISON_GREATER_EQUAL};
	static const std::vector<std::string> logicals = { LOGICAL_AND, LOGICAL_OR };
	static const std::vector<std::string> bitwises = { BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT };
	static const std::vector<std::string> parenthesis = { LEFT_PAREN, RIGHT_PAREN };
	static const std::vector<std::string> braces = { LEFT_BRACE, RIGHT_BRACE };

	// TODO: check for: identifier, variable, whitespace

	if (isStrInVector(buffer, keywords))
		token.type = keyword;
	else if (isStrInVector(buffer, operators))
		token.type = operation;
	else if (isStrInVector(buffer, comparisons))
		token.type = comparison;
	else if (isStrInVector(buffer, logicals))
		token.type = logic;
	else if (isStrInVector(buffer, bitwises))
		token.type = bitwise;
	else if (isStrInVector(buffer, parenthesis))
		token.type = paren;
	else if (isStrInVector(buffer, braces))
		token.type = brace;

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

	// keep track of reading
	if (currentChar == '\t') {
		currentTabs++;
		currentColumn += 4;
	}
	else if (currentChar == '\n') {
		currentTabs = 0;
		currentColumn = 1;
		currentRow++;
	} else {
		currentColumn++;
	}


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
				fileReadError(FileReadError::UNKNOWN_CHAR, std::to_string(peek()));
			consume();
		}
	}
	buffer.push_back('\n');
	setToken(buffer, enter);
}

// Erases any repeated TokenType::enter tokens
void				Lexer::cleanTokens() {
	TokenType	lastType = unknown;

	for (std::vector<Token>::iterator it = _tokens.begin(); it != _tokens.end();) {
		if (lastType == TokenType::enter && lastType == it->type) {
			it = _tokens.erase(it); // Advance iterator after erasing
		} else {
			lastType = it->type;
			++it;
		}
	}
}

void				Lexer::printTokens() {
	for (std::vector<Token>::const_iterator it = _tokens.begin(); it != _tokens.end(); it++) {
		std::string type;

		switch (it->type) {
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

		// print
		std::cout << "[" << type << " " << (it->value == "\n" ? "\\n" : it->value) << "]";
		if (it->type != enter && it->type != tab)
			std::cout << "[t" << it->tabCount << " " << it->row << ":" << it->column << "]";
		std::cout << " ";
		if (it->type == enter)
			std::cout << "\n";
	}
	std::cout << std::endl;
}
