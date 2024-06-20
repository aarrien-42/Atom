#include "atom.hpp"

// TODO: Change class names and class object names to be more readable
int main(int ac, char** av) {
    if (ac < 2) {
        fileReadError(FileReadError::INV_EXEC);
    } else {
        std::string fileName;
        size_t fileExtLen = strlen(FILE_EXT);

        ConfigManager Config(&av[1]);
        CodeGeneratorManager CodeGen((Config.isSetExecutableName()) ? Config.getExecutableName() : "atom.exe");

        for (int fileNumber = 1; fileNumber < ac; fileNumber++) {
            fileName = av[fileNumber];

            if (fileName.size() == 0) continue;
            if (fileName.size() <= fileExtLen || fileName.compare(fileName.size() - fileExtLen, fileExtLen, FILE_EXT))
                fileReadError(FileReadError::INV_FILE);

            /*-LEXER-*/
            LexerManager Lexer(fileName);
            std::cout << BOLDBLUE << "\nTOKEN LIST:\n\n" << RESET;
            std::cout << " * Before clean up:\n";
            Lexer.printTokens();
            std::cout << " * After clean up:\n";
            Lexer.cleanTokens();
            Lexer.printTokens();
            std::cout << "\n";

            /*-PARSER-*/
            std::cout << BOLDBLUE << "\nPARSER:\n\n" << RESET;
            ParserManager Parser(Lexer.getTokens(), fileName);
            ProgramNode* program = Parser.getProgram();

            /*-CODE GENERATOR-*/
            CodeGen.addProgram(program);
        }
        std::cout << BOLDBLUE << "\nCODE GENERATOR:\n\n" << RESET;
        CodeGen.writeFullProgramCode();
    }

    return 0;
}
