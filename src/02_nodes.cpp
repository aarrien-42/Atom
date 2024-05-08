#include "nodes.hpp"

/*-PROGRAM-*/

ProgramNode::ProgramNode( Parser& parser, size_t level ) : ASTNode(NodeType::Program, level) {
	std::cout << "  **PROGRAM NODE CREATED**\n";

	fileName = ""; // Still not captured

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

	// Print result node
	this->printNode();
}

/*-BLOCK-*/

BlockNode::BlockNode( Parser& parser, size_t initialTabs, size_t level ) : ASTNode(NodeType::Block, level) {
	std::cout << "  **BLOCK NODE CREATED**\n";
	bool	newValidLine = true;

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

	// Print result node
	this->printNode();
}

BoxNode::BoxNode( Parser& parser, size_t level ) : ASTNode(NodeType::Box, level) {
	std::cout << "  **BOX NODE CREATED**\n";
	int nestedParen = 0, index = 0;
	bool validBox = false;

	if (parser.peek().value == "(") {
		while (!validBox && (parser.peek(index).type != enter || !parser.peek(index).value.empty())) {
			index++;
			if (parser.peek().value == "(") {
				nestedParen++;
			} else if (parser.peek(index).value == ")") {
				if (nestedParen == 0)
					validBox = true;
				else
					nestedParen--;
			}
		}
		if (validBox) {
			parser.consume();
			if (parser.peek().value == "(") {
				node = new BoxNode(parser, this->level + 1);
			} else if (parser.peek().value == ")") {
				parserNodeError(INV_BOX_NODE, parser.consume(), "Nothing between parenthesis");
			} else {
				//if (parser.peek(1).type != NodeType::enter)
				// WORK IN PROGRESS
			}
		} else {
			parserNodeError(INV_BOX_NODE, parser.consume(), "Parenthesis not closed");
		}
	} else
		parserNodeError(INV_BOX_NODE, parser.consume(), "Invalid Box node");

	// Print result node
	this->printNode();
}

/*-FUNCTION-*/

FuncDeclNode::FuncDeclNode( Parser& parser, size_t level ) : ASTNode(NodeType::FuncDecl, level), body(nullptr) {
	std::cout << "  **FUNC DECL NODE CREATED**\n";

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

	// Print result node
	this->printNode();
}

FuncCallNode::FuncCallNode( Parser& parser, size_t level ) : ASTNode(NodeType::FuncCall, level) {
	(void)parser;
}

/*-CONDITIONAL-*/

// More conditional types need to be implemented
ConditionNode::ConditionNode( Parser& parser, size_t level ) : ASTNode(NodeType::Condition, level), leftComp(nullptr), rightComp(nullptr) {
	std::cout << "  **CONDITIONAL NODE CREATED**\n";
	bool withParen = false;

	if (parser.peek().type == TokenType::paren) {
		if (IsParenthesisClosed(parser)) {
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

	// Print result node
	this->printNode();
}

IfStatementNode::IfStatementNode( Parser& parser, size_t level ) : ASTNode(NodeType::IfStatement, level), condition(nullptr), body(nullptr), ifBranch(nullptr), elseBranch(nullptr) {
	std::cout << "  **IF NODE CREATED**\n";
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

	// Print result node
	this->printNode();
}

WhileLoopNode::WhileLoopNode( Parser& parser, size_t level ) : ASTNode(NodeType::WhileLoop, level), condition(nullptr), body(nullptr) {
	std::cout << "  **WHILE LOOP NODE CREATED**\n";
	(void)parser;

	// Print result node
	this->printNode();
}

ForLoopNode::ForLoopNode( Parser& parser, size_t level ) : ASTNode(NodeType::ForLoop, level), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
	std::cout << "  **FOR LOOP NODE CREATED**\n";
	(void)parser;

	// Print result node
	this->printNode();
}

/*-OPERATION-*/

BinOpNode::BinOpNode( Parser& parser, size_t level ) : ASTNode(NodeType::BinOp, level), leftOp(nullptr), rightOp(nullptr) {
	std::cout << "  **BIN OP NODE CREATED**\n";
	
	if (parser.peek(1).type == TokenType::operation) {
		ASTNode** opNode;
		while (true) {
			leftOp == nullptr ? (opNode = &leftOp) : (opNode = &rightOp) ;
			if (leftOp == nullptr || (leftOp != nullptr && !operation.empty() && rightOp == nullptr)) {
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
	} else {
		parserNodeError(INV_BIN_OP_NODE, parser.consume(), "Expected operation");
	}

	// Print result node
	this->printNode();
}

UnaryOpNode::UnaryOpNode( Parser& parser, size_t level ) : ASTNode(NodeType::UnaryOp, level), operand(nullptr) {
	std::cout << "  **UNARY OP NODE CREATED**\n";
	(void)parser;

	// Print result node
	this->printNode();
}

/*-VARAIBLE-*/

VarDeclNode::VarDeclNode( Parser& parser, size_t level ) : ASTNode(NodeType::VarDecl, level), initialValue(nullptr) {
	std::cout << "  **VAR DECL NODE CREATED**\n";

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

	// Print result node
	this->printNode();
}

AssignNode::AssignNode( Parser& parser, size_t level ) : ASTNode(NodeType::Assign, level), value(nullptr) {
	std::cout << "  **ASSIGN NODE CREATED**\n";

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

	// Print result node
	this->printNode();
}

LiteralNode::LiteralNode( Parser& parser, size_t level ) : ASTNode(NodeType::Literal, level) {
	std::cout << "  **LITERAL NODE CREATED**\n";

	if (parser.peek().type != literal)
		parserNodeError(INV_LITERAL_NODE, parser.consume(), "Invalid Literal Node");
	else
		value = parser.consume().value;

	// Print result node
	this->printNode();
}

IdentifierNode::IdentifierNode( Parser& parser, size_t level ) : ASTNode(NodeType::Identifier, level) {
	std::cout << "  **IDENTIFIER NODE CREATED**\n";

	if (parser.peek().type != identifier)
		parserNodeError(INV_IDENTIFIER_NODE, parser.consume(), "Invalid Identifier Node");
	else
		name = parser.consume().value;

	// Print result node
	this->printNode();
}

/*-RETURN-*/

ReturnNode::ReturnNode( Parser& parser, size_t level ) : ASTNode(NodeType::Return, level), returnValue(nullptr) {
	std::cout << "  **RETURN NODE CREATED**\n";

	if (parser.peek().value != "r.")
		parserNodeError(INV_RETURN_NODE, parser.consume(), "Invalid Return Node");
	else {
		parser.consume();
		if (parser.peek().type == paren)
			returnValue = new BoxNode(parser, this->level + 1);
		else if (parser.peek().type == identifier)
			returnValue = new IdentifierNode(parser, this->level + 1);
		else if (parser.peek().type == literal)
			returnValue = new LiteralNode(parser, this->level + 1);
	}

	// Print result node
	this->printNode();
}

/*-UTILS-*/

bool IsParenthesisClosed( Parser& parser ) {
	int index = 1; // Starts looking at the next value
	size_t parenLevel;
	bool returnValue = false;

	if (parser.peek().value == "(") {
		parenLevel = 1;
		while (true) {
			if (parser.peek(index).type == TokenType::paren) {
				if (parser.peek(index).value == "(") {
					parenLevel++;
				} else if (parser.peek(index).value == ")") {
					parenLevel--;
					if (parenLevel == 0) {
						returnValue = true;
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

	return returnValue;
}
