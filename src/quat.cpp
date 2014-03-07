
#include "math/math.h"
#include "math/quat.h"

namespace hamLibs {
namespace math {

/*
 * Quaternion Specializations
 */
HL_DEFINE_CLASS_TYPE(quat_t, float);
HL_DEFINE_CLASS_TYPE(quat_t, double);
HL_DEFINE_CLASS_TYPE(quat_t, int);
HL_DEFINE_CLASS_TYPE(quat_t, medp_t);

} /* End math namespace */
} /* End hamLibs namespace */

