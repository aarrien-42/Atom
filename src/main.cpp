#include "atom.hpp"

int main(int ac, char** av) {
	if (ac != 2)
		exitError(E_INVALID_EXEC);

	std::string	file = av[1];
	size_t		fileExtLen = strlen(FILE_EXT);
	if (file.size() <= fileExtLen || file.compare(file.size() - fileExtLen, fileExtLen, FILE_EXT))
		exitError(E_INVALID_FILE);

	return 0;
}
