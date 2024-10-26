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

bool BinOpNode::isValid( ParserManager& parser, int& newPos, BinOpValidNext* nextValid ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;
    bool isValid = false;

    // Check for <box><operation><box>
    bool isBoxOpBox = false;
    if (tmpNewPos == newPos) {
        if (BoxNode::isValid(parser, tmpNewPos)) {
            if (parser.peek(tmpNewPos).type == TokenType::operation) {
                tmpNewPos++;
                if (BoxNode::isValid(parser, tmpNewPos)) {
                    isBoxOpBox = true;
                }
            }
        }
    }

    if (!isBoxOpBox) {
        tmpNewPos = newPos;
    }

    // Check for <box><operation><literal>
    bool isBoxOpLit = false;
    if (tmpNewPos == newPos) {
        if (BoxNode::isValid(parser, tmpNewPos)) {
            if (parser.peek(tmpNewPos).type == TokenType::operation) {
                tmpNewPos++;
                if (LiteralNode::isValid(parser, tmpNewPos)) {
                    isBoxOpLit = true;
                }
            }
        }
    }

    if (!isBoxOpLit) {
        tmpNewPos = newPos;
    }

    // Check for <literal><operation><box>
    bool isLitOpBox = false;
    if (tmpNewPos == newPos) {
        if (LiteralNode::isValid(parser, tmpNewPos)) {
            if (parser.peek(tmpNewPos).type == TokenType::operation) {
                tmpNewPos++;
                if (BoxNode::isValid(parser, tmpNewPos)) {
                    isLitOpBox = true;
                }
            }
        }
    }

    if (!isLitOpBox) {
        tmpNewPos = newPos;
    }

    // Check for <literal><operation><literal>
    bool isLitOpLit = false;
    if (tmpNewPos == newPos) {
        if (LiteralNode::isValid(parser, tmpNewPos)) {
            if (parser.peek(tmpNewPos).type == TokenType::operation) {
                tmpNewPos++;
                if (LiteralNode::isValid(parser, tmpNewPos)) {
                    isLitOpLit = true;
                }
            }
        }
    }

    if (!isLitOpLit) {
        tmpNewPos = newPos;
    }

    if (isBoxOpBox || isBoxOpLit || isLitOpBox || isLitOpLit) {
        isValid = true;
    }

    if (isValid) {
        newPos = tmpNewPos;
    }

    return isValid;
}

void BinOpNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    BinOpValidNext validNext = BinOpValidNext::BOVNnone;
    int parserPos = 0;
    if (!BinOpNode::isValid(parser, parserPos, &validNext)) {
        // "Invalid BinOp Node"
        return;
    }

    switch (validNext) {
        case BinOpValidNext::BOVNboxOpBox:
            leftOp = new BoxNode(parser);
            operation = parser.consume().value;
            rightOp = new BoxNode(parser);
            break;
        case BinOpValidNext::BOVNlitOpBox:
            leftOp = new LiteralNode(parser);
            operation = parser.consume().value;
            rightOp = new BoxNode(parser);
            break;
        case BinOpValidNext::BOVNboxOpLit:
            leftOp = new BoxNode(parser);
            operation = parser.consume().value;
            rightOp = new LiteralNode(parser);
            break;
        case BinOpValidNext::BOVNlitOpLit:
            leftOp = new LiteralNode(parser);
            operation = parser.consume().value;
            rightOp = new LiteralNode(parser);
            break;
    }
}
