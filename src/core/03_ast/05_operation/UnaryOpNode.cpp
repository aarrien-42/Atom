#include "UnaryOpNode.hpp"

UnaryOpNode::UnaryOpNode( ParserManager& parser ) : ASTNode(NodeType::UnaryOp), operand(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] UnaryOpNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void UnaryOpNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    (void)parser;

    config.printDebug("[-] UnaryOpNode\n", RED);
}
