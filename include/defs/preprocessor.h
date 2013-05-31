
/* Preprocessor Definitions & Directives */

#ifndef __HL_PREPROCESSOR_H__
#define __HL_PREPROCESSOR_H__

#include "setup.h"
#include "endian.h"

/******************************************************************************
		HamLibs Macros
******************************************************************************/
/*
 * Preprocessor Stringify
 */
#ifndef HL_STRINGIFY
	#define HL_STRINGIFY( x ) #x
#endif /* HL_STRINGIFY */

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

#endif /* __HL_PREPROCESSOR_H__ */
