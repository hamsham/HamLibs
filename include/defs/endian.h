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
        ((1 & 0xFFFFFFFF) == HL_LITTLE_ENDIAN)
            ? HL_LITTLE_ENDIAN
            : ((1 & 0xFFFFFFFF) == HL_BIG_ENDIAN)
                ? HL_BIG_ENDIAN
                : ((1 & 0xFFFFFFFF) == HL_PDP_ENDIAN)
                    ? HL_PDP_ENDIAN
                    : HL_UNKNOWN_ENDIAN;
}

} /* end utils namespace */
} /* End hamLibs namespace */

/**
 * Macro that should be used to always get the endianness of the current build
 * target.
 */
#define HL_ENDIANNESS hamLibs::utils::getEndianOrder()

#endif /* __HL_ENDIAN_H__ */
