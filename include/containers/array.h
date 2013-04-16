
/*
 * Just a very simple dynamic array implementation. No bells or whistles.
 * Do not expect this to have anywhere near the same performance as std::vector
 */

#ifndef __HL_DYNAMIC_ARRAY_H__
#define __HL_DYNAMIC_ARRAY_H__

#include "../defs/preprocessor.h"
#include "../defs/types.h"

namespace hamLibs {
namespace containers {

template <typename type>
class array {
	private:
		type* Array;
		hlSize_t Size;

	public:
		array				();
		array				(hlSize_t numItems);
		array				(const type& data);
		array				(const type& data, hlSize_t numCopies);
		array				(const array& copy);
		~array				();

		//operators
		array&	operator =	(const array& input);
		array&	operator +=	(const array& input);
		array	operator +	(const array& input) const;
		bool		operator ==	(const array& compare) const;
		bool		operator !=	(const array& compare) const;
		type&		operator []	(hlSize_t);
		type		operator []	(hlSize_t) const;

		//deletion
		void		popFront	();
		void		popBack		();
		void		pop			(hlSize_t index);

		//insertion
		void		pushFront	(const type& data);
		void		pushBack	(const type& data);
		void		push		(hlSize_t index, const type& data);
		void		pushAfter	(hlSize_t index, const type& data);

		//traversal
		type&		front		();
		type&		back		();

		//miscellaneous
		static void	copy		(array& dest, const array& source);
		static void	append		(array& dest, const array& source);
		void		resize		(hlSize_t newSize);
		void		clear		();
		bool		empty		() const;
		hlSize_t	size		() const;
		type*		data		() const;
};

//---------------------------------------------------------------------
//			[Con/De]struction
//---------------------------------------------------------------------
template <typename type>
array<type>::array() {
	Size = 0;
	Array = new type[0];
}

template <typename type>
array<type>::array(hlSize_t numItems) {
	Size = numItems;
	Array = new type[numItems];
}

template <typename type>
array<type>::array(const array& copy) {
	Array = new type [copy.Size];
	Size = 0;
	while (Size != copy.Size) {
		Array[Size] = copy.Array[Size];
		++Size;
	}
}

template <typename type>
array<type>::array(const type& data) {
	Array = new type[1];
	Array[0] = data;
	Size = 1;
}

template <typename type>
array<type>::array(const type& data, hlSize_t numCopies) {
	Array = new type[numCopies];
	Size = 0;
	while (Size < numCopies) {
		Array[Size] = data;
		++Size;
	}
}

template <typename type>
array<type>::~array() {
	delete [] Array;
}

//---------------------------------------------------------------------
//			Operators
//---------------------------------------------------------------------
template <typename type>
array<type>& array<type>::operator = (const array& input) {
	copy(*this, input);
	return *this;
}

template <typename type>
array<type>& array<type>::operator += (const array& input) {
	append(*this, input);
	return *this;
}

template <typename type>
array<type> array<type>::operator + (const array& input) const {
	array<type> temp(*this);
	append(temp, input);
	return temp;
}

template <typename type>
bool array<type>::operator == (const array& compare) const {
	if (Size != compare.Size) return false;
	hlSize_t iter = 0;
	while (iter < Size) {
		if (Array[iter] != compare.Array[iter])
			return false;
		++iter;
	}
	return true;
}

template <typename type>
bool array<type>::operator != (const array& compare) const {
	if (Size != compare.Size) return true;
	hlSize_t iter = 0;
	while (iter < Size) {
		if (Array[iter] != compare.Array[iter])
			return true;
		++iter;
	}
	return false;
}

template <typename type>
type& array<type>::operator [] (hlSize_t index) {
	HL_ASSERT(index >= 0);
	return Array[index];
}

template <typename type>
type array<type>::operator [] (hlSize_t index) const {
	HL_ASSERT(index >= 0);
	return Array[index];
}

//---------------------------------------------------------------------
//			Deletion
//---------------------------------------------------------------------
template <typename type>
void array<type>::popFront() {
	if (!Size) return;
	hlSize_t i = 0;
	--Size;
	type* temp = new type[Size];
	while (i < Size) {
		temp[i] = Array[i+1];
		++i;
	}
	delete [] Array;
	Array = temp;
}

template <typename type>
void array<type>::popBack() {
	if (!Size) return;
	--Size;
	hlSize_t i = 0;
	type* temp = new type[Size];
	while (i < Size) {
		temp[i] = Array[i];
		++i;
	}
	delete [] Array;
	Array = temp;
}

template <typename type>
void array<type>::pop(hlSize_t index) {
	if (Size == 0 || index >= Size) return;
	
	--Size;
	hlSize_t i = 0;
	hlSize_t j = 0;
	type* temp = new type[Size];
	while (i < Size) {
		temp[i] = (i != index) ? Array[j] : Array[++j];
		++i; ++j;
	}
	delete [] Array;
	Array = temp;
}

//---------------------------------------------------------------------
//			Insertion
//---------------------------------------------------------------------
template <typename type>
void array<type>::pushFront(const type& data) {
	++Size;
	type* temp = new type[Size];
	temp[0] = data;
	hlSize_t i = 1;
	while (i < Size) {
		temp[i] = Array[i-1];
		++i;
	}
	delete [] Array;
	Array = temp;
}

template <typename type>
void array<type>::pushBack(const type& data) {
	type* temp = new type[Size+1];
	hlSize_t i = 0;
	while (i < Size) {
		temp[i] = Array[i];
		++i;
	}
	temp[Size] = data;
	++Size;
	delete [] Array;
	Array = temp;
}

template <typename type>
void array<type>:: push(hlSize_t index, const type& data) {
	//Resize if trying to access an out-of-bounds element
	if (index >= Size) {
		pushBack(data);
		return;
	}
	
	++Size;
	hlSize_t i = 0;
	hlSize_t j = 0;
	type* temp = new type[Size];
	
	while (i < Size) {
		if (i != index) {
			temp[i] = Array[j];
			++j;
		}
		else {
			temp[i] = data;
		}
		++i;
	}
	delete [] Array;
	Array = temp;
}

template <typename type>
void array<type>::pushAfter(hlSize_t index, const type& data) {
	push(++index, data);
}

//---------------------------------------------------------------------
//			Traversal
//---------------------------------------------------------------------
template <typename type>
type& array<type>::front() {
	return Array[0];
}

template <typename type>
type& array<type>::back() {
	return Array[Size-1];
}

//---------------------------------------------------------------------
//			Misc
//---------------------------------------------------------------------
template <typename type>
void array<type>::copy(array& dest, const array& source) {
	delete [] dest.Array;
	dest.Array = new type[source.Size];
	
	hlSize_t iter = dest.Size = source.Size;
	while (iter--) {
		dest.Array[iter] = source.Array[iter];
	}
}

template <typename type>
void array<type>::append(array& dest, const array& source) {
	hlSize_t firstHalf= 0;
	hlSize_t secondHalf = source.Size;
	hlSize_t newSize = dest.Size + source.Size;
	type* temp = new type[newSize];
	
	while (firstHalf < dest.Size) {
		temp[firstHalf] = dest.Array[firstHalf];
		++firstHalf;
	}
	firstHalf = 0;
	while (secondHalf < newSize) {
		temp[secondHalf] = source.Array[firstHalf];
		++firstHalf;
		++secondHalf;
	}
	delete [] dest.Array;
	dest.Array = temp;
	dest.Size = newSize;
}

template <typename type>
void array<type>::resize(hlSize_t newSize) {
	//this function may leave uninitialized variables if newSize > Size
	if (newSize == Size) return;
	else if (!newSize) {
		clear();
		return;
	}
	
	type* temp = new type[newSize];
	hlSize_t iter = (newSize > Size) ? Size : newSize;
	while (iter--) { //insures only preexisting variables are copied
		temp[iter] = Array[iter];
	}
	delete [] Array;
	Array = temp;
	Size = newSize;
}

template <typename type>
void array<type>::clear() {
	delete [] Array;
	Array = new type[0];
	Size = 0;
}

template <typename type>
bool array<type>::empty() const {
	return (Size) ? false : true;
}

template <typename type>
hlSize_t array<type>::size() const {
	return Size;
}

template <typename type>
type* array<type>::data() const {
	return Array;
}

} //end containers namespace
} //end hamLibs namespace

#endif //__HL_DYNAMIC_ARRAY_H__
