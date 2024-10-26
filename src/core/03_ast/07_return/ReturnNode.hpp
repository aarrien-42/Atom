#pragma once

#include "nodes.hpp"

// Description: Return node
// Data: Return value (normally a literal)
struct ReturnNode : public ASTNode {
    ASTNode* returnValue;

    std::vector<std::string>& scopedVariables;

    ReturnNode( ParserManager&, std::vector<std::string>& );
    ~ReturnNode() {}

    static bool isValid( ParserManager& parser, int& newPos );
    NodeType getNode( ParserManager& parser, int newPos = 0 );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ReturnNode\n", RED);

        returnValue->deleteNode();
    }
};
