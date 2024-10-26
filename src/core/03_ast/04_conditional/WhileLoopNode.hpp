#pragma once

#include "nodes.hpp"

// Description: While loop node
// Data: Condition (ConditionNode) and body (BlockNode)
struct WhileLoopNode : public ASTNode {
    ASTNode* condition;
    ASTNode* body;

    std::vector<std::string>& scopedVariables;

    WhileLoopNode( ParserManager&, std::vector<std::string>& );
    ~WhileLoopNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting WhileLoopNode\n", RED);

        condition->deleteNode();
        body->deleteNode();
    }
};
