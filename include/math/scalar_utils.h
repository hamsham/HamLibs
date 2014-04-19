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

    #define HL_ROUND(x)     (std::floor(0.5 + x))
    #define HL_DEG2RAD(x)   (x * 0.01745329251994329577) // x * (PI / 180)
    #define HL_RAD2DEG(x)   (x * 57.2957795130823208768) // x * (180 / PI)

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

    #define HL_ROUND(x)		(std::floor(0.5f + x))
    #define HL_DEG2RAD(x)	(x * 0.01745329251994329577f) // x * (PI / 180)
    #define HL_RAD2DEG(x)	(x * 57.2957795130823208768f) // x * (180 / PI)

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

#define HL_SQRT(x)      std::sqrt(x)
#define HL_SIN(x)       std::sin(x)
#define HL_COS(x)       std::cos(x)
#define HL_TAN(x)       std::tan(x)

namespace hamLibs {

/*
 * Prototypes
 */
namespace math {

/**
 * max
 * Get the minimum of two single numbers
 * This function can be run at compile-time.
 * 
 * @param a
 * 
 * @param b
 * 
 * @return The largest number of the two parameters a and b.
 */
template <typename scalar_t>
constexpr scalar_t min(scalar_t a, scalar_t b);

/**
 * max
 * Get the maximum of two single numbers.
 * This function can be run at compile-time.
 * 
 * @param a
 * 
 * @param b
 * 
 * @return The largest number of the two parameters a and b.
 */
template <typename scalar_t>
constexpr scalar_t max(scalar_t a, scalar_t b);

/**
 * Perform a square root on a single number without using the standard library.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The square root of the input number.
 */
template <typename scalar_t>
inline scalar_t fastSqrt(scalar_t);

/**
 * Perform a square root on a single number without using the standard library.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The square root of the input number.
 */
template <>
inline float fastSqrt<float>(float);

/**
 * Get the inverse square root of a number.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The inverse square root (1/sqrt(x)) of the input number.
 */
template <typename scalar_t>
inline scalar_t fastInvSqrt(scalar_t);

/**
 * Get the inverse square root of a number.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The inverse square root (1/sqrt(x)) of the input number.
 */
template <>
inline float fastInvSqrt<float>(float);

/**
 * Convert a number from degrees to radians.
 * 
 * @param the value of an angle, in degrees.
 * 
 * @return the value of an angle, in radians.
 */
template <typename scalar_t>
constexpr scalar_t degToRad(scalar_t);

/**
 * Convert a number from radians to degrees.
 * This function can be run at compile-time.
 * 
 * @param the value of an angle, in radians.
 * 
 * @return the value of an angle, in degrees.
 */
template <typename scalar_t>
constexpr scalar_t radToDeg(scalar_t);

/**
 * Calculate the log-base2 of a number
 * @param a number
 * @return the log-base2 of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t fastLog2(scalar_t);

/**
 * Calculate the log-base2 of a number
 * @param a number
 * @return the log-base2 of a number, using IEEE floating point arithmetic
 */
template <>
inline float fastLog2<float>(float);

/**
 * Calculate the log-base10 of a number
 * @param a number
 * @return the log-base10 of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t fastLog(scalar_t);

/**
 * Calculate the log-base2 of a number
 * @param a number
 * @return the log-base2 of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t fastLogBase(scalar_t base, scalar_t);

/**
 * Find the next (greater) power of two that is closest to the value of a number
 * 
 * @param An unsigned integral type
 * 
 * @return The next greatest power of two.
 */
inline unsigned nextPow2(unsigned);

/**
 * Find the next (greater) power of two that is closest to the value of a number
 * 
 * @param A signed integral type
 * 
 * @return The next greatest power of two.
 */
inline int nextPow2(int);

/**
 * Find the previous (lesser) power of two that is closest to the value of a number
 * 
 * @param An unsigned integral type
 * 
 * @return The next lesser power of two.
 */
inline unsigned prevPow2(unsigned);

/**
 * Find the previous (lesser) power of two that is closest to the value of a number
 * 
 * @param A signed integral type
 * 
 * @return The next lesser power of two.
 */
inline int prevPow2(int);

/**
 * Find the closest power of two to a number. This may either be greater than
 * or less than the input number.
 * 
 * @param An unsigned integral type
 * 
 * @return The closest power of two to a number.
 */
inline unsigned nearPow2(unsigned);

/**
 * Find the closest power of two to a number. This may either be greater than
 * or less than the input number.
 * 
 * @param A signed integral type
 * 
 * @return The closest power of two to a number.
 */
inline int nearPow2(int);

/**
 * Determine if a number is a power of two or not.
 * 
 * @param A number who's value should be evaluated.
 * 
 * @return True if the number is a poiwer of two.
 * False if the number is not a power of two.
 */
constexpr bool isPow2(unsigned);

/**
 * Determine if a number is a power of two or not.
 * 
 * @param A number who's value should be evaluated.
 * 
 * @return True if the number is a poiwer of two.
 * False if the number is not a power of two.
 */
constexpr bool isPow2(int);

/**
 * Retrieve the factorial of a number
 * 
 * @param A number who's factorial is to be calculated.
 * 
 * @return The factorial of a given number.
 */
template <typename scalar_t>
constexpr scalar_t factorial(scalar_t);

/**
 * Evaluate a number to a given power.
 * 
 * @param A number who's power is to be evaluated.
 * 
 * @param The degree to which the first parameter's power should be evaluated.
 * 
 * @return A number, raised to a given power.
 */
template <typename scalar_t, typename int_t>
constexpr scalar_t pow(scalar_t, int_t);

/**
 * Evaluate the sine of an angle at compile-time.
 * 
 * @param An angle, in radians, who's sine value is to be calculated.
 * 
 * @return The sine of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t sin(scalar_t);

/**
 * Evaluate the cosine of an angle at compile-time.
 * 
 * @param An angle, in radians, who's cosine value is to be calculated.
 * 
 * @return The cosine of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t cos(scalar_t);

/**
 * Evaluate the tangent of an angle at compile-time.
 * 
 * @param An angle, in radians, who's tangent value is to be calculated.
 * 
 * @return The tangent of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t tan(scalar_t);

/**
 * Evaluate the sum of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be added together.
 * 
 * @return The sum of a set of numbers.
 */
template <typename scalar_t>
constexpr scalar_t sum(const scalar_t&);

/**
 * Evaluate the sum of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be added together.
 * 
 * @return The sum of a set of numbers.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t sum(const scalar_t& num, const scalars_t&... nums);

/**
 * Evaluate the average of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be averaged.
 * 
 * @return The average of a set of numbers.
 */
template <typename scalar_t>
constexpr scalar_t average();

/**
 * Evaluate the average of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be averaged.
 * 
 * @return The average of a set of numbers.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t average(const scalar_t& num, const scalars_t&... nums);

} // end math namespace

///////////////////////////////////////////////////////////////////////////////
// Function definitiona
///////////////////////////////////////////////////////////////////////////////
template <typename scalar_t> constexpr
scalar_t math::min(scalar_t a, scalar_t b) {
    return (a < b) ? a : b;
}

template <typename scalar_t> constexpr
scalar_t math::max(scalar_t a, scalar_t b) {
    return (a > b) ? a : b;
}

/*
 * Fast inverse square root method adopted for regular square rooting.
 * this method was found at:
 *		http://rrrola.wz.cz/inv_sqrt.html
 * and:
 *		http://jheriko-rtw.blogspot.com/2009/04/understanding-and-improving-fast.html
 */
template <typename scalar_t> inline
scalar_t math::fastInvSqrt(scalar_t input) {
    return (scalar_t) fastInvSqrt<float>((float) input);
}

template <typename scalar_t> inline
scalar_t math::fastSqrt(scalar_t input) {
    return scalar_t(1.0f / fastInvSqrt<scalar_t>(input));
}

template <> inline
float math::fastInvSqrt<float>(float x) {

    union {
        float f;
        unsigned int u;
    } y = {x};
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
}

template <> inline
float math::fastSqrt<float>(float input) {
    return float( 1.0f / fastInvSqrt<float>(input));
}

template <typename scalar_t> constexpr
scalar_t math::degToRad(scalar_t input) {
    return HL_DEG2RAD(input);
}

template <typename scalar_t> constexpr
scalar_t math::radToDeg(scalar_t input) {
    return HL_RAD2DEG(input);
}

/*
 * Fast Approximate logarithms
 * This method was found on flipcode:
 * http://www.flipcode.com/archives/Fast_log_Function.shtml
 * 
 * Accurate to within 5 decimal places.
 * This method relies on the IEEE floating point specification
 */
template <typename scalar_t> inline
scalar_t math::fastLog2(scalar_t n) {
    return (scalar_t) fastLog2<float>((float) n);
}

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

template <typename scalar_t> inline
scalar_t math::fastLog(scalar_t n) {
    return fastLog2<scalar_t>(n) * 0.693147181f; // ln( 2 )
}

template <typename scalar_t> inline
scalar_t math::fastLogBase(scalar_t base, scalar_t n) {
    return fastLog2<scalar_t>(n) / fastLog2<scalar_t>(base);
}

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

inline int math::nextPow2(int n) {
    return (int)nextPow2((unsigned)n);
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

inline int math::prevPow2(int n) {
    return (int)prevPow2((unsigned)n);
}

inline unsigned math::nearPow2(unsigned n) {
    const unsigned pp2 = prevPow2(n);
    const unsigned np2 = nextPow2(n);
    const unsigned lo = n - pp2;
    const unsigned hi = np2 - n;

    return lo < hi ? pp2 : np2;
}

inline int math::nearPow2(int n) {
    return (int)nearPow2((unsigned)n);
}

constexpr bool math::isPow2(unsigned n) {
    return n && !(n & (n-1));
}

constexpr bool math::isPow2(int n) {
    return (int)isPow2((unsigned)n);
}

template <typename scalar_t>
constexpr scalar_t math::factorial(scalar_t x) {
    return (1 < x) ? x*factorial(x-1) : 1;
}

template <typename scalar_t, typename int_t>
constexpr scalar_t math::pow(scalar_t x, int_t y) {
    return (0 < y) ? x * pow(x,y-1) : 1;
}

template <typename scalar_t>
constexpr scalar_t math::sin(scalar_t x) {
    return x
        -(x*x*x*scalar_t(1.f/6))
        +(x*x*x*x*x*scalar_t(1.f/120))
        -(x*x*x*x*x*x*x*scalar_t(1.f/5040))
        +(x*x*x*x*x*x*x*x*x*scalar_t(1.f/362880));
}

template <typename scalar_t>
constexpr scalar_t math::cos(scalar_t x) {
    return 1
        -(x*x*scalar_t(1.f/2))
        +(x*x*x*x*scalar_t(1.f/4))
        -(x*x*x*x*x*x*scalar_t(1.f/720))
        +(x*x*x*x*x*x*x*x*scalar_t(1.f/40320));
}

template <typename scalar_t>
constexpr scalar_t math::tan(scalar_t x) {
    return x
        +(x*x*x*scalar_t(1.f/3))
        +(x*x*x*x*x*scalar_t(2.f/15))
        +(x*x*x*x*x*x*x*scalar_t(17.f/315))
        +(x*x*x*x*x*x*x*x*x*scalar_t(62.f/2835));
}

template <typename scalar_t>
constexpr scalar_t sum(const scalar_t& num) {
    return num;
}

template <typename scalar_t, typename... scalars_t>
constexpr scalar_t sum(const scalar_t& num, const scalars_t&... nums) {
    return num + sum(nums...);
}

template <typename scalar_t>
constexpr scalar_t average() {
    return scalar_t(0);
}

template <typename scalar_t, typename... scalars_t>
constexpr scalar_t average(const scalar_t& num, const scalars_t&... nums) {
    return sum(num, nums...) / scalar_t(sizeof...(scalars_t)+1);
}

} /* end hamlibs namespace */

#endif	/* SCALAR_UTILS_H */
