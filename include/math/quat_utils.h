/* 
 * File:   quat_utils.h
 * Author: hammy
 *
 * Created on January 8, 2013, 8:55 AM
 */

#ifndef __HL_QUAT_UTILS_H__
#define	__HL_QUAT_UTILS_H__

namespace hamLibs {
namespace math {

///////////////////////////////////////////////////////////////////////////////
//		Quaternion Functions
///////////////////////////////////////////////////////////////////////////////
template <typename numType> numType			dot( const quat<numType>&, const quat<numType>& );

template <typename numType> numType			magnitude( const quat<numType>& );

template <typename numType> quat<numType>	inverse( const quat<numType>& );

template <typename numType> quat<numType>	conjugate( const quat<numType>& );

template <typename numType> quat<numType>	normalize( const quat<numType>& );

///////////////////////////////////////////////////////////////////////////////
//		Quaternions & Matrices
///////////////////////////////////////////////////////////////////////////////
// 3x3 Matrices
template <typename numType> mat3<numType>	quatToMat3( const quat<numType>& );

// 4x4 Matrices
template <typename numType> mat4<numType>	quatToMat4( const quat<numType>& );

///////////////////////////////////////////////////////////////////////////////
//		Quaternions & Vectors
///////////////////////////////////////////////////////////////////////////////
template <typename numType> vec3<numType>	toVec( const quat<numType>& );
template <typename numType> vec4<numType>	toVec( const quat<numType>& );

///////////////////////////////////////////////////////////////////////////////
//		Quaternions & Euler Angles
///////////////////////////////////////////////////////////////////////////////
template <typename numType> numType			getAngle( const quat<numType>& );
template <typename numType> numType			pitch( const quat<numType>& );
template <typename numType> numType			yaw( const quat<numType>& );
template <typename numType> numType			roll( const quat<numType>& );

template <typename numType> vec3<numType>	toEuler( const quat<numType>& );

template <typename numType> void			toAxisAngle( const quat<numType>&, vec3<numType>&, numType& );
template <typename numType> vec4<numType>	toAxisAngle( const quat<numType>& );

template <typename numType> quat<numType>	fromAxisAngle( const vec3<numType>&, const numType& );
template <typename numType> quat<numType>	fromAxisAngle( const vec4<numType>& );

} // math namespace
} // hamLibs namespace

#endif	/* __HL_QUAT_UTILS_H__ */

