#pragma once

#include "nodes.hpp"

// Description: Binary (pair) operation node
// Data: Operation (+, -, *, /, %, etc.) and two operands
struct BinOpNode : public ASTNode {
    std::string operation;
    ASTNode* leftOp;
    ASTNode* rightOp;

    BinOpNode( ParserManager&, size_t );
    BinOpNode( const BinOpNode& other, size_t level );
    ~BinOpNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting BinOpNode\n", RED);

        leftOp->deleteNode();
        rightOp->deleteNode();
    }
};
