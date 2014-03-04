//various math operations

#ifndef __HL_MATH_H__
#define __HL_MATH_H__

/*
 * NOTES:
 * All angle measurements used by this library are in radians
 * I also use constructors rather than assignments when creating objects and
 * variables, so this might make readability slightly difficult at first.
 */

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
#define HL_SQRT( x )    sqrtf( x )

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
    namespace math {

        //-------------------------------------------------------------
        //				Prototypes & Declarations
        //-------------------------------------------------------------
        // Fixed-point numbers
        template <typename fixedBase, unsigned fracDigits> class fixed_t;

        //Multidimensional math classes
        template <class numType> class mat2_t;
        template <class numType> class mat3_t;
        template <class numType> class mat4_t;
        template <class numType> class quat_t;
        template <class numType> class vec2_t;
        template <class numType> class vec3_t;
        template <class numType> class vec4_t;

        template <typename numType> constexpr numType min(numType, numType);
        template <typename numType> constexpr numType max(numType, numType);

        template <typename numType> inline numType fastSqrt(numType);
        template <typename numType> inline numType fastInvSqrt(numType);
        template <> inline float fastSqrt< float >(float);
        template <> inline float fastInvSqrt< float >(float);

        template <typename numType> constexpr numType degToRad(numType);
        template <typename numType> constexpr numType radToDeg(numType);

        template <typename numType> inline numType fastLog2(numType);
        template <> inline float fastLog2< float >(float);
        template <typename numType> inline numType fastLog(numType);
        template <typename numType> inline numType fastLogBase(numType base, numType);

        inline unsigned nextPow2(unsigned);
        inline unsigned prevPow2(unsigned);
        inline unsigned nearPow2(unsigned);

        //-------------------------------------------------------------
        //				Definitions
        //-------------------------------------------------------------

        template <typename numType> constexpr
        numType min(numType a, numType b) {
            return (a < b) ? a : b;
        }

        template <typename numType> constexpr
        numType max(numType a, numType b) {
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
        numType fastInvSqrt(numType input) {
            return (numType) fastInvSqrt<float>((float) input);
        }

        //-----------------------------------------------------------------

        template <typename numType> inline
        numType fastSqrt(numType input) {
            return numType(1.0f / fastInvSqrt<numType>(input));
        }

        //-----------------------------------------------------------------

        template <> inline
        float fastInvSqrt< float >(float x) {

            union {
                float f;
                unsigned int u;
            } y = {x};
            y.u = 0x5F1FFFF9ul - (y.u >> 1);
            return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
        }

        //-----------------------------------------------------------------

        template <> inline
        float fastSqrt< float >(float input) {
            return float( 1.0f / fastInvSqrt<float>(input));
        }

        //-----------------------------------------------------------------

        template <typename numType> constexpr
        numType degToRad(numType input) {
            return HL_DEG2RAD(input);
        }

        //-----------------------------------------------------------------

        template <typename numType> constexpr
        numType radToDeg(numType input) {
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
        template < typename numType > inline
        numType fastLog2(numType n) {
            return (numType) fastLog2<float>((float) n);
        }

        //-----------------------------------------------------------------

        template <> inline
        float fastLog2< float >(float n) {
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

        template < typename numType > inline
        numType fastLog(numType n) {
            return fastLog2<numType>(n) * 0.693147181f; // ln( 2 )
        }

        //-----------------------------------------------------------------

        template < typename numType > inline
        numType fastLogBase(numType base, numType n) {
            return fastLog2<numType>(n) / fastLog2<numType>(base);
        }

        //-----------------------------------------------------------------

        inline unsigned nextPow2(unsigned n) {
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

        inline unsigned prevPow2(unsigned n) {
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

        inline unsigned nearPow2(unsigned n) {
            const unsigned pp2 = prevPow2(n);
            const unsigned np2 = nextPow2(n);
            const unsigned lo = n - pp2;
            const unsigned hi = np2 - n;

            return lo < hi ? pp2 : np2;
        }

    }//end math namespace
}//end hamlibs namespace

#include "fixed.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"
#include "quat.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "quat_utils.h"
#include "vec_utils.h"
#include "mat_utils.h"

#endif /* __HL_MATH_H__ */
