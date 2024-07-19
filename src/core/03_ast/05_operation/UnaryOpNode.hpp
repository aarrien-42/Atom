#pragma once

#include "nodes.hpp"

// Description: Unary operation node
// Data: Operation (++, --, etc.) and an operand
struct UnaryOpNode : public ASTNode {
    std::string operation;
    ASTNode* operand;

    UnaryOpNode( ParserManager&, size_t );
    ~UnaryOpNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting UnaryOpNode\n", RED);

        operand->deleteNode();
    }

    void printNode() const override {
        ASTNode::printNode();

        operand->printNode();
        ConfigManager::getInstance().printDebug(operation);
    }
};
