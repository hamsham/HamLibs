/* 
 * File:   fixed.h
 * Author: hammy
 *
 * Created on May 17, 2013, 6:02 AM
 */

#ifndef __HL_FIXED_H__
#define	__HL_FIXED_H__

#include "scalar_utils.h"

/*
 * NOTE:
 *      The fixed-point number class is still very experimental.
 *      In it's current state, it's very prone to overflows.
 *      Use at your own risk!
 */

namespace hamLibs {
namespace math {

template <typename fixedBase, unsigned fracDigits>
class fixed_t {
private:
    fixedBase number;

public:

    constexpr fixed_t() :
        number(0)
    {}

    constexpr fixed_t(const fixed_t& f) :
        number(f.number)
    {}

    constexpr fixed_t(fixedBase f) :
        number(f)
    {}

    constexpr fixed_t(float f) :
        number((fixedBase(1) << fracDigits) * f)
    {}

    ~fixed_t() = default;

    inline fixed_t& operator ++() {
        return *this = fixed_t(++number);
    }

    inline fixed_t& operator --() {
        return *this = fixed_t(--number);
    }

    inline fixed_t operator ++(int) {
        return fixed_t(++number);
    }

    inline fixed_t operator --(int) {
        return fixed_t(--number);
    }

    constexpr bool operator !() const {
        return !number;
    }

    constexpr bool operator ==(const fixed_t& f) const {
        return number == f.number;
    }

    constexpr bool operator !=(const fixed_t& f) const {
        return number != f.number;
    }

    constexpr bool operator >=(const fixed_t& f) const {
        return number >= f.number;
    }

    constexpr bool operator <=(const fixed_t& f) const {
        return number <= f.number;
    }

    constexpr bool operator>(const fixed_t& f) const {
        return number > f.number;
    }

    constexpr bool operator<(const fixed_t& f) const {
        return number < f.number;
    }

    constexpr fixed_t operator +(const fixed_t& f) const {
        return fixed_t(number + f.number);
    }

    constexpr fixed_t operator -(const fixed_t& f) const {
        return fixed_t(number - f.number);
    }

    constexpr fixed_t operator -() const {
        return fixed_t(-number);
    }

    constexpr fixed_t operator *(const fixed_t& f) const {
        return fixed_t(number * f.number);
    }

    constexpr fixed_t operator /(const fixed_t& f) const {
        return fixed_t(number / f.number);
    }

    constexpr fixed_t operator %(const fixed_t& f) const {
        return fixed_t(number % f.number);
    }

    constexpr fixed_t operator &(const fixed_t& f) const {
        return fixed_t(number & f.number);
    }

    constexpr fixed_t operator |(const fixed_t& f) const {
        return fixed_t(number | f.number);
    }

    constexpr fixed_t operator ^ (const fixed_t& f) const {
        return fixed_t(number ^ f.number);
    }

    constexpr fixed_t operator ~() const {
        return fixed_t(~number);
    }

    constexpr fixed_t operator >>(const fixed_t& f) const {
        return fixed_t(number >> f.number);
    }

    constexpr fixed_t operator <<(const fixed_t& f) const {
        return fixed_t(number << f.number);
    }

    inline fixed_t& operator =(const fixed_t& f) {
        number = f.number;
        return *this;
    }

    inline fixed_t& operator +=(const fixed_t& f) {
        number += f.number;
        return *this;
    }

    inline fixed_t& operator -=(const fixed_t& f) {
        number -= f.number;
        return *this;
    }

    inline fixed_t& operator *=(const fixed_t& f) {
        number *= f.number;
        return *this;
    }

    inline fixed_t& operator /=(const fixed_t& f) {
        number /= f.number;
        return *this;
    }

    inline fixed_t& operator %=(const fixed_t& f) {
        number %= f.number;
        return *this;
    }

    inline fixed_t& operator &=(const fixed_t& f) {
        number &= f.number;
        return *this;
    }

    inline fixed_t& operator |=(const fixed_t& f) {
        number |= f.number;
        return *this;
    }

    inline fixed_t& operator ^=(const fixed_t& f) {
        number ^= f.number;
        return *this;
    }

    inline fixed_t& operator >>=(const fixed_t& f) {
        number >>= f.number;
        return *this;
    }

    inline fixed_t& operator <<=(const fixed_t& f) {
        number <<= f.number;
        return *this;
    }

    constexpr operator float() {
        return float(1.f / (fixedBase(1) << fracDigits)) * number;
    }

    constexpr fixed_t& operator =(float f) {
        return *this = fixed_t(f);
    }
};

/*
 * Fixed-point specializations
 */
HL_DECLARE_CLASS_TYPE(lowp_t, fixed_t, int32_t, 7); // 24.7 (-1 for the sign-bit)
HL_DECLARE_CLASS_TYPE(lowp, fixed_t, HL_INT, 7);
HL_DECLARE_CLASS_TYPE(medp_t, fixed_t, int32_t, 15); // 16.15
HL_DECLARE_CLASS_TYPE(medp, fixed_t, HL_INT, 15);
HL_DECLARE_CLASS_TYPE(highp_t, fixed_t, int32_t, 23); // 8.23
HL_DECLARE_CLASS_TYPE(highp, fixed_t, HL_INT, 23);

HL_DECLARE_CLASS_TYPE(long_lowp_t, fixed_t, int64_t, 15); // 48.15
HL_DECLARE_CLASS_TYPE(long_medp_t, fixed_t, int64_t, 31); // 32.31
HL_DECLARE_CLASS_TYPE(long_highp_t, fixed_t, int64_t, 47); // 16.47

HL_DECLARE_CLASS_TYPE(ulowp_t, fixed_t, uint32_t, 8); // 24.8 (-1 for the sign-bit)
HL_DECLARE_CLASS_TYPE(ulowp, fixed_t, HL_INT, 8);
HL_DECLARE_CLASS_TYPE(umedp_t, fixed_t, uint32_t, 16); // 16.16
HL_DECLARE_CLASS_TYPE(umedp, fixed_t, HL_INT, 16);
HL_DECLARE_CLASS_TYPE(uhighp_t, fixed_t, uint32_t, 24); // 8.24
HL_DECLARE_CLASS_TYPE(uhigh, fixed_t, HL_INT, 24);

HL_DECLARE_CLASS_TYPE(ulong_lowp_t, fixed_t, uint64_t, 16); // 48.16
HL_DECLARE_CLASS_TYPE(ulong_medp_t, fixed_t, uint64_t, 32); // 32.32
HL_DECLARE_CLASS_TYPE(ulong_highp_t, fixed_t, uint64_t, 48); // 16.48

}//end math namespace
}//end hamlibs namespace

#endif	/* __HL_FIXED_H__ */

