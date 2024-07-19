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

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        ASTNode::putSpaces();
        Config.printDebug("Operator: " + operation + "\n");
        ASTNode::putSpaces();
        Config.printDebug("Left Operand:\n");
        leftOp->printNode();
        ASTNode::putSpaces();
        Config.printDebug("Right Operand:\n");
        rightOp->printNode();
    }
};
