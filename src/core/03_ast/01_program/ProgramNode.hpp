#pragma once

#include "nodes.hpp"

// Description: Stores information about a single .atm file
// Data: Program file name and all functions declared in the file
struct ProgramNode : public ASTNode {
    std::string fileName;
    std::vector<ASTNode*> functions;

    ProgramNode( ParserManager&, std::string );
    ~ProgramNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ProgramNode\n", RED);

        for (ASTNode* function : functions)
            function->deleteNode();
    }
};
