#include "BoxNode.hpp"

BoxNode::BoxNode( ParserManager& parser ) : ASTNode(NodeType::Box) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] BoxNode created\n", BOLDMAGENTA);
    fillData(parser);
    config.printDebug("[-] BoxNode\n", RED);
}

bool BoxNode::isValid( ParserManager& parser, int& newPos ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;
    bool isParenClosed = false;

    // Check if parenthesis closes
    if (parser.peek(tmpNewPos).type == TokenType::paren && parser.peek(tmpNewPos).value == "(") {
        size_t parenLevel = 1;
        tmpNewPos++;
        while (true) {
            if (parser.peek(tmpNewPos).type == TokenType::paren) {
                if (parser.peek(tmpNewPos).value == "(") {
                    parenLevel++;
                } else if (parser.peek(tmpNewPos).value == ")") {
                    parenLevel--;
                    if (parenLevel == 0) {
                        isParenClosed = true;
                        break;
                    }
                }
            } else if (parser.peek(tmpNewPos).type == TokenType::enter) {
                break;
            }
            tmpNewPos++;
        }
    }
    tmpNewPos++;

    if (isParenClosed) {
        newPos = tmpNewPos;
        return true;
    }

    return false;
}

NodeType BoxNode::getNode( ParserManager& parser, int newPos ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;

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

void BoxNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    int parserPos = 0;
    if (!BoxNode::isValid(parser, parserPos)) {
        parserNodeError(INV_BOX_NODE, parser, "Invalid Box Node");
        return;
    }

    parser.consume(); // Consume open paren
    NodeType nodeType = getNode(parser);
    switch (nodeType) {
        case NodeType::BinOp:
            node = new BinOpNode(parser);
            break;
        case NodeType::Box:
            node = new BoxNode(parser);
            break;
        case NodeType::Literal:
            node = new LiteralNode(parser);
            break;
        case NodeType::Identifier:
            node = new IdentifierNode(parser);
            break;
        default:
            parserNodeError(INV_BOX_NODE, parser, "Invalid Box Node");
    }
    parser.consume(); // Consume close paren
}
