#include "IdentifierNode.hpp"

IdentifierNode::IdentifierNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Identifier, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] IdentifierNode created\n", BOLDCYAN);

    fillData(parser);
}

bool IdentifierNode::isValid( ParserManager& parser, int& newPos ) {
    int tmpNewPos = newPos;
    bool isValid = false;

    if (parser.peek(tmpNewPos++).type == TokenType::identifier) {
        isValid = true;
    }

    if (isValid) {
        tmpNewPos = newPos;
    }

    return isValid;
}

void IdentifierNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    if (parser.peek().type == identifier) {
        name = parser.consume().value;
        config.printDebug("  Identifier: [" + name + "]\n");
    } else {
        parserNodeError(INV_IDENTIFIER_NODE, parser, "Invalid Identifier Node");
    }

    config.printDebug("[-] IdentifierNode\n", RED);
}
