#include "LiteralNode.hpp"

LiteralNode::LiteralNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Literal, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] LiteralNode created\n", BOLDCYAN);

    fillData(parser);
}

bool LiteralNode::isValid( ParserManager& parser, int& newPos ) {
    int tmpNewPos = newPos;
    bool isValid = false;

    if (parser.peek(tmpNewPos++).type == TokenType::literal) {
        isValid = true;
    }

    if (isValid) {
        newPos = tmpNewPos;
    }

    return isValid;
}

void LiteralNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    if (parser.peek().type == literal) {
        value = parser.consume().value;
        config.printDebug("  Literal: [" + value + "]\n");
    } else {
        parserNodeError(INV_LITERAL_NODE, parser, "Invalid Literal Node");
    }

    config.printDebug("[-] LiteralNode\n", RED);
}
