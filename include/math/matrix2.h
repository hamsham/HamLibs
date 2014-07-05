/*
 * 3d matrix class
 * recommended for use with non-integral types

 * NOTES:
 * Matrix is Row-Major
 * orientation is as follows:
 * ----------------
 *		XX	XY
 *		YX	YY
 * ----------------
*/

#ifndef __HL_MATH_MATRIX2_H__
#define __HL_MATH_MATRIX2_H__

#include "scalar_utils.h"
#include "math/fixed.h"
#include "vec2.h"

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat2 class
//---------------------------------------------------------------------
template <typename numType>
struct mat2_t {
    // data
    vec2_t<numType> m[2];
    
	// Main Constructor
    constexpr mat2_t(
        numType inXX, numType inXY,
        numType inYX, numType inYY
    );
    
    // Delegated constructors
    constexpr mat2_t();
    constexpr mat2_t(numType);
    constexpr mat2_t(const mat2_t<numType>&);
    constexpr mat2_t(mat2_t<numType>&&);
    constexpr mat2_t(const vec2_t<numType>& x, const vec2_t<numType>& y);
    
	~mat2_t() = default;
    
    // Conversions & Casting
    template <typename otherType>
    constexpr explicit operator mat2_t<otherType>() const;
    
    // Subscripting
	inline const vec2_t<numType>& operator[] (int i) const;
	inline vec2_t<numType>& operator[] (int i);

	//mat-mat operators
	mat2_t&			operator	++		(); //prefix operators
	mat2_t&			operator	--		();
	mat2_t			operator	++		(int); //postfix operators
	mat2_t			operator	--		(int);
	mat2_t			operator	+		(const mat2_t<numType>& input) const;
	mat2_t			operator	-		(const mat2_t<numType>& input) const;
	mat2_t			operator	-		() const;
	mat2_t			operator	*		(const mat2_t<numType>& input) const;
	mat2_t&			operator	=		(const mat2_t<numType>& input);
	mat2_t&			operator	=		(mat2_t<numType>&& input);
	mat2_t&			operator	+=		(const mat2_t<numType>& input);
	mat2_t&			operator	-=		(const mat2_t<numType>& input);
	mat2_t&			operator	*=		(const mat2_t<numType>& input);
	bool			operator	==		(const mat2_t<numType>& input) const;
	bool			operator	!=		(const mat2_t<numType>& input) const;

	//mat-vector operators
	mat2_t			operator	+		(const vec2_t<numType>&) const;
	mat2_t			operator	-		(const vec2_t<numType>&) const;
	vec2_t<numType>	operator	*		(const vec2_t<numType>&) const;
	mat2_t&			operator	=		(const vec2_t<numType>&);
	mat2_t&			operator	+=		(const vec2_t<numType>&);
	mat2_t&			operator	-=		(const vec2_t<numType>&);

	//mat-scalar operators
	mat2_t			operator	+		(numType) const;
	mat2_t			operator	-		(numType) const;
	mat2_t			operator	*		(numType) const;
	mat2_t			operator	/		(numType) const;
	mat2_t&			operator	=		(numType);
	mat2_t&			operator	+=		(numType);
	mat2_t&			operator	-=		(numType);
	mat2_t&			operator	*=		(numType);
	mat2_t&			operator	/=		(numType);
};

/*
 * 2x2 Matrix Specializations
 */
HL_DECLARE_CLASS_TYPE(mat2f, mat2_t, float);
HL_DECLARE_CLASS_TYPE(mat2d, mat2_t, double);
HL_DECLARE_CLASS_TYPE(mat2i, mat2_t, int);
HL_DECLARE_CLASS_TYPE(mat2x, mat2_t, medp_t);
HL_DECLARE_CLASS_TYPE(mat2, mat2_t, HL_FLOAT);

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
mat2_t<numType> operator + (numType n, const mat2_t<numType>& m);

template <typename numType> inline
mat2_t<numType> operator - (numType n, const mat2_t<numType>& m);

template <typename numType> inline
mat2_t<numType> operator * (numType n, const mat2_t<numType>& m);

template <typename numType> inline
mat2_t<numType> operator / (numType n, const mat2_t<numType>& m);

//---------------------------------------------------------------------
// Constructors
//---------------------------------------------------------------------
// Main Constructor
template <typename numType>
constexpr mat2_t<numType>::mat2_t(
    numType inXX, numType inXY,
    numType inYX, numType inYY) :
    m{
        { inXX, inXY },
        { inYX, inYY },
    }
{}

template <typename numType>
constexpr mat2_t<numType>::mat2_t() :
    m{
        {numType(0), numType(0)},
        {numType(0), numType(0)}
    }
{}

template <typename numType>
constexpr mat2_t<numType>::mat2_t(numType n) :
    m{
        {n, numType(0)},
        {numType(0), n}
    }
{}

template <typename numType>
constexpr mat2_t<numType>::mat2_t(
    const vec2_t<numType>& x,
    const vec2_t<numType>& y
) :
    m{
        {x.v[0], x.v[1]},
        {y.v[0], y.v[1]}
    }
{}

template <typename numType>
constexpr mat2_t<numType>::mat2_t(const mat2_t<numType>& m) :
    m{
        {m.m[0][0], m.m[0][1]},
        {m.m[1][0], m.m[1][1]}
    }
{}

template <typename numType>
constexpr mat2_t<numType>::mat2_t(mat2_t<numType>&& m) :
    m{
        {m.m[0][0], m.m[0][1]},
        {m.m[1][0], m.m[1][1]}
    }
{}

//---------------------------------------------------------------------
// Conversions & Casting
//---------------------------------------------------------------------
template <typename numType>
template <typename otherType>
constexpr mat2_t<numType>::operator mat2_t<otherType>() const {
    return mat2_t<otherType>{
        (otherType)m[0][0], (otherType)m[0][1],
        (otherType)m[1][0], (otherType)m[1][1]
    };
}

//---------------------------------------------------------------------
// Subscripting Operators
//---------------------------------------------------------------------
template <typename numType>
inline const vec2_t<numType>& mat2_t<numType>::operator[](int i) const {
    return m[i];
}

template <typename numType>
inline vec2_t<numType>& mat2_t<numType>::operator[](int i) {
    return m[i];
}

//---------------------------------------------------------------------
//	mat-mat Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator++ () {
	++m[0][0]; ++m[0][1];
	++m[1][0]; ++m[1][1];
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator-- () {
	--m[0][0]; --m[0][1];
	--m[1][0]; --m[1][1];
	return *this;
}

//postfix operators
template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator++ (int) {
	return mat2_t<numType>(
		++m[0][0], ++m[0][1],
		++m[1][0], ++m[1][1]
	);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator-- (int) {
	return mat2_t<numType>(
		--m[0][0], --m[0][1],
		--m[1][0], --m[1][1]
	);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator + (const mat2_t<numType>& input) const {
	return mat2_t<numType>(
		m[0][0] + input.m[0][0], m[0][1] + input.m[0][1],
		m[1][0] + input.m[1][0], m[1][1] + input.m[1][1]
	);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator - (const mat2_t<numType>& input) const {
	return mat2_t<numType>(
		m[0][0] - input.m[0][0], m[0][1] - input.m[0][1],
		m[1][0] - input.m[1][0], m[1][1] - input.m[1][1]
	);
}

//for operations like "mat2a = -mat2b"
template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator - () const {
	return mat2_t<numType>(	-m[0][0], -m[0][1],
							-m[1][0], -m[1][1]);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator * (const mat2_t<numType>& input) const {
	return mat2_t<numType>(
	//X
		(input.m[0][0]*m[0][0]) + (input.m[0][1]*m[1][0]),
		(input.m[0][0]*m[0][1]) + (input.m[0][1]*m[1][1]),
	//Y
		(input.m[1][0]*m[0][0]) + (input.m[1][1]*m[1][0]),
		(input.m[1][0]*m[0][1]) + (input.m[1][1]*m[1][1])
	);
}

template <typename numType>
mat2_t<numType>& mat2_t<numType>::operator =(const mat2_t<numType>& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    
    return *this;
}

template <typename numType>
mat2_t<numType>& mat2_t<numType>::operator =(mat2_t<numType>&& input) {
    m[0][0] = input.m[0][0];
    m[0][1] = input.m[0][1];
    
    m[1][0] = input.m[1][0];
    m[1][1] = input.m[1][1];
    
    return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator += (const mat2_t<numType>& input) {
	m[0][0] += input.m[0][0]; m[0][1] += input.m[0][1];
	m[1][0] += input.m[1][0]; m[1][1] += input.m[1][1];
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator -= (const mat2_t<numType>& input) {
	m[0][0] -= input.m[0][0]; m[0][1] -= input.m[0][1];
	m[1][0] -= input.m[1][0]; m[1][1] -= input.m[1][1];
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator *= (const mat2_t<numType>& input) {
	return *this = *this * input;
}

template <typename numType> inline
bool mat2_t<numType>::operator == (const mat2_t<numType>& compare) const {
	return	(
				m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] &&
				m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1]
			);
}

template <typename numType> inline
bool mat2_t<numType>::operator != (const mat2_t<numType>& compare) const {
	return	(
				m[0][0] != compare.m[0][0] || m[0][1] != compare.m[0][1] ||
				m[1][0] != compare.m[1][0] || m[1][1] != compare.m[1][1]
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations (Declared in the vector header)
//---------------------------------------------------------------------
template <typename numType> inline
mat2_t<numType> vec2_t<numType>::operator + (const mat2_t<numType>& m) const {
	return mat2_t<numType>(
		v[0] + m.m[0][0], v[0] + m.m[0][1],
		v[1] + m.m[1][0], v[1] + m.m[1][1]
	);
}

template <typename numType> inline
mat2_t<numType> vec2_t<numType>::operator - (const mat2_t<numType>& m) const {
	return mat2_t<numType>(
		v[0] - m.m[0][0], v[0] - m.m[0][1],
		v[1] - m.m[1][0], v[1] - m.m[1][1]
	);
}

// Multiplies by a row vector
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator * (const mat2_t<numType>& m) const {
	return vec2_t<numType>(
		(m.m[0][0] * v[0]) + (m.m[1][0] * v[1]),
		(m.m[0][1] * v[0]) + (m.m[1][1] * v[1])
	);
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator *= (const mat2_t<numType>& m) {
	*this = *this * m;
	return *this;
}

//---------------------------------------------------------------------
//	matrix-vector Operators
//---------------------------------------------------------------------
template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator + (const vec2_t<numType>& input) const {
	return mat2_t(
		m[0][0] + input.v[0], m[0][1] + input.v[1],
		m[1][0] + input.v[0], m[1][1] + input.v[1]
	);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator - (const vec2_t<numType>& input) const {
	return mat2_t(
		m[0][0] - input.v[0], m[0][1] - input.v[1],
		m[1][0] - input.v[0], m[1][1] - input.v[1]
	);
}

// Multiply by a column-vector
template <typename numType> inline
vec2_t<numType> mat2_t<numType>::operator * (const vec2_t<numType>& inVec) const {
	return vec2_t<numType>(
		(m[0][0] * inVec.v[0]) + (m[0][1] * inVec.v[1]),
		(m[1][0] * inVec.v[0]) + (m[1][1] * inVec.v[1])
	);
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator = (const vec2_t<numType>& input) {
	m[0][0] = input.v[0]; m[0][1] = input.v[0];
	m[1][0] = input.v[1]; m[1][1] = input.v[1];
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator += (const vec2_t<numType>& input) {
	m[0][0] += input.v[0]; m[0][1] += input.v[1];
	m[1][0] += input.v[0]; m[1][1] += input.v[1];
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator -= (const vec2_t<numType>& input) {
	m[0][0] -= input.v[0]; m[0][1] -= input.v[1];
	m[1][0] -= input.v[0]; m[1][1] -= input.v[1];
	return *this;
}

//---------------------------------------------------------------------
//	mat-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator + (numType input) const {
	return mat2_t<numType>(
		m[0][0] + input, m[0][1] + input,
		m[1][0] + input, m[1][1] + input
	);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator - (numType input) const {
	return mat2_t<numType>(
		m[0][0] - input, m[0][1] - input,
		m[1][0] - input, m[1][1] - input
	);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator * (numType input) const {
	return mat2_t<numType>(
		m[0][0] * input, m[0][1] * input,
		m[1][0] * input, m[1][1] * input
	);
}

template <typename numType> inline
mat2_t<numType> mat2_t<numType>::operator / (numType input) const {
	return mat2_t<numType>(
		m[0][0] / input, m[0][1] / input,
		m[1][0] / input, m[1][1] / input
	);
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator = (numType input) {
	m[0][0] = input; m[0][1] = input;
	m[1][0] = input; m[1][1] = input;
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator += (numType input) {
	m[0][0] += input; m[0][1] += input;
	m[1][0] += input; m[1][1] += input;
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator -= (numType input) {
	m[0][0] -= input; m[0][1] -= input;
	m[1][0] -= input; m[1][1] -= input;
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator *= (numType input) {
	m[0][0] *= input; m[0][1] *= input;
	m[1][0] *= input; m[1][1] *= input;
	return *this;
}

template <typename numType> inline
mat2_t<numType>& mat2_t<numType>::operator /= (numType input) {
	m[0][0] /= input; m[0][1] /= input;
	m[1][0] /= input; m[1][1] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
mat2_t<numType> operator + (numType n, const mat2_t<numType>& m) {
	return m + n;
}

template <typename numType> inline
mat2_t<numType> operator - (numType n, const mat2_t<numType>& m) {
	return m - n;
}

template <typename numType> inline
mat2_t<numType> operator * (numType n, const mat2_t<numType>& m) {
	return m * n;
}

template <typename numType> inline
mat2_t<numType> operator / (numType n, const mat2_t<numType>& m) {
	return m / n;
}

} //end math namespace
} //end hamlibs namespace
#endif /*__mat2_H__*/
