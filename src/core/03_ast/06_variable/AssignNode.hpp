#pragma once

#include "nodes.hpp"

// Description: Variable assignation node
// Data: Variable name and new value
struct AssignNode : public ASTNode {
    std::string variableName;
    ASTNode* value;

    AssignNode( ParserManager& );
    ~AssignNode() {}

    static bool isValid( ParserManager&, int& newPos );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting AssignNode\n", RED);

        value->deleteNode(); 
    }
};
