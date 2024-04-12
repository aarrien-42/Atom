#include "atom.hpp"

int main(int ac, char** av) {
	if (ac != 2)
		fileReadError(FileReadError::INV_EXEC);

	std::string	fileName = av[1];
	size_t		fileExtLen = strlen(FILE_EXT);
	if (fileName.size() <= fileExtLen || fileName.compare(fileName.size() - fileExtLen, fileExtLen, FILE_EXT))
		fileReadError(FileReadError::INV_FILE);

	Lexer L(fileName);
	std::cout << "TOKEN LIST:\n\n";
	std::cout << " * Before clean up:\n";
	L.printTokens();
	std::cout << " * After clean up:\n";
	L.cleanTokens();
	L.printTokens();
	std::cout << "\n";

	std::cout << "PARSER:\n\n";
	Parser P(L.getTokens());

	return 0;
}
