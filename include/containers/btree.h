/* 
 * File:   bTree.h
 * Author: hammy
 *
 * Created on June 19, 2013, 12:25 AM
 */

#ifndef __HL_B_TREE_H__
#define	__HL_B_TREE_H__

#include "tree_common.h"

namespace hamLibs {
namespace containers {

template <typename data_t>
struct bTreeNode {
    data_t*     data        = nullptr;
    bTreeNode*  subNodes    = nullptr;

    ~bTreeNode() {
        delete data;
        delete [] subNodes;
        
        data = nullptr;
        subNodes = nullptr;
    }
};

/******************************************************************************
 *  Binary-Tree Structure Setup
******************************************************************************/
template <typename key_t, typename data_t>
class bTree : virtual public treeBase {

    enum node_dir : unsigned {
        BNODE_LEFT   = 0,
        BNODE_RIGHT  = 1,
        BNODE_MAX
    };

    protected:
        bTreeNode<data_t>   head;
        unsigned            numNodes = 0;
        
    private:
        bTreeNode<data_t>* iterate( const key_t* k, bool createNodes );
        
    public:
        ~bTree() {}
        
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
 * Binary-Tree -- Element iteration
 */ 
template <typename key_t, typename data_t>
bTreeNode<data_t>* bTree<key_t, data_t>::iterate( const key_t* k, bool createNodes ) {
    
    node_dir            dir;
    unsigned            iter        = 0;
    bTreeNode<data_t>*  bNodeIter   = const_cast< bTreeNode<data_t>* >( &this->head );
    const bitMask*      bitIter     = nullptr;

    while ( bitIter = treeBase::getKeyByte( k, iter++ ) ) {
        
        unsigned j = HL_BITS_PER_BYTE;
        while ( j-- ) {
            
            // compare the bits of each byte in k
            dir = bitIter->operator [](j) ? BNODE_LEFT : BNODE_RIGHT;

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
bool bTree<key_t, data_t>::hasData( const key_t& k ) const {
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

#endif	/* __HL_B_TREE_H__ */

