/*
 * 3d vector structure
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 *		Z
 * ----------
*/

#ifndef __HL_MATH_VEC3_H__
#define __HL_MATH_VEC3_H__

#include "scalar_utils.h"
#include "math/fixed.h"

namespace hamLibs {
namespace math {

/* 3x3 Matrix forward declaration */
template <typename numType>
struct mat3_t;

/******************************************************************************
 * 3D Vector Class
******************************************************************************/
template <typename numType>
struct vec3_t {
	union {
		numType v[3];
		struct {
			numType x, y, z;
		} index;
	};
    
	// Main Constructor
	constexpr vec3_t(numType inX, numType inY, numType inZ);
	constexpr vec3_t();
	constexpr vec3_t(numType n);
	constexpr vec3_t(const vec3_t<numType>& input);
	constexpr vec3_t(vec3_t<numType>&& input);
    
	~vec3_t() = default;
    
    // Conversions & Casting
    template <typename otherType>
    constexpr explicit operator vec3_t<otherType>() const;
    
    // Subscripting Operators
	constexpr numType operator      []      (int i) const;
	inline numType& operator        []      (int i);

	//vector-vector operators
	vec3_t			operator 		+ 		(const vec3_t<numType>&) const;
	vec3_t			operator 		- 		(const vec3_t<numType>&) const;
	vec3_t			operator 		- 		() const;
	vec3_t			operator 		* 		(const vec3_t<numType>&) const;
	vec3_t			operator 		/ 		(const vec3_t<numType>&) const;
	vec3_t&			operator		= 		(const vec3_t<numType>&);
	vec3_t&			operator		= 		(vec3_t<numType>&&);
	vec3_t&			operator 		+= 		(const vec3_t<numType>&);
	vec3_t&			operator 		-= 		(const vec3_t<numType>&);
	vec3_t&			operator 		*= 		(const vec3_t<numType>&);
	vec3_t&			operator 		/= 		(const vec3_t<numType>&);
	vec3_t&			operator 		++		(); //prefix operators
	vec3_t&			operator 		--		();
	vec3_t			operator 		++		(int); //postfix operators
	vec3_t			operator 		--		(int);
	bool			operator		==		(const vec3_t<numType>& compare) const; //comparisons
	bool			operator		!=		(const vec3_t<numType>& compare) const;
	bool			operator		<		(const vec3_t<numType>& compare) const;
	bool			operator		>		(const vec3_t<numType>& compare) const;
	bool			operator		<=		(const vec3_t<numType>& compare) const;
	bool			operator		>=		(const vec3_t<numType>& compare) const;

	//vector-matrix operators (implementation in the matrix3 header)
	mat3_t<numType>	operator		+		(const mat3_t<numType>&) const;
	mat3_t<numType>	operator		-		(const mat3_t<numType>&) const;
	vec3_t<numType>	operator		*		(const mat3_t<numType>&) const;
	vec3_t&			operator		*=		(const mat3_t<numType>&);

	//vector-scalar operators
	vec3_t			operator 		= 		(numType);
	vec3_t			operator 		+ 		(numType) const;
	vec3_t			operator 		- 		(numType) const;
	vec3_t			operator 		* 		(numType) const;
	vec3_t			operator 		/ 		(numType) const;
	vec3_t&			operator 		+= 		(numType);
	vec3_t&			operator 		-= 		(numType);
	vec3_t&			operator 		*= 		(numType);
	vec3_t&			operator 		/= 		(numType);
};

/*
 * 3D Vector Specializations
 */
HL_DECLARE_CLASS_TYPE(vec3f, vec3_t, float);
HL_DECLARE_CLASS_TYPE(vec3d, vec3_t, double);
HL_DECLARE_CLASS_TYPE(vec3i, vec3_t, int);
HL_DECLARE_CLASS_TYPE(vec3x, vec3_t, medp_t);
HL_DECLARE_CLASS_TYPE(vec3, vec3_t, HL_FLOAT);

//---------------------------------------------------------------------
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec3_t<numType> operator + (numType n, const vec3_t<numType>& v);

template <typename numType> inline
vec3_t<numType> operator - (numType n, const vec3_t<numType>& v);

template <typename numType> inline
vec3_t<numType> operator * (numType n, const vec3_t<numType>& v);

template <typename numType> inline
vec3_t<numType> operator / (numType n, const vec3_t<numType>& v);

//---------------------------------------------------------------------
// Constructors
//---------------------------------------------------------------------
// Main Constructor
template <typename numType>
constexpr vec3_t<numType>::vec3_t(numType inX, numType inY, numType inZ) :
    v{inX, inY, inZ}
{}

template <typename numType>
constexpr vec3_t<numType>::vec3_t() :
    v{numType(0), numType(0), numType(0)}
{}

template <typename numType>
constexpr vec3_t<numType>::vec3_t(numType n) :
    v{n, n, n}
{}

template <typename numType>
constexpr vec3_t<numType>::vec3_t(const vec3_t<numType>& v) :
    v{v.v[0], v.v[1], v.v[2]}
{}

template <typename numType>
constexpr vec3_t<numType>::vec3_t(vec3_t<numType>&& v) :
    v{v.v[0], v.v[1], v.v[2]}
{}

//---------------------------------------------------------------------
// Conversions & Casting
//---------------------------------------------------------------------
template <typename numType>
template <typename otherType>
constexpr vec3_t<numType>::operator vec3_t<otherType>() const {
    return vec3_t<otherType>{(otherType)v[0], (otherType)v[1], (otherType)v[2]};
}

//---------------------------------------------------------------------
// Subscripting Operators
//---------------------------------------------------------------------
template <typename numType>
constexpr numType vec3_t<numType>::operator[] (int i) const {
    return v[i];
}

template <typename numType>
inline numType& vec3_t<numType>::operator[] (int i) {
    return v[i];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator + (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] + input.v[0],
		v[1] + input.v[1],
		v[2] + input.v[2]
	);
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator - (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] - input.v[0],
		v[1] - input.v[1],
		v[2] - input.v[2]
	);
}

//for operations like "vectA = -vectB"
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator - () const {
	return vec3_t<numType>(-v[0], -v[1], -v[2]);
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator * (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] * input.v[0],
		v[1] * input.v[1],
		v[2] * input.v[2]
	);
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator / (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] / input.v[0],
		v[1] / input.v[1],
		v[2] / input.v[2]
	);
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator = (const vec3_t<numType>& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator = (vec3_t<numType>&& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator += (const vec3_t<numType>& input) {
	v[0] += input.v[0];
	v[1] += input.v[1];
	v[2] += input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator -= (const vec3_t<numType>& input) {
	v[0] -= input.v[0];
	v[1] -= input.v[1];
	v[2] -= input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator *= (const vec3_t<numType>& input) {
	v[0] *= input.v[0];
	v[1] *= input.v[1];
	v[2] *= input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator /= (const vec3_t<numType>& input) {
	v[0] /= input.v[0];
	v[1] /= input.v[1];
	v[2] /= input.v[2];
	return *this;
}

// prefix operations
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator++ () {
	++v[0];
	++v[1];
	++v[2];
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator-- () {
	--v[0];
	--v[1];
	--v[2];
	return *this;
}
//postfix operations
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator++ (int) {
	return vec3_t<numType>(
		++v[0],
		++v[1],
		++v[2]
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator-- (int) {
	return vec3_t<numType>(
		--v[0],
		--v[1],
		--v[2]
	);
}

//comparisons
template <typename numType> inline
bool vec3_t<numType>::operator== (const vec3_t<numType>& compare) const {
	return (	v[0] == compare.v[0] &&
				v[1] == compare.v[1] &&
				v[2] == compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator!= (const vec3_t<numType>& compare) const {
	return (	v[0] != compare.v[0] ||
				v[1] != compare.v[1] ||
				v[2] != compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator< (const vec3_t<numType>& compare) const {
	return (	v[0] < compare.v[0] &&
				v[1] < compare.v[1] &&
				v[2] < compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator> (const vec3_t<numType>& compare) const {
	return (	v[0] > compare.v[0] &&
				v[1] > compare.v[1] &&
				v[2] > compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator<= (const vec3_t<numType>& compare) const {
	return (	v[0] <= compare.v[0] &&
				v[1] <= compare.v[1] &&
				v[2] <= compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator>= (const vec3_t<numType>& compare) const {
	return (	v[0] >= compare.v[0] &&
				v[1] >= compare.v[1] &&
				v[2] >= compare.v[2]
			);
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator = (numType input) {
	v[0] = input;
	v[1] = input;
	v[2] = input;
	return *this;
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator + (numType input) const {
	return vec3_t<numType>(
		v[0] + input,
		v[1] + input,
		v[2] + input
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator - (numType input) const {
	return vec3_t<numType>(
		v[0] - input,
		v[1] - input,
		v[2] - input
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator * (numType input) const {
	return vec3_t<numType>(
		v[0] * input,
		v[1] * input,
		v[2] * input
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator / (numType input) const {
	return vec3_t<numType>(
		v[0] / input,
		v[1] / input,
		v[2] / input
	);
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator += (numType input) {
	v[0] += input;
	v[1] += input;
	v[2] += input;
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator -= (numType input) {
	v[0] -= input;
	v[1] -= input;
	v[2] -= input;
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator *= (numType input) {
	v[0] *= input;
	v[1] *= input;
	v[2] *= input;
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator /= (numType input) {
	v[0] /= input;
	v[1] /= input;
	v[2] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec3_t<numType> operator + (numType n, const vec3_t<numType>& v) {
	return v + n;
}

template <typename numType> inline
vec3_t<numType> operator - (numType n, const vec3_t<numType>& v) {
	return v - n;
}

template <typename numType> inline
vec3_t<numType> operator * (numType n, const vec3_t<numType>& v) {
	return v * n;
}

template <typename numType> inline
vec3_t<numType> operator / (numType n, const vec3_t<numType>& v) {
	return v / n;
}

} //end math namespace
} //end hamlibs namespace

#endif /* __HL_MATH_VEC3_H__*/
