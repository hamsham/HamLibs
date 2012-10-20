/* 
 * File:   filesystem.h
 * Author: hammy
 *
 * Created on April 28, 2012, 9:19 PM
 */

#ifndef FILESYSTEM_H
#define	FILESYSTEM_H

namespace hamLibs {
namespace filesystem {
	std::string	getCurrentPath		();
	bool		setCurrentPath		(const char* path);
	void		getFileListing		(	containers::dynArray<ALLEGRO_FS_ENTRY*>& fileList,
								std::string extension,
								int flags =	ALLEGRO_FILEMODE_READ	|
											ALLEGRO_FILEMODE_WRITE	|
											ALLEGRO_FILEMODE_EXECUTE	|
											ALLEGRO_FILEMODE_HIDDEN	|
											ALLEGRO_FILEMODE_ISFILE	|
											ALLEGRO_FILEMODE_ISDIR	);
	void		clearFileListing	(containers::dynArray<ALLEGRO_FS_ENTRY*>& fileList);
	//extra functionality
	bool		fileIsReadable		(ALLEGRO_FS_ENTRY* inFile);	//check file properties
	bool		fileIsWritable		(ALLEGRO_FS_ENTRY* inFile);
	bool		fileIsExecutable	(ALLEGRO_FS_ENTRY* inFile);
	bool		fileIsHidden		(ALLEGRO_FS_ENTRY* inFile);
	bool		fileIsFile			(ALLEGRO_FS_ENTRY* inFile);
	bool		fileIsDirectory		(ALLEGRO_FS_ENTRY* inFile);
	
	bool		createDirectory		(const char* path);			//file interactions
	bool		filenameExists		(const char* path);
	bool		deleteFile			(const char* path);
	bool		filenameExists		(ALLEGRO_FS_ENTRY* path);
	bool		deleteFile			(ALLEGRO_FS_ENTRY* path);
	off_t		getFileSize			(ALLEGRO_FS_ENTRY* path);
	time_t		getFileAccessTime	(ALLEGRO_FS_ENTRY* path);
	time_t		getFileCreationTime	(ALLEGRO_FS_ENTRY* path);
	time_t		getFileModifiedTime	(ALLEGRO_FS_ENTRY* path);

}//end filesystem namespace
}//end hamLibs namespace

#endif	/* FILESYSTEM_H */
