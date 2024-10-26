#include "IfStatementNode.hpp"

IfStatementNode::IfStatementNode( ParserManager& parser, std::vector<std::string>& scopedVariables ) : ASTNode(NodeType::IfStatement), scopedVariables(scopedVariables), condition(nullptr), body(nullptr), elseBranch(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] IfStatementNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void IfStatementNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();
    size_t initialTabs = parser.peek().tabCount;

    if (parser.peek().value != "i.") {
        parserNodeError(INV_IF_NODE, parser, "Invalid if statement");
    } else {
        parser.consume();
        if (parser.peek().type != TokenType::enter ) {
            // Check for conditional
            if (parser.peek().value == "(") {
                condition = new BoxNode(parser);
            } else {
                condition = new ConditionNode(parser);
            }

            if (parser.peek().type == TokenType::enter) {
                parser.consume();
            }

            // Check for IfStatement body
            config.printDebug("Initial tab count: " + std::to_string(initialTabs) + ", New body tab count: " + std::to_string(parser.peek().tabCount) + "\n", YELLOW);
            if (parser.peek().tabCount > initialTabs) {
                body = new BlockNode(parser, scopedVariables, parser.peek().tabCount);
            } else {
                parserNodeError(INV_IF_NODE, parser, "Bad alignment for if statement body");
            }
        } else {
            parserNodeError(INV_IF_NODE, parser, "If statement node needs a condition");
        }
    }

    config.printDebug("[-] IfStatementNode\n", RED);
}
