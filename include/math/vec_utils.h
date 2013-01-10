/* 
 * File:   vec_utils.h
 * Author: hammy
 *
 * Created on January 8, 2013, 3:14 PM
 */

#ifndef __HL_VEC_UTILS_H__
#define	__HL_VEC_UTILS_H__

#include "math.h"

namespace hamLibs {
namespace math {

///////////////////////////////////////////////////////////////////////////////
// 2D Vectors
///////////////////////////////////////////////////////////////////////////////
template <typename numType> numType			dot( const vec2<numType>&, const vec2<numType>& );

template <typename numType> vec2<numType>	cross( const vec2<numType>&, const vec2<numType>& );

template <typename numType> vec2<numType>	normalize( const vec2<numType>& );

template <typename numType> numType			magnitude( const vec2<numType>& );

template <typename numType> vec2<numType>	rotate( const vec2<numType>&, numType );

template <typename numType> numType			angleBetween( const vec2<numType>&, const vec2<numType>& );

///////////////////////////////////////////////////////////////////////////////
// 3D Vectors
///////////////////////////////////////////////////////////////////////////////
template <typename numType> numType			dot( const vec3<numType>&, const vec3<numType>& );

template <typename numType> vec3<numType>	cross( const vec3<numType>&, const vec3<numType>& );

template <typename numType> vec3<numType>	normalize( const vec3<numType>& v ) {
	numType mag = hamLibs::math::fastInvSqrt(
		(v.x * v.x)+
		(v.y * v.y)+
		(v.z * v.z)
	);
	return vec3<numType>(
		v.x*mag,
		v.y*mag,
		v.z*mag
	);
}

template <typename numType> numType			magnitude( const vec3<numType>& );

template <typename numType> vec3<numType>	rotateX( const vec3<numType>&, numType );
template <typename numType> vec3<numType>	rotateY( const vec3<numType>&, numType );
template <typename numType> vec3<numType>	rotateZ( const vec3<numType>&, numType );

template <typename numType> numType			angleBetween( const vec3<numType>&, const vec3<numType>& );

///////////////////////////////////////////////////////////////////////////////
// 4D Vectors
///////////////////////////////////////////////////////////////////////////////
template <typename numType> numType			dot( const vec4<numType>&, const vec4<numType>& );

template <typename numType> vec4<numType>	cross( const vec4<numType>&, const vec4<numType>& );

template <typename numType> vec4<numType>	normalize( const vec4<numType>& );

template <typename numType> numType			magnitude( const vec4<numType>& );

template <typename numType> vec4<numType>	rotateX( const vec4<numType>&, numType );
template <typename numType> vec4<numType>	rotateY( const vec4<numType>&, numType );
template <typename numType> vec4<numType>	rotateZ( const vec4<numType>&, numType );

template <typename numType> numType			angleBetween( const vec4<numType>&, const vec4<numType>& );

} // math namespace
} // hamLibs namespace

#endif	/* __HL_VEC_UTILS_H__ */

