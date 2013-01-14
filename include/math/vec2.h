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

namespace hamLibs {
namespace math {

template <typename numType>
struct vec2_t {
	numType v[2];
	numType	&x, &y;

	//constructors
	vec2_t			();
	vec2_t			(const vec2_t<numType>& invect);
	vec2_t			(numType inX, numType inY);
	~vec2_t			() {}

	//array operators
	numType			operator		[]		(int) const;
	numType&		operator		[]		(int);

	//vector-vector operators
	vec2_t&			operator		= 		(const vec2_t<numType>&);
	vec2_t			operator 		+ 		(const vec2_t<numType>&) const;
	vec2_t			operator 		- 		(const vec2_t<numType>&) const;
	vec2_t			operator 		- 		() const;
	vec2_t			operator 		* 		(const vec2_t<numType>&) const;
	vec2_t			operator 		/ 		(const vec2_t<numType>&) const;
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

	//vector-matrix operators
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

//---------------------------------------------------------------------
//	Vector Constructors
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec2_t<numType>::vec2_t() :
	vec2_t(
		numType(0), numType(0)
	)
{}

template <typename numType> HL_IMPERATIVE
vec2_t<numType>::vec2_t(const vec2_t<numType>& input) :
	vec2_t(
		input.x, input.y
	)
{}

template <typename numType> HL_IMPERATIVE
vec2_t<numType>::vec2_t(numType inX, numType inY) :
	v{ inX, inY },
	x( v[0] ), y( v[1] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType vec2_t<numType>::operator[](const int index) const {
	HL_ASSERT((index == 0) || (index == 1));
	return v[ index ];
}

template <typename numType> HL_IMPERATIVE
numType& vec2_t<numType>::operator[](const int index) {
	HL_ASSERT((index == 0) || (index == 1));
	return v[ index ];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator = (const vec2_t<numType>& input) {
	x = input.x;
	y = input.y;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator + (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		x + input.x,
		y + input.y
	);
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator - (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		x - input.x,
		y - input.y
	);
}

//for operations like "vectA = -vectB"
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator - () const {
	return vec2_t<numType>(-x, -y);
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator * (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		x * input.x,
		y * input.y
	);
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator / (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		x / input.x,
		y / input.y
	);
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator += (const vec2_t<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator -= (const vec2_t<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator *= (const vec2_t<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator /= (const vec2_t<numType>& input) {
	*this = *this / input;
	return *this;
}

// prefix operations
template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator++ () {
	++x;
	++y;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator-- () {
	--x;
	--y;
	return *this;
}
//postfix operations
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator++ (int) {
	return vec2_t<numType>(
		++x,
		++y
	);
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator-- (int) {
	return vec2_t<numType>(
		--x,
		--y
	);
}

//comparisons
template <typename numType> HL_IMPERATIVE
bool vec2_t<numType>::operator== (const vec2_t<numType>& compare) const {
	return (	x == compare.x &&
				y == compare.y
			);
}

template <typename numType> HL_IMPERATIVE
bool vec2_t<numType>::operator!= (const vec2_t<numType>& compare) const {
	return (	x != compare.x &&
				y != compare.y
			);
}

template <typename numType> HL_IMPERATIVE
bool vec2_t<numType>::operator< (const vec2_t<numType>& compare) const {
	return (	x < compare.x &&
				y < compare.y
			);
}

template <typename numType> HL_IMPERATIVE
bool vec2_t<numType>::operator> (const vec2_t<numType>& compare) const {
	return (	x > compare.x &&
				y > compare.y
			);
}

template <typename numType> HL_IMPERATIVE
bool vec2_t<numType>::operator<= (const vec2_t<numType>& compare) const {
	return (	x <= compare.x &&
				y <= compare.y
			);
}

template <typename numType> HL_IMPERATIVE
bool vec2_t<numType>::operator>= (const vec2_t<numType>& compare) const {
	return (	x >= compare.x &&
				y >= compare.y
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat2_t<numType> vec2_t<numType>::operator + (const mat2_t<numType>& m) const {
	return mat2_t<numType>(
		x + m.xx, x + m.xy,
		y + m.yx, y + m.yy
	);
}

template <typename numType> HL_IMPERATIVE
mat2_t<numType> vec2_t<numType>::operator - (const mat2_t<numType>& m) const {
	return mat2_t<numType>(
		x - m.xx, x - m.xy,
		y - m.yx, y - m.yy
	);
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator * (const mat2_t<numType>& m) const {
	return vec2_t<numType>(
		(m.xx * x) + (m.xy * y),
		(m.yx * x) + (m.yy * y)
	);
}

template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator *= (const mat2_t<numType>& m) {
	*this = *this * m;
	return *this;
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator = (numType input) {
	x = input;
	y = input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator + (numType input) const {
	return vec2_t<numType>(
		x + input,
		y + input
	);
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator - (numType input) const {
	return vec2_t<numType>(
		x - input,
		y - input
	);
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator * (numType input) const {
	return vec2_t<numType>(
		x * input,
		y * input
	);
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType> vec2_t<numType>::operator / (numType input) const {
	return vec2_t<numType>(
		x / input,
		y / input
	);
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec2_t<numType>& vec2_t<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace

#endif /* __HL_MATH_VEC2_H__*/
