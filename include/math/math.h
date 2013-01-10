//various math operations

#ifndef __HL_MATH_H__
#define __HL_MATH_H__

/*
 * NOTES:
 * All angle measurements used by this library are in radians
 * The Fixed-Point class is totally experimental and heavily relies on Allegro5
 */

#include <cmath>
#include "../defs/preprocessor.h"

#define HL_PI			3.14159265358979323846f
#define HL_TWO_PI		6.28318530717958647693f
#define HL_PI_OVR2		1.57079632679489661923f
#define HL_PI_OVR4		0.78539816339744830962f
#define HL_PI_INV		0.31830988618379067153f
#define HL_DEG2RAD(x)	(x * 0.01745329251994329577f) // x * (PI / 180)
#define HL_RAD2DEG(x)	(x * 57.2957795130823208768f) // x * (180 / PI)
#define HL_E			2.71828182845904523536f
#define HL_EPSILON		1.0e-5f
#define HL_ROUND(x)		(std::floor(x + 0.5f))

namespace hamLibs {
namespace math {
	//-------------------------------------------------------------
	//				Prototypes & Declarations
	//-------------------------------------------------------------
	//Multidimensional math classes
	template <class numType> class mat2;
	template <class numType> class mat3;
	template <class numType> class mat4;
	template <class numType> class quat;
	template <class numType> class vec2;
	template <class numType> class vec3;
	template <class numType> class vec4;
		
	template <typename numType>	numType fastSqrt(numType);
	template <typename numType>	numType fastInvSqrt(numType);
	template <typename numType>	numType degToRad(numType);
	template <typename numType>	numType radToDeg(numType);

	//-------------------------------------------------------------
	//				Definitions
	//-------------------------------------------------------------
	/* Fast inverse square root method adopted for regular square rooting.
	 * his method was found at:
	 *		http://rrrola.wz.cz/inv_sqrt.html
	 * and:
	 *		http://jheriko-rtw.blogspot.com/2009/04/understanding-and-improving-fast.html
	*/
	template <typename numType> HL_IMPERATIVE
	numType fastInvSqrt(numType input) {
		float x = static_cast<float>(input);
		union { float f; unsigned int u; } y = {x};
		y.u = 0x5F1FFFF9ul - (y.u >> 1);
		return (numType)(0.703952253f * y.f * (2.38924456f - x * y.f * y.f));
	}

	template <typename numType> HL_IMPERATIVE
	numType fastSqrt(numType input) {
		float x = static_cast<float>(input);
		union { float f; unsigned int u; } y = {x};
		y.u = 0x5F1FFFF9ul - (y.u >> 1);
		return (numType)1.0f/(0.703952253f * y.f * (2.38924456f - x * y.f * y.f));
	}

	//-----------------------------------------------------------------
	template <typename numType> HL_IMPERATIVE
	numType degToRad(numType input) {
		return HL_DEG2RAD(input);
	}

	//-----------------------------------------------------------------
	template <typename numType> HL_IMPERATIVE
	numType radToDeg(numType input) {
		return HL_RAD2DEG(input);
	}

}//end math namespace
}//end hamlibs namespace

//#include "math/fixed.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"
#include "quat.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

//#include "quat_utils.h"
#include "vec_utils.h"
#include "mat_utils.h"

#endif /* __HL_MATH_H__ */
