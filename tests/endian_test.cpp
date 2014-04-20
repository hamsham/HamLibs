/* 
 * File:   endian test.cpp
 * Author: hammy
 *
 * Created on December 8, 2013, 9:15 PM
 */

#include <iostream>

#include "../include/hamLibs.h"

using hamLibs::utils::HL_UNKNOWN_ENDIAN;
using hamLibs::utils::HL_LITTLE_ENDIAN;
using hamLibs::utils::HL_BIG_ENDIAN;
using hamLibs::utils::HL_PDP_ENDIAN;

int main() {
    switch(HL_ENDIANNESS) {
        case HL_UNKNOWN_ENDIAN:
            std::cout << "HL_UNKNOWN_ENDIAN" << std::endl;
            break;
            
        case HL_LITTLE_ENDIAN:
            std::cout << "HL_LITTLE_ENDIAN" << std::endl;
            break;
            
        case HL_BIG_ENDIAN:
            std::cout << "HL_BIG_ENDIAN" << std::endl;
            break;
            
        case HL_PDP_ENDIAN:
            std::cout << "HL_PDP_ENDIAN" << std::endl;
            break;
            
        default:
            std::cout << "WTF" << std::endl;
    }
    
    return 0;
}

