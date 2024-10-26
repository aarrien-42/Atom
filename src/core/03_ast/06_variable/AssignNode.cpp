#include "AssignNode.hpp"

AssignNode::AssignNode( ParserManager& parser ) : ASTNode(NodeType::Assign), value(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] AssignNode created\n", BOLDMAGENTA);
    fillData(parser);
    config.printDebug("[-] AssignNode\n", RED);
}

bool AssignNode::isValid( ParserManager& parser, int& newPos ) {
    int tmpNewPos = newPos;
    bool isValid = false;

    // Check variable name
    if (parser.peek(tmpNewPos++).type != TokenType::identifier) {
        return false;
    }

    // Check for the equal
    if (parser.peek(tmpNewPos++).value != "=") {
        return false;
    }

    // Check if it's a BoxNode
    bool isBoxNode = BoxNode::isValid(parser, tmpNewPos);

    // Check if it's a BinOpNode
    bool isBinOpNode = BinOpNode::isValid(parser, tmpNewPos);

    // Check if it's a LiteralNode
    bool isLiteralNode = LiteralNode::isValid(parser, tmpNewPos);

    // Check if it's a IdentifierNode
    bool isIdentifierNode = IdentifierNode::isValid(parser, tmpNewPos);

    if (isBoxNode || isBinOpNode || isLiteralNode || isIdentifierNode) {
        newPos = tmpNewPos;
        return true;
    }

    return false;
}

NodeType AssignNode::getNode( ParserManager& parser, int newPos = 0 ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos + 2; // Jump variable name and equal

    // Check if it's a BinOpNode
    if (BinOpNode::isValid(parser, tmpNewPos)) {
        return NodeType::BinOp;
    }

    // Check if it's a BoxNode
    if (BoxNode::isValid(parser, tmpNewPos)) {
        return NodeType::Box;
    }

    // Check if it's a LiteralNode
    if (LiteralNode::isValid(parser, tmpNewPos)) {
        return NodeType::Literal;
    }

    // Check if it's a IdentifierNode
    if (IdentifierNode::isValid(parser, tmpNewPos)) {
        return NodeType::Identifier;
    }

    return NodeType::Unknown;
}

void AssignNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    int pos = 0;
    if (!AssignNode::isValid(parser, pos)) {
        // Invalid AssignNode
        return;
    }

    NodeType nodeType = getNode(parser);
    variableName = parser.consume().value; // Variable name
    parser.consume(); // Equal
    switch (nodeType) {
        case NodeType::Box:
            value = new BoxNode(parser);
            break;
        case NodeType::BinOp:
            value = new BinOpNode(parser);
            break;
        case NodeType::Literal:
            value = new LiteralNode(parser);
            break;
        case NodeType::Identifier:
            value = new IdentifierNode(parser);
            break;
    }

}
