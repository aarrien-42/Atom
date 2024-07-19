#pragma once

#include "nodes.hpp"

// Description: Function call node
// Data: Name and parameters (normally LiteralNode)
struct FuncCallNode : public ASTNode {
    std::string functionName;
    std::vector<ASTNode*> parameters;

    FuncCallNode( ParserManager&, size_t );
    ~FuncCallNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting FuncCallNode\n", RED);

        for (ASTNode* param : parameters)
            param->deleteNode();
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
    }
};