#pragma once

#include "nodes.hpp"

// Description: Unary operation node
// Data: Operation (++, --, etc.) and an operand
struct UnaryOpNode : public ASTNode {
    std::string operation;
    ASTNode* operand;

    UnaryOpNode( ParserManager& );
    ~UnaryOpNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting UnaryOpNode\n", RED);

        operand->deleteNode();
    }
};
