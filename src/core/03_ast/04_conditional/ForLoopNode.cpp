#include "ForLoopNode.hpp"

ForLoopNode::ForLoopNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::ForLoop, level), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ForLoopNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void ForLoopNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    (void)parser;
}
