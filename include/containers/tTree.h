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

#ifndef HL_BITS_PER_BYTE
    #define HL_BITS_PER_BYTE 8
#endif /* NUM_BITS_PER_BYTE */

namespace hamLibs {
namespace containers {

enum node_dir : int {
    LEFT_NODE   = 0,
    MID_NODE    = 1,
    RIGHT_NODE  = 2,
    MAX_NODE    = 3
};

struct bitmask {
    char b1 : 1;
    char b2 : 1;
    char b3 : 1;
    char b4 : 1;
    char b5 : 1;
    char b6 : 1;
    char b7 : 1;
    char b8 : 1;

    char operator[] ( unsigned i ) const {
        switch( i ) {
            case 0 : return b1;
            case 1 : return b2;
            case 2 : return b3;
            case 3 : return b4;
            case 4 : return b5;
            case 5 : return b6;
            case 6 : return b7;
            case 7 : return b8;
        }
        return 0; // Avoiding a compiler error
    }
};

template <typename data_t>
struct node {
    bitmask bits = { 0,0,0,0,0,0,0,0 };
    data_t* data = nullptr;
    node*   subNodes = {nullptr};

    ~node() {
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
class tTreeBase {
    
    protected:
        node<data_t> head;
        int numNodes = 0;
        
    public:
        virtual ~tTreeBase() {}
        
        virtual node<data_t>* iterate( const void* key, bool createSubNodes ) = 0;
        
        // STL-Map behavior
        data_t&         operator [] ( const key_t& k );
        
        void            push        ( const key_t& k, const data_t& d );
        void            pop         ( const key_t& k );
        bool            hasData     ( const key_t& k ) const;
        const data_t*   getData     ( const key_t& k );
        int             size        () const { return numNodes; }
        void            clear       () { delete [] head.subNodes; delete head.data; }
};

/*
 * Tri-Tree -- Array Subscript operators
 */
template <typename key_t, typename data_t>
data_t& tTreeBase<key_t, data_t>::operator []( const key_t& k ) {
    node<data_t>* iter = iterate( &k, true );
    
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
void tTreeBase<key_t, data_t>::push( const key_t& k, const data_t& d ) {
    node<data_t>* iter = iterate( &k, true );
    
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
void tTreeBase<key_t, data_t>::pop( const key_t& k ) {
    node<data_t>* iter = iterate( &k, false );

    if ( !iter || iter->data )
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
bool tTreeBase<key_t, data_t>::hasData( const key_t& k ) const {
    node<data_t>* iter = iterate( &k, false );

    return iter && ( iter->data != nullptr );
}

/*
 * Tri-Tree -- Push
 * Return a pointer to the data that lies at a key
 * Returns a nullptr if no data exists
 */
template <typename key_t, typename data_t>
const data_t* tTreeBase<key_t, data_t>::getData( const key_t& k ) {
    node<data_t>* iter = iterate( &k, false );

    if ( !iter )
        return nullptr;

    return iter->data;
}

/******************************************************************************
 *  Tri-Tree Structure 
******************************************************************************/
template <typename key_t, typename data_t>
class tTree final : public tTreeBase<key_t, data_t> {
    
    private:
        node<data_t>* iterate( const void* k, bool createNodes );
    
    public:
        tTree         ()      {}
        ~tTree        ()      {}

}; // end tTree class
    
template <typename key_t, typename data_t>
node<data_t>* tTree<key_t, data_t>::iterate( const void* k, bool createNodes ) {

    node<data_t>* nodeIter = const_cast< node<data_t>* >( &this->head );
    node_dir dir;

    for ( unsigned i = 0; i < sizeof( key_t ); ++i ) {
        // iterate through each set of bits within the key
        const bitmask*  bitIter = reinterpret_cast< const bitmask* >( k ) + i;

        for ( unsigned j = 0; j < HL_BITS_PER_BYTE; ++j ) {
            // compare the bits of each byte in k
            if ( bitIter->operator[](j) < nodeIter->bits[j] ) {
                dir = LEFT_NODE;
            }
            else if ( bitIter->operator[](j) > nodeIter->bits[j] ) {
                dir = RIGHT_NODE;
            }
            else {
                dir = MID_NODE;
            }

            // check to see if a new node needs to be made
            if ( !nodeIter->subNodes ) {
                if ( createNodes ) {
                    // create and initialize the upcoming sub node
                    nodeIter->subNodes = new node<data_t>[ MAX_NODE ];
                    nodeIter->subNodes[ dir ].bits = *bitIter;
                }
                else {
                    return nullptr;
                }
            }

            // move to the next node
            nodeIter = &(nodeIter->subNodes[ dir ]);
        }
    }
    return nodeIter;
}


/******************************************************************************
 *  Tri-Tree Structure -- C-string partial specialization
******************************************************************************/
template <typename data_t>
class tTree<const char*, data_t> final : public tTreeBase<const char*, data_t>  {
    
    private:
        node<data_t>* iterate( const void* str, bool createNodes );
        
    public:
        tTree         ()      {}
        ~tTree        ()      {}
        
}; // end tTree class, string specialization
    
template <typename data_t>
node<data_t>* tTree<const char*, data_t>::iterate( const void* str, bool createNodes ) {
    node<data_t>* nodeIter = const_cast< node<data_t>* >( &this->head );
    node_dir dir;
    const char* s = (const char*)str;

    for ( unsigned i = 0; s[ i ] != '\0'; ++i ) {
        // iterate through each set of bits within the key
        const bitmask*  bitIter = reinterpret_cast< const bitmask* >( s+i );

        for ( unsigned j = 0; j < HL_BITS_PER_BYTE; ++j ) {
            // compare the bits of each byte in k
            if ( bitIter->operator[](j) < nodeIter->bits[j] ) {
                dir = LEFT_NODE;
            }
            else if ( bitIter->operator[](j) > nodeIter->bits[j] ) {
                dir = RIGHT_NODE;
            }
            else {
                dir = MID_NODE;
            }

            // check to see if a new node needs to be made
            if ( !nodeIter->subNodes ) {
                if ( createNodes ) {
                    // create and initialize the upcoming sub node
                    nodeIter->subNodes = new node<data_t>[ MAX_NODE ];
                    nodeIter->subNodes[ dir ].bits = *bitIter;
                }
                else {
                    return nullptr;
                }
            }

            // move to the next node
            nodeIter = &(nodeIter->subNodes[ dir ]);
        }
    }
    return nodeIter;
}

} // end containers namespace
} // end hamLibs namespace

#endif	/* __HL_TRI_TREE_H__ */

