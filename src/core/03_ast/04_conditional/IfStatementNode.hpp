#pragma once

#include "nodes.hpp"

// Description: If statement node
// Data: Condition (ConditionNode), body (BlockNode) and optional if and else branches
struct IfStatementNode : public ASTNode {
    ASTNode* condition;
    ASTNode* body;
    ASTNode* elseBranch; // just in case there's an else

    std::vector<std::string>& scopedVariables;

    IfStatementNode( ParserManager&, std::vector<std::string>&, size_t );
    ~IfStatementNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting IfStatementNode\n", RED);

        condition->deleteNode();
        body->deleteNode();
        if (elseBranch != nullptr) {
            elseBranch->deleteNode();
        }
    }
};