#include "ReturnNode.hpp"

ReturnNode::ReturnNode( ParserManager& parser, std::vector<std::string>& scopedVariables, size_t level ) : ASTNode(NodeType::Return, level), scopedVariables(scopedVariables), returnValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ReturnNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void ReturnNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    if (parser.peek().value != "r.")
        parserNodeError(INV_RETURN_NODE, parser, "Invalid Return Node");
    else {
        parser.consume();

        if (parser.peek().type != TokenType::enter && parser.peek(1).type != TokenType::enter) {
            if (parser.peek().type == TokenType::paren)
                returnValue = new BoxNode(parser, this->level + 1);
            else if (parser.peek(1).type == TokenType::operation)
                returnValue = new BinOpNode(parser, this->level + 1);
            else if (parser.peek(1).type == TokenType::comparison)
                returnValue = new ConditionNode(parser, this->level + 1);
        } else {
            if (parser.peek().type == TokenType::identifier)
                returnValue = new IdentifierNode(parser, this->level + 1);
            else if (parser.peek().type == TokenType::literal)
                returnValue = new LiteralNode(parser, this->level + 1);
        }

        // Line must end by now
        if (parser.peek().type != TokenType::enter) {
            parserNodeError(INV_RETURN_NODE, parser, "Expected a new line");
        }
    }

    config.printDebug("[-] ReturnNode\n", RED);
}
