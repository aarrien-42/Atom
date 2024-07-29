#include "WhileLoopNode.hpp"

WhileLoopNode::WhileLoopNode( ParserManager& parser, std::vector<std::string>& scopedVariables, size_t level ) : ASTNode(NodeType::WhileLoop, level), scopedVariables(scopedVariables), condition(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] WhileLoopNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void WhileLoopNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    (void)parser;
    (void)config;
}
