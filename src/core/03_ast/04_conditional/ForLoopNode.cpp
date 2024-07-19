#include "ForLoopNode.hpp"

ForLoopNode::ForLoopNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::ForLoop, level), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ForLoopNode created\n", BOLDMAGENTA);
    (void)parser;
    /* STILL NOT IMPLEMENTED */
}