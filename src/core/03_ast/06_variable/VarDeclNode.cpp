#include "VarDeclNode.hpp"

VarDeclNode::VarDeclNode( ParserManager& parser, std::vector<std::string>& scopedVariables, size_t level ) : ASTNode(NodeType::VarDecl, level), scopedVariables(scopedVariables), initialValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] VarDeclNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void VarDeclNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

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
                parserNodeError(INV_VARDECL_NODE, parser, "Expected assignation");
            }
        }
    } else {
        parserNodeError(INV_VARDECL_NODE, parser, "Variable needs an identifier");
    }

    config.printDebug("[-] VarDeclNode\n", RED);
}
