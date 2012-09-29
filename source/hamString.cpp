
#include "../include/hamLibs.h"
namespace hamLibs {

//---------------------------------------------------------------------
//			Misc functions not intended for external use
//---------------------------------------------------------------------
namespace {
	inline size_t getStrLen(const char* str) {
		if (!str) return 0;
		register size_t iter = 0;
		while (str[iter]) ++iter;
		return iter;
	}
	
	inline void copyStr(char* dest, const char* src, size_t size) {
		while (size--) dest[size] = src[size];
	}
	
	inline void copyStr(char* dest, const char* src, size_t size, size_t destOffset) {
		while (size--) dest[size] = src[size+destOffset];
	}
	
	//forward-iterating comparisons
	inline bool cmpStr(const char* str1, size_t offset, const char* str2, size_t size) {
		size_t pos(0);
		while (pos != size) {
			if (str1[pos+offset] ^ str2[pos]) return false;
			++pos;
		}
		return true;
	}
	
	//reverse-iterating comparisons
	bool rCmpStr (const char* haystack, size_t offset, const char* needle, size_t nSize) {
		while (nSize) {
			--nSize;
			if (haystack[offset--] ^ needle[nSize]) return false;
		}
		return true;
	}
} //end anonymous namespace

///////////////////////////////////////////////////////////////////////////////
//					HamString Class
///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
//				Construction & Destruction
//---------------------------------------------------------------------
hamString::hamString() :
	array	(new char[1]),
	Size	(0)
{
	array[0] = 0;
}

hamString::hamString(char c) :
	Size	(1),
	array	(new char[2])
{
	array[0] = c;
	array[1] = 0;
}

hamString::hamString(const char* str) {
	//determine the length of the string
	Size = getStrLen(str);
	//allocate memory; add a '+1' for NULL termination
	array = new char[Size+1];
	//copy
	copyStr(array, str, Size);
	//verify NULL termination
	array[Size] = 0;
}

hamString::hamString(const hamString& str) {
	//determine the length of the string
	Size = str.Size;
	//allocate memory; add a '+1' for NULL termination
	array = new char[Size+1];
	//copy
	copyStr(array, str.array, Size);
	//verify NULL termination
	array[Size] = 0;
}

hamString::~hamString() {
	delete [] array;
}

//---------------------------------------------------------------------
//				Operators
//---------------------------------------------------------------------
hamString& hamString::operator = (const char* str) {
	delete [] array;
	Size = getStrLen(str);
	array = new char[Size+1];
	copyStr(array, str, Size);
	array[Size] = 0;
	return *this;
}

hamString& hamString::operator = (const hamString& input) {
	delete [] array;
	Size = input.Size;
	array = new char[Size+1];
	copyStr(array, input.array, Size);
	array[Size] = 0;
	return *this;
}
hamString& hamString::operator = (char c) {
	Size = 1;
	delete [] array;
	array = new char[2];
	array[0] = c;
	array[1] = 0;
	return *this;
}

//---------------------------------------------------------------------
hamString& hamString::operator += (const hamString& input) {
	size_t tempSize = Size + input.Size;
	char* temp = new char[tempSize+1]; //need room for NULL termination
	
	register size_t i = 0;
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	
	for (register size_t j = 0; j < input.Size; ++i, ++j) {
		temp[i] = input.array[j];
	}
	delete [] array;
	array = temp;
	Size = tempSize;
	return *this;
}
hamString& hamString::operator += (const char* str) {
	size_t strLen = getStrLen(str);
	size_t tempSize = Size + strLen;
	char* temp = new char[tempSize+1]; //need room for NULL termination
	
	register size_t i = 0;
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	
	for (register size_t j = 0; j < strLen; ++i, ++j) {
		temp[i] = str[j];
	}
	delete [] array;
	array = temp;
	Size = tempSize;
	return *this;
}
hamString& hamString::operator += (char c) {
	char* temp = new char[Size+2]; //need room for NULL termination & 'c'
	
	register size_t i = 0;
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
hamString hamString::operator + (const hamString& str) const {
	hamString temp(*this);
	temp.push(Size, str.array, str.Size);
	return temp;
}
hamString hamString::operator + (const char* str) const {
	hamString temp(*this);
	temp.operator+=(str);
	return temp;
}
hamString hamString::operator + (char c) const {
	hamString temp(*this);
	temp.operator+=(c);
	return temp;
}

//---------------------------------------------------------------------
bool hamString::operator == (const hamString& compare) const {
	if (compare.Size != Size ) return false;
	return cmpStr(array, 0, compare.array, Size);
}
bool hamString::operator == (const char* compare) const {
	size_t strLen = getStrLen(compare);
	if (strLen != Size ) return false;
	return cmpStr(array, 0, compare, Size);
}
bool hamString::operator == (char compare) const {
	if (Size != 1) return false;
	return array[0] == compare;
}

//---------------------------------------------------------------------
bool hamString::operator != (const hamString& compare) const {
	if (compare.Size != Size ) return true;
	return !cmpStr(array, 0, compare.array, Size);
}
bool hamString::operator != (const char* compare) const {
	size_t strLen = getStrLen(compare);
	if (strLen != Size ) return true;
	return !cmpStr(array, 0, compare, Size);
}
bool hamString::operator != (char compare) const {
	if (Size != 1) return true;
	return array[0] != compare;
}

//---------------------------------------------------------------------
char& hamString::operator [](int i) {
	HL_ASSERT(i < Size);
	return array[i];
}

char hamString::operator [](int i) const {
	HL_ASSERT(i < Size);
	return array[i];
}

//---------------------------------------------------------------------
//				Deletion
//---------------------------------------------------------------------
void hamString::clear () {
	delete [] array;
	array = new char[1];
	Size = 0;
	array[0] = 0;
}

void hamString::popFront() {
	if (!Size) return;
	register size_t i = 0;
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
void hamString::popBack() {
	if (!Size) return;
	register size_t i = 0;
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

void hamString::pop(size_t index) {
	if (Size == 0) return;
	assert(index < Size);
	--Size;
	register size_t i = 0;
	register size_t j = 0;
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
void hamString::push(size_t index, const char* data, size_t strSize) {
	if (index > Size) index = Size;
	size_t tempSize = Size + strSize;
	char* temp = new char[tempSize+1];
	
	size_t iter = 0;
	size_t strPos = 0;
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

void hamString::pushAfter(size_t index, const char* data, size_t strSize) {
	this->push(++index, data, strSize);
}

//hamStrings
void hamString::push(size_t index, const hamString& str) {
	this->push(index, str.array, str.Size);
}
void hamString::pushAfter(size_t index, const hamString& str) {
	this->push(++index, str.array, str.Size);
}

//char strings with unknown length
void hamString::push(size_t index, const char* str) {
	size_t strSize = getStrLen(str);
	this->push(index, str, strSize);
}
void hamString::pushAfter(size_t index, const char* str) {
	size_t strSize = getStrLen(str);
	this->push(++index, str, strSize);
}

//individual characters
void hamString::push(size_t index, char c) {
	this->push(index, &c, 1);
}
void hamString::pushAfter(size_t index, char c) {
	this->push(++index, &c, 1);
}

//---------------------------------------------------------------------
//				Direct Insertion
//---------------------------------------------------------------------
void hamString::pushFront (const char* str, size_t strSize) {
	this->push(0, str, strSize);
}

void hamString::pushBack (const char* str, size_t strSize) {
	this->push(Size, str, strSize);
}

void hamString::pushFront (const hamString& str) {
	this->push(0, str.array, str.Size);
}

void hamString::pushBack (const hamString& str) {
	this->push(Size, str.array, str.Size);
}

void hamString::pushFront (const char* str) {
	size_t strSize = getStrLen(str);
	this->push(0, str, strSize);
}

void hamString::pushBack (const char* str) {
	size_t strSize = getStrLen(str);
	this->push(Size, str, strSize);
}

void hamString::pushFront (char c) {
	const char str[1] = {c};
	this->push(0, str, 1);
}

void hamString::pushBack (char c) {
	const char str[1] = {c};
	this->push(Size, str, 1);
}


//---------------------------------------------------------------------
//				Traversal
//---------------------------------------------------------------------
char& hamString::front() {
	return array[0];
}

char& hamString::back() {
	return array[Size-1];
}

//---------------------------------------------------------------------
//				Searching
//---------------------------------------------------------------------
long int hamString::find(const char* str, size_t strLen) const {
	if (!strLen || !Size) return nPos;
	size_t currPos = 0;
	size_t limit = 0 + strLen;
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

long int hamString::find(const hamString& str) const {
	return this->find(str.array, Size);
}

long int hamString::find(const char* str) const {
	size_t strLength = getStrLen(str);
	return this->find(str, strLength);
}

long int hamString::find(char c) const {
	const char str[1] = {c};
	return this->find(str, 1);
}

//---------------------------------------------------------------------
long int hamString::rFind(const char* str, size_t strLen) const {
	if (!strLen || !Size) return nPos;
	size_t offset = Size-1;
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

long int hamString::rFind(const hamString& str) const {
	return this->rFind(str.array, Size);
}

long int hamString::rFind(const char* str) const {
	size_t strLength = getStrLen(str);
	return this->rFind(str, strLength);
}

long int hamString::rFind(char c) const {
	const char str[1] = {c};
	return this->rFind(str, 1);
}

//---------------------------------------------------------------------
//				Utility Functions
//---------------------------------------------------------------------
void hamString::copy (const hamString& str) {
	this->operator=(str);
}
void hamString::copy (const char* str) {
	this->operator=(str);
}
void hamString::copy (char c) {
	this->operator=(c);
}

//---------------------------------------------------------------------
void hamString::append (const hamString& str) {
	this->push(Size, str.array, str.Size);
}

void hamString::append (const char* str, size_t strLength) {
	this->push(Size, str, strLength);
}

void hamString::append (const char* str) {
	size_t strSize = getStrLen(str);
	this->push(Size, str, strSize);
}

void hamString::append (char c) {
	const char str[1] = {c};
	this->push(Size, str, 1);
}

//---------------------------------------------------------------------
void hamString::resize (size_t newSize, char c) {
	if (newSize == Size) return;
	char* temp = new char[newSize+1];
	
	for (register size_t i = 0; i < newSize; ++i) {
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

void hamString::resize(size_t newSize) {
	this->resize(newSize, '\0');
}

//---------------------------------------------------------------------
//				Miscellaneous
//---------------------------------------------------------------------
hamString hamString::subStr(size_t pos, size_t length) const {
	hamString temp;
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

bool hamString::empty () const {
	return (Size) ? false : true;
}

size_t hamString::size () const {
	return Size;
}

void hamString::swap (hamString& input) {
	char* temp = input.array;
	input.array = array;
	array = temp;
}

const char* hamString::cStr () const {
	return array;
}

} //end hamLibs namespace
