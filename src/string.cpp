
#include "../include/hamLibs.h"

namespace hamLibs {
namespace containers {

//---------------------------------------------------------------------
//			Misc functions not intended for external use
//---------------------------------------------------------------------
inline hlSize_t getStrLen(const char* str) {
    if (!str) return 0;
    register hlSize_t iter = 0;
    while (str[iter]) ++iter;
    return iter;
}

inline void copyStr(char* dest, const char* src, hlSize_t size) {
    while (size--) dest[size] = src[size];
}

inline void copyStr(char* dest, const char* src, hlSize_t size, hlSize_t destOffset) {
    while (size--) dest[size] = src[size+destOffset];
}

//forward-iterating comparisons
inline bool cmpStr(const char* str1, hlSize_t offset, const char* str2, hlSize_t size) {
    hlSize_t pos(0);
    while (pos != size) {
        if (str1[pos+offset] ^ str2[pos]) return false;
        ++pos;
    }
    return true;
}

//reverse-iterating comparisons
bool rCmpStr (const char* haystack, hlSize_t offset, const char* needle, hlSize_t nSize) {
    while (nSize) {
        --nSize;
        if (haystack[offset--] ^ needle[nSize]) return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//					HamString Class
///////////////////////////////////////////////////////////////////////////////
const int string::nPos( -1 );

//---------------------------------------------------------------------
//				Construction & Destruction
//---------------------------------------------------------------------
string::string() :
	array	(new char[1]),
	Size	(0)
{
	array[0] = 0;
}

string::string(char c) :
	array	(new char[2]),
	Size	(1)
{
	array[0] = c;
	array[1] = 0;
}

string::string(const char* str) {
	//determine the length of the string
	Size = getStrLen(str);
	//allocate memory; add a '+1' for NULL termination
	array = new char[Size+1];
	//copy
	copyStr(array, str, Size);
	//verify NULL termination
	array[Size] = 0;
}

string::string(const string& str) {
	//determine the length of the string
	Size = str.Size;
	//allocate memory; add a '+1' for NULL termination
	array = new char[Size+1];
	//copy
	copyStr(array, str.array, Size);
	//verify NULL termination
	array[Size] = 0;
}

string::~string() {
	delete [] array;
}

//---------------------------------------------------------------------
//				Operators
//---------------------------------------------------------------------
string& string::operator = (const char* str) {
	delete [] array;
	Size = getStrLen(str);
	array = new char[Size+1];
	copyStr(array, str, Size);
	array[Size] = 0;
	return *this;
}

string& string::operator = (const string& input) {
	delete [] array;
	Size = input.Size;
	array = new char[Size+1];
	copyStr(array, input.array, Size);
	array[Size] = 0;
	return *this;
}
string& string::operator = (char c) {
	Size = 1;
	delete [] array;
	array = new char[2];
	array[0] = c;
	array[1] = 0;
	return *this;
}

//---------------------------------------------------------------------
string& string::operator += (const string& input) {
	hlSize_t tempSize = Size + input.Size;
	char* temp = new char[tempSize+1]; //need room for NULL termination
	
	register hlSize_t i = 0;
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	
	for (register hlSize_t j = 0; j < input.Size; ++i, ++j) {
		temp[i] = input.array[j];
	}
	delete [] array;
	array = temp;
	Size = tempSize;
	return *this;
}
string& string::operator += (const char* str) {
	hlSize_t strLen = getStrLen(str);
	hlSize_t tempSize = Size + strLen;
	char* temp = new char[tempSize+1]; //need room for NULL termination
	
	register hlSize_t i = 0;
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	
	for (register hlSize_t j = 0; j < strLen; ++i, ++j) {
		temp[i] = str[j];
	}
	delete [] array;
	array = temp;
	Size = tempSize;
	return *this;
}
string& string::operator += (char c) {
	char* temp = new char[Size+2]; //need room for NULL termination & 'c'
	
	register hlSize_t i = 0;
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	temp[Size] = c;
	temp[++Size] = 0;
	
	delete [] array;
	array = temp;
	return *this;
}

//---------------------------------------------------------------------
string string::operator + (const string& str) const {
	string temp(*this);
	temp.push(Size, str.array, str.Size);
	return temp;
}
string string::operator + (const char* str) const {
	string temp(*this);
	temp.operator+=(str);
	return temp;
}
string string::operator + (char c) const {
	string temp(*this);
	temp.operator+=(c);
	return temp;
}

//---------------------------------------------------------------------
bool string::operator == (const string& compare) const {
	if (compare.Size != Size ) return false;
	return cmpStr(array, 0, compare.array, Size);
}
bool string::operator == (const char* compare) const {
	hlSize_t strLen = getStrLen(compare);
	if (strLen != Size ) return false;
	return cmpStr(array, 0, compare, Size);
}
bool string::operator == (char compare) const {
	if (Size != 1) return false;
	return array[0] == compare;
}

//---------------------------------------------------------------------
bool string::operator != (const string& compare) const {
	if (compare.Size != Size ) return true;
	return !cmpStr(array, 0, compare.array, Size);
}
bool string::operator != (const char* compare) const {
	hlSize_t strLen = getStrLen(compare);
	if (strLen != Size ) return true;
	return !cmpStr(array, 0, compare, Size);
}
bool string::operator != (char compare) const {
	if (Size != 1) return true;
	return array[0] != compare;
}

//---------------------------------------------------------------------
char& string::operator [](int i) {
	HL_ASSERT(i >= 0);
	return array[i];
}

char string::operator [](int i) const {
	HL_ASSERT(i >= 0);
	return array[i];
}

//---------------------------------------------------------------------
//				Deletion
//---------------------------------------------------------------------
void string::clear () {
	delete [] array;
	array = new char[1];
	Size = 0;
	array[0] = 0;
}

void string::popFront() {
	if (!Size) return;
	register hlSize_t i = 0;
	char* temp = new char[Size];
	--Size;
	
	while (i < Size) {
		temp[i] = array[i+1];
		++i;
	}
	delete [] array;
	array = temp;
	array[Size] = 0; //NULL termination
}
void string::popBack() {
	if (!Size) return;
	register hlSize_t i = 0;
	char* temp = new char[Size];
	--Size;
	
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	delete [] array;
	array = temp;
	array[Size] = 0; //NULL termination
}

void string::pop(hlSize_t index) {
	if (Size == 0) return;
	HL_ASSERT(index < Size);
	--Size;
	register hlSize_t i = 0;
	register hlSize_t j = 0;
	char* temp = new char[Size+1];
	
	while (i < Size) {
		temp[i] = (i != index) ? array[j] : array[++j];
		++i; ++j;
	}
	delete [] array;
	array = temp;
	array[Size] = 0; //NULL termination
}

//---------------------------------------------------------------------
//				Random Access Insertion
//---------------------------------------------------------------------
void string::push(hlSize_t index, const char* data, hlSize_t strSize) {
	if (index > Size) index = Size;
	hlSize_t tempSize = Size + strSize;
	char* temp = new char[tempSize+1];
	
	hlSize_t iter = 0;
	hlSize_t strPos = 0;
	while (iter < index) {
		temp[iter] = array[iter];
		++iter;
	}
	while (strPos < strSize) {
		temp[iter] = data[strPos];
		++iter;
		++strPos;
	}
	//return to where the first string was rudely interrupted
	strPos = index;
	while (strPos < Size) {
		temp[iter] = array[strPos];
		++iter;
		++strPos;
	}
	
	delete [] array;
	array = temp;
	Size = tempSize;
	array[Size] = 0;
}

void string::pushAfter(hlSize_t index, const char* data, hlSize_t strSize) {
	this->push(++index, data, strSize);
}

//hamStrings
void string::push(hlSize_t index, const string& str) {
	this->push(index, str.array, str.Size);
}
void string::pushAfter(hlSize_t index, const string& str) {
	this->push(++index, str.array, str.Size);
}

//char strings with unknown length
void string::push(hlSize_t index, const char* str) {
	hlSize_t strSize = getStrLen(str);
	this->push(index, str, strSize);
}
void string::pushAfter(hlSize_t index, const char* str) {
	hlSize_t strSize = getStrLen(str);
	this->push(++index, str, strSize);
}

//individual characters
void string::push(hlSize_t index, char c) {
	this->push(index, &c, 1);
}
void string::pushAfter(hlSize_t index, char c) {
	this->push(++index, &c, 1);
}

//---------------------------------------------------------------------
//				Direct Insertion
//---------------------------------------------------------------------
void string::pushFront (const char* str, hlSize_t strSize) {
	this->push(0, str, strSize);
}

void string::pushBack (const char* str, hlSize_t strSize) {
	this->push(Size, str, strSize);
}

void string::pushFront (const string& str) {
	this->push(0, str.array, str.Size);
}

void string::pushBack (const string& str) {
	this->push(Size, str.array, str.Size);
}

void string::pushFront (const char* str) {
	hlSize_t strSize = getStrLen(str);
	this->push(0, str, strSize);
}

void string::pushBack (const char* str) {
	hlSize_t strSize = getStrLen(str);
	this->push(Size, str, strSize);
}

void string::pushFront (char c) {
	const char str[1] = {c};
	this->push(0, str, 1);
}

void string::pushBack (char c) {
	const char str[1] = {c};
	this->push(Size, str, 1);
}


//---------------------------------------------------------------------
//				Traversal
//---------------------------------------------------------------------
char& string::front() {
	return array[0];
}

char& string::back() {
	return array[Size-1];
}

//---------------------------------------------------------------------
//				Searching
//---------------------------------------------------------------------
hlSize_t string::find(const char* str, hlSize_t strLen) const {
	if (!strLen || !Size) return nPos;
	hlSize_t currPos = 0;
	hlSize_t limit = 0 + strLen;
	--strLen;
	
	while (limit < Size) {
		limit = currPos+strLen;
		//only search for the requested substring if the
		//first and last letters are found within "array"
		if (	str[0] & array[currPos]
		&&		array[currPos+strLen] & str[strLen]
		&&		cmpStr(array, currPos, str, strLen+1)) return currPos;
		++currPos;
	}
	return nPos;
}

hlSize_t string::find(const string& str) const {
	return this->find(str.array, Size);
}

hlSize_t string::find(const char* str) const {
	hlSize_t strLength = getStrLen(str);
	return this->find(str, strLength);
}

hlSize_t string::find(char c) const {
	const char str[1] = {c};
	return this->find(str, 1);
}

//---------------------------------------------------------------------
hlSize_t string::rFind(const char* str, hlSize_t strLen) const {
	if (!strLen || !Size) return nPos;
	hlSize_t offset = Size-1;
	strLen -= 1;

	while (true) {
		if (	array[offset] == str[strLen]
		&&		array[offset-strLen] == str[0]
		&&		rCmpStr(array, offset, str, strLen+1)) return offset-strLen;
		if (!offset) break;
		--offset;
	}
	return nPos;
}

hlSize_t string::rFind(const string& str) const {
	return this->rFind(str.array, Size);
}

hlSize_t string::rFind(const char* str) const {
	hlSize_t strLength = getStrLen(str);
	return this->rFind(str, strLength);
}

hlSize_t string::rFind(char c) const {
	const char str[1] = {c};
	return this->rFind(str, 1);
}

//---------------------------------------------------------------------
//				Utility Functions
//---------------------------------------------------------------------
void string::copy (const string& str) {
	this->operator=(str);
}
void string::copy (const char* str) {
	this->operator=(str);
}
void string::copy (char c) {
	this->operator=(c);
}

//---------------------------------------------------------------------
void string::append (const string& str) {
	this->push(Size, str.array, str.Size);
}

void string::append (const char* str, hlSize_t strLength) {
	this->push(Size, str, strLength);
}

void string::append (const char* str) {
	hlSize_t strSize = getStrLen(str);
	this->push(Size, str, strSize);
}

void string::append (char c) {
	const char str[1] = {c};
	this->push(Size, str, 1);
}

//---------------------------------------------------------------------
void string::resize (hlSize_t newSize, char c) {
	if (newSize == Size) return;
	char* temp = new char[newSize+1];
	
	for (register hlSize_t i = 0; i < newSize; ++i) {
		if (newSize > Size && i >= Size) {
			temp[i] = c;
		}
		else {
			temp[i] = array[i];
		}
	}
	
	Size = newSize;
	delete [] array;
	array = temp;
	array[Size] = 0;
}

void string::resize(hlSize_t newSize) {
	this->resize(newSize, '\0');
}

//---------------------------------------------------------------------
//				Miscellaneous
//---------------------------------------------------------------------
string string::subStr(hlSize_t pos, hlSize_t length) const {
	string temp;
	//error checking
	if (pos > Size) return temp;
	delete [] temp.array;
	if (pos+length > Size) length = Size-pos;
	temp.array = new char[length+1];
	temp.Size = length;
	
	copyStr(temp.array, this->array, length, pos);
	temp.array[length] = 0;
	return temp;
}

bool string::empty () const {
	return (Size) ? false : true;
}

hlSize_t string::size () const {
	return Size;
}

void string::swap (string& input) {
	char* temp = input.array;
	input.array = array;
	array = temp;
}

const char* string::cStr () const {
	return array;
}

} // end containers namespace
} //end hamLibs namespace
