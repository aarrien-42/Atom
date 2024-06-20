#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "colors.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

/*
    Description:
        - Reads initial arguments and sets compilation configuration
        - Prints colored comments if necesary
        - Can be accessed globally
    Syntax: f:<flags>
        - 'd' => Activate just debug comments
        - 'v' => Show detailed printings
        - 'l' => Execute just Lexer
        - 'p' => Execute just Lexer and Parser
        - 'c' => Adds color to certain comments
        - 'o' => After it determine final executable name
*/
class ConfigManager {
    private:
        bool setDebug;
        bool setVerbose;
        bool setExecuteLexer;
        bool setExecuteParser;
        bool setExecuteCodeGen;
        bool setColorful;

        bool setExecutableName;
        std::string executableName;
    public:
        ConfigManager( char** );
        ~ConfigManager();

        bool isSetExecutableName() { return setExecutableName; }
        std::string getExecutableName() { return executableName; }

        bool canExecuteLexer() { return setExecuteLexer;}
        bool canExecuteParser() { return setExecuteParser;}
        bool canExecuteCodeGen() { return setExecuteCodeGen;}

        void printDebug( std::string );
        void printVerbose( std::string );

};

#endif