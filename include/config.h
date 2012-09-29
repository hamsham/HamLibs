//Allegro File Configuration Library

#ifndef __HAMLIBS_CONFIG_H__
#define __HAMLIBS_CONFIG_H__

namespace hamLibs {

class config {
	private:
		ALLEGRO_CONFIG*		cfg;
		ALLEGRO_CONFIG_SECTION*	sectionIterator;
		ALLEGRO_CONFIG_ENTRY*	entryIterator;
		std::string			file;
		
		typedef const char* cstr;

	public:
		enum configLoadStatus {
			LOAD_SUCCESS,
			CONFIG_NOT_EMPTY,
			FILE_DOES_NOT_EXIST,
			LOAD_IO_ERROR
		};
		enum configSaveStatus {
			SAVE_SUCCESS,
			CONFIG_EMPTY,
			OVERWRITE_PREVENTED,
			SAVE_IO_ERROR
		};
		
		config		();
		config		(const config& cfgCopy); //undefined
		~config		();
		config& operator = ( const config& cfgCopy ); //undefined

		//file handling
		int	loadConfigFile				(cstr fileName);
		int	saveConfigFile				(cstr fileName, bool overwrite = true);
		int	saveConfigFile				();
		void	clearConfig				();
		bool	checkIfOpen				() {return (cfg != HL_NULL) ? true : false;};

		//data acquisition & manipulation
		cstr	getFirstConfigSection	();
		cstr	getNextConfigSection	();
		cstr	getFirstConfigEntry		(cstr section);
		cstr	getNextConfigEntry		(cstr section);
		cstr	getConfigVal			(cstr section, cstr name);
		void	setConfigVal			(cstr section, cstr name, cstr setValue);
		
		//etcetera
		void	addSection			(cstr section);
		void	addComment			(cstr section, cstr comment);
		void	append				(const config& data);
};

} // end hamlibs namespace
#endif	/* CONFIG_H */
