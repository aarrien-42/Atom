#include "WhileLoopNode.hpp"

WhileLoopNode::WhileLoopNode( ParserManager& parser, std::vector<std::string>& scopedVariables ) : ASTNode(NodeType::WhileLoop), scopedVariables(scopedVariables), condition(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] WhileLoopNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void WhileLoopNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    (void)parser;

    config.printDebug("[-] WhileLoopNode\n", RED);
}
