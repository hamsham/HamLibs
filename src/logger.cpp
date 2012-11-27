
//Allegro-based event-logging class
#include <ostream>
#include "../include/hamLibs.h"

namespace hamLibs {

logger::logger() :
	logFile(0)
{}
	
logger::logger(std::ostream* streamToLogWith) :
	logFile(streamToLogWith)
{}

logger::~logger() {
	logFile = 0;
}

bool logger::getLogState() const {
	return isLogging;
}

void logger::setLogState(bool state) {
	isLogging = state;
}

void logger::log(const char* info2Log, ...) {
	if (logFile == HL_NULL || isLogging == false) return;
	std::ostream& output = *logFile;
	
	va_list args;
	va_start(args, info2Log);
	output << "\t" << al_get_time() << " -- ";
	output << info2Log << args;
	output << "\n";
	va_end(args);
	output.flush();
}

} //end hamlibs namespace
