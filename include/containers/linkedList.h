/*
 * linked list class
 * --------------------------------------------------------------------
 * 
 * I really feel like shit for writing this code the way I did, but I did it to
 * make the implementation as easy and efficient as I know how.
 * 
 * The linked list is actually implemented as a "looped" list.
 * This means that the start and endpoints of the list are linked together.
 * In order to avoid problems with this kind of implementation, and to ease in
 * node navigation, I inserted a spacer in between the first and last nodes.
 * This was unfortunately necessary, but actually turned into a happy accident.
 * --------------------------------------------------------------------
 * 
 * NOTES:
 * The head node is a pointer which navigates through the list.
 * After any insertion, the head node will point to the node which was inserted.
 * After any deletion, the head pointer will point to the next element in the
 * list. If the item deleted is the last node in the list, then the head node
 * will point to the next-to-last node (which becomes the last node).
 * Popping a node off the list WILL NOT free the data that the node points to.
 * I decided to leave it up to the users implementation to determine how the
 * data in a node is deleted.
*/

#ifndef __HL_LINKEDLIST__
#define __HL_LINKEDLIST__
namespace hamLibs {
namespace containers {

template <class type>
class linkedList {
	private:
		struct node {
			type	data;
			node	*next;
			node	*prev;
			node();
		};
		
		node		mainNode;	//mainNode serves as the list's beginning and end
		node		*iter;		//List navigation pointer
		hlSize_t	numNodes;
		
	public:
		linkedList	();
		linkedList	(const linkedList& listCopy);
		~linkedList	();
		linkedList&	operator=	(const linkedList& listCopy);

		//link navigation
		void		goToFront	();			//immediately move "iter" to the front of the list
		void		goToBack	();			//immediately move "iter" to the end of the list
		void		goToNext	();			//move iter to the next node in the list if it's not at the end
		void		goToPrev	();			//move iter to the previous node in the list if it's not at the beginning

		//data acquisition
		type*		getFirst	() const;		//get the first item. returns HL_NULL if no objects exist within the list. Does not move the iterator
		type*		getLast		() const;		//get the last item. returns HL_NULL if no objects exist within the list. Does not move the iterator.
		type*		getCurrent	() const;		//get currently selected item. returns HL_NULL if no objects exist within the list
		type*		getNext		() const;		//increment selection ("iter") pointer, return its data (returns HL_NULL if at the end of the list)
		type*		getPrev		() const;		//decrement selection ("iter") pointer, return its data (returns HL_NULL if at the end of the list)
		type*		peekNext	() const;		//get the next item in the list without incrementing the "iter" pointer
		type*		peekPrev	() const;

		//insertion
		void		pushFront	(const type& object);	//add an element to the front of the list
		void		pushBack	(const type& object);	//add an element to the end of the list
		void		pushBefore	(const type& object);	//add an element in front of the "iter" pointer; move the iter pointer to the new node
		void		pushAfter	(const type& object);	//add an element behind the "iter" pointer, move the iter pointer to the new node

		//deletion
		void		popnode		();				//delete the node pointer to by "iter", move to the next node
		void		popFront	();				//delete the front node; move "iter" to the following node
		void		popBack		();				//delete the node pointed to by "iter". move to the next node. (will move to the previous node if at the end of the list)
		void		clear		();				//delete all elements in the list

		//miscellaneous
		hlSize_t	size		() const;
		bool		empty		() const;		//check if the list is empty
};

//-----------------------------------------------------------------------------
//			Construction & Destruction
//-----------------------------------------------------------------------------
template <class type>
linkedList<type>::node::node() :
	data(),
	next(HL_NULL),
	prev(HL_NULL)
{}

template <class type>
linkedList<type>::linkedList() :
	mainNode(),
	iter(&mainNode),
	numNodes(0)
{
	iter->next = iter;
	iter->prev = iter;
}

template <class type>
linkedList<type>::linkedList(const linkedList& listCopy) {
	*this = listCopy;
}

template <class type>
linkedList<type>::~linkedList() {
	clear();
}

template <class type>
linkedList<type>& linkedList<type>::operator =(const linkedList& listCopy) {
	const node* iterPos = iter; //preserve the iteration position
	hlSize_t iterating(size);
	
	listCopy.clear();
	this->goToFront();
	while (iterating--) {
		listCopy.pushBack( this->getCurrent() );
		this->goToNext();
	}
	iter = iterPos; //restore the iteration position
}

//-----------------------------------------------------------------------------
//			Link Navigation
//-----------------------------------------------------------------------------
template <class type>
void linkedList<type>::goToFront() {
	iter = mainNode.next;
}

template <class type>
void linkedList<type>::goToBack() {
	iter = mainNode.prev;
}

template <class type>
void linkedList<type>::goToNext() {
	if (iter->next != &mainNode) {
		iter = iter->next;
	}
}

template <class type>
void linkedList<type>::goToPrev() {
	if (iter->prev != &mainNode) {
		iter = iter->prev;
	}
}

//-----------------------------------------------------------------------------
//			Data Acquisition
//-----------------------------------------------------------------------------
template <class type>
type* linkedList<type>::getFirst() const {
	return &(mainNode.next->data);
}
template <class type>
type* linkedList<type>::getLast() const {
	return &(mainNode.prev->data);
}
template <class type>
type* linkedList<type>::getCurrent() const {
	return &(iter->data);
}

template <class type>
type* linkedList<type>::getNext() const {
	if (iter->next != &mainNode) {
		iter = iter->next;
		return &(iter->data);
	}
	else {
		return HL_NULL;
	}
}

template <class type>
type* linkedList<type>::getPrev() const {
	if (iter->prev != &mainNode) {
		iter = iter->prev;
		return &(iter->data);
	}
	else {
		return HL_NULL;
	}
}

template <class type>
type* linkedList<type>::peekNext() const {
	return &(iter->next->data);
}

template <class type>
type* linkedList<type>::peekPrev() const {
	return &(iter->prev->data);
}

//-----------------------------------------------------------------------------
//			Insertion
//-----------------------------------------------------------------------------
template <class type>
void linkedList<type>::pushFront(const type& object) {
	iter = mainNode.next;
	pushBefore(object);
}

template <class type>
void linkedList<type>::pushBack(const type& object) {
	iter = &mainNode;
	pushBefore(object);
}

template <class type>
void linkedList<type>::pushBefore(const type& object) {
	node* temp = new node;
	temp->data = object;
	
	temp->next = iter;
	temp->prev = iter->prev;
	temp->prev->next = temp;
	iter->prev = temp;
	iter = temp;
	
	++numNodes;
}

template <class type>
void linkedList<type>::pushAfter(const type& object) {
	iter = iter->next;
	pushBefore(object);
}

//-----------------------------------------------------------------------------
//			Deletion
//-----------------------------------------------------------------------------
template <class type>
void linkedList<type>::popnode() {
	//make sure that there's actually something to delete
	if (iter == &mainNode) return;
	node* temp = iter;
	iter = iter->next;
	iter->prev = temp->prev;
	temp->prev->next = iter;
	delete temp;

	//move to the last node if necessary
	if (iter == &mainNode) iter = mainNode.prev;
	--numNodes;
}

template <class type>
void linkedList<type>::popFront() {
	iter = mainNode.next;
	popnode();
}

template <class type>
void linkedList<type>::popBack() {
	iter = mainNode.prev;
	popnode();
}

template <class type>
void linkedList<type>::clear() {
	iter = mainNode.next;
	while (iter != &mainNode) {
		popnode();
	}
}

//-----------------------------------------------------------------------------
//			Miscellaneous
//-----------------------------------------------------------------------------
template <class type>
hlSize_t linkedList<type>::size() const {
	return numNodes;
}

template <class type>
bool linkedList<type>::empty() const {
	return (mainNode.next != &mainNode) ? false : true;
}

} //end containers namespace
} //end hamLibs namespace
#endif //__HL_LINKEDLIST__
