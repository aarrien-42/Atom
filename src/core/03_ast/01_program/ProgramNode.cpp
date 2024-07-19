#include "ProgramNode.hpp"

/*-PROGRAM-*/

ProgramNode::ProgramNode( ParserManager& parser, std::string file, size_t level ) : ASTNode(NodeType::Program, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ProgramNode created\n", BOLDMAGENTA);

    fileName = file;

    while (!parser.peek().value.empty()) {
        if (parser.peek().type == tab || parser.peek().type == enter) {
            parser.consume();
        } else {
            if (parser.peek().type == identifier && getStrEndChar(parser.peek().value) == ':') {
                functions.push_back(new FuncDeclNode(parser, this->level + 1));
            } else {
                std::cerr << "Still not implemented\n";
                std::cout << parser.peek().value << "\n";
                parser.consume();
            }
        }
    }
}
