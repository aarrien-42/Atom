#ifndef LEXER_HPP
#define LEXER_HPP

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <vector>
	#include "error.hpp"

	#define KEYWORD_IF					"i."
	#define KEYWORD_ELSE				"e."
	#define KEYWORD_IF_ELSE				"ie."
	#define KEYWORD_WHILE				"w."
	#define KEYWORD_FOR					"f."
	#define KEYWORD_RETURN				"r."
	#define KEYWORD_CONTINUE			"c."
	#define KEYWORD_BREAK				"b."

	#define OPERATOR_PLUS				"+"
	#define OPERATOR_MINUS				"-"
	#define OPERATOR_MULTIPLY			"*"
	#define OPERATOR_DIVIDE				"/"
	#define OPERATOR_MODULO				"%"
	#define OPERATOR_ASSIGN				"="

	#define COMPARISON_EQUAL			"=="
	#define COMPARISON_NOT_EQUAL		"!="
	#define COMPARISON_LESS				"<"
	#define COMPARISON_LESS_EQUAL		"<="
	#define COMPARISON_GREATER			">"
	#define COMPARISON_GREATER_EQUAL	">="

	#define LOGICAL_AND					"and"
	#define LOGICAL_OR					"or"

	#define BITWISE_AND					"&"
	#define BITWISE_OR					"|"
	#define BITWISE_XOR					"^"
	#define BITWISE_NOT					"~"

	#define LEFT_PAREN					"("
	#define RIGHT_PAREN					")"
	#define LEFT_BRACE					"{"
	#define RIGHT_BRACE					"}"
	#define SEMICOLON					";"
	#define COMMA						","
	#define COMMENT						"#"
	#define WHITESPACE					" \n\t\v\f\r"

	enum TokenType {
		identifier,		// variable name
		variable,		// number, string literal
		keyword,		// if, else, else if, while, for, return, continue, break
		operator_type,	// +, -, *, /, %, =
		comparison,		// ==, !=, <, <=, >, >=
		logic,			// &&, ||
		bitwise,		// &, |, ^, ~
		paren,			// (, )
		brace,			// {, }
		comment,		// #
		whitespace		// spaces
	};

	struct Token {
		TokenType	_type;
		std::string	_value = "";
	};

	class Lexer {
		private:
			std::string			_sourceFileContent;
			std::vector<Token>	_tokens;
			size_t				_index;
		public:
			Lexer( const std::string& fileName );
			~Lexer();

			std::vector<Token>	getTokens();

			char				peek();
			char				consume();
			void				createToken( std::string& token );
			void				tokenize();
	};

#endif