#include "ForLoopNode.hpp"

ForLoopNode::ForLoopNode( ParserManager& parser, std::vector<std::string>& scopedVariables ) : ASTNode(NodeType::ForLoop), scopedVariables(scopedVariables), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ForLoopNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void ForLoopNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    (void)parser;

    config.printDebug("[-] ForLoopNode\n", RED);
}
