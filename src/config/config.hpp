#pragma once

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
        - Can be accessed globally (singleton instance)
    Syntax: f:<flags>
        - 'd' => Activate debug mode
        - 'l' => Execute just Lexer
        - 'p' => Execute just Lexer and Parser
        - 'c' => Adds color to certain comments
        - 'o' => After it determine final executable name
        - 'r' => Doesn't remove the .asm file after compiling and linking
*/
class ConfigManager {
    private:
        bool setExecuteLexer;
        bool setExecuteParser;
        bool setExecuteCodeGen;
        bool setColorful;
        bool setRaw;

        bool setDebug; // TODO: add a way to just debug certain compilation states
        DebugMode debugMode;

        bool setExecutableName;
        std::string executableName;

        ConfigManager();
    public:
        static ConfigManager& getInstance();
        void initConfig( char** );

        bool isSetExecutableName() { return setExecutableName; }
        std::string getExecutableName() { return executableName; }

        bool canExecuteLexer() { return setExecuteLexer;}
        bool canExecuteParser() { return setExecuteParser;}
        bool canExecuteCodeGen() { return setExecuteCodeGen;}

        bool canRemoveAssemblyCode() { return !setRaw;}

        void printDebug( std::string, std::string = RESET );

};
