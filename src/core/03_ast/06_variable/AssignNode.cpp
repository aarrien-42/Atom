#include "AssignNode.hpp"

AssignNode::AssignNode( ParserManager& parser ) : ASTNode(NodeType::Assign), value(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] AssignNode created\n", BOLDMAGENTA);

    fillData(parser);
}

bool AssignNode::isValid( ParserManager& parser, int& newPos ) {
    int tmpNewPos = newPos;
    bool isValid = false;

    // Check for the equal
    if (parser.peek(tmpNewPos++).value != "=") {
        return false;
    }

    // Check for <operation(=)><box>
    bool isAssignBox = false;
    if (tmpNewPos == (newPos + 1)) {
        if (BoxNode::isValid(parser, tmpNewPos)) {
            isAssignBox = true;
        }
    }

    // Check for <operation(=)><binOp>
    bool isAssignBinOp = false;
    if (tmpNewPos == (newPos + 1)) {
        if (BinOpNode::isValid(parser, tmpNewPos)) {
            isAssignBinOp = true;
        }
    }

    // Check for <operation(=)><identifier>
    bool isAssignIdentifier = false;
    if (tmpNewPos == (newPos + 1)) {
        if (IdentifierNode::isValid(parser, tmpNewPos)) {
            isAssignIdentifier = true;
        }
    }

    // Check for <operation(=)><literal>
    bool isAssignLiteral = false;
    if (tmpNewPos == (newPos + 1)) {
        if (LiteralNode::isValid(parser, tmpNewPos)) {
            isAssignLiteral = true;
        }
    }

    if (isAssignBox||  isAssignBinOp || isAssignIdentifier || isAssignLiteral) {
        if (parser.peek(tmpNewPos).type == TokenType::enter) {
            isValid = true;
        }
    }

    if (isValid) {
        tmpNewPos = newPos;
    }

    return isValid;
}

void AssignNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    if (parser.peek().type == identifier) {
        variableName = parser.consume().value;
        if (parser.peek().value == "=") {
            parser.consume();
            if (parser.peek().type == TokenType::paren) { // box assignation
                value = new BoxNode(parser);
            } else if (parser.peek(1).type == TokenType::enter) { // simple assignation
                if (parser.peek().type == identifier)
                    value = new IdentifierNode(parser);
                else if (parser.peek().type == literal)
                    value = new LiteralNode(parser);
                else {
                    parserNodeError(INV_ASSIGN_NODE, parser, "Invalid simple assignation");
                }
            } else { // advanced assignation
                if (parser.peek().type == TokenType::identifier && parser.peek(1).type == TokenType::paren) { // function call
                    value = new FuncCallNode(parser);
                } else if (parser.peek(1).type == TokenType::operation) {
                    value = new BinOpNode(parser);
                } else {
                    parserNodeError(INV_ASSIGN_NODE, parser, "Invalid advanced assignation");
                }
            }
        } else {
            parserNodeError(INV_ASSIGN_NODE, parser, "Assignation not done");
        }
    } else {
        parserNodeError(INV_ASSIGN_NODE, parser, "Invalid assignation");
    }

    config.printDebug("[-] AssignNode\n", RED);
}
