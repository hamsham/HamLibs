
#include "math/math.h"
#include "math/matrix4.h"

namespace hamLibs {
namespace math {

/*
 * 4x4 Matrix Specializations
 */
HL_DEFINE_CLASS_TYPE(mat4_t, float);
HL_DEFINE_CLASS_TYPE(mat4_t, double);
HL_DEFINE_CLASS_TYPE(mat4_t, int);
HL_DEFINE_CLASS_TYPE(mat4_t, medp_t);

} /* End math namespace */
} /* End hamLibs namespace */
