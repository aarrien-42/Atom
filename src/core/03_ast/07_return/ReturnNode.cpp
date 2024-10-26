#include "ReturnNode.hpp"

ReturnNode::ReturnNode( ParserManager& parser, std::vector<std::string>& scopedVariables ) : ASTNode(NodeType::Return), scopedVariables(scopedVariables), returnValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();

    config.printDebug("[*] ReturnNode created\n", BOLDMAGENTA);
    fillData(parser);
    config.printDebug("[-] ReturnNode\n", RED);
}

bool ReturnNode::isValid( ParserManager& parser, int& newPos, ReturnValidNext* validNext ) {
    ConfigManager& config = ConfigManager::getInstance();
    int tmpNewPos = newPos;
    bool isValid = false;

    bool saveNext = false;
    if (validNext != nullptr) {
        saveNext = true;
    }

    // Check keyword
    if (parser.peek(tmpNewPos++).value != "r.") {
        return false;
    }

    // Check if it's a BoxNode
    bool isBoxNode = false;
    if (tmpNewPos == (newPos + 1)) {
        isBoxNode = BoxNode::isValid(parser, tmpNewPos);
        if (saveNext)
            *validNext = ReturnValidNext::RVNbox;
    }

    // Check if it's a BinOpNode
    bool isBinOpNode = false;
    if (tmpNewPos == (newPos + 1)) {
        isBinOpNode = BinOpNode::isValid(parser, tmpNewPos);
        if (saveNext)
            *validNext = ReturnValidNext::RVNbinOp;
    }

    // Check if it's a LiteralNode
    bool isLiteralNode = false;
    if (tmpNewPos == (newPos + 1)) {
        isLiteralNode = LiteralNode::isValid(parser, tmpNewPos);
        if (saveNext)
            *validNext = ReturnValidNext::RVNliteral;
    }

    // Check if it's a IdentifierNode
    bool isIdentifierNode = false;
    if (tmpNewPos == (newPos + 1)) {
        isIdentifierNode = IdentifierNode::isValid(parser, tmpNewPos);
        if (saveNext)
            *validNext = ReturnValidNext::RVNidentifier;
    }

    if (isBoxNode || isBinOpNode || isLiteralNode || isIdentifierNode) {
        if (parser.peek(tmpNewPos).type == TokenType::enter) {
            isValid = true;
        }
    }

    if (isValid) {
        newPos = tmpNewPos;
    }

    return isValid;
}

void ReturnNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    ReturnValidNext validNext = ReturnValidNext::RVNnone;
    int parserPos = 0;
    if (!ReturnNode::isValid(parser, parserPos, &validNext)) {
        parserNodeError(INV_RETURN_NODE, parser, "Invalid Return Node");
        return;
    }

    if (parser.peek().value == "r.") {
        parser.consume();
        switch (validNext) {
            case ReturnValidNext::RVNbox:
                returnValue = new BoxNode(parser);
                break;
            case ReturnValidNext::RVNbinOp:
                returnValue = new BinOpNode(parser);
                break;
            case ReturnValidNext::RVNliteral:
                returnValue = new LiteralNode(parser);
                break;
            case ReturnValidNext::RVNidentifier:
                returnValue = new IdentifierNode(parser);
                break;
            default:
                parserNodeError(INV_RETURN_NODE, parser, "Invalid Return Node");
        }
    }
}
