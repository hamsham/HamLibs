
/* Preprocessor Definitions & Directives */

#ifndef __HL_PREPROCESSOR_H__
#define __HL_PREPROCESSOR_H__

#include "setup.h"

/******************************************************************************
		HamLibs Macros
******************************************************************************/
/*
 * Debug Mode
 */
#ifdef HL_DEBUG
	#include <cassert>
	#define HL_ASSERT(x) assert(x)
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

#endif /* __HL_PREPROCESSOR_H__ */
