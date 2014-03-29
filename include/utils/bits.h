/* 
 * File:   bits.h
 * Author: hammy
 *
 * Created on June 21, 2013, 1:31 AM
 */

#ifndef __HL_BITS_H__
#define	__HL_BITS_H__

#include <climits>
#include "../utils/assert.h"

#ifndef HL_BITS_PER_BYTE
#define HL_BITS_PER_BYTE CHAR_BIT
#endif

namespace hamLibs {
namespace utils {

/*
 *  Convenience structure to facilitate bit acquisition of bytes
 */
struct alignas(1) bitMask {
    char byte = 0;

    constexpr int get(int i) {
        return (byte >> i) & 1;
    }

    inline void set(int i, int val) {
        byte = (byte & ~(1 << i)) | (val << i);
    }
};

/*
 *  Functions allowing access to individual bytes
 */
// Function to retrieve the next set of bits at the pointer "key"
template <typename key_t>
constexpr const bitMask* getByte(const key_t* key, unsigned iter);

/* template specializations */
template <>
constexpr const bitMask* getByte(const char*, unsigned);

template <>
constexpr const bitMask* getByte(const wchar_t*, unsigned);

template <>
constexpr const bitMask* getByte(const char16_t*, unsigned);

template <>
constexpr const bitMask* getByte(const char32_t*, unsigned);

/*
 * Bit Mask Function
 */
template <typename key_t>
constexpr const bitMask* getByte(const key_t* k, unsigned iter) {
    return (iter < sizeof (k))
            ? reinterpret_cast<const bitMask*> (k) + iter
            : nullptr;
}

template <>
constexpr const bitMask* getByte(const char* str, unsigned iter) {
    return (str[ iter / sizeof (char) ] != '\0')
            ? reinterpret_cast<const bitMask*> (str) + iter
            : nullptr;
}

template <>
constexpr const bitMask* getByte(const wchar_t* str, unsigned iter) {
    return (str[ iter / sizeof (wchar_t) ] != '\0')
            ? reinterpret_cast<const bitMask*> (str) + iter
            : nullptr;
}

template <>
constexpr const bitMask* getByte(const char16_t* str, unsigned iter) {
    return (str[ iter / sizeof (char16_t) ] != '\0')
            ? reinterpret_cast<const bitMask*> (str) + iter
            : nullptr;
}

template <>
constexpr const bitMask* getByte(const char32_t* str, unsigned iter) {
    return (str[ iter / sizeof (char32_t) ] != '\0')
            ? reinterpret_cast<const bitMask*> (str) + iter
            : nullptr;
}

} // end utils namespace
} // end hamLibs namespace

#endif	/* __HL_BITS_H__ */

