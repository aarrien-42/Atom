#include "atom.hpp"

// TODO: Change class names and class object names to be more readable
int main(int ac, char** av) {
    if (ac < 2) {
        fileReadError(FileReadError::INV_EXEC);
    } else {
        std::string fileName;
        size_t fileExtLen = strlen(FILE_EXT);

        ConfigManager& Config = ConfigManager::getInstance();
        Config.initConfig(&av[1]);
        CodeGeneratorManager CodeGen((Config.isSetExecutableName()) ? Config.getExecutableName() : "atom_out.exe");

        for (int fileNumber = 1; fileNumber < ac; fileNumber++) {
            fileName = av[fileNumber];

            if (fileName.size() == 0) continue;
            if (fileName.size() <= fileExtLen || fileName.compare(fileName.size() - fileExtLen, fileExtLen, FILE_EXT))
                fileReadError(FileReadError::INV_FILE);

            if (Config.canExecuteLexer()) {
                /*-LEXER-*/
                Config.printDebug("\nLEXER:\n\n", BOLDBLUE); // Print state
                LexerManager Lexer(fileName);
                Config.printDebug("TOKEN LIST:\n", BOLDMAGENTA);
                Config.printDebug("Before clean up:\n", BOLDWHITE);
                Lexer.printTokens();
                Config.printDebug("After clean up:\n", BOLDWHITE);
                Lexer.cleanTokens();
                Lexer.printTokens();

                if (Config.canExecuteParser()) {
                    /*-PARSER-*/
                    Config.printDebug("\nPARSER:\n\n", BOLDBLUE); // Print state
                    ParserManager Parser(Lexer.getTokens(), fileName);
                    ProgramNode* program = Parser.getProgram();

                    if (Config.canExecuteCodeGen()) {
                        /*-CODE GENERATOR-*/
                        CodeGen.addProgram(program);
                    }
                }
            }
        }
        // After Compiling every file
        if (Config.canExecuteCodeGen()) {
            /*-CODE GENERATOR-*/
            Config.printDebug("\nCODE GENERATOR:\n\n", BOLDBLUE); // Print state
            CodeGen.writeFullProgramCode();
        }
    }

    return 0;
}
