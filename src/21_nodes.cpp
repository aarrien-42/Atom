#include "nodes.hpp"

/*-PROGRAM-*/

ProgramNode::ProgramNode( ParserManager& parser, std::string file, size_t level ) : ASTNode(NodeType::Program, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ProgramNode created\n", BOLDMAGENTA);

    fileName = file;

    while (!parser.peek().value.empty()) {
        if (parser.peek().type == tab || parser.peek().type == enter) {
            parser.consume();
        } else {
            if (parser.peek().type == identifier && getStrEndChar(parser.peek().value) == ':') {
                functions.push_back(new FuncDeclNode(parser, this->level + 1));
            } else {
                std::cerr << "Still not implemented\n";
                std::cout << parser.peek().value << "\n";
                parser.consume();
            }
        }
    }
}

/*-BLOCK-*/

BlockNode::BlockNode( ParserManager& parser, size_t initialTabs, size_t level ) : ASTNode(NodeType::Block, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BlockNode created\n", BOLDMAGENTA);

    bool newValidLine = true;
    do {
        if (parser.peek().type == TokenType::enter || parser.peek().type == TokenType::tab) {
            if (parser.peek().type == TokenType::enter)
                newValidLine = true;
            parser.consume();
        } else {
            if (!newValidLine) {
                break;
            }
            // block body check
            if (parser.peek().type == TokenType::keyword) {
                if (parser.peek().value == "i.") {
                    statements.push_back(new IfStatementNode(parser, this->level + 1));
                } else if (parser.peek().value == "w.") {
                    statements.push_back(new WhileLoopNode(parser, this->level + 1));
                } else if (parser.peek().value == "f.") {
                    statements.push_back(new ForLoopNode(parser, this->level + 1));
                } else if (parser.peek().value == "v.") {
                    statements.push_back(new VarDeclNode(parser, this->level + 1));
                } else if (parser.peek().value == "r.") {
                    statements.push_back(new ReturnNode(parser, this->level + 1));
                } else {
                    parserNodeError(INV_BLOCK_NODE, parser.consume(), "Invalid keyword");
                }
            } else if (parser.peek().type == TokenType::identifier) {
                statements.push_back(new AssignNode(parser, this->level + 1));
            } else {
                parserNodeError(INV_BLOCK_NODE, parser.consume(), "Not implemented yet");
            }
            newValidLine = false;
        }
        if (parser.peek().type != TokenType::enter && parser.peek().tabCount != initialTabs)
            break;
    } while (!parser.peek().value.empty());
}

BoxNode::BoxNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Box, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BoxNode created\n", BOLDMAGENTA);

    // Check if box parenthesis closes
    const int tokensTillBoxEnd = isParenthesisClosed(parser);
    config.printDebug("Tokens until end of the box: " + std::to_string(tokensTillBoxEnd) + "\n");

    if (tokensTillBoxEnd > 0) {
        // Check if Box Node is valid, should only contain: paren, operation, literal
        bool validBox = true;
        for (int index = 0; index < tokensTillBoxEnd; index++) {
            Token token = parser.peek(index);
            if (token.type != TokenType::paren && token.type != TokenType::operation && token.type != TokenType::literal) {
                parserNodeError(INV_BOX_NODE, parser.peek(), "Invalid token inside parenthesis detected");
                validBox = false;
            }
        }

        if (validBox) {
            config.printDebug("Valid BoxNode\n", YELLOW);

            // Check for a valid operation box
            bool literal = false, operation = false;
            for (int index = 0; index < tokensTillBoxEnd; index++) {
                Token token = parser.peek(index);

                if (token.type == TokenType::literal) {
                    literal = true;
                }
                if (token.type == TokenType::operation) {
                    operation = true;
                }
            }

            parser.consume(); // Consume first box parenthesis
            if (literal && operation) {
                config.printDebug("Operation\n", GREEN);
                node = new BinOpNode(parser, level + 1);
            } else if (literal && !operation) {
                config.printDebug("Literal\n", GREEN);
                node = new LiteralNode(parser, level + 1);
            }
            parser.consume(); // Consume last box parenthesis

        }
    } else {
        parserNodeError(INV_BOX_NODE, parser.consume(), "Parenthesis not closed");
    }
}

/*-FUNCTION-*/

FuncDeclNode::FuncDeclNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::FuncDecl, level), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] FuncDeclNode created\n", BOLDMAGENTA);

    functionName = parser.consume().value;
    if (parser.peek().type != enter) { // Function has parameters
        while (parser.peek().type != TokenType::enter) {
            if (parser.peek().type == TokenType::identifier)
                parameters.push_back(new IdentifierNode(parser, this->level + 1));
            else
                parserNodeError(INV_FUNCDECL_NODE, parser.consume(), "Invalid Function declaration node");
        }
    }

    if (parser.peek().type == TokenType::enter)
        parser.consume();

    body = new BlockNode(parser, parser.peek().tabCount, this->level + 1);
}

FuncCallNode::FuncCallNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::FuncCall, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] FuncCallNode created\n", BOLDMAGENTA);
    (void)parser;
}

/*-CONDITIONAL-*/

// More conditional types need to be implemented
ConditionNode::ConditionNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Condition, level), leftComp(nullptr), rightComp(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ConditionNode created\n", BOLDMAGENTA);
    bool withParen = false;

    if (parser.peek().type == TokenType::paren) {
        if (isParenthesisClosed(parser)) {
            withParen = true;
            parser.consume();
        } else {
            parserNodeError(INV_CONDITION_NODE, parser.consume(), "Parenthesis not closed");
        }
    }

    ASTNode** compNode;
    while (true) {
        leftComp == nullptr ? (compNode = &leftComp) : (compNode = &rightComp) ;
        if (leftComp == nullptr || (leftComp != nullptr && !comparation.empty() && rightComp == nullptr)) {
            if (parser.peek().type == TokenType::identifier) {
                *compNode = new IdentifierNode(parser, this->level + 1);
            } else if (parser.peek().type == TokenType::literal) {
                *compNode = new LiteralNode(parser, this->level + 1);
            } else if (parser.peek().value == "(") {
                *compNode = new BoxNode(parser, this->level + 1);
            }
        } else if (comparation.empty()) {
            if (parser.peek().type == TokenType::comparison) {
                comparation = parser.consume().value;
            } else {
                parserNodeError(INV_CONDITION_NODE, parser.consume(), "No comparation operator used");
            }
        } else {
            break;
        }
    }

    if (withParen) parser.consume();
    if (parser.peek().type == TokenType::enter) {
        parser.consume();
    } else {
        parserNodeError(INV_CONDITION_NODE, parser.consume(), "Condition should end in newline");
    }
}

IfStatementNode::IfStatementNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::IfStatement, level), condition(nullptr), body(nullptr), ifBranch(nullptr), elseBranch(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] IfStatementNode created\n", BOLDMAGENTA);
    size_t initialTabs = parser.peek().tabCount;

    if (parser.peek().value == "i.") {
        parser.consume();
        if (parser.peek().type != TokenType::enter ) {
            condition = new ConditionNode(parser, this->level + 1);
            if (parser.peek().tabCount > initialTabs) {
                body = new BlockNode(parser, parser.peek().tabCount, this->level + 1);
            } else {
                parserNodeError(INV_IF_NODE, parser.consume(), "Bad alignment for if statement body");
            }
        } else {
            parserNodeError(INV_IF_NODE, parser.consume(), "If statement node needs a condition");
        }
    } else {
        parserNodeError(INV_IF_NODE, parser.consume(), "Invalid if statement");
    }
}

WhileLoopNode::WhileLoopNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::WhileLoop, level), condition(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] WhileLoopNode created\n", BOLDMAGENTA);
    (void)parser;
}

ForLoopNode::ForLoopNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::ForLoop, level), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ForLoopNode created\n", BOLDMAGENTA);
    (void)parser;
}

/*-OPERATION-*/

BinOpNode::BinOpNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::BinOp, level), leftOp(nullptr), rightOp(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] BinOpNode created\n", BOLDMAGENTA);

    ASTNode** opNode;
    while (true) {
        leftOp == nullptr ? (opNode = &leftOp) : (opNode = &rightOp);
        bool isLeft = (leftOp == nullptr);
        bool isRight = (leftOp != nullptr && !operation.empty() && rightOp == nullptr);

        // If right operator is substitute, check if there are more operations
        bool multipleOperations = false;
        if (isRight) {
            Token token = parser.peek(isParenthesisClosed(parser) + 1);
            config.printDebug("    Check for multiple operations\n");
            config.printDebug("    Token after valid operand [" + token.value + "]\n");
            if (token.type == TokenType::operation) {
                config.printDebug("New binary operation\n", GREEN);
                *opNode = new BinOpNode(parser, level + 1);
                multipleOperations = true;
            }
        }

        if (!multipleOperations) {
            if (parser.peek().type != TokenType::literal && parser.peek().type != TokenType::paren) {
                if (isLeft || isRight) {
                    parserNodeError(INV_BIN_OP_NODE, parser.peek(), "Invalid operation");
                }
            }

            // Check for literal, operator, parenthesis or operation end
            if (parser.peek().type == TokenType::literal) {
                *opNode = new LiteralNode(parser, level + 1);
            } else if (parser.peek().type == TokenType::operation) {
                operation = parser.consume().value;
                config.printDebug("  Operation: [" + operation + "]\n");
            } else if (parser.peek().type == TokenType::paren) {
                if (parser.peek().value == "(") {
                    *opNode = new BoxNode(parser, level + 1);
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
}

UnaryOpNode::UnaryOpNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::UnaryOp, level), operand(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] UnaryOpNode created\n", BOLDMAGENTA);
    (void)parser;
}

/*-VARAIBLE-*/

VarDeclNode::VarDeclNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::VarDecl, level), initialValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] VarDeclNode created\n", BOLDMAGENTA);

    if (parser.peek().value == "v.")
        parser.consume();
    if (parser.peek().type == TokenType::identifier) {
        if (parser.peek(1).type == TokenType::enter) {
            name = parser.consume().value;
        } else {
            name = parser.peek().value;
            if (parser.peek(1).value == "=") {
                initialValue = new AssignNode(parser, this->level + 1);
            } else {
                parserNodeError(INV_VARDECL_NODE, parser.consume(), "Expected assignation");
            }
        }
    } else {
        parserNodeError(INV_VARDECL_NODE, parser.consume(), "Variable needs an identifier");
    }
}

AssignNode::AssignNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Assign, level), value(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] AssignNode created\n", BOLDMAGENTA);

    if (parser.peek().type == identifier) {
        variableName = parser.consume().value;
        if (parser.peek().value == "=") {
            parser.consume();
            if (parser.peek().type == TokenType::paren) { // box assignation
                value = new BoxNode(parser, this->level + 1);
            } else if (parser.peek(1).type == TokenType::enter) { // simple assignation
                if (parser.peek().type == identifier)
                    value = new IdentifierNode(parser, this->level + 1);
                else if (parser.peek().type == literal)
                    value = new LiteralNode(parser, this->level + 1);
                else {
                    parserNodeError(INV_ASSIGN_NODE, parser.consume(), "Invalid simple assignation");
                }
            } else { // advanced assignation
                if (parser.peek().type == TokenType::identifier && parser.peek(1).type == TokenType::paren) { // function call
                    value = new FuncCallNode(parser, this->level + 1);
                } else if (parser.peek(1).type == TokenType::operation) {
                    value = new BinOpNode(parser, this->level + 1);
                } else {
                    parserNodeError(INV_ASSIGN_NODE, parser.consume(), "Invalid advanced assignation");
                }
            }
        } else {
            parserNodeError(INV_ASSIGN_NODE, parser.consume(), "Assignation not done");
        }
    } else {
        parserNodeError(INV_ASSIGN_NODE, parser.consume(), "Invalid assignation");
    }
}

LiteralNode::LiteralNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Literal, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] LiteralNode created\n", BOLDCYAN);

    if (parser.peek().type == literal) {
        value = parser.consume().value;
        config.printDebug("  Literal: [" + value + "]\n");
    } else {
        parserNodeError(INV_LITERAL_NODE, parser.consume(), "Invalid Literal Node");
    }
}

IdentifierNode::IdentifierNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Identifier, level) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] IdentifierNode created\n", BOLDCYAN);

    if (parser.peek().type == identifier) {
        name = parser.consume().value;
        config.printDebug("  Identifier: [" + name + "]\n");
    } else {
        parserNodeError(INV_IDENTIFIER_NODE, parser.consume(), "Invalid Identifier Node");
    }
}

/*-RETURN-*/

ReturnNode::ReturnNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Return, level), returnValue(nullptr) {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("[*] ReturnNode created\n", BOLDMAGENTA);

    if (parser.peek().value != "r.")
        parserNodeError(INV_RETURN_NODE, parser.consume(), "Invalid Return Node");
    else {
        parser.consume();

        if (parser.peek().type != TokenType::enter && parser.peek(1).type != TokenType::enter) {
            if (parser.peek().type == TokenType::paren)
                returnValue = new BoxNode(parser, this->level + 1);
            else if (parser.peek(1).type == TokenType::operation)
                returnValue = new BinOpNode(parser, this->level + 1);
            else if (parser.peek(1).type == TokenType::comparison)
                returnValue = new ConditionNode(parser, this->level + 1);
        } else {
            if (parser.peek().type == TokenType::identifier)
                returnValue = new IdentifierNode(parser, this->level + 1);
            else if (parser.peek().type == TokenType::literal)
                returnValue = new LiteralNode(parser, this->level + 1);
        }

        // Line must end by now
        if (parser.peek().type != TokenType::enter) {
            parserNodeError(INV_RETURN_NODE, parser.consume(), "Expected a new line");
        }
    }
}

/*-UTILS-*/

int isParenthesisClosed( ParserManager& parser ) {
    int index = 1; // Starts looking at the next value
    size_t parenLevel;
    bool isParenClosed = false;

    if (parser.peek().value == "(") {
        parenLevel = 1;
        while (true) {
            if (parser.peek(index).type == TokenType::paren) {
                if (parser.peek(index).value == "(") {
                    parenLevel++;
                } else if (parser.peek(index).value == ")") {
                    parenLevel--;
                    if (parenLevel == 0) {
                        isParenClosed = true;
                        break;
                    }
                }
            } else if (parser.peek(index).type == TokenType::enter) {
                break;
            }
            index++;
        }
    }

    if (isParenClosed) {
        return index;
    }
    return isParenClosed;
}
