#pragma once

#include "nodes.hpp"

// Description: Literal node
// Data: Value, could be a string or a number (either way it saves as a string)
struct LiteralNode : public ASTNode {
    std::string value;

    LiteralNode( ParserManager&, size_t );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting LiteralNode\n", RED);


    }

    void printNode() const override {
        ASTNode::printNode();

        putSpaces();
        ConfigManager::getInstance().printDebug(value + "\n");
    }
};
