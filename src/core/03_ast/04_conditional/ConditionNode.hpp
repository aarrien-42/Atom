#pragma once

#include "nodes.hpp"

// Description: Condition node
// Data: Comparation (<, >, ==, etc.) and nodes to be compared
struct ConditionNode : public ASTNode {
    std::string comparation;
    ASTNode* leftComp;
    ASTNode* rightComp;

    ConditionNode( ParserManager&, size_t );
    ~ConditionNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ConditionNode\n", RED);

        leftComp->deleteNode();
        rightComp->deleteNode(); 
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        putSpaces();
        Config.printDebug("Comparator: " + comparation + "\n");
        putSpaces();
        Config.printDebug("Left node: " + comparation + "\n");
        leftComp->printNode();
        putSpaces();
        Config.printDebug("Right node: " + comparation + "\n");
        rightComp->printNode();
    }
};