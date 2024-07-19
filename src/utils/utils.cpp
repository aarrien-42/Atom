#include "utils.hpp"

bool isStrInVector( const std::string& buffer , const std::vector<std::string>& vector ) {
    for (std::vector<std::string>::const_iterator it = vector.begin(); it != vector.end(); it++) {
        if (*it == buffer)
            return true;
    }
    return false;
}

char getStrEndChar( const std::string& str ) {
    return *(str.end()-1);
}

int isParenthesisClosed( ParserManager& parser ) {
    int index = 1; // Starts looking at the next value
    size_t parenLevel;
    bool isParenClosed = false;

    if (parser.peek().value == "(") {
        parenLevel = 1;
        while (true) {
            if (parser.peek(index).type == TokenType::paren) {
                if (parser.peek(index).value == "(") {
                    parenLevel++;
                } else if (parser.peek(index).value == ")") {
                    parenLevel--;
                    if (parenLevel == 0) {
                        isParenClosed = true;
                        break;
                    }
                }
            } else if (parser.peek(index).type == TokenType::enter) {
                break;
            }
            index++;
        }
    }

    if (isParenClosed) {
        return index;
    }
    return isParenClosed;
}
