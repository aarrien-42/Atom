#include "utils.hpp"

bool isStrInVector( const std::string& buffer , const std::vector<std::string>& vector ) {
	for (std::vector<std::string>::const_iterator it = vector.begin(); it != vector.end(); it++) {
		if (*it == buffer)
			return true;
	}
	return false;
}

char getStrEndChar( const std::string& str ) {
	return *(str.end()-1);
}
