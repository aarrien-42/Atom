#pragma once

#include "nodes.hpp"

// Description: Stores a chunk of lines or statements
// Data: Function or Conditional content
struct BlockNode : public ASTNode {
    std::vector<ASTNode*> statements;
    size_t initialTabs;

    std::vector<std::string>& scopeVariables;

    BlockNode( ParserManager&, std::vector<std::string>&, size_t );
    ~BlockNode() {}

    void fillData( ParserManager& );

    void deleteNode() override {
        ConfigManager::getInstance().printDebug("Deleting BlockNode: tabs(" + std::to_string(initialTabs) + ")\n", RED);

        for (ASTNode* statement : statements) {
            ConfigManager::getInstance().printDebug(" - ", RED);
            statement->deleteNode();
        }

        ConfigManager::getInstance().printDebug("[-] tabs(" + std::to_string(initialTabs) + ")\n", RED);
    }
};
