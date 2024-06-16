#include "config.hpp"

/*-CONSTRUCTOR-*/

Config::Config( std::string filename ) {
    std::ifstream configFile(filename);

    if (!configFile.is_open()) {
        std::cerr << "Failed to open config file: " << filename << std::endl;
    } else {
        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                if (key == "debug") {
                    setDebug = isTrue(value);
                } else if (key == "verbose") {
                    setVerbose = isTrue(value);
                } else if (key == "lexer") {
                    setExecuteTillLexer = isTrue(value);
                } else if (key == "parser") {
                    setExecuteTillParser = isTrue(value);
                } else if (key == "color") {
                    setColorful = isTrue(value);
                } else if (key == "output") {
                    setExecutableName = (value != "\"\"");
                    if (setExecutableName) {
                        executableName = value;
                    }
                }
            }
        }
    }

}

/*-DESTRUCTOR-*/

Config::~Config() {}

/*-METHODS-*/

bool Config::isTrue( std::string str ) {
    return (str == "true" || str == "True" || str == "TRUE" || str == "t" || str == "T");
}

void Config::printDebug( std::string str ) {
    (void)str;
}

void Config::printVerbose( std::string str ) {
    (void)str;
}
