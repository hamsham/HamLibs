
//hamLibs miscellaneous functions
#include "../include/hamLibs.h"

namespace hamLibs {
	
	bool hlInit() {
		if (!al_init()) return false;
	}
	
}//end hamlibs namespace
