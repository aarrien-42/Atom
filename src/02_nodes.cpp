#include "nodes.hpp"

/*-BLOCK-*/

BlockNode::BlockNode( Parser& parser, size_t blockInitTab ) : ASTNode(NodeType::Block) {
	std::cout << "  **BLOCK NODE CREATED**\n";
	do {
		if (parser.peek().type == enter) {
			parser.consume();
			if (parser.peek().type == tab)
				parser.currentTabs = parser.consume().value.size();
			else
				parser.currentTabs = 0;
		} else if (parser.peek().type == tab) {
			parser.currentTabs = parser.consume().value.size();
		} else {
			std::cout << "Inside block = " << parser.peek().value << " type = " << parser.peek().type << std::endl;
			// block body check
			if (parser.peek().type == keyword) {
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
					std::cerr << "Invalid keyword\n";
				}
			} else if (parser.peek().type == identifier) {
				statements.push_back(new AssignNode(parser));
			} else {
				std::cerr << "Not implemented yet\n";
			}
			parser.consume();
		}
	} while (!parser.peek().value.empty() && parser.currentTabs > blockInitTab);
}

BoxNode::BoxNode( Parser& parser ) : ASTNode(NodeType::Box) {
	std::cout << "  **BOX NODE CREATED**\n";

	if (parser.peek().value == "(") {

	} else
		std::cerr << "Invalid Box Node";
}

/*-FUNCTION-*/

FuncDeclNode::FuncDeclNode( Parser& parser ) : ASTNode(NodeType::FuncDecl), body(nullptr) {
	std::cout << "  **FUNC DECL NODE CREATED**\n";

	functionName = parser.consume().value;
	std::cout << "	name = " << functionName << std::endl;
	if (parser.peek().type != enter) {
		std::cerr << "Invalid function declaration node\n";
	} else {
		parser.consume();
		body = new BlockNode(parser, parser.currentTabs);
	}
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
		
		
	} else {
		std::cerr << "Invalid Conditional Node\n";
	}
}

IfStatementNode::IfStatementNode( Parser& parser ) : ASTNode(NodeType::IfStatement), condition(nullptr), body(nullptr), ifBranch(nullptr), elseBranch(nullptr) {
	std::cout << "  **IF NODE CREATED**\n";

	if (parser.peek().value == "i.")
		parser.consume();
	if (parser.peek().type == enter )
		std::cerr << "If statement need a condition\n";
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
			if (parser.peek().type == enter)
				std::cerr << "Invalid variable assignation\n";
			if (parser.peek().type == literal) {
				initialValue = new LiteralNode(parser);
			} else if (parser.peek().type == identifier) {
				initialValue = new IdentifierNode(parser);
			}
		}
	} else {
		std::cerr << "Variable needs an identifier\n";
	}
	std::cout << "	Variable " << name << " declared\n";
}

AssignNode::AssignNode( Parser& parser ) : ASTNode(NodeType::Assign), value(nullptr) {
	std::cout << "  **ASSIGN NODE CREATED**\n";

	if (parser.peek().type == identifier) {
		variableName = parser.consume().value;
		std::cout << "assigned " << parser.peek().value << " to " << variableName << "\n";
		if (parser.peek().value == "=") {
			parser.consume();
			if (parser.peek().type == paren || parser.peek(1).type != enter) {
				value = new BoxNode(parser);
			} else {
				if (parser.peek().type == identifier)
					value = new IdentifierNode(parser);
				else if (parser.peek().type == literal)
					value = new LiteralNode(parser);
			}
		} else {
			std::cerr << "Assign error 1 \n";
		}
	} else {
		std::cerr << "Assign error 2 \n";
	}
}

LiteralNode::LiteralNode( Parser& parser ) : ASTNode(NodeType::Literal) {
	std::cout << "  **LITERAL NODE CREATED**\n";

	if (parser.peek().type != literal)
		std::cerr << "Invalid Literal Node\n";
	else
		value = parser.consume().value;
}

IdentifierNode::IdentifierNode( Parser& parser ) : ASTNode(NodeType::Identifier) {
	std::cout << "  **IDENTIFIER NODE CREATED**\n";

	if (parser.peek().type != identifier)
		std::cerr << "Invalid Identifier Node\n";
	else
		name = parser.consume().value;
}

/*-RETURN-*/

ReturnNode::ReturnNode( Parser& parser ) : ASTNode(NodeType::Return), returnValue(nullptr) {
	std::cout << "  **RETURN NODE CREATED**\n";

	if (parser.peek().value != "r.")
		std::cerr << "Invalid Return Node\n";
	else {
		if (parser.peek().type == paren)
			returnValue = new BoxNode(parser);
		else if (parser.peek().type == identifier)
			returnValue = new IdentifierNode(parser);
		else if (parser.peek().type == literal)
			returnValue = new LiteralNode(parser);
	}
}
