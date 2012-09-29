/*
 * stack class
*/

#ifndef __HL_QUEUE__
#define __HL_QUEUE__
namespace hamLibs {
namespace containers {

template <class type>
class queue {
	private:
		struct node {
			type *data;
			node *next, *prev;
		};
		node	*first;		//List navigation
		node	*last;
		size_t	numNodes;
		
		
	public:
		queue 	();
		~queue 	();

		//data acquisition
		type*	front		() const;
		type*	peekNext	() const;
		type*	back		() const;

		//insertion & deletion
		void	push		(const type& object);
		void	pop			();
		void	clear		();

		//miscellaneous
		size_t	size		() const;
		bool	empty		() const;
};

//-----------------------------------------------------------------------------
//			Construction & Destruction
//-----------------------------------------------------------------------------
template <class type>
queue<type>::queue() {
	first = new node;
	first->data = HL_NULL;
	first->next = HL_NULL;
	last = first;
	numNodes = 0;
}

template <class type>
queue<type>::~queue() {
	clear();
}

//-----------------------------------------------------------------------------
//			Data Acquisition
//-----------------------------------------------------------------------------
template <class type>
type* queue<type>::front() const {
	return first->data;
}

template <class type>
type* queue<type>::peekNext() const {
	return (first->next) ? first->next->data : NULL;
}

template <class type>
type* queue<type>::back() const {
	return last->data;
}

//-----------------------------------------------------------------------------
//			Insertion
//-----------------------------------------------------------------------------
template <class type>
void queue<type>::push(const type& object) {
	*last->data = object;
	last->next = new node;
	last = last->next;
	last->data = HL_NULL;
	last->next = HL_NULL;
	++numNodes;
}

//-----------------------------------------------------------------------------
//			Deletion
//-----------------------------------------------------------------------------
template <class type>
void queue<type>::pop() {
	if (first->data) {
		node* temp = first;
		first = first->next;
		delete temp;
		--numNodes;
	}
}

template <class type>
void queue<type>::clear() {
	do {
		pop();
	} while (last != first);
}

//-----------------------------------------------------------------------------
//			Miscellaneous
//-----------------------------------------------------------------------------
template <class type>
size_t queue<type>::size() const {
	return numNodes;
}

template <class type>
bool queue<type>::empty() const {
	return (first->data) ? false : true;
}

} //end containers namespace
} //end hamlibs namespace
#endif //__HL_QUEUE__
