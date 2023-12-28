#include "error.hpp"

void	printError( const std::string& str ) {
	std::cerr << str << std::endl;
}

void	exitError( const Error& error ) {
	switch (error) {
		case E_INVALID_EXEC:
			printError("Invalid execution\nUse: ./" + std::string(EXECUTABLE) + " <name>" + std::string(FILE_EXT));
			break;
		case E_INVALID_FILE:
			printError("Invalid file format, file should have " + std::string(FILE_EXT) + " extension");
			break;
		case E_FILE_OPEN:
			printError("File couldn't be opened. Please check the permissions.");
			break;
		default:
			printError("Unknown Error");
			break;
	}
	exit(error + 1);
}