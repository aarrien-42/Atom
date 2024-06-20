#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "colors.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

enum DebugMode {
    Default, ShowLexer, 
};

/*
    Description:
        - Reads initial arguments and sets compilation configuration
        - Prints colored comments if necesary
        - Can be accessed globally
    Syntax: f:<flags>
        - 'd' => Activate debug mode
        - 'l' => Execute just Lexer
        - 'p' => Execute just Lexer and Parser
        - 'c' => Adds color to certain comments
        - 'o' => After it determine final executable name
*/
class ConfigManager {
    private:
        bool setExecuteLexer;
        bool setExecuteParser;
        bool setExecuteCodeGen;
        bool setColorful;

        bool setDebug; // TODO: add a way to just debug certain compilation states
        DebugMode debugMode;

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

        void printDebug( std::string, std::string = RESET );

};

#endif