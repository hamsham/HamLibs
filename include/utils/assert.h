
#ifndef __HL_ASSERT_H__
#define __HL_ASSERT_H__

#include "../defs/preprocessor.h"

namespace hamLibs {
namespace utils {

enum error_t : int {
	ALERT, // prints to std::cout
	WARNING, // prints to std::cerr
	ERROR // prints to std::cerr, throws an exception of type int
};

void runtime_assert(bool condition, error_t type, const char* const msg);

} /* End Utils namespace */
} /* End HamLibs namespace */

/*
 * Basic Assertion Template
 */
#ifndef HL_ASSERT_BASIC
	#define HL_ASSERT_BASIC( x, fileName, lineNum, type )\
		hamLibs::utils::runtime_assert(\
			(x), type,\
			"Assertion failed"\
            " on line " HL_STRINGIFY( lineNum )\
            " of " HL_STRINGIFY( fileName )\
            ": (" HL_STRINGIFY( x ) ")"\
		)
#endif /* HL_ASSERT_BASIC */

/* Assertion Types */
#ifndef HL_ASSERT
	#define HL_ASSERT( x ) HL_ASSERT_BASIC( x, __FILE__, __LINE__, hamLibs::utils::ERROR )
#endif /* ASSERT */

#ifdef HL_DEBUG
    #ifndef HL_DEBUG_ASSERT
    	#define HL_DEBUG_ASSERT( x ) HL_ASSERT( x )
    #endif
#else
    #define HL_DEBUG_ASSERT
#endif /* DEBUG */

#ifndef HL_WARN
	#define HL_WARN( x ) HL_ASSERT_BASIC( x, __FILE__, __LINE__, hamLibs::utils::WARNING )
#endif /* ASSERT_WARN */

#ifndef HL_ALERT
	#define HL_ALERT( x ) HL_ASSERT_BASIC( x, __FILE__, __LINE__, hamLibs::utils::ALERT )
#endif /* ASSERT_ALERT */

#endif /* __HL_ASSERT_H__ */
