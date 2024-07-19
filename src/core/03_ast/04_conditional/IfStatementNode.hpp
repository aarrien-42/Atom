#pragma once

#include "nodes.hpp"

// Description: If statement node
// Data: Condition (ConditionNode), body (BlockNode) and optional if and else branches
struct IfStatementNode : public ASTNode {
    ASTNode* condition;
    ASTNode* body;
    ASTNode* ifBranch; // not above condition so else if
    ASTNode* elseBranch; // just in case there's an else

    IfStatementNode( ParserManager&, size_t );
    ~IfStatementNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting IfStatementNode\n", RED);

        condition->deleteNode();
        body->deleteNode();
        ifBranch->deleteNode();
        elseBranch->deleteNode();
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        putSpaces();
        Config.printDebug("Condition:\n");
        condition->printNode();
        putSpaces();
        Config.printDebug("Body:\n");
        body->printNode();
        if (ifBranch != nullptr) {
            putSpaces();
            Config.printDebug("If branch:\n");
            ifBranch->printNode();
        }
        if (elseBranch != nullptr) {
            putSpaces();
            Config.printDebug("Else branch:\n");
            elseBranch->printNode();
        }
    }
};