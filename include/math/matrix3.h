/*
 * 3d matrix class
 * recommended for use with non-integral types
 * 
 * NOTES:
 * Matrix is Row-Major
 * orientation is as follows:
 * ---------------------
 *		XX	XY	XZ
 *		YX	YY	YZ
 *		ZX	ZY	ZZ
 * ---------------------
*/

#ifndef __HL_MATH_MATRIX3_H__
#define __HL_MATH_MATRIX3_H__

#include "scalar_utils.h"
#include "math/fixed.h"
#include "vec3.h"

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat3 class
//---------------------------------------------------------------------
template <typename numType>
struct mat3_t {
    union {
        numType m[3][3];
        
        struct {
            vec3_t<numType> x;
            vec3_t<numType> y;
            vec3_t<numType> z;
        } row;
    };
    
	// Main Constructor
    constexpr mat3_t(
        numType inXX, numType inXY, numType inXZ,
        numType inYX, numType inYY, numType inYZ,
        numType inZX, numType inZY, numType inZZ
    );
    
    // Delegated Constructors
    constexpr mat3_t();
    constexpr mat3_t(numType);
    constexpr mat3_t(const mat3_t<numType>&);
    constexpr mat3_t(mat3_t<numType>&&);
    constexpr mat3_t(
        const vec3_t<numType>& x,
        const vec3_t<numType>& y,
        const vec3_t<numType>& z
    );
    
	~mat3_t() = default;
    
    // Conversions & Casting
    template <typename otherType>
    constexpr explicit operator mat3_t<otherType>() const;

	//Subscripting operators
	const numType*  operator    []      (int i) const;
	inline numType* operator    []      (int i);

	//matrix-matrix operators
	mat3_t&			operator	++		(); //prefix operators
	mat3_t&			operator	--		();
	mat3_t			operator	++		(int); //postfix operators
	mat3_t			operator	--		(int);
	mat3_t			operator	+		(const mat3_t<numType>& input) const;
	mat3_t			operator	-		(const mat3_t<numType>& input) const;
	mat3_t			operator	-		() const;
	mat3_t			operator	*		(const mat3_t<numType>& input) const;
	mat3_t&			operator	=		(const mat3_t<numType>& input);
	mat3_t&			operator	=		(mat3_t<numType>&& input);
	mat3_t&			operator	+=		(const mat3_t<numType>& input);
	mat3_t&			operator	-=		(const mat3_t<numType>& input);
	mat3_t&			operator	*=		(const mat3_t<numType>& input);
	bool			operator	==		(const mat3_t<numType>& input) const;
	bool			operator	!=		(const mat3_t<numType>& input) const;

	//matrix-vector operators
	mat3_t			operator	+		(const vec3_t<numType>&) const;
	mat3_t			operator	-		(const vec3_t<numType>&) const;
	vec3_t<numType>	operator	*		(const vec3_t<numType>&) const;
	mat3_t&			operator	=		(const vec3_t<numType>&);
	mat3_t&			operator	+=		(const vec3_t<numType>&);
	mat3_t&			operator	-=		(const vec3_t<numType>&);

	//matrix-scalar operators
	mat3_t			operator	+		(numType) const;
	mat3_t			operator	-		(numType) const;
	mat3_t			operator	*		(numType) const;
	mat3_t			operator	/		(numType) const;
	mat3_t&			operator	=		(numType);
	mat3_t&			operator	+=		(numType);
	mat3_t&			operator	-=		(numType);
	mat3_t&			operator	*=		(numType);
	mat3_t&			operator	/=		(numType);
};

/*
 * 3x3 Matrix Specializations
 */
HL_DECLARE_CLASS_TYPE(mat3f, mat3_t, float);
HL_DECLARE_CLASS_TYPE(mat3d, mat3_t, double);
HL_DECLARE_CLASS_TYPE(mat3i, mat3_t, int);
HL_DECLARE_CLASS_TYPE(mat3x, mat3_t, medp_t);
HL_DECLARE_CLASS_TYPE(mat3, mat3_t, HL_FLOAT);

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
mat3_t<numType> operator + (numType n, const mat3_t<numType>& m);

template <typename numType> inline
mat3_t<numType> operator - (numType n, const mat3_t<numType>& m);

template <typename numType> inline
mat3_t<numType> operator * (numType n, const mat3_t<numType>& m);

template <typename numType> inline
mat3_t<numType> operator / (numType n, const mat3_t<numType>& m);

//---------------------------------------------------------------------
// Constructors
//---------------------------------------------------------------------
// Main Constructor
template <typename numType>
constexpr mat3_t<numType>::mat3_t(
    numType inXX, numType inXY, numType inXZ,
    numType inYX, numType inYY, numType inYZ,
    numType inZX, numType inZY, numType inZZ) :
    m{
        { inXX, inXY, inXZ },
        { inYX, inYY, inYZ },
        { inZX, inZY, inZZ }
    }
{}

template <typename numType>
constexpr mat3_t<numType>::mat3_t() :
    mat3_t(
        numType(0), numType(0), numType(0),
        numType(0), numType(0), numType(0),
        numType(0), numType(0), numType(0)
    )
{}

template <typename numType>
constexpr mat3_t<numType>::mat3_t(numType n) :
    mat3_t(
        n, numType(0), numType(0),
        numType(0), n, numType(0),
        numType(0), numType(0), n
    )
{}

template <typename numType>
constexpr mat3_t<numType>::mat3_t(const mat3_t<numType>& input) :
    mat3_t(
        input.m[0][0], input.m[0][1], input.m[0][2],
        input.m[1][0], input.m[1][1], input.m[1][2],
        input.m[2][0], input.m[2][1], input.m[2][2]
    )
{}

template <typename numType>
constexpr mat3_t<numType>::mat3_t(mat3_t<numType>&& input) :
    mat3_t(
        input.m[0][0], input.m[0][1], input.m[0][2],
        input.m[1][0], input.m[1][1], input.m[1][2],
        input.m[2][0], input.m[2][1], input.m[2][2]
    )
{}

template <typename numType>
constexpr mat3_t<numType>::mat3_t(
    const vec3_t<numType>& x,
    const vec3_t<numType>& y,
    const vec3_t<numType>& z
) : mat3_t(
        x.v[0], x.v[1], x.v[2],
        y.v[0], y.v[1], y.v[2],
        z.v[0], z.v[1], z.v[2]
    )
{}

//---------------------------------------------------------------------
// Conversions & Casting
//---------------------------------------------------------------------
template <typename numType>
template <typename otherType>
constexpr mat3_t<numType>::operator mat3_t<otherType>() const {
    return mat3_t<otherType>{
        (otherType)m[0][0], (otherType)m[0][1], (otherType)m[0][2],
        (otherType)m[1][0], (otherType)m[1][1], (otherType)m[1][2],
        (otherType)m[2][0], (otherType)m[2][1], (otherType)m[2][2]
    };
}

//---------------------------------------------------------------------
// Subscripting Operators
//---------------------------------------------------------------------
template <typename numType>
const numType* mat3_t<numType>::operator[](int i) const {
    return m[i];
}

template <typename numType>
inline numType* mat3_t<numType>::operator[](int i) {
    return m[i];
}

//---------------------------------------------------------------------
//	Matrix-Matrix Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator++ () {
	++m[0][0]; ++m[0][1]; ++m[0][2];
	++m[1][0]; ++m[1][1]; ++m[1][2];
	++m[2][0]; ++m[2][1]; ++m[2][2];
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator-- () {
	--m[0][0]; --m[0][1]; --m[0][2];
	--m[1][0]; --m[1][1]; --m[1][2];
	--m[2][0]; --m[2][1]; --m[2][2];
	return *this;
}

//postfix operators
template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator++ (int) {
	return mat3_t<numType>(
		++m[0][0], ++m[0][1], ++m[0][2],
		++m[1][0], ++m[1][1], ++m[1][2],
		++m[2][0], ++m[2][1], ++m[2][2]
	);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator-- (int) {
	return mat3_t<numType>(
		--m[0][0], --m[0][1], --m[0][2],
		--m[1][0], --m[1][1], --m[1][2],
		--m[2][0], --m[2][1], --m[2][2]
	);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator + (const mat3_t<numType>& input) const {
	return mat3_t<numType>(
		m[0][0] + input.m[0][0], m[0][1] + input.m[0][1], m[0][2] + input.m[0][2],
		m[1][0] + input.m[1][0], m[1][1] + input.m[1][1], m[1][2] + input.m[1][2],
		m[2][0] + input.m[2][0], m[2][1] + input.m[2][1], m[2][2] + input.m[2][2]
	);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator - (const mat3_t<numType>& input) const {
	return mat3_t<numType>(
		m[0][0] - input.m[0][0], m[0][1] - input.m[0][1], m[0][2] - input.m[0][2],
		m[1][0] - input.m[1][0], m[1][1] - input.m[1][1], m[1][2] - input.m[1][2],
		m[2][0] - input.m[2][0], m[2][1] - input.m[2][1], m[2][2] - input.m[2][2]
	);
}

//for operations like "matrix3a = -matrix3b"
template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator - () const {
	return mat3_t<numType>(	-m[0][0], -m[0][1], -m[0][2],
							-m[1][0], -m[1][1], -m[1][2],
							-m[2][0], -m[2][1], -m[2][2]);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator * (const mat3_t<numType>& input) const {
	return mat3_t<numType>(
	//X
		(m[0][0]*input.m[0][0]) + (m[0][1]*input.m[1][0]) + (m[0][2]*input.m[2][0]),
		(m[0][0]*input.m[0][1]) + (m[0][1]*input.m[1][1]) + (m[0][2]*input.m[2][1]),
		(m[0][0]*input.m[0][2]) + (m[0][1]*input.m[1][2]) + (m[0][2]*input.m[2][2]),
		
	//Y
		(m[1][0]*input.m[0][0]) + (m[1][1]*input.m[1][0]) + (m[1][2]*input.m[2][0]),
		(m[1][0]*input.m[0][1]) + (m[1][1]*input.m[1][1]) + (m[1][2]*input.m[2][1]),
		(m[1][0]*input.m[0][2]) + (m[1][1]*input.m[1][2]) + (m[1][2]*input.m[2][2]),
		
	//Z
		(m[2][0]*input.m[0][0]) + (m[2][1]*input.m[1][0]) + (m[2][2]*input.m[2][0]),
		(m[2][0]*input.m[0][1]) + (m[2][1]*input.m[1][1]) + (m[2][2]*input.m[2][1]),
		(m[2][0]*input.m[0][2]) + (m[2][1]*input.m[1][2]) + (m[2][2]*input.m[2][2])
	);
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator = (const mat3_t<numType>& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2];
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator = (mat3_t<numType>&& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2];
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator += (const mat3_t<numType>& input) {
	m[0][0] += input.m[0][0]; m[0][1] += input.m[0][1]; m[0][2] += input.m[0][2];
	m[1][0] += input.m[1][0]; m[1][1] += input.m[1][1]; m[1][2] += input.m[1][2];
	m[2][0] += input.m[2][0]; m[2][1] += input.m[2][1]; m[2][2] += input.m[2][2];
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator -= (const mat3_t<numType>& input) {
	m[0][0] -= input.m[0][0]; m[0][1] -= input.m[0][1]; m[0][2] -= input.m[0][2];
	m[1][0] -= input.m[1][0]; m[1][1] -= input.m[1][1]; m[1][2] -= input.m[1][2];
	m[2][0] -= input.m[2][0]; m[2][1] -= input.m[2][1]; m[2][2] -= input.m[2][2];
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator *= (const mat3_t<numType>& input) {
	return *this = *this * input;
}

template <typename numType> inline
bool mat3_t<numType>::operator == (const mat3_t<numType>& compare) const {
	return	(
				m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] && m[0][2] == compare.m[0][2] &&
				m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1] && m[1][2] == compare.m[1][2] &&
				m[2][0] == compare.m[2][0] && m[2][1] == compare.m[2][1] && m[2][2] == compare.m[2][2]
			);
}

template <typename numType> inline
bool mat3_t<numType>::operator != (const mat3_t<numType>& compare) const {
	return	(
				m[0][0] != compare.m[0][0] || m[0][1] != compare.m[0][1] || m[0][2] != compare.m[0][2] ||
				m[1][0] != compare.m[1][0] || m[1][1] != compare.m[1][1] || m[1][2] != compare.m[1][2] ||
				m[2][0] != compare.m[2][0] || m[2][1] != compare.m[2][1] || m[2][2] != compare.m[2][2]
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations (Declared in the 3D Vector header)
//---------------------------------------------------------------------
template <typename numType> inline
mat3_t<numType> vec3_t<numType>::operator + (const mat3_t<numType>& m) const {
	return mat3_t<numType>(
		v[0] + m.m[0][0], v[0] + m.m[0][1], v[0] + m.m[0][2],
		v[1] + m.m[1][0], v[1] + m.m[1][1], v[1] + m.m[1][2],
		v[2] + m.m[2][0], v[2] + m.m[2][1], v[2] + m.m[2][2]
	);
}

template <typename numType> inline
mat3_t<numType> vec3_t<numType>::operator - (const mat3_t<numType>& m) const {
	return mat3_t<numType>(
		v[0] - m.m[0][0], v[0] - m.m[0][1], v[0] - m.m[0][2],
		v[1] - m.m[1][0], v[1] - m.m[1][1], v[1] - m.m[1][2],
		v[2] - m.m[2][0], v[2] - m.m[2][1], v[2] - m.m[2][2]
	);
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator * (const mat3_t<numType>& m) const {
	return vec3_t<numType>(
		(m.m[0][0] * v[0]) + (m.m[0][1] * v[1]) + (m.m[0][2] * v[2]),
		(m.m[1][0] * v[0]) + (m.m[1][1] * v[1]) + (m.m[1][2] * v[2]),
		(m.m[2][0] * v[0]) + (m.m[2][1] * v[1]) + (m.m[2][2] * v[2])
	);
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator *= (const mat3_t<numType>& m) {
	*this = *this * m;
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Vector Operators
//---------------------------------------------------------------------
template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator + (const vec3_t<numType>& input) const {
	return mat3_t(
		m[0][0] + input.v[0], m[0][1] + input.v[1], m[0][2] + input.v[2],
		m[1][0] + input.v[0], m[1][1] + input.v[1], m[1][2] + input.v[2],
		m[2][0] + input.v[0], m[2][1] + input.v[1], m[2][2] + input.v[2]
	);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator - (const vec3_t<numType>& input) const {
	return mat3_t(
		m[0][0] - input.v[0], m[0][1] - input.v[1], m[0][2] - input.v[2],
		m[1][0] - input.v[0], m[1][1] - input.v[1], m[1][2] - input.v[2],
		m[2][0] - input.v[0], m[2][1] - input.v[1], m[2][2] - input.v[2]
	);
}

template <typename numType> inline
vec3_t<numType> mat3_t<numType>::operator * (const vec3_t<numType>& inVect) const {
	return vec3_t<numType>(
		(m[0][0] * inVect.v[0]) + (m[0][1] * inVect.v[1]) + (m[0][2] * inVect.v[2]),
		(m[1][0] * inVect.v[0]) + (m[1][1] * inVect.v[1]) + (m[1][2] * inVect.v[2]),
		(m[2][0] * inVect.v[0]) + (m[2][1] * inVect.v[1]) + (m[2][2] * inVect.v[2])
	);
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator = (const vec3_t<numType>& input) {
	m[0][0] = input.v[0]; m[0][1] = input.v[1]; m[0][2] = input.v[2];
	m[1][0] = input.v[0]; m[1][1] = input.v[1]; m[1][2] = input.v[2];
	m[2][0] = input.v[0]; m[2][1] = input.v[1]; m[2][2] = input.v[2];
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator += (const vec3_t<numType>& input) {
	m[0][0] += input.v[0]; m[0][1] += input.v[1]; m[0][2] += input.v[2];
	m[1][0] += input.v[0]; m[1][1] += input.v[1]; m[1][2] += input.v[2];
	m[2][0] += input.v[0]; m[2][1] += input.v[1]; m[2][2] += input.v[2];
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator -= (const vec3_t<numType>& input) {
	m[0][0] -= input.v[0]; m[0][1] -= input.v[1]; m[0][2] -= input.v[2];
	m[1][0] -= input.v[0]; m[1][1] -= input.v[1]; m[1][2] -= input.v[2];
	m[2][0] -= input.v[0]; m[2][1] -= input.v[1]; m[2][2] -= input.v[2];
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator + (numType input) const {
	return mat3_t<numType>(
		m[0][0] + input, m[0][1] + input, m[0][2] + input,
		m[1][0] + input, m[1][1] + input, m[1][2] + input,
		m[2][0] + input, m[2][1] + input, m[2][2] + input
	);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator - (numType input) const {
	return mat3_t<numType>(
		m[0][0] - input, m[0][1] - input, m[0][2] - input,
		m[1][0] - input, m[1][1] - input, m[1][2] - input,
		m[2][0] - input, m[2][1] - input, m[2][2] - input
	);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator * (numType input) const {
	return mat3_t<numType>(
		m[0][0] * input, m[0][1] * input, m[0][2] * input,
		m[1][0] * input, m[1][1] * input, m[1][2] * input,
		m[2][0] * input, m[2][1] * input, m[2][2] * input
	);
}

template <typename numType> inline
mat3_t<numType> mat3_t<numType>::operator / (numType input) const {
	input = numType( 1 ) / input;
	return mat3_t<numType>(
		m[0][0] * input, m[0][1] * input, m[0][2] * input,
		m[1][0] * input, m[1][1] * input, m[1][2] * input,
		m[2][0] * input, m[2][1] * input, m[2][2] * input
	);
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator = (numType input) {
	m[0][0] = input; m[0][1] = input; m[0][2] = input;
	m[1][0] = input; m[1][1] = input; m[1][2] = input;
	m[2][0] = input; m[2][1] = input; m[2][2] = input;
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator += (numType input) {
	m[0][0] += input; m[0][1] += input; m[0][2] += input;
	m[1][0] += input; m[1][1] += input; m[1][2] += input;
	m[2][0] += input; m[2][1] += input; m[2][2] += input;
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator -= (numType input) {
	m[0][0] -= input; m[0][1] -= input; m[0][2] -= input;
	m[1][0] -= input; m[1][1] -= input; m[1][2] -= input;
	m[2][0] -= input; m[2][1] -= input; m[2][2] -= input;
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator *= (numType input) {
	m[0][0] *= input; m[0][1] *= input; m[0][2] *= input;
	m[1][0] *= input; m[1][1] *= input; m[1][2] *= input;
	m[2][0] *= input; m[2][1] *= input; m[2][2] *= input;
	return *this;
}

template <typename numType> inline
mat3_t<numType>& mat3_t<numType>::operator /= (numType input) {
	m[0][0] /= input; m[0][1] /= input; m[0][2] /= input;
	m[1][0] /= input; m[1][1] /= input; m[1][2] /= input;
	m[2][0] /= input; m[2][1] /= input; m[2][2] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
mat3_t<numType> operator + (numType n, const mat3_t<numType>& m) {
	return m + n;
}

template <typename numType> inline
mat3_t<numType> operator - (numType n, const mat3_t<numType>& m) {
	return m - n;
}

template <typename numType> inline
mat3_t<numType> operator * (numType n, const mat3_t<numType>& m) {
	return m * n;
}

template <typename numType> inline
mat3_t<numType> operator / (numType n, const mat3_t<numType>& m) {
	return m / n;
}

} //end math namespace
} //end hamlibs namespace
#endif /*__MATRIX3_H__*/
