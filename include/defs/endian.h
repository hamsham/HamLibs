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

enum hl_endianness : uint32_t {
    HL_LITTLE_ENDIAN   = 0x03020100,
    HL_BIG_ENDIAN      = 0x00010203,
    HL_PDP_ENDIAN      = 0x01000302,
    HL_UNKNOWN_ENDIAN  = 0xFFFFFFFF
};

static constexpr uint8_t endianValues[4] = {0, 1, 2, 3};

constexpr hl_endianness getEndianOrder() {
    return
        (0x00 == endianValues[0])           // If Little Endian Byte Order,
            ? HL_LITTLE_ENDIAN              // return 0 for little endian.
            : (0x03 == endianValues[0])     // Else if Big Endian Byte Order,
                ? HL_BIG_ENDIAN             // return 1 for big endian.
                : (0x02 == endianValues[0]) // Else if PDP Endian Byte Order,
                    ? HL_PDP_ENDIAN         // return 2 for pdp endian.
                    : HL_UNKNOWN_ENDIAN;    // Else return -1 for wtf endian.
}

} /* End Utils namespace */
} /* End HamLibs namespace */

#endif /* __HL_ENDIAN_H__ */
