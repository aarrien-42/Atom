#pragma once

#include "nodes.hpp"

// Description: Function declaration node
// Data: Name, parameters and body (normally a BlockNode)
struct FuncDeclNode : public ASTNode {
    std::string functionName;
    std::vector<ASTNode*> parameters;
    ASTNode* body;

    std::vector<std::string> funcVariables;

    FuncDeclNode( ParserManager& );
    ~FuncDeclNode() {}

    static bool isValid( ParserManager& parser, int& newPos );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting FuncDeclNode\n", RED);

        ConfigManager::getInstance().printDebug(" Deleting parameters:\n", RED);
        for (ASTNode* param : parameters) {
            param->deleteNode();
        }

        ConfigManager::getInstance().printDebug(" Deleting body:\n", RED);
        body->deleteNode();
    }
};