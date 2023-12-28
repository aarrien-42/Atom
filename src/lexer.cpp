#include "lexer.hpp"

Lexer::Lexer( const std::string& fileName ) {
	// Open the file
	std::ifstream inputFile(fileName);

	// Check if the file is open
	if (!inputFile.is_open())
		exitError(E_FILE_OPEN);

	// Read the file content into a string
	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	std::string fileContent = buffer.str();

	// Close the file
	inputFile.close();

	// Display the content
	std::cout << "File Content:\n" << fileContent << std::endl;
}