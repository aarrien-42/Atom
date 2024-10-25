#pragma once

#include "nodes.hpp"

// Description: Return node
// Data: Return value (normally a literal)
struct ReturnNode : public ASTNode {
    ASTNode* returnValue;

    std::vector<std::string>& scopedVariables;

    ReturnNode( ParserManager&, std::vector<std::string>&, size_t );
    ~ReturnNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ReturnNode\n", RED);

        returnValue->deleteNode();
    }
};
