#pragma once

#include "nodes.hpp"

// Description: Identifier node
// Data: Name of the variable to identify
struct IdentifierNode : public ASTNode {
    std::string name;

    IdentifierNode( ParserManager&, size_t );

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting IdentifierNode\n", RED);
    }
};
