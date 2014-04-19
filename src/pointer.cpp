/* 
 * File:   pointer.cpp
 * Author: miles
 * 
 * Created on April 19, 2014, 2:54 PM
 */

#include "../include/defs/preprocessor.h"
#include "../include/utils/pointer.h"

namespace hamLibs {
namespace utils {

HL_DEFINE_CLASS_TYPE(pointer, void*);

HL_DEFINE_CLASS_TYPE(pointer, char);
HL_DEFINE_CLASS_TYPE(pointer, unsigned char);

HL_DEFINE_CLASS_TYPE(pointer, short);
HL_DEFINE_CLASS_TYPE(pointer, unsigned short);

HL_DEFINE_CLASS_TYPE(pointer, int);
HL_DEFINE_CLASS_TYPE(pointer, unsigned int);

HL_DEFINE_CLASS_TYPE(pointer, long);
HL_DEFINE_CLASS_TYPE(pointer, unsigned long);

HL_DEFINE_CLASS_TYPE(pointer, long long);
HL_DEFINE_CLASS_TYPE(pointer, unsigned long long);

HL_DEFINE_CLASS_TYPE(pointer, float);
HL_DEFINE_CLASS_TYPE(pointer, double);
HL_DEFINE_CLASS_TYPE(pointer, long double);

} /* end utils namespace */
} /* end hamLibs namespace */
