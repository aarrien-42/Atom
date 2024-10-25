#include "ASTPrinter.hpp"

void putSpaces(size_t count) {
    ConfigManager& config = ConfigManager::getInstance();
    size_t spaceSize = 2;

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < spaceSize; j++) {
            config.printDebug(" ");
        }
    }
}

void printNodeType(ASTNode* node, size_t& level) {
    std::string textColor = getColor(level);
    std::string nodeName;

    level++;
    switch (node->getType()) {
        case NodeType::Program:     nodeName = "ProgramNode";     break;
        case NodeType::Block:       nodeName = "BlockNode";       break;
        case NodeType::Box:         nodeName = "BoxNode";         break;
        case NodeType::FuncDecl:    nodeName = "FuncDeclNode";    break;
        case NodeType::FuncCall:    nodeName = "FuncCallNode";    break;
        case NodeType::Condition:   nodeName = "ConditionNode";   break;
        case NodeType::IfStatement: nodeName = "IfStatementNode"; break;
        case NodeType::WhileLoop:   nodeName = "WhileLoopNode";   break;
        case NodeType::ForLoop:     nodeName = "ForLoopNode";     break;
        case NodeType::BinOp:       nodeName = "BinOpNode";       break;
        case NodeType::UnaryOp:     nodeName = "UnaryOpNode";     break;
        case NodeType::VarDecl:     nodeName = "VarDeclNode";     break;
        case NodeType::Assign:      nodeName = "AssignNode";      break;
        case NodeType::Literal:     nodeName = "LiteralNode";     break;
        case NodeType::Identifier:  nodeName = "IdentifierNode";  break;
        case NodeType::Return:      nodeName = "ReturnNode";      break;
        default: nodeName = "Unknown";
    }

    putSpaces(level);
    ConfigManager::getInstance().printDebug("[" + nodeName + "]:\n", textColor);
}

void ASTPrinter::printNode(ASTNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    printNodeType(node, level);
    switch (node->getType()) {
        case NodeType::Program:
            printProgramNode(dynamic_cast<ProgramNode*>(node), level);
            break;
        case NodeType::Block:
            printBlockNode(dynamic_cast<BlockNode*>(node), level);
            break;
        case NodeType::Box:
            printBoxNode(dynamic_cast<BoxNode*>(node), level);
            break;
        case NodeType::FuncDecl:
            printFuncDeclNode(dynamic_cast<FuncDeclNode*>(node), level);
            break;
        case NodeType::FuncCall:
            printFuncCallNode(dynamic_cast<FuncCallNode*>(node), level);
            break;
        case NodeType::Condition:
            printConditionNode(dynamic_cast<ConditionNode*>(node), level);
            break;
        case NodeType::IfStatement:
            printIfStatementNode(dynamic_cast<IfStatementNode*>(node), level);
            break;
        case NodeType::WhileLoop:
            printWhileLoopNode(dynamic_cast<WhileLoopNode*>(node), level);
            break;
        case NodeType::ForLoop:
            printForLoopNode(dynamic_cast<ForLoopNode*>(node), level);
            break;
        case NodeType::BinOp:
            printBinOpNode(dynamic_cast<BinOpNode*>(node), level);
            break;
        case NodeType::UnaryOp:
            printUnaryOpNode(dynamic_cast<UnaryOpNode*>(node), level);
            break;
        case NodeType::VarDecl:
            printVarDeclNode(dynamic_cast<VarDeclNode*>(node), level);
            break;
        case NodeType::Assign:
            printAssignNode(dynamic_cast<AssignNode*>(node), level);
            break;
        case NodeType::Literal:
            printLiteralNode(dynamic_cast<LiteralNode*>(node), level);
            break;
        case NodeType::Identifier:
            printIdentifierNode(dynamic_cast<IdentifierNode*>(node), level);
            break;
        case NodeType::Return:
            printReturnNode(dynamic_cast<ReturnNode*>(node), level);
            break;
        default:
            config.printDebug("Invalid node to print\n", YELLOW);
            break;
    }
}


void ASTPrinter::printProgramNode(ProgramNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("File name = " + node->fileName + "\n");
    for (ASTNode* function : node->functions) {
        printNode(function, level);
    }
}

void ASTPrinter::printBlockNode(BlockNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    for (ASTNode* statement : node->statements) {
        printNode(statement, level);
    }
}

void ASTPrinter::printBoxNode(BoxNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    printNode(node->node, level);
}

void ASTPrinter::printFuncDeclNode(FuncDeclNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("Function name = " + node->functionName + "\n");
    if (!node->parameters.empty()) {
        putSpaces(level + 1);
        config.printDebug("Parameters:\n");
        for (ASTNode* param : node->parameters) {
            printNode(param, level);
            config.printDebug(" ");
        }
    }
    putSpaces(level + 1);
    config.printDebug("Body:\n");
    printNode(node->body, level);
}

void ASTPrinter::printFuncCallNode(FuncCallNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("Function name = " + node->functionName + "\n");
    if (!node->parameters.empty()) {
        putSpaces(level + 1);
        config.printDebug("Parameters:\n");
        for (ASTNode* param : node->parameters) {
            printNode(param, level);
            config.printDebug(" ");
        }
    }
}

void ASTPrinter::printConditionNode(ConditionNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("Comparator: " + node->comparation + "\n");
    putSpaces(level + 1);
    config.printDebug("Left node:\n");
    printNode(node->leftComp, level);
    putSpaces(level + 1);
    config.printDebug("Right node:\n");
    printNode(node->rightComp, level);
}

void ASTPrinter::printIfStatementNode(IfStatementNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("Condition:\n");
    printNode(node->condition, level);
    putSpaces(level + 1);
    config.printDebug("Body:\n");
    printNode(node->body, level);
    if (node->elseBranch != nullptr) {
        putSpaces(level + 1);
        config.printDebug("Else branch:\n");
        printNode(node->elseBranch, level);
    }
}

void ASTPrinter::printWhileLoopNode(WhileLoopNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

}

void ASTPrinter::printForLoopNode(ForLoopNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();
}

void ASTPrinter::printBinOpNode(BinOpNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("Operator: " + node->operation + "\n");
    putSpaces(level + 1);
    config.printDebug("Left Operand:\n");
    printNode(node->leftOp, level);
    putSpaces(level + 1);
    config.printDebug("Right Operand:\n");
    printNode(node->rightOp, level);
}

void ASTPrinter::printUnaryOpNode(UnaryOpNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    printNode(node->operand, level);
    config.printDebug(node->operation);
}

void ASTPrinter::printVarDeclNode(VarDeclNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("Variable name: " + node->name + "\n");
    if (node->initialValue != nullptr) {
        putSpaces(level + 1);
        config.printDebug("Initial value:\n");
        printNode(node->initialValue, level);
    }
}

void ASTPrinter::printAssignNode(AssignNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug("Variable name: " + node->variableName + "\n");
    printNode(node->value, level);
}

void ASTPrinter::printLiteralNode(LiteralNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug(node->value + "\n");
}

void ASTPrinter::printIdentifierNode(IdentifierNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    putSpaces(level + 1);
    config.printDebug(node->name + "\n");
}

void ASTPrinter::printReturnNode(ReturnNode* node, size_t level) {
    ConfigManager& config = ConfigManager::getInstance();

    printNode(node->returnValue, level);
}
