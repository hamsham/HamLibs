
/* Preprocessor Definitions & Directives */

#ifndef __HL_PREPROCESSOR_H__
#define __HL_PREPROCESSOR_H__

#include "setup.h"
#include "endian.h"

/******************************************************************************
		HamLibs Macros
******************************************************************************/
/*
 * Debug Mode
 */
#ifdef HL_DEBUG
	#include "../utils/assert.h"
	#define HL_ASSERT(x) ASSERT(x)
#else
	#define HL_ASSERT(x)
#endif

/*
 * Max/Min
 */
#define HL_MAX( x, y ) (( x > y) ? x : y )
#define HL_MIN( x, y ) (( x < y) ? x : y )

/*
 * Pointer Handling
 */
#define HL_NULL nullptr

/*
 * Floating Point Values & Precision
 */
#ifndef HL_FLOAT
	#define HL_FLOAT float
#endif

#define HL_SQRT( x ) std::sqrt( x )
//#define HL_SQRT( x ) hamLibs::math::fastSqrt( x )

/*
 * Preprocessor Stringify
 */
#ifndef HL_STRINGIFY
	#define HL_STRINGIFY( x ) #x
#endif /* HL_STRINGIFY */

#endif /* __HL_PREPROCESSOR_H__ */
