#include "ReturnNode.hpp"

ReturnNode::ReturnNode( ParserManager& parser, std::vector<std::string>& scopedVariables ) : ASTNode(NodeType::Return), scopedVariables(scopedVariables), returnValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] ReturnNode created\n", BOLDMAGENTA);
    fillData(parser);
    config.printDebug("[-] ReturnNode\n", RED);
}

bool ReturnNode::isValid( ParserManager& parser, int& newPos ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;

    // Check keyword
    if (parser.peek(tmpNewPos++).value != "r.") {
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

NodeType ReturnNode::getNode( ParserManager& parser, int newPos ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos + 1; // Jump keyword (r.)

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

void ReturnNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    int pos = 0;
    if (!ReturnNode::isValid(parser, pos)) {
        parserNodeError(INV_RETURN_NODE, parser, "Invalid Return Node");
        return;
    }

    NodeType nodeType = getNode(parser);
    if (parser.peek().value == "r.") {
        parser.consume();
        switch (nodeType) {
            case NodeType::Box:
                returnValue = new BoxNode(parser);
                break;
            case NodeType::BinOp:
                returnValue = new BinOpNode(parser);
                break;
            case NodeType::Literal:
                returnValue = new LiteralNode(parser);
                break;
            case NodeType::Identifier:
                returnValue = new IdentifierNode(parser);
                break;
            default:
                parserNodeError(INV_RETURN_NODE, parser, "Invalid Return Node");
        }
    }
}
