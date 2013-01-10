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
struct mat3 {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const mat3<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, mat3<type>& );
	
	numType m[3][3];
	numType	&xx, &xy, xz,
			&yx, &yy, &yz,
			&zx, &zy, &zz;

	//hardhat construction
	mat3();
	mat3(numType n);
	mat3(const mat3<numType>& input);
	//delegatoed constructor
	mat3(	numType inXX, numType inXY, numType inXZ,
			numType inYX, numType inYY, numType inYZ,
			numType inZX, numType inZY, numType inZZ);
	~mat3(){}

	//array operators
	numType*		operator	[]		(int);

	//matrix-matrix operators
	mat3&			operator	++		(); //prefix operators
	mat3&			operator	--		();
	mat3			operator	++		(int); //postfix operators
	mat3			operator	--		(int);
	mat3			operator	+		(const mat3<numType>& input) const;
	mat3			operator	-		(const mat3<numType>& input) const;
	mat3			operator	-		() const;
	mat3			operator	*		(const mat3<numType>& input) const;
	mat3&			operator	=		(const mat3<numType>& input);
	mat3&			operator	+=		(const mat3<numType>& input);
	mat3&			operator	-=		(const mat3<numType>& input);
	mat3&			operator	*=		(const mat3<numType>& input);
	bool			operator	==		(const mat3<numType>& input) const;
	bool			operator	!=		(const mat3<numType>& input) const;

	//matrix-vector operators
	mat3			operator	+		(const vec3<numType>&) const;
	mat3			operator	-		(const vec3<numType>&) const;
	vec3<numType>	operator	*		(const vec3<numType>&) const;
	mat3&			operator	=		(const vec3<numType>&);
	mat3&			operator	+=		(const vec3<numType>&);
	mat3&			operator	-=		(const vec3<numType>&);

	//matrix-scalar operators
	mat3			operator	+		(numType) const;
	mat3			operator	-		(numType) const;
	mat3			operator	*		(numType) const;
	mat3			operator	/		(numType) const;
	mat3&			operator	=		(numType);
	mat3&			operator	+=		(numType);
	mat3&			operator	-=		(numType);
	mat3&			operator	*=		(numType);
	mat3&			operator	/=		(numType);
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const mat3<type>& mat ) {
	sout
		<< mat.m[0][0] << " " << mat.m[0][1] << " " << mat.m[0][2] << " "
		<< mat.m[1][0] << " " << mat.m[1][1] << " " << mat.m[1][2] << " "
		<< mat.m[2][0] << " " << mat.m[2][1] << " " << mat.m[2][2];
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, mat3<type>& mat ) {
	stin
		>> mat.m[0][0] >> mat.m[0][1] >> mat.m[0][2]
		>> mat.m[1][0] >> mat.m[1][1] >> mat.m[1][2]
		>> mat.m[2][0] >> mat.m[2][1] >> mat.m[2][2];
	return stin;
}

//---------------------------------------------------------------------
//	3x3 Matrix Constructors (mostly delegated)
//---------------------------------------------------------------------
//construct all matricies as identity matricies unless stated otherwise
//all constructions use list-initializations and Delegations
template <typename numType> HL_IMPERATIVE
mat3<numType>::mat3() :
	mat3(
		numType(0), numType(0), numType(0),
		numType(0), numType(0), numType(0),
		numType(0), numType(0), numType(0)
	)
{}
template <typename numType> HL_IMPERATIVE
mat3<numType>::mat3(numType n) :
	mat3(
		n, numType(0), numType(0),
		numType(0), n, numType(0),
		numType(0), numType(0), n
	)
{}

template <typename numType> HL_IMPERATIVE
mat3<numType>::mat3(const mat3<numType>& input) :
	mat3(
		input.m[0][0], input.m[0][1], input.m[0][2],
		input.m[1][0], input.m[1][1], input.m[1][2],
		input.m[2][0], input.m[2][1], input.m[2][2]
	)
{}

template <typename numType> HL_IMPERATIVE
mat3<numType>::mat3(	numType inXX, numType inXY, numType inXZ,
						numType inYX, numType inYY, numType inYZ,
						numType inZX, numType inZY, numType inZZ) :
	m{
		{ inXX, inXY, inXZ },
		{ inYX, inYY, inYZ },
		{ inZX, inZY, inZZ }
	},
	xx( m[0][0] ), xy( m[0][1] ), xz( m[0][2] ),
	yx( m[1][0] ), yy( m[1][1] ), yz( m[1][2] ),
	zx( m[2][0] ), zy( m[2][1] ), zz( m[2][2] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType* mat3<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 3));
	return m[ index ];
}

//---------------------------------------------------------------------
//	Matrix-Matrix Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator++ () {
	++m[0][0]; ++m[0][1]; ++m[0][2];
	++m[1][0]; ++m[1][1]; ++m[1][2];
	++m[2][0]; ++m[2][1]; ++m[2][2];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator-- () {
	--m[0][0]; --m[0][1]; --m[0][2];
	--m[1][0]; --m[1][1]; --m[1][2];
	--m[2][0]; --m[2][1]; --m[2][2];
	return *this;
}

//postfix operators
template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator++ (int) {
	return mat3<numType>(
		++m[0][0], ++m[0][1], ++m[0][2],
		++m[1][0], ++m[1][1], ++m[1][2],
		++m[2][0], ++m[2][1], ++m[2][2]
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator-- (int) {
	return mat3<numType>(
		--m[0][0], --m[0][1], --m[0][2],
		--m[1][0], --m[1][1], --m[1][2],
		--m[2][0], --m[2][1], --m[2][2]
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator + (const mat3<numType>& input) const {
	return mat3<numType>(
		m[0][0] + input.m[0][0], m[0][1] + input.m[0][1], m[0][2] + input.m[0][2],
		m[1][0] + input.m[1][0], m[1][1] + input.m[1][1], m[1][2] + input.m[1][2],
		m[2][0] + input.m[2][0], m[2][1] + input.m[2][1], m[2][2] + input.m[2][2]
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator - (const mat3<numType>& input) const {
	return mat3<numType>(
		m[0][0] - input.m[0][0], m[0][1] - input.m[0][1], m[0][2] - input.m[0][2],
		m[1][0] - input.m[1][0], m[1][1] - input.m[1][1], m[1][2] - input.m[1][2],
		m[2][0] - input.m[2][0], m[2][1] - input.m[2][1], m[2][2] - input.m[2][2]
	);
}

//for operations like "matrix3a = -matrix3b"
template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator - () const {
	return mat3<numType>(	-m[0][0], -m[0][1], -m[0][2],
							-m[1][0], -m[1][1], -m[1][2],
							-m[2][0], -m[2][1], -m[2][2]);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator * (const mat3<numType>& input) const {
	return mat3<numType>(
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
mat3<numType>& mat3<numType>::operator = (const mat3<numType>& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator += (const mat3<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator -= (const mat3<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator *= (const mat3<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
bool mat3<numType>::operator == (const mat3<numType>& compare) const {
	return	(
				m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] && m[0][2] == compare.m[0][2] &&
				m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1] && m[1][2] == compare.m[1][2] &&
				m[2][0] == compare.m[2][0] && m[2][1] == compare.m[2][1] && m[2][2] == compare.m[2][2]
			);
}

template <typename numType> HL_IMPERATIVE
bool mat3<numType>::operator != (const mat3<numType>& compare) const {
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
mat3<numType> mat3<numType>::operator + (const vec3<numType>& input) const {
	return mat3(
		m[0][0] + input.x, m[0][1] + input.y, m[0][2] + input.z,
		m[1][0] + input.x, m[1][1] + input.y, m[1][2] + input.z,
		m[2][0] + input.x, m[2][1] + input.y, m[2][2] + input.z
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator - (const vec3<numType>& input) const {
	return mat3(
		m[0][0] - input.x, m[0][1] - input.y, m[0][2] - input.z,
		m[1][0] - input.x, m[1][1] - input.y, m[1][2] - input.z,
		m[2][0] - input.x, m[2][1] - input.y, m[2][2] - input.z
	);
}

template <typename numType> HL_IMPERATIVE
vec3<numType> mat3<numType>::operator * (const vec3<numType>& inVect) const {
	return vec3<numType>(
		(m[0][0] * inVect.x) + (m[0][1] * inVect.y) + (m[0][2] * inVect.z),
		(m[1][0] * inVect.x) + (m[1][1] * inVect.y) + (m[1][2] * inVect.z),
		(m[2][0] * inVect.x) + (m[2][1] * inVect.y) + (m[2][2] * inVect.z)
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator = (const vec3<numType>& input) {
	m[0][0] = input.x; m[0][1] = input.y; m[0][2] = input.z;
	m[1][0] = input.x; m[1][1] = input.y; m[1][2] = input.z;
	m[2][0] = input.x; m[2][1] = input.y; m[2][2] = input.z;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator += (const vec3<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator -= (const vec3<numType>& input) {
	*this = *this - input;
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator + (numType input) const {
	return mat3<numType>(
		m[0][0] + input, m[0][1] + input, m[0][2] + input,
		m[1][0] + input, m[1][1] + input, m[1][2] + input,
		m[2][0] + input, m[2][1] + input, m[2][2] + input
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator - (numType input) const {
	return mat3<numType>(
		m[0][0] - input, m[0][1] - input, m[0][2] - input,
		m[1][0] - input, m[1][1] - input, m[1][2] - input,
		m[2][0] - input, m[2][1] - input, m[2][2] - input
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator * (numType input) const {
	return mat3<numType>(
		m[0][0] * input, m[0][1] * input, m[0][2] * input,
		m[1][0] * input, m[1][1] * input, m[1][2] * input,
		m[2][0] * input, m[2][1] * input, m[2][2] * input
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType> mat3<numType>::operator / (numType input) const {
	return mat3<numType>(
		m[0][0] / input, m[0][1] / input, m[0][2] / input,
		m[1][0] / input, m[1][1] / input, m[1][2] / input,
		m[2][0] / input, m[2][1] / input, m[2][2] / input
	);
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator = (numType input) {
	m[0][0] = input; m[0][1] = input; m[0][2] = input;
	m[1][0] = input; m[1][1] = input; m[1][2] = input;
	m[2][0] = input; m[2][1] = input; m[2][2] = input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat3<numType>& mat3<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace
#endif /*__MATRIX3_H__*/
