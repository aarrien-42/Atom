#pragma once

#include "nodes.hpp"

// Description: Variable assignation node
// Data: Variable name and new value
struct AssignNode : public ASTNode {
    std::string variableName;
    ASTNode* value;

    AssignNode( ParserManager&, size_t );
    ~AssignNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting AssignNode\n", RED);

        value->deleteNode(); 
    }

    void printNode() const override {
        ASTNode::printNode();

        putSpaces();
        ConfigManager::getInstance().printDebug("Variable name: " + variableName + "\n");
        value->printNode();
    }
};
