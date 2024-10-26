#include "LiteralNode.hpp"

LiteralNode::LiteralNode( ParserManager& parser ) : ASTNode(NodeType::Literal) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] LiteralNode created\n", BOLDCYAN);
    fillData(parser);
    config.printDebug("[-] LiteralNode\n", RED);
}

bool LiteralNode::isValid( ParserManager& parser, int& newPos ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;

    if (parser.peek(tmpNewPos++).type == TokenType::literal) {
        newPos = tmpNewPos;
        return true;
    }

    return false;
}

void LiteralNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    int pos = 0;
    if (!LiteralNode::isValid(parser, pos)) {
        parserNodeError(INV_LITERAL_NODE, parser, "Invalid Literal Node");
        return;
    }

    value = parser.consume().value;
    config.printDebug("  Literal: [" + value + "]\n");
}
