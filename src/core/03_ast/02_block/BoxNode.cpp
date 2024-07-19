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
        // Check if Box Node is valid, should only contain: paren, operation, literal
        bool validBox = true;
        for (int index = 0; index < tokensTillBoxEnd; index++) {
            Token token = parser.peek(index);
            if (token.type != TokenType::paren && token.type != TokenType::operation && token.type != TokenType::literal) {
                parserNodeError(INV_BOX_NODE, parser.peek(), "Invalid token inside parenthesis detected");
                validBox = false;
            }
        }

        if (validBox) {
            config.printDebug("Valid BoxNode\n", YELLOW);

            // Check for a valid operation box
            bool literal = false, operation = false;
            for (int index = 0; index < tokensTillBoxEnd; index++) {
                Token token = parser.peek(index);

                if (token.type == TokenType::literal) {
                    literal = true;
                }
                if (token.type == TokenType::operation) {
                    operation = true;
                }
            }

            parser.consume(); // Consume first box parenthesis

            // Check if another BoxNode needs to be created inside this BoxNode
            bool boxInsideBox = false;
            if (parser.peek().type == TokenType::paren) {
                config.printDebug("Another posible BoxNode\n", GREEN);

                int tillParenClose =  isParenthesisClosed(parser);
                if (parser.peek().value == "(" && parser.peek(tillParenClose + 1).type != TokenType::operation) {
                    boxInsideBox = true;
                }
            }

            if (boxInsideBox) {
                config.printDebug("Another Box\n", GREEN);
                node = new BoxNode(parser, level + 1);
            } else {
                // Check for BinOpNode or LiteralNode
                if (literal && operation) {
                    config.printDebug("Operation\n", GREEN);
                    node = new BinOpNode(parser, level + 1);
                } else if (literal && !operation) {
                    config.printDebug("Literal\n", GREEN);
                    node = new LiteralNode(parser, level + 1);
                }
            }

            parser.consume(); // Consume last box parenthesis
        }
    } else {
        parserNodeError(INV_BOX_NODE, parser.consume(), "Parenthesis not closed");
    }
}
