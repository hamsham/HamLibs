/* 
 * File:   vec_utils.h
 * Author: hammy
 *
 * Created on January 8, 2013, 3:14 PM
 */

#ifndef __HL_VEC_UTILS_H__
#define	__HL_VEC_UTILS_H__

#include "scalar_utils.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

namespace hamLibs {

/*
 * Prototypes
 */
namespace math {

/*
 * 2D Vectors
 */
template <typename N> constexpr N           dot(const vec2_t<N>&, const vec2_t<N>&);
template <typename N> constexpr N           cross(const vec2_t<N>&, const vec2_t<N>&);
template <typename N> inline vec2_t<N>      normalize(const vec2_t<N>&);
template <typename N> constexpr N           length_squared(const vec2_t<N>&);
template <typename N> inline N              length(const vec2_t<N>&);
template <typename N> inline vec2_t<N>      rotate(const vec2_t<N>&, N);
template <typename N> inline N              angleBetween(const vec2_t<N>&, const vec2_t<N>&);
template <typename N> inline N              angleBetween(const vec2_t<N>&, const vec2_t<N>&, const vec2_t<N>& origin);
template <typename N> constexpr vec2_t<N>   min(const vec2_t<N>&, const vec2_t<N>&, N); /* Compares length */
template <typename N> constexpr vec2_t<N>   mix(const vec2_t<N>&, const vec2_t<N>&, N);
template <typename N> constexpr vec2_t<N>   max(const vec2_t<N>&, const vec2_t<N>&, N); /* Compares length */
template <typename N> inline vec2_t<N>      project(const vec2_t<N>& v1, const vec2_t<N>& v2);
template <typename N> inline vec2_t<N>      reflect(const vec2_t<N>& v1, const vec2_t<N>& norm);
template <typename N> constexpr vec2_t<N>   mid(const vec2_t<N>& v1, const vec2_t<N>& v2);

/*
 * 3D Vectors
 */
template <typename N> constexpr N           dot(const vec3_t<N>&, const vec3_t<N>&);
template <typename N> constexpr vec3_t<N>   cross(const vec3_t<N>&, const vec3_t<N>&);
template <typename N> inline vec3_t<N>      normalize(const vec3_t<N>&);
template <typename N> constexpr N           length_squared(const vec3_t<N>&);
template <typename N> inline N              length(const vec3_t<N>&);
template <typename N> inline vec3_t<N>      xRotation(N);
template <typename N> inline vec3_t<N>      yRotation(N);
template <typename N> inline vec3_t<N>      zRotation(N);
template <typename N> inline N              angleBetween(const vec3_t<N>&, const vec3_t<N>&);
template <typename N> inline N              angleBetween(const vec3_t<N>&, const vec3_t<N>&, const vec3_t<N>& origin);
template <typename N> constexpr vec3_t<N>   min(const vec3_t<N>&, const vec3_t<N>&, N);
template <typename N> constexpr vec3_t<N>   mix(const vec3_t<N>&, const vec3_t<N>&, N);
template <typename N> constexpr vec3_t<N>   max(const vec3_t<N>&, const vec3_t<N>&, N);
template <typename N> inline vec3_t<N>      project(const vec3_t<N>& v1, const vec3_t<N>& v2);
template <typename N> inline vec3_t<N>      reflect(const vec3_t<N>& v1, const vec3_t<N>& norm);
template <typename N> constexpr vec3_t<N>   mid(const vec3_t<N>& v1, const vec3_t<N>& v2);

/*
 * 4D Vectors
 */
template <typename N> constexpr N           dot(const vec4_t<N>&, const vec4_t<N>&);
template <typename N> inline vec4_t<N>      normalize(const vec4_t<N>&);
template <typename N> constexpr N           length_squared(const vec4_t<N>&);
template <typename N> inline N              length(const vec4_t<N>&);
template <typename N> inline N              angleBetween(const vec4_t<N>&, const vec4_t<N>&);
template <typename N> inline N              angleBetween(const vec3_t<N>&, const vec3_t<N>&, const vec3_t<N>& origin);
template <typename N> constexpr vec4_t<N>   min(const vec4_t<N>&, const vec4_t<N>&, N);
template <typename N> constexpr vec4_t<N>   mix(const vec4_t<N>&, const vec4_t<N>&, N);
template <typename N> constexpr vec4_t<N>   max(const vec4_t<N>&, const vec4_t<N>&, N);
template <typename N> inline vec4_t<N>      project(const vec4_t<N>& v1, const vec4_t<N>& v2);
template <typename N> inline vec4_t<N>      reflect(const vec4_t<N>& v1, const vec4_t<N>& norm);
template <typename N> constexpr vec4_t<N>   mid(const vec4_t<N>& v1, const vec4_t<N>& v2);

} // end math namespace

///////////////////////////////////////////////////////////////////////////////
// 2D Vectors
///////////////////////////////////////////////////////////////////////////////
template <typename numType> constexpr
numType math::dot(const vec2_t<numType>& v1, const vec2_t<numType>& v2) {
    return (v1.v[0] * v2.v[0]) + (v1.v[1] * v2.v[1]);
}

template <typename numType> constexpr
numType math::cross(const vec2_t<numType>& v1, const vec2_t<numType>& v2) {
    return (v1[0]*v2[1])-(v1[1]*v2[0]);
}


template <typename numType> inline
math::vec2_t<numType> math::normalize(const vec2_t<numType>& v) {
    const numType magInv = numType(1) / length<numType>(v);
    
    return v * magInv;
}

template <typename numType> constexpr
numType math::length_squared(const vec2_t<numType>& v) {
    return (v.v[0] * v.v[0]) + (v.v[1] * v.v[1]);
}

template <typename numType> inline
numType math::length(const vec2_t<numType>& v) {
    return (numType) HL_SQRT(length_squared<numType>(v));
}

template <typename numType> inline
math::vec2_t<numType> math::rotate(const vec2_t<numType>& v, numType angle) {
    const numType s = HL_SIN(angle);
    const numType c = HL_COS(angle);

    return vec2_t<numType>((v.v[0]*c) - (v.v[1]*s), (v.v[0]*s) + (v.v[1]*c));
}

template <typename numType> inline
numType math::angleBetween(const vec2_t<numType>& v1, const vec2_t<numType>& v2) {
    return (numType) acos(
        dot<numType>(v1, v2) / (length<numType>(v1)*length<numType>(v2))
    );
}

template <typename numType> inline
numType math::angleBetween(const vec2_t<numType>& v1, const vec2_t<numType>& v2, const vec2_t<numType>& origin) {
    return (numType) acos(
        dot<numType>(v1-origin, v2-origin) / (length<numType>(v1)*length<numType>(v2))
    );
}

template <typename numType> constexpr
math::vec2_t<numType> math::min(const vec2_t<numType>& v1, const vec2_t<numType>& v2) {
    return length_squared<numType>(v1) < length_squared<numType>(v2) ? v1 : v2;
}

template <typename numType> constexpr
math::vec2_t<numType> math::mix(const vec2_t<numType>& v1, const vec2_t<numType>& v2, numType percent) {
    return vec2_t<numType>{v1 + ((v2 - v1) * percent)};
}

template <typename numType> constexpr
math::vec2_t<numType> math::max(const vec2_t<numType>& v1, const vec2_t<numType>& v2) {
    return length_squared<numType>(v1) > length_squared<numType>(v2) ? v1 : v2;
}

template <typename numType> inline
math::vec2_t<numType> math::project(const vec2_t<numType>& v1, const vec2_t<numType>& v2) {
    const numType v1Len = math::length<numType>(v1);
    const numType v2Len = math::length<numType>(v2);
    
    const math::vec2_t<numType>&& v1Norm = v1 / v1Len;
    const math::vec2_t<numType>&& v2Norm = v2 / v2Len;
    
    const numType cosTheta = math::dot<numType>(v1Norm, v2Norm);
    
    return v2Norm * cosTheta * v1Len;
}

template <typename numType> inline
math::vec2_t<numType> math::reflect(const vec2_t<numType>& v, const vec2_t<numType>& norm) {
    const math::vec2_t<numType>&& nv = math::normalize<numType>(v);
    const math::vec2_t<numType>&& bounce = norm * (math::dot<numType>(nv, norm) * numType(2));
    return bounce - nv;
}

template <typename numType> constexpr
math::vec2_t<numType> math::mid(const vec2_t<numType>& v1, const vec2_t<numType>& v2) {
    return vec2_t<numType>{(v1[0]+v2[0]) * numType(0.5), (v1[1]+v2[1]) * numType(0.5)};
}

///////////////////////////////////////////////////////////////////////////////
// 3D Vectors
///////////////////////////////////////////////////////////////////////////////
template <typename numType> constexpr
numType math::dot(const vec3_t<numType>& v1, const vec3_t<numType>& v2) {
    return (v1.v[0] * v2.v[0]) + (v1.v[1] * v2.v[1]) + (v1.v[2] * v2.v[2]);
}

template <typename numType> constexpr
math::vec3_t<numType> math::cross(const vec3_t<numType>& v1, const vec3_t<numType>& v2) {
    return vec3_t<numType>(
        (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]),
        (v1.v[2] * v2.v[0]) - (v1.v[0] * v2.v[2]),
        (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0])
    );
}

template <typename numType> inline
math::vec3_t<numType> math::normalize(const vec3_t<numType>& v) {
    const numType magInv = numType(1) / length<numType>(v);
    
    return v * magInv;
}

template <typename numType> constexpr
numType math::length_squared(const vec3_t<numType>& v) {
    return (v.v[0] * v.v[0]) + (v.v[1] * v.v[1]) + (v.v[2] * v.v[2]);
}

template <typename numType> inline
numType math::length(const vec3_t<numType>& v) {
    return (numType) HL_SQRT(length_squared<numType>(v));
}

template <typename numType> inline
math::vec3_t<numType> math::xRotation(numType angle) {
    const numType s = HL_SIN(angle);
    const numType c = HL_COS(angle);

    return vec3_t<numType>(numType(1), c+s, c-s);
}

template <typename numType> inline
math::vec3_t<numType> math::yRotation(numType angle) {
    const numType s = HL_SIN(angle);
    const numType c = HL_COS(angle);

    return vec3_t<numType>(c-s, numType(1), s+c);
}

template <typename numType> inline
math::vec3_t<numType> math::zRotation(numType angle) {
    const numType s = HL_SIN(angle);
    const numType c = HL_COS(angle);

    return vec3_t<numType>(c+s, c-s, numType(1));
}

template <typename numType> inline
numType math::angleBetween(const vec3_t<numType>& v1, const vec3_t<numType>& v2) {
    return (numType) acos(
        dot<numType>(v1, v2) / (length<numType>(v1) * length<numType>(v2))
    );
}

template <typename numType> inline
numType math::angleBetween(const vec3_t<numType>& v1, const vec3_t<numType>& v2, const vec3_t<numType>& origin) {
    return (numType) acos(
        dot<numType>(v1-origin, v2-origin) / (length<numType>(v1) * length<numType>(v2))
    );
}

template <typename numType> constexpr
math::vec3_t<numType> math::min(const vec3_t<numType>& v1, const vec3_t<numType>& v2) {
    return length_squared<numType>(v1) < length_squared<numType>(v2) ? v1 : v2;
}

template <typename numType> constexpr
math::vec3_t<numType> math::mix(const vec3_t<numType>& v1, const vec3_t<numType>& v2, numType percent) {
    return vec3_t<numType>{v1 + ((v2 - v1) * percent)};
}

template <typename numType> constexpr
math::vec3_t<numType> math::max(const vec3_t<numType>& v1, const vec3_t<numType>& v2) {
    return length_squared<numType>(v1) > length_squared<numType>(v2) ? v1 : v2;
}

template <typename numType> inline
math::vec3_t<numType> math::project(const vec3_t<numType>& v1, const vec3_t<numType>& v2) {
    const numType v1Len = math::length<numType>(v1);
    const numType v2Len = math::length<numType>(v2);
    
    const math::vec3_t<numType> v1Norm = v1 / v1Len;
    const math::vec3_t<numType> v2Norm = v2 / v2Len;
    
    const numType cosTheta = math::dot<numType>(v1Norm, v2Norm);
    
    return v2Norm * cosTheta * v1Len;
}

template <typename numType> inline
math::vec3_t<numType> math::reflect(const vec3_t<numType>& v, const vec3_t<numType>& norm) {
    const math::vec3_t<numType>&& nv = math::normalize(v);
    
    const math::vec3_t<numType>&& bounce = norm * (math::dot<numType>(nv, norm) * numType(2));
    
    return bounce - nv;
}

template <typename numType> constexpr
math::vec3_t<numType> math::mid(const vec3_t<numType>& v1, const vec3_t<numType>& v2) {
    return vec3_t<numType>{
        (v1[0]+v2[0]) * numType(0.5),
        (v1[1]+v2[1]) * numType(0.5),
        (v1[2]+v2[2]) * numType(0.5)
    };
}

///////////////////////////////////////////////////////////////////////////////
// 4D Vectors
///////////////////////////////////////////////////////////////////////////////
template <typename numType> constexpr
numType math::dot(const vec4_t<numType>& v1, const vec4_t<numType>& v2) {
    return (v1.v[0] * v2.v[0]) + (v1.v[1] * v2.v[1]) + (v1.v[2] * v2.v[2]) + (v1.v[3] * v2.v[3]);
}

template <typename numType> inline
math::vec4_t<numType> math::normalize(const vec4_t<numType>& v) {
    const numType magInv = numType(1) / length<numType>(v);
    
    return v * magInv;
}

template <typename numType> constexpr
numType math::length_squared(const vec4_t<numType>& v) {
    return (v.v[0] * v.v[0]) + (v.v[1] * v.v[1]) +
        (v.v[2] * v.v[2]) + (v.v[3] * v.v[3]);
}

template <typename numType> inline
numType math::length(const vec4_t<numType>& v) {
    return (numType) HL_SQRT(length_squared<numType>(v));
}

template <typename numType> inline
numType math::angleBetween(const vec4_t<numType>& v1, const vec4_t<numType>& v2) {
    return (numType) acos(
        dot<numType>(v1, v2) / (length<numType>(v1) * length<numType>(v2))
    );
}

template <typename numType> inline
numType math::angleBetween(const vec4_t<numType>& v1, const vec4_t<numType>& v2, const vec4_t<numType>& origin) {
    return (numType) acos(
        dot<numType>(v1-origin, v2-origin) / (length<numType>(v1) * length<numType>(v2))
    );
}

template <typename numType> constexpr
math::vec4_t<numType> math::min(const vec4_t<numType>& v1, const vec4_t<numType>& v2) {
    return length_squared<numType>(v1) < length_squared<numType>(v2) ? v1 : v2;
}

template <typename numType> constexpr
math::vec4_t<numType> math::mix(const vec4_t<numType>& v1, const vec4_t<numType>& v2, numType percent) {
    return vec4_t<numType>{v1 + ((v2 - v1) * percent)};
}

template <typename numType> constexpr
math::vec4_t<numType> math::max(const vec4_t<numType>& v1, const vec4_t<numType>& v2) {
    return length_squared<numType>(v1) > length_squared<numType>(v2) ? v1 : v2;
}

template <typename numType> inline
math::vec4_t<numType> math::project(const vec4_t<numType>& v1, const vec4_t<numType>& v2) {
    const numType v1Len = math::length<numType>(v1);
    const numType v2Len = math::length<numType>(v2);
    
    const math::vec4_t<numType> v1Norm = v1 / v1Len;
    const math::vec4_t<numType> v2Norm = v2 / v2Len;
    
    const numType cosTheta = math::dot<numType>(v1Norm, v2Norm);
    
    return v2Norm * cosTheta * v1Len;
}

template <typename numType> inline
math::vec4_t<numType> math::reflect(const vec4_t<numType>& v, const vec4_t<numType>& norm) {
    const math::vec4_t<numType>&& nv = math::normalize(v);
    const math::vec4_t<numType>&& bounce = norm * (math::dot<numType>(nv, norm) * numType(2));
    return bounce - nv;
}

template <typename numType> constexpr
math::vec4_t<numType> math::mid(const vec4_t<numType>& v1, const vec4_t<numType>& v2) {
    return vec3_t<numType>{
        (v1[0]+v2[0]) * numType(0.5),
        (v1[1]+v2[1]) * numType(0.5),
        (v1[2]+v2[2]) * numType(0.5),
        (v1[3]+v2[3]) * numType(0.5)
    };
}

} // hamLibs namespace

#endif	/* __HL_VEC_UTILS_H__ */
