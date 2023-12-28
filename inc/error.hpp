#ifndef ERROR_HPP
#define ERROR_HPP

	#include <iostream>
	#include "atom.hpp"

	enum Error {
		E_INVALID_EXEC, E_INVALID_FILE
	};

	void	printError( const std::string& str );
	void	exitError( const Error& error );

#endif