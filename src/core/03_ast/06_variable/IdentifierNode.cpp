#include "IdentifierNode.hpp"

IdentifierNode::IdentifierNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Identifier, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] IdentifierNode created\n", BOLDCYAN);

    fillData(parser);
}

void IdentifierNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    if (parser.peek().type == identifier) {
        name = parser.consume().value;
        config.printDebug("  Identifier: [" + name + "]\n");
    } else {
        parserNodeError(INV_IDENTIFIER_NODE, parser.consume(), "Invalid Identifier Node");
    }
}
