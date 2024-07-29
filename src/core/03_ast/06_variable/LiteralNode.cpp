#include "LiteralNode.hpp"

LiteralNode::LiteralNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Literal, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] LiteralNode created\n", BOLDCYAN);

    fillData(parser);
}

void LiteralNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    if (parser.peek().type == literal) {
        value = parser.consume().value;
        config.printDebug("  Literal: [" + value + "]\n");
    } else {
        parserNodeError(INV_LITERAL_NODE, parser, "Invalid Literal Node");
    }
}
