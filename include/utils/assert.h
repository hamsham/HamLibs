
#ifndef __HL_ASSERT_H__
#define __HL_ASSERT_H__

namespace hamLibs {
namespace utils {

enum errorType : int {
	ALERT, // prints to std::cout
	WARNING, // prints to std::cerr
	ERROR // prints to std::cerr, throws an exception of type int
};

void HL_API assert_runtime( bool condition, errorType type, const char* msg );

/*
 * Basic Assertion Template
 */
#ifndef assert_basic
	#define assert_basic( x, fileName, lineNum, type )\
		assert_runtime(\
			x, type,\
			"Assertion failed"\
            " on line " HL_STRINGIFY( lineNum )\
            " of " HL_STRINGIFY( fileName )\
            ": (" HL_STRINGIFY( x ) ")"\
		)
#endif /* assert_basic */

/* Assertion Types */
#ifndef ASSERT
	#define ASSERT( x ) assert_basic( x, __FILE__, __LINE__, utils::ERROR )
#endif /* ASSERT */

#ifndef ASSERT_FATAL
	#define ASSERT_FATAL( x ) ASSERT( x )
#endif /* ASSERT_FATAL */

#ifndef ASSERT_WARN
	#define ASSERT_WARN( x ) assert_basic( x, __FILE__, __LINE__, utils::WARNING )
#endif /* ASSERT_WARN */

#ifndef ASSERT_ALERT
	#define ASSERT_ALERT( x ) assert_basic( x, __FILE__, __LINE__, utils::ALERT )
#endif /* ASSERT_ALERT */

} /* End Utils namespace */
} /* End HamLibs namespace */

#endif /* __HL_ASSERT_H__ */
