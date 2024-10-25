#include "BinOpNode.hpp"

BinOpNode::BinOpNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::BinOp, level), leftOp(nullptr), rightOp(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BinOpNode created\n", BOLDMAGENTA);

    fillData(parser);
}

BinOpNode::BinOpNode( const BinOpNode& other, size_t level ) : ASTNode(NodeType::BinOp, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BinOpNode copied\n", BOLDMAGENTA);

    operation = other.operation;
    leftOp = other.leftOp;
    rightOp = other.rightOp;
}

bool BinOpNode::isValid( ParserManager& parser, int& newPos ) {
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
    ASTNode** opNode;

    while (true) {
        leftOp == nullptr ? (opNode = &leftOp) : (opNode = &rightOp);

        // Check for subsequent operations
        if (leftOp != nullptr && rightOp != nullptr) {
            config.printDebug("    Check for multiple operations\n");
            if (parser.peek().type == TokenType::operation) {
                config.printDebug("New binary operation: ", GREEN);
                if (parser.peek().value == "+" || parser.peek().value == "-") {
                    config.printDebug("[" + parser.peek().value + "]\n", CYAN);
                    leftOp = new BinOpNode(*this, level++);
                    rightOp = nullptr;
                    operation.erase();
                } else if (parser.peek().value == "*" || parser.peek().value == "/") {
                    config.printDebug("[" + parser.peek().value + "]\n", CYAN);
                    config.printDebug("Current Op [" + operation + "]\n", CYAN);
                    if (operation != "*" && operation != "/") {
                        BinOpNode* newNode = new BinOpNode(*this, level + 1); // level needs to be check
                        rightOp = newNode;
                        newNode->operation = parser.consume().value;
                        newNode->leftOp = newNode->rightOp;
                        newNode->rightOp = nullptr;
                        newNode->fillData(parser);
                    } else {
                        leftOp = new BinOpNode(*this, level++);
                        rightOp = nullptr;
                        operation.erase();
                    }
                }
            } else {
                break;
            }
        }

        if (leftOp != nullptr && operation.empty()) {
            if (parser.peek().type == TokenType::operation) {
                operation = parser.consume().value;
            }
        }

        // Check for literal, identifier or parenthesis
        if (parser.peek().type == TokenType::literal) {
            *opNode = new LiteralNode(parser, level + 1);
        } else if (parser.peek().type == TokenType::identifier) {
            *opNode = new IdentifierNode(parser, level + 1);
        } else if (parser.peek().type == TokenType::paren) {
            if (parser.peek().value == "(") {
                *opNode = new BoxNode(parser, level + 1);
            } else {
                break;
            }
        } else {
            break;
        }
    }

    config.printDebug("[-] BinOpNode\n", RED);
}
