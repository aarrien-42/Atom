#pragma once

#include "nodes.hpp"

enum BoxValidNext {
    BVNnone,
    BVNbinOp,
    BVNcondition,
    BVNbox,
};

// Description: Stores smaller chunks of data
// Data: Node between parenthsis (normally used in operations)
struct BoxNode : public ASTNode {
    ASTNode* node;

    BoxNode( ParserManager&, size_t );
    ~BoxNode() {}

    static bool isValid( ParserManager&, int& newPos, BoxValidNext* nextValid = nullptr );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting BoxNode\n", RED);

        node->deleteNode();
    }
};
