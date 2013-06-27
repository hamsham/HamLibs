/* 
 * File:   tree_common.h
 * Author: hammy
 *
 * Created on June 21, 2013, 1:31 AM
 */

#ifndef __HL_TREE_COMMON_H__
#define	__HL_TREE_COMMON_H__

#ifndef HL_BITS_PER_BYTE
    #define HL_BITS_PER_BYTE 8
#endif /* NUM_BITS_PER_BYTE */


namespace hamLibs {
    namespace containers {

struct bitMask {
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

/******************************************************************************
 *  Tree Structure Bast class
******************************************************************************/
class treeBase {
    protected:
        template <typename key_t>
        static const bitMask* getKeyByte( const key_t* key, unsigned iter );
        
    public:
        virtual ~treeBase() = 0;
        
};

inline treeBase::~treeBase() {}

template <typename key_t>
const bitMask* treeBase::getKeyByte( const key_t* k, unsigned iter ) {
    return (iter < sizeof( key_t ))
        ? reinterpret_cast< const bitMask* >( k+iter )
        : nullptr;
}

template <>
const bitMask* treeBase::getKeyByte( const char*, unsigned );

    } // end containers namespace
} // end hamLibs namespace

#endif	/* __HL_TREE_COMMON_H__ */

