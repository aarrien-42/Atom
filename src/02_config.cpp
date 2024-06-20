#include "config.hpp"

/*-CONSTRUCTOR-*/

Config::Config( char** arguments ) {
    setDebug = false;
    setVerbose = false;
    setExecuteTillLexer = false;
    setExecuteTillParser = false;
    setColorful = false;
    setExecutableName = false;

    // Get argument count
    size_t argCount = 0;
    while (arguments[argCount] != NULL) {
        argCount++;
    }

    // Loop each argument
    bool requestExecutableName = false;
    for (size_t argIndex = 0; argIndex < argCount; argIndex++) {
        std::string argument(arguments[argIndex]);

        if (requestExecutableName) {
            requestExecutableName = false;
            setExecutableName = true;
            executableName = argument;
            arguments[argIndex][0] = '\0'; // Discard it as program file
        } else {
            std::string flagReference("f:");

            // Set flags
            if (argument.size() > flagReference.size() && argument.find(flagReference) == 0) {
                std::string flags = argument.substr(2);
                arguments[argIndex][0] = '\0'; // Discard it as program file

                for (size_t flagIndex = 0; flagIndex < flags.size(); flagIndex++) {
                    char flag = flags.at(flagIndex);
                    switch (flag) {
                        case 'd':
                            setDebug = true;
                            break;
                        case 'v':
                            setVerbose = true;
                            break;
                        case 'l':
                            setExecuteTillLexer = true;
                            break;
                        case 'p':
                            setExecuteTillLexer = false;
                            setExecuteTillParser = true;
                            break;
                        case 'c':
                            setColorful = true;
                            break;
                        case 'o':
                            if (argIndex + 1 != argCount) {
                                requestExecutableName = true;
                            } else {
                                std::cerr << "No executable name found" << std::endl;
                            }
                            break;
                        default: std::cerr << "Unknown flag used" << std::endl; break;
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
