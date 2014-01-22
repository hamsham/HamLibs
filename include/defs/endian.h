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

/*
union endianValue {
    //constexpr uint8_t lsBit[ sizeof( uint32_t ) ] = {0,1,2,3};
    uint8_t lsBit[ sizeof( uint32_t ) ];
    uint32_t byteOrder;
    
    constexpr endianValue() :
        lsBit{0,1,2,3}
    {}
    constexpr endianValue(const endianValue&) = default;
    constexpr endianValue(endianValue&&) = default;
    
    ~endianValue() = default;
};

constexpr int checkEndianness() {
    return ( endianValue().byteOrder == 0x03020100 )        // If Little Endian Byte Order,
        ? HL_LITTLE_ENDIAN                                  // return 0 for little endian.
        : ( endianValue().byteOrder == 0x00010203 )     // Else if Big Endian Byte Order,
            ? HL_BIG_ENDIAN                                 // return 1 for big endian.
            : ( endianValue().byteOrder == 0x01000302 ) // Else if PDP Endian Byte Order,
                ? HL_PDP_ENDIAN                         // return 2 for pdp endian.
                : HL_UNKNOWN_ENDIAN;                    // Else return -1 for wtf endian.
}

constexpr static int HL_ENDIANNESS_CHECK = checkEndianness();
*/


enum e_endianness : int {
    HL_UNKNOWN_ENDIAN  = -1,
    HL_LITTLE_ENDIAN   = 0x03020100ul,
    HL_BIG_ENDIAN      = 0x00010203ul,
    HL_PDP_ENDIAN      = 0x01000302ul
};

static constexpr union {
    uint8_t lsBit[ sizeof( uint32_t ) ];
    uint32_t byteOrder;
} endianValue = {{0,1,2,3}};

#define HL_ENDIAN_ORDER (hamLibs::utils::endianValue.byteOrder)

} /* End Utils namespace */
} /* End HamLibs namespace */

#endif /* __HL_ENDIAN_H__ */
