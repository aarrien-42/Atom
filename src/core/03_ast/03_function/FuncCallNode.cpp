#include "FuncCallNode.hpp"

FuncCallNode::FuncCallNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::FuncCall, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] FuncCallNode created\n", BOLDMAGENTA);
    (void)parser;
}