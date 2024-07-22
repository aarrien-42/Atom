#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iostream>

#include "parser.hpp"
class ParserManager;

bool isStrInVector( const std::string& buffer , const std::vector<std::string>& vector );
char getStrEndChar( const std::string& str );

int isParenthesisClosed( ParserManager& );
void printScopedVariables( std::vector<std::string>& );

#endif