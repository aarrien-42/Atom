#include "IdentifierNode.hpp"

IdentifierNode::IdentifierNode( ParserManager& parser ) : ASTNode(NodeType::Identifier) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] IdentifierNode created\n", BOLDCYAN);
    fillData(parser);
    config.printDebug("[-] IdentifierNode\n", RED);
}

bool IdentifierNode::isValid( ParserManager& parser, int& newPos ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;

    if (parser.peek(tmpNewPos++).type == TokenType::identifier) {
        newPos = tmpNewPos;
        return true;
    }

    return false;
}

void IdentifierNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();


    int pos = 0;
    if (!IdentifierNode::isValid(parser, pos)) {
        parserNodeError(INV_IDENTIFIER_NODE, parser, "Invalid Identifier Node");
        return;
    }

    name = parser.consume().value;
    config.printDebug("  Identifier: [" + name + "]\n");
}
