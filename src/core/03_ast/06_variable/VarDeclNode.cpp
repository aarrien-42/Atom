#include "VarDeclNode.hpp"

VarDeclNode::VarDeclNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::VarDecl, level), initialValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] VarDeclNode created\n", BOLDMAGENTA);

    if (parser.peek().value == "v.")
        parser.consume();
    if (parser.peek().type == TokenType::identifier) {
        if (parser.peek(1).type == TokenType::enter) {
            name = parser.consume().value;
        } else {
            name = parser.peek().value;
            if (parser.peek(1).value == "=") {
                initialValue = new AssignNode(parser, this->level + 1);
            } else {
                parserNodeError(INV_VARDECL_NODE, parser.consume(), "Expected assignation");
            }
        }
    } else {
        parserNodeError(INV_VARDECL_NODE, parser.consume(), "Variable needs an identifier");
    }
}
