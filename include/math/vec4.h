/*
 * 4d vector structure
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 *		Z
 *		W
 * ----------
*/

#ifndef __HL_MATH_VEC4_H__
#define __HL_MATH_VEC4_H__

#include "scalar_utils.h"
#include "math/fixed.h"

namespace hamLibs {
namespace math {

/* 4x4 Matrix forward declaration */
template <typename numType>
struct mat4_t;

/******************************************************************************
 * 4D Vector Class
******************************************************************************/
template <typename numType>
struct vec4_t {
    // data
    numType v[4];
    
	// Main Constructor
	constexpr vec4_t(numType inX, numType inY, numType inZ, numType inW);
	constexpr vec4_t();
	constexpr vec4_t(numType n);
	constexpr vec4_t(const vec4_t<numType>& input);
	constexpr vec4_t(vec4_t<numType>&& input);
    
	~vec4_t() = default;
    
    // Conversions & Casting
    template <typename otherType>
    constexpr explicit operator vec4_t<otherType>() const;
    
    const numType*  operator        &       () const;
    inline numType* operator        &       ();
    
    // Subscripting Operators
	constexpr numType operator      []      (int i) const;
	inline numType& operator        []      (int i);

	//vector-vector operators
	vec4_t			operator 		+ 		(const vec4_t<numType>&) const;
	vec4_t			operator 		- 		(const vec4_t<numType>&) const;
	vec4_t			operator 		- 		() const;
	vec4_t			operator 		* 		(const vec4_t<numType>&) const;
	vec4_t			operator 		/ 		(const vec4_t<numType>&) const;
	vec4_t&			operator		= 		(const vec4_t<numType>&);
	vec4_t&			operator		= 		(vec4_t<numType>&&);
	vec4_t&			operator 		+= 		(const vec4_t<numType>&);
	vec4_t&			operator 		-= 		(const vec4_t<numType>&);
	vec4_t&			operator 		*= 		(const vec4_t<numType>&);
	vec4_t&			operator 		/= 		(const vec4_t<numType>&);
	vec4_t&			operator 		++		(); //prefix operators
	vec4_t&			operator 		--		();
	vec4_t			operator 		++		(int); //postfix operators
	vec4_t			operator 		--		(int);
	bool			operator		==		(const vec4_t<numType>& compare) const; //comparisons
	bool			operator		!=		(const vec4_t<numType>& compare) const;
	bool			operator		<		(const vec4_t<numType>& compare) const;
	bool			operator		>		(const vec4_t<numType>& compare) const;
	bool			operator		<=		(const vec4_t<numType>& compare) const;
	bool			operator		>=		(const vec4_t<numType>& compare) const;

	//vector-matrix operators (implementation in the matrix4 header)
	mat4_t<numType>	operator		+		(const mat4_t<numType>&) const;
	mat4_t<numType>	operator		-		(const mat4_t<numType>&) const;
	vec4_t<numType>	operator		*		(const mat4_t<numType>&) const;
	vec4_t&			operator		*=		(const mat4_t<numType>&);

	//vector-scalar operators
	vec4_t			operator 		= 		(numType);
	vec4_t			operator 		+ 		(numType) const;
	vec4_t			operator 		- 		(numType) const;
	vec4_t			operator 		* 		(numType) const;
	vec4_t			operator 		/ 		(numType) const;
	vec4_t&			operator 		+= 		(numType);
	vec4_t&			operator 		-= 		(numType);
	vec4_t&			operator 		*= 		(numType);
	vec4_t&			operator 		/= 		(numType);
};

/*
 * 4D Vector Specializations
 */
HL_DECLARE_CLASS_TYPE(vec4f, vec4_t, float);
HL_DECLARE_CLASS_TYPE(vec4d, vec4_t, double);
HL_DECLARE_CLASS_TYPE(vec4i, vec4_t, int);
HL_DECLARE_CLASS_TYPE(vec4x, vec4_t, medp_t);
HL_DECLARE_CLASS_TYPE(vec4, vec4_t, HL_FLOAT);

//---------------------------------------------------------------------
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType> operator + (numType n, const vec4_t<numType>& v);

template <typename numType> inline
vec4_t<numType> operator - (numType n, const vec4_t<numType>& v);

template <typename numType> inline
vec4_t<numType> operator * (numType n, const vec4_t<numType>& v);

template <typename numType> inline
vec4_t<numType> operator / (numType n, const vec4_t<numType>& v);

//---------------------------------------------------------------------
// Constructors
//---------------------------------------------------------------------
// Main Constructor
template <typename numType>
constexpr vec4_t<numType>::vec4_t(numType inX, numType inY, numType inZ, numType inW) :
    v{inX, inY, inZ, inW}
{}

template <typename numType>
constexpr vec4_t<numType>::vec4_t() :
    v{numType(0), numType(0), numType(0), numType(1)}
{}

template <typename numType>
constexpr vec4_t<numType>::vec4_t(numType n) :
    v{n, n, n, numType(1)}
{}

template <typename numType>
constexpr vec4_t<numType>::vec4_t(const vec4_t<numType>& v) :
    v{v.v[0], v.v[1], v.v[2], v.v[3]}
{}

template <typename numType>
constexpr vec4_t<numType>::vec4_t(vec4_t<numType>&& v) :
    v{v.v[0], v.v[1], v.v[2], v.v[3]}
{}

//---------------------------------------------------------------------
// Conversions & Casting
//---------------------------------------------------------------------
template <typename numType>
template <typename otherType>
constexpr vec4_t<numType>::operator vec4_t<otherType>() const {
    return vec4_t<otherType>{
        (otherType)v[0], (otherType)v[1], (otherType)v[2], (otherType)v[3]
    };
}

template <typename numType>
const numType* vec4_t<numType>::operator&() const {
    return v;
}

template <typename numType>
inline numType* vec4_t<numType>::operator&() {
    return v;
}

//---------------------------------------------------------------------
// Subscripting Operators
//---------------------------------------------------------------------
template <typename numType>
constexpr numType vec4_t<numType>::operator[] (int i) const {
    return v[i];
}

template <typename numType>
inline numType& vec4_t<numType>::operator[] (int i) {
    return v[i];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator + (const vec4_t<numType>& input) const {
	return vec4_t(
		v[0] + input.v[0],
		v[1] + input.v[1],
		v[2] + input.v[2],
		v[3] + input.v[3]
	);
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator - (const vec4_t<numType>& input) const {
	return vec4_t(
		v[0] - input.v[0],
		v[1] - input.v[1],
		v[2] - input.v[2],
		v[3] - input.v[3]
	);
}

//for operations like "vectA = -vectB"
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator - () const {
	return vec4_t<numType>(-v[0], -v[1], -v[2], -v[3]);
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator * (const vec4_t<numType>& input) const {
	return vec4_t<numType>(
		v[0] * input.v[0],
		v[1] * input.v[1],
		v[2] * input.v[2],
		v[3] * input.v[3]
	);
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator / (const vec4_t<numType>& input) const {
	return vec4_t<numType>(
		v[0] / input.v[0],
		v[1] / input.v[1],
		v[2] / input.v[2],
		v[3] / input.v[3]
	);
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator = (const vec4_t<numType>& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	v[3] = input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator = (vec4_t<numType>&& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	v[3] = input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator += (const vec4_t<numType>& input) {
    v[0] += input.v[0];
    v[1] += input.v[1];
    v[2] += input.v[2];
    v[3] += input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator -= (const vec4_t<numType>& input) {
    v[0] -= input.v[0];
    v[1] -= input.v[1];
    v[2] -= input.v[2];
    v[3] -= input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator *= (const vec4_t<numType>& input) {
    v[0] *= input.v[0];
    v[1] *= input.v[1];
    v[2] *= input.v[2];
    v[3] *= input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator /= (const vec4_t<numType>& input) {
    v[0] /= input.v[0];
    v[1] /= input.v[1];
    v[2] /= input.v[2];
    v[3] /= input.v[3];
	return *this;
}

// prefix operations
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator++ () {
	++v[0];
	++v[1];
	++v[2];
	++v[3];
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator-- () {
	--v[0];
	--v[1];
	--v[2];
	--v[3];
	return *this;
}

//postfix operations
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator++ (int) {
	return vec4_t<numType>(
		++v[0],
		++v[1],
		++v[2],
		++v[3]
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator-- (int) {
	return vec4_t<numType>(
		--v[0],
		--v[1],
		--v[2],
		--v[3]
	);
}

//comparisons
template <typename numType> inline
bool vec4_t<numType>::operator== (const vec4_t<numType>& compare) const {
	return (	v[0] == compare.v[0] &&
				v[1] == compare.v[1] &&
				v[2] == compare.v[2] &&
				v[3] == compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator!= (const vec4_t<numType>& compare) const {
	return (	v[0] != compare.v[0] ||
				v[1] != compare.v[1] ||
				v[2] != compare.v[2] ||
				v[3] != compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator< (const vec4_t<numType>& compare) const {
	return (	v[0] < compare.v[0] &&
				v[1] < compare.v[1] &&
				v[2] < compare.v[2] &&
				v[3] < compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator> (const vec4_t<numType>& compare) const {
	return (	v[0] > compare.v[0] &&
				v[1] > compare.v[1] &&
				v[2] > compare.v[2] &&
				v[3] > compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator<= (const vec4_t<numType>& compare) const {
	return (	v[0] <= compare.v[0] &&
				v[1] <= compare.v[1] &&
				v[2] <= compare.v[2] &&
				v[3] <= compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator>= (const vec4_t<numType>& compare) const {
	return (	v[0] >= compare.v[0] &&
				v[1] >= compare.v[1] &&
				v[2] >= compare.v[2] &&
				v[3] >= compare.v[3]
			);
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator = (numType input) {
	v[0] = input;
	v[1] = input;
	v[2] = input;
	v[3] = input;
	return *this;
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator + (numType input) const {
	return vec4_t<numType>(
		v[0] + input,
		v[1] + input,
		v[2] + input,
		v[3] + input
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator - (numType input) const {
	return vec4_t<numType>(
		v[0] - input,
		v[1] - input,
		v[2] - input,
		v[3] - input
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator * (numType input) const {
	return vec4_t<numType>(
		v[0] * input,
		v[1] * input,
		v[2] * input,
		v[3] * input
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator / (numType input) const {
	return vec4_t<numType>(
		v[0] / input,
		v[1] / input,
		v[2] / input,
		v[3] / input
	);
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator += (numType input) {
    v[0] += input;
    v[1] += input;
    v[2] += input;
    v[3] += input;
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator -= (numType input) {
    v[0] -= input;
    v[1] -= input;
    v[2] -= input;
    v[3] -= input;
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator *= (numType input) {
    v[0] *= input;
    v[1] *= input;
    v[2] *= input;
    v[3] *= input;
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator /= (numType input) {
    v[0] /= input;
    v[1] /= input;
    v[2] /= input;
    v[3] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType> operator + (numType n, const vec4_t<numType>& v) {
	return v + n;
}

template <typename numType> inline
vec4_t<numType> operator - (numType n, const vec4_t<numType>& v) {
	return v - n;
}

template <typename numType> inline
vec4_t<numType> operator * (numType n, const vec4_t<numType>& v) {
	return v * n;
}

template <typename numType> inline
vec4_t<numType> operator / (numType n, const vec4_t<numType>& v) {
	return v / n;
}

} //end math namespace
} //end hamlibs namespace
#endif /* __HL_MATH_VEC4_H__*/
