#include "WhileLoopNode.hpp"

WhileLoopNode::WhileLoopNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::WhileLoop, level), condition(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] WhileLoopNode created\n", BOLDMAGENTA);
    (void)parser;
    /* STILL NOT IMPLEMENTED */
}