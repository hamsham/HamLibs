/*
 * stack class
*/

#ifndef __HL_STACK__
#define __HL_STACK__
namespace hamLibs {
namespace containers {

//readability problems start... here
namespace {
	//this is the glue which binds the stack class together
} //end anonymous namespace


template <class type>
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
template <class type>
const typename stack<type>::node stack<type>::bottom = {HL_NULL, HL_NULL};

template <class type>
stack<type>::stack() {
	iter = const_cast<type*>(&bottom);
	numNodes = 0;
}

template <class type>
stack<type>::~stack() {
	clear();
}

//-----------------------------------------------------------------------------
//			Data Acquisition
//-----------------------------------------------------------------------------
template <class type>
type* stack<type>::top() const {
	return iter->data;
}

template <class type>
type* stack<type>::peekNext() const {
	return (iter->next) ? iter->next->data : HL_NULL;
}

//-----------------------------------------------------------------------------
//			Insertion
//-----------------------------------------------------------------------------
template <class type>
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
template <class type>
void stack<type>::pop() {
	if (iter != &bottom) {
		node* temp = iter;
		iter = iter->next;
		delete temp;
		--numNodes;
	}
}

template <class type>
void stack<type>::clear() {
	while (iter->data != HL_NULL) {
		pop();
	}
}

//-----------------------------------------------------------------------------
//			Miscellaneous
//-----------------------------------------------------------------------------
template <class type>
hlSize_t stack<type>::size() const {
	return numNodes;
}

template <class type>
bool stack<type>::empty() const {
	return (iter == &bottom) ? true : false;
}

} //end containers namespace
} //end hamLibs namespace
#endif //__HL_STACK__
