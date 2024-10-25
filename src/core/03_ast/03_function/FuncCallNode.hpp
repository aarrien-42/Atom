#pragma once

#include "nodes.hpp"

// Description: Function call node
// Data: Name and parameters (normally LiteralNode)
struct FuncCallNode : public ASTNode {
    std::string functionName;
    std::vector<ASTNode*> parameters;

    FuncCallNode( ParserManager&, size_t );
    ~FuncCallNode() {}

    static bool isValid( ParserManager& parser, int& newPos );
    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting FuncCallNode\n", RED);

        for (ASTNode* param : parameters)
            param->deleteNode();
    }
};