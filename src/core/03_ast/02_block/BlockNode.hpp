#pragma once

#include "nodes.hpp"

// Description: Stores a chunk of lines or statements
// Data: Function or Conditional content
struct BlockNode : public ASTNode {
    std::vector<ASTNode*> statements;
    size_t initialTabs;

    std::vector<std::string>& scopeVariables;

    BlockNode( ParserManager&, std::vector<std::string>&, size_t, size_t );
    ~BlockNode() {}

    void fillData( ParserManager& );

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
