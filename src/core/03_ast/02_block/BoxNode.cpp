#include "BoxNode.hpp"

BoxNode::BoxNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Box, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BoxNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void BoxNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    // Check if box parenthesis closes
    const int tokensTillBoxEnd = isParenthesisClosed(parser);
    config.printDebug("Tokens until end of the box: " + std::to_string(tokensTillBoxEnd) + "\n");

    if (tokensTillBoxEnd > 0) {
        parser.consume(); // Consume first BoxNode parenthesis
        ASTNode* tempNode = nullptr;
        while (true) {
            config.printDebug("Current token [" + parser.peek().value + " (" + std::to_string(parser.peek().type) + ")" + "]\n");

            size_t opIndex = 0;
            if (parser.peek().type == TokenType::paren && parser.peek().value == ")") {
                break;
            } else if (parser.peek().type == TokenType::paren && parser.peek().value == "(") {
                opIndex = isParenthesisClosed(parser) + 1;
            } else {
                opIndex = 1;
            }

            config.printDebug("opNode value = " + parser.peek(opIndex).value + " (" + std::to_string(opIndex) + ")" + "\n");
            if (parser.peek(opIndex).type == TokenType::operation) {
                tempNode = new BinOpNode(parser, level + 1);
            } else if (parser.peek(opIndex).type == TokenType::comparison) {
                tempNode = new ConditionNode(parser, level + 1);
                break;
            }
        }
        parser.consume(); // Consume last BoxNode parenthesis
        node = tempNode;
    } else {
        parserNodeError(INV_BOX_NODE, parser, "Parenthesis not closed");
    }
    config.printDebug("[-] BoxNode\n", RED);
}
