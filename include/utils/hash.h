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

/*
 * The following are some useful compile-time string hashing functions.
 * Each function has an interface and an implementation.
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
constexpr unsigned long int hashDJB2_impl( const charType* str, unsigned int hashVal ) {
	return ( !*str )
	? hashVal
	: hashDJB2_impl( str+1, ((hashVal << 5) + hashVal) ^ *str );
}

/*
 * DJB2 Hashing Function
 */
template <typename charType>
constexpr unsigned long int hashDJB2( const charType* str ) {
	return ( !str ) ? 0 : hashDJB2_impl( str, 5381 );
}

/*
 * SDBM Hashing Implementation (Do not use)
 * This method was found here:
 * http://www.cse.yorku.ca/~oz/hash.html
 */
template <typename charType>
constexpr unsigned long int hashSDBM_impl( const charType* str, unsigned int hashVal ) {
    return ( !*str )
    ?   hashVal
    :   hashSDBM_impl( str+1, *str + (hashVal << 6) + (hashVal << 16) - hashVal );
}


/*
 * SDBM Hashing Function
 */
template <typename charType>
constexpr unsigned long int hashSDBM( const charType* str ) {
    return ( !str ) ? 0 : hashSDBM_impl( str, 65599 );
}

#define hashDJB2_ansi( x )  hashDJB2< char >( x )
#define hashDJB2_utf8( x )  hashDJB2< wchar_t >( x )
#define hashDJB2_utf16( x ) hashDJB2< char16_t >( x )
#define hashDJB2_utf32( x ) hashDJB2< char32_t >( x )

#define hashSDBM_ansi( x )  hashSDBM< char >( x )
#define hashSDBM_utf8( x )  hashSDBM< wchar_t >( x )
#define hashSDBM_utf16( x ) hashSDBM< char16_t >( x )
#define hashSDBM_utf32( x ) hashSDBM< char32_t >( x )

} // end utils namespace
} // end hamlibs namespace

#endif	/* __HL_HASH_H__ */

