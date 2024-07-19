#pragma once

#include "nodes.hpp"

// Description: Variable declaration node
// Data: Name and initial value (normally a number or string literal)
struct VarDeclNode : public ASTNode {
    std::string name;
    ASTNode* initialValue;

    VarDeclNode( ParserManager&, size_t );
    ~VarDeclNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting VarDeclNode\n", RED);

        initialValue->deleteNode();
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        putSpaces();
        Config.printDebug("Variable name: " + name + "\n");
        if (initialValue != nullptr) {
            putSpaces();
            Config.printDebug("Initial value:\n");
            initialValue->printNode();
        }
    }
};
