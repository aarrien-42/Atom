#include "BlockNode.hpp"

BlockNode::BlockNode( ParserManager& parser, std::vector<std::string>& scpVars, size_t tabs ) : ASTNode(NodeType::Block), scopeVariables(scpVars), initialTabs(tabs) {
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

    while (true) {
        // Consume enter or tab tokens
        while (parser.peek().type == TokenType::enter || parser.peek().type == TokenType::tab) {
            parser.consume();
        }

        if (parser.peek().type != TokenType::enter && parser.peek().tabCount < initialTabs) {
            config.printDebug("[BlockNode] TabCount (" + std::to_string(parser.peek().tabCount) + ") exceeds initialTabs (" + std::to_string(initialTabs) + ")\n", YELLOW);
            break;
        }
        if (parser.peek().value.empty()) {
            break;
        }

        config.printDebug("Current Token: [" + parser.peek().value + "]\n", CYAN);

        // block body check
        if (parser.peek().type == TokenType::keyword) {
            if (parser.peek().value == "i.") {
                statements.push_back(new IfStatementNode(parser, scopeVariables));
            } else if (parser.peek().value == "w.") {
                statements.push_back(new WhileLoopNode(parser, scopeVariables));
            } else if (parser.peek().value == "f.") {
                statements.push_back(new ForLoopNode(parser, scopeVariables));
            } else if (parser.peek().value == "v.") {
                ASTNode* node = new VarDeclNode(parser, scopeVariables);
                statements.push_back(node);
                VarDeclNode* varDeclNode = dynamic_cast<VarDeclNode*>(node);
                config.printDebug("New variable " + varDeclNode->name + "\n", GREEN);
                scopeVariables.push_back(varDeclNode->name);
            } else if (parser.peek().value == "r.") {
                statements.push_back(new ReturnNode(parser, scopeVariables));
            } else {
                parserNodeError(INV_BLOCK_NODE, parser, "Invalid keyword");
            }
        } else if (parser.peek().type == TokenType::identifier) {
            statements.push_back(new AssignNode(parser));
        } else {
            parserNodeError(INV_BLOCK_NODE, parser, "Not implemented yet");
        }
    }

    config.printDebug("[-] BlockNode\n", RED);
}
