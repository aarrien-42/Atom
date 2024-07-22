#pragma once

#include "nodes.hpp"

// Description: Function declaration node
// Data: Name, parameters and body (normally a BlockNode)
struct FuncDeclNode : public ASTNode {
    std::string functionName;
    std::vector<ASTNode*> parameters;
    ASTNode* body;

    std::vector<std::string> funcVariables;

    FuncDeclNode( ParserManager&, size_t );
    ~FuncDeclNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting FuncDeclNode\n", RED);

        for (ASTNode* param : parameters)
            param->deleteNode();
        body->deleteNode();
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        ASTNode::putSpaces();
        Config.printDebug("Function name = " + functionName + "\n");
        if (!parameters.empty()) {
            ASTNode::putSpaces();
            Config.printDebug("Parameters:\n");
            for (ASTNode* param : parameters) {
                param->printNode();
                Config.printDebug(" ");
            }
        }
        ASTNode::putSpaces();
        Config.printDebug("Body:\n");
        body->printNode();
    }
};