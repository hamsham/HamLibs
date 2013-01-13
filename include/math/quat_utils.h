/* 
 * File:   quat_utils.h
 * Author: hammy
 *
 * Created on January 8, 2013, 8:55 AM
 */

#ifndef __HL_QUAT_UTILS_H__
#define	__HL_QUAT_UTILS_H__

#include "quat.h"


namespace hamLibs {

///////////////////////////////////////////////////////////////////////////////
//		Prototypes
///////////////////////////////////////////////////////////////////////////////
	namespace math {
//-----------------------------------------------------------------------------
//		Quaternion Functions
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType			dot( const quat_t<numType>&, const quat_t<numType>& );

template <typename numType> HL_IMPERATIVE numType			magnitude( const quat_t<numType>& );

template <typename numType> HL_IMPERATIVE quat_t<numType>	inverse( const quat_t<numType>& );

template <typename numType> HL_IMPERATIVE quat_t<numType>	conjugate( const quat_t<numType>& );

template <typename numType> HL_IMPERATIVE quat_t<numType>	normalize( const quat_t<numType>& );

//-----------------------------------------------------------------------------
//		Quaternions & Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE mat3_t<numType>	quatToMat3( const quat_t<numType>& );
template <typename numType> HL_IMPERATIVE mat4_t<numType>	quatToMat4( const quat_t<numType>& );

template <typename numType> HL_IMPERATIVE quat_t<numType>	matToQuat( const mat3_t<numType>& );
template <typename numType> HL_IMPERATIVE quat_t<numType>	matToQuat( const mat4_t<numType>& );

//-----------------------------------------------------------------------------
//		Quaternions & Euler Angles
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE numType			getAngle( const quat_t<numType>& );

template <typename numType> HL_IMPERATIVE vec3_t<numType>	toEuler( const quat_t<numType>& );
template <typename numType> HL_IMPERATIVE quat_t<numType>	fromEuler( const vec3_t<numType>& );
template <typename numType> HL_IMPERATIVE quat_t<numType>	fromEuler( numType, numType, numType );

template <typename numType> HL_IMPERATIVE void				toAxisAngle( const quat_t<numType>&, vec3_t<numType>&, numType& );
template <typename numType> HL_IMPERATIVE vec4_t<numType>	toAxisAngle( const quat_t<numType>& );

template <typename numType> HL_IMPERATIVE quat_t<numType>	fromAxisAngle( const vec3_t<numType>&, numType );
template <typename numType> HL_IMPERATIVE quat_t<numType>	fromAxisAngle( const vec4_t<numType>& );

///////////////////////////////////////////////////////////////////////////////
//		Definitions
///////////////////////////////////////////////////////////////////////////////
	} // end math namespace
//-----------------------------------------------------------------------------
//		Quaternion Functions
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType math::dot( const quat_t<numType>& q1, const quat_t<numType>& q2 ) {
	return (q1.x*q2.x) + (q1.y*q2.y) + (q1.z*q2.z) + (q1.w*q2.w);
}

template <typename numType> HL_IMPERATIVE
numType math::magnitude( const quat_t<numType>& q ) {
	return HL_SQRT( (q.x*q.x) + (q.y*q.y) + (q.z*q.z) + (q.w*q.w) );
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::inverse( const quat_t<numType>& q ) {
	numType dotInv(
		numType(1) / ( (q.x*q.x) + (q.y*q.y) + (q.z*q.z) + (q.w*q.w) )
	);
	return quat_t<numType>(
		-q.x * dotInv,
		-q.y * dotInv,
		-q.z * dotInv,
		q.w * dotInv
	);
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::conjugate( const quat_t<numType>& q ) {
	return quat_t<numType>( -q.x, -q.y, -q.z, q.w );
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::normalize( const quat_t<numType>& q ) {
	numType magInv(
		numType(1) / HL_SQRT( (q.x*q.x) + (q.y*q.y) + (q.z*q.z) + (q.w*q.w) )
	);
	return quat_t<numType>(
		q.x * magInv,
		q.y * magInv,
		q.z * magInv,
		q.w * magInv
	);
}

//-----------------------------------------------------------------------------
//		Quaternions & Matrices
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
math::mat3_t<numType> math::quatToMat3( const quat_t<numType>& q ) {
	numType xx = q.x * q.x * numType(numType(2));
	numType yy = q.y * q.y * numType(numType(2));
	numType zz = q.z * q.z * numType(numType(2));
	numType xy = q.x * q.y;
	numType xz = q.x * q.z;
	numType xw = q.x * q.w;
	numType yz = q.y * q.z;
	numType yw = q.y * q.w;
	numType zw = q.z * q.w;
	
	return mat3_t<numType>(
		numType(1)-(yy+zz),	numType(numType(2))*(xy+zw),	numType(numType(2))*(xz-yw),
		numType(numType(2))*(xy-zw),	numType(1)-(xx+zz),	numType(numType(2))*(yz+xw),
		numType(numType(2))*(xz+yw),	numType(numType(2))*(yz-xw),	numType(1)-(xx+yy)
	);
}

template <typename numType> HL_IMPERATIVE
math::mat4_t<numType> math::quatToMat4( const quat_t<numType>& q ) {
	numType xx = q.x * q.x * numType(numType(2));
	numType yy = q.y * q.y * numType(numType(2));
	numType zz = q.z * q.z * numType(numType(2));
	numType xy = q.x * q.y;
	numType xz = q.x * q.z;
	numType xw = q.x * q.w;
	numType yz = q.y * q.z;
	numType yw = q.y * q.w;
	numType zw = q.z * q.w;
	
	return mat4_t<numType>(
		numType(1)-(yy+zz),	numType(numType(2))*(xy+zw),	numType(numType(2))*(xz-yw), numType(0),
		numType(numType(2))*(xy-zw),	numType(1)-(xx+zz),	numType(numType(2))*(yz+xw), numType(0),
		numType(numType(2))*(xz+yw),	numType(numType(2))*(yz-xw),	numType(1)-(xx+yy), numType(0),
		numType(0), numType(0), numType(0), numType(1)
	);
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::matToQuat( const mat3_t<numType>& m ) {
    numType s( 0 );
    numType trace( m.xx + m.yy + m.zz );
	quat_t<numType> q;

	if (trace > numType(0)) {
        s = HL_SQRT(trace + numType(1));
        q.w = s * numType(0.5);
        s = numType(0.5) / s;
        q.x = (m.yz - m.zy) * s;
        q.y = (m.zx - m.xz) * s;
        q.z = (m.xy - m.yx) * s;
    }
    else {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.yy > m.xx)
            i = 1;

        if (m.zz > m[i][i])
            i = 2;

        j = nxt[i];
        k = nxt[j];
        s = HL_SQRT((m[i][i] - (m[j][j] + m[k][k])) + numType(1));

        q[i] = s * numType(0.5);
        s = numType(0.5) / s;
        q[3] = (m[j][k] - m[k][j]) * s;
        q[j] = (m[i][j] + m[j][i]) * s;
        q[k] = (m[i][k] + m[k][i]) * s;
    }
	return q;
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::matToQuat( const mat4_t<numType>& m ) {
    numType s( 0 );
    numType trace( m.xx + m.yy + m.zz );
	quat_t<numType> q;

	if (trace > numType(0)) {
        s = HL_SQRT(trace + numType(1));
        q.w = s * numType(0.5);
        s = numType(0.5) / s;
        q.x = (m.yz - m.zy) * s;
        q.y = (m.zx - m.xz) * s;
        q.z = (m.xy - m.yx) * s;
    }
    else {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.yy > m.xx)
            i = 1;

        if (m.zz > m[i][i])
            i = 2;

        j = nxt[i];
        k = nxt[j];
        s = HL_SQRT((m[i][i] - (m[j][j] + m[k][k])) + numType(1));

        q[i] = s * numType(0.5);
        s = numType(0.5) / s;
        q[3] = (m[j][k] - m[k][j]) * s;
        q[j] = (m[i][j] + m[j][i]) * s;
        q[k] = (m[i][k] + m[k][i]) * s;
    }
	return q;
}
//-----------------------------------------------------------------------------
//		quat_t<numType>s & Euler Angles
//-----------------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType math::getAngle( const quat_t<numType>& q ) {
	return numType( std::acos( q.w * numType(2) ) );
}

template <typename numType> HL_IMPERATIVE
math::vec3_t<numType> math::toEuler( const quat_t<numType>& q ) {
	numType xx( q.x * q.x );
	numType yy( q.y * q.y );
	numType zz( q.z * q.z );
	numType pitch(
		std::atan2(
			numType(2) * ((q.w*q.x) * (q.y*q.z)),
			numType(1) - (numType(2) * (xx+yy))
		)
	);
	numType yaw(
		std::asin(
			numType(2) * ((q.w*q.y) - (q.z*q.x))
		)
	);
	numType roll(
		std::atan2(
			numType(2) * ((q.w*q.z) + (q.x*q.y)),
			numType(1) - (numType(2) * (yy+zz))
		)
	);
	return vec3_t<numType>( pitch, yaw, roll );
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::fromEuler( const vec3_t<numType>& angles ) {
	const vec3_t<numType> xAxis( numType(1), numType(0), numType(0) );
	const vec3_t<numType> yAxis( numType(0), numType(1), numType(0) );
	const vec3_t<numType> zAxis( numType(0), numType(0), numType(1) );
	
	return
		fromAxisAngle( zAxis, angles.z ) *
		fromAxisAngle( yAxis, angles.y ) *
		fromAxisAngle( xAxis, angles.x );
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::fromEuler( numType pitch, numType yaw, numType roll ) {
	const vec3_t<numType> xAxis( numType(1), numType(0), numType(0) );
	const vec3_t<numType> yAxis( numType(0), numType(1), numType(0) );
	const vec3_t<numType> zAxis( numType(0), numType(0), numType(1) );
	
	return
		fromAxisAngle( zAxis, roll ) *
		fromAxisAngle( yAxis, yaw ) *
		fromAxisAngle( xAxis, pitch );
}

template <typename numType> HL_IMPERATIVE
void math::toAxisAngle( const quat_t<numType>& q, vec3_t<numType>& v, numType& a ) {
	numType s( HL_SQRT( numType(1) - (q.w*q.w)) );
	
	if (std::abs( s ) <= numType(0) )
		s = numType(1);
	s = numType(1) / s;
	
	v.x = q.x * s,
	v.y = q.y * s,
	v.z = q.z * s,
	a = std::acos( q.w ) * numType(2);
}

template <typename numType> HL_IMPERATIVE
math::vec4_t<numType> math::toAxisAngle( const quat_t<numType>& q ) {
	numType c( q.w );
	numType s( HL_SQRT( numType(1) - (q.w*q.w)) );
	
	if (std::abs( s ) <= numType(0) )
		s = numType(1);
	s = numType(1) / s;
	
	return vec4_t<numType>(
		q.x * s,
		q.y * s,
		q.z * s,
		std::acos( q.w ) * numType(2)
	);
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::fromAxisAngle( const vec3_t<numType>& axis, numType angle ) {
	numType a( angle * numType(0.5) );
	numType s( std::sin( a ));
	return quat_t<numType>(
			s * axis.x,
			s * axis.y,
			s * axis.z,
			std::cos( a )
	);
}

template <typename numType> HL_IMPERATIVE
math::quat_t<numType> math::fromAxisAngle( const vec4_t<numType>& v ) {
	numType a( v.w * numType(0.5) );
	numType s( std::sin( a ));
	return quat_t<numType>(
			s * v.x,
			s * v.y,
			s * v.z,
			std::cos( a )
	);
}


} // hamLibs namespace

#endif	/* __HL_QUAT_UTILS_H__ */
