#include "BlockNode.hpp"

BlockNode::BlockNode( ParserManager& parser, size_t tabs, size_t level ) : ASTNode(NodeType::Block, level), initialTabs(tabs) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BlockNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void BlockNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    bool newValidLine = true;
    do {
        if (parser.peek().type == TokenType::enter || parser.peek().type == TokenType::tab) {
            if (parser.peek().type == TokenType::enter)
                newValidLine = true;
            parser.consume();
        } else {
            if (!newValidLine) {
                break;
            }
            // block body check
            if (parser.peek().type == TokenType::keyword) {
                if (parser.peek().value == "i.") {
                    statements.push_back(new IfStatementNode(parser, this->level + 1));
                } else if (parser.peek().value == "w.") {
                    statements.push_back(new WhileLoopNode(parser, this->level + 1));
                } else if (parser.peek().value == "f.") {
                    statements.push_back(new ForLoopNode(parser, this->level + 1));
                } else if (parser.peek().value == "v.") {
                    statements.push_back(new VarDeclNode(parser, this->level + 1));
                } else if (parser.peek().value == "r.") {
                    statements.push_back(new ReturnNode(parser, this->level + 1));
                } else {
                    parserNodeError(INV_BLOCK_NODE, parser.consume(), "Invalid keyword");
                }
            } else if (parser.peek().type == TokenType::identifier) {
                statements.push_back(new AssignNode(parser, this->level + 1));
            } else {
                parserNodeError(INV_BLOCK_NODE, parser.consume(), "Not implemented yet");
            }
            newValidLine = false;
        }
        if (parser.peek().type != TokenType::enter && parser.peek().tabCount != initialTabs)
            break;
    } while (!parser.peek().value.empty());
}
