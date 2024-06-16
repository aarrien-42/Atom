#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "colors.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/*
    Description:
        - Reads initial arguments and sets compilation configuration
        - Prints colored comments if necesary
        - Can be accessed globally
    Initial idea:
        - '-d' or '--debug'   => Activate just debug comments
        - '-v' or '--verbose' => Show detailed printings
        - '-l' or '--lexer'   => Execute just Lexer
        - '-p' or '--parser'  => Execute just Lexer and Parser
        - '-c' or '--color'   => Adds color to certain comments
        - '-o' or '--output'  => After it determine final executable name
    Final idea: All the configuration flags go into a file
*/
class Config {
    private:
        bool setDebug;
        bool setVerbose;
        bool setExecuteTillLexer;
        bool setExecuteTillParser;
        bool setColorful;

        bool setExecutableName;
        std::string executableName;
    public:
        Config( std::string );
        ~Config();

        bool isTrue( std::string );
        bool isSetExecutableName() { return setExecutableName; }
        std::string getExecutableName() { return executableName; }

        bool canExecuteLexer() { return setExecuteTillLexer;}
        bool canExecuteParser() { return setExecuteTillParser;}

        void printDebug( std::string );
        void printVerbose( std::string );

};

#endif