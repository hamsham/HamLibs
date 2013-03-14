
#ifndef __ASSERT_H__
#define __ASSERT_H__

namespace hamLibs {
namespace utils {

enum errorType : int {
	ALERT,
	WARNING,
	ERROR
};

void assert_runtime( bool condition, errorType type, const char* msg );

#ifndef STRINGIFY
	#define STRINGIFY( x ) #x
#endif /* STRINGIFY */

/*
 * Basic Assertion Template
 */
#ifndef assert_basic
	#define assert_basic( x, lineNum, type )\
		assert_runtime(\
			x, type,\
			"Assertion failed on line " STRINGIFY( lineNum ) ". " STRINGIFY( x )\
		)
#endif /* assert_basic */

/* Assertion Types */
#ifndef ASSERT
	#define ASSERT( x ) assert_basic( x, __LINE__, utils::ERROR )
#endif /* ASSERT */

#ifndef ASSERT_FATAL
	#define ASSERT_FATAL( x ) ASSERT( x )
#endif /* ASSERT_FATAL */

#ifndef ASSERT_WARN
	#define ASSERT_WARN( x ) assert_basic( x, __LINE__, utils::WARNING )
#endif /* ASSERT_WARN */

#ifndef ASSERT_ALERT
	#define ASSERT_ALERT( x ) assert_basic( x, __LINE__, utils::ALERT )
#endif /* ASSERT_ALERT */

} /* End Utils namespace */
} /* End HamLibs namespace */

#endif /* __ASSERT_H__ */
