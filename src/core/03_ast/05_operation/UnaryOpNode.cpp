#include "UnaryOpNode.hpp"

UnaryOpNode::UnaryOpNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::UnaryOp, level), operand(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] UnaryOpNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void UnaryOpNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    (void)parser;
}
