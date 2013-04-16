/*
 * stack class
*/

#ifndef __HL_STACK__
#define __HL_STACK__

#include "../defs/preprocessor.h"
#include "../defs/types.h"

namespace hamLibs {
namespace containers {

template <typename type>
class stack {
	private:
		struct node {
			type *data;
			node *next;
		};
		
		node *iter;		//List navigation
		hlSize_t numNodes;
		static const node bottom;
		
	public:
		stack		();
		~stack		();

		//data acquisition
		type*		top			() const;
		type*		peekNext	() const;

		//insertion & deletion
		void		push		(const type& ptr);
		void		pop			();
		void		clear		();

		//miscellaneous
		hlSize_t	size		() const;
		bool		empty		() const;
};

//-----------------------------------------------------------------------------
//			Construction & Destruction
//-----------------------------------------------------------------------------
template <typename type>
const typename stack<type>::node stack<type>::bottom = {HL_NULL, HL_NULL};

template <typename type>
stack<type>::stack() {
	iter = const_cast<type*>(&bottom);
	numNodes = 0;
}

template <typename type>
stack<type>::~stack() {
	clear();
}

//-----------------------------------------------------------------------------
//			Data Acquisition
//-----------------------------------------------------------------------------
template <typename type>
type* stack<type>::top() const {
	return iter->data;
}

template <typename type>
type* stack<type>::peekNext() const {
	return (iter->next) ? iter->next->data : HL_NULL;
}

//-----------------------------------------------------------------------------
//			Insertion
//-----------------------------------------------------------------------------
template <typename type>
void stack<type>::push(const type& object) {
	node* temp = new node;
	*temp->data = object;
	
	temp->next = iter;
	iter = temp;
	
	++numNodes;
}

//-----------------------------------------------------------------------------
//			Deletion
//-----------------------------------------------------------------------------
template <typename type>
void stack<type>::pop() {
	if (iter != &bottom) {
		const node* temp = iter;
		iter = iter->next;
		delete temp;
		--numNodes;
	}
}

template <typename type>
void stack<type>::clear() {
	while (iter->data != HL_NULL) {
		pop();
	}
}

//-----------------------------------------------------------------------------
//			Miscellaneous
//-----------------------------------------------------------------------------
template <typename type>
hlSize_t stack<type>::size() const {
	return numNodes;
}

template <typename type>
bool stack<type>::empty() const {
	return iter == &bottom;
}

} //end containers namespace
} //end hamLibs namespace
#endif //__HL_STACK__
