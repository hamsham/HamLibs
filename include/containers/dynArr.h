
#ifndef __DYNAMIC_ARRAY__
#define __DYNAMIC_ARRAY__
namespace hamLibs {
namespace containers {

template <typename type>
class dynArray {
	private:
		type* array;
		size_t Size;

	public:
		dynArray				();
		dynArray				(size_t numItems);
		dynArray				(const type& data);
		dynArray				(const type& data, size_t numCopies);
		dynArray				(const dynArray& copy);
		~dynArray				();

		//operators
		dynArray&	operator =	(const dynArray& input);
		dynArray&	operator +=	(const dynArray& input);
		dynArray	operator +	(const dynArray& input) const;
		bool		operator ==	(const dynArray& compare) const;
		bool		operator !=	(const dynArray& compare) const;
		type&		operator []	(size_t);
		type		operator []	(size_t) const;

		//deletion
		void		popFront	();
		void		popBack		();
		void		pop			(size_t index);

		//insertion
		void		pushFront	(const type& data);
		void		pushBack	(const type& data);
		void		push		(size_t index, const type& data);
		void		pushAfter	(size_t index, const type& data);

		//traversal
		type&		front		();
		type&		back		();

		//miscellaneous
		static void	copy		(dynArray& dest, const dynArray& source);
		static void	append		(dynArray& dest, const dynArray& source);
		void		resize		(size_t newSize);
		void		clear		();
		bool		empty		() const;
		size_t		size		() const;
		type*		data		() const;
};

//---------------------------------------------------------------------
//			[Con/De]struction
//---------------------------------------------------------------------
template <typename type>
dynArray<type>::dynArray() {
	Size = 0;
	array = new type[0];
}

template <typename type>
dynArray<type>::dynArray(size_t numItems) {
	Size = numItems;
	array = new type[numItems];
}

template <typename type>
dynArray<type>::dynArray(const dynArray& copy) {
	array = new type [copy.Size];
	Size = 0;
	while (Size != copy.Size) {
		array[Size] = copy.array[Size];
		++Size;
	}
}

template <typename type>
dynArray<type>::dynArray(const type& data) {
	array = new type[1];
	array[0] = data;
	Size = 1;
}

template <typename type>
dynArray<type>::dynArray(const type& data, size_t numCopies) {
	array = new type[numCopies];
	Size = 0;
	while (Size < numCopies) {
		array[Size] = data;
		++Size;
	}
}

template <typename type>
dynArray<type>::~dynArray() {
	delete [] array;
}

//---------------------------------------------------------------------
//			Operators
//---------------------------------------------------------------------
template <typename type>
dynArray<type>& dynArray<type>::operator = (const dynArray& input) {
	copy(*this, input);
	return *this;
}

template <typename type>
dynArray<type>& dynArray<type>::operator += (const dynArray& input) {
	append(*this, input);
	return *this;
}

template <typename type>
dynArray<type> dynArray<type>::operator + (const dynArray& input) const {
	dynArray<type> temp(*this);
	append(temp, input);
	return temp;
}

template <typename type>
bool dynArray<type>::operator == (const dynArray& compare) const {
	if (Size != compare.Size) return false;
	size_t iter = 0;
	while (iter < Size) {
		if (array[iter] != compare.array[iter])
			return false;
		++iter;
	}
	return true;
}

template <typename type>
bool dynArray<type>::operator != (const dynArray& compare) const {
	if (Size != compare.Size) return true;
	size_t iter = 0;
	while (iter < Size) {
		if (array[iter] != compare.array[iter])
			return true;
		++iter;
	}
	return false;
}

template <typename type>
type& dynArray<type>::operator [] (size_t index) {
	//assert(index >= 0);
	return array[index];
}

template <typename type>
type dynArray<type>::operator [] (size_t index) const {
	//assert(index >= 0);
	return array[index];
}

//---------------------------------------------------------------------
//			Deletion
//---------------------------------------------------------------------
template <typename type>
void dynArray<type>::popFront() {
	if (!Size) return;
	size_t i = 0;
	--Size;
	type* temp = new type[Size];
	while (i < Size) {
		temp[i] = array[i+1];
		++i;
	}
	delete [] array;
	array = temp;
}

template <typename type>
void dynArray<type>::popBack() {
	if (!Size) return;
	--Size;
	size_t i = 0;
	type* temp = new type[Size];
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	delete [] array;
	array = temp;
}

template <typename type>
void dynArray<type>::pop(size_t index) {
	if (Size == 0 || index >= Size) return;
	
	--Size;
	size_t i = 0;
	size_t j = 0;
	type* temp = new type[Size];
	while (i < Size) {
		temp[i] = (i != index) ? array[j] : array[++j];
		++i; ++j;
	}
	delete [] array;
	array = temp;
}

//---------------------------------------------------------------------
//			Insertion
//---------------------------------------------------------------------
template <typename type>
void dynArray<type>::pushFront(const type& data) {
	++Size;
	type* temp = new type[Size];
	temp[0] = data;
	size_t i = 1;
	while (i < Size) {
		temp[i] = array[i-1];
		++i;
	}
	delete [] array;
	array = temp;
}

template <typename type>
void dynArray<type>::pushBack(const type& data) {
	type* temp = new type[Size+1];
	size_t i = 0;
	while (i < Size) {
		temp[i] = array[i];
		++i;
	}
	temp[Size] = data;
	++Size;
	delete [] array;
	array = temp;
}

template <typename type>
void dynArray<type>:: push(size_t index, const type& data) {
	//Resize if trying to access an out-of-bounds element
	if (index >= Size) {
		pushBack(data);
		return;
	}
	
	++Size;
	size_t i = 0;
	size_t j = 0;
	type* temp = new type[Size];
	
	while (i < Size) {
		if (i != index) {
			temp[i] = array[j];
			++j;
		}
		else {
			temp[i] = data;
		}
		++i;
	}
	delete [] array;
	array = temp;
}

template <typename type>
void dynArray<type>::pushAfter(size_t index, const type& data) {
	push(++index, data);
}

//---------------------------------------------------------------------
//			Traversal
//---------------------------------------------------------------------
template <typename type>
type& dynArray<type>::front() {
	return array[0];
}

template <typename type>
type& dynArray<type>::back() {
	return array[Size-1];
}

//---------------------------------------------------------------------
//			Misc
//---------------------------------------------------------------------
template <typename type>
void dynArray<type>::copy(dynArray& dest, const dynArray& source) {
	delete [] dest.array;
	dest.array = new type[source.Size];
	
	size_t iter = dest.Size = source.Size;
	while (iter--) {
		dest.array[iter] = source.array[iter];
	}
}

template <typename type>
void dynArray<type>::append(dynArray& dest, const dynArray& source) {
	size_t firstHalf= 0;
	size_t secondHalf = source.Size;
	size_t newSize = dest.Size + source.Size;
	type* temp = new type[newSize];
	
	while (firstHalf < dest.Size) {
		temp[firstHalf] = dest.array[firstHalf];
		++firstHalf;
	}
	firstHalf = 0;
	while (secondHalf < newSize) {
		temp[secondHalf] = source.array[firstHalf];
		++firstHalf;
		++secondHalf;
	}
	delete [] dest.array;
	dest.array = temp;
	dest.Size = newSize;
}

template <typename type>
void dynArray<type>::resize(size_t newSize) {
	//this function may leave uninitialized variables if newSize > Size
	if (newSize == Size) return;
	else if (!newSize) {
		clear();
		return;
	}
	
	type* temp = new type[newSize];
	size_t iter = (newSize > Size) ? Size : newSize;
	while (iter--) { //insures only preexisting variables are copied
		temp[iter] = array[iter];
	}
	delete [] array;
	array = temp;
	Size = newSize;
}

template <typename type>
void dynArray<type>::clear() {
	delete [] array;
	array = new type[0];
	Size = 0;
}

template <typename type>
bool dynArray<type>::empty() const {
	return (Size) ? false : true;
}

template <typename type>
size_t dynArray<type>::size() const {
	return Size;
}

template <typename type>
type* dynArray<type>::data() const {
	return array;
}

} //end containers namespace
} //end hamLibs namespace
#endif //__DYNAMIC_ARRAY__
