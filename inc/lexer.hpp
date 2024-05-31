#ifndef LEXER_HPP
#define LEXER_HPP

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <vector>
	#include <unordered_map>
	#include "utils.hpp"
	#include "error.hpp"

	#define KEYWORD_IF					"i."
	#define KEYWORD_ELSE				"e."
	#define KEYWORD_IF_ELSE				"ie."
	#define KEYWORD_WHILE				"w."
	#define KEYWORD_FOR					"f."
	#define KEYWORD_VARIABLE			"v."
	#define KEYWORD_PRINT				"p."
	#define KEYWORD_RETURN				"r."

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
	#define COMMENT						"//"
	#define NEW_LINE					"\n"
	#define TAB							"\t"
	#define WHITESPACE					" \v\f\r"

	enum TokenType {
		identifier,             // variable and function name
		literal,                // number, string literal
		keyword,                // if, else, while, for, return, continue, break, variable, print
		operation,              // +, -, *, /, %, =
		comparison,             // ==, !=, <, <=, >, >=
		logic,                  // &&, ||
		bitwise,                // &, |, ^, ~
		paren,                  // (, )
		brace,                  // {, }
		enter,                  // \n
		tab,                    // \t
		comment,                // //
		whitespace,             // spaces
		unknown
	};

	struct Token {
		TokenType	type;
		std::string	value;

		size_t		tabCount;
		size_t		row, column;
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
			void				setToken( std::string& buffer , TokenType tokenType = unknown );

			char				peek();
			char				consume();
			void				tokenize();

			void				cleanTokens();
			void				printTokens();
	};

#endif