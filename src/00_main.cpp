#include "atom.hpp"

// TODO: Change class names and class object names to be more readable
int main(int ac, char** av) {
    if (ac < 2) {
        fileReadError(FileReadError::INV_EXEC);
    } else {
        std::string fileName;
        size_t fileExtLen = strlen(FILE_EXT);

        Config C(&av[1]);
        return 0;
        CodeGenerator CG((C.isSetExecutableName()) ? C.getExecutableName() : "atom.exe");

        for (int fileNumber = 1; fileNumber < ac; fileNumber++) {
            fileName = av[fileNumber];
            if (fileName.size() <= fileExtLen || fileName.compare(fileName.size() - fileExtLen, fileExtLen, FILE_EXT))
                fileReadError(FileReadError::INV_FILE);

            /*-LEXER-*/
            Lexer L(fileName);
            std::cout << BOLDBLUE << "\nTOKEN LIST:\n\n" << RESET;
            std::cout << " * Before clean up:\n";
            L.printTokens();
            std::cout << " * After clean up:\n";
            L.cleanTokens();
            L.printTokens();
            std::cout << "\n";

            /*-PARSER-*/
            std::cout << BOLDBLUE << "\nPARSER:\n\n" << RESET;
            Parser P(L.getTokens(), fileName);
            ProgramNode* program = P.getProgram();

            /*-CODE GENERATOR-*/
            CG.addProgram(program);
        }
        std::cout << BOLDBLUE << "\nCODE GENERATOR:\n\n" << RESET;
        CG.writeFullProgramCode();
    }

    return 0;
}
