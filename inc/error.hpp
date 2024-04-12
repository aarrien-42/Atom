#ifndef ERROR_HPP
#define ERROR_HPP

	#include <iostream>
	#include "atom.hpp"

	struct Token;

	// File read based errors
	enum FileReadError {
		INV_EXEC, INV_FILE, FILE_OPEN, UNKNOWN_CHAR
	};

	// Parser errors
	enum ParserNodeError {
		INV_BLOCK_NODE, INV_BOX_NODE, INV_FUNCDECL_NODE, INV_FUNCCALL_NODE,
		INV_CONDITION_NODE, INV_IF_NODE, INV_WHILE_NODE, INV_FOR_NODE,
		INV_BIN_OP_NODE, INV_UNARY_OP_NODE, INV_VARDECL_NODE, INV_ASSIGN_NODE,
		INV_LITERAL_NODE, INV_IDENTIFIER_NODE, INV_RETURN_NODE
	};

	void	printError( const std::string& str );
	
	void	fileReadError( const FileReadError& error, std::string aditionalInfo = "" );
	void	parserNodeError( const ParserNodeError& error, Token errorToken, std::string aditionalInfo = "" );

#endif