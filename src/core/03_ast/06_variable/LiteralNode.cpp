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

    int parserPos = 0;
    if (!LiteralNode::isValid(parser, parserPos)) {
        parserNodeError(INV_LITERAL_NODE, parser, "Invalid Literal Node");
        return;
    }

    value = parser.consume().value;
    config.printDebug("  Literal: [" + value + "]\n");
}
