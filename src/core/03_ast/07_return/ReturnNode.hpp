#pragma once

#include "nodes.hpp"

enum ReturnValidNext {
    RVNnone,
    RVNbox,
    RVNbinOp,
    RVNliteral,
    RVNidentifier
};

// Description: Return node
// Data: Return value (normally a literal)
struct ReturnNode : public ASTNode {
    ASTNode* returnValue;

    std::vector<std::string>& scopedVariables;

    ReturnNode( ParserManager&, std::vector<std::string>&, size_t );
    ~ReturnNode() {}

    static bool isValid( ParserManager& parser, int& newPos, ReturnValidNext* validNext = nullptr );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting ReturnNode\n", RED);

        returnValue->deleteNode();
    }
};
