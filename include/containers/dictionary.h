/* 
 * File:   dictionary.h
 * Author: hammy
 *
 * Created on August 28, 2012, 4:53 PM
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "linkedList.h"


namespace hamLibs {
namespace containers {

typedef const char* const cstr;

template <typename type>
class dictionary {
	private:
		struct node {
			char		letter;
			type		definition;
			node*	alphabet[26];
			
			explicit	node		();
			explicit	node		(const node& nodeCopy);
			~		node		();
			node&	operator=	(const node& nodeCopy);
			void		clear	();
		};
		
		node	mainNode;
		
		int		getArrayIndex		(char c) const;
		node*	iterateToNode		(cstr nodeName);
		std::string iterateToNextNode	(cstr nodeName = "a");
		
	public:
		dictionary			(){}
		dictionary			(const dictionary& dictionCopy) {mainNode = dictionCopy.mainNode;}
		~dictionary			() {}
		dictionary& operator=	(const dictionary& dictCopy);
		
		type* getDefinition		(cstr word) const;
		void setDefinition		(cstr word, const type& inDefinition);
		void clearDefinition	(cstr word);
		bool knowWord			(cstr word);
		bool knowDefinition		(cstr word);
		bool knowSubWords		(cstr word);	//check if there are any sub-nodes within a node
		void addWord			(cstr word);
		void deleteWord		(cstr word);
		void clear			() {mainNode.clear();}
		
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
dictionary<type>::node::node(const node& nodeCopy)  :
	letter		(0),
	definition	(HL_NULL)
{
	//NULL-ify all of the elements in the array
	int iter = 26;
	while (iter--) {
		alphabet[iter] = HL_NULL;
	}
	*this = nodeCopy;
}

template <typename type>
 dictionary<type>::node::~node() {
	clear();
}

template <typename type> typename
dictionary<type>::node& dictionary<type>::node::operator = (const node& nodeCopy) {
	clear();
	letter = nodeCopy.letter;
	definition = new type(nodeCopy.definition);
	
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
	int iter(26);
	while (iter--) {
		delete alphabet[iter];
		alphabet[ iter ] = HL_NULL;
	}
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
dictionary<type>::node* dictionary<type>::iterateToNode(cstr nodeName) {
	int pos(0), index(0);
	node* nodeTracker(&mainNode); //dictionary iterator

	do {
		index = getArrayIndex( nodeName[pos] );
		if (index == -1 || !nodeTracker->alphabet[ index ]) return HL_NULL;
		nodeTracker = nodeTracker->alphabet[index];
		++pos;
	} while (nodeName[ pos ]);					//end the loop when a null-termination is reached
	return nodeTracker;						//return the position of the requested node
}

template <typename type>
std::string dictionary<type>::iterateToNextNode(cstr nodeName) {
	std::string nodeIdentifier( nodeName );
	node* nodeIter = iterateToNode( nodeName );
	int iter = 0;
	
	//search for a possible child node
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
	node* nodeTracker(&mainNode); //dictionary iterator

	while ( word[ pos ] ) { //end when a null-termination is reached
		index = getArrayIndex( word[ pos ] );		//get the index of the next letter in dictionary<type>::alphabet[]
		if (index == -1) return;

		if (nodeTracker->alphabet[ index ] == HL_NULL) {
			nodeTracker->alphabet[ index ] = new node;	//add a new word to the dictionary if possible
			nodeTracker->alphabet[ index ]->letter = word[ pos ];
		}
		nodeTracker = nodeTracker->alphabet[index];	//move to the next letter in dictionary<type>::alphabet
		++pos;
	}
}

template <typename type>
void dictionary<type>::deleteWord(cstr word) {
	node* nodeTracker( iterateToNode(word) );
	if (nodeTracker != HL_NULL && nodeTracker != &mainNode)
		delete nodeTracker;
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
