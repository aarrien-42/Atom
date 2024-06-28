#include "nodes.hpp"

/*-PROGRAM-*/

ProgramNode::ProgramNode( ParserManager& parser, std::string file, size_t level ) : ASTNode(NodeType::Program, level) {
    ConfigManager::getInstance().printDebug("ProgramNode created\n", CYAN);

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
    ConfigManager::getInstance().printDebug("BlockNode created\n", CYAN);
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
    ConfigManager::getInstance().printDebug("BoxNode created\n", CYAN);
    int nestedParen = 0, index = 0;
    bool validBox = false;

    if (parser.peek().value == "(") {
        // Check if the parenthesis closes, validBox will be set to true
        while (!validBox && (parser.peek(index).type != enter && !parser.peek(index).value.empty())) {
            if (parser.peek(index).value == "(") {
                nestedParen++;
            } else if (parser.peek(index).value == ")") {
                nestedParen--;
                if (nestedParen == 0)
                    validBox = true;
            }
            index++;
        }
        if (validBox) {
            parser.consume();
            if (parser.peek().value == "(") {
                // Another BoxNode at the start
                int closeIndex = isParenthesisClosed(parser);
                if (closeIndex != 0) {
                    if (parser.peek(closeIndex + 1).type == TokenType::operation) {
                        node = new BinOpNode(parser, level + 1);
                    } else if (parser.peek(closeIndex + 1).type == TokenType::comparison) {
                        node = new ConditionNode(parser, level + 1);
                    } else {
                        parserNodeError(INV_BOX_NODE, parser.consume(), "Not implemented yet");
                    }
                } else {
                    parserNodeError(INV_BOX_NODE, parser.consume(), "Parenthesis not closed");
                }
            } else if (parser.peek().value == ")") {
                parserNodeError(INV_BOX_NODE, parser.consume(), "Nothing between parenthesis");
            } else {
                // Another BoxNode at the end
                if (parser.peek(1).value != ")") {
                    if (parser.peek(2).value != ")") {
                        if (parser.peek(1).type == TokenType::operation) {
                            node = new BinOpNode(parser, level + 1);
                        } else if (parser.peek(1).type == TokenType::comparison) {
                            node = new ConditionNode(parser, level + 1);
                        } else {
                            parserNodeError(INV_BOX_NODE, parser.consume(), "Not implemented yet");
                        }
                    } else {
                        parserNodeError(INV_BOX_NODE, parser.consume(), "Expected second operand");
                    }
                } else {
                    // Just a literal or identifier between parenthesis
                    if (parser.peek().type == TokenType::literal || parser.peek().type == TokenType::identifier) {
                        if (parser.peek().type == TokenType::literal) {
                            node = new LiteralNode(parser, level + 1);
                        } else {
                            node = new IdentifierNode(parser, level + 1);
                        }
                    } else {
                        parserNodeError(INV_BOX_NODE, parser.consume(), "Invalid operation between parenthesis");
                    }
                }
            }
            // Consume last paren from box
            if (parser.peek().value == ")") {
                parser.consume();
            } else {
                parserNodeError(INV_BOX_NODE, parser.consume(), "Expecting close parenthesis");
            }
        } else {
            parserNodeError(INV_BOX_NODE, parser.consume(), "Parenthesis not closed");
        }
    } else
        parserNodeError(INV_BOX_NODE, parser.consume(), "Invalid Box node");
}

/*-FUNCTION-*/

FuncDeclNode::FuncDeclNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::FuncDecl, level), body(nullptr) {
    ConfigManager::getInstance().printDebug("FuncDeclNode created\n", CYAN);

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
    (void)parser;
}

/*-CONDITIONAL-*/

// More conditional types need to be implemented
ConditionNode::ConditionNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Condition, level), leftComp(nullptr), rightComp(nullptr) {
    ConfigManager::getInstance().printDebug("ConditionNode created\n", CYAN);
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
    ConfigManager::getInstance().printDebug("IfStatementNode created\n", CYAN);
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
    ConfigManager::getInstance().printDebug("WhileLoopNode created\n", CYAN);
    (void)parser;
}

ForLoopNode::ForLoopNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::ForLoop, level), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
    ConfigManager::getInstance().printDebug("ForLoopNode created\n", CYAN);
    (void)parser;
}

/*-OPERATION-*/

BinOpNode::BinOpNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::BinOp, level), leftOp(nullptr), rightOp(nullptr) {
    ConfigManager::getInstance().printDebug("BinOpNode created\n", CYAN);

    ASTNode** opNode;
    while (true) {
        leftOp == nullptr ? (opNode = &leftOp) : (opNode = &rightOp) ;
        if (leftOp == nullptr || (leftOp != nullptr && !operation.empty() && rightOp == nullptr)) {
            // Multiple continous operations
            if (leftOp != nullptr && !operation.empty() && rightOp == nullptr) {
                if (parser.peek(1).type == TokenType::operation) {
                    rightOp = new BinOpNode(parser, level + 1);
                }
            }
            // Simple binary operation
            if (parser.peek().type == TokenType::identifier) {
                *opNode = new IdentifierNode(parser, this->level + 1);
            } else if (parser.peek().type == TokenType::literal) {
                *opNode = new LiteralNode(parser, this->level + 1);
            } else if (parser.peek().value == "(") {
                *opNode = new BoxNode(parser, this->level + 1);
            }
        } else if (operation.empty()) {
            if (parser.peek().type == TokenType::operation) {
                operation = parser.consume().value;
            } else {
                parserNodeError(INV_BIN_OP_NODE, parser.consume(), "No operation operator used");
            }
        } else {
            break;
        }
    }
}

UnaryOpNode::UnaryOpNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::UnaryOp, level), operand(nullptr) {
    ConfigManager::getInstance().printDebug("UnaryOpNode created\n", CYAN);
    (void)parser;
}

/*-VARAIBLE-*/

VarDeclNode::VarDeclNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::VarDecl, level), initialValue(nullptr) {
    ConfigManager::getInstance().printDebug("VarDeclNode created\n", CYAN);

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
    ConfigManager::getInstance().printDebug("AssignNode created\n", CYAN);

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
    ConfigManager::getInstance().printDebug("LiteralNode created\n", CYAN);

    if (parser.peek().type != literal)
        parserNodeError(INV_LITERAL_NODE, parser.consume(), "Invalid Literal Node");
    else
        value = parser.consume().value;
}

IdentifierNode::IdentifierNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Identifier, level) {
    ConfigManager::getInstance().printDebug("IdentifierNode created\n", CYAN);

    if (parser.peek().type != identifier)
        parserNodeError(INV_IDENTIFIER_NODE, parser.consume(), "Invalid Identifier Node");
    else
        name = parser.consume().value;
}

/*-RETURN-*/

ReturnNode::ReturnNode( ParserManager& parser, size_t level ) : ASTNode(NodeType::Return, level), returnValue(nullptr) {
    ConfigManager::getInstance().printDebug("ReturnNode created\n", CYAN);

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
    } else {
        std::cerr << "This is not a parenthesis block start\n";
    }

    if (isParenClosed) {
        return index;
    }
    return isParenClosed;
}
