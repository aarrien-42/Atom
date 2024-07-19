#include "IfStatementNode.hpp"

IfStatementNode::IfStatementNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::IfStatement, level), condition(nullptr), body(nullptr), ifBranch(nullptr), elseBranch(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] IfStatementNode created\n", BOLDMAGENTA);
    size_t initialTabs = parser.peek().tabCount;

    if (parser.peek().value == "i.") {
        parser.consume();
        if (parser.peek().type != TokenType::enter ) {
            condition = new ConditionNode(parser, this->level + 1);
            if (parser.peek().tabCount > initialTabs) {
                body = new BlockNode(parser, parser.peek().tabCount, this->level + 1);
            } else {
                parserNodeError(INV_IF_NODE, parser.consume(), "Bad alignment for if statement body");
            }
        } else {
            parserNodeError(INV_IF_NODE, parser.consume(), "If statement node needs a condition");
        }
    } else {
        parserNodeError(INV_IF_NODE, parser.consume(), "Invalid if statement");
    }
}