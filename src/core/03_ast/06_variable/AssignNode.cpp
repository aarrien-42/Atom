#include "AssignNode.hpp"

AssignNode::AssignNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Assign, level), value(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] AssignNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void AssignNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    if (parser.peek().type == identifier) {
        variableName = parser.consume().value;
        if (parser.peek().value == "=") {
            parser.consume();
            if (parser.peek().type == TokenType::paren) { // box assignation
                value = new BoxNode(parser, this->level + 1);
            } else if (parser.peek(1).type == TokenType::enter) { // simple assignation
                if (parser.peek().type == identifier)
                    value = new IdentifierNode(parser, this->level + 1);
                else if (parser.peek().type == literal)
                    value = new LiteralNode(parser, this->level + 1);
                else {
                    parserNodeError(INV_ASSIGN_NODE, parser, "Invalid simple assignation");
                }
            } else { // advanced assignation
                if (parser.peek().type == TokenType::identifier && parser.peek(1).type == TokenType::paren) { // function call
                    value = new FuncCallNode(parser, this->level + 1);
                } else if (parser.peek(1).type == TokenType::operation) {
                    value = new BinOpNode(parser, this->level + 1);
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
}
