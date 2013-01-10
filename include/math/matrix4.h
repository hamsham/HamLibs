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

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat4 class
//---------------------------------------------------------------------
template <typename numType>
struct mat4 {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const mat4<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, mat4<type>& );
	
	numType m[4][4];
	numType	&xx, &xy, &xz, &xw,
			&yx, &yy, &yz, &yw,
			&zx, &zy, &zz, &zw,
			&wx, &wy, &wz, &ww;

	//hardhat construction
	mat4();
	mat4(numType n);
	mat4(const mat4<numType>& input);
	//delegated constructor
	mat4(	numType inXX, numType inX, numType inXZ, numType inXW,
			numType inYX, numType inYY, numType inYZ, numType inYW,
			numType inZX, numType inZ, numType inZZ, numType inZW,
			numType inWX, numType inWY, numType inWZ, numType inWW);
	~mat4(){}

	//array operators
	numType*		operator	[]		(int);

	//matrix-matrix operators
	mat4&			operator	++		(); //prefix operators
	mat4&			operator	--		();
	mat4			operator	++		(int); //postfix operators
	mat4			operator	--		(int);
	mat4			operator	+		(const mat4<numType>& input) const;
	mat4			operator	-		(const mat4<numType>& input) const;
	mat4			operator	-		() const;
	mat4			operator	*		(const mat4<numType>& input) const;
	mat4&			operator	=		(const mat4<numType>& input);
	mat4&			operator	+=		(const mat4<numType>& input);
	mat4&			operator	-=		(const mat4<numType>& input);
	mat4&			operator	*=		(const mat4<numType>& input);
	bool			operator	==		(const mat4<numType>& input) const;
	bool			operator	!=		(const mat4<numType>& input) const;

	//matrix-vector operators
	mat4			operator	+		(const vec4<numType>&) const;
	mat4			operator	-		(const vec4<numType>&) const;
	vec4<numType>	operator	*		(const vec4<numType>&) const;
	mat4&			operator	=		(const vec4<numType>&);
	mat4&			operator	+=		(const vec4<numType>&);
	mat4&			operator	-=		(const vec4<numType>&);

	//matrix-scalar operators
	mat4			operator	+		(numType) const;
	mat4			operator	-		(numType) const;
	mat4			operator	*		(numType) const;
	mat4			operator	/		(numType) const;
	mat4&			operator	=		(numType);
	mat4&			operator	+=		(numType);
	mat4&			operator	-=		(numType);
	mat4&			operator	*=		(numType);
	mat4&			operator	/=		(numType);
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const mat4<type>& mat ) {
	sout
		<< mat.m[0][0] << " " << mat.m[0][1] << " " << mat.m[0][2] << " " << mat.m[0][3] << " "
		<< mat.m[1][0] << " " << mat.m[1][1] << " " << mat.m[1][2] << " " << mat.m[1][3] << " "
		<< mat.m[2][0] << " " << mat.m[2][1] << " " << mat.m[2][2] << " " << mat.m[2][3] << " "
		<< mat.m[3][0] << " " << mat.m[3][1] << " " << mat.m[3][2] << " " << mat.m[3][3];
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, mat4<type>& mat ) {
	stin
		>> mat.m[0][0] >> mat.m[0][1] >> mat.m[0][2] >> mat.m[0][3]
		>> mat.m[1][0] >> mat.m[1][1] >> mat.m[1][2] >> mat.m[1][3]
		>> mat.m[2][0] >> mat.m[2][1] >> mat.m[2][2] >> mat.m[2][3]
		>> mat.m[3][0] >> mat.m[3][1] >> mat.m[3][2] >> mat.m[3][3];
	return stin;
}

//---------------------------------------------------------------------
//	4x4 Matrix Constructors (mostly delegated)
//---------------------------------------------------------------------
//all constructions use list-initializations and Delegations
template <typename numType> HL_IMPERATIVE
mat4<numType>::mat4() :
	mat4(
		numType(0), numType(0), numType(0), numType(0),
		numType(0), numType(0), numType(0), numType(0),
		numType(0), numType(0), numType(0), numType(0),
		numType(0), numType(0), numType(0), numType(0)
	)
{}
//all constructions use list-initializations and Delegations
template <typename numType> HL_IMPERATIVE
mat4<numType>::mat4(numType n) :
	mat4(
		n, numType(0), numType(0), numType(0),
		numType(0), n, numType(0), numType(0),
		numType(0), numType(0), n, numType(0),
		numType(0), numType(0), numType(0), n
	)
{}

template <typename numType> HL_IMPERATIVE
mat4<numType>::mat4(const mat4<numType>& input) :
	mat4(
		input.m[0][0], input.m[0][1], input.m[0][2], input.m[0][3],
		input.m[1][0], input.m[1][1], input.m[1][2], input.m[1][3],
		input.m[2][0], input.m[2][1], input.m[2][2], input.m[2][3],
		input.m[3][0], input.m[3][1], input.m[3][2], input.m[3][3]
	)
{}

template <typename numType> HL_IMPERATIVE
mat4<numType>::mat4(	numType inXX, numType inXY, numType inXZ, numType inXW,
						numType inYX, numType inYY, numType inYZ, numType inYW,
						numType inZX, numType inZY, numType inZZ, numType inZW,
						numType inWX, numType inWY, numType inWZ, numType inWW) :
	m{
		{ inXX, inXY, inXZ, inXW },
		{ inYX, inYY, inYZ, inYW },
		{ inZX, inZY, inZZ, inZW },
		{ inWX, inWY, inWZ, inWW }
	},
	xx( m[0][0] ), xy( m[0][1] ), xz( m[0][2] ), xw( m[0][3] ),
	yx( m[1][0] ), yy( m[1][1] ), yz( m[1][2] ), yw( m[1][3] ),
	zx( m[2][0] ), zy( m[2][1] ), zz( m[2][2] ), zw( m[2][3] ),
	wx( m[3][0] ), wy( m[3][1] ), wz( m[3][2] ), ww( m[3][3] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType* mat4<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 4));
	return m[ index ];
}

//---------------------------------------------------------------------
//	Matrix-Matrix Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator++ () {
	++m[0][0]; ++m[0][1]; ++m[0][2]; ++m[0][3];
	++m[1][0]; ++m[1][1]; ++m[1][2]; ++m[1][3];
	++m[2][0]; ++m[2][1]; ++m[2][2]; ++m[2][3];
	++m[3][0]; ++m[3][1]; ++m[3][2]; ++m[3][3];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator-- () {
	--m[0][0]; --m[0][1]; --m[0][2]; --m[0][3];
	--m[1][0]; --m[1][1]; --m[1][2]; --m[1][3];
	--m[2][0]; --m[2][1]; --m[2][2]; --m[2][3];
	--m[3][0]; --m[3][1]; --m[3][2]; --m[3][3];
	return *this;
}

//postfix operators
template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator++ (int) {
	return mat4<numType>(
		++m[0][0], ++m[0][1], ++m[0][2], ++m[0][3],
		++m[1][0], ++m[1][1], ++m[1][2], ++m[1][3],
		++m[2][0], ++m[2][1], ++m[2][2], ++m[2][3],
		++m[3][0], ++m[3][1], ++m[3][2], ++m[3][3]
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator-- (int) {
	return mat4<numType>(
		--m[0][0], --m[0][1], --m[0][2], --m[0][3],
		--m[1][0], --m[1][1], --m[1][2], --m[1][3],
		--m[2][0], --m[2][1], --m[2][2], --m[2][3],
		--m[3][0], --m[3][1], --m[3][2], --m[3][3]
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator + (const mat4<numType>& input) const {
	return mat4<numType>(
		m[0][0] + input.m[0][0], m[0][1] + input.m[0][1], m[0][2] + input.m[0][2], m[0][3] + input.m[0][3],
		m[1][0] + input.m[1][0], m[1][1] + input.m[1][1], m[1][2] + input.m[1][2], m[1][3] + input.m[1][3],
		m[2][0] + input.m[2][0], m[2][1] + input.m[2][1], m[2][2] + input.m[2][2], m[2][3] + input.m[2][3],
		m[3][0] + input.m[3][0], m[3][1] + input.m[3][1], m[3][2] + input.m[3][2], m[3][3] + input.m[3][3]
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator - (const mat4<numType>& input) const {
	return mat4<numType>(
		m[0][0] - input.m[0][0], m[0][1] - input.m[0][1], m[0][2] - input.m[0][2], m[0][3] - input.m[0][3],
		m[1][0] - input.m[1][0], m[1][1] - input.m[1][1], m[1][2] - input.m[1][2], m[1][3] - input.m[1][3],
		m[2][0] - input.m[2][0], m[2][1] - input.m[2][1], m[2][2] - input.m[2][2], m[2][3] - input.m[2][3],
		m[3][0] - input.m[3][0], m[3][1] - input.m[3][1], m[3][2] - input.m[3][2], m[3][3] - input.m[3][3]
	);
}

//for operations like "matrix4a = -matrix4b"
template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator - () const {
	return mat4<numType>(	-m[0][0], -m[0][1], -m[0][2], -m[0][3],
							-m[1][0], -m[1][1], -m[1][2], -m[1][3],
							-m[2][0], -m[2][1], -m[2][2], -m[2][3],
							-m[3][0], -m[3][1], -m[3][2], -m[3][3]);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator * (const mat4<numType>& input) const {
	return mat4<numType>(
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
	//if this is wrong, fuck you
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator = (const mat4<numType>& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1]; m[0][2] = input.m[0][2]; m[0][3] = input.m[0][3];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1]; m[1][2] = input.m[1][2]; m[1][3] = input.m[1][3];
	m[2][0] = input.m[2][0]; m[2][1] = input.m[2][1]; m[2][2] = input.m[2][2]; m[2][3] = input.m[2][3];
	m[3][0] = input.m[3][0]; m[3][1] = input.m[3][1]; m[3][2] = input.m[3][2]; m[3][3] = input.m[3][3];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator += (const mat4<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator -= (const mat4<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator *= (const mat4<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
bool mat4<numType>::operator == (const mat4<numType>& compare) const {
	return	(
				m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] && m[0][2] == compare.m[0][2] && m[0][3] == compare.m[0][3] &&
				m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1] && m[1][2] == compare.m[1][2] && m[1][3] == compare.m[1][3] &&
				m[2][0] == compare.m[2][0] && m[2][1] == compare.m[2][1] && m[2][2] == compare.m[2][2] && m[2][3] == compare.m[2][3] &&
				m[3][0] == compare.m[3][0] && m[3][1] == compare.m[3][1] && m[3][2] == compare.m[3][2] && m[3][3] == compare.m[3][3]
			);
}

template <typename numType> HL_IMPERATIVE
bool mat4<numType>::operator != (const mat4<numType>& compare) const {
	return	(
				m[0][0] != compare.m[0][0] && m[0][1] != compare.m[0][1] && m[0][2] != compare.m[0][2] && m[0][3] != compare.m[0][3] &&
				m[1][0] != compare.m[1][0] && m[1][1] != compare.m[1][1] && m[1][2] != compare.m[1][2] && m[1][3] != compare.m[1][3] &&
				m[2][0] != compare.m[2][0] && m[2][1] != compare.m[2][1] && m[2][2] != compare.m[2][2] && m[2][3] != compare.m[2][3] &&
				m[3][0] != compare.m[3][0] && m[3][1] != compare.m[3][1] && m[3][2] != compare.m[3][2] && m[3][3] != compare.m[3][3]
			);
}

//---------------------------------------------------------------------
//	Matrix-Vector Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator + (const vec4<numType>& input) const {
	return mat4(
		m[0][0] + input.x, m[0][1] + input.y, m[0][2] + input.z, m[0][3] + input.w,
		m[1][0] + input.x, m[1][1] + input.y, m[1][2] + input.z, m[1][3] + input.w,
		m[2][0] + input.x, m[2][1] + input.y, m[2][2] + input.z, m[2][3] + input.w,
		m[3][0] + input.x, m[3][1] + input.y, m[3][2] + input.z, m[3][3] + input.w
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator - (const vec4<numType>& input) const {
	return mat4(
		m[0][0] - input.x, m[0][1] - input.y, m[0][2] - input.z, m[0][3] - input.w,
		m[1][0] - input.x, m[1][1] - input.y, m[1][2] - input.z, m[1][3] - input.w,
		m[2][0] - input.x, m[2][1] - input.y, m[2][2] - input.z, m[2][3] - input.w,
		m[3][0] - input.x, m[3][1] - input.y, m[3][2] - input.z, m[3][3] - input.w
	);
}

template <typename numType> HL_IMPERATIVE
vec4<numType> mat4<numType>::operator * (const vec4<numType>& inVect) const {
	return vec4<numType>(
		(m[0][0] * inVect.x) + (m[0][1] * inVect.y) + (m[0][2] * inVect.z) + (m[0][3] * inVect.w),
		(m[1][0] * inVect.x) + (m[1][1] * inVect.y) + (m[1][2] * inVect.z) + (m[1][3] * inVect.w),
		(m[2][0] * inVect.x) + (m[2][1] * inVect.y) + (m[2][2] * inVect.z) + (m[2][3] * inVect.w),
		(m[3][0] * inVect.x) + (m[3][1] * inVect.y) + (m[3][2] * inVect.z) + (m[3][3] * inVect.w)
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator = (const vec4<numType>& input) {
	m[0][0] = input.x; m[0][1] = input.y; m[0][2] = input.z; m[0][3] = input.w;
	m[1][0] = input.x; m[1][1] = input.y; m[1][2] = input.z; m[1][3] = input.w;
	m[2][0] = input.x; m[2][1] = input.y; m[2][2] = input.z; m[2][3] = input.w;
	m[3][0] = input.x; m[3][1] = input.y; m[3][2] = input.z; m[3][3] = input.w;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator += (const vec4<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator -= (const vec4<numType>& input) {
	*this = *this - input;
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator + (numType input) const {
	return mat4<numType>(
		m[0][0] + input, m[0][1] + input, m[0][2] + input, m[0][3] + input,
		m[1][0] + input, m[1][1] + input, m[1][2] + input, m[1][3] + input,
		m[2][0] + input, m[2][1] + input, m[2][2] + input, m[2][3] + input,
		m[3][0] + input, m[3][1] + input, m[3][2] + input, m[3][3] + input
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator - (numType input) const {
	return mat4<numType>(
		m[0][0] - input, m[0][1] - input, m[0][2] - input, m[0][3] - input,
		m[1][0] - input, m[1][1] - input, m[1][2] - input, m[1][3] - input,
		m[2][0] - input, m[2][1] - input, m[2][2] - input, m[2][3] - input,
		m[3][0] - input, m[3][1] - input, m[3][2] - input, m[3][3] - input
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator * (numType input) const {
	return mat4<numType>(
		m[0][0] * input, m[0][1] * input, m[0][2] * input, m[0][3] * input,
		m[1][0] * input, m[1][1] * input, m[1][2] * input, m[1][3] * input,
		m[2][0] * input, m[2][1] * input, m[2][2] * input, m[2][3] * input,
		m[3][0] * input, m[3][1] * input, m[3][2] * input, m[3][3] * input
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType> mat4<numType>::operator / (numType input) const {
	return mat4<numType>(
		m[0][0] / input, m[0][1] / input, m[0][2] / input, m[0][3] / input,
		m[1][0] / input, m[1][1] / input, m[1][2] / input, m[1][3] / input,
		m[2][0] / input, m[2][1] / input, m[2][2] / input, m[2][3] / input,
		m[3][0] / input, m[3][1] / input, m[3][2] / input, m[3][3] / input
	);
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator = (numType input) {
	m[0][0] = input; m[0][1] = input; m[0][2] = input; m[0][3] = input;
	m[1][0] = input; m[1][1] = input; m[1][2] = input; m[1][3] = input;
	m[2][0] = input; m[2][1] = input; m[2][2] = input; m[2][3] = input;
	m[3][0] = input; m[3][1] = input; m[3][2] = input; m[3][3] = input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat4<numType>& mat4<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace
#endif /*__MATRIX4_H__*/
