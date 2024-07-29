#include "ConditionNode.hpp"

// More conditional types need to be implemented
ConditionNode::ConditionNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Condition, level), leftComp(nullptr), rightComp(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ConditionNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void ConditionNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    ASTNode** opNode;

    while (true) {
        leftComp == nullptr ? (opNode = &leftComp) : (opNode = &rightComp);

        // Check for subsequent operations
        if (leftComp != nullptr && rightComp != nullptr) {
            config.printDebug("    Check for multiple comparations\n");
            if (parser.peek().type == TokenType::comparison) {
                config.printDebug("New comparation: ", GREEN);

            } else {
                break;
            }
        }

        if (leftComp != nullptr && comparation.empty()) {
            if (parser.peek().type == TokenType::comparison) {
                comparation = parser.consume().value;
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

    config.printDebug("[-] ConditionNode\n", RED);
}
