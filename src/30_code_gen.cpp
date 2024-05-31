#include "code_gen.hpp"

/*-CONSTRUCTOR-*/

CodeGenerator::CodeGenerator( std::string outputFile ) : _outputFile(outputFile) {
	
}

/*-DESTRUCTOR-*/

CodeGenerator::~CodeGenerator() {
	for (ProgramNode* program : _parsedPrograms) {
		delete program;
	}
}

/*-METHODS-*/

void	CodeGenerator::addProgram( ProgramNode* program ) {
	_parsedPrograms.push_back(program);
}

void	CodeGenerator::writeFullProgramCode() {
	std::ofstream outDataFile("asm/data.asm", std::ios::out | std::ios::trunc);
	std::ofstream outCodeFile("asm/code.asm", std::ios::out | std::ios::trunc);
	
	if (outDataFile.is_open() && outCodeFile.is_open()) {
		/*-DATA-*/
		outDataFile << "section .data\n";

		/*-CODE-*/
		outCodeFile << "%include 'data.asm'\n\nsection .text\n  global _start\n\n_start:";
	}
}
