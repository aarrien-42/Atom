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
			std::cout << "Inside block = " << parser.peek().value << " type = " << parser.peek().type << std::endl;
			if (!newValidLine) {
				parserNodeError(INV_BLOCK_NODE, parser.consume(), "Invalid new line");
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
		if (parser.peek().type != TokenType::enter && parser.peek().tabCount != initialTabs + 1)
			break;
	} while (!parser.peek().value.empty());
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
}

/*-FUNCTION-*/

FuncDeclNode::FuncDeclNode( Parser& parser ) : ASTNode(NodeType::FuncDecl), body(nullptr) {
	std::cout << "  **FUNC DECL NODE CREATED**\n";

	size_t functionTabs = parser.peek().tabCount;
	functionName = parser.consume().value;
	std::cout << "	name = " << functionName << std::endl;
	if (parser.peek().type != enter) { // Function has parameters
		while (parser.peek().type != TokenType::enter) {
			std::cout << "new parameter: " << parser.peek().value << "\n";
			if (parser.peek().type == TokenType::identifier)
				parameters.push_back(new IdentifierNode(parser));
			else
				parserNodeError(INV_FUNCDECL_NODE, parser.consume(), "Invalid Function declaration node");
		}
	}

	if (parser.peek().type == TokenType::enter)
		parser.consume();

	body = new BlockNode(parser, functionTabs);
}

FuncCallNode::FuncCallNode( Parser& parser ) : ASTNode(NodeType::FuncCall) {
	(void)parser;
}

/*-CONDITIONAL-*/

// More conditional types need to be implemented
ConditionNode::ConditionNode( Parser& parser ) : ASTNode(NodeType::Condition), leftComp(nullptr), rightComp(nullptr) {
	std::cout << "  **CONDITIONAL NODE CREATED**\n";

	if (parser.peek().value == "(") {
		parser.consume();
		
		
	} else
		parserNodeError(INV_CONDITION_NODE, parser.consume(), "Invalid Conditional node");
}

IfStatementNode::IfStatementNode( Parser& parser ) : ASTNode(NodeType::IfStatement), condition(nullptr), body(nullptr), ifBranch(nullptr), elseBranch(nullptr) {
	std::cout << "  **IF NODE CREATED**\n";

	if (parser.peek().value == "i.")
		parser.consume();
	if (parser.peek().type == enter )
		parserNodeError(INV_IF_NODE, parser.consume(), "If statement node needs a condition");
	else {
		condition = new ConditionNode(parser);
	}
}

WhileLoopNode::WhileLoopNode( Parser& parser ) : ASTNode(NodeType::WhileLoop), condition(nullptr), body(nullptr) {
	(void)parser;
}

ForLoopNode::ForLoopNode( Parser& parser ) : ASTNode(NodeType::ForLoop), initialization(nullptr), condition(nullptr), iteration(nullptr), body(nullptr) {
	(void)parser;
}

/*-OPERATION-*/

BinOpNode::BinOpNode( Parser& parser ) : ASTNode(NodeType::BinOp), leftOp(nullptr), rightOp(nullptr) {
	(void)parser;
}

UnaryOpNode::UnaryOpNode( Parser& parser ) : ASTNode(NodeType::UnaryOp), operand(nullptr) {
	(void)parser;
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
}

AssignNode::AssignNode( Parser& parser ) : ASTNode(NodeType::Assign), value(nullptr) {
	std::cout << "  **ASSIGN NODE CREATED**\n";

	if (parser.peek().type == identifier) {
		variableName = parser.consume().value;
		if (parser.peek().value == "=") {
			parser.consume();
			if (parser.peek().type == paren) {
				value = new BoxNode(parser);
			} else {
				if (parser.peek().type == identifier)
					value = new IdentifierNode(parser);
				else if (parser.peek().type == literal)
					value = new LiteralNode(parser);
			}
		} else {
			parserNodeError(INV_ASSIGN_NODE, parser.consume(), "Assignation not done");
		}
	} else {
		parserNodeError(INV_ASSIGN_NODE, parser.consume(), "Invalid assignation");
	}
}

LiteralNode::LiteralNode( Parser& parser ) : ASTNode(NodeType::Literal) {
	std::cout << "  **LITERAL NODE CREATED**\n";

	if (parser.peek().type != literal)
		parserNodeError(INV_LITERAL_NODE, parser.consume(), "Invalid Literal Node");
	else
		value = parser.consume().value;
}

IdentifierNode::IdentifierNode( Parser& parser ) : ASTNode(NodeType::Identifier) {
	std::cout << "  **IDENTIFIER NODE CREATED**\n";

	if (parser.peek().type != identifier)
		parserNodeError(INV_IDENTIFIER_NODE, parser.consume(), "Invalid Identifier Node");
	else
		name = parser.consume().value;
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
}