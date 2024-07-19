#pragma once

#include "nodes.hpp"

// Description: Return node
// Data: Return value (normally a literal)
struct ReturnNode : public ASTNode {
    ASTNode* returnValue;

    ReturnNode( ParserManager&, size_t );
    ~ReturnNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ReturnNode\n", RED);

        returnValue->deleteNode();
    }

    void	printNode() const override {
        ASTNode::printNode();

        returnValue->printNode();
    }
};
