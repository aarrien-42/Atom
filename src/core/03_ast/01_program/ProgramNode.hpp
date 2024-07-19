#pragma once

#include "nodes.hpp"

// Description: Stores information about a single .atm file
// Data: Program file name and all functions declared in the file
struct ProgramNode : public ASTNode {
    std::string fileName;
    std::vector<ASTNode*> functions;

    ProgramNode( ParserManager&, std::string, size_t = 0 );
    ~ProgramNode() {}

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ProgramNode\n", RED);

        for (ASTNode* function : functions)
            function->deleteNode();
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager::getInstance().printDebug("File name = " + fileName + "\n");
        for (ASTNode* function : functions) {
            function->printNode();
        }
    }
};
