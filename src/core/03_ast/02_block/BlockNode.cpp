#include "BlockNode.hpp"

BlockNode::BlockNode( ParserManager& parser, std::vector<std::string>& scpVars, size_t tabs, size_t level ) : ASTNode(NodeType::Block, level), scopeVariables(scpVars), initialTabs(tabs) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BlockNode created\n", BOLDMAGENTA);

    config.printDebug("[BlockNode] Initial variables:\n", BOLDCYAN);
    printScopedVariables(scopeVariables);

    fillData(parser);

    config.printDebug("[BlockNode] Final variables:\n", BOLDCYAN);
    printScopedVariables(scopeVariables);
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
                    statements.push_back(new IfStatementNode(parser, scopeVariables, this->level + 1));
                } else if (parser.peek().value == "w.") {
                    statements.push_back(new WhileLoopNode(parser, scopeVariables, this->level + 1));
                } else if (parser.peek().value == "f.") {
                    statements.push_back(new ForLoopNode(parser, scopeVariables, this->level + 1));
                } else if (parser.peek().value == "v.") {
                    ASTNode* node = new VarDeclNode(parser, scopeVariables, this->level + 1);
                    statements.push_back(node);
                    VarDeclNode* varDeclNode = dynamic_cast<VarDeclNode*>(node);
                    config.printDebug("New variable " + varDeclNode->name + "\n", GREEN);
                    scopeVariables.push_back(varDeclNode->name);
                } else if (parser.peek().value == "r.") {
                    statements.push_back(new ReturnNode(parser, scopeVariables, this->level + 1));
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
