#include "BinOpNode.hpp"

BinOpNode::BinOpNode( ParserManager& parser ) : ASTNode(NodeType::BinOp), leftOp(nullptr), rightOp(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] BinOpNode created\n", BOLDMAGENTA);
    fillData(parser);
    config.printDebug("[-] BinOpNode\n", RED);
}

BinOpNode::BinOpNode( const BinOpNode& other ) : ASTNode(NodeType::BinOp) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BinOpNode copied\n", BOLDMAGENTA);

    operation = other.operation;
    leftOp = other.leftOp;
    rightOp = other.rightOp;
}

bool BinOpNode::isValid( ParserManager& parser, int& newPos) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;

    bool isLeftValid = (BoxNode::isValid(parser, tmpNewPos) ||
                        LiteralNode::isValid(parser, tmpNewPos) ||
                        IdentifierNode::isValid(parser, tmpNewPos));
    if (!isLeftValid) {
        return false;
    }

    if (parser.peek(tmpNewPos++).type != TokenType::operation) {
        return false;
    }

    bool isRigthValid = (BoxNode::isValid(parser, tmpNewPos) ||
                        LiteralNode::isValid(parser, tmpNewPos) ||
                        IdentifierNode::isValid(parser, tmpNewPos));
    if (!isRigthValid) {
        return false;
    }

    if (isLeftValid && isRigthValid) {
        return true;
    }

    return false;
}

NodeType BinOpNode::getNode(ParserManager& parser, bool isLeft, int newPos) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;

    // Check if it's a BinOpNode
    if (!isLeft) {
        if (BinOpNode::isValid(parser, tmpNewPos)) {
            return NodeType::BinOp;
        }
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

bool BinOpNode::fillDataOp( ParserManager& parser, bool isLeft ) {
    bool filled = true;

    ASTNode** opNode;
    if (isLeft) {
        opNode = &leftOp;
    } else {
        opNode = &rightOp;
    }

    NodeType nodeType = getNode(parser, isLeft);
    switch (nodeType) {
        case NodeType::BinOp: {
            // Multiple operations, only gets here with empty rigthOp
            if (parser.peek(1).value == "*" || parser.peek(1).value == "/") {
                rightOp = new BinOpNode(parser);
            } else {
                rightOp = new LiteralNode(parser);
                BinOpNode* newNode = new BinOpNode(*this);
                leftOp = newNode;
                operation.erase();
                rightOp = nullptr;
                filled = false;
            }
            break;
        }
        case NodeType::Box:
            *opNode = new BoxNode(parser);
            break;
        case NodeType::Literal:
            *opNode = new LiteralNode(parser);
            break;
        case NodeType::Identifier:
            *opNode = new IdentifierNode(parser);
            break;
    }

    return filled;
}

void BinOpNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    int pos = 0;
    if (!BinOpNode::isValid(parser, pos)) {
        // "Invalid BinOp Node"
        return;
    }

    fillDataOp(parser, true);
    while (true) {
        // Fill operation
        operation = parser.consume().value;

        // Try to fill rigth
        if (!fillDataOp(parser, false)) {
            continue;
        }
        break;
    }
}
