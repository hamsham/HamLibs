
//preprocessor definitions

#ifdef DEBUG
	#include <cassert>
	#define HL_ASSERT(x) assert(x)
#else
	#define HL_ASSERT(x)
#endif

//inline function insurance
#if defined (_MSC_VER)
	#define HL_INLINE __forceinline
#elif defined (__GNUC__) || defined (__MINGW32__) || defined (__MINGW64__)
		#define HL_INLINE inline __attribute__((always_inline))
#else
	#define HL_INLINE inline
#endif
