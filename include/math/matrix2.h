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

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat2 class
//---------------------------------------------------------------------
template <typename numType>
struct mat2 {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const mat2<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, mat2<type>& );
	
	numType	m[2][2];
	numType	&xx, &xy,
			&yx, &yy; // these references are attached to the array above during construction

	//hardhat construction
	mat2();
	mat2(numType n);
	mat2(const mat2<numType>& input);
	//delegated constructor
	mat2(	numType inXX, numType inXY,
			numType inYX, numType inYY
	);
	~mat2() {};

	//array operators
	numType*		operator	[]		(int);

	//mat-mat operators
	mat2&			operator	++		();			//prefix operators
	mat2&			operator	--		();
	mat2			operator	++		(int);	//postfix operators
	mat2			operator	--		(int);
	mat2			operator	+		(const mat2<numType>& input) const;
	mat2			operator	-		(const mat2<numType>& input) const;
	mat2			operator	-		() const;
	mat2			operator	*		(const mat2<numType>& input) const;
	mat2&			operator	=		(const mat2<numType>& input);
	mat2&			operator	+=		(const mat2<numType>& input);
	mat2&			operator	-=		(const mat2<numType>& input);
	mat2&			operator	*=		(const mat2<numType>& input);
	bool			operator	==		(const mat2<numType>& input) const;
	bool			operator	!=		(const mat2<numType>& input) const;

	//mat-vector operators
	mat2			operator	+		(const vec2<numType>&) const;
	mat2			operator	-		(const vec2<numType>&) const;
	vec2<numType>	operator	*		(const vec2<numType>&) const;
	mat2&			operator	=		(const vec2<numType>&);
	mat2&			operator	+=		(const vec2<numType>&);
	mat2&			operator	-=		(const vec2<numType>&);

	//mat-scalar operators
	mat2			operator	+		(numType) const;
	mat2			operator	-		(numType) const;
	mat2			operator	*		(numType) const;
	mat2			operator	/		(numType) const;
	mat2&			operator	=		(numType);
	mat2&			operator	+=		(numType);
	mat2&			operator	-=		(numType);
	mat2&			operator	*=		(numType);
	mat2&			operator	/=		(numType);
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const mat2<type>& mat ) {
	sout
		<< mat.m[0][0] << " " << mat.m[0][1] << " "
		<< mat.m[1][0] << " " << mat.m[1][1];
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, mat2<type>& mat ) {
	stin
		>> mat.m[0][0] >> mat.m[0][1]
		>> mat.m[1][0] >> mat.m[1][1];
	return stin;
}

//---------------------------------------------------------------------
//	2x2 Matrix Constructors (mostly delegated)
//---------------------------------------------------------------------
//all constructions use list-initializations and Delegations
template <typename numType> HL_IMPERATIVE
mat2<numType>::mat2() :
	mat2(
		numType(0), numType(0),
		numType(0), numType(0)
	)
{}
template <typename numType> HL_IMPERATIVE
mat2<numType>::mat2(numType n) :
	mat2(
		n, numType(0),
		numType(0), n
	)
{}

template <typename numType> HL_IMPERATIVE
mat2<numType>::mat2(const mat2<numType>& input) :
	mat2(
		input.m[0][0], input.m[0][1],
		input.m[1][0], input.m[1][1]
	)
{}

template <typename numType> HL_IMPERATIVE
mat2<numType>::mat2(	numType inXX, numType inXY,
						numType inYX, numType inYY) :
	m{
		{ inXX, inXY },
		{ inYX, inYY }
	},
	xx( m[0][0] ), xy( m[0][1] ),
	yx( m[1][0] ), yy( m[1][1] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType* mat2<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 2));
	return m[ index ];
}

//---------------------------------------------------------------------
//	mat-mat Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator++ () {
	++m[0][0]; ++m[0][1];
	++m[1][0]; ++m[1][1];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator-- () {
	--m[0][0]; --m[0][1];
	--m[1][0]; --m[1][1];
	return *this;
}

//postfix operators
template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator++ (int) {
	return mat2<numType>(
		++m[0][0], ++m[0][1],
		++m[1][0], ++m[1][1]
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator-- (int) {
	return mat2<numType>(
		--m[0][0], --m[0][1],
		--m[1][0], --m[1][1]
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator + (const mat2<numType>& input) const {
	return mat2<numType>(
		m[0][0] + input.m[0][0], m[0][1] + input.m[0][1],
		m[1][0] + input.m[1][0], m[1][1] + input.m[1][1]
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - (const mat2<numType>& input) const {
	return mat2<numType>(
		m[0][0] - input.m[0][0], m[0][1] - input.m[0][1],
		m[1][0] - input.m[1][0], m[1][1] - input.m[1][1]
	);
}

//for operations like "mat2a = -mat2b"
template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - () const {
	return mat2<numType>(	-m[0][0], -m[0][1],
							-m[1][0], -m[1][1]);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator * (const mat2<numType>& input) const {
	return mat2<numType>(
	//X
		(m[0][0]*input.m[0][0]) + (m[0][1]*input.m[1][0]),
		(m[0][0]*input.m[0][1]) + (m[0][1]*input.m[1][1]),
		
	//Y
		(m[1][0]*input.m[0][0]) + (m[1][1]*input.m[1][0]),
		(m[1][0]*input.m[0][1]) + (m[1][1]*input.m[1][1])
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator = (const mat2<numType>& input) {
	m[0][0] = input.m[0][0]; m[0][1] = input.m[0][1];
	m[1][0] = input.m[1][0]; m[1][1] = input.m[1][1];
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator += (const mat2<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator -= (const mat2<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator *= (const mat2<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
bool mat2<numType>::operator == (const mat2<numType>& compare) const {
	return	(
				m[0][0] == compare.m[0][0] && m[0][1] == compare.m[0][1] &&
				m[1][0] == compare.m[1][0] && m[1][1] == compare.m[1][1]
			);
}

template <typename numType> HL_IMPERATIVE
bool mat2<numType>::operator != (const mat2<numType>& compare) const {
	return	(
				m[0][0] != compare.m[0][0] && m[0][1] != compare.m[0][1] &&
				m[1][0] != compare.m[1][0] && m[1][1] != compare.m[1][1]
			);
}

//---------------------------------------------------------------------
//	mat-vector Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator + (const vec2<numType>& input) const {
	return mat2(
		m[0][0] + input.x, m[0][1] + input.y,
		m[1][0] + input.x, m[1][1] + input.y
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - (const vec2<numType>& input) const {
	return mat2(
		m[0][0] - input.x, m[0][1] - input.y,
		m[1][0] - input.x, m[1][1] - input.y
	);
}

template <typename numType> HL_IMPERATIVE
vec2<numType> mat2<numType>::operator * (const vec2<numType>& inVec) const {
	return vec2<numType>(
		(m[0][0] * inVec.x) + (m[0][1] * inVec.y),
		(m[1][0] * inVec.x) + (m[1][1] * inVec.y)
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator = (const vec2<numType>& input) {
	m[0][0] = input.x; m[0][1] = input.x;
	m[1][0] = input.y; m[1][1] = input.y;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator += (const vec2<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator -= (const vec2<numType>& input) {
	*this = *this - input;
	return *this;
}

//---------------------------------------------------------------------
//	mat-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator + (numType input) const {
	return mat2<numType>(
		m[0][0] + input, m[0][1] + input,
		m[1][0] + input, m[1][1] + input
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - (numType input) const {
	return mat2<numType>(
		m[0][0] - input, m[0][1] - input,
		m[1][0] - input, m[1][1] - input
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator * (numType input) const {
	return mat2<numType>(
		m[0][0] * input, m[0][1] * input,
		m[1][0] * input, m[1][1] * input
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator / (numType input) const {
	return mat2<numType>(
		m[0][0] / input, m[0][1] / input,
		m[1][0] / input, m[1][1] / input
	);
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator = (numType input) {
	m[0][0] = input; m[0][1] = input;
	m[1][0] = input; m[1][1] = input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace
#endif /*__mat2_H__*/
