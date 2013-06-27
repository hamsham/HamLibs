/* 
 * File:   tTree.h
 * Author: hammy
 *
 * Created on June 19, 2013, 12:25 AM
 */

#ifndef __HL_TRI_TREE_H__
#define	__HL_TRI_TREE_H__

/*
 * The Tri-Tree is a simple structure which contains three leafs per node
 * Currently, no iterators exist (in progress).
 * Only fixed-sized keys are supported, but there is a class specialization for
 * C-style strings. Additional specializations will be added as needed.
 */

#include "tree_common.h"

namespace hamLibs {
namespace containers {

template <typename data_t>
struct tTreeNode {
    bitMask     bits        = { 0,0,0,0,0,0,0,0 };
    data_t*     data        = nullptr;
    tTreeNode*  subNodes    = nullptr;

    ~tTreeNode() {
        delete data;
        delete [] subNodes;
        
        data = nullptr;
        subNodes = nullptr;
    }
};

/******************************************************************************
 *  Tri-Tree Structure Setup
******************************************************************************/
template <typename key_t, typename data_t>
class tTree: virtual public treeBase {

    enum node_dir : unsigned {
        LEFT_NODE   = 0,
        MID_NODE    = 1,
        RIGHT_NODE  = 2,
        MAX_NODE    = 3
    };
    
    protected:
        tTreeNode<data_t>   head;
        unsigned            numNodes = 0;
        
    public:
        ~tTree() {}
        
        tTreeNode<data_t>* iterate( const void* key, bool createSubNodes );
        
        // STL-Map behavior
        data_t&         operator [] ( const key_t& k );
        
        void            push        ( const key_t& k, const data_t& d );
        void            pop         ( const key_t& k );
        bool            hasData     ( const key_t& k ) const;
        const data_t*   getData     ( const key_t& k );
        unsigned        size        () const { return numNodes; }
        void            clear       ();
};

/*
 * Tri-Tree -- Iteration
 */
template <typename key_t, typename data_t>
tTreeNode<data_t>* tTree<key_t, data_t>::iterate( const void* k, bool createNodes ) {
    
    node_dir            dir;
    unsigned            iter        = 0;
    tTreeNode<data_t>*  tNodeIter   = const_cast< tTreeNode<data_t>* >( &this->head );
    const bitMask*      bitIter     = nullptr;

    while ( bitIter = treeBase::getKeyByte( k, iter++ ) ) {
        
        unsigned j = HL_BITS_PER_BYTE;
        while ( j-- ) {
            // compare the bits of each byte in k
            if ( bitIter->operator[](j) < tNodeIter->bits[j] ) {
                dir = LEFT_NODE;
            }
            else if ( bitIter->operator[](j) > tNodeIter->bits[j] ) {
                dir = RIGHT_NODE;
            }
            else {
                dir = MID_NODE;
            }

            // check to see if a new node needs to be made
            if ( !tNodeIter->subNodes ) {
                if ( createNodes ) {
                    // create and initialize the upcoming sub node
                    tNodeIter->subNodes = new tTreeNode<data_t>[ MAX_NODE ];
                    tNodeIter->subNodes[ dir ].bits = *bitIter;
                }
                else {
                    return nullptr;
                }
            }

            // move to the next node
            tNodeIter = &(tNodeIter->subNodes[ dir ]);
        }
    }
    return tNodeIter;
}

/*
 * Tri-Tree -- Destructor
 */
template <typename key_t, typename data_t>
void tTree<key_t, data_t>::clear() {
    delete head.data;
    delete [] head.subNodes;
    
    head.data = nullptr;
    head.subNodes = nullptr;
    numNodes = 0;
}

/*
 * Tri-Tree -- Array Subscript operators
 */
template <typename key_t, typename data_t>
data_t& tTree<key_t, data_t>::operator []( const key_t& k ) {
    tTreeNode<data_t>* iter = iterate( &k, true );
    
    if ( !iter->data ) {
        iter->data = new data_t();
        ++numNodes;
    }
    
    return *iter->data;
}

/*
 * Tri-Tree -- Push
 * Push a data element to the tree using a key
 */
template <typename key_t, typename data_t>
void tTree<key_t, data_t>::push( const key_t& k, const data_t& d ) {
    tTreeNode<data_t>* iter = iterate( &k, true );
    
    if ( !iter->data ) {
        iter->data = new data_t( d );
        ++numNodes;
    }
    else {
        *iter->data = d;
    }
}

/*
 * Tri-Tree -- Pop
 * Remove whichever element lies at the key
 */
template <typename key_t, typename data_t>
void tTree<key_t, data_t>::pop( const key_t& k ) {
    tTreeNode<data_t>* iter = iterate( &k, false );

    if ( !iter || !iter->data )
        return;

    delete iter->data;
    iter->data = nullptr;
    --numNodes;
}

/*
 * Tri-Tree -- Has Data
 * Return true if there is a data element at the key
 */
template <typename key_t, typename data_t>
bool tTree<key_t, data_t>::hasData( const key_t& k ) const {
    tTreeNode<data_t>* iter = iterate( &k, false );

    return iter && ( iter->data != nullptr );
}

/*
 * Tri-Tree -- Push
 * Return a pointer to the data that lies at a key
 * Returns a nullptr if no data exists
 */
template <typename key_t, typename data_t>
const data_t* tTree<key_t, data_t>::getData( const key_t& k ) {
    tTreeNode<data_t>* iter = iterate( &k, false );

    if ( !iter )
        return nullptr;

    return iter->data;
}

} // end containers namespace
} // end hamLibs namespace

#endif	/* __HL_TRI_TREE_H__ */

