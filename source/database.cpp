
//database implementation
#include "../include/hamLibs.h"

namespace hamLibs {
using namespace std;

//---------------------------------------------------------
//	[De]Construction
//---------------------------------------------------------

database::database() {
}

database::database(const database& copy) {
	for (size_t i = 0; i < copy.data.size(); ++i) {
		data.pushBack(copy.data[i]);
		for (size_t j = 0; j < copy.data[i].size(); ++j) {
			data[i].pushBack(copy.data[i][j]);
		}
	}
}

database::~database() {
	data.clear();
}

//---------------------------------------------------------
//	File Loading & Saving
//---------------------------------------------------------

	int database::loadCSV(const char* fileName, char delim, char textDelim) {
	//return a CSV loading status code using the enumeration in the header file
	if (data.empty() == false) return CSV_LOAD_DENIED;

	ifstream fin;
	fin.sync_with_stdio(false);
	std::string input;
	char inChar = 0;
	containers::dynArray<std::string> row;
	bool stringFound = false;

	fin.open(fileName, ifstream::in);
	if (!fin.good()) {
		return CSV_LOAD_FAILED;
	}

	while (fin.good()) {
		inChar = fin.get();
		if (inChar == textDelim) {
			stringFound = !stringFound;
		}
		//text string delimeters are removed upon finding
		if (inChar == delim || inChar == '\n' || !fin.good()) {
			if (stringFound == false || !fin.good()) {
				row.pushBack(input);
				input.clear();
			}
			if (inChar != delim && inChar != '\r' && stringFound == false) {
				data.pushBack(row);
				row.clear();
			}
		}
		else {
			input.push_back(inChar);
		}
	}
	row.clear();
	fin.close();
	return CSV_LOAD_SUCCESS;
}

void database::unloadCSV() {
	data.clear();
}

void database::saveToCSV(const dataArray &dataToSave, const char* fileName) {
	size_t length = 0;
	size_t ending = dataToSave.size()-1;
	ofstream fout;
	fout.sync_with_stdio(false);
	fout.open(fileName);
	for (size_t i = 0; i < dataToSave.size(); ++i) {
			length = dataToSave[i].size();
			for (size_t j = 0; j < length; ++j) {
				fout << dataToSave[i][j].c_str();
				if (j+1 != length) fout << ",";
			}
			if (i != ending) fout << endl;
	}
	fout.close();
}

void database::saveToCSV(dataList &dataToSave, const char* fileName) {
	const size_t ending = dataToSave.size()-1;
	ofstream fout;
	fout.sync_with_stdio(false);
	fout.open(fileName);
	dataToSave.goToFront();
	for (size_t rowIter = dataToSave.size(); rowIter; --rowIter) {
			dataToSave.getCurrent()->goToFront();
			for (size_t colIter = dataToSave.getCurrent()->size(); colIter; --colIter) {
				fout << dataToSave.getCurrent()->getCurrent()->c_str();
				if (colIter+1 != dataToSave.getCurrent()->size()) fout << ",";
				dataToSave.getCurrent()->goToNext();
			}
			if (rowIter != ending) fout << endl;
			dataToSave.goToNext();
	}
	fout.close();
}

void database::saveDB(const char* fileName) const {
	saveToCSV(data, fileName);
}

void database::copyFromDB(const database& dbToGet) {
	data = dbToGet.data;
}

void database::copyToDB(database& dbToPut) const {
	dbToPut.data = data;
}

void database::getDb(dataArray& inData) const {
	inData = data;
}

//---------------------------------------------------------
//	Misc
//---------------------------------------------------------
#ifdef DEBUG
void database::printDB() const {
	size_t length = 0;
	for (size_t i = 0; i < data.size(); ++i) {
		length = data[i].size() - 1;
		cout << i << ": ";
		for (size_t j = 0; j < length; ++j) {
		cout << data[i][j].c_str();
			if (j != length) cout << ", ";
		}
		cout << endl;
	}
	cout << endl;
}
#endif

//---------------------------------------------------------
//	Data Extraction & manipulation
//---------------------------------------------------------
//get & set data-------------------------------------------------------
std::string database::getItem(int row, int column) const {
	//character strings were removed upon loading the database
	HL_ASSERT((row < data.size()) && (column < data[row].size()));
	std::string parser(data[row][column]);
	return parser.c_str();
}

void database::setItem(int row, int column, const char* value) {
	HL_ASSERT((row < data.size()) && (column < data[row].size()));
	data[row][column] = value;
}

//find data------------------------------------------------------------
int database::findByRow(int row, const std::string& item) {
	for (size_t i = 0; i < data[row].size(); ++i) {
		if (data[i][row] == item) return i;
	}
	return -1; //if item is not found
}

int database::findByCol(int col, const std::string& item) {
	for (size_t i = 0; i < data.size(); ++i) {
		if (data[col][i] == item) return i;
	}
	return -1; //if item is not found
}

//insert empty stuff---------------------------------------------------
void database::insertRow(size_t position) {
	containers::dynArray<std::string> newVal;
	if (position < data.size()) {
		data.push(position, newVal);
	}
	else {
		data.pushBack(newVal);
	}
}

void database::insertCol(size_t position) {
	std::string newVal;
	for (size_t i = 0; i < data.size(); ++i) {
		if (position < data[i].size()) {
			data[i].push(position, newVal);
		}
	}
}

//delete stuff---------------------------------------------------------
void database::deleteRow(size_t position) {
	data.pop(position);
}

void database::deleteCol(size_t position) {
	for (size_t i = 0; i < data.size(); ++i) {
		if (position < data[i].size()) {
			data[i].pop(position);
		}
	}
}

} //end hamlibs namespace
