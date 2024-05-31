#include "atom.hpp"

int main(int ac, char** av) {
	if (ac < 2) {
		fileReadError(FileReadError::INV_EXEC);
	} else {
		std::string	fileName;
		size_t		fileExtLen = strlen(FILE_EXT);

		for (int fileNumber = 1; fileNumber < ac; fileNumber++) {
			fileName = av[fileNumber];
			if (fileName.size() <= fileExtLen || fileName.compare(fileName.size() - fileExtLen, fileExtLen, FILE_EXT))
				fileReadError(FileReadError::INV_FILE);

			/*-LEXER-*/
			Lexer L(fileName);
			std::cout << "TOKEN LIST:\n\n";
			std::cout << " * Before clean up:\n";
			L.printTokens();
			std::cout << " * After clean up:\n";
			L.cleanTokens();
			L.printTokens();
			std::cout << "\n";

			/*-PARSER-*/
			std::cout << "PARSER:\n\n";
			Parser P(L.getTokens(), fileName);
			ProgramNode* program = P.getProgram();
			delete program;
		}
	}

	return 0;
}
