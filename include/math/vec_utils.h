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

///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////
	namespace math {
//-----------------------------------------------------------------------------
// 2D Vectors
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType			dot( const vec2_t<numType>&, const vec2_t<numType>& );

template <typename numType> HL_IMPERATIVE vec2_t<numType>	normalize( const vec2_t<numType>& );

template <typename numType> HL_IMPERATIVE numType			magnitude( const vec2_t<numType>& );

template <typename numType> HL_IMPERATIVE vec2_t<numType>	rotate( const vec2_t<numType>&, numType );

template <typename numType> HL_IMPERATIVE numType			angleBetween( const vec2_t<numType>&, const vec2_t<numType>& );
template <typename numType> HL_IMPERATIVE numType			angleBetween( const vec2_t<numType>&, const vec2_t<numType>&, const vec2_t<numType>& origin );

//-----------------------------------------------------------------------------
// 3D Vectors
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType			dot( const vec3_t<numType>&, const vec3_t<numType>& );

template <typename numType> HL_IMPERATIVE vec3_t<numType>	cross( const vec3_t<numType>&, const vec3_t<numType>& );

template <typename numType> HL_IMPERATIVE vec3_t<numType>	normalize( const vec3_t<numType>& );

template <typename numType> HL_IMPERATIVE numType			magnitude( const vec3_t<numType>& );

template <typename numType> HL_IMPERATIVE vec3_t<numType>	xRotation( numType );
template <typename numType> HL_IMPERATIVE vec3_t<numType>	yRotation( numType );
template <typename numType> HL_IMPERATIVE vec3_t<numType>	zRotation( numType );

template <typename numType> HL_IMPERATIVE numType			angleBetween( const vec3_t<numType>&, const vec3_t<numType>& );
template <typename numType> HL_IMPERATIVE numType			angleBetween( const vec3_t<numType>&, const vec3_t<numType>&, const vec3_t<numType>& origin );

//-----------------------------------------------------------------------------
// 4D Vectors
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType			dot( const vec4_t<numType>&, const vec4_t<numType>& );

template <typename numType> HL_IMPERATIVE vec4_t<numType>	normalize( const vec4_t<numType>& );

template <typename numType> HL_IMPERATIVE numType			magnitude( const vec4_t<numType>& );

template <typename numType> HL_IMPERATIVE numType			angleBetween( const vec4_t<numType>&, const vec4_t<numType>& );
template <typename numType> HL_IMPERATIVE numType			angleBetween( const vec3_t<numType>&, const vec3_t<numType>&, const vec3_t<numType>& origin );

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////
	} // end math namespace
//-----------------------------------------------------------------------------
// 2D Vectors
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType math::dot( const vec2_t<numType>& v1, const vec2_t<numType>& v2 ) {
	return (v1.x*v2.x) + (v1.y*v2.y);
}

template <typename numType> HL_IMPERATIVE
math::vec2_t<numType> math::normalize( const vec2_t<numType>& v ) {
	numType magInv(
		numType(1) / HL_SQRT(
			(v.x * v.x)+
			(v.y * v.y)
		)
	);
	return vec2_t<numType>(
		v.x*magInv,
		v.y*magInv
	);
}

template <typename numType> HL_IMPERATIVE
numType math::magnitude( const vec2_t<numType>& v ) {
	return numType(
		HL_SQRT(
			(v.x * v.x) +
			(v.y * v.y)
		)
	);
}

template <typename numType> HL_IMPERATIVE
math::vec2_t<numType> math::rotate( const vec2_t<numType>& v, numType angle ) {
	numType s = sin(angle);
	numType c = cos(angle);

	return vec2_t<numType>(
		(v.x*c) - (v.y*s),
		(v.x*s) + (v.y*c)
	);
}

template <typename numType> HL_IMPERATIVE
numType math::angleBetween( const vec2_t<numType>& v1, const vec2_t<numType>& v2 ) {
	return numType( acos(
			dot( v1, v2 ) / ( magnitude( v1 )*magnitude( v2 ) )
	) );
}

template <typename numType> HL_IMPERATIVE
numType math::angleBetween( const vec2_t<numType>& v1, const vec2_t<numType>& v2, const vec2_t<numType>& origin ) {
	return numType( acos(
			dot( v1-origin, v2-origin ) / ( magnitude( v1 )*magnitude( v2 ) )
	) );
}

//-----------------------------------------------------------------------------
// 3D Vectors
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType math::dot( const vec3_t<numType>& v1, const vec3_t<numType>& v2 ) {
	return	(v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

template <typename numType> HL_IMPERATIVE
math::vec3_t<numType> math::cross( const vec3_t<numType>& v1, const vec3_t<numType>& v2 ) {
	return vec3_t<numType>(
		(v1.y*v2.z) - (v1.z*v2.y),
		(v1.z*v2.x) - (v1.x*v2.z),
		(v1.x*v2.y) - (v1.y*v2.x)
	);
}

template <typename numType> HL_IMPERATIVE
math::vec3_t<numType> math::normalize( const vec3_t<numType>& v ) {
	numType magInv(
		numType(1) / HL_SQRT(
			(v.x * v.x) +
			(v.y * v.y) +
			(v.z * v.z)
		)
	);
	return vec3_t<numType>(
		v.x*magInv,
		v.y*magInv,
		v.z*magInv
	);
}

template <typename numType> HL_IMPERATIVE
numType math::magnitude( const vec3_t<numType>& v ) {
	return numType(
		HL_SQRT(
			(v.x * v.x) +
			(v.y * v.y) +
			(v.z * v.z)
		)
	);
}

template <typename numType> HL_IMPERATIVE
math::vec3_t<numType> math::xRotation( numType angle ) {
	numType s = sin(angle);
	numType c = cos(angle);

	return vec3_t<numType>(
		numType(1),
		c + s,
		c - s
	);
}

template <typename numType> HL_IMPERATIVE
math::vec3_t<numType> math::yRotation( numType angle ) {
	numType s = sin(angle);
	numType c = cos(angle);

	return vec3_t<numType>(
		c - s,
		numType(1),
		s + c
	);
}

template <typename numType> HL_IMPERATIVE
math::vec3_t<numType> math::zRotation( numType angle ) {
	numType s = sin(angle);
	numType c = cos(angle);

	return vec3_t<numType>(
		c + s,
		c - s,
		numType(1)
	);
}

template <typename numType> HL_IMPERATIVE
numType math::angleBetween( const vec3_t<numType>& v1, const vec3_t<numType>& v2 ) {
	return numType( acos(
			dot( v1, v2 ) / ( magnitude( v1 )*magnitude( v2 ) )
	) );
}

template <typename numType> HL_IMPERATIVE
numType math::angleBetween( const vec3_t<numType>& v1, const vec3_t<numType>& v2, const vec3_t<numType>& origin ) {
	return numType( acos(
			dot( v1-origin, v2-origin ) / ( magnitude( v1 )*magnitude( v2 ) )
	) );
}

//-----------------------------------------------------------------------------
// 4D Vectors
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType math::dot( const vec4_t<numType>& v1, const vec4_t<numType>& v2 ) {
	return	(v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

template <typename numType> HL_IMPERATIVE
math::vec4_t<numType> math::normalize( const vec4_t<numType>& v ) {
	numType magInv(
		numType(1) / HL_SQRT(
			(v.x * v.x) +
			(v.y * v.y) +
			(v.z * v.z) +
			(v.w * v.w)
		)
	);
	return vec4_t<numType>(
		v.x*magInv,
		v.y*magInv,
		v.z*magInv,
		v.w*magInv
	);
}

template <typename numType> HL_IMPERATIVE
numType math::magnitude( const vec4_t<numType>& v ) {
	return numType(
		HL_SQRT(
			(v.x * v.x) +
			(v.y * v.y) +
			(v.z * v.z) +
			(v.w * v.w)
		)
	);
}

template <typename numType> HL_IMPERATIVE
numType math::angleBetween( const vec4_t<numType>& v1, const vec4_t<numType>& v2 ) {
	return numType( acos(
			dot( v1, v2 ) / ( magnitude( v1 )*magnitude( v2 ) )
	) );
}

template <typename numType> HL_IMPERATIVE
numType math::angleBetween( const vec4_t<numType>& v1, const vec4_t<numType>& v2, const vec4_t<numType>& origin ) {
	return numType( acos(
			dot( v1-origin, v2-origin ) / ( magnitude( v1 )*magnitude( v2 ) )
	) );
}

} // hamLibs namespace

#endif	/* __HL_VEC_UTILS_H__ */
