/*
 * 3d matrix class
 * recommended for use with non-integral types
 * 
 * NOTES:
 * Matrix is Column-Major
 * orientation is as follows:
 * ---------------------
 *		XX	XY	XZ
 *		YX	YY	YZ
 *		ZX	ZY	ZZ
 * ---------------------
*/

#ifndef __HL_MATH_MATRIX3_H__
#define __HL_MATH_MATRIX3_H__

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
			numType	xx, xy, xz,
					yx, yy, yz,
					zx, zy, zz;
		} index;
	};

	//hardhat construction
	mat3_t();
	mat3_t(numType n);
	mat3_t(const mat3_t<numType>&);
	mat3_t(mat3_t<numType>&&);
	//delegatoed constructor
	mat3_t(	numType inXX, numType inXY, numType inXZ,
			numType inYX, numType inYY, numType inYZ,
			numType inZX, numType inZY, numType inZZ);
	~mat3_t(){}

	//array operators
	numType*		operator	[]		(int);
	const numType*	operator	[]		(int) const;

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

//---------------------------------------------------------------------
//	3x3 Matrix Constructors (mostly delegated)
//---------------------------------------------------------------------
//construct all matricies as identity matricies unless stated otherwise
//all constructions use list-initializations and Delegations
template <typename numType> HL_IMPERATIVE
mat3_t<numType>::mat3_t() :
	mat3_t(
		numType(0), numType(0), numType(0),
		numType(0), numType(0), numType(0),
		numType(0), numType(0), numType(0)
	)
{}
template <typename numType> HL_IMPERATIVE
mat3_t<numType>::mat3_t(numType n) :
	mat3_t(
		n, numType(0), numType(0),
		numType(0), n, numType(0),
		numType(0), numType(0), n
	)
{}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>::mat3_t(const mat3_t<numType>& input) :
	mat3_t(
		input.m[0][0], input.m[0][1], input.m[0][2],
		input.m[1][0], input.m[1][1], input.m[1][2],
		input.m[2][0], input.m[2][1], input.m[2][2]
	)
{}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>::mat3_t(mat3_t<numType>&& input) :
	mat3_t(
		input.m[0][0], input.m[0][1], input.m[0][2],
		input.m[1][0], input.m[1][1], input.m[1][2],
		input.m[2][0], input.m[2][1], input.m[2][2]
	)
{}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>::mat3_t(	numType inXX, numType inXY, numType inXZ,
							numType inYX, numType inYY, numType inYZ,
							numType inZX, numType inZY, numType inZZ ) :
	m{
		{ inXX, inXY, inXZ },
		{ inYX, inYY, inYZ },
		{ inZX, inZY, inZZ }
	}
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType* mat3_t<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 3));
	return m[ index ];
}

template <typename numType> HL_IMPERATIVE
const numType* mat3_t<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 3));
	return m[ index ];
}

//---------------------------------------------------------------------
//	Matrix-Matrix Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator++ () {
	++m[0][0]; ++m[0][1]; ++m[0][2];
	++m[1][0]; ++m[1][1]; ++m[1][2];
	++m[2][0]; ++m[2][1]; ++m[2][2];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator-- () {
	--m[0][0]; --m[0][1]; --m[0][2];
	--m[1][0]; --m[1][1]; --m[1][2];
	--m[2][0]; --m[2][1]; --m[2][2];
	return *this;
}

//postfix operators
template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator++ (int) {
	return mat3_t<numType>(
		++m[0][0], ++m[0][1], ++m[0][2],
		++m[1][0], ++m[1][1], ++m[1][2],
		++m[2][0], ++m[2][1], ++m[2][2]
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator-- (int) {
	return mat3_t<numType>(
		--m[0][0], --m[0][1], --m[0][2],
		--m[1][0], --m[1][1], --m[1][2],
		--m[2][0], --m[2][1], --m[2][2]
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator + (const mat3_t<numType>& input) const {
	return mat3_t<numType>(
		m[0][0] + input.m[0][0], m[0][1] + input.m[0][1], m[0][2] + input.m[0][2],
		m[1][0] + input.m[1][0], m[1][1] + input.m[1][1], m[1][2] + input.m[1][2],
		m[2][0] + input.m[2][0], m[2][1] + input.m[2][1], m[2][2] + input.m[2][2]
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator - (const mat3_t<numType>& input) const {
	return mat3_t<numType>(
		m[0][0] - input.m[0][0], m[0][1] - input.m[0][1], m[0][2] - input.m[0][2],
		m[1][0] - input.m[1][0], m[1][1] - input.m[1][1], m[1][2] - input.m[1][2],
		m[2][0] - input.m[2][0], m[2][1] - input.m[2][1], m[2][2] - input.m[2][2]
	);
}

//for operations like "matrix3a = -matrix3b"
template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator - () const {
	return mat3_t<numType>(	-m[0][0], -m[0][1], -m[0][2],
							-m[1][0], -m[1][1], -m[1][2],
							-m[2][0], -m[2][1], -m[2][2]);
}

template <typename numType> HL_IMPERATIVE
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
	//if this is wrong, fuck you
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator = (const mat3_t<numType>& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator = (mat3_t<numType>&& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator += (const mat3_t<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator -= (const mat3_t<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator *= (const mat3_t<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
bool mat3_t<numType>::operator == (const mat3_t<numType>& compare) const {
	return	(
				m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] && m[0][2] == compare.m[0][2] &&
				m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1] && m[1][2] == compare.m[1][2] &&
				m[2][0] == compare.m[2][0] && m[2][1] == compare.m[2][1] && m[2][2] == compare.m[2][2]
			);
}

template <typename numType> HL_IMPERATIVE
bool mat3_t<numType>::operator != (const mat3_t<numType>& compare) const {
	return	(
				m[0][0] != compare.m[0][0] && m[0][1] != compare.m[0][1] && m[0][2] != compare.m[0][2] &&
				m[1][0] != compare.m[1][0] && m[1][1] != compare.m[1][1] && m[1][2] != compare.m[1][2] &&
				m[2][0] != compare.m[2][0] && m[2][1] != compare.m[2][1] && m[2][2] != compare.m[2][2]
			);
}

//---------------------------------------------------------------------
//	Matrix-Vector Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator + (const vec3_t<numType>& input) const {
	return mat3_t(
		m[0][0] + input.v[0], m[0][1] + input.v[1], m[0][2] + input.v[2],
		m[1][0] + input.v[0], m[1][1] + input.v[1], m[1][2] + input.v[2],
		m[2][0] + input.v[0], m[2][1] + input.v[1], m[2][2] + input.v[2]
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator - (const vec3_t<numType>& input) const {
	return mat3_t(
		m[0][0] - input.v[0], m[0][1] - input.v[1], m[0][2] - input.v[2],
		m[1][0] - input.v[0], m[1][1] - input.v[1], m[1][2] - input.v[2],
		m[2][0] - input.v[0], m[2][1] - input.v[1], m[2][2] - input.v[2]
	);
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType> mat3_t<numType>::operator * (const vec3_t<numType>& inVect) const {
	return vec3_t<numType>(
		(m[0][0] * inVect.v[0]) + (m[0][1] * inVect.v[1]) + (m[0][2] * inVect.v[2]),
		(m[1][0] * inVect.v[0]) + (m[1][1] * inVect.v[1]) + (m[1][2] * inVect.v[2]),
		(m[2][0] * inVect.v[0]) + (m[2][1] * inVect.v[1]) + (m[2][2] * inVect.v[2])
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator = (const vec3_t<numType>& input) {
	m[0][0] = input.v[0]; m[0][1] = input.v[1]; m[0][2] = input.v[2];
	m[1][0] = input.v[0]; m[1][1] = input.v[1]; m[1][2] = input.v[2];
	m[2][0] = input.v[0]; m[2][1] = input.v[1]; m[2][2] = input.v[2];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator += (const vec3_t<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator -= (const vec3_t<numType>& input) {
	*this = *this - input;
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator + (numType input) const {
	return mat3_t<numType>(
		m[0][0] + input, m[0][1] + input, m[0][2] + input,
		m[1][0] + input, m[1][1] + input, m[1][2] + input,
		m[2][0] + input, m[2][1] + input, m[2][2] + input
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator - (numType input) const {
	return mat3_t<numType>(
		m[0][0] - input, m[0][1] - input, m[0][2] - input,
		m[1][0] - input, m[1][1] - input, m[1][2] - input,
		m[2][0] - input, m[2][1] - input, m[2][2] - input
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator * (numType input) const {
	return mat3_t<numType>(
		m[0][0] * input, m[0][1] * input, m[0][2] * input,
		m[1][0] * input, m[1][1] * input, m[1][2] * input,
		m[2][0] * input, m[2][1] * input, m[2][2] * input
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> mat3_t<numType>::operator / (numType input) const {
	input = numType( 1 ) / input;
	return mat3_t<numType>(
		m[0][0] * input, m[0][1] * input, m[0][2] * input,
		m[1][0] * input, m[1][1] * input, m[1][2] * input,
		m[2][0] * input, m[2][1] * input, m[2][2] * input
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator = (numType input) {
	m[0][0] = input; m[0][1] = input; m[0][2] = input;
	m[1][0] = input; m[1][1] = input; m[1][2] = input;
	m[2][0] = input; m[2][1] = input; m[2][2] = input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType>& mat3_t<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace
#endif /*__MATRIX3_H__*/
