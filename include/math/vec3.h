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

namespace hamLibs {
namespace math {

template <typename numType>
struct vec3_t {
	numType v[3];
	numType &x, &y, &z;

	//constructors
	vec3_t			();
	vec3_t			(const numType inVect[3]);
	vec3_t			(const vec3_t<numType>& invect);
	vec3_t			(numType inX, numType inY, numType inZ);
	~vec3_t			(){}

	//array operators
	numType			operator		[]		(int) const;
	numType&		operator		[]		(int);

	//vector-vector operators
	vec3_t&			operator		= 		(const vec3_t<numType>&);
	vec3_t			operator 		+ 		(const vec3_t<numType>&) const;
	vec3_t			operator 		- 		(const vec3_t<numType>&) const;
	vec3_t			operator 		- 		() const;
	vec3_t			operator 		* 		(const vec3_t<numType>&) const;
	vec3_t			operator 		/ 		(const vec3_t<numType>&) const;
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

	//vector-matrix operators
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

//---------------------------------------------------------------------
//	Vector Constructors
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec3_t<numType>::vec3_t() :
	vec3_t(
		numType(0), numType(0), numType(0)
	)
{}

template <typename numType> HL_IMPERATIVE
vec3_t<numType>::vec3_t(const vec3_t<numType>& input) :
	vec3_t(
		input.x, input.y, input.z
	)
{}

template <typename numType> HL_IMPERATIVE
vec3_t<numType>::vec3_t(numType inX, numType inY, numType inZ) :
	v{ inX, inY, inZ },
	x( v[0] ), y( v[1] ), z( v[2] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType vec3_t<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 3));
	return v[ index ];
}

template <typename numType> HL_IMPERATIVE
numType& vec3_t<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 3));
	return v[ index ];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator = (const vec3_t<numType>& input) {
	x = input.x;
	y = input.y;
	z = input.z;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator + (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		x + input.x,
		y + input.y,
		z + input.z
	);
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator - (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		x - input.x,
		y - input.y,
		z - input.z
	);
}

//for operations like "vectA = -vectB"
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator - () const {
	return vec3_t<numType>(-x, -y, -z);
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator * (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		x * input.x,
		y * input.y,
		z * input.z
	);
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator / (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		x / input.x,
		y / input.y,
		z / input.z
	);
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator += (const vec3_t<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator -= (const vec3_t<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator *= (const vec3_t<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator /= (const vec3_t<numType>& input) {
	*this = *this / input;
	return *this;
}

// prefix operations
template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator++ () {
	++x;
	++y;
	++z;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator-- () {
	--x;
	--y;
	--z;
	return *this;
}
//postfix operations
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator++ (int) {
	return vec3_t<numType>(
		++x,
		++y,
		++z
	);
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator-- (int) {
	return vec3_t<numType>(
		--x,
		--y,
		--z
	);
}

//comparisons
template <typename numType> HL_IMPERATIVE
bool vec3_t<numType>::operator== (const vec3_t<numType>& compare) const {
	return (	x == compare.x &&
				y == compare.y &&
				z == compare.z
			);
}

template <typename numType> HL_IMPERATIVE
bool vec3_t<numType>::operator!= (const vec3_t<numType>& compare) const {
	return (	x != compare.x &&
				y != compare.y &&
				z != compare.z
			);
}

template <typename numType> HL_IMPERATIVE
bool vec3_t<numType>::operator< (const vec3_t<numType>& compare) const {
	return (	x < compare.x &&
				y < compare.y &&
				z < compare.z
			);
}

template <typename numType> HL_IMPERATIVE
bool vec3_t<numType>::operator> (const vec3_t<numType>& compare) const {
	return (	x > compare.x &&
				y > compare.y &&
				z > compare.z
			);
}

template <typename numType> HL_IMPERATIVE
bool vec3_t<numType>::operator<= (const vec3_t<numType>& compare) const {
	return (	x <= compare.x &&
				y <= compare.y &&
				z <= compare.z
			);
}

template <typename numType> HL_IMPERATIVE
bool vec3_t<numType>::operator>= (const vec3_t<numType>& compare) const {
	return (	x >= compare.x &&
				y >= compare.y &&
				z >= compare.z
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat3_t<numType> vec3_t<numType>::operator + (const mat3_t<numType>& m) const {
	return mat3_t<numType>(
		x + m.xx, x + m.xy, x + m.xz,
		y + m.yx, y + m.yy, y + m.yz,
		z + m.zx, z + m.zy, z + m.zz
	);
}

template <typename numType> HL_IMPERATIVE
mat3_t<numType> vec3_t<numType>::operator - (const mat3_t<numType>& m) const {
	return mat3_t<numType>(
		x - m.xx, x - m.xy, x - m.xz,
		y - m.yx, y - m.yy, y - m.yz,
		z - m.zx, z - m.zy, z - m.zz
	);
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator * (const mat3_t<numType>& m) const {
	return vec3_t<numType>(
		(m.xx * x) + (m.xy * y) + (m.xz * z),
		(m.yx * x) + (m.yy * y) + (m.yz * z),
		(m.zx * x) + (m.zy * y) + (m.zz * z)
	);
}

template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator *= (const mat3_t<numType>& m) {
	*this = *this * m;
	return *this;
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator = (numType input) {
	x = input;
	y = input;
	z = input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator + (numType input) const {
	return vec3_t<numType>(
		x + input,
		y + input,
		z + input
	);
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator - (numType input) const {
	return vec3_t<numType>(
		x - input,
		y - input,
		z - input
	);
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator * (numType input) const {
	return vec3_t<numType>(
		x * input,
		y * input,
		z * input
	);
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType> vec3_t<numType>::operator / (numType input) const {
	return vec3_t<numType>(
		x / input,
		y / input,
		z / input
	);
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec3_t<numType>& vec3_t<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace

#endif /* __HL_MATH_VEC3_H__*/
