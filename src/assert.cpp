
#include <iostream>
#include "../include/utils/assert.h"

void hamLibs::utils::runtime_assert(bool condition, error_t type, const char* const msg) {
	if (condition) {
        return;
    }

	const char* const errorString[] = {
        "ALERT: ",
        "WARNING: ",
        "ERROR: "
    };
    
	std::ostream& stream = (type > ALERT) ? std::cerr : std::cout;
	
	stream << errorString[type] << msg << std::endl;

	if (type == ERROR) {
        throw ERROR;
    }
}
