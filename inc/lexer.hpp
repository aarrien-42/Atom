#ifndef LEXER_HPP
#define LEXER_HPP

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <vector>
	#include <unordered_map>
	#include "error.hpp"

	enum TokenType {
		identifier_var,				// variable and function name
		identifier_func,
		variable_num,				// number, string literal
		variable_string,
		keyword_if,					// if, else, else if, while, for, return, continue, break
		keyword_else,
		keyword_if_else,
		keyword_while,
		keyword_for,
		keyword_return,
		keyword_continue,
		keyword_break,
		keyword_variable,
		keyword_print,
		operator_plus,				// +, -, *, /, %, =
		operator_minus,
		operator_multiply,
		operator_divide,
		operator_modulus,
		operator_assign,
		comparison_equal,			// ==, !=, <, <=, >, >=
		comparison_not_equal,
		comparison_less,
		comparison_less_equal,
		comparison_greater,
		comparison_greater_equal,
		logic_and,					// &&, ||
		logic_or,
		bitwise_and,				// &, |, ^, ~
		bitwise_or,
		bitwise_xor,
		bitwise_not,
		paren_open,					// (, )
		paren_close,
		brace_open,					// {, }
		brace_close,
		comment,					// #
		whitespace					// spaces
	};

	static const std::unordered_map<std::string, TokenType> tokenMap = {
		{"i.", keyword_if},
		{"e.", keyword_else},
		{"ie.", keyword_if_else},
		{"w.", keyword_while},
		{"f.", keyword_for},
		{"r.", keyword_return},
		{"c.", keyword_continue},
		{"b.", keyword_break},
		{"v.", keyword_variable},
		{"p.", keyword_print},
		{"+", operator_plus},
		{"-", operator_minus},
		{"*", operator_multiply},
		{"/", operator_divide},
		{"%", operator_modulus},
		{"=", operator_assign},
		{"==", comparison_equal},
		{"!=", comparison_not_equal},
		{"<", comparison_less},
		{"<=", comparison_less_equal},
		{">", comparison_greater},
		{">=", comparison_greater_equal},
		{"and", logic_and},
		{"or", logic_or},
		{"&", bitwise_and},
		{"|", bitwise_or},
		{"^", bitwise_xor},
		{"~", bitwise_not},
		{"(", paren_open},
		{")", paren_close},
		{"{", brace_open},
		{"}", brace_close}
	};

	struct Token {
		TokenType	_type {};
		std::string	_value;
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
			void				createToken( std::string& buffer );
			void				tokenize();

			void				printTokens();
	};

#endif