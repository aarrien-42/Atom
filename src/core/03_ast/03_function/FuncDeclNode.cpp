#include "FuncDeclNode.hpp"

FuncDeclNode::FuncDeclNode( ParserManager& parser ) : ASTNode(NodeType::FuncDecl), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] FuncDeclNode created\n", BOLDMAGENTA);

    fillData(parser);

    config.printDebug("[FuncDeclNode] Final variables:\n", BOLDCYAN);
    printScopedVariables(funcVariables);
}

bool FuncDeclNode::isValid( ParserManager& parser, int& newPos ) {
    int tmpNewPos = newPos;
    bool isValid = false;

    // Check function name
    if (parser.peek(tmpNewPos).type == TokenType::identifier && getStrEndChar(parser.peek(tmpNewPos).value) == ':') {
        tmpNewPos++;
        if (parser.peek(tmpNewPos).type == TokenType::enter) {
            isValid = true;
        } else {
            // Check function parameters
            while (parser.peek(tmpNewPos).type != TokenType::enter) {
                if (IdentifierNode::isValid(parser, tmpNewPos)) {
                    isValid = true;
                } else {
                    isValid = false;
                    break;
                }
            }
        }
    }

    if (isValid) {
        tmpNewPos = newPos;
    }

    return isValid;
}

void FuncDeclNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    // Set the function name
    functionName = parser.consume().value;
    if (parser.peek().type != enter) { // Function has parameters
        while (parser.peek().type != TokenType::enter) {
            if (parser.peek().type == TokenType::identifier)
                parameters.push_back(new IdentifierNode(parser));
            else
                parserNodeError(INV_FUNCDECL_NODE, parser, "Invalid Function declaration node");
        }
    }

    if (parser.peek().type == TokenType::enter)
        parser.consume();

    // Save the function name
    Function* function = parser.addFunction(functionName);
    if (function == nullptr) {
        parserNodeError(INV_FUNCDECL_NODE, parser, "Invalid Function name");
    }

    // Set the function body
    body = new BlockNode(parser, funcVariables, parser.peek().tabCount);

    config.printDebug("[-] FuncDeclNode\n", RED);
}
