
#include "containers/tree_common.h"

namespace hamLibs {
    namespace containers {

treeBase::~treeBase() {}

template <>
const bitMask* treeBase::getKeyByte( const char* str, unsigned iter ) {
    return (str[ iter ] != '\0')
        ? reinterpret_cast< const bitMask* >( str+iter )
        : nullptr;
}

    } // end containers namespace
} // end hamLibs namespace
