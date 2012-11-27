/* 
 * File:   filesystem.cpp
 * Author: hammy
 * 
 * Created on April 28, 2012, 9:19 PM
 */

#include "../include/hamLibs.h"

//private stuff. beware.
namespace {
	ALLEGRO_FS_ENTRY* fs = HL_NULL;
	std::string directory;
}

namespace hamLibs {
namespace filesystem {
	using namespace containers;
//end anonymous namespace

bool setCurrentPath(const char* path) {
	directory = path;
	fs = al_create_fs_entry(directory.c_str());
	if (al_fs_entry_exists(fs) && directory.size() > 0) {
		al_destroy_fs_entry(fs);
		return true;
	}
	else {
		al_destroy_fs_entry(fs);
		return false;
	}
}

std::string getCurrentPath() {
	if (!directory.empty())	return directory;
	else {
		directory = al_get_current_directory();
		return directory;
	}
}

void getFileListing(	dynArray<ALLEGRO_FS_ENTRY*>& fileList,
						std::string extension,
						int flags	) {
	fs = al_create_fs_entry(directory.c_str());
	if (al_open_directory(fs) == false) {
		al_destroy_fs_entry(fs);
		return;
	}
	ALLEGRO_FS_ENTRY* filePopulator = HL_NULL;
	clearFileListing(fileList);
	int fNameSize = 0;
	std::string fileName;
	if (!extension.empty() && extension[0] != '.') {
		extension.insert(0, ".", 1);
	}
	
	while (true) {
		filePopulator = al_read_directory(fs);
		if (filePopulator == HL_NULL) break;
		if ((flags & al_get_fs_entry_mode(filePopulator)) == 0) continue;
		if (extension.size() == 0) {
			fileList.pushBack(filePopulator);
		}
		else {
			fileName = al_get_fs_entry_name(filePopulator);
			fNameSize = fileName.size() - extension.size();
			if (fileName.substr(fileName.find_last_of(extension, fNameSize)) == extension) {
				fileList.pushBack(filePopulator);
			}
		}
	}
	al_close_directory(fs);
	al_destroy_fs_entry(fs);
}

//---------------------------------------------------------------------
//				filesystem function definitions
//---------------------------------------------------------------------
bool fileIsReadable(ALLEGRO_FS_ENTRY* inFile) {
	return (al_get_fs_entry_mode(inFile) & ALLEGRO_FILEMODE_READ) ? true : false;
}

bool fileIsWritable(ALLEGRO_FS_ENTRY* inFile) {
	return (al_get_fs_entry_mode(inFile) & ALLEGRO_FILEMODE_WRITE) ? true : false;
}

bool fileIsExecutable(ALLEGRO_FS_ENTRY* inFile) {
	return (al_get_fs_entry_mode(inFile) & ALLEGRO_FILEMODE_EXECUTE) ? true : false;
}

bool fileIsHidden(ALLEGRO_FS_ENTRY* inFile) {
	return (al_get_fs_entry_mode(inFile) & ALLEGRO_FILEMODE_HIDDEN) ? true : false;
}

bool fileIsFile(ALLEGRO_FS_ENTRY* inFile) {
	return (al_get_fs_entry_mode(inFile) & ALLEGRO_FILEMODE_ISFILE) ? true : false;
}

bool fileIsDirectory(ALLEGRO_FS_ENTRY* inFile) {
	return (al_get_fs_entry_mode(inFile) & ALLEGRO_FILEMODE_ISDIR) ? true : false;
}

void clearFileListing(containers::dynArray<ALLEGRO_FS_ENTRY*>& fileList) {
	size_t iter = fileList.size();
	while(iter--) {
		al_destroy_fs_entry(fileList[iter]);
	}
	fileList.clear();
}

//---------------------------------------------------------------------
//				File/Folder Interaction
//---------------------------------------------------------------------
bool		createDirectory		(const char* path) {
	return al_make_directory(path);
}

bool		filenameExists		(const char* path) {
	return al_filename_exists(path);
}

bool		deleteFile			(const char* path) {
	return al_remove_filename(path);
}

bool		filenameExists		(ALLEGRO_FS_ENTRY* path) {
	return al_fs_entry_exists(path);
}

bool		deleteFile			(ALLEGRO_FS_ENTRY* path) {
	return al_remove_fs_entry(path);
}

off_t		getFileSize			(ALLEGRO_FS_ENTRY* path) {
	return al_get_fs_entry_size(path);
}

time_t		getFileAccessTime	(ALLEGRO_FS_ENTRY* path) {
	return al_get_fs_entry_atime(path);
}

time_t		getFileCreationTime	(ALLEGRO_FS_ENTRY* path) {
	return al_get_fs_entry_ctime(path);
}

time_t		getFileModifiedTime	(ALLEGRO_FS_ENTRY* path) {
	return al_get_fs_entry_mtime(path);
}

} //end filesystem namespace
}//end hamLibs namespace
