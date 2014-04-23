/* 
 * File:   quat_utils.h
 * Author: hammy
 *
 * Created on January 8, 2013, 8:55 AM
 */

#ifndef __HL_QUAT_UTILS_H__
#define	__HL_QUAT_UTILS_H__

#include "scalar_utils.h"
#include "vec3.h"
#include "vec4.h"
#include "matrix3.h"
#include "matrix4.h"
#include "quat.h"

namespace hamLibs {

/*
 * Prototypes
 */
namespace math {

/*
 * Quaternion Functions
 */
template <typename N> constexpr N           dot(const quat_t<N>&, const quat_t<N>&);
template <typename N> constexpr N           length_squared(const quat_t<N>&);
template <typename N> inline N              length(const quat_t<N>&);
template <typename N> inline quat_t<N>      inverse(const quat_t<N>&);
template <typename N> constexpr quat_t<N>   conjugate(const quat_t<N>&);
template <typename N> inline quat_t<N>      normalize(const quat_t<N>&);
template <typename N> constexpr quat_t<N>   lerp(const quat_t<N>&, const quat_t<N>&, N);
template <typename N> constexpr quat_t<N>   nlerp(const quat_t<N>&, const quat_t<N>&, N);
template <typename N> inline quat_t<N>      slerp(const quat_t<N>&, const quat_t<N>&, N);

/*
 * Quaternions & Matrices
 */
template <typename N> inline mat3_t<N>      quatToMat3(const quat_t<N>&);
template <typename N> inline mat4_t<N>      quatToMat4(const quat_t<N>&);
template <typename N> inline quat_t<N>      matToQuat(const mat3_t<N>&);
template <typename N> inline quat_t<N>      matToQuat(const mat4_t<N>&);

/*
 * Quaternions & Euler Angles
 */
template <typename N> constexpr vec3_t<N>   getAxisX(const quat_t<N>&); // Right-Vector
template <typename N> constexpr vec3_t<N>   getAxisY(const quat_t<N>&); // Up-Vector
template <typename N> constexpr vec3_t<N>   getAxisZ(const quat_t<N>&); // Forwards Vector
template <typename N> inline N              getAngle(const quat_t<N>&);
template <typename N> inline vec3_t<N>      toEuler(const quat_t<N>&);
template <typename N> inline quat_t<N>      fromEuler(const vec3_t<N>&);
template <typename N> inline quat_t<N>      fromEuler(N, N, N);
template <typename N> inline void           toAxisAngle(const quat_t<N>&, vec3_t<N>&, N&);
template <typename N> inline vec4_t<N>      toAxisAngle(const quat_t<N>&);
template <typename N> inline quat_t<N>      fromAxisAngle(const vec3_t<N>&, N);
template <typename N> inline quat_t<N>      fromAxisAngle(const vec4_t<N>&);

} // end math namespace

///////////////////////////////////////////////////////////////////////////////
// Quaternion Functions
///////////////////////////////////////////////////////////////////////////////
template <typename numType> constexpr
numType math::dot(const quat_t<numType>& q1, const quat_t<numType>& q2) {
    return (q1.q[0] * q2.q[0]) + (q1.q[1] * q2.q[1]) + (q1.q[2] * q2.q[2]) + (q1.q[3] * q2.q[3]);
}

template <typename numType> constexpr
numType math::length_squared(const quat_t<numType>& q) {
    return (q.q[0]*q.q[0]) + (q.q[1]*q.q[1]) + (q.q[2]*q.q[2]) + (q.q[3]*q.q[3]);
}

template <typename numType> inline
numType math::length(const quat_t<numType>& q) {
    return HL_SQRT(length_squared<numType>(q));
}

template <typename numType> inline
math::quat_t<numType> math::inverse(const quat_t<numType>& q) {
    const numType lenInv{
        numType(1) / math::length<numType>(q)
    };
    return quat_t<numType>{
        -q.q[0] * lenInv,
        -q.q[1] * lenInv,
        -q.q[2] * lenInv,
        q.q[3] * lenInv
    };
}

template <typename numType> constexpr
math::quat_t<numType> math::conjugate(const quat_t<numType>& q) {
    return quat_t<numType>{-q.q[0], -q.q[1], -q.q[2], q.q[3]};
}

template <typename numType> inline
math::quat_t<numType> math::normalize(const quat_t<numType>& q) {
    const numType magInv{
        numType(1) / length<numType>(q)
    };
    
    return quat_t<numType>{
        q.q[0] * magInv,
        q.q[1] * magInv,
        q.q[2] * magInv,
        q.q[3] * magInv
    };
}

template <typename numType> constexpr
math::quat_t<numType> math::lerp(const quat_t<numType>& q1, const quat_t<numType>& q2, numType percent) {
    return quat_t<numType>{q1 + ((q2 - q1) * percent)};
}

template <typename numType> constexpr
math::quat_t<numType> math::nlerp(const quat_t<numType>& q1, const quat_t<numType>& q2, numType percent) {
    return normalize(lerp<numType>(q1, q2));
}

/**
 * SLERP
 * This method has been adapted from Professor W. Randolph Franklin
 * Rensselaer Polytechnic Institute
 * http://www.ecse.rpi.edu/Homepages/wrf/pmwiki/pmwiki.php
 * http://www.ecse.rpi.edu/~wrf/wiki/ComputerGraphicsFall2012/guha/Code/quaternionAnimation.cpp
 * 
 * Request from the author must be granted prior to use in commercial products.
 */
template <typename numType> inline
math::quat_t<numType> math::slerp(const quat_t<numType>& q1, const quat_t<numType>& q2, numType t) {
    numType dotProd = dot(q1, q2);

    // Reverse the sign of q2 if q1.q2 < 0.
    if (dotProd < numType(0)) {
        dotProd = -dotProd;
    }

    const numType theta = acos(dotProd);
    numType mult1, mult2;

    if (theta >= HL_EPSILON) {
        const numType st = (numType) HL_SIN(theta);
        mult1 = HL_SIN((numType(1) - t) * theta) / st;
        mult2 = HL_SIN(t * theta) / st;
    }
    else {
        // To avoid division by 0 and by very small numbers the approximation of sin(angle)
        // by angle is used when theta is small (0.000001 is chosen arbitrarily).
        mult1 = numType(1) - t;
        mult2 = t;
    }

    return quat_t<numType>{
        mult1 * q1.q[0] + mult2 * q2.q[0],
        mult1 * q1.q[1] + mult2 * q2.q[1],
        mult1 * q1.q[2] + mult2 * q2.q[2],
        mult1 * q1.q[3] + mult2 * q2.q[3]
    };
}

///////////////////////////////////////////////////////////////////////////////
// Quaternions & Matrices
///////////////////////////////////////////////////////////////////////////////
template <typename numType> inline
math::mat3_t<numType> math::quatToMat3(const quat_t<numType>& q) {
    const numType xx = q.q[0] * q.q[0] * numType(2);
    const numType yy = q.q[1] * q.q[1] * numType(2);
    const numType zz = q.q[2] * q.q[2] * numType(2);
    const numType xy = q.q[0] * q.q[1];
    const numType xz = q.q[0] * q.q[2];
    const numType xw = q.q[0] * q.q[3];
    const numType yz = q.q[1] * q.q[2];
    const numType yw = q.q[1] * q.q[3];
    const numType zw = q.q[2] * q.q[3];

    return mat3_t<numType>{
        numType(1)-(yy + zz),   numType(2)*(xy + zw),   numType(2)*(xz - yw),
        numType(2)*(xy - zw),   numType(1)-(xx + zz),   numType(2)*(yz + xw),
        numType(2)*(xz + yw),   numType(2)*(yz - xw),   numType(1)-(xx + yy)
    };
}

template <typename numType> inline
math::mat4_t<numType> math::quatToMat4(const quat_t<numType>& q) {
    const numType xx = q.q[0] * q.q[0] * numType(2);
    const numType yy = q.q[1] * q.q[1] * numType(2);
    const numType zz = q.q[2] * q.q[2] * numType(2);
    const numType xy = q.q[0] * q.q[1];
    const numType xz = q.q[0] * q.q[2];
    const numType xw = q.q[0] * q.q[3];
    const numType yz = q.q[1] * q.q[2];
    const numType yw = q.q[1] * q.q[3];
    const numType zw = q.q[2] * q.q[3];

    return mat4_t<numType>{
        numType(1)-(yy + zz),   numType(2)*(xy + zw),   numType(2)*(xz - yw),   numType(0),
        numType(2)*(xy - zw),   numType(1)-(xx + zz),   numType(2)*(yz + xw),   numType(0),
        numType(2)*(xz + yw),   numType(2)*(yz - xw),   numType(1)-(xx + yy),   numType(0),
        numType(0),             numType(0),             numType(0),             numType(1)
    };
}

template <typename numType> inline
math::quat_t<numType> math::matToQuat(const mat3_t<numType>& m) {
    numType s(0);
    numType trace(m.m[0][0] + m.m[1][1] + m.m[2][2]);
    quat_t<numType> q;

    if (trace > numType(0)) {
        s = HL_SQRT(trace + numType(1));
        q.q[3] = s * numType(0.5);
        s = numType(0.5) / s;
        q.q[0] = (m.m[1][2] - m.m[2][1]) * s;
        q.q[1] = (m.m[2][0] - m.m[0][2]) * s;
        q.q[2] = (m.m[0][1] - m.m[1][0]) * s;
    }
    else {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.m[1][1] > m.m[0][0]) {
            i = 1;
        }

        if (m.m[2][2] > m.m[i][i]) {
            i = 2;
        }

        j = nxt[i];
        k = nxt[j];
        s = HL_SQRT((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + numType(1));

        q[i] = s * numType(0.5);
        s = numType(0.5) / s;
        q[3] = (m.m[j][k] - m.m[k][j]) * s;
        q[j] = (m.m[i][j] + m.m[j][i]) * s;
        q[k] = (m.m[i][k] + m.m[k][i]) * s;
    }
    
    return q;
}

template <typename numType> inline
math::quat_t<numType> math::matToQuat(const mat4_t<numType>& m) {
    numType s(0);
    numType trace(m.m[0][0] + m.m[1][1] + m.m[2][2]);
    quat_t<numType> q;

    if (trace > numType(0)) {
        s = HL_SQRT(trace + numType(1));
        q.q[3] = s * numType(0.5);
        s = numType(0.5) / s;
        q.q[0] = (m.m[1][2] - m.m[2][1]) * s;
        q.q[1] = (m.m[2][0] - m.m[0][2]) * s;
        q.q[2] = (m.m[0][1] - m.m[1][0]) * s;
    }
    else {
        int nxt[3] = {1, 2, 0};
        int i(0), j(0), k(0);

        if (m.m[1][1] > m.m[0][0]) {
            i = 1;
        }

        if (m.m[2][2] > m.m[i][i]) {
            i = 2;
        }

        j = nxt[i];
        k = nxt[j];
        s = HL_SQRT((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + numType(1));

        q[i] = s * numType(0.5);
        s = numType(0.5) / s;
        q[3] = (m.m[j][k] - m.m[k][j]) * s;
        q[j] = (m.m[i][j] + m.m[j][i]) * s;
        q[k] = (m.m[i][k] + m.m[k][i]) * s;
    }
    return q;
}

///////////////////////////////////////////////////////////////////////////////
// Quaternions & Euler Angles
///////////////////////////////////////////////////////////////////////////////
/*
 * Methods to extract quaternion components was found here:
 * http://nic-gamedev.blogspot.com/2011/11/quaternion-math-getting-local-axis.html
 * 
 * The equations for these functions can also be found in the quatToMatN() functions.
 */
template <typename numType> constexpr
math::vec3_t<numType> math::getAxisX(const math::quat_t<numType>& q) {
    return math::vec3_t<numType>{
        numType(1) - numType(2) * (q[1] * q[1] + q[2] * q[2]),
        numType(2) * (q[0] * q[1] + q[3] * q[2]),
        numType(2) * (q[0] * q[2] - q[3] * q[1])
    };
}

template <typename numType> constexpr
math::vec3_t<numType> math::getAxisY(const math::quat_t<numType>& q) {
    return math::vec3_t<numType>{
        numType(2) * (q[0] * q[1] - q[3] * q[2]),
        numType(1) - numType(2) * (q[0] * q[0] + q[2] * q[2]),
        numType(2) * (q[1] * q[2] + q[3] * q[0])
    };
}

template <typename numType> constexpr
math::vec3_t<numType> math::getAxisZ(const math::quat_t<numType>& q) {
    return math::vec3_t<numType>{
        numType(2) * (q[0] * q[2] + q[3] * q[1]),
        numType(2) * (q[1] * q[2] - q[3] * q[0]),
        numType(1) - numType(2) * (q[0] * q[0] + q[1] * q[1])
    };
}

template <typename numType> inline
numType math::getAngle(const quat_t<numType>& q) {
    return numType{std::acos(q.q[3] * numType(2))};
}

template <typename numType> inline
math::vec3_t<numType> math::toEuler(const quat_t<numType>& q) {
    const numType xx{q.q[0] * q.q[0]};
    const numType yy{q.q[1] * q.q[1]};
    const numType zz{q.q[2] * q.q[2]};
    
    const numType pitch{
        std::atan2(
            numType(2) * ((q.q[3] * q.q[0]) * (q.q[1] * q.q[2])),
            numType(1) - (numType(2) * (xx + yy))
        )
    };
    const numType yaw{
        std::asin(numType(2) * ((q.q[3] * q.q[1]) - (q.q[2] * q.q[0])))
    };
    const numType roll{
        std::atan2(
            numType(2) * ((q.q[3] * q.q[2]) + (q.q[0] * q.q[1])),
            numType(1) - (numType(2) * (yy + zz))
        )
    };
    return vec3_t<numType>(pitch, yaw, roll);
}

template <typename numType> inline
math::quat_t<numType> math::fromEuler(const math::vec3_t<numType>& angles) {
    const numType cp{HL_COS(angles.v[0] * numType(0.5))};
    const numType sp{HL_SIN(angles.v[0] * numType(0.5))};

    const numType cy{HL_COS(angles.v[1] * numType(0.5))};
    const numType sy{HL_SIN(angles.v[1] * numType(0.5))};

    const numType cr{HL_COS(angles.v[2] * numType(0.5))};
    const numType sr{HL_SIN(angles.v[2] * numType(0.5))};

    return math::quat_t<numType>{
        (sy * cp * cr) - (cy * sp * sr),
        (cy * sp * cr) + (sy * cp * sr),
        (cy * cp * sr) - (sy * sp * cr),
        (cy * cp * cr) + (sy * sp * sr)
    };
}

template <typename numType> inline
math::quat_t<numType> math::fromEuler(numType pitch, numType yaw, numType roll) {
    const numType cp{HL_COS(pitch * numType(0.5))};
    const numType sp{HL_SIN(pitch * numType(0.5))};

    const numType cy{HL_COS(yaw * numType(0.5))};
    const numType sy{HL_SIN(yaw * numType(0.5))};

    const numType cr{HL_COS(roll * numType(0.5))};
    const numType sr{HL_SIN(roll * numType(0.5))};

    return math::quat_t<numType>{
        (sy * cp * cr) - (cy * sp * sr),
        (cy * sp * cr) + (sy * cp * sr),
        (cy * cp * sr) - (sy * sp * cr),
        (cy * cp * cr) + (sy * sp * sr)
    };
}

template <typename numType> inline
void math::toAxisAngle(const quat_t<numType>& q, vec3_t<numType>& v, numType& a) {
    numType s{HL_SQRT(numType(1) - (q.q[3] * q.q[3]))};

    if (std::abs(s) <= numType(0)) {
        s = numType(1);
    }

    s = numType(1) / s;

    v.v[0] = q.q[0] * s,
    v.v[1] = q.q[1] * s,
    v.v[2] = q.q[2] * s,
    a = std::acos(q.q[3]) * numType(2);
}

template <typename numType> inline
math::vec4_t<numType> math::toAxisAngle(const quat_t<numType>& q) {
    const numType c{q.q[3]};
    numType s{HL_SQRT(numType(1) - c * c)};

    if (std::abs(s) <= numType(0)) {
        s = numType(1);
    }

    s = numType(1) / s;

    return vec4_t<numType>(
        q.q[0] * s,
        q.q[1] * s,
        q.q[2] * s,
        std::acos(q.q[3]) * numType(2)
    );
}

template <typename numType> inline
math::quat_t<numType> math::fromAxisAngle(const vec3_t<numType>& axis, numType angle) {
    numType a{angle * numType(0.5)};
    numType s{HL_SIN(a)};
    return quat_t<numType>{
        s * axis.v[0],
        s * axis.v[1],
        s * axis.v[2],
        HL_COS(a)
    };
}

template <typename numType> inline
math::quat_t<numType> math::fromAxisAngle(const vec4_t<numType>& v) {
    numType a{v.v[3] * numType(0.5)};
    numType s{HL_SIN(a)};
    return quat_t<numType>{
        s * v.v[0],
        s * v.v[1],
        s * v.v[2],
        HL_COS(a)
    };
}

} // hamLibs namespace

#endif	/* __HL_QUAT_UTILS_H__ */
