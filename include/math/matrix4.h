/*
 * 4d matrix class
 * recommended for use with non-integral types
 * 
 * NOTES:
 * Matrix is Row-Major
 * orientation is as follows:
 * ---------------------
 *		XX	XY	XZ	XW
 *		YX	YY	YZ	YW
 *		ZX	ZY	ZZ	ZW
 *		WX	WY	WZ	WW
 * ---------------------
*/

#ifndef __HL_MATH_MATRIX4_H__
#define __HL_MATH_MATRIX4_H__

#include "../utils/assert.h"
#include "math/fixed.h"
#include "vec4.h"

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat4 class
//---------------------------------------------------------------------
template <typename numType>
struct mat4_t {
	union {
		numType m[4][4];
        
		struct {
			numType	xx, xy, xz, xw,
					yx, yy, yz, yw,
					zx, zy, zz, zw,
					wx, wy, wz, ww;
		} index;
        
        struct {
            vec4_t<numType> x;
            vec4_t<numType> y;
            vec4_t<numType> z;
            vec4_t<numType> w;
        } row;
	};
    
    /*
     * Delegated Constructors
     * 
     * mat4_t()
     * mat4_t( numType n )
     * mat4_t( numType n0, numType n1, numType n2, ..., numType n15 )
     * mat4_t( vec4_t x, vec4_t y, vec4_t z, vec4_t w )
     * mat4_t( const mat4_t& )
     * mat4_t( mat4_t&& )
     */
	// Main Constructor
    constexpr mat4_t(
        numType inXX, numType inXY, numType inXZ, numType inXW,
        numType inYX, numType inYY, numType inYZ, numType inYW,
        numType inZX, numType inZY, numType inZZ, numType inZW,
        numType inWX, numType inWY, numType inWZ, numType inWW) :
        m{
            { inXX, inXY, inXZ, inXW },
            { inYX, inYY, inYZ, inYW },
            { inZX, inZY, inZZ, inZW },
            { inWX, inWY, inWZ, inWW }
        }
    {}
    
    constexpr mat4_t() :
        mat4_t(
            numType(0), numType(0), numType(0), numType(0),
            numType(0), numType(0), numType(0), numType(0),
            numType(0), numType(0), numType(0), numType(0),
            numType(0), numType(0), numType(0), numType(0)
        )
    {}
    
    constexpr mat4_t(numType n) :
        mat4_t(
            n, numType(0), numType(0), numType(0),
            numType(0), n, numType(0), numType(0),
            numType(0), numType(0), n, numType(0),
            numType(0), numType(0), numType(0), n
        )
    {}
    
    constexpr mat4_t(const mat3_t<numType>& input) :
        mat4_t(
            input.m[0][0], input.m[0][1], input.m[0][2], numType(0),
            input.m[1][0], input.m[1][1], input.m[1][2], numType(0),
            input.m[2][0], input.m[2][1], input.m[2][2], numType(0),
            numType(0), numType(0), numType(0), numType(1)
        )
    {}
    
    constexpr mat4_t(const mat4_t<numType>& input) :
        mat4_t(
            input.m[0][0], input.m[0][1], input.m[0][2], input.m[0][3],
            input.m[1][0], input.m[1][1], input.m[1][2], input.m[1][3],
            input.m[2][0], input.m[2][1], input.m[2][2], input.m[2][3],
            input.m[3][0], input.m[3][1], input.m[3][2], input.m[3][3]
        )
    {}
    
    constexpr mat4_t(mat3_t<numType>&& input) :
        mat4_t(
            input.m[0][0], input.m[0][1], input.m[0][2], numType(0),
            input.m[1][0], input.m[1][1], input.m[1][2], numType(0),
            input.m[2][0], input.m[2][1], input.m[2][2], numType(0),
            numType(0), numType(0), numType(0), numType(1)
        )
    {}
    
    constexpr mat4_t(mat4_t<numType>&& input) :
        mat4_t(
            input.m[0][0], input.m[0][1], input.m[0][2], input.m[0][3],
            input.m[1][0], input.m[1][1], input.m[1][2], input.m[1][3],
            input.m[2][0], input.m[2][1], input.m[2][2], input.m[2][3],
            input.m[3][0], input.m[3][1], input.m[3][2], input.m[3][3]
        )
    {}
    
    constexpr mat4_t(
        const vec4_t<numType>& x,
        const vec4_t<numType>& y,
        const vec4_t<numType>& z,
        const vec4_t<numType>& w
    ) : mat4_t(
            x.v[0], x.v[1], x.v[2], x.v[3],
            y.v[0], y.v[1], y.v[2], y.v[3],
            z.v[0], z.v[1], z.v[2], z.v[3],
            w.v[0], w.v[1], w.v[2], w.v[3]
        )
    {}
    
	~mat4_t() = default;
    
    // Subscripting Operators
	const numType*  operator    []      (int i) const { return m[i]; }
	inline numType* operator    []      (int i) { return m[i]; }
    
    // Conversions & Casting
    template <typename otherType>
    constexpr explicit operator mat4_t<otherType>() const {
        return mat4_t<otherType>{
            (otherType)m[0][0], (otherType)m[0][1], (otherType)m[0][2], (otherType)m[0][3],
            (otherType)m[1][0], (otherType)m[1][1], (otherType)m[1][2], (otherType)m[1][3],
            (otherType)m[2][0], (otherType)m[2][1], (otherType)m[2][2], (otherType)m[2][3],
            (otherType)m[3][0], (otherType)m[3][1], (otherType)m[3][2], (otherType)m[3][3]
        };
    }

	//matrix-matrix operators
	mat4_t&			operator	++		(); //prefix operators
	mat4_t&			operator	--		();
	mat4_t			operator	++		(int); //postfix operators
	mat4_t			operator	--		(int);
	mat4_t			operator	+		(const mat4_t<numType>& input) const;
	mat4_t			operator	-		(const mat4_t<numType>& input) const;
	mat4_t			operator	-		() const;
	mat4_t			operator	*		(const mat4_t<numType>& input) const;
	mat4_t&			operator	=		(const mat4_t<numType>& input);
	mat4_t&			operator	=		(mat4_t<numType>&& input);
	mat4_t&			operator	+=		(const mat4_t<numType>& input);
	mat4_t&			operator	-=		(const mat4_t<numType>& input);
	mat4_t&			operator	*=		(const mat4_t<numType>& input);
	bool			operator	==		(const mat4_t<numType>& input) const;
	bool			operator	!=		(const mat4_t<numType>& input) const;

	//matrix-vector operators
	mat4_t			operator	+		(const vec4_t<numType>&) const;
	mat4_t			operator	-		(const vec4_t<numType>&) const;
	vec4_t<numType>	operator	*		(const vec4_t<numType>&) const;
	mat4_t&			operator	=		(const vec4_t<numType>&);
	mat4_t&			operator	+=		(const vec4_t<numType>&);
	mat4_t&			operator	-=		(const vec4_t<numType>&);

	//matrix-scalar operators
	mat4_t			operator	+		(numType) const;
	mat4_t			operator	-		(numType) const;
	mat4_t			operator	*		(numType) const;
	mat4_t			operator	/		(numType) const;
	mat4_t&			operator	=		(numType);
	mat4_t&			operator	+=		(numType);
	mat4_t&			operator	-=		(numType);
	mat4_t&			operator	*=		(numType);
	mat4_t&			operator	/=		(numType);
};

/*
 * 4x4 Matrix Specializations
 */
HL_DECLARE_CLASS_TYPE(mat4f, mat4_t, float);
HL_DECLARE_CLASS_TYPE(mat4d, mat4_t, double);
HL_DECLARE_CLASS_TYPE(mat4i, mat4_t, int);
HL_DECLARE_CLASS_TYPE(mat4x, mat4_t, medp_t);
HL_DECLARE_CLASS_TYPE(mat4, mat4_t, HL_FLOAT);

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
mat4_t<numType> operator + (numType n, const mat4_t<numType>& m);

template <typename numType> inline
mat4_t<numType> operator - (numType n, const mat4_t<numType>& m);

template <typename numType> inline
mat4_t<numType> operator * (numType n, const mat4_t<numType>& m);

template <typename numType> inline
mat4_t<numType> operator / (numType n, const mat4_t<numType>& m);

//---------------------------------------------------------------------
//	Matrix-Matrix Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator++ () {
	++m[0][0]; ++m[0][1]; ++m[0][2]; ++m[0][3];
	++m[1][0]; ++m[1][1]; ++m[1][2]; ++m[1][3];
	++m[2][0]; ++m[2][1]; ++m[2][2]; ++m[2][3];
	++m[3][0]; ++m[3][1]; ++m[3][2]; ++m[3][3];
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator-- () {
	--m[0][0]; --m[0][1]; --m[0][2]; --m[0][3];
	--m[1][0]; --m[1][1]; --m[1][2]; --m[1][3];
	--m[2][0]; --m[2][1]; --m[2][2]; --m[2][3];
	--m[3][0]; --m[3][1]; --m[3][2]; --m[3][3];
	return *this;
}

//postfix operators
template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator++ (int) {
	return mat4_t<numType>(
		++m[0][0], ++m[0][1], ++m[0][2], ++m[0][3],
		++m[1][0], ++m[1][1], ++m[1][2], ++m[1][3],
		++m[2][0], ++m[2][1], ++m[2][2], ++m[2][3],
		++m[3][0], ++m[3][1], ++m[3][2], ++m[3][3]
	);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator-- (int) {
	return mat4_t<numType>(
		--m[0][0], --m[0][1], --m[0][2], --m[0][3],
		--m[1][0], --m[1][1], --m[1][2], --m[1][3],
		--m[2][0], --m[2][1], --m[2][2], --m[2][3],
		--m[3][0], --m[3][1], --m[3][2], --m[3][3]
	);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator + (const mat4_t<numType>& input) const {
	return mat4_t<numType>(
		m[0][0] + input.m[0][0], m[0][1] + input.m[0][1], m[0][2] + input.m[0][2], m[0][3] + input.m[0][3],
		m[1][0] + input.m[1][0], m[1][1] + input.m[1][1], m[1][2] + input.m[1][2], m[1][3] + input.m[1][3],
		m[2][0] + input.m[2][0], m[2][1] + input.m[2][1], m[2][2] + input.m[2][2], m[2][3] + input.m[2][3],
		m[3][0] + input.m[3][0], m[3][1] + input.m[3][1], m[3][2] + input.m[3][2], m[3][3] + input.m[3][3]
	);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator - (const mat4_t<numType>& input) const {
	return mat4_t<numType>(
		m[0][0] - input.m[0][0], m[0][1] - input.m[0][1], m[0][2] - input.m[0][2], m[0][3] - input.m[0][3],
		m[1][0] - input.m[1][0], m[1][1] - input.m[1][1], m[1][2] - input.m[1][2], m[1][3] - input.m[1][3],
		m[2][0] - input.m[2][0], m[2][1] - input.m[2][1], m[2][2] - input.m[2][2], m[2][3] - input.m[2][3],
		m[3][0] - input.m[3][0], m[3][1] - input.m[3][1], m[3][2] - input.m[3][2], m[3][3] - input.m[3][3]
	);
}

//for operations like "matrix4a = -matrix4b"
template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator - () const {
	return mat4_t<numType>(	-m[0][0], -m[0][1], -m[0][2], -m[0][3],
							-m[1][0], -m[1][1], -m[1][2], -m[1][3],
							-m[2][0], -m[2][1], -m[2][2], -m[2][3],
							-m[3][0], -m[3][1], -m[3][2], -m[3][3]);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator * (const mat4_t<numType>& input) const {
	return mat4_t<numType>(
	//X
		(m[0][0]*input.m[0][0]) + (m[0][1]*input.m[1][0]) + (m[0][2]*input.m[2][0]) + (m[0][3]*input.m[3][0]),
		(m[0][0]*input.m[0][1]) + (m[0][1]*input.m[1][1]) + (m[0][2]*input.m[2][1]) + (m[0][3]*input.m[3][1]),
		(m[0][0]*input.m[0][2]) + (m[0][1]*input.m[1][2]) + (m[0][2]*input.m[2][2]) + (m[0][3]*input.m[3][2]),
		(m[0][0]*input.m[0][3]) + (m[0][1]*input.m[1][3]) + (m[0][2]*input.m[2][3]) + (m[0][3]*input.m[3][3]),
	//Y
		(m[1][0]*input.m[0][0]) + (m[1][1]*input.m[1][0]) + (m[1][2]*input.m[2][0]) + (m[1][3]*input.m[3][0]),
		(m[1][0]*input.m[0][1]) + (m[1][1]*input.m[1][1]) + (m[1][2]*input.m[2][1]) + (m[1][3]*input.m[3][1]),
		(m[1][0]*input.m[0][2]) + (m[1][1]*input.m[1][2]) + (m[1][2]*input.m[2][2]) + (m[1][3]*input.m[3][2]),
		(m[1][0]*input.m[0][3]) + (m[1][1]*input.m[1][3]) + (m[1][2]*input.m[2][3]) + (m[1][3]*input.m[3][3]),
	//Z
		(m[2][0]*input.m[0][0]) + (m[2][1]*input.m[1][0]) + (m[2][2]*input.m[2][0]) + (m[2][3]*input.m[3][0]),
		(m[2][0]*input.m[0][1]) + (m[2][1]*input.m[1][1]) + (m[2][2]*input.m[2][1]) + (m[2][3]*input.m[3][1]),
		(m[2][0]*input.m[0][2]) + (m[2][1]*input.m[1][2]) + (m[2][2]*input.m[2][2]) + (m[2][3]*input.m[3][2]),
		(m[2][0]*input.m[0][3]) + (m[2][1]*input.m[1][3]) + (m[2][2]*input.m[2][3]) + (m[2][3]*input.m[3][3]),
	//W
		(m[3][0]*input.m[0][0]) + (m[3][1]*input.m[1][0]) + (m[3][2]*input.m[2][0]) + (m[3][3]*input.m[3][0]),
		(m[3][0]*input.m[0][1]) + (m[3][1]*input.m[1][1]) + (m[3][2]*input.m[2][1]) + (m[3][3]*input.m[3][1]),
		(m[3][0]*input.m[0][2]) + (m[3][1]*input.m[1][2]) + (m[3][2]*input.m[2][2]) + (m[3][3]*input.m[3][2]),
		(m[3][0]*input.m[0][3]) + (m[3][1]*input.m[1][3]) + (m[3][2]*input.m[2][3]) + (m[3][3]*input.m[3][3])
	);
	// I really hope this is correct
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator = (const mat4_t<numType>& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2]; m[0][3] = input.m[0][3];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2]; m[1][3] = input.m[1][3];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2]; m[2][3] = input.m[2][3];
	m[3][0] = input.m[3][0]; m[3][1] = input.m[3][1]; m[3][2] = input.m[3][2]; m[3][3] = input.m[3][3];
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator = (mat4_t<numType>&& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2]; m[0][3] = input.m[0][3];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2]; m[1][3] = input.m[1][3];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2]; m[2][3] = input.m[2][3];
	m[3][0] = input.m[3][0]; m[3][1] = input.m[3][1]; m[3][2] = input.m[3][2]; m[3][3] = input.m[3][3];
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator += (const mat4_t<numType>& input) {
	m[0][0] += input.m[0][0]; m[0][1] += input.m[0][1]; m[0][2] += input.m[0][2]; m[0][3] += input.m[0][3];
	m[1][0] += input.m[1][0]; m[1][1] += input.m[1][1]; m[1][2] += input.m[1][2]; m[1][3] += input.m[1][3];
	m[2][0] += input.m[2][0]; m[2][1] += input.m[2][1]; m[2][2] += input.m[2][2]; m[2][3] += input.m[2][3];
	m[3][0] += input.m[3][0]; m[3][1] += input.m[3][1]; m[3][2] += input.m[3][2]; m[3][3] += input.m[3][3];
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator -= (const mat4_t<numType>& input) {
	m[0][0] -= input.m[0][0]; m[0][1] -= input.m[0][1]; m[0][2] -= input.m[0][2]; m[0][3] -= input.m[0][3];
	m[1][0] -= input.m[1][0]; m[1][1] -= input.m[1][1]; m[1][2] -= input.m[1][2]; m[1][3] -= input.m[1][3];
	m[2][0] -= input.m[2][0]; m[2][1] -= input.m[2][1]; m[2][2] -= input.m[2][2]; m[2][3] -= input.m[2][3];
	m[3][0] -= input.m[3][0]; m[3][1] -= input.m[3][1]; m[3][2] -= input.m[3][2]; m[3][3] -= input.m[3][3];
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator *= (const mat4_t<numType>& input) {
	return *this = *this * input;
}

template <typename numType> inline
bool mat4_t<numType>::operator == (const mat4_t<numType>& compare) const {
	return	(
				m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] && m[0][2] == compare.m[0][2] && m[0][3] == compare.m[0][3] &&
				m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1] && m[1][2] == compare.m[1][2] && m[1][3] == compare.m[1][3] &&
				m[2][0] == compare.m[2][0] && m[2][1] == compare.m[2][1] && m[2][2] == compare.m[2][2] && m[2][3] == compare.m[2][3] &&
				m[3][0] == compare.m[3][0] && m[3][1] == compare.m[3][1] && m[3][2] == compare.m[3][2] && m[3][3] == compare.m[3][3]
			);
}

template <typename numType> inline
bool mat4_t<numType>::operator != (const mat4_t<numType>& compare) const {
	return	(
				m[0][0] != compare.m[0][0] || m[0][1] != compare.m[0][1] || m[0][2] != compare.m[0][2] || m[0][3] != compare.m[0][3] ||
				m[1][0] != compare.m[1][0] || m[1][1] != compare.m[1][1] || m[1][2] != compare.m[1][2] || m[1][3] != compare.m[1][3] ||
				m[2][0] != compare.m[2][0] || m[2][1] != compare.m[2][1] || m[2][2] != compare.m[2][2] || m[2][3] != compare.m[2][3] ||
				m[3][0] != compare.m[3][0] || m[3][1] != compare.m[3][1] || m[3][2] != compare.m[3][2] || m[3][3] != compare.m[3][3]
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations (Declared in the 4D Vector header)
//---------------------------------------------------------------------
template <typename numType> inline
mat4_t<numType> vec4_t<numType>::operator + (const mat4_t<numType>& m) const {
	return mat4_t<numType>(
		v[0] + m.m[0][0], v[0] + m.m[0][1], v[0] + m.m[0][2], v[0] + m.m[0][3],
		v[1] + m.m[1][0], v[1] + m.m[1][1], v[1] + m.m[1][2], v[1] + m.m[1][3],
		v[2] + m.m[2][0], v[2] + m.m[2][1], v[2] + m.m[2][2], v[2] + m.m[2][3],
		v[3] + m.m[3][0], v[3] + m.m[3][1], v[3] + m.m[3][2], v[3] + m.m[3][3]
	);
}

template <typename numType> inline
mat4_t<numType> vec4_t<numType>::operator - (const mat4_t<numType>& m) const {
	return mat4_t<numType>(
		v[0] - m.m[0][0], v[0] - m.m[0][1], v[0] - m.m[0][2], v[0] - m.m[0][3],
		v[1] - m.m[1][0], v[1] - m.m[1][1], v[1] - m.m[1][2], v[1] - m.m[1][3],
		v[2] - m.m[2][0], v[2] - m.m[2][1], v[2] - m.m[2][2], v[2] - m.m[2][3],
		v[3] - m.m[3][0], v[3] - m.m[3][1], v[3] - m.m[3][2], v[3] - m.m[3][3]
	);
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator * (const mat4_t<numType>& m) const {
	return vec4_t<numType>(
		(m.m[0][0] * v[0]) + (m.m[0][1] * v[1]) + (m.m[0][2] * v[2]) + (m.m[0][3] * v[3]),
		(m.m[1][0] * v[0]) + (m.m[1][1] * v[1]) + (m.m[1][2] * v[2]) + (m.m[1][3] * v[3]),
		(m.m[2][0] * v[0]) + (m.m[2][1] * v[1]) + (m.m[2][2] * v[2]) + (m.m[2][3] * v[3]),
		(m.m[3][0] * v[0]) + (m.m[3][1] * v[1]) + (m.m[3][2] * v[2]) + (m.m[3][3] * v[3])
	);
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator *= (const mat4_t<numType>& m) {
	*this = *this * m;
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Vector Operators
//---------------------------------------------------------------------
template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator + (const vec4_t<numType>& input) const {
	return mat4_t(
		m[0][0] + input.v[0], m[0][1] + input.v[1], m[0][2] + input.v[2], m[0][3] + input.v[3],
		m[1][0] + input.v[0], m[1][1] + input.v[1], m[1][2] + input.v[2], m[1][3] + input.v[3],
		m[2][0] + input.v[0], m[2][1] + input.v[1], m[2][2] + input.v[2], m[2][3] + input.v[3],
		m[3][0] + input.v[0], m[3][1] + input.v[1], m[3][2] + input.v[2], m[3][3] + input.v[3]
	);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator - (const vec4_t<numType>& input) const {
	return mat4_t(
		m[0][0] - input.v[0], m[0][1] - input.v[1], m[0][2] - input.v[2], m[0][3] - input.v[3],
		m[1][0] - input.v[0], m[1][1] - input.v[1], m[1][2] - input.v[2], m[1][3] - input.v[3],
		m[2][0] - input.v[0], m[2][1] - input.v[1], m[2][2] - input.v[2], m[2][3] - input.v[3],
		m[3][0] - input.v[0], m[3][1] - input.v[1], m[3][2] - input.v[2], m[3][3] - input.v[3]
	);
}

template <typename numType> inline
vec4_t<numType> mat4_t<numType>::operator * (const vec4_t<numType>& inVect) const {
	return vec4_t<numType>(
		(m[0][0] * inVect.v[0]) + (m[0][1] * inVect.v[1]) + (m[0][2] * inVect.v[2]) + (m[0][3] * inVect.v[3]),
		(m[1][0] * inVect.v[0]) + (m[1][1] * inVect.v[1]) + (m[1][2] * inVect.v[2]) + (m[1][3] * inVect.v[3]),
		(m[2][0] * inVect.v[0]) + (m[2][1] * inVect.v[1]) + (m[2][2] * inVect.v[2]) + (m[2][3] * inVect.v[3]),
		(m[3][0] * inVect.v[0]) + (m[3][1] * inVect.v[1]) + (m[3][2] * inVect.v[2]) + (m[3][3] * inVect.v[3])
	);
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator = (const vec4_t<numType>& input) {
	m[0][0] = input.v[0]; m[0][1] = input.v[1]; m[0][2] = input.v[2]; m[0][3] = input.v[3];
	m[1][0] = input.v[0]; m[1][1] = input.v[1]; m[1][2] = input.v[2]; m[1][3] = input.v[3];
	m[2][0] = input.v[0]; m[2][1] = input.v[1]; m[2][2] = input.v[2]; m[2][3] = input.v[3];
	m[3][0] = input.v[0]; m[3][1] = input.v[1]; m[3][2] = input.v[2]; m[3][3] = input.v[3];
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator += (const vec4_t<numType>& input) {
	m[0][0] += input.v[0]; m[0][1] += input.v[1]; m[0][2] += input.v[2]; m[0][3] += input.v[3];
	m[1][0] += input.v[0]; m[1][1] += input.v[1]; m[1][2] += input.v[2]; m[1][3] += input.v[3];
	m[2][0] += input.v[0]; m[2][1] += input.v[1]; m[2][2] += input.v[2]; m[2][3] += input.v[3];
	m[3][0] += input.v[0]; m[3][1] += input.v[1]; m[3][2] += input.v[2]; m[3][3] += input.v[3];
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator -= (const vec4_t<numType>& input) {
	m[0][0] -= input.v[0]; m[0][1] -= input.v[1]; m[0][2] -= input.v[2]; m[0][3] -= input.v[3];
	m[1][0] -= input.v[0]; m[1][1] -= input.v[1]; m[1][2] -= input.v[2]; m[1][3] -= input.v[3];
	m[2][0] -= input.v[0]; m[2][1] -= input.v[1]; m[2][2] -= input.v[2]; m[2][3] -= input.v[3];
	m[3][0] -= input.v[0]; m[3][1] -= input.v[1]; m[3][2] -= input.v[2]; m[3][3] -= input.v[3];
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator + (numType input) const {
	return mat4_t<numType>(
		m[0][0] + input, m[0][1] + input, m[0][2] + input, m[0][3] + input,
		m[1][0] + input, m[1][1] + input, m[1][2] + input, m[1][3] + input,
		m[2][0] + input, m[2][1] + input, m[2][2] + input, m[2][3] + input,
		m[3][0] + input, m[3][1] + input, m[3][2] + input, m[3][3] + input
	);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator - (numType input) const {
	return mat4_t<numType>(
		m[0][0] - input, m[0][1] - input, m[0][2] - input, m[0][3] - input,
		m[1][0] - input, m[1][1] - input, m[1][2] - input, m[1][3] - input,
		m[2][0] - input, m[2][1] - input, m[2][2] - input, m[2][3] - input,
		m[3][0] - input, m[3][1] - input, m[3][2] - input, m[3][3] - input
	);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator * (numType input) const {
	return mat4_t<numType>(
		m[0][0] * input, m[0][1] * input, m[0][2] * input, m[0][3] * input,
		m[1][0] * input, m[1][1] * input, m[1][2] * input, m[1][3] * input,
		m[2][0] * input, m[2][1] * input, m[2][2] * input, m[2][3] * input,
		m[3][0] * input, m[3][1] * input, m[3][2] * input, m[3][3] * input
	);
}

template <typename numType> inline
mat4_t<numType> mat4_t<numType>::operator / (numType input) const {
	return mat4_t<numType>(
		m[0][0] / input, m[0][1] / input, m[0][2] / input, m[0][3] / input,
		m[1][0] / input, m[1][1] / input, m[1][2] / input, m[1][3] / input,
		m[2][0] / input, m[2][1] / input, m[2][2] / input, m[2][3] / input,
		m[3][0] / input, m[3][1] / input, m[3][2] / input, m[3][3] / input
	);
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator = (numType input) {
	m[0][0] = input; m[0][1] = input; m[0][2] = input; m[0][3] = input;
	m[1][0] = input; m[1][1] = input; m[1][2] = input; m[1][3] = input;
	m[2][0] = input; m[2][1] = input; m[2][2] = input; m[2][3] = input;
	m[3][0] = input; m[3][1] = input; m[3][2] = input; m[3][3] = input;
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator += (numType input) {
	m[0][0] += input; m[0][1] += input; m[0][2] += input; m[0][3] += input;
	m[1][0] += input; m[1][1] += input; m[1][2] += input; m[1][3] += input;
	m[2][0] += input; m[2][1] += input; m[2][2] += input; m[2][3] += input;
	m[3][0] += input; m[3][1] += input; m[3][2] += input; m[3][3] += input;
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator -= (numType input) {
	m[0][0] -= input; m[0][1] -= input; m[0][2] -= input; m[0][3] -= input;
	m[1][0] -= input; m[1][1] -= input; m[1][2] -= input; m[1][3] -= input;
	m[2][0] -= input; m[2][1] -= input; m[2][2] -= input; m[2][3] -= input;
	m[3][0] -= input; m[3][1] -= input; m[3][2] -= input; m[3][3] -= input;
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator *= (numType input) {
	m[0][0] *= input; m[0][1] *= input; m[0][2] *= input; m[0][3] *= input;
	m[1][0] *= input; m[1][1] *= input; m[1][2] *= input; m[1][3] *= input;
	m[2][0] *= input; m[2][1] *= input; m[2][2] *= input; m[2][3] *= input;
	m[3][0] *= input; m[3][1] *= input; m[3][2] *= input; m[3][3] *= input;
	return *this;
}

template <typename numType> inline
mat4_t<numType>& mat4_t<numType>::operator /= (numType input) {
	m[0][0] /= input; m[0][1] /= input; m[0][2] /= input; m[0][3] /= input;
	m[1][0] /= input; m[1][1] /= input; m[1][2] /= input; m[1][3] /= input;
	m[2][0] /= input; m[2][1] /= input; m[2][2] /= input; m[2][3] /= input;
	m[3][0] /= input; m[3][1] /= input; m[3][2] /= input; m[3][3] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
mat4_t<numType> operator + (numType n, const mat4_t<numType>& m) {
	return m + n;
}

template <typename numType> inline
mat4_t<numType> operator - (numType n, const mat4_t<numType>& m) {
	return m - n;
}

template <typename numType> inline
mat4_t<numType> operator * (numType n, const mat4_t<numType>& m) {
	return m * n;
}

template <typename numType> inline
mat4_t<numType> operator / (numType n, const mat4_t<numType>& m) {
	return m / n;
}

} //end math namespace
} //end hamlibs namespace
#endif /*__MATRIX4_H__*/
