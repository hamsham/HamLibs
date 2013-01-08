//database library

#ifndef __HAMLIBS_DATABASE_H__
#define __HAMLIBS_DATABASE_H__

#include "containers/dynArr.h"


/*
	This database library reads in *.CSV text files.
	One vector is used to hold the horizontal lines
	while another is used to hold the vertical lines.
*/

namespace hamLibs {
	
enum CSV_Status {
	CSV_LOAD_FAILED,
	CSV_LOAD_DENIED,
	CSV_LOAD_SUCCESS
};

class database {
	private:
		typedef containers::dynArray< containers::dynArray<std::string> > dataArray;
		typedef containers::linkedList< containers::linkedList<std::string> > dataList;
		dataArray data;
		
		static void	saveToCSV	(const dataArray& dataToSave, const char* fileName);
		static void	saveToCSV	(dataList& dataToSave, const char* fileName); //resets iteration positions

	public:
		database	();
		database	(const database& copy);
		~database	();

		// file loading functions
		int			loadCSV			(const char* fileName, char delim = ',', char textDelim = '\"');
		void		unloadCSV		();

		// data loading & saving
		void		saveDB			(const char* fileName) const;
		void		copyToDB		(database& dbToPut) const;
		void		copyFromDB		(const database& dbToGet);
		void		getDb			(dataArray& inDB) const;
		
		//misc
		void		printDB			() const;
		
		// data extraction & manipulation, all vector positions start at 0 like arrays
		template <typename dataType>
		void		getItem			(dataType* item, int row, int column) const;
		std::string	getItem		(int row, int column) const;
		template <typename dataType>
		void		setItem			(int row, int column, const dataType& value);
		void		setItem			(int row, int column, const char* value);
		int			findByRow		(int row, const std::string& item);
		int			findByCol		(int col, const std::string& item);
		void		insertRow		(hlSize_t position);
		void		insertCol		(hlSize_t position);
		void		deleteRow		(hlSize_t position);
		void		deleteCol		(hlSize_t position);
};

//---------------------------------------------------------
//	Data Extraction & Manipulation
//---------------------------------------------------------
template <typename dataType>
void database::getItem(dataType* item, int row, int column) const {
	if ( (row < 0) || (row > data.size()) || (column < 0) || (column > data[row].size())) {
		item = 0;
		return;
	}
	stringUtils::convertToType(data[row][column], *item);
}

template <typename dataType>
void database::setItem(int row, int column, const dataType& value) {
	if ( (row < 0) || (row > data.size()) || (column < 0) || (column > data[row].size())) {
		return;
	}
	stringUtils::convertToString(value, data[row][column]);
}

} //end hamlibs namespace
#endif
