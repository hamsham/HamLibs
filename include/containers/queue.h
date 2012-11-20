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
			type data;
			node *next = HL_NULL;
		};
		node	*first = NULL;		//List navigation
		node	*last = NULL;
		size_t	numNodes;
		
		
	public:
		queue 	();
		~queue 	();

		//data acquisition
		type*	front	() const;
		type*	peekNext	() const;
		type*	back		() const;

		//insertion & deletion
		void		push		(const type& object);
		void		pop		();
		void		clear	();

		//miscellaneous
		size_t	size		() const;
		bool		empty	() const;
};

//-----------------------------------------------------------------------------
//			Construction & Destruction
//-----------------------------------------------------------------------------
template <class type> HL_INLINE
queue<type>::queue() :
	first( HL_NULL ),
	last( HL_NULL ),
	numNodes( 0 )
{}

template <class type> HL_INLINE
queue<type>::~queue() {
	clear();
}

//-----------------------------------------------------------------------------
//			Data Acquisition
//-----------------------------------------------------------------------------
template <class type>
type* queue<type>::front() const {
	return (first) ? (&first->data) : HL_NULL;
}

template <class type>
type* queue<type>::peekNext() const {
	if (first && first->next)
		return &(first->next->data);
	return HL_NULL;
}

template <class type>
type* queue<type>::back() const {
	return (last) ? &(last->data) : HL_NULL;
}

//-----------------------------------------------------------------------------
//			Insertion
//-----------------------------------------------------------------------------
template <class type>
void queue<type>::push(const type& object) {
	node* temp = new node;
	temp->data = object;
	temp->next = first;
	first = temp;
	++numNodes;
	
	if (numNodes == 1)
		last = first;
}

//-----------------------------------------------------------------------------
//			Deletion
//-----------------------------------------------------------------------------
template <class type>
void queue<type>::pop() {
	if (first == HL_NULL)
		return;
	
	node* temp( first->next );
	delete first;
	--numNodes;
	
	first = temp;	
	if (first == HL_NULL)
		last = HL_NULL;
}

template <class type>
void queue<type>::clear() {
	while (first != HL_NULL) {
		pop();
	}
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
	return (first == HL_NULL) ? true : false;
}

} //end containers namespace
} //end hamlibs namespace
#endif //__HL_QUEUE__
