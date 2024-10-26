#include "FuncCallNode.hpp"

FuncCallNode::FuncCallNode( ParserManager& parser ) : ASTNode(NodeType::FuncCall) {
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
