#include "error.hpp"

void	printError( const std::string& str ) {
	std::cerr << str << std::endl;
}

void	fileReadError( const FileReadError& error , std::string aditionalInfo ) {
	switch (error) {
		case INV_EXEC:
			printError("Invalid execution\nUse: ./" + std::string(EXECUTABLE) + " <name>" + std::string(FILE_EXT)); break;
		case INV_FILE:
			printError("Invalid file format, file should have " + std::string(FILE_EXT) + " extension"); break;
		case FILE_OPEN:
			printError("File couldn't be opened. Please check the permissions."); break;
		case UNKNOWN_CHAR:
			printError("Unknown character used: " + aditionalInfo); break;
		default:
			printError("Unknown Error"); break;
	}

	exit(100 + error);
}

void	parserNodeError( const ParserNodeError& error, Token errorToken, std::string aditionalInfo ) {
	switch (error) {
		case INV_BLOCK_NODE:
			printError("BlockNode: " + aditionalInfo); break;
		case INV_BOX_NODE:
			printError("BoxNode: " + aditionalInfo); break;
		case INV_FUNCDECL_NODE:
			printError("FuncDeclNode: " + aditionalInfo); break;
		case INV_FUNCCALL_NODE:
			printError("FuncCallNode: " + aditionalInfo); break;
		case INV_CONDITION_NODE:
			printError("ConditionNode: " + aditionalInfo); break;
		case INV_IF_NODE:
			printError("IfStatementNode: " + aditionalInfo); break;
		case INV_WHILE_NODE:
			printError("WhileLoopNode: " + aditionalInfo); break;
		case INV_FOR_NODE:
			printError("ForLoopNode: " + aditionalInfo); break;
		case INV_BIN_OP_NODE:
			printError("BinOpNode: " + aditionalInfo); break;
		case INV_UNARY_OP_NODE:
			printError("UnaryOpNode: " + aditionalInfo); break;
		case INV_VARDECL_NODE:
			printError("VarDeclNode: " + aditionalInfo); break;
		case INV_ASSIGN_NODE:
			printError("AssignNode: " + aditionalInfo); break;
		case INV_LITERAL_NODE:
			printError("LiteralNode: " + aditionalInfo); break;
		case INV_IDENTIFIER_NODE:
			printError("IdentifierNode: " + aditionalInfo); break;
		case INV_RETURN_NODE:
			printError("ReturnNode: " + aditionalInfo); break;
	}

	std::cerr << "Error at -> " << errorToken.row << ":" << errorToken.column << std::endl;
	exit(200 + error);
}