#ifndef PARSER_HPP
#define PARSER_HPP

	#include <iostream>
	#include <vector>
	#include "lexer.hpp"
	#include "utils.hpp"
	#include "nodes.hpp"
	#include "error.hpp"

	struct Token;
	struct ASTNode;

	class Parser {
		private:
			std::vector<ASTNode>	_tree;
			std::vector<Token>		_tokens;
			size_t					_index;
		public:
			Parser( const std::vector<Token>& );
			~Parser();

			std::vector<ASTNode>	getTree();

			Token					peek( int pos = 0);
			Token					consume();

			void					printTree();
	};

#endif