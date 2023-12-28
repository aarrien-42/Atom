#include <iostream>
#include "error.hpp"

int main(int ac, char** av) {
	if (ac != 2)
		exitError(E_INVALID_EXEC);
	(void)av;
	return 0;
}