#include "FuncCallNode.hpp"

FuncCallNode::FuncCallNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::FuncCall, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] FuncCallNode created\n", BOLDMAGENTA);

    fillData(parser);
}

bool FuncCallNode::isValid( ParserManager& parser, int& newPos ) {
    int tmpNewPos = newPos;
    bool isValid = false;



    if (isValid) {
        tmpNewPos = newPos;
    }

    return isValid;
}

void FuncCallNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    (void)parser;

    config.printDebug("[-] FuncCallNode\n", RED);
}
