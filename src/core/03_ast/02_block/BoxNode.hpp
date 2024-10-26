#pragma once

#include "nodes.hpp"

// Description: Stores smaller chunks of data
// Data: Node between parenthsis (normally used in operations)
struct BoxNode : public ASTNode {
    ASTNode* node;

    BoxNode( ParserManager& );
    ~BoxNode() {}

    static bool isValid( ParserManager&, int& newPos );
    NodeType getNode( ParserManager&, int newPos = 0 );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting BoxNode\n", RED);

        node->deleteNode();
    }
};
