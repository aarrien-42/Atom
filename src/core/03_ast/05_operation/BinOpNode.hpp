#pragma once

#include "nodes.hpp"

enum BinOpValidNext {
    BOVNnone,
    BOVNboxOpBox,
    BOVNlitOpBox,
    BOVNboxOpLit,
    BOVNlitOpLit
};

// Description: Binary (pair) operation node
// Data: Operation (+, -, *, /, %, etc.) and two operands
struct BinOpNode : public ASTNode {
    std::string operation;
    ASTNode* leftOp;
    ASTNode* rightOp;

    BinOpNode( ParserManager& );
    BinOpNode( const BinOpNode& other );
    ~BinOpNode() {}

    static bool isValid( ParserManager& parser, int& newPos, BinOpValidNext* nextValid = nullptr );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting BinOpNode\n", RED);

        leftOp->deleteNode();
        rightOp->deleteNode();
    }
};
