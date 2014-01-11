/* 
 * File:   bTree.h
 * Author: hammy
 *
 * Created on June 19, 2013, 12:25 AM
 */

#ifndef __HL_B_TREE_H__
#define __HL_B_TREE_H__

#include <iostream>
#include <new>
#include "../utils/bits.h"

namespace hamLibs {
namespace containers {

enum bnode_dir : unsigned {
    BNODE_LEFT   = 0,
    BNODE_RIGHT  = 1,
    BNODE_MAX
};

/**
 * Binary Tree Node
 */
template <typename data_t>
class bTreeNode {
    private:
        template <typename, typename>
        friend class bTree;
    
        data_t*     data        = nullptr;
        bTreeNode*  subNodes    = nullptr;
        
    public:
        
        constexpr bTreeNode();
        bTreeNode( const bTreeNode& btn );
        bTreeNode( bTreeNode&& btn );

        ~bTreeNode();
        
        bTreeNode& operator=( const bTreeNode& btn );
        bTreeNode& operator=( bTreeNode&& btn );
};

/**
 * B-Tree Node Constructor
 */
template <typename data_t>
constexpr bTreeNode<data_t>::bTreeNode() {}

/**
 * B-Tree Node Copy Constructor
 */
template <typename data_t>
bTreeNode<data_t>::bTreeNode( const bTreeNode& btn ) :
    data{
        btn.data != nullptr
            ? new(std::nothrow) data_t(*btn.data)
            : nullptr
    },
    subNodes{nullptr}
{
    if (btn.subNodes != nullptr) {
        subNodes = new(std::nothrow) bTreeNode[ BNODE_MAX ];
        subNodes[ BNODE_LEFT ] = btn.subNodes[ BNODE_LEFT ];
        subNodes[ BNODE_RIGHT ] = btn.subNodes[ BNODE_RIGHT ];
    }
}

/**
 * B-Tree Node Move Constructor
 */
template <typename data_t>
bTreeNode<data_t>::bTreeNode( bTreeNode&& btn ) :
    data{ btn.data },
    subNodes{ btn.subNodes }
{
    btn.data = nullptr;
    btn.subNodes = nullptr;
}

/**
 * B-Tree Node Destructor
 */
template <typename data_t>
bTreeNode<data_t>::~bTreeNode() {
    delete data;
    data = nullptr;
    
    delete [] subNodes;
    subNodes = nullptr;
}

/**
 * B-Tree Node Copy Operator
 */
template <typename data_t>
bTreeNode<data_t>& bTreeNode<data_t>::operator=( const bTreeNode& btn ) {
    delete data;
    if (btn.data) {
        data = new(std::nothrow) data_t;
        *data = *btn.data;
    }
    else {
        data = nullptr;
    }
    
    delete subNodes;
    if (btn.subNodes) {
        subNodes = new(std::nothrow) bTreeNode[ BNODE_MAX ];
        subNodes[ BNODE_LEFT ] = btn.subNodes[ BNODE_LEFT ];
        subNodes[ BNODE_RIGHT ] = btn.subNodes[ BNODE_RIGHT ];
    }
    else {
        subNodes = nullptr;
    }
}

/**
 * B-Tree Node Move Operator
 */
template <typename data_t>
bTreeNode<data_t>& bTreeNode<data_t>::operator=( bTreeNode&& btn ) {
    data = btn.data;
    btn.data = nullptr;
    
    subNodes = btn.subNodes;
    btn.subNodes = nullptr;
}

/******************************************************************************
 *  Binary-Tree Structure Setup
 * 
 * TODO Add iterators
******************************************************************************/
template <typename key_t, typename data_t>
class bTree {

    protected:
        bTreeNode<data_t>   head = bTreeNode<data_t>();
        unsigned            numNodes = 0;
        
    private:
        bTreeNode<data_t>* iterate( const key_t* k, bool createNodes );
        
    public:
        constexpr bTree ();
        bTree           ( const bTree& );
        bTree           ( bTree&& );
        
        ~bTree          () {}
        
        bTree&          operator=   ( const bTree& );
        bTree&          operator=   ( bTree&& );
        
        // STL-Map behavior
        data_t&         operator [] ( const key_t& k );
        
        void            push        ( const key_t& k, const data_t& d );
        void            pop         ( const key_t& k );
        bool            hasData     ( const key_t& k );
        const data_t*   getData     ( const key_t& k );
        unsigned        size        () const { return numNodes; }
        void            clear       ();
};

/*
 * Binary Tree -- Constructor
 */
template <typename key_t, typename data_t>
constexpr bTree<key_t, data_t>::bTree() :
    head{},
    numNodes{0}
{}

/*
 * Binary Tree -- Copy Constructor
 */
template <typename key_t, typename data_t>
bTree<key_t, data_t>::bTree( const bTree& bt ) :
    head{ bt.head },
    numNodes{ bt.numNodes }
{}

/*
 * Binary Tree -- Move Constructor
 */
template <typename key_t, typename data_t>
bTree<key_t, data_t>::bTree( bTree&& bt ) {
    head.subNodes = bt.head.subNodes;
    bt.head.subNodes = nullptr;
    
    numNodes = bt.numNodes;
    bt.numNodes = 0;
}

/*
 * Binary Tree -- Copy Operator
 */
template <typename key_t, typename data_t>
bTree<key_t, data_t>& bTree<key_t, data_t>::operator =( const bTree& bt ) {
    head = bt.head;
    numNodes = bt.numNodes;
    return *this;
}

/*
 * Binary Tree -- Move Operator
 */
template <typename key_t, typename data_t>
bTree<key_t, data_t>& bTree<key_t, data_t>::operator =( bTree&& bt ) {
    head.subNodes = bt.head.subNodes;
    bt.head.subNodes = nullptr;
    
    numNodes = bt.numNodes;
    bt.numNodes = 0;
    
    return *this;
}

/*
 * Binary-Tree -- Element iteration
 */
template <typename key_t, typename data_t>
bTreeNode<data_t>* bTree<key_t, data_t>::iterate( const key_t* k, bool createNodes ) {
    
    unsigned            bytePos     = 0;
    bTreeNode<data_t>*  bNodeIter   = &head;
    const utils::bitMask* byteIter  = nullptr;
    
    while ( (byteIter = hamLibs::utils::getByte< key_t >( k, bytePos++ )) ) {
        
        for ( unsigned currBit = HL_BITS_PER_BYTE; currBit--; ) {

            // check to see if a new bTreeNode needs to be made
            if ( !bNodeIter->subNodes ) {
                if ( createNodes ) {
                    // create and initialize the upcoming sub bTreeNode
                    bNodeIter->subNodes = new bTreeNode<data_t>[ BNODE_MAX ];
                }
                else {
                    return nullptr;
                }
            }
            
            // move to the next bTreeNode
            const int dir = byteIter->get( currBit );
            bNodeIter = &(bNodeIter->subNodes[ dir ]);
        }
    }
    
    return bNodeIter;
}

/*
 * Binary-Tree -- Destructor
 */
template <typename key_t, typename data_t>
void bTree<key_t, data_t>::clear() {
    delete head.data;
    delete [] head.subNodes;
    
    head.data = nullptr;
    head.subNodes = nullptr;
    numNodes = 0;
}

/*
 * Binary-Tree -- Array Subscript operators
 */
template <typename key_t, typename data_t>
data_t& bTree<key_t, data_t>::operator []( const key_t& k ) {
    bTreeNode<data_t>* iter = iterate( &k, true );
    
    if ( !iter->data ) {
        iter->data = new data_t();
        ++numNodes;
    }
    
    return *iter->data;
}

/*
 * Binary-Tree -- Push
 * Push a data element to the tree using a key
 */
template <typename key_t, typename data_t>
void bTree<key_t, data_t>::push( const key_t& k, const data_t& d ) {
    bTreeNode<data_t>* iter = iterate( &k, true );
    
    if ( !iter->data ) {
        iter->data = new data_t( d );
        ++numNodes;
    }
    else {
        *iter->data = d;
    }
}

/*
 * Binary-Tree -- Pop
 * Remove whichever element lies at the key
 */
template <typename key_t, typename data_t>
void bTree<key_t, data_t>::pop( const key_t& k ) {
    bTreeNode<data_t>* iter = iterate( &k, false );

    if ( !iter || !iter->data )
        return;

    delete iter->data;
    iter->data = nullptr;
    --numNodes;
}

/*
 * Binary-Tree -- Has Data
 * Return true if there is a data element at the key
 */
template <typename key_t, typename data_t>
bool bTree<key_t, data_t>::hasData( const key_t& k ) {
    bTreeNode<data_t>* iter = iterate( &k, false );

    return iter && ( iter->data != nullptr );
}

/*
 * Binary-Tree -- Push
 * Return a pointer to the data that lies at a key
 * Returns a nullptr if no data exists
 */
template <typename key_t, typename data_t>
const data_t* bTree<key_t, data_t>::getData( const key_t& k ) {
    bTreeNode<data_t>* iter = iterate( &k, false );

    if ( !iter )
        return nullptr;

    return iter->data;
}

} // end containers namespace
} // end hamLibs namespace

#endif  /* __HL_B_TREE_H__ */

