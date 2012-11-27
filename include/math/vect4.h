/*
 * 4d vector class
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

#ifndef __HAMLIBS_MATH_VECT4_H__
#define __HAMLIBS_MATH_VECT4_H__

namespace hamLibs {
namespace math {

template <class numType>
class vec4 {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const vec4<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, vec4<type>& );
	
	public:
		numType v4[4];
		numType &x, &y, &z, &w;

		enum {X, Y, Z, W};
		
		//constructors
		vec4			();
		vec4			(const numType inVect[4]);
		vec4			(const vec4<numType>& invect);
		vec4			(numType inX=0, numType inY=0, numType inZ=0, numType inW=0);
		~vec4			(){}

		//array operators
		numType			operator		[]		(int) const;
		numType&		operator		[]		(int);

		//vector-vector operators
		vec4&			operator		= 		(const vec4<numType>&);
		vec4			operator 		+ 		(const vec4<numType>&) const;
		vec4			operator 		- 		(const vec4<numType>&) const;
		vec4			operator 		- 		() const;
		vec4			operator 		* 		(const vec4<numType>&) const;
		vec4			operator 		/ 		(const vec4<numType>&) const;
		vec4&			operator 		+= 		(const vec4<numType>&);
		vec4&			operator 		-= 		(const vec4<numType>&);
		vec4&			operator 		*= 		(const vec4<numType>&);
		vec4&			operator 		/= 		(const vec4<numType>&);
		vec4&			operator 		++		(); //prefix operators
		vec4&			operator 		--		();
		vec4			operator 		++		(int); //postfix operators
		vec4			operator 		--		(int);
		bool			operator		==		(const vec4<numType>& compare) const; //comparisons
		bool			operator		!=		(const vec4<numType>& compare) const;
		bool			operator		<		(const vec4<numType>& compare) const;
		bool			operator		>		(const vec4<numType>& compare) const;
		bool			operator		<=		(const vec4<numType>& compare) const;
		bool			operator		>=		(const vec4<numType>& compare) const;

		//vector-matrix operators
		mat4<numType>	operator		+		(const mat4<numType>&) const;
		mat4<numType>	operator		-		(const mat4<numType>&) const;
		vec4<numType>	operator		*		(const mat4<numType>&) const;
		vec4&			operator		*=		(const mat4<numType>&);

		//vector-scalar operators
		vec4			operator 		= 		(numType);
		vec4			operator 		+ 		(numType) const;
		vec4			operator 		- 		(numType) const;
		vec4			operator 		* 		(numType) const;
		vec4			operator 		/ 		(numType) const;
		vec4&			operator 		+= 		(numType);
		vec4&			operator 		-= 		(numType);
		vec4&			operator 		*= 		(numType);
		vec4&			operator 		/= 		(numType);

		//vector rotation functions
		void			rotateX			(numType radians);
		void			rotateY			(numType radians);
		void			rotateZ			(numType radians);
		vec4			rotVectX		(numType radians);
		vec4			rotVectY		(numType radians);
		vec4			rotVectZ		(numType radians);

		//misc functions
		numType			Magnitude		()		const;
		vec4			getNormal		()		const;
		void			normalize		();
		void			zero			();
		static numType	dotProduct		(const vec4<numType>& v1, const vec4<numType>& v2);
		static numType	angleBetween	(const vec4<numType>& v1, const vec4<numType>& v2, const vec4<numType>& origin = 0);
		static vec4		crossProduct	(const vec4<numType>& v1, const vec4<numType>& v2);
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const vec4<type>& v4 ) {
	sout
		<< v4.x << " " << v4.y << " " << v4.z << " " << v4.w;
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, vec4<type>& v4 ) {
	stin
		>> v4.x >> v4.y >> v4.z >> v4.w;
	return stin;
}

//---------------------------------------------------------------------
//	Vector Constructors
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec4<numType>::vec4() :
	vec4 (
		0, 0, 0, 1
	)
{}

template <class numType> HL_IMPERATIVE
vec4<numType>::vec4(const numType input[4]) :
	vec4 (
		input[X], input[Y], input[Z], input[W]
	)
{}

template <class numType> HL_IMPERATIVE
vec4<numType>::vec4(const vec4<numType>& input) :
	vec4 (
		input.x, input.y, input.z, input.w
	)
{}

template <class numType> HL_IMPERATIVE
vec4<numType>::vec4(numType inX, numType inY, numType inZ, numType inW) :
	v4{ inX, inY, inZ, inW },
	x( v4[0] ), y( v4[1] ), z( v4[2] ), w( v4[3] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType vec4<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 4));
	return v4[ index ];
}

template <class numType> HL_IMPERATIVE
numType& vec4<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 4));
	return v4[ index ];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator = (const vec4<numType>& input) {
	x = input.x;
	y = input.y;
	z = input.z;
	w = input.w;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator + (const vec4<numType>& input) const {
	return vec4(
		x + input.x,
		y + input.y,
		z + input.z,
		w + input.w
	);
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator - (const vec4<numType>& input) const {
	return vec4(
		x - input.x,
		y - input.y,
		z - input.z,
		w - input.w
	);
}

//for operations like "vectA = -vectB"
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator - () const {
	return vec4<numType>(-x, -y, -z, -w);
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator * (const vec4<numType>& input) const {
	return vec4<numType>(
		x * input.x,
		y * input.y,
		z * input.z,
		w * input.w
	);
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator / (const vec4<numType>& input) const {
	return vec4<numType>(
		x / input.x,
		y / input.y,
		z / input.z,
		w / input.w
	);
}

template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator += (const vec4<numType>& input) {
	x += input.x;
	y += input.y;
	z += input.z;
	w += input.w;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator -= (const vec4<numType>& input) {
	x -= input.x;
	y -= input.y;
	z -= input.z;
	w -= input.w;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator *= (const vec4<numType>& input) {
	x *= input.x;
	y *= input.y;
	z *= input.z;
	w *= input.w;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator /= (const vec4<numType>& input) {
	x /= input.x;
	y /= input.y;
	z /= input.z;
	w /= input.w;
	return *this;
}

// prefix operations
template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator++ () {
	++x;
	++y;
	++z;
	++w;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator-- () {
	--x;
	--y;
	--z;
	--w;
	return *this;
}

//postfix operations
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator++ (int) {
	return vec4<numType>(
		++x,
		++y,
		++z,
		++w
	);
}
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator-- (int) {
	return vec4<numType>(
		--x,
		--y,
		--z,
		--w
	);
}

//comparisons
template <class numType> HL_IMPERATIVE
bool vec4<numType>::operator== (const vec4<numType>& compare) const {
	return (	x == compare.x &&
				y == compare.y &&
				z == compare.z &&
				w == compare.w
			);
}

template <class numType> HL_IMPERATIVE
bool vec4<numType>::operator!= (const vec4<numType>& compare) const {
	return (	x != compare.x &&
				y != compare.y &&
				z != compare.z &&
				w != compare.w
			);
}

template <class numType> HL_IMPERATIVE
bool vec4<numType>::operator< (const vec4<numType>& compare) const {
	return (	x < compare.x &&
				y < compare.y &&
				z < compare.z &&
				w < compare.w
			);
}

template <class numType> HL_IMPERATIVE
bool vec4<numType>::operator> (const vec4<numType>& compare) const {
	return (	x > compare.x &&
				y > compare.y &&
				z > compare.z &&
				w > compare.w
			);
}

template <class numType> HL_IMPERATIVE
bool vec4<numType>::operator<= (const vec4<numType>& compare) const {
	return (	x <= compare.x &&
				y <= compare.y &&
				z <= compare.z &&
				w <= compare.w
			);
}

template <class numType> HL_IMPERATIVE
bool vec4<numType>::operator>= (const vec4<numType>& compare) const {
	return (	x >= compare.x &&
				y >= compare.y &&
				z >= compare.z &&
				w >= compare.w
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
mat4<numType> vec4<numType>::operator + (const mat4<numType>& m4x4) const {
	return mat4<numType>(
		x + m4x4.xx, x + m4x4.xy, x + m4x4.xz, x + m4x4.xw,
		y + m4x4.yx, y + m4x4.yy, y + m4x4.yz, y + m4x4.yw,
		z + m4x4.zx, z + m4x4.zy, z + m4x4.zz, z + m4x4.zw,
		w + m4x4.wx, w + m4x4.wy, w + m4x4.wz, w + m4x4.ww
	);
}

template <class numType> HL_IMPERATIVE
mat4<numType> vec4<numType>::operator - (const mat4<numType>& m4x4) const {
	return mat4<numType>(
		x - m4x4.xx, x - m4x4.xy, x - m4x4.xz, x - m4x4.xw,
		y - m4x4.yx, y - m4x4.yy, y - m4x4.yz, y - m4x4.yw,
		z - m4x4.zx, z - m4x4.zy, z - m4x4.zz, z - m4x4.zw,
		w - m4x4.wx, w - m4x4.wy, w - m4x4.wz, w - m4x4.ww
	);
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator * (const mat4<numType>& m4x4) const {
	return vec4<numType>(
		(m4x4.xx * x) + (m4x4.xy * y) + (m4x4.xz * z) + (m4x4.xw * w),
		(m4x4.yx * x) + (m4x4.yy * y) + (m4x4.yz * z) + (m4x4.yw * w),
		(m4x4.zx * x) + (m4x4.zy * y) + (m4x4.zz * z) + (m4x4.zw * w),
		(m4x4.wx * x) + (m4x4.wy * y) + (m4x4.wz * z) + (m4x4.ww * w)
	);
}

template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator *= (const mat4<numType>& m4x4) {
	vec4<numType> temp(
		(m4x4.xx * x) + (m4x4.xy * y) + (m4x4.xz * z) + (m4x4.xw * w),
		(m4x4.yx * x) + (m4x4.yy * y) + (m4x4.yz * z) + (m4x4.yw * w),
		(m4x4.zx * x) + (m4x4.zy * y) + (m4x4.zz * z) + (m4x4.zw * w),
		(m4x4.wx * x) + (m4x4.wy * y) + (m4x4.wz * z) + (m4x4.ww * w)
	);
	x = temp.x;
	y = temp.y;
	z = temp.z;
	w = temp.w;
	return *this;
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator = (numType input) {
	x = input;
	y = input;
	z = input;
	w = input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator + (numType input) const {
	return vec4<numType>(
		x + input,
		y + input,
		z + input,
		w + input
	);
}
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator - (numType input) const {
	return vec4<numType>(
		x - input,
		y - input,
		z - input,
		w - input
	);
}
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator * (numType input) const {
	return vec4<numType>(
		x * input,
		y * input,
		z * input,
		w * input
	);
}
template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::operator / (numType input) const {
	return vec4<numType>(
		x / input,
		y / input,
		z / input,
		w / input
	);
}
template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator += (numType input) {
	x += input;
	y += input;
	z += input;
	w += input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator -= (numType input) {
	x -= input;
	y -= input;
	z -= input;
	w -= input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator *= (numType input) {
	x *= input;
	y *= input;
	z *= input;
	w *= input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec4<numType>& vec4<numType>::operator /= (numType input) {
	x /= input;
	y /= input;
	z /= input;
	w /= input;
	return *this;
}

//---------------------------------------------------------------------
//	Vector Rotation Functions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
void vec4<numType>::rotateX (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	numType temp[] = {
		(y*cosTheta) + (z*sinTheta),
		(z*cosTheta) - (y*sinTheta),
	};
	y = temp[0];
	z = temp[1];
}

template <class numType> HL_IMPERATIVE
void vec4<numType>::rotateY (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	numType temp[] = {
		(x*cosTheta) - (z*sinTheta),
		(x*sinTheta) + (z*cosTheta)
	};
	x = temp[0];
	z = temp[1];
}

template <class numType> HL_IMPERATIVE
void vec4<numType>::rotateZ (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	numType temp[] = {
		(x*cosTheta) + (y*sinTheta),
		(y*cosTheta) - (x*sinTheta),
	};
	x = temp[0];
	y = temp[1];
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::rotVectX (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec4<numType>(
		x,
		(y*cosTheta) + (z*sinTheta),
		(z*cosTheta) - (y*sinTheta),
		w
	);
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::rotVectY (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec4<numType>(
		(x*cosTheta) - (z*sinTheta),
		y,
		(x*sinTheta) + (z*cosTheta),
		w
	);

}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::rotVectZ (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec4<numType>(
		(x*cosTheta) + (y*sinTheta),
		(y*cosTheta) - (x*sinTheta),
		z,
		w
	);
}

//---------------------------------------------------------------------
//	Miscellaneous Functions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType vec4<numType>::Magnitude() const {
	return hamLibs::math::fastSqrt(
		(x * x)+
		(y * y)+
		(z * z)+
		(w * w)
	);
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::getNormal() const {
	numType mag = hamLibs::math::fastInvSqrt(
		(x * x)+
		(y * y)+
		(z * z)+
		(w * w)
	);
	return vec4<numType>(
		x*mag,
		y*mag,
		z*mag,
		w*mag
	);
}

template <class numType> HL_IMPERATIVE
void vec4<numType>::normalize() {
	numType mag = hamLibs::math::fastInvSqrt(
		(x * x)+
		(y * y)+
		(z * z)+
		(w * w)
	);
	x *= mag;
	y *= mag;
	z *= mag;
	w *= mag;
}

template <class numType> HL_IMPERATIVE
numType vec4<numType>::dotProduct(const vec4<numType>& v1, const vec4<numType>& v2) {
	return	(v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

template <class numType> HL_IMPERATIVE
numType vec4<numType>::angleBetween(const vec4<numType>& v1, const vec4<numType>& v2, const vec4<numType>& origin) {
	return	acos(
				((v1.x - origin.x) * (v2.x - origin.x)) +
				((v1.y - origin.y) * (v2.y - origin.y)) +
				((v1.z - origin.z) * (v2.z - origin.z)) +
				((v1.w - origin.w) * (v2.w - origin.w))
			);
}

template <class numType> HL_IMPERATIVE
vec4<numType> vec4<numType>::crossProduct(const vec4<numType>& v1, const vec4<numType>& v2) {
	return vec4<numType>(
		(v1.y*v2.z) - (v1.z*v2.y),
		(v1.z*v2.x) - (v1.x*v2.z),
		(v1.x*v2.y) - (v1.y*v2.x),
		0
	);
}

template <class numType> HL_IMPERATIVE
void vec4<numType>::zero() {
	x = y = z = w = 0;
}

} //end math namespace
} //end hamlibs namespace
#endif /* __VECT4_H__*/
