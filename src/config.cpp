
//Allegro File Configuration Library
#include "../include/hamLibs.h"

namespace hamLibs {
	
config::config() :
	cfg( al_create_config() ),
	sectionIterator(HL_NULL),
	entryIterator(HL_NULL)
{}

config::~config() {
	if (cfg != HL_NULL) al_destroy_config(cfg);
}

//---------------------------------------------------------------------
//		File Handling
//---------------------------------------------------------------------
int config::loadConfigFile(const char* fileName) {
	//check if the file exists, then close the current file if necessary
	if (al_filename_exists(fileName) == false){
		return config::FILE_DOES_NOT_EXIST;
	}
	al_destroy_config(cfg);
	cfg = al_load_config_file(fileName);
	if (cfg != HL_NULL) {
		file = fileName;
		return config::LOAD_SUCCESS;
	}
	else {
		cfg = al_create_config();
		return config::LOAD_IO_ERROR;
	}
}

int config::saveConfigFile(const char* fileName, bool overwrite) {
	if (al_filename_exists(fileName) && overwrite == false)
		return config::OVERWRITE_PREVENTED;
	
	if (al_save_config_file(fileName, cfg)) {
		file = fileName;
		return config::SAVE_SUCCESS;
	}
	else {
		return config::SAVE_IO_ERROR;
	}
}

int config::saveConfigFile() {
	return saveConfigFile(file.c_str(), true);
}

void config::clearConfig() {
	al_destroy_config(cfg);
	cfg = al_create_config();
	sectionIterator = HL_NULL;
	entryIterator = HL_NULL;
	file.clear();
}

//---------------------------------------------------------------------
//		String Acquisition & Storage
//---------------------------------------------------------------------
const char* config::getFirstConfigSection() {
	return al_get_first_config_section(cfg, &sectionIterator);
}

const char* config::getNextConfigSection() {
	return al_get_next_config_section(&sectionIterator);
}

const char* config::getFirstConfigEntry(const char* section) {
	return al_get_first_config_entry(cfg, section, &entryIterator);
}

const char* config::getNextConfigEntry() {
	return al_get_next_config_entry(&entryIterator);
}

const char* config::getConfigVal(const char* section, const char* name) {
	return al_get_config_value(cfg, section, name);
}

void config::setConfigVal(const char* section, const char* name, const char* setValue) {
	//check if the config is not open
	al_set_config_value(cfg, section, name, setValue);
}

//---------------------------------------------------------------------
//		ETC
//---------------------------------------------------------------------
void config::addSection(const char* section) {
	al_add_config_section(cfg, section);
}

void config::addComment(const char* section, const char* comment) {
	al_add_config_comment(cfg, section, comment);
}

void config::append(const config& data) {
	al_merge_config_into(cfg, data.cfg);
}

} //end hamlibs namespace
