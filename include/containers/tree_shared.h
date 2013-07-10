/* 
 * File:   tree_common.h
 * Author: hammy
 *
 * Created on June 21, 2013, 1:31 AM
 */

#ifndef __HL_TREE_COMMON_H__
#define	__HL_TREE_COMMON_H__

#include <climits>
#include "../utils/assert.h"

#if CHAR_BIT != 8
    #error "Error: The current architecture does not define the number of "\
    "bits per byte as 8. Please adjust the bitMask structure below accordingly."
#else
    #define HL_BITS_PER_BYTE CHAR_BIT
#endif

namespace hamLibs {
    namespace containers {
        
/******************************************************************************
 *  Convenience structure to ensure bit acquisition of bytes
******************************************************************************/
struct alignas(1) bitMask {
    char byte = 0;

    int operator[] ( int i ) const {
        HL_DEBUG_ASSERT( i < HL_BITS_PER_BYTE );
        return (byte >> i) & 1;
    }
};

/******************************************************************************
 *  Functions shared between tree-type objects
******************************************************************************/
namespace treeShared {
    
    // Function to retrieve the next set of bits at the pointer "key"
    template <typename key_t>
    inline const bitMask* getKeyByte( const key_t* key, unsigned iter );
    
    /* template specializations */
    template <>
    inline const bitMask* getKeyByte( const char*, unsigned );

    template <>
    inline const bitMask* getKeyByte( const wchar_t*, unsigned );

    template <>
    inline const bitMask* getKeyByte( const char16_t*, unsigned );

    template <>
    inline const bitMask* getKeyByte( const char32_t*, unsigned );
    
} // end treeShared namespace

/*
 * Tree Bit Mask Function
 */
template <typename key_t>
inline const bitMask* treeShared::getKeyByte( const key_t* k, unsigned iter ) {
    return (iter < sizeof( key_t ))
        ? reinterpret_cast< const bitMask* >( k )+iter
        : nullptr;
}

/*
 * Tree Bit Mask Specializations
 */
template <>
inline const bitMask* treeShared::getKeyByte( const char* str, unsigned iter ) {
    return (str[ iter/sizeof(char) ] != '\0')
        ? reinterpret_cast< const bitMask* >( str )+iter
        : nullptr;
}

template <>
inline const bitMask* treeShared::getKeyByte( const wchar_t* str, unsigned iter ) {
    return (str[ iter/sizeof(wchar_t) ] != '\0')
        ? reinterpret_cast< const bitMask* >( str )+iter
        : nullptr;
}

template <>
inline const bitMask* treeShared::getKeyByte( const char16_t* str, unsigned iter ) {
    return (str[ iter/sizeof(char16_t) ] != '\0')
        ? reinterpret_cast< const bitMask* >( str )+iter
        : nullptr;
}

template <>
inline const bitMask* treeShared::getKeyByte( const char32_t* str, unsigned iter ) {
    return (str[ iter/sizeof(char32_t) ] != '\0')
        ? reinterpret_cast< const bitMask* >( str )+iter
        : nullptr;
}

    } // end containers namespace
} // end hamLibs namespace

#endif	/* __HL_TREE_COMMON_H__ */

