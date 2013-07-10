
#include "containers/tree_shared.h"

namespace hamLibs {
    namespace containers {

/*
 * Tree Bit Mask Specializations
template <>
const bitMask* treeShared::getKeyByte( const char* str, unsigned iter ) {
    return (str[ iter ] != '\0')
        ? reinterpret_cast< const bitMask* >( str+iter )
        : nullptr;
}

template <>
const bitMask* treeShared::getKeyByte( const wchar_t* str, unsigned iter ) {
    return (str[ iter ] != '\0')
        ? reinterpret_cast< const bitMask* >( str+iter )
        : nullptr;
}

template <>
const bitMask* treeShared::getKeyByte( const char16_t* str, unsigned iter ) {
    return (str[ iter ] != '\0')
        ? reinterpret_cast< const bitMask* >( str+iter )
        : nullptr;
}

template <>
const bitMask* treeShared::getKeyByte( const char32_t* str, unsigned iter ) {
    return (str[ iter ] != '\0')
        ? reinterpret_cast< const bitMask* >( str+iter )
        : nullptr;
}
 */

    } // end containers namespace
} // end hamLibs namespace
