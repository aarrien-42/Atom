#include "atom.hpp"

int main(int ac, char** av) {
	if (ac != 2)
		exitError(E_INVALID_EXEC);

	std::string	fileName = av[1];
	size_t		fileExtLen = strlen(FILE_EXT);
	if (fileName.size() <= fileExtLen || fileName.compare(fileName.size() - fileExtLen, fileExtLen, FILE_EXT))
		exitError(E_INVALID_FILE);

	Lexer L(fileName);
	std::cout << "TOKEN LIST:\n\n";
	L.printTokens();
	std::cout << "\n";

	std::cout << "PARSER:\n\n";
	Parser P(L.getTokens());

	return 0;
}
