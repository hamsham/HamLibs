/* 
 * File:   scalar_utils.h
 * Author: miles
 *
 * Created on March 6, 2014, 10:04 PM
 */

#ifndef __HL_SCALAR_UTILS_H__
#define	__HL_SCALAR_UTILS_H__

#include <cmath>
#include <cstdint>
#include "../defs/preprocessor.h"

/*
 * Floating Point Values & Precision
 */
#ifdef HL_HIGH_PRECISION
#define HL_FLOAT        double
#define HL_INT          int64_t

#define HL_ROUND(x)     (std::floor(x + 0.5))
#define HL_DEG2RAD(x)   (x * 0.01745329251994329577) // x * (PI / 180)
#define HL_RAD2DEG(x)   (x * 57.2957795130823208768) // x * (180 / PI)
#define HL_SQRT( x )    sqrt( x )

#define HL_SIN(x)       std::sin(x)
#define HL_COS(x)       std::cos(x)
#define HL_TAN(x)       std::tan(x)

#define HL_PI           3.14159265358979323846
#define HL_TWO_PI       6.28318530717958647693
#define HL_PI_OVER_2    1.57079632679489661923
#define HL_PI_OVER_3    1.04719755119659774615
#define HL_PI_OVER_4    0.78539816339744830962
#define HL_PI_OVER_6    0.52359877559829887307
#define HL_PI_INVERSE   0.31830988618379067153 // 1 / pi
#define HL_E            2.71828182845904523536
#define HL_EPSILON      1.0e-9
#else
#define HL_FLOAT        float
#define HL_INT          int32_t

#define HL_ROUND(x)		(std::floor(x + 0.5f))
#define HL_DEG2RAD(x)	(x * 0.01745329251994329577f) // x * (PI / 180)
#define HL_RAD2DEG(x)	(x * 57.2957795130823208768f) // x * (180 / PI)
#define HL_SQRT(x)      std::sqrt(x)

#define HL_SIN(x)       std::sin(x)
#define HL_COS(x)       std::cos(x)
#define HL_TAN(x)       std::tan(x)

#define HL_PI           3.14159265358979323846f
#define HL_TWO_PI       6.28318530717958647693f
#define HL_PI_OVER_2    1.57079632679489661923f
#define HL_PI_OVER_3    1.04719755119659774615f
#define HL_PI_OVER_4    0.78539816339744830962f
#define HL_PI_OVER_6    0.52359877559829887307f
#define HL_PI_INVERSE   0.31830988618379067153f // 1 / pi
#define HL_E            2.71828182845904523536f
#define HL_EPSILON      1.0e-5f
#endif

namespace hamLibs {

/*
 * Prototypes
 */
namespace math {

template <typename numType> constexpr numType   min(numType, numType);
template <typename numType> constexpr numType   max(numType, numType);

template <typename numType> inline numType      fastSqrt(numType);
template <typename numType> inline numType      fastInvSqrt(numType);
template <> inline float                        fastSqrt<float>(float);
template <> inline float                        fastInvSqrt<float>(float);

template <typename numType> constexpr numType   degToRad(numType);
template <typename numType> constexpr numType   radToDeg(numType);

template <typename numType> inline numType      fastLog2(numType);
template <> inline float                        fastLog2<float>(float);
template <typename numType> inline numType      fastLog(numType);
template <typename numType> inline numType      fastLogBase(numType base, numType);

inline unsigned                                 nextPow2(unsigned);
inline unsigned                                 prevPow2(unsigned);
inline unsigned                                 nearPow2(unsigned);

template <typename scalar_t> constexpr scalar_t factorial(scalar_t);

template <typename scalar_t, typename int_t> constexpr scalar_t pow(scalar_t, int_t);

template <typename scalar_t> constexpr scalar_t sin(scalar_t);
template <typename scalar_t> constexpr scalar_t cos(scalar_t);
template <typename scalar_t> constexpr scalar_t tan(scalar_t);

} // end math namespace

///////////////////////////////////////////////////////////////////////////////
// Function definitiona
///////////////////////////////////////////////////////////////////////////////
template <typename numType> constexpr
numType math::min(numType a, numType b) {
    return (a < b) ? a : b;
}

template <typename numType> constexpr
numType math::max(numType a, numType b) {
    return (a > b) ? a : b;
}

//-----------------------------------------------------------------

/* Fast inverse square root method adopted for regular square rooting.
 * this method was found at:
 *		http://rrrola.wz.cz/inv_sqrt.html
 * and:
 *		http://jheriko-rtw.blogspot.com/2009/04/understanding-and-improving-fast.html
 */
template <typename numType> inline
numType math::fastInvSqrt(numType input) {
    return (numType) fastInvSqrt<float>((float) input);
}

//-----------------------------------------------------------------

template <typename numType> inline
numType math::fastSqrt(numType input) {
    return numType(1.0f / fastInvSqrt<numType>(input));
}

//-----------------------------------------------------------------

template <> inline
float math::fastInvSqrt<float>(float x) {

    union {
        float f;
        unsigned int u;
    } y = {x};
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
}

//-----------------------------------------------------------------

template <> inline
float math::fastSqrt<float>(float input) {
    return float( 1.0f / fastInvSqrt<float>(input));
}

//-----------------------------------------------------------------

template <typename numType> constexpr
numType math::degToRad(numType input) {
    return HL_DEG2RAD(input);
}

//-----------------------------------------------------------------

template <typename numType> constexpr
numType math::radToDeg(numType input) {
    return HL_RAD2DEG(input);
}

//-----------------------------------------------------------------

/*
 * Fast Approximate logarithms
 * This method was found on flipcode:
 * http://www.flipcode.com/archives/Fast_log_Function.shtml
 * 
 * Accurate to within 5 decimal places.
 * This method relies on the IEEE floating point specification
 */
template <typename numType> inline
numType math::fastLog2(numType n) {
    return (numType) fastLog2<float>((float) n);
}

//-----------------------------------------------------------------

template <> inline
float math::fastLog2<float>(float n) {
    int* const exp = reinterpret_cast<int*> (&n);
    int x = *exp;

    const int log2 = ((x >> 23) & 255) - 128;

    x &= ~(255 << 23);
    x += 127 << 23;

    *exp = x;
    n = ((-1.f / 3.f) * n + 2.f) * n - 2.f / 3.f;
    return n + log2;
}

//-----------------------------------------------------------------

template <typename numType> inline
numType math::fastLog(numType n) {
    return fastLog2<numType>(n) * 0.693147181f; // ln( 2 )
}

//-----------------------------------------------------------------

template <typename numType> inline
numType math::fastLogBase(numType base, numType n) {
    return fastLog2<numType>(n) / fastLog2<numType>(base);
}

//-----------------------------------------------------------------

inline unsigned math::nextPow2(unsigned n) {
    if (n == 0) {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return ++n;
}

inline unsigned math::prevPow2(unsigned n) {
    if (n == 0) {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

inline unsigned math::nearPow2(unsigned n) {
    const unsigned pp2 = prevPow2(n);
    const unsigned np2 = nextPow2(n);
    const unsigned lo = n - pp2;
    const unsigned hi = np2 - n;

    return lo < hi ? pp2 : np2;
}

//-----------------------------------------------------------------

template <typename scalar_t>
constexpr scalar_t math::factorial(scalar_t x) {
    return (1 < x) ? x*factorial(x-1) : 1;
}

//-----------------------------------------------------------------

template <typename scalar_t, typename int_t>
constexpr scalar_t math::pow(scalar_t x, int_t y) {
    return (0 < y) ? x * pow(x,y-1) : 1;
}

//-----------------------------------------------------------------

template <typename scalar_t>
constexpr scalar_t math::sin(scalar_t x) {
    return x
        -(x*x*x*scalar_t(1.0/6))
        +(x*x*x*x*x*scalar_t(1.0/120))
        -(x*x*x*x*x*x*x*scalar_t(1.0/5040))
        +(x*x*x*x*x*x*x*x*x*scalar_t(1.0/362880));
}

template <typename scalar_t>
constexpr scalar_t math::cos(scalar_t x) {
    return 1
        -(x*x*scalar_t(1.0/2))
        +(x*x*x*x*scalar_t(1.0/4))
        -(x*x*x*x*x*x*scalar_t(1.0/720))
        +(x*x*x*x*x*x*x*x*scalar_t(1.0/40320));
}

template <typename scalar_t>
constexpr scalar_t math::tan(scalar_t x) {
    return x
        +(x*x*x*scalar_t(1.0/3))
        +(x*x*x*x*x*scalar_t(2.0/15))
        +(x*x*x*x*x*x*x*scalar_t(17.0/315))
        +(x*x*x*x*x*x*x*x*x*scalar_t(62.0/2835));
}

} /* end hamlibs namespace */

#endif	/* SCALAR_UTILS_H */
