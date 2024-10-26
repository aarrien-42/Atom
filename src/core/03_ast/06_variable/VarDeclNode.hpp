#pragma once

#include "nodes.hpp"

// Description: Variable declaration node
// Data: Name and initial value (normally a number or string literal)
struct VarDeclNode : public ASTNode {
    std::string name;
    ASTNode* initialValue;

    std::vector<std::string>& scopedVariables;

    VarDeclNode( ParserManager&, std::vector<std::string>& );
    ~VarDeclNode() {}

    static bool isValid( ParserManager& parser, int& newPos );
    NodeType getNode( ParserManager& parser, int newPos = 0 );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting VarDeclNode\n", RED);

        if (initialValue != nullptr)
            initialValue->deleteNode();
    }
};
