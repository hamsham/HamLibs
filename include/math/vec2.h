/*
 * 2d vector structure
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 * ----------
*/

#ifndef __HL_MATH_VEC2_H__
#define __HL_MATH_VEC2_H__

#include "scalar_utils.h"
#include "math/fixed.h"

namespace hamLibs {
namespace math {

/* 2x2 Matrix forward declaration */
template <typename numType>
struct mat2_t;

/******************************************************************************
 * 2D Vector Class
******************************************************************************/
template <typename numType>
struct vec2_t {
    // data
	numType v[2];
    
	// Main Constructor
	constexpr vec2_t(numType inX, numType inY);
    
    // Delegated Constructors
	constexpr vec2_t();
	constexpr vec2_t(numType n);
	constexpr vec2_t(const vec2_t<numType>& input);
	constexpr vec2_t(vec2_t<numType>&& input);
    
	~vec2_t() = default;
    
    // Conversions & Casting
    template <typename otherType>
    constexpr explicit operator vec2_t<otherType>() const;
    
    const numType*  operator        &       () const;
    inline numType* operator        &       ();
    
    // Subscripting Operators
	constexpr numType operator      []      (int i) const;
	inline numType& operator        []      (int i);
    
	//vector-vector operators
	vec2_t			operator 		+ 		(const vec2_t<numType>&) const;
	vec2_t			operator 		- 		(const vec2_t<numType>&) const;
	vec2_t			operator 		- 		() const;
	vec2_t			operator 		* 		(const vec2_t<numType>&) const;
	vec2_t			operator 		/ 		(const vec2_t<numType>&) const;
	vec2_t&			operator		= 		(const vec2_t<numType>&);
	vec2_t&			operator		= 		(vec2_t<numType>&&);
	vec2_t&			operator 		+= 		(const vec2_t<numType>&);
	vec2_t&			operator 		-= 		(const vec2_t<numType>&);
	vec2_t&			operator 		*= 		(const vec2_t<numType>&);
	vec2_t&			operator 		/= 		(const vec2_t<numType>&);
	vec2_t&			operator 		++		(); //prefix operators
	vec2_t&			operator 		--		();
	vec2_t			operator 		++		(int); //postfix operators
	vec2_t			operator 		--		(int);
	bool			operator		==		(const vec2_t<numType>& compare) const; //comparisons
	bool			operator		!=		(const vec2_t<numType>& compare) const;
	bool			operator		<		(const vec2_t<numType>& compare) const;
	bool			operator		>		(const vec2_t<numType>& compare) const;
	bool			operator		<=		(const vec2_t<numType>& compare) const;
	bool			operator		>=		(const vec2_t<numType>& compare) const;

	//vector-matrix operators (implementation in the matrix2 header)
	mat2_t<numType>	operator		+		(const mat2_t<numType>&) const;
	mat2_t<numType>	operator		-		(const mat2_t<numType>&) const;
	vec2_t<numType>	operator		*		(const mat2_t<numType>&) const;
	vec2_t&			operator		*=		(const mat2_t<numType>&);

	//vector-scalar operators
	vec2_t			operator 		= 		(numType);
	vec2_t			operator 		+ 		(numType) const;
	vec2_t			operator 		- 		(numType) const;
	vec2_t			operator 		* 		(numType) const;
	vec2_t			operator 		/ 		(numType) const;
	vec2_t&			operator 		+= 		(numType);
	vec2_t&			operator 		-= 		(numType);
	vec2_t&			operator 		*= 		(numType);
	vec2_t&			operator 		/= 		(numType);
};

/*
 * 2D Vector Specializations
 */
HL_DECLARE_CLASS_TYPE(vec2f, vec2_t, float);
HL_DECLARE_CLASS_TYPE(vec2d, vec2_t, double);
HL_DECLARE_CLASS_TYPE(vec2i, vec2_t, int);
HL_DECLARE_CLASS_TYPE(vec2x, vec2_t, medp_t);
HL_DECLARE_CLASS_TYPE(vec2, vec2_t, HL_FLOAT);

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType> operator + (numType n, const vec2_t<numType>& v);

template <typename numType> inline
vec2_t<numType> operator - (numType n, const vec2_t<numType>& v);

template <typename numType> inline
vec2_t<numType> operator * (numType n, const vec2_t<numType>& v);

template <typename numType> inline
vec2_t<numType> operator / (numType n, const vec2_t<numType>& v);

//---------------------------------------------------------------------
// Constructors
//---------------------------------------------------------------------
// Main Constructor
template <typename numType>
constexpr vec2_t<numType>::vec2_t(numType inX, numType inY) :
    v{inX, inY}
{}

template <typename numType>
constexpr vec2_t<numType>::vec2_t() :
    v{numType(0), numType(0)}
{}

template <typename numType>
constexpr vec2_t<numType>::vec2_t(numType n) :
    v{n, n}
{}

template <typename numType>
constexpr vec2_t<numType>::vec2_t(const vec2_t<numType>& v) :
    v{v.v[0], v.v[1]}
{}

template <typename numType>
constexpr vec2_t<numType>::vec2_t(vec2_t<numType>&& v) :
    v{v.v[0], v.v[1]}
{}

//---------------------------------------------------------------------
// Conversions & Casting
//---------------------------------------------------------------------
template <typename numType>
template <typename otherType>
constexpr vec2_t<numType>::operator vec2_t<otherType>() const {
    return vec2_t<otherType>{(otherType)v[0], (otherType)v[1]};
}

template <typename numType>
const numType* vec2_t<numType>::operator&() const {
    return v;
}

template <typename numType>
inline numType* vec2_t<numType>::operator&() {
    return v;
}

//---------------------------------------------------------------------
// Subscripting Operators
//---------------------------------------------------------------------
template <typename numType>
constexpr numType vec2_t<numType>::operator[] (int i) const {
    return v[i];
}
    
template <typename numType>
inline numType& vec2_t<numType>::operator[] (int i) {
    return v[i];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator + (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] + input.v[0],
		v[1] + input.v[1]
	);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator - (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] - input.v[0],
		v[1] - input.v[1]
	);
}

//for operations like "vectA = -vectB"
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator - () const {
	return vec2_t<numType>(-v[0], -v[1]);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator * (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] * input.v[0],
		v[1] * input.v[1]
	);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator / (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] / input.v[0],
		v[1] / input.v[1]
	);
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator += (const vec2_t<numType>& input) {
	v[0] += input.v[0];
	v[1] += input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator = (const vec2_t<numType>& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator = (vec2_t<numType>&& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator -= (const vec2_t<numType>& input) {
	v[0] -= input.v[0];
	v[1] -= input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator *= (const vec2_t<numType>& input) {
	v[0] *= input.v[0];
	v[1] *= input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator /= (const vec2_t<numType>& input) {
	v[0] /= input.v[0];
	v[1] /= input.v[1];
	return *this;
}

// prefix operations
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator++ () {
	++v[0];
	++v[1];
	return *this;
}
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator-- () {
	--v[0];
	--v[1];
	return *this;
}
//postfix operations
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator++ (int) {
	return vec2_t<numType>(
		++v[0],
		++v[1]
	);
}
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator-- (int) {
	return vec2_t<numType>(
		--v[0],
		--v[1]
	);
}

//comparisons
template <typename numType> inline
bool vec2_t<numType>::operator== (const vec2_t<numType>& compare) const {
	return (	v[0] == compare.v[0] &&
				v[1] == compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator!= (const vec2_t<numType>& compare) const {
	return (	v[0] != compare.v[0] ||
				v[1] != compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator< (const vec2_t<numType>& compare) const {
	return (	v[0] < compare.v[0] &&
				v[1] < compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator> (const vec2_t<numType>& compare) const {
	return (	v[0] > compare.v[0] &&
				v[1] > compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator<= (const vec2_t<numType>& compare) const {
	return (	v[0] <= compare.v[0] &&
				v[1] <= compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator>= (const vec2_t<numType>& compare) const {
	return (	v[0] >= compare.v[0] &&
				v[1] >= compare.v[1]
			);
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator - (numType input) const {
	return vec2_t<numType>(
		v[0] - input,
		v[1] - input
	);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator * (numType input) const {
	return vec2_t<numType>(
		v[0] * input,
		v[1] * input
	);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator / (numType input) const {
	return vec2_t<numType>(
		v[0] / input,
		v[1] / input
	);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator = (numType input) {
	v[0] = input;
	v[1] = input;
	return *this;
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator + (numType input) const {
	return vec2_t<numType>(
		v[0] + input,
		v[1] + input
	);
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator += (numType input) {
    v[0] += input;
    v[1] += input;
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator -= (numType input) {
    v[0] -= input;
    v[1] -= input;
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator *= (numType input) {
    v[0] *= input;
    v[1] *= input;
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator /= (numType input) {
    v[0] /= input;
    v[1] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType> operator + (numType n, const vec2_t<numType>& v) {
	return v + n;
}

template <typename numType> inline
vec2_t<numType> operator - (numType n, const vec2_t<numType>& v) {
	return v - n;
}

template <typename numType> inline
vec2_t<numType> operator * (numType n, const vec2_t<numType>& v) {
	return v * n;
}

template <typename numType> inline
vec2_t<numType> operator / (numType n, const vec2_t<numType>& v) {
	return v / n;
}

} //end math namespace
} //end hamlibs namespace

#endif /* __HL_MATH_VEC2_H__*/
