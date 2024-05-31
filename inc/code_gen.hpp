#ifndef CODE_GEN_HPP
#define CODE_GEN_HPP

#include <iostream>
#include <filesystem>

#include <string>
#include <vector>

#include "nodes.hpp"

struct ProgramNode;

class CodeGenerator {
	private:
		std::string _outputFile;
		std::vector<ProgramNode*> _parsedPrograms;
	public:
		CodeGenerator( std::string );
		~CodeGenerator();

		void	addProgram( ProgramNode* );
		void	writeFullProgramCode();
};

#endif