/* 
 * File:   mat_utils.h
 * Author: hammy
 *
 * Created on January 8, 2013, 3:48 PM
 */

#ifndef __HL_MAT_UTILS_H__
#define	__HL_MAT_UTILS_H__

#include "math.h"

namespace hamLibs {
namespace math {

///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////
	
//-----------------------------------------------------------------------------
//2x2 Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType		determinant( const mat2<numType>& );

template <typename numType> HL_IMPERATIVE mat2<numType>	inverse( const mat2<numType>& );

template <typename numType> HL_IMPERATIVE mat2<numType>	transpose( const mat2<numType>& );

template <typename numType> HL_IMPERATIVE mat2<numType>	rotate( const mat2<numType>&, numType );

template <typename numType> HL_IMPERATIVE mat2<numType>	scale( const mat2<numType>&, const vec2<numType>& );
	
//-----------------------------------------------------------------------------
// 3x3 Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType		determinant( const mat3<numType>& );

template <typename numType> HL_IMPERATIVE mat3<numType>	inverse( const mat3<numType>& );

template <typename numType> HL_IMPERATIVE mat3<numType>	transpose( const mat3<numType>& );

template <typename numType> HL_IMPERATIVE mat3<numType>	rotate( const mat3<numType>&, const vec3<numType>&, numType );

template <typename numType> HL_IMPERATIVE mat3<numType>	scale( const mat3<numType>&, const vec3<numType>& );

//-----------------------------------------------------------------------------
// 4x4 Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType		determinant( const mat4<numType>& );

template <typename numType> HL_IMPERATIVE mat4<numType>	inverse( const mat4<numType>& );

template <typename numType> HL_IMPERATIVE mat4<numType>	transpose( const mat4<numType>& );

template <typename numType> HL_IMPERATIVE mat4<numType>	rotate( const mat4<numType>&, const vec3<numType>&, numType );

template <typename numType> HL_IMPERATIVE mat4<numType>	scale( const mat4<numType>&, const vec3<numType>& );

template <typename numType> HL_IMPERATIVE mat4<numType>	translate( const mat4<numType>&, const vec3<numType>& );

template <typename numType> HL_IMPERATIVE mat4<numType>	perspective( numType fov, numType aspect, numType zNear, numType zFar );

template <typename numType> HL_IMPERATIVE mat4<numType>	ortho( numType top, numType bottom, numType left, numType right );

template <typename numType> HL_IMPERATIVE mat4<numType>	lookAt( const vec3<numType>& pos, const vec3<numType>& target, const vec3<numType>& up );

template <typename numType> HL_IMPERATIVE mat4<numType>	frustum( numType top, numType bottom, numType left, numType right, numType near, numType far );

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////
	
//-----------------------------------------------------------------------------
//2x2 Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType determinant( const mat2<numType>& m ) {
	return (m.xx*m.yy) - (m.xy*m.yx);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> inverse( const mat2<numType>& m ) {
	numType determinantInv(
		numType( 1 ) / ( (m.xx * m.yy) - (m.xy * m.yx) )
	);
	
	return mat2<numType>(
		m.yy * determinantInv, m.xy * determinantInv,
		m.yx * determinantInv, m.xx * determinantInv
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> transpose( const mat2<numType>& m ) {
	return mat2<numType>(
		m.xx, m.yx,
		m.xy, m.yy
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> rotate( const mat2<numType>& m, numType angle ) {
	numType c( std::cos( angle ) );
	numType s( std::sin( angle ) );
	return mat2<numType>(
		m.xx = m.xx * c,	m.xy = m.xy * s,
		m.yx = -m.yx * s,	m.yy = m.yy * c
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> scale( const mat2<numType>& m, const vec2<numType>& amount ) {
	return mat2<numType>(
		m.xx*amount.x, m.xy,
		m.yx, m.yy*amount.y
	);
}
	
//-----------------------------------------------------------------------------
// 3x3 Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType determinant( const mat3<numType>& m ) {
	return ( (m.xx*m.yy*m.zz) + (m.xy*m.yz*m.zx) + (m.xz*m.yx*m.zy) ) -
		( (m.xz*m.yy*m.zx) + (m.xy*m.yx*m.zz) + (m.xx*m.yz*m.zy) );
}

template <typename numType> HL_IMPERATIVE
mat3<numType> inverse( const mat3<numType>& m ) {
	return
	mat3<numType>(
		m.xx, m.yx, m.zx,
		m.xy, m.yy, m.zy,
		m.xz, m.yz, m.zz )
	* ( numType( 1 ) / determinant( m ) );
}

template <typename numType> HL_IMPERATIVE
mat3<numType> transpose( const mat3<numType>& m ) {
	return mat3<numType>(
		m.xx, m.yx, m.zx,
		m.xy, m.yy, m.zy,
		m.xz, m.yz, m.zz );
}

template <typename numType> HL_IMPERATIVE
mat3<numType> rotate( const mat3<numType>& m, const vec3<numType>& axis, numType angle ) {
	numType			c( std::cos(angle) ), s( std::sin(angle) );
	vec3<numType>	a( normalize(axis) );
	numType			omc( numType(1) - c );
	numType			xy( (a.x*a.y)*omc ), yz( (a.y*a.z)*omc ), zx( (a.z*a.x)*omc );
	numType			sx( s*a.x ), sy( s*a.y ), sz( s*a.z );
	
	return mat3<numType>(
		m.xx * ( c+((a.x*a.x) * omc )), m.xy * ( xy - sz ), m.xz * ( zx + sy ),
		m.yx * ( xy + sz ), m.yy * ( c+((a.y*a.y) * omc) ), m.yz * ( yz - sx ),
		m.zx * ( zx - sy ), m.zy * ( yz + sx ), m.zz * ( c+((a.z*a.z) * omc ))
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> scale( const mat3<numType>& m, const vec3<numType>& scale ) {
	return mat3<numType>(
		m.xx*scale.x, m.xy, m.xz,
		m.yx, m.yy*scale.y, m.yz,
		m.zx, m.zy, m.zz*scale.z
	);
}
	
//-----------------------------------------------------------------------------
// 4x4 Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType determinant( const mat4<numType>& m ) {
	return numType(
		( m.xw*m.yz*m.zy*m.wx ) - ( m.xz*m.yw*m.zy*m.wx ) - ( m.xw*m.yy*m.zz*m.wx ) + ( m.xy*m.yw*m.zz*m.wx ) +
		( m.xz*m.yy*m.zw*m.wx ) - ( m.xy*m.yz*m.zw*m.wx ) - ( m.xw*m.yz*m.zx*m.wy ) + ( m.xz*m.yw*m.zx*m.wy ) +
		( m.xw*m.yx*m.zz*m.wy ) - ( m.xx*m.yw*m.zz*m.wy ) - ( m.xz*m.yx*m.zw*m.wy ) + ( m.xx*m.yz*m.zw*m.wy ) +
		( m.xw*m.yy*m.zx*m.wz ) - ( m.xy*m.yw*m.zx*m.wz ) - ( m.xw*m.yx*m.zy*m.wz ) + ( m.xx*m.yw*m.zy*m.wz ) +
		( m.xy*m.yx*m.zw*m.wz ) - ( m.xx*m.yy*m.zw*m.wz ) - ( m.xz*m.yy*m.zx*m.ww ) + ( m.xy*m.yz*m.zx*m.ww ) +
		( m.xz*m.yx*m.zy*m.ww ) - ( m.xx*m.yz*m.zy*m.ww ) - ( m.xy*m.yx*m.zz*m.ww ) + ( m.xx*m.yy*m.zz*m.ww )
	);
	//umm... wow
}

template <typename numType> HL_IMPERATIVE
mat4<numType> inverse( const mat4<numType>& m ) {
	
	//these operations appear only 2 times in the return value
	numType zwwx( m.zw * m.wx );
	
	//these operations appear 3 times in the return value
	numType xxyy( m.xx * m.yy );
	numType xxyz( m.xx * m.yz );
	numType xzyy( m.xz * m.yy );
	numType xyyz( m.xy * m.yz );
	numType zwwy( m.zw * m.wy );
	numType zwwz( m.zw * m.wz );
	
	//these operations appear 4 times in the return value
	numType xxyw( m.xx * m.yw );
	numType xyyx( m.xy * m.yx );
	numType xyyw( m.xy * m.yw );
	numType xzyx( m.xz * m.yx );
	numType xzyw( m.xz * m.yw );
	numType xwyx( m.xw * m.yx );
	numType xwyy( m.xw * m.yy );
	numType xwyz( m.xw * m.yz );
	numType yyzw( m.yy * m.zw );
	numType yzzw( m.yz * m.zw );
	numType zxwy( m.zx * m.wy );
	numType zxwz( m.zx * m.wz );
	numType zxww( m.zx * m.ww );
	numType zywx( m.zy * m.wx );
	numType zywz( m.zy * m.wz );
	numType zyww( m.zy * m.ww );
	numType zzwx( m.zz * m.wx );
	numType zzwy( m.zz * m.wy );
	numType zzww( m.zz * m.ww );
	
	return mat4<numType>(
		( yzzw*m.wy ) - ( m.yw*zzwy ) + ( m.yw*zywz ) - ( yyzw*m.wz ) - ( m.yz*zyww ) + ( m.yy*zzww ),
		( m.xw*zzwy ) - ( m.xz*zwwy ) - ( m.xw*zywz ) + ( m.xy*zwwz ) + ( m.xz*zyww ) - ( m.xy*zzww ),
		( xzyw*m.wy ) - ( xwyz*m.wy ) + ( xwyy*m.wz ) - ( xyyw*m.wz ) - ( xzyy*m.ww ) + ( xyyz*m.ww ),
		( xwyz*m.zy ) - ( xzyw*m.zy ) - ( xwyy*m.zz ) + ( xyyw*m.zz ) + ( m.xz*yyzw ) - ( m.xy*yzzw ),
		( m.yw*zzwx ) - ( yzzw*m.wx ) - ( m.yw*zxwz ) + ( m.yx*zwwz ) + ( m.yz*zxww ) - ( m.yx*zzww ),
		( m.xz*zwwx ) - ( m.xw*zzwx ) + ( m.xw*zxwz ) - ( m.xx*zwwz ) - ( m.xz*zxww ) + ( m.xx*zzww ),
		( xwyz*m.wx ) - ( xzyw*m.wx ) - ( xwyx*m.wz ) + ( xxyw*m.wz ) + ( xzyx*m.ww ) - ( xxyz*m.ww ),
		( xzyw*m.zx ) - ( xwyz*m.zx ) + ( xwyx*m.zz ) - ( xxyw*m.zz ) - ( xzyx*m.zw ) + ( m.xx*yzzw ),
		( yyzw*m.wx ) - ( m.yw*zywx ) + ( m.yw*zxwy ) - ( m.yx*zwwy ) - ( m.yy*zxww ) + ( m.yx*zyww ),
		( m.xw*zywx ) - ( m.xy*zwwx ) - ( m.xw*zxwy ) + ( m.xx*zwwy ) + ( m.xy*zxww ) - ( m.xx*zyww ),
		( xyyw*m.wx ) - ( xwyy*m.wx ) + ( xwyx*m.wy ) - ( xxyw*m.wy ) - ( xyyx*m.ww ) + ( xxyy*m.ww ),
		( xwyy*m.zx ) - ( xyyw*m.zx ) - ( xwyx*m.zy ) + ( xxyw*m.zy ) + ( xyyx*m.zw ) - ( m.xx*yyzw ),
		( m.yz*zywx ) - ( m.yy*zzwx ) - ( m.yz*zxwy ) + ( m.yx*zzwy ) + ( m.yy*zxwz ) - ( m.yx*zywz ),
		( m.xy*zzwx ) - ( m.xz*zywx ) + ( m.xz*zxwy ) - ( m.xx*zzwy ) - ( m.xy*zxwz ) + ( m.xx*zywz ),
		( xzyy*m.wx ) - ( xyyz*m.wx ) - ( xzyx*m.wy ) + ( xxyz*m.wy ) + ( xyyx*m.wz ) - ( xxyy*m.wz ),
		( xyyz*m.zx ) - ( xzyy*m.zx ) + ( xzyx*m.zy ) - ( xxyz*m.zy ) - ( xyyx*m.zz ) + ( xxyy*m.zz )
	) * numType(1) / determinant(m);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> transpose( const mat4<numType>& m ) {
	return mat4<numType>(
		m.xx, m.yx, m.zx, m.wx,
		m.xy, m.yy, m.zy, m.wy,
		m.xz, m.yz, m.zz, m.wz,
		m.xw, m.yw, m.zw, m.ww );
}

template <typename numType> HL_IMPERATIVE
mat4<numType> rotate( const mat4<numType>& m, const vec3<numType>& axis, numType angle ) {
	numType			c( std::cos(angle) );
	numType			s( std::sin(angle) );
	vec3<numType>	a( normalize<numType>(axis) );
	numType			omc( numType(1) - c );
	numType			xy( (a.x*a.y)*omc );
	numType			yz( (a.y*a.z)*omc );
	numType			zx( (a.z*a.x)*omc );
	numType			sx( s*a.x ), sy( s*a.y ), sz( s*a.z );
	
	return mat4<numType>(
		m.xx * ( c+((a.x*a.x) * omc )),	m.xy * ( xy - sz ),				m.xz * ( zx + sy ), m.xw,
		m.yx * ( xy + sz ),				m.yy * ( c+((a.y*a.y) * omc) ),	m.yz * ( yz - sx ), m.yw,
		m.zx * ( zx - sy ),				m.zy * ( yz + sx ),				m.zz * ( c+((a.z*a.z) * omc )), m.zw,
		m.wx, m.wy, m.wz, m.ww
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> scale( const mat4<numType>& m, const vec3<numType>& scale ) {
	return mat4<numType>(
		m.xx*scale.x, m.xy, m.xz, m.xw,
		m.yx, m.yy*scale.y, m.yz, m.yw,
		m.zx, m.zy, m.zz*scale.z, m.zw,
		m.wx, m.wy, m.wz, m.ww
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> translate( const mat4<numType>& m, const vec3<numType>& t ) {
	return mat4<numType>(
		m.xx, m.xy, m.xz, m.xw,
		m.yx, m.yy, m.yz, m.yw,
		m.zx, m.zy, m.zz, m.zw,
		m.wx+t.x, m.wy+t.y, m.wz+t.z, m.ww
	);
}
/*

template <typename numType> HL_IMPERATIVE
mat4<numType> perspective( numType fov, numType aspect, numType zNear, numType zFar ) ;

template <typename numType> HL_IMPERATIVE
mat4<numType> ortho( numType top, numType bottom, numType left, numType right ) ;

template <typename numType> HL_IMPERATIVE
mat4<numType> lookAt( const vec3<numType>& pos, const vec3<numType>& target, const vec3<numType>& up );

template <typename numType> HL_IMPERATIVE
mat4<numType> frustum( numType top, numType bottom, numType left, numType right, numType near, numType far );
*/
} // math namespace
} // hamLibs namespace

#endif	/* __HL_MAT_UTILS_H__ */