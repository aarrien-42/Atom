#include "ProgramNode.hpp"

ProgramNode::ProgramNode( ParserManager& parser, std::string file) : ASTNode(NodeType::Program), fileName(file) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ProgramNode created\n", BOLDMAGENTA);

    fillData(parser);
}

void ProgramNode::fillData( ParserManager& parser ) {
    ConfigManager& config = ConfigManager::getInstance();

    while (!parser.peek().value.empty()) {
        if (parser.peek().type == tab || parser.peek().type == enter) {
            parser.consume();
        } else {
            if (parser.peek().type == identifier && getStrEndChar(parser.peek().value) == ':') {
                functions.push_back(new FuncDeclNode(parser));
            } else {
                config.printDebug("(" + parser.peek().value + ") Still not implemented\n", MAGENTA);
                parser.consume();
            }
        }
    }

    config.printDebug("[-] ProgramNode\n", RED);
}
