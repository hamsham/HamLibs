/*
 * stack class
*/

#ifndef __HL_QUEUE__
#define __HL_QUEUE__

#include "../defs/preprocessor.h"
#include "../defs/types.h"

namespace hamLibs {
namespace containers {

template <typename type>
class queue {
	private:
		struct node {
			type data;
			node *next = HL_NULL;
		};
		node		*first = HL_NULL;		//List navigation
		node		*last = HL_NULL;
		hlSize_t	numNodes;
		
		
	public:
		queue		();
		~queue		();

		//data acquisition
		type*		front		() const;
		type*		peekNext	() const;
		type*		back		() const;

		//insertion & deletion
		void		push		(const type& object);
		void		pop			();
		void		clear		();

		//miscellaneous
		hlSize_t	size		() const;
		bool		empty		() const;
};

//-----------------------------------------------------------------------------
//			Construction & Destruction
//-----------------------------------------------------------------------------
template <typename type> HL_INLINE
queue<type>::queue() :
	first( HL_NULL ),
	last( HL_NULL ),
	numNodes( 0 )
{}

template <typename type> HL_INLINE
queue<type>::~queue() {
	clear();
}

//-----------------------------------------------------------------------------
//			Data Acquisition
//-----------------------------------------------------------------------------
template <typename type>
type* queue<type>::front() const {
	return (first) ? (&first->data) : HL_NULL;
}

template <typename type>
type* queue<type>::peekNext() const {
	if (first && first->next)
		return &(first->next->data);
	return HL_NULL;
}

template <typename type>
type* queue<type>::back() const {
	return (last) ? &(last->data) : HL_NULL;
}

//-----------------------------------------------------------------------------
//			Insertion
//-----------------------------------------------------------------------------
template <typename type>
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
template <typename type>
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

template <typename type>
void queue<type>::clear() {
	while (first != HL_NULL) {
		pop();
	}
}

//-----------------------------------------------------------------------------
//			Miscellaneous
//-----------------------------------------------------------------------------
template <typename type>
hlSize_t queue<type>::size() const {
	return numNodes;
}

template <typename type>
bool queue<type>::empty() const {
	return (first == HL_NULL) ? true : false;
}

} //end containers namespace
} //end hamlibs namespace
#endif //__HL_QUEUE__
