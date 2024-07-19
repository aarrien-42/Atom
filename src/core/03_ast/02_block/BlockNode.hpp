#pragma once

#include "nodes.hpp"

// Description: Stores a chunk of lines or statements
// Data: Function or Conditional content
struct BlockNode : public ASTNode {
    std::vector<ASTNode*> statements;

    BlockNode( ParserManager&, size_t, size_t );
    ~BlockNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting BlockNode\n", RED);

        for (ASTNode* statement : statements)
            statement->deleteNode();
    }

    void printNode() const override {
        ASTNode::printNode();

        for (ASTNode* statement : statements) {
            statement->printNode();
        }
    }
};
