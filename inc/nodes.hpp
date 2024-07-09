#ifndef NODES_HPP
#define NODES_HPP

#include <iostream>
#include <vector>
#include "parser.hpp"
#include "lexer.hpp"
#include "colors.hpp"
#include "config.hpp"

enum NodeType {
    Program,
    Block,
    Box,
    FuncDecl,       // <func>:
    FuncCall,       // <func>(<p1>, <p2>)
    Condition,      // (<left><comparator><right>)
    IfStatement,    // i. (<condition>)
    WhileLoop,      // w. (<condition>)
    ForLoop,        // f. (<assign>, <condition>, <operation>)
    BinOp,          // <left><operator><right>
    UnaryOp,        // <left><operator>
    VarDecl,        // v. <var>
    Assign,         // <var> = <?>
    Literal,        // "42" or 42
    Identifier,     // <var>
    Return,         // r. <value>
};

class ParserManager;

/*-MAIN-*/

struct ASTNode {
        private:
            NodeType type;
        protected:
            size_t level;
        public:
        ASTNode(NodeType t, size_t l = 0) : type(t), level(l) {}
        virtual ~ASTNode() {}

        NodeType getType() { return type; }

        virtual void putSpaces(bool isNode = false) const {
            ConfigManager& Config = ConfigManager::getInstance();
            size_t spaceSize = 2;

            for (size_t i = 0; i < level + !isNode; i++) {
                for (size_t j = 0; j < spaceSize; j++) {
                    Config.printDebug(" ");
                }
            }
        }

        virtual void printNode() const {
            putSpaces(true);
            std::string textColor = getColor(level);
            std::string nodeName;
            switch (type) {
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
            ConfigManager::getInstance().printDebug("[" + nodeName + "]:\n", textColor);
        }
};

/*-PROGRAM-*/

// Description: Stores information about a single .atm file
// Data: Program file name and all functions declared in the file
struct ProgramNode : public ASTNode {
    std::string fileName;
    std::vector<ASTNode*> functions;

    ProgramNode( ParserManager&, std::string, size_t = 0 );
    ~ProgramNode() {
        for (ASTNode* function : functions)
            delete function;
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager::getInstance().printDebug("File name = " + fileName + "\n");
        for (ASTNode* function : functions) {
            function->printNode();
        }
    }
};

/*-BLOCK-*/

// Description: Stores a chunk of lines or statements
// Data: Function or Conditional content
struct BlockNode : public ASTNode {
    std::vector<ASTNode*> statements;

    BlockNode( ParserManager&, size_t, size_t );
    ~BlockNode() {
        for (ASTNode* statement : statements)
            delete statement;
    }

    void printNode() const override {
        ASTNode::printNode();

        for (ASTNode* statement : statements) {
            statement->printNode();
        }
    }
};

// Description: Stores smaller chunks of data
// Data: Node between parenthsis (normally used in operations)
struct BoxNode : public ASTNode {
    ASTNode* node;

    BoxNode( ParserManager&, size_t );
    ~BoxNode() { delete node; }

    void printNode() const override {
        ASTNode::printNode();

        node->printNode();
    }
};

/*-FUNCTION-*/

// Description: Function declaration node
// Data: Name, parameters and body (normally a BlockNode)
struct FuncDeclNode : public ASTNode {
    std::string functionName;
    std::vector<ASTNode*> parameters;
    ASTNode* body;

    FuncDeclNode( ParserManager&, size_t );
    ~FuncDeclNode() {
        for (ASTNode* param : parameters)
            delete param;
        delete body;
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        ASTNode::putSpaces();
        Config.printDebug("Function name = " + functionName + "\n");
        if (!parameters.empty()) {
            ASTNode::putSpaces();
            Config.printDebug("Parameters:\n");
            for (ASTNode* param : parameters) {
                param->printNode();
                Config.printDebug(" ");
            }
        }
        ASTNode::putSpaces();
        Config.printDebug("Body:\n");
        body->printNode();
    }
};

// Description: Function call node
// Data: Name and parameters (normally LiteralNode)
struct FuncCallNode : public ASTNode {
    std::string functionName;
    std::vector<ASTNode*> parameters;

    FuncCallNode( ParserManager&, size_t );
    ~FuncCallNode() {
        for (ASTNode* param : parameters)
            delete param;
    }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        ASTNode::putSpaces();
        Config.printDebug("Function name = " + functionName + "\n");
        if (!parameters.empty()) {
            ASTNode::putSpaces();
            Config.printDebug("Parameters:\n");
            for (ASTNode* param : parameters) {
                param->printNode();
                Config.printDebug(" ");
            }
        }
    }
};

/*-CONDITIONAL-*/

// Description: Condition node
// Data: Comparation (<, >, ==, etc.) and nodes to be compared
struct ConditionNode : public ASTNode {
    std::string comparation;
    ASTNode* leftComp;
    ASTNode* rightComp;

    ConditionNode( ParserManager&, size_t );
    ~ConditionNode() { delete leftComp; delete rightComp; }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        putSpaces();
        Config.printDebug("Comparator: " + comparation + "\n");
        putSpaces();
        Config.printDebug("Left node: " + comparation + "\n");
        leftComp->printNode();
        putSpaces();
        Config.printDebug("Right node: " + comparation + "\n");
        rightComp->printNode();
    }
};

// Description: If statement node
// Data: Condition (ConditionNode), body (BlockNode) and optional if and else branches
struct IfStatementNode : public ASTNode {
    ASTNode* condition;
    ASTNode* body;
    ASTNode* ifBranch; // not above condition so else if
    ASTNode* elseBranch; // just in case there's an else

    IfStatementNode( ParserManager&, size_t );
    ~IfStatementNode() { delete condition; delete body; delete ifBranch; delete elseBranch; }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        putSpaces();
        Config.printDebug("Condition:\n");
        condition->printNode();
        putSpaces();
        Config.printDebug("Body:\n");
        body->printNode();
        if (ifBranch != nullptr) {
            putSpaces();
            Config.printDebug("If branch:\n");
            ifBranch->printNode();
        }
        if (elseBranch != nullptr) {
            putSpaces();
            Config.printDebug("Else branch:\n");
            elseBranch->printNode();
        }
    }
};

// Description: While loop node
// Data: Condition (ConditionNode) and body (BlockNode)
struct WhileLoopNode : public ASTNode {
    ASTNode* condition;
    ASTNode* body;

    WhileLoopNode( ParserManager&, size_t );
    ~WhileLoopNode() { delete condition; delete body; }

    void printNode() const override {
        ASTNode::printNode();
    }
};

// Description: For loop node
// Data: Initialization (VarDeclNode or AssignNode), condition (ConditionNode), iteration (BinOpNode) and body (BlockNode)
struct ForLoopNode : public ASTNode {
    ASTNode* initialization;
    ASTNode* condition;
    ASTNode* iteration;
    ASTNode* body;

    ForLoopNode( ParserManager&, size_t );
    ~ForLoopNode() { delete initialization; delete condition; delete iteration; delete body; }

    void printNode() const override {
        ASTNode::printNode();
    }
};

/*-OPERATION-*/

// Description: Binary (pair) operation node
// Data: Operation (+, -, *, /, %, etc.) and two operands
struct BinOpNode : public ASTNode {
    std::string operation;
    ASTNode* leftOp;
    ASTNode* rightOp;

    BinOpNode( ParserManager&, size_t );
    BinOpNode( const BinOpNode& other, size_t level );
    ~BinOpNode() { /*delete leftOp; delete rightOp;*/ }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        ASTNode::putSpaces();
        Config.printDebug("Operator: " + operation + "\n");
        ASTNode::putSpaces();
        Config.printDebug("Left Operand:\n");
        leftOp->printNode();
        ASTNode::putSpaces();
        Config.printDebug("Right Operand:\n");
        rightOp->printNode();
    }
};

// Description: Unary operation node
// Data: Operation (++, --, etc.) and an operand
struct UnaryOpNode : public ASTNode {
    std::string operation;
    ASTNode* operand;

    UnaryOpNode( ParserManager&, size_t );
    ~UnaryOpNode() { delete operand; }

    void printNode() const override {
        ASTNode::printNode();

        operand->printNode();
        ConfigManager::getInstance().printDebug(operation);
    }
};

/*-VARAIBLE-*/

// Description: Variable declaration node
// Data: Name and initial value (normally a number or string literal)
struct VarDeclNode : public ASTNode {
    std::string name;
    ASTNode* initialValue;

    VarDeclNode( ParserManager&, size_t );
    ~VarDeclNode() { delete initialValue; }

    void printNode() const override {
        ASTNode::printNode();

        ConfigManager& Config = ConfigManager::getInstance();

        putSpaces();
        Config.printDebug("Variable name: " + name + "\n");
        if (initialValue != nullptr) {
            putSpaces();
            Config.printDebug("Initial value:\n");
            initialValue->printNode();
        }
    }
};

// Description: Variable assignation node
// Data: Variable name and new value
struct AssignNode : public ASTNode {
    std::string variableName;
    ASTNode* value;

    AssignNode( ParserManager&, size_t );
    ~AssignNode() { delete value; }

    void printNode() const override {
        ASTNode::printNode();

        putSpaces();
        ConfigManager::getInstance().printDebug("Variable name: " + variableName + "\n");
        value->printNode();
    }
};

// Description: Literal node
// Data: Value, could be a string or a number (either way it saves as a string)
struct LiteralNode : public ASTNode {
    std::string value;

    LiteralNode( ParserManager&, size_t );

    void printNode() const override {
        ASTNode::printNode();

        putSpaces();
        ConfigManager::getInstance().printDebug(value + "\n");
    }
};

// Description: Identifier node
// Data: Name of the variable to identify
struct IdentifierNode : public ASTNode {
    std::string name;

    IdentifierNode( ParserManager&, size_t );

    void printNode() const override {
        ASTNode::printNode();

        putSpaces();
        ConfigManager::getInstance().printDebug(name + "\n");
    }
};

/*-RETURN-*/

// Description: Return node
// Data: Return value (normally a literal)
struct ReturnNode : public ASTNode {
    ASTNode* returnValue;

    ReturnNode( ParserManager&, size_t );
    ~ReturnNode() { delete returnValue; }

    void	printNode() const override {
        ASTNode::printNode();

        returnValue->printNode();
    }
};

/*-UTILS-*/

int isParenthesisClosed( ParserManager& );

#endif