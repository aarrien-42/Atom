#pragma once

#include "nodes.hpp"

// Description: For loop node
// Data: Initialization (VarDeclNode or AssignNode), condition (ConditionNode), iteration (BinOpNode) and body (BlockNode)
struct ForLoopNode : public ASTNode {
    ASTNode* initialization;
    ASTNode* condition;
    ASTNode* iteration;
    ASTNode* body;

    std::vector<std::string>& scopedVariables;

    ForLoopNode( ParserManager&, std::vector<std::string>&, size_t );
    ~ForLoopNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ForLoopNode\n", RED);

        initialization->deleteNode();
        condition->deleteNode();
        iteration->deleteNode();
        body->deleteNode();
    }
};
