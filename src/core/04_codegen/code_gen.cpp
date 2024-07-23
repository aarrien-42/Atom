#include "code_gen.hpp"

/*-CONSTRUCTOR-*/

CodeGeneratorManager::CodeGeneratorManager( std::string outputFile ) : _assemblyCodeFileName("code"), _outputFileName(outputFile) {}

/*-DESTRUCTOR-*/

CodeGeneratorManager::~CodeGeneratorManager() {
    // Delete all AST structures
    for (ProgramNode* program : _parsedPrograms) {
        delete program;
    }
}

/*-METHODS-*/

void CodeGeneratorManager::addProgram( ProgramNode* program ) {
    _parsedPrograms.push_back(program);
}

void CodeGeneratorManager::writeFullProgramCode() {
    ConfigManager& config = ConfigManager::getInstance();
    config.printDebug("Output program = " + _outputFileName + "\n", MAGENTA);

    _outCodeFile.open(_assemblyCodeFileName + ".asm", std::ios::out | std::ios::trunc);

    if (_outCodeFile.is_open()) {
        /*-CODE-*/
        _outCodeFile << "section .bss\n";
        config.printDebug("Variables:\n", YELLOW);
        for (size_t progCount = 0; progCount < _parsedPrograms.size(); progCount++) {
            for (auto function : _parsedPrograms[progCount]->functions) {
                FuncDeclNode* funcNode = dynamic_cast<FuncDeclNode*>(function);
                config.printDebug("  - Function [" + funcNode->functionName + "]:\n", YELLOW);
                for (std::vector<std::string>::const_iterator it = funcNode->funcVariables.begin(); it != funcNode->funcVariables.end(); it++) {
                    config.printDebug("    - " + *it + "\n", YELLOW);
                    _outCodeFile << "  " << *it << " resb 8\n";
                }
            }
        }

        // Start writting the program
        _outCodeFile << "section .text\n";
        _outCodeFile << "  global _start\n";
        for (size_t progCount = 0; progCount < _parsedPrograms.size(); progCount++) {
            nodeHandler(_parsedPrograms[progCount]);
        }

        // Close assembly code files
        _outCodeFile.close();

        // Compile and link assembly code
        ConfigManager::getInstance().printDebug("\nCOMPILING AND LINKING CODE:\n\n", BOLDBLUE);
        assembleAndLink();

        // Execute code
        ConfigManager::getInstance().printDebug("\nEXECUTING CODE:\n\n", BOLDBLUE);
        ConfigManager::getInstance().printDebug("Execution result:\n", MAGENTA);

        int exitCode = std::system(("./" + _outputFileName).c_str());
        exitCode = WIFEXITED(exitCode) ? WEXITSTATUS(exitCode) : -1;

        ConfigManager::getInstance().printDebug("Exit code:\n", MAGENTA);
        ConfigManager::getInstance().printDebug(std::to_string(exitCode) + "\n");
    }
}

void CodeGeneratorManager::nodeHandler( ASTNode* node ) {
    if (node == nullptr) {
        return;
    }

    ConfigManager::getInstance().printDebug("Node type = " + std::to_string(node->getType()) + "\n");
    switch (node->getType()) {
        case NodeType::Program: {
            ConfigManager::getInstance().printDebug("  ProgramNode:\n", GREEN);
            ProgramNode* programNode = dynamic_cast<ProgramNode*>(node);
            for (ASTNode* function : programNode->functions) {
                nodeHandler(function);
            }
            break;
        }
        case NodeType::Block: {
            ConfigManager::getInstance().printDebug("  BlockNode:\n", GREEN);
            BlockNode* programNode = dynamic_cast<BlockNode*>(node);
            for (ASTNode* statement : programNode->statements) {
                nodeHandler(statement);
            }
            break;
        }
        case NodeType::Box: {
            ConfigManager::getInstance().printDebug("  BoxNode:\n", GREEN);
            BoxNode* boxNode = dynamic_cast<BoxNode*>(node);
            nodeHandler(boxNode->node);
            break;
        }
        case NodeType::FuncDecl: {
            ConfigManager::getInstance().printDebug("  FuncDeclNode:\n", GREEN);
            FuncDeclNode* funcDeclNode = dynamic_cast<FuncDeclNode*>(node);
            writeFuncDeclNode(funcDeclNode);
            nodeHandler(funcDeclNode->body);
            break;
        }
        case NodeType::FuncCall: {
            ConfigManager::getInstance().printDebug("  FuncCallNode:\n", GREEN);
            FuncCallNode* funcCallNode = dynamic_cast<FuncCallNode*>(node);
            writeFuncCallNode(funcCallNode);
            break;
        }
        case NodeType::Condition: {
            ConfigManager::getInstance().printDebug("  ConditionNode:\n", GREEN);
            ConditionNode* conditionNode = dynamic_cast<ConditionNode*>(node);
            writeConditionNode(conditionNode);
            break;
        }
        case NodeType::IfStatement: {
            ConfigManager::getInstance().printDebug("  IfStatementNode:\n", GREEN);
            IfStatementNode* ifStatementNode = dynamic_cast<IfStatementNode*>(node);
            writeIfStatementNode(ifStatementNode);
            break;
        }
        case NodeType::WhileLoop: {
            ConfigManager::getInstance().printDebug("  WhileLoopNode:\n", GREEN);
            WhileLoopNode* whileLoopNode = dynamic_cast<WhileLoopNode*>(node);
            writeWhileLoopNode(whileLoopNode);
            break;
        }
        case NodeType::ForLoop: {
            ConfigManager::getInstance().printDebug("  ForLoopNode:\n", GREEN);
            ForLoopNode* forLoopNode = dynamic_cast<ForLoopNode*>(node);
            writeForLoopNode(forLoopNode);
            break;
        }
        case NodeType::BinOp: {
            ConfigManager::getInstance().printDebug("  BinOpNode:\n", GREEN);
            BinOpNode* binOpNode = dynamic_cast<BinOpNode*>(node);
            writeBinOpNode(binOpNode);
            break;
        }
        case NodeType::UnaryOp: {
            ConfigManager::getInstance().printDebug("  UnaryOpNode:\n", GREEN);
            UnaryOpNode* unaryOpNode = dynamic_cast<UnaryOpNode*>(node);
            writeUnaryOpNode(unaryOpNode);
            break;
        }
        case NodeType::VarDecl: {
            ConfigManager::getInstance().printDebug("  VarDeclNode:\n", GREEN);
            VarDeclNode* varDeclNode = dynamic_cast<VarDeclNode*>(node);
            writeVarDeclNode(varDeclNode);
            break;
        }
        case NodeType::Assign: {
            ConfigManager::getInstance().printDebug("  AssignNode:\n", GREEN);
            AssignNode* assignNode = dynamic_cast<AssignNode*>(node);
            writeAssignNode(assignNode);
            break;
        }
        case NodeType::Literal: {
            ConfigManager::getInstance().printDebug("  LiteralNode:\n", GREEN);
            LiteralNode* literalNode = dynamic_cast<LiteralNode*>(node);
            writeLiteralNode(literalNode);
            break;
        }
        case NodeType::Identifier: {
            ConfigManager::getInstance().printDebug("  IdentifierNode:\n", GREEN);
            IdentifierNode* identifierNode = dynamic_cast<IdentifierNode*>(node);
            writeIdentifierNode(identifierNode);
            break;
        }
        case NodeType::Return: {
            ConfigManager::getInstance().printDebug("  ReturnNode:\n", GREEN);
            ReturnNode* returnNode = dynamic_cast<ReturnNode*>(node);
            writeReturnNode(returnNode);
            break;
        }
    }
}

void CodeGeneratorManager::writeFuncDeclNode( FuncDeclNode* node ) {
    if (node->functionName == "main:") {
        _outCodeFile << "_start:\n";
    } else {
        _outCodeFile << node->functionName << "\n";
    }
    (void)node;
}

void CodeGeneratorManager::writeFuncCallNode( FuncCallNode* node ) {
    (void)node;
}

void CodeGeneratorManager::writeConditionNode( ConditionNode* node ) {
    (void)node;
}

void CodeGeneratorManager::writeIfStatementNode( IfStatementNode* node ) {
    (void)node;
}

void CodeGeneratorManager::writeWhileLoopNode( WhileLoopNode* node ) {
    (void)node;
}

void CodeGeneratorManager::writeForLoopNode( ForLoopNode* node ) {
    (void)node;
}

void CodeGeneratorManager::writeBinOpNode( BinOpNode* node ) {
    ConfigManager::getInstance().printDebug("Operation: [" + node->operation + "]\n", BLUE);

    nodeHandler(node->leftOp);
    nodeHandler(node->rightOp);

    _outCodeFile << "  POP rcx\n";
    _outCodeFile << "  POP rax\n";

    if (node->operation.size() == 1) {
        char op = node->operation.at(0);
        switch (op) {
            case '+':
                _outCodeFile << "  ADD rax, rcx\n";
                break;
            case '-':
                _outCodeFile << "  SUB rax, rcx\n";
                break;
            case '*':
                _outCodeFile << "  MUL rcx\n";
                break;
            case '/':
                _outCodeFile << "  DIV rcx\n";
                break;
        }
    }
    _outCodeFile << "  PUSH rax\n\n";
}

void CodeGeneratorManager::writeUnaryOpNode( UnaryOpNode* node ) {
    (void)node;
}

void CodeGeneratorManager::writeVarDeclNode( VarDeclNode* node ) {
    if (node->initialValue != nullptr) {
        nodeHandler(node->initialValue);
    }
}

void CodeGeneratorManager::writeAssignNode( AssignNode* node ) {
    nodeHandler(node->value);
    _outCodeFile << "; Assign value to " << node->variableName << "\n";
    _outCodeFile << "  POP rax\n";
    _outCodeFile << "  MOV qword [" << node->variableName << "], rax\n\n";
}

void CodeGeneratorManager::writeLiteralNode( LiteralNode* node ) {
    _outCodeFile << "; Get literal value\n";

    _outCodeFile << "  PUSH " << node->value << "\n\n";
}

void CodeGeneratorManager::writeIdentifierNode( IdentifierNode* node ) {
    _outCodeFile << "; Get identifier value\n";

    _outCodeFile << "  MOV rax, qword [" << node->name << "]\n";
    _outCodeFile << "  PUSH rax\n\n";
}

void CodeGeneratorManager::writeReturnNode( ReturnNode* node ) {
    nodeHandler(node->returnValue);
    _outCodeFile << "  POP rdi\n"; // Set exit value
    _outCodeFile << "  MOV rax, 60\n"; // Set exit syscall
    _outCodeFile << "  syscall\n\n";
}


void CodeGeneratorManager::assembleAndLink() {
    // Remove any existing same name executable
    std::remove(_outputFileName.c_str());

    // Assemble the assembly file using NASM
    std::string asmFile = _assemblyCodeFileName + ".asm";
    std::string objFile = _assemblyCodeFileName + ".o";

    std::string nasmCommand = "nasm -f elf64 -g " + asmFile + " -o " + objFile;
    ConfigManager::getInstance().printDebug("Nasm command : " + nasmCommand + "\n", RED);
    int nasmResult = std::system(nasmCommand.c_str());

    if (nasmResult != 0) {
        std::cerr << "Error: NASM assembler failed with code " << nasmResult << std::endl;
        return;
    }

    // Link the object file using LD
    std::string ldCommand = "ld " + objFile + " -o " + _outputFileName;
    ConfigManager::getInstance().printDebug("Ld command : " + ldCommand + "\n", RED);
    int ldResult = std::system(ldCommand.c_str());

    if (ldResult != 0) {
        std::cerr << "Error: LD linker failed with code " << ldResult << std::endl;
        return;
    }

    // Remove not executable files
    if (ConfigManager::getInstance().canRemoveAssemblyCode()) {
        std::remove(asmFile.c_str());
    }
    std::remove(objFile.c_str());
}
