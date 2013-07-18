/* 
 * File:   hash.h
 * Author: hammy
 *
 * Created on February 23, 2013, 12:01 PM
 */

#ifndef __HL_HASH_H__
#define	__HL_HASH_H__

#include <string>

namespace hamLibs {
namespace utils {

typedef unsigned long hashVal_t;

/*
 * The following are some useful compile-time string hashing functions.
 * Each function has an interface and an implementation.
 * Please ignore the magic numbers, they were found alongside each algorithm.
 * 
 * The functions have been made into templates in order to allow for the use
 * of the following types
 * const char*
 * const wchar_t*
 * const char16_t*
 * const char32_t*
 */

/*
 * DJB2 hash implementation
 * This method was found on here:
 * http://nguillemot.blogspot.com/2012/06/side-story-compile-time-string-hashing.html
 * 
 * this function is reserved for "hashDJB2()" and should not be used
 */
template <typename charType>
constexpr hashVal_t hashDJB2_impl( const charType* str, unsigned int hashVal ) {
	return ( !*str )
	? hashVal
	: hashDJB2_impl( str+1, ((hashVal << 5) + hashVal) ^ *str );
}

/*
 * DJB2 Hashing Function
 */
template <typename charType>
constexpr hashVal_t hashDJB2( const charType* str ) {
	return ( !str ) ? 0 : hashDJB2_impl( str, 5381 );
}

/*
 * SDBM Hashing Implementation
 * This method was found here:
 * http://www.cse.yorku.ca/~oz/hash.html
 */
template <typename charType>
constexpr hashVal_t hashSDBM_impl( const charType* str, unsigned int hashVal ) {
    return ( !*str )
    ?   hashVal
    :   hashSDBM_impl( str+1, *str + (hashVal << 6) + (hashVal << 16) - hashVal );
}

/*
 * SDBM Hashing Function
 */
template <typename charType>
constexpr hashVal_t hashSDBM( const charType* str ) {
    return ( !str ) ? 0 : hashSDBM_impl( str, 65599 );
}

/*
 * FNV-1a Hashing Function Implementation
 * This one was found here:
 * http://www.eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
*/
template <typename charType>
constexpr hashVal_t hashFNV1Recursive( const charType* str, unsigned int hashVal ) {
    return ( !*str )
    ?   hashVal
    :   hashFNV1Recursive( str+1, *str ^ (hashVal * 16777619) );
}

template <typename charType>
constexpr hashVal_t hashFNV1( const charType* str ) {
    return ( !str ) ? 0 : hashFNV1Recursive( str, 2166136261 );
}

/*
 * Hash Function Defines
 */
#define hashDJB2_ansi( x )  hashDJB2< char >( x )
#define hashDJB2_utf8( x )  hashDJB2< wchar_t >( x )
#define hashDJB2_utf16( x ) hashDJB2< char16_t >( x )
#define hashDJB2_utf32( x ) hashDJB2< char32_t >( x )

#define hashSDBM_ansi( x )  hashSDBM< char >( x )
#define hashSDBM_utf8( x )  hashSDBM< wchar_t >( x )
#define hashSDBM_utf16( x ) hashSDBM< char16_t >( x )
#define hashSDBM_utf32( x ) hashSDBM< char32_t >( x )

#define hashFNV1_ansi( x )  hashFNV1< char >( x )
#define hashFNV1_utf8( x )  hashFNV1< wchar_t >( x )
#define hashFNV1_utf16( x ) hashFNV1< char16_t >( x )
#define hashFNV1_utf32( x ) hashFNV1< char32_t >( x )

} // end utils namespace
} // end hamlibs namespace

#endif	/* __HL_HASH_H__ */

