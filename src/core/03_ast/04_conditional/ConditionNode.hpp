#pragma once

#include "nodes.hpp"

// Description: Condition node
// Data: Comparation (<, >, ==, etc.) and nodes to be compared
struct ConditionNode : public ASTNode {
    std::string comparation;
    ASTNode* leftComp;
    ASTNode* rightComp;

    ConditionNode( ParserManager&, size_t );
    ~ConditionNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ConditionNode\n", RED);

        leftComp->deleteNode();
        rightComp->deleteNode(); 
    }
};
