
#include "math/math.h"
#include "math/fixed.h"

namespace hamLibs {
namespace math {

/*
 * Fixed-point specializations
 */
HL_DEFINE_CLASS_TYPE(fixed_t, int32_t, 7); // 24.7 (-1 for the sign-bit)
HL_DEFINE_CLASS_TYPE(fixed_t, int32_t, 15); // 16.15
HL_DEFINE_CLASS_TYPE(fixed_t, int32_t, 23); // 8.23

HL_DEFINE_CLASS_TYPE(fixed_t, int64_t, 15); // 48.15
HL_DEFINE_CLASS_TYPE(fixed_t, int64_t, 31); // 32.31
HL_DEFINE_CLASS_TYPE(fixed_t, int64_t, 47); // 16.47

HL_DEFINE_CLASS_TYPE(fixed_t, uint32_t, 8); // 24.8 (-1 for the sign-bit)
HL_DEFINE_CLASS_TYPE(fixed_t, uint32_t, 16); // 16.16
HL_DEFINE_CLASS_TYPE(fixed_t, uint32_t, 24); // 8.24

HL_DEFINE_CLASS_TYPE(fixed_t, uint64_t, 16); // 48.16
HL_DEFINE_CLASS_TYPE(fixed_t, uint64_t, 32); // 32.32
HL_DEFINE_CLASS_TYPE(fixed_t, uint64_t, 48); // 16.48

} /* End math namespace */
} /* End hamLibs namespace */
