#include "FuncDeclNode.hpp"

FuncDeclNode::FuncDeclNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::FuncDecl, level), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] FuncDeclNode created\n", BOLDMAGENTA);

    fillData(parser);

    config.printDebug("[FuncDeclNode] Final variables:\n", BOLDCYAN);
    printScopedVariables(funcVariables);
}

void FuncDeclNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    // Set the function name
    functionName = parser.consume().value;
    if (parser.peek().type != enter) { // Function has parameters
        while (parser.peek().type != TokenType::enter) {
            if (parser.peek().type == TokenType::identifier)
                parameters.push_back(new IdentifierNode(parser, this->level + 1));
            else
                parserNodeError(INV_FUNCDECL_NODE, parser.consume(), "Invalid Function declaration node");
        }
    }

    if (parser.peek().type == TokenType::enter)
        parser.consume();

    // Save the function name
    Function* function = parser.addFunction(functionName);
    if (function == nullptr) {
        parserNodeError(INV_FUNCDECL_NODE, parser.consume(), "Invalid Function name");
    }

    // Set the function body
    body = new BlockNode(parser, funcVariables, parser.peek().tabCount, this->level + 1);
}
