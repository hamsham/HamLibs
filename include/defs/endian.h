/* 
 * File:   endian.h
 * Author: hammy
 *
 * Created on March 13, 2013, 11:17 PM
 */

#ifndef __HL_ENDIAN_H__
#define __HL_ENDIAN_H__

#include <cstdint>

namespace hamLibs {
namespace utils {

/**
 * This enumeration can be placed into templated objects in order to generate
 * compile-time code based on a program's target endianness.
 *
 * The values placed in this enum are used just in case the need arises in
 * order to manually compare them against the number order in the
 * endianValues[] array.
 */
enum endian_t : uint32_t {
    HL_LITTLE_ENDIAN   = 0x00000001,
    HL_BIG_ENDIAN      = 0x01000000,
    HL_PDP_ENDIAN      = 0x00010000,
    HL_UNKNOWN_ENDIAN  = 0xFFFFFFFF
};

/**
 * A simple function that can be used to help determine a program's endianness
 * at compile-time.
 */
constexpr endian_t getEndianOrder() {
    return
        ((0xFFFFFFFF & 1) == HL_LITTLE_ENDIAN)
            ? HL_LITTLE_ENDIAN
            : ((0xFFFFFFFF & 1) == HL_BIG_ENDIAN)
                ? HL_BIG_ENDIAN
                : ((0xFFFFFFFF & 1) == HL_PDP_ENDIAN)
                    ? HL_PDP_ENDIAN
                    : HL_UNKNOWN_ENDIAN;
}

/**
 * Swap the bytes of an unsigned 16-bit integral type between big and little
 * endian representation. This function can be used at compile-time.
 * 
 * @param n
 * an unsigned integral type.
 * 
 * @return uint16_t
 * The value of the input parameter with its bytes swapped between big & little
 * endian representation.
 */
constexpr uint16_t btol(uint16_t n) {
    return (n >> 8) ^ (n << 8);
}

/**
 * Swap the bytes of a signed 16-bit integral type between big and little
 * endian representation. This function can be used at compile-time.
 * 
 * @param n
 * a signed integral type.
 * 
 * @return int16_t
 * The value of the input parameter with its bytes swapped between big & little
 * endian representation.
 */
constexpr int16_t btol(int16_t n) {
    return (int16_t)btol((uint16_t)n);
}

/**
 * Swap the bytes of an unsigned 32-bit integral type between big and little
 * endian representation. This function can be used at compile-time.
 * 
 * @param n
 * an unsigned integral type.
 * 
 * @return uint32_t
 * The value of the input parameter with its bytes swapped between big & little
 * endian representation.
 */
constexpr uint32_t btol(uint32_t n) {
    return
    (0x000000FF & (n >> 24)) ^
    (0x0000FF00 & (n >> 8)) ^
    (0x00FF0000 & (n << 8)) ^
    (0xFF000000 & (n << 24));
}

/**
 * Swap the bytes of a signed 32-bit integral type between big and little
 * endian representation. This function can be used at compile-time.
 * 
 * @param n
 * a signed integral type.
 * 
 * @return int32_t
 * The value of the input parameter with its bytes swapped between big & little
 * endian representation.
 */
constexpr int32_t btol(int32_t n) {
    return (int32_t)btol((uint32_t)n);
}

/**
 * Swap the bytes of an unsigned 64-bit integral type between big and little
 * endian representation. This function can be used at compile-time.
 * 
 * @param n
 * an unsigned integral type.
 * 
 * @return uint64_t
 * The value of the input parameter with its bytes swapped between big & little
 * endian representation.
 */
constexpr uint64_t btol(uint64_t n) {
    return
    (0x00000000000000FF & (n >> 56)) ^
    (0x000000000000FF00 & (n >> 40)) ^
    (0x0000000000FF0000 & (n >> 24)) ^
    (0x00000000FF000000 & (n >> 8)) ^
    (0x000000FF00000000 & (n << 8)) ^
    (0x0000FF0000000000 & (n << 24)) ^
    (0x00FF000000000000 & (n << 40)) ^
    (0xFF00000000000000 & (n << 56));
}

/**
 * Swap the bytes of a signed 64-bit integral type between big and little
 * endian representation. This function can be used at compile-time.
 * 
 * @param n
 * a signed integral type.
 * 
 * @return int64_t
 * The value of the input parameter with its bytes swapped between big & little
 * endian representation.
 */
constexpr int64_t btol(int64_t n) {
    return (int64_t)btol((uint64_t)n);
}

/**
 * Swap the bytes of a POD type between big and little endian representation.
 * 
 * @param n
 * A plain-old-data type.
 * 
 * @return numType
 * The value of the input parameter with its bytes swapped between big & little
 * endian representation.
 */
template <typename numType>
numType btol(numType n) {
    numType ret;
    unsigned char* const pIn = (unsigned char* const)&n;
    unsigned char* const pOut = (unsigned char* const)&ret;
    
    for (unsigned i = 0, j = sizeof(numType)-1; i < sizeof(numType); ++i, --j) {
        pOut[i] = pIn[j];
    }
    
    return ret;
}

} /* end utils namespace */
} /* End hamLibs namespace */

/**
 * Macro that should be used to always get the endianness of the current build
 * target.
 */
#define HL_ENDIANNESS hamLibs::utils::getEndianOrder()

#endif /* __HL_ENDIAN_H__ */
