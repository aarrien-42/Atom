#include "BoxNode.hpp"

BoxNode::BoxNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Box, level) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] BoxNode created\n", BOLDMAGENTA);
    fillData(parser);
    config.printDebug("[-] BoxNode\n", RED);
}

bool BoxNode::isValid( ParserManager& parser, int& newPos, BoxValidNext* nextValid ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;
    bool isValid = false, isParenClosed = false;
    size_t parenLevel = 1;

    bool saveNext = false;
    if (nextValid != nullptr) {
        saveNext = true;
    }

    // Check if parenthesis closes
    if (parser.peek(tmpNewPos).type == TokenType::paren && parser.peek(tmpNewPos).value == "(") {
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

    tmpNewPos = newPos;
    if (isParenClosed) {
        tmpNewPos++;
    
        // Check for BinOpNode
        bool isBinOpNode = false;
        if (tmpNewPos == (newPos + 1)) {
            if (BinOpNode::isValid(parser, tmpNewPos)) {
                isBinOpNode = true;
                if (saveNext)
                    *nextValid = BoxValidNext::BVNbinOp;
            }
        }

        // Check for ConditionalNode
        bool isConditionalNode = false;
        if (tmpNewPos == (newPos + 1)) {

        }

        // Check for BoxNode
        bool isBoxNode = false;
        if (tmpNewPos == (newPos + 1)) {
            if (BinOpNode::isValid(parser, tmpNewPos)) {
                isBoxNode = true;
                if (saveNext)
                    *nextValid = BoxValidNext::BVNbox;
            }
        }

        if (isBinOpNode || isConditionalNode || isBoxNode) {
            isValid = true;
        }
    }

    if (isValid) {
        newPos = tmpNewPos;
    }

    return isValid;
}

void BoxNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    BoxValidNext validNext = BoxValidNext::BVNnone;
    int parserPos = 0;
    if (!BoxNode::isValid(parser, parserPos, &validNext)) {
        parserNodeError(INV_BOX_NODE, parser, "Invalid Box Node");
        return;
    }

    parser.consume(); // Consume open paren
    switch (validNext) {
        case BoxValidNext::BVNbinOp:
            node = new BinOpNode(parser, level);
            break;
        case BoxValidNext::BVNcondition:
            node = new ConditionNode(parser, level);
            break;
        case BoxValidNext::BVNbox:
            node = new BoxNode(parser, level);
            break;
        default:
            parserNodeError(INV_BOX_NODE, parser, "Invalid Box Node");
    }
    parser.consume(); // Consume close paren
}
