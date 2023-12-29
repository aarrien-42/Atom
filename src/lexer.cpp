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

void				Lexer::createToken( std::string& token ) {
	std::cout << token << std::endl;
	token.clear();
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
			createToken(buffer);
		} else if (isdigit(peek())) {
			// digit
			while (peek() != 0 && isdigit(peek()))
				buffer.push_back(consume());
			createToken(buffer);
		} else if (std::string("\'\"").find(peek()) != std::string::npos) {
			// quotes
			currentChar = peek();
			buffer.push_back(consume());
			while (peek() != 0 && peek() != currentChar)
				buffer.push_back(consume());
			if (peek() == currentChar)
				buffer.push_back(consume());
			createToken(buffer);
		} else if (std::string("(){}").find(peek()) != std::string::npos) {
			// parenthesis and braces
			buffer.push_back(consume());
			createToken(buffer);
		} else if (std::string("=!<>+-*/%").find(peek()) != std::string::npos) {
			// operators and comparison
			buffer.push_back(consume());
			if (peek() == '=')
				buffer.push_back(consume());
			createToken(buffer);
		} else {
			consume();
		}
	}
}
