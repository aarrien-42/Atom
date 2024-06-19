#include "config.hpp"

/*-CONSTRUCTOR-*/

Config::Config( char** arguments ) {
    setDebug = false;
    setVerbose = false;
    setExecuteTillLexer = false;
    setExecuteTillParser = false;
    setColorful = false;
    setExecutableName = false;


    size_t argCount = 0;
    for (argCount = 0; arguments[argCount] != NULL; argCount++) {
        std::cout << arguments[argCount] << "\n";
    }

    bool requestExecutableName = false;
    for (size_t argIndex = 0; argIndex < argCount; argIndex++) {
        std::string argument(arguments[argIndex]);
        std::cout << "ARGUMENT " << argIndex << " : " << argument << std::endl;

        if (requestExecutableName) {
            requestExecutableName = false;
            setExecutableName = true;
            executableName = argument;
        } else {
            std::string flagReference("f:");

            if (argument.size() > flagReference.size() && argument.find(flagReference) == 0) {
                std::string flags = argument.substr(2);
                std::cout << "FLAGS = " << flags << std::endl;

                for (size_t flagIndex = 0; flagIndex < flags.size(); flagIndex++) {
                    char flag = flags.at(flagIndex);
                    switch (flag) {
                        case 'd':
                            std::cout << "  DEBUG" << std::endl;
                            setDebug = true;
                            break;
                        case 'v':
                            std::cout << "  VERBOSE" << std::endl;
                            setVerbose = true;
                            break;
                        case 'l':
                            std::cout << "  LEXER" << std::endl;
                            setExecuteTillLexer = true;
                            break;
                        case 'p':
                            std::cout << "  PARSER" << std::endl;
                            setExecuteTillParser = true;
                            break;
                        case 'c':
                            std::cout << "  COLOR" << std::endl;
                            setColorful = true;
                            break;
                        case 'o':
                            std::cout << "  OUTPUT" << std::endl;
                            if (argIndex + 1 != argCount) {
                                requestExecutableName = true;
                            } else {
                                std::cout << "No executable name found" << std::endl;
                            }
                            break;
                        default: std::cout << "  UNKNOWN" << std::endl; break;
                    }
                }
            }
        }
    }
}

/*-DESTRUCTOR-*/

Config::~Config() {
    std::cout << setDebug << setVerbose << setExecuteTillLexer << setExecuteTillParser << setColorful << std::endl;
    if (setExecutableName) std::cout << executableName << std::endl;
}

/*-METHODS-*/

void Config::printDebug( std::string str ) {
    // Will only print if it's set to debug
    (void)str;
}

void Config::printVerbose( std::string str ) {
    // Will only print if it's set to vebose
    (void)str;
}
