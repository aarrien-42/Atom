#include "config.hpp"

/*-CONSTRUCTOR-*/

ConfigManager::ConfigManager() {
    setDebug = false;
    setExecuteLexer = true;
    setExecuteParser = true;
    setExecuteCodeGen = true;
    setColorful = false;
    setRaw = false;
    setExecutableName = false;
}

/*-METHODS-*/

ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

void ConfigManager::initConfig( char** arguments ) {
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
                        case 'l':
                            setExecuteLexer = true;
                            setExecuteParser = false;
                            setExecuteCodeGen = false;
                            break;
                        case 'p':
                            setExecuteLexer = true;
                            setExecuteParser = true;
                            setExecuteCodeGen = false;
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
                        case 'r':
                            setRaw = true;
                            break;
                        default: std::cerr << "Unknown flag used" << std::endl; break;
                    }
                }
            }
        }
    }
}

void ConfigManager::printDebug( std::string str, std::string strColor ) {
    if (setDebug) {
        if (setColorful) std::cout << strColor;
        std::cout << str;
        if (setColorful) std::cout << RESET;
    }
}
