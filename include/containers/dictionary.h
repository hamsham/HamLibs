/* 
 * File:   dictionary.h
 * Author: hammy
 *
 * Created on August 28, 2012, 4:53 PM
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H


namespace hamLibs {
namespace containers {

typedef const char* const cstr;

template <typename type>
class dictionary {
	private:
		struct node {
			char		letter;
			type*	definition;
			node*	alphabet[26];
			
			explicit	node		();
			explicit	node		(const node& nodeCopy);
			~node			();
			node&	operator=	(const node& nodeCopy);
			void		clear	();
			bool		hasSubNodes() const;
		};
		
		node	mainNode;
		
		int		getArrayIndex		(char c) const;
		node*	iterateToNode		(cstr nodeName) const;
		std::string iterateToNextNode	(cstr nodeName) const;
		std::string iterateToPrevNode	(cstr nodeName) const;
		
	public:
		class iterator {
			friend class dictionary<type>;
			
			private:
				const dictionary* dictToIter;
				const dictionary::node* currentNode;
				std::string currentWord;
				
			public:
				iterator();
				iterator( const iterator& iterCopy );
				~iterator();
				
				iterator operator ++ (int); // postfix
				iterator operator -- (int);
				iterator& operator ++ (); // prefix
				iterator& operator -- ();
				iterator& operator = ( const iterator& iterCopy );
				iterator& operator = ( const dictionary& dict );
				
				bool atFront () const;
				bool atEnd() const;
				
				void goToFront();
				void goToEnd();
				void goToWord( cstr word );
				
				cstr getCurrentWord() const;
				type* getData() const;
		};
		
		dictionary			(){}
		dictionary			(const dictionary& dictionCopy) {mainNode = dictionCopy.mainNode;}
		~dictionary			() {}
		dictionary& operator=	(const dictionary& dictCopy);
		
		type* getDefinition		(cstr word) const;
		void setDefinition		(cstr word, const type& inDefinition);
		void clearDefinition	(cstr word);
		bool knowWord			(cstr word);
		bool knowDefinition		(cstr word);
		bool knowSubWords		(cstr word); //check if there are any sub-nodes within a node
		void addWord			(cstr word);
		void deleteWord		(cstr word); //clears a node's letter (if it doesn't have any sub-nodes) and its definition
		void clear			() {mainNode.clear();}
		
		iterator begin			() const;
		iterator end			() const;
		
		//TODO!!!
		//void printDictionary		(std::ostream& outputStream, cstr wordSeparator = " -- ");
		//bool saveToCSVFile	(cstr fileName);
		//bool loadFromCSVFile	(cstr fileName);
};

//-----------------------------------------------------------------------------
//		Node Structure
//-----------------------------------------------------------------------------
template <typename type>
dictionary<type>::node::node() :
	letter		(0),
	definition	(HL_NULL)
{
	//NULL-ify all of the elements in the array
	int iter = 26;
	while (iter--) {
		alphabet[iter] = HL_NULL;
	}
}

template <typename type>
dictionary<type>::node::node(const node& nodeCopy) :
	letter(0),
	definition( HL_NULL )
{
	int iter(26);
	while (iter--)
		alphabet[ iter ] = HL_NULL;
	*this = ( nodeCopy );
}

template <typename type>
 dictionary<type>::node::~node() {
	clear();
}

template <typename type> typename
dictionary<type>::node& dictionary<type>::node::operator = (const node& nodeCopy) {
	clear();
	letter = nodeCopy.letter;
	
	if (nodeCopy.definition != HL_NULL) {
		if (definition)
			delete definition;
		definition = new type(*(nodeCopy.definition));
		
	}
	
	int iter(26);
	while (iter--) {
		if (nodeCopy.alphabet[ iter ]) {
			alphabet[ iter ] = new node (*nodeCopy.alphabet[ iter ]); //begin recursive awesomeness!
		}
	}
	return *this;
}

template <typename type>
void dictionary<type>::node::clear() {
	letter = 0;
	delete definition;
	definition = HL_NULL;
	
	int iter(26);
	while (iter--) {
		delete alphabet[ iter ];
		alphabet[ iter ] = HL_NULL;
	}
}

template <typename type>
bool dictionary<type>::node::hasSubNodes() const {
	int iter(26);
	while (iter--) {
		if ( alphabet[ iter ] != HL_NULL )
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//		Utilities
//-----------------------------------------------------------------------------
template <typename type>
dictionary<type>& dictionary<type>::operator = (const dictionary& dictCopy) {
	mainNode = dictCopy.mainNode;
	return *this;
}

template <typename type> typename
dictionary<type>::node* dictionary<type>::iterateToNode(cstr nodeName) const {
	int pos(0), index(0);
	node* nodeTracker( const_cast< node* >(&mainNode) ); //dictionary iterator

	do {
		index = getArrayIndex( nodeName[pos] );
		if (index == -1 || !nodeTracker->alphabet[ index ]) return HL_NULL;
		nodeTracker = nodeTracker->alphabet[index];
		++pos;
	} while (nodeName[ pos ]);					//end the loop when a null-termination is reached
	return nodeTracker;						//return the position of the requested node
}

template <typename type>
std::string dictionary<type>::iterateToNextNode(cstr nodeName) const {
	std::string nodeIdentifier;
	if (nodeName != HL_NULL) {
		nodeIdentifier = nodeName;
	}
	else {
		nodeIdentifier = "a";
	}
	node* nodeIter = iterateToNode( nodeName );
	int iter = 0;
	
	//search for a possible child node (going from a-z)
	if (nodeIter) {
		while (iter < 26) {
			if (nodeIter->alphabet[ iter ]) {
				//move to the next node by incrementing the specified letter by "iter"
				nodeIdentifier.push_back( 'a' + iter );
				return nodeIdentifier;
			}
			++iter;
		}
	}
	
	//if no child node was found in the previous loop, go to the parent node, then return the next sibling node
	while (nodeIdentifier.size() > 0) {
		if (nodeIdentifier[ nodeIdentifier.size()-1 ] == 'z' ) {
			nodeIdentifier.erase( nodeIdentifier.size()-1 );
			continue;
		}
		nodeIdentifier[ nodeIdentifier.size()-1 ] += 1;
		nodeIter = iterateToNode( nodeIdentifier.c_str() );
		if (nodeIter) return nodeIdentifier;
	}
	return nodeIdentifier;
}

template <typename type>
std::string dictionary<type>::iterateToPrevNode(cstr nodeName) const {
	std::string nodeIdentifier;
	if (nodeName != HL_NULL) {
		nodeIdentifier = nodeName;
	}
	else {
		return nodeIdentifier;
	}
	node* nodeIter = iterateToNode( nodeName );
	int iter = 26;
	
	//search for a possible child node (going from z-a)
	if (nodeIter) {
		while (iter--) {
			if (nodeIter->alphabet[ iter ]) {
				//move to the next node by incrementing the specified letter by "iter"
				nodeIdentifier.push_back( 'a' + iter );
				return nodeIdentifier;
			}
		}
	}
	
	//if no child node was found in the previous loop, go to the parent node, then return the next sibling node
	while (nodeIdentifier.size() > 0) {
		if (nodeIdentifier[ nodeIdentifier.size()-1 ] == 'a' ) {
			nodeIdentifier.erase( nodeIdentifier.size()-1 );
			continue;
		}
		nodeIdentifier[ nodeIdentifier.size()-1 ] -= 1;
		nodeIter = iterateToNode( nodeIdentifier.c_str() );
		if (nodeIter) return nodeIdentifier;
	}
	return nodeIdentifier;
}

template <typename type>
int dictionary<type>::getArrayIndex(char c) const {
	//make sure the letter in question actually is a letter
	if ((c < 'a') && (c > 'Z') || (c < 'A') || (c > 'z')) return -1;
	return (c < 'a') ? c - 'A' : c - 'a';	//convert all uppercase letters to lowercase (See asciitable.com)
	//get the index of the next letter in dictionary<type>::alphabet[]
}

//-----------------------------------------------------------------------------
//		Definitions
//-----------------------------------------------------------------------------
template <typename type>
type* dictionary<type>::getDefinition(cstr word) const {
	node* nodeTracker( iterateToNode(word) );
	return nodeTracker->definition;
}

template <typename type>
void dictionary<type>::setDefinition(cstr word, const type& inDefinition) {
	node* nodeTracker( iterateToNode(word) );
	if (nodeTracker) {
		if (nodeTracker->definition)
			delete nodeTracker->definition;
		nodeTracker->definition = new type( inDefinition );
	}
}

template <typename type>
void dictionary<type>::clearDefinition(cstr word) {
	node* nodeTracker( iterateToNode(word) );
	if (nodeTracker) {
		delete nodeTracker->definition;
		nodeTracker->definition = HL_NULL;
	}
}

template <typename type>
bool dictionary<type>::knowWord(cstr word) {
	node* nodeTracker( iterateToNode(word) );
	return (nodeTracker) ? true : false;
}

template <typename type>
bool dictionary<type>::knowDefinition(cstr word) {
	node* nodeTracker( iterateToNode(word) );
	return (nodeTracker && nodeTracker->definition) ? true : false;
}

template <typename type>
bool dictionary<type>::knowSubWords(cstr word) {
	node* nodeTracker( iterateToNode(word) );
	if (nodeTracker) {
		int iter(26);
		while (iter--) {
			if (nodeTracker[ iter ]) return true;
		}
	}
	return false;
}

template <typename type>
void dictionary<type>::addWord(cstr word) {
	int pos(0), index(0);
	node* nodeIter( const_cast< node* >(&mainNode) );

	while ( word[ pos ] ) { //end when a null-termination is reached
		index = getArrayIndex( word[ pos ] );		//get the index of the next letter in dictionary<type>::alphabet[]
		if (index == -1) return;

		if (nodeIter->alphabet[ index ] == HL_NULL) {
			nodeIter->alphabet[ index ] = new node;	//add a new word to the dictionary if possible
			nodeIter->alphabet[ index ]->letter = word[ pos ];
		}
		nodeIter = nodeIter->alphabet[index];	//move to the next letter in dictionary<type>::alphabet
		++pos;
	}
}

template <typename type>
void dictionary<type>::deleteWord(cstr word) {
	node* nodeTracker( iterateToNode(word) );
	if (nodeTracker != HL_NULL && nodeTracker != &mainNode) {
		if (nodeTracker->hasSubNodes() == false) {
			nodeTracker->letter = 0;
		}
		delete nodeTracker->definition;
		nodeTracker->definition = HL_NULL;
	}
}

//-----------------------------------------------------------------------------
//		Iterations
//-----------------------------------------------------------------------------
template <typename type>
dictionary<type>::iterator::iterator() :
	dictToIter( HL_NULL ),
	currentNode( HL_NULL ),
	currentWord( "" )
{}

template <typename type>
dictionary<type>::iterator::iterator( const dictionary<type>::iterator& iterCopy ) :
	dictToIter( iterCopy.dictToIter ),
	currentNode( iterCopy.currentNode ),
	currentWord( iterCopy.currentWord )
{}

template <typename type>
dictionary<type>::iterator::~iterator() {}

template <typename type> typename
dictionary<type>::iterator dictionary<type>::begin() const {
	node* nodeIter( const_cast< node* >(&mainNode) );
	std::string currWord;
	
	int iter(0);
	while (iter < 26) {
		if ( nodeIter->alphabet[ iter ] != HL_NULL ) {
			currWord.push_back( nodeIter->alphabet[ iter ]->letter );
			break;
		}
		else {
			++iter;
		}
	}
	iterator temp;
	temp.dictToIter = this;
	temp.goToWord( (currWord.size() > 0) ? currWord.c_str() : HL_NULL );
	return temp;
}

template <typename type> typename
dictionary<type>::iterator dictionary<type>::end() const {
	node* nodeIter( const_cast< node* >(&mainNode) );
	std::string currWord;
	
	int iter(25);
	while (iter >= 0) {
		if ( nodeIter->alphabet[ iter ] != HL_NULL ) {
			currWord.push_back( nodeIter->alphabet[ iter ]->letter );
			nodeIter = nodeIter->alphabet[ iter ];
			iter = 25;
		}
		else {
			--iter;
		}
	}
	iterator temp;
	temp.dictToIter = this;
	temp.goToWord( (currWord.size() > 0) ? currWord.c_str() : HL_NULL );
	return temp;
}

template <typename type> typename
dictionary<type>::iterator dictionary<type>::iterator::operator ++(int) {
	operator++();
	return *this;
}

template <typename type> typename
dictionary<type>::iterator dictionary<type>::iterator::operator --(int) {
	operator--();
	return *this;
}

template <typename type> typename
dictionary<type>::iterator& dictionary<type>::iterator::operator ++() {
	if (dictToIter != HL_NULL) {
		currentWord = dictToIter->iterateToNextNode( currentWord.c_str() );
		currentNode = dictToIter->iterateToNode( currentWord.c_str() );
	}
	return *this;
}

template <typename type> typename
dictionary<type>::iterator& dictionary<type>::iterator::operator --() {
	if (dictToIter != HL_NULL) {
		currentWord = dictToIter->iterateToPrevNode( currentWord.c_str() );
		currentNode = dictToIter->iterateToNode( currentWord.c_str() );
	}
	return *this;
}

template <typename type> typename
dictionary<type>::iterator& dictionary<type>::iterator::operator = ( const iterator& iterCopy ) {
	dictToIter = iterCopy.dictToIter;
	currentNode = iterCopy.currentNode;
	currentWord = iterCopy.currentWord;
}

template <typename type> typename
dictionary<type>::iterator& dictionary<type>::iterator::operator = ( const dictionary& dict ) {
	*this = dict.begin();
}

template <typename type>
bool dictionary<type>::iterator::atFront () const {
	if (dictToIter == HL_NULL
	|| dictToIter->iterateToPrevNode( currentWord.c_str() ).size() == 0)
		   return true;
	return false;
}

template <typename type>
bool dictionary<type>::iterator::atEnd() const {
	if (dictToIter == HL_NULL
	|| dictToIter->iterateToNextNode( currentWord.c_str() ).size() == 0)
		return true;
	return false;
}

template <typename type>
void dictionary<type>::iterator::goToFront() {
	if (dictToIter != HL_NULL)
		*this = dictToIter->begin();
}

template <typename type>
void dictionary<type>::iterator::goToEnd() {
	if (dictToIter != HL_NULL)
		*this = dictToIter->end();
}

template <typename type>
void dictionary<type>::iterator::goToWord( cstr word ) {
	if (dictToIter == HL_NULL || word == HL_NULL)
		return;
	
	currentNode = dictToIter->iterateToNode( word );
	if ( currentNode != HL_NULL )
		currentWord = word;
}

template <typename type>
cstr dictionary<type>::iterator::getCurrentWord() const {
	if (dictToIter != HL_NULL)
		return currentWord.c_str();
	return HL_NULL;
}

template <typename type>
type* dictionary<type>::iterator::getData() const {
	if (dictToIter != HL_NULL && currentNode != HL_NULL)
		return currentNode->definition;
	return HL_NULL;
}

//-----------------------------------------------------------------------------
//		Data saving & reloading
//-----------------------------------------------------------------------------
/*
template <typename type>
void dictionary<type>::printDictionary(std::ostream& output, cstr wordSeparator) {
	node* nodeTracker = iterateToNode("a");
	std::string currentNode = "a";
	
	do {
		if (nodeTracker && nodeTracker->definition.size() != 0) {
			output << "\t" << currentNode.c_str() << wordSeparator;
			output << nodeTracker->definition.c_str() << wordSeparator << std::endl;
		}
		currentNode = iterateToNextNode( currentNode.c_str() );
		nodeTracker = iterateToNode( currentNode.c_str() );
	} while (nodeTracker);
}

bool dictionary<type>::saveToCSVFile(cstr fileName) {
	std::ofstream fout(fileName, std::ios_base::out | std::ios_base::binary);
	if (!fout) {
		std::cerr << "ERROR: Unable to save dictionary file " << fileName << "!" << std::endl;
		return false;
	}
	
	printDictionary(fout, ", ");
	fout.close();
	
	if (fout.fail()) {
		std::cerr << "ERROR: A problem occurred while saving the dictionary file " << fileName << "!";
		std::cerr << std::endl;
		fout.clear();
		return false;
	}
	fout.clear();
	return true;
}

bool dictionary<type>::loadFromCSVFile(cstr fileName) {
	return false;
}
*/

} //end containers namespace
} //end hamLibs namespace
#endif	/* DICTIONARY_H */
