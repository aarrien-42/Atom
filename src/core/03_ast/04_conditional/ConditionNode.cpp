#include "ConditionNode.hpp"

// More conditional types need to be implemented
ConditionNode::ConditionNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Condition, level), leftComp(nullptr), rightComp(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ConditionNode created\n", BOLDMAGENTA);
    (void)parser;
    /* STILL NOT IMPLEMENTED */
}