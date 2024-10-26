#include "VarDeclNode.hpp"

VarDeclNode::VarDeclNode( ParserManager& parser, std::vector<std::string>& scopedVariables ) : ASTNode(NodeType::VarDecl), scopedVariables(scopedVariables), initialValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] VarDeclNode created\n", BOLDMAGENTA);
    fillData(parser);
    config.printDebug("[-] VarDeclNode\n", RED);
}

bool VarDeclNode::isValid( ParserManager& parser, int& newPos ) {
    int tmpNewPos = newPos;

    // Check the keyword
    if (parser.peek(tmpNewPos++).value != "v.") {
        return false;
    }

    if (IdentifierNode::isValid(parser, tmpNewPos)) {
        tmpNewPos = newPos;
        return true;
    }

    return false;
}

NodeType VarDeclNode::getNode( ParserManager& parser, int newPos ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;

    // Check if it's an AssignNode
    if (AssignNode::isValid(parser, tmpNewPos)) {
        return NodeType::Assign;
    }

    // Check if it's a IdentifierNode
    if (IdentifierNode::isValid(parser, tmpNewPos)) {
        return NodeType::Identifier;
    }

    return NodeType::Unknown;
}

void VarDeclNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    int pos = 0;
    if (!VarDeclNode::isValid(parser, pos)) {
        // Invalid VarDeclNode Node
        return;
    }

    parser.consume(); // Consume keyword (v.)
    NodeType nodeType = getNode(parser);
    switch (nodeType) {
        case NodeType::Assign:
            initialValue = new AssignNode(parser);
            break;
        case NodeType::Identifier:
            initialValue = new IdentifierNode(parser);
            break;
    }
}
