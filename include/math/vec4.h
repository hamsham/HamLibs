/*
 * 4d vector structure
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 *		Z
 *		W
 * ----------
*/

#ifndef __HL_MATH_VEC4_H__
#define __HL_MATH_VEC4_H__

namespace hamLibs {
namespace math {

template <typename numType>
struct vec4_t {
	numType v[4];
	numType &x, &y, &z, &w;

	//constructors
	vec4_t			();
	vec4_t			(const vec4_t<numType>& invect);
	vec4_t			(numType inX, numType inY, numType inZ, numType inW);
	~vec4_t			(){}

	//array operators
	numType			operator		[]		(int) const;
	numType&		operator		[]		(int);

	//vector-vector operators
	vec4_t&			operator		= 		(const vec4_t<numType>&);
	vec4_t			operator 		+ 		(const vec4_t<numType>&) const;
	vec4_t			operator 		- 		(const vec4_t<numType>&) const;
	vec4_t			operator 		- 		() const;
	vec4_t			operator 		* 		(const vec4_t<numType>&) const;
	vec4_t			operator 		/ 		(const vec4_t<numType>&) const;
	vec4_t&			operator 		+= 		(const vec4_t<numType>&);
	vec4_t&			operator 		-= 		(const vec4_t<numType>&);
	vec4_t&			operator 		*= 		(const vec4_t<numType>&);
	vec4_t&			operator 		/= 		(const vec4_t<numType>&);
	vec4_t&			operator 		++		(); //prefix operators
	vec4_t&			operator 		--		();
	vec4_t			operator 		++		(int); //postfix operators
	vec4_t			operator 		--		(int);
	bool			operator		==		(const vec4_t<numType>& compare) const; //comparisons
	bool			operator		!=		(const vec4_t<numType>& compare) const;
	bool			operator		<		(const vec4_t<numType>& compare) const;
	bool			operator		>		(const vec4_t<numType>& compare) const;
	bool			operator		<=		(const vec4_t<numType>& compare) const;
	bool			operator		>=		(const vec4_t<numType>& compare) const;

	//vector-matrix operators
	mat4_t<numType>	operator		+		(const mat4_t<numType>&) const;
	mat4_t<numType>	operator		-		(const mat4_t<numType>&) const;
	vec4_t<numType>	operator		*		(const mat4_t<numType>&) const;
	vec4_t&			operator		*=		(const mat4_t<numType>&);

	//vector-scalar operators
	vec4_t			operator 		= 		(numType);
	vec4_t			operator 		+ 		(numType) const;
	vec4_t			operator 		- 		(numType) const;
	vec4_t			operator 		* 		(numType) const;
	vec4_t			operator 		/ 		(numType) const;
	vec4_t&			operator 		+= 		(numType);
	vec4_t&			operator 		-= 		(numType);
	vec4_t&			operator 		*= 		(numType);
	vec4_t&			operator 		/= 		(numType);
};

//---------------------------------------------------------------------
//	Vector Constructors
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec4_t<numType>::vec4_t() :
	vec4_t(
		numType(0), numType(0), numType(0), numType(0)
	)
{}

template <typename numType> HL_IMPERATIVE
vec4_t<numType>::vec4_t(const vec4_t<numType>& input) :
	vec4_t(
		input.x, input.y, input.z, input.w
	)
{}

template <typename numType> HL_IMPERATIVE
vec4_t<numType>::vec4_t(numType inX, numType inY, numType inZ, numType inW) :
	v{ inX, inY, inZ, inW },
	x( v[0] ), y( v[1] ), z( v[2] ), w( v[3] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType vec4_t<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 4));
	return v[ index ];
}

template <typename numType> HL_IMPERATIVE
numType& vec4_t<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 4));
	return v[ index ];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator = (const vec4_t<numType>& input) {
	x = input.x;
	y = input.y;
	z = input.z;
	w = input.w;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator + (const vec4_t<numType>& input) const {
	return vec4_t(
		x + input.x,
		y + input.y,
		z + input.z,
		w + input.w
	);
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator - (const vec4_t<numType>& input) const {
	return vec4_t(
		x - input.x,
		y - input.y,
		z - input.z,
		w - input.w
	);
}

//for operations like "vectA = -vectB"
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator - () const {
	return vec4_t<numType>(-x, -y, -z, -w);
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator * (const vec4_t<numType>& input) const {
	return vec4_t<numType>(
		x * input.x,
		y * input.y,
		z * input.z,
		w * input.w
	);
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator / (const vec4_t<numType>& input) const {
	return vec4_t<numType>(
		x / input.x,
		y / input.y,
		z / input.z,
		w / input.w
	);
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator += (const vec4_t<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator -= (const vec4_t<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator *= (const vec4_t<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator /= (const vec4_t<numType>& input) {
	*this = *this / input;
	return *this;
}

// prefix operations
template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator++ () {
	++x;
	++y;
	++z;
	++w;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator-- () {
	--x;
	--y;
	--z;
	--w;
	return *this;
}

//postfix operations
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator++ (int) {
	return vec4_t<numType>(
		++x,
		++y,
		++z,
		++w
	);
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator-- (int) {
	return vec4_t<numType>(
		--x,
		--y,
		--z,
		--w
	);
}

//comparisons
template <typename numType> HL_IMPERATIVE
bool vec4_t<numType>::operator== (const vec4_t<numType>& compare) const {
	return (	x == compare.x &&
				y == compare.y &&
				z == compare.z &&
				w == compare.w
			);
}

template <typename numType> HL_IMPERATIVE
bool vec4_t<numType>::operator!= (const vec4_t<numType>& compare) const {
	return (	x != compare.x &&
				y != compare.y &&
				z != compare.z &&
				w != compare.w
			);
}

template <typename numType> HL_IMPERATIVE
bool vec4_t<numType>::operator< (const vec4_t<numType>& compare) const {
	return (	x < compare.x &&
				y < compare.y &&
				z < compare.z &&
				w < compare.w
			);
}

template <typename numType> HL_IMPERATIVE
bool vec4_t<numType>::operator> (const vec4_t<numType>& compare) const {
	return (	x > compare.x &&
				y > compare.y &&
				z > compare.z &&
				w > compare.w
			);
}

template <typename numType> HL_IMPERATIVE
bool vec4_t<numType>::operator<= (const vec4_t<numType>& compare) const {
	return (	x <= compare.x &&
				y <= compare.y &&
				z <= compare.z &&
				w <= compare.w
			);
}

template <typename numType> HL_IMPERATIVE
bool vec4_t<numType>::operator>= (const vec4_t<numType>& compare) const {
	return (	x >= compare.x &&
				y >= compare.y &&
				z >= compare.z &&
				w >= compare.w
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
mat4_t<numType> vec4_t<numType>::operator + (const mat4_t<numType>& m) const {
	return mat4_t<numType>(
		x + m.xx, x + m.xy, x + m.xz, x + m.xw,
		y + m.yx, y + m.yy, y + m.yz, y + m.yw,
		z + m.zx, z + m.zy, z + m.zz, z + m.zw,
		w + m.wx, w + m.wy, w + m.wz, w + m.ww
	);
}

template <typename numType> HL_IMPERATIVE
mat4_t<numType> vec4_t<numType>::operator - (const mat4_t<numType>& m) const {
	return mat4_t<numType>(
		x - m.xx, x - m.xy, x - m.xz, x - m.xw,
		y - m.yx, y - m.yy, y - m.yz, y - m.yw,
		z - m.zx, z - m.zy, z - m.zz, z - m.zw,
		w - m.wx, w - m.wy, w - m.wz, w - m.ww
	);
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator * (const mat4_t<numType>& m) const {
	return vec4_t<numType>(
		(m.xx * x) + (m.xy * y) + (m.xz * z) + (m.xw * w),
		(m.yx * x) + (m.yy * y) + (m.yz * z) + (m.yw * w),
		(m.zx * x) + (m.zy * y) + (m.zz * z) + (m.zw * w),
		(m.wx * x) + (m.wy * y) + (m.wz * z) + (m.ww * w)
	);
}

template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator *= (const mat4_t<numType>& m) {
	*this = *this * m;
	return *this;
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator = (numType input) {
	x = input;
	y = input;
	z = input;
	w = input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator + (numType input) const {
	return vec4_t<numType>(
		x + input,
		y + input,
		z + input,
		w + input
	);
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator - (numType input) const {
	return vec4_t<numType>(
		x - input,
		y - input,
		z - input,
		w - input
	);
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator * (numType input) const {
	return vec4_t<numType>(
		x * input,
		y * input,
		z * input,
		w * input
	);
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType> vec4_t<numType>::operator / (numType input) const {
	return vec4_t<numType>(
		x / input,
		y / input,
		z / input,
		w / input
	);
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}
template <typename numType> HL_IMPERATIVE
vec4_t<numType>& vec4_t<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace
#endif /* __HL_MATH_VEC4_H__*/
