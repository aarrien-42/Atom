#include "nodes.hpp"

/*-PROGRAM-*/

ProgramNode::ProgramNode( Parser& parser ) : ASTNode(NodeType::Program) {
	std::cout << "  **PROGRAM NODE CREATED**\n";

	fileName = ""; // Still not captured

	while (!parser.peek().value.empty()) {
		if (parser.peek().type == tab || parser.peek().type == enter) {
			parser.consume();
		} else {
			if (parser.peek().type == identifier && getStrEndChar(parser.peek().value) == ':') {
				functions.push_back(new FuncDeclNode(parser));
			} else {
				std::cerr << "Still not implemented\n";
				parser.consume();
			}
		}
	}

	// Print result node
	this->printNode();
}

/*-BLOCK-*/

BlockNode::BlockNode( Parser& parser, size_t initialTabs ) : ASTNode(NodeType::Block) {
	std::cout << "  **BLOCK NODE CREATED**\n";
	bool	newValidLine = true;

	do {
		if (parser.peek().type == TokenType::enter || parser.peek().type == TokenType::tab) {
			if (parser.peek().type == TokenType::enter)
				newValidLine = true;
			parser.consume();
		} else {
			if (!newValidLine) {
				parserNodeError(INV_BLOCK_NODE, parser.consume(), "Expected newline");
			}
			// block body check
			if (parser.peek().type == TokenType::keyword) {
				if (parser.peek().value == "i.") {
					statements.push_back(new IfStatementNode(parser));
				} else if (parser.peek().value == "w.") {
					statements.push_back(new WhileLoopNode(parser));
				} else if (parser.peek().value == "f.") {
					statements.push_back(new ForLoopNode(parser));
				} else if (parser.peek().value == "v.") {
					statements.push_back(new VarDeclNode(parser));
				} else if (parser.peek().value == "r.") {
					statements.push_back(new ReturnNode(parser));
				} else {
					parserNodeError(INV_BLOCK_NODE, parser.consume(), "Invalid keyword");
				}
			} else if (parser.peek().type == TokenType::identifier) {
				statements.push_back(new AssignNode(parser));
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

BoxNode::BoxNode( Parser& parser ) : ASTNode(NodeType::Box) {
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
				node = new BoxNode(parser);
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

FuncDeclNode::FuncDeclNode( Parser& parser ) : ASTNode(NodeType::FuncDecl), body(nullptr) {
	std::cout << "  **FUNC DECL NODE CREATED**\n";

	functionName = parser.consume().value;
	if (parser.peek().type != enter) { // Function has parameters
		while (parser.peek().type != TokenType::enter) {
			if (parser.peek().type == TokenType::identifier)
				parameters.push_back(new IdentifierNode(parser));
			else
				parserNodeError(INV_FUNCDECL_NODE, parser.consume(), "Invalid Function declaration node");
		}
	}

	if (parser.peek().type == TokenType::enter)
		parser.consume();

	body = new BlockNode(parser, parser.peek().tabCount);

	// Print result node
	this->printNode();
}

FuncCallNode::FuncCallNode( Parser& parser ) : ASTNode(NodeType::FuncCall) {
	(void)parser;
}

/*-CONDITIONAL-*/

// More conditional types need to be implemented
ConditionNode::ConditionNode( Parser& parser ) : ASTNode(NodeType::Condition), leftComp(nullptr), rightComp(nullptr) {
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
				*compNode = new IdentifierNode(parser);
			} else if (parser.peek().type == TokenType::literal) {
				*compNode = new LiteralNode(parser);
			} else if (parser.peek().value == "(") {
				*compNode = new LiteralNode(parser);
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

IfStatementNode::IfStatementNode( Parser& parser ) : ASTNode(NodeType::IfStatement), condition(nullptr), body(nullptr), ifBranch(nullptr), elseBranch(nullptr) {
	std::cout << "  **IF NODE CREATED**\n";
	size_t initialTabs = parser.peek().tabCount;

	if (parser.peek().value == "i.") {
		parser.consume();
		if (parser.peek().type != TokenType::enter ) {
			condition = new ConditionNode(parser);
			if (parser.peek().tabCount > initialTabs) {
				body = new BlockNode(parser, parser.peek().tabCount);
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

WhileLoopNode::WhileLoopNode( Parser& parser ) : ASTNode(NodeType::WhileLoop), condition(nullptr), body(nullptr) {
	(void)parser;

	// Print result node
	this->printNode();
}

ForLoopNode::ForLoopNode( Parser& parser ) : ASTNode(NodeType::ForLoop), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
	(void)parser;

	// Print result node
	this->printNode();
}

/*-OPERATION-*/

BinOpNode::BinOpNode( Parser& parser ) : ASTNode(NodeType::BinOp), leftOp(nullptr), rightOp(nullptr) {
	(void)parser;

	// Print result node
	this->printNode();
}

UnaryOpNode::UnaryOpNode( Parser& parser ) : ASTNode(NodeType::UnaryOp), operand(nullptr) {
	(void)parser;

	// Print result node
	this->printNode();
}

/*-VARAIBLE-*/

VarDeclNode::VarDeclNode( Parser& parser ) : ASTNode(NodeType::VarDecl), initialValue(nullptr) {
	std::cout << "  **VAR DECL NODE CREATED**\n";

	if (parser.peek().value == "v.")
		parser.consume();
	if (parser.peek().type == identifier) {
		name = parser.consume().value;
		if (parser.peek().value == "=") {
			parser.consume();
			if (parser.peek().type == enter) {
				parserNodeError(INV_VARDECL_NODE, parser.consume(), "Invalid variable assignation");
			}
			if (parser.peek().type == paren) {
				initialValue = new BoxNode(parser);
			} else if (parser.peek().type == literal) {
				initialValue = new LiteralNode(parser);
			} else if (parser.peek().type == identifier) {
				initialValue = new IdentifierNode(parser);
			}
		}
	} else {
		parserNodeError(INV_VARDECL_NODE, parser.consume(), "Variable needs an identifier");
	}
	std::cout << "	Variable " << name << " declared\n";

	// Print result node
	this->printNode();
}

AssignNode::AssignNode( Parser& parser ) : ASTNode(NodeType::Assign), value(nullptr) {
	std::cout << "  **ASSIGN NODE CREATED**\n";

	if (parser.peek().type == identifier) {
		variableName = parser.consume().value;
		if (parser.peek().value == "=") {
			parser.consume();
			if (parser.peek().type == TokenType::paren) { // box assignation
				value = new BoxNode(parser);
			} else if (parser.peek(1).type == TokenType::enter) { // simple assignation
				if (parser.peek().type == identifier)
					value = new IdentifierNode(parser);
				else if (parser.peek().type == literal)
					value = new LiteralNode(parser);
				else {
					parserNodeError(INV_ASSIGN_NODE, parser.consume(), "Invalid simple assignation");
				}
			} else { // advanced assignation
				if (parser.peek().type == TokenType::identifier && parser.peek(1).type == TokenType::paren) { // function call
					value = new FuncCallNode(parser);
				} else if (parser.peek(1).type == TokenType::operation) {
					value = new BinOpNode(parser);
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

LiteralNode::LiteralNode( Parser& parser ) : ASTNode(NodeType::Literal) {
	std::cout << "  **LITERAL NODE CREATED**\n";

	if (parser.peek().type != literal)
		parserNodeError(INV_LITERAL_NODE, parser.consume(), "Invalid Literal Node");
	else
		value = parser.consume().value;

	// Print result node
	this->printNode();
}

IdentifierNode::IdentifierNode( Parser& parser ) : ASTNode(NodeType::Identifier) {
	std::cout << "  **IDENTIFIER NODE CREATED**\n";

	if (parser.peek().type != identifier)
		parserNodeError(INV_IDENTIFIER_NODE, parser.consume(), "Invalid Identifier Node");
	else
		name = parser.consume().value;

	// Print result node
	this->printNode();
}

/*-RETURN-*/

ReturnNode::ReturnNode( Parser& parser ) : ASTNode(NodeType::Return), returnValue(nullptr) {
	std::cout << "  **RETURN NODE CREATED**\n";

	if (parser.peek().value != "r.")
		parserNodeError(INV_RETURN_NODE, parser.consume(), "Invalid Return Node");
	else {
		parser.consume();
		if (parser.peek().type == paren)
			returnValue = new BoxNode(parser);
		else if (parser.peek().type == identifier)
			returnValue = new IdentifierNode(parser);
		else if (parser.peek().type == literal)
			returnValue = new LiteralNode(parser);
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
