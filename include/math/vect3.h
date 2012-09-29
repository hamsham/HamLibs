/*
 * 3d vector class
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 *		Z
 * ----------
*/

#ifndef __HAMLIBS_MATH_VECT3_H__
#define __HAMLIBS_MATH_VECT3_H__

namespace hamLibs {
namespace math {

template <class numType>
class vec3 {
	public:
		union {
			struct {
				numType x, y, z;
			};
			numType v3[3];
		};

		enum {X, Y, Z};
		
		//constructors
		vec3			();
		vec3			(numType inVect[3]);
		vec3			(const vec3<numType>& invect);
		vec3			(numType inX, numType inY, numType inZ);
		~vec3			(){}

		//array operators
		numType			operator		[]		(int) const;
		numType&		operator		[]		(int);

		//vector-vector operators
		vec3&			operator		= 		(const vec3<numType>&);
		vec3			operator 		+ 		(const vec3<numType>&) const;
		vec3			operator 		- 		(const vec3<numType>&) const;
		vec3			operator 		- 		() const;
		vec3			operator 		* 		(const vec3<numType>&) const;
		vec3			operator 		/ 		(const vec3<numType>&) const;
		vec3&			operator 		+= 		(const vec3<numType>&);
		vec3&			operator 		-= 		(const vec3<numType>&);
		vec3&			operator 		*= 		(const vec3<numType>&);
		vec3&			operator 		/= 		(const vec3<numType>&);
		vec3&			operator 		++		(); //prefix operators
		vec3&			operator 		--		();
		vec3			operator 		++		(int); //postfix operators
		vec3			operator 		--		(int);
		bool			operator		==		(const vec3<numType>& compare); //comparisons
		bool			operator		!=		(const vec3<numType>& compare);
		bool			operator		<		(const vec3<numType>& compare);
		bool			operator		>		(const vec3<numType>& compare);
		bool			operator		<=		(const vec3<numType>& compare);
		bool			operator		>=		(const vec3<numType>& compare);

		//vector-matrix operators
		mat3<numType>	operator		+		(const mat3<numType>&) const;
		mat3<numType>	operator		-		(const mat3<numType>&) const;
		vec3<numType>	operator		*		(const mat3<numType>&) const;
		vec3&			operator		*=		(const mat3<numType>&);

		//vector-scalar operators
		vec3			operator 		= 		(numType);
		vec3			operator 		+ 		(numType) const;
		vec3			operator 		- 		(numType) const;
		vec3			operator 		* 		(numType) const;
		vec3			operator 		/ 		(numType) const;
		vec3&			operator 		+= 		(numType);
		vec3&			operator 		-= 		(numType);
		vec3&			operator 		*= 		(numType);
		vec3&			operator 		/= 		(numType);

		//vector rotation functions
		void			rotateX			(numType radians);
		void			rotateY			(numType radians);
		void			rotateZ			(numType radians);
		vec3			rotVectX		(numType radians);
		vec3			rotVectY		(numType radians);
		vec3			rotVectZ		(numType radians);

		//misc functions
		numType			Magnitude		()		const;
		vec3			getNormal		()		const;
		void			normalize		();
		void			zero			();
		static numType	dotProduct		(const vec3<numType>& v1, const vec3<numType>& v2);
		static numType	angleBetween	(const vec3<numType>& v1, const vec3<numType>& v2, const vec3<numType>& origin = 0);
		static vec3		crossProduct	(const vec3<numType>& v1, const vec3<numType>& v2);
};

//---------------------------------------------------------------------
//	Vector Constructors
//---------------------------------------------------------------------
template <class numType> HL_INLINE
vec3<numType>::vec3() :
	x(0), y(0), z(0)
{}

template <class numType> HL_INLINE
vec3<numType>::vec3(numType inVect[3]) :
	x(inVect[X]), y(inVect[Y]), z(inVect[Z])
{}

template <class numType> HL_INLINE
vec3<numType>::vec3(const vec3<numType>& inVect) :
	x(inVect.x), y(inVect.y), z(inVect.z)
{}

template <class numType> HL_INLINE
vec3<numType>::vec3(numType inX, numType inY, numType inZ) :
	x(inX), y(inY), z(inZ)
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <class numType> HL_INLINE
numType vec3<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 3));
	return v3[ index ];
}

template <class numType> HL_INLINE
numType& vec3<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 3));
	return v3[ index ];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator = (const vec3<numType>& input) {
	x = input.x;
	y = input.y;
	z = input.z;
	return *this;
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator + (const vec3<numType>& input) const {
	return vec3<numType>(
		x + input.x,
		y + input.y,
		z + input.z
	);
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator - (const vec3<numType>& input) const {
	return vec3<numType>(
		x - input.x,
		y - input.y,
		z - input.z
	);
}

//for operations like "vectA = -vectB"
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator - () const {
	return vec3<numType>(-x, -y, -z);
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator * (const vec3<numType>& input) const {
	return vec3<numType>(
		x * input.x,
		y * input.y,
		z * input.z
	);
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator / (const vec3<numType>& input) const {
	return vec3<numType>(
		x / input.x,
		y / input.y,
		z / input.z
	);
}

template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator += (const vec3<numType>& input) {
	x += input.x;
	y += input.y;
	z += input.z;
	return *this;
}

template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator -= (const vec3<numType>& input) {
	x -= input.x;
	y -= input.y;
	z -= input.z;
	return *this;
}

template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator *= (const vec3<numType>& input) {
	x *= input.x;
	y *= input.y;
	z *= input.z;
	return *this;
}

template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator /= (const vec3<numType>& input) {
	x /= input.x;
	y /= input.y;
	z /= input.z;
	return *this;
}

// prefix operations
template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator++ () {
	++x;
	++y;
	++z;
	return *this;
}
template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator-- () {
	--x;
	--y;
	--z;
	return *this;
}
//postfix operations
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator++ (int) {
	return vec3<numType>(
		++x,
		++y,
		++z
	);
}
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator-- (int) {
	return vec3<numType>(
		--x,
		--y,
		--z
	);
}

//comparisons
template <class numType> HL_INLINE
bool vec3<numType>::operator== (const vec3<numType>& compare) {
	return (	x == compare.x &&
				y == compare.y &&
				z == compare.z
			);
}

template <class numType> HL_INLINE
bool vec3<numType>::operator!= (const vec3<numType>& compare) {
	return (	x != compare.x &&
				y != compare.y &&
				z != compare.z
			);
}

template <class numType> HL_INLINE
bool vec3<numType>::operator< (const vec3<numType>& compare) {
	return (	x < compare.x &&
				y < compare.y &&
				z < compare.z
			);
}

template <class numType> HL_INLINE
bool vec3<numType>::operator> (const vec3<numType>& compare) {
	return (	x > compare.x &&
				y > compare.y &&
				z > compare.z
			);
}

template <class numType> HL_INLINE
bool vec3<numType>::operator<= (const vec3<numType>& compare) {
	return (	x <= compare.x &&
				y <= compare.y &&
				z <= compare.z
			);
}

template <class numType> HL_INLINE
bool vec3<numType>::operator>= (const vec3<numType>& compare) {
	return (	x >= compare.x &&
				y >= compare.y &&
				z >= compare.z
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations
//---------------------------------------------------------------------
template <class numType> HL_INLINE
mat3<numType> vec3<numType>::operator + (const mat3<numType>& m3x3) const {
	return mat3<numType>(
		x + m3x3.xx, x + m3x3.xy, x + m3x3.xz,
		y + m3x3.yx, y + m3x3.yy, y + m3x3.yz,
		z + m3x3.zx, z + m3x3.zy, z + m3x3.zz
	);
}

template <class numType> HL_INLINE
mat3<numType> vec3<numType>::operator - (const mat3<numType>& m3x3) const {
	return mat3<numType>(
		x - m3x3.xx, x - m3x3.xy, x - m3x3.xz,
		y - m3x3.yx, y - m3x3.yy, y - m3x3.yz,
		z - m3x3.zx, z - m3x3.zy, z - m3x3.zz
	);
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator * (const mat3<numType>& m3x3) const {
	return vec3<numType>(
		(m3x3.xx * x) + (m3x3.xy * y) + (m3x3.xz * z),
		(m3x3.yx * x) + (m3x3.yy * y) + (m3x3.yz * z),
		(m3x3.zx * x) + (m3x3.zy * y) + (m3x3.zz * z)
	);
}

template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator *= (const mat3<numType>& m3x3) {
	vec3<numType> temp(
		(m3x3.xx * x) + (m3x3.xy * y) + (m3x3.xz * z),
		(m3x3.yx * x) + (m3x3.yy * y) + (m3x3.yz * z),
		(m3x3.zx * x) + (m3x3.zy * y) + (m3x3.zz * z)
	);
	x = temp[X];
	y = temp.y;
	z = temp.z;
	return *this;
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator = (numType input) {
	x = input;
	y = input;
	z = input;
	return *this;
}
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator + (numType input) const {
	return vec3<numType>(
		x + input,
		y + input,
		z + input
	);
}
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator - (numType input) const {
	return vec3<numType>(
		x - input,
		y - input,
		z - input
	);
}
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator * (numType input) const {
	return vec3<numType>(
		x * input,
		y * input,
		z * input
	);
}
template <class numType> HL_INLINE
vec3<numType> vec3<numType>::operator / (numType input) const {
	return vec3<numType>(
		x / input,
		y / input,
		z / input
	);
}
template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator += (numType input) {
	x += input;
	y += input;
	z += input;
	return *this;
}
template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator -= (numType input) {
	x -= input;
	y -= input;
	z -= input;
	return *this;
}
template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator *= (numType input) {
	x *= input;
	y *= input;
	z *= input;
	return *this;
}
template <class numType> HL_INLINE
vec3<numType>& vec3<numType>::operator /= (numType input) {
	x /= input;
	y /= input;
	z /= input;
	return *this;
}

//---------------------------------------------------------------------
//	Vector Rotation Functions
//---------------------------------------------------------------------
template <class numType> HL_INLINE
void vec3<numType>::rotateX (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	numType temp[] = {
		(y*cosTheta) + (z*sinTheta),
		(z*cosTheta) - (y*sinTheta)
	};
	y = temp[0];
	z = temp[1];
}

template <class numType> HL_INLINE
void vec3<numType>::rotateY (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	numType temp[] = {
		(x*cosTheta) - (z*sinTheta),
		(x*sinTheta) + (z*cosTheta)
	};
	x = temp[0];
	z = temp[1];
}

template <class numType> HL_INLINE
void vec3<numType>::rotateZ (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	numType temp[] = {
		(x*cosTheta) + (y*sinTheta),
		(y*cosTheta) - (x*sinTheta)
	};
	x = temp[0];
	y = temp[1];
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::rotVectX (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec3<numType>(
		x,
		(y*cosTheta) + (z*sinTheta),
		(z*cosTheta) - (y*sinTheta)
	);
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::rotVectY (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec3<numType>(
		(x*cosTheta) - (z*sinTheta),
		y,
		(x*sinTheta) + (z*cosTheta)
	);

}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::rotVectZ (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec3<numType>(
		(x*cosTheta) + (y*sinTheta),
		(y*cosTheta) - (x*sinTheta),
		z
	);
}

//---------------------------------------------------------------------
//	Miscellaneous Functions
//---------------------------------------------------------------------
template <class numType> HL_INLINE
numType vec3<numType>::Magnitude() const {
	return hamLibs::math::fastSqrt(
		(x * x)+
		(y * y)+
		(z * z)
	);
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::getNormal() const {
	numType mag = hamLibs::math::fastInvSqrt(
		(x * x)+
		(y * y)+
		(z * z)
	);
	return vec3<numType>(
		x*mag,
		y*mag,
		z*mag
	);
}

template <class numType> HL_INLINE
void vec3<numType>::normalize() {
	numType mag = hamLibs::math::fastInvSqrt(
		(x * x)+
		(y * y)+
		(z * z)
	);
	x *= mag;
	y *= mag;
	z *= mag;
}

template <class numType> HL_INLINE
numType vec3<numType>::dotProduct(const vec3<numType>& v1, const vec3<numType>& v2) {
	return	(v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

template <class numType> HL_INLINE
numType vec3<numType>::angleBetween(const vec3<numType>& v1, const vec3<numType>& v2, const vec3<numType>& origin) {
	return	acos(
				((v1.x - origin.x) * (v2.x - origin.x)) +
				((v1.y - origin.y) * (v2.y - origin.y)) +
				((v1.z - origin.z) * (v2.z - origin.z))
			);
}

template <class numType> HL_INLINE
vec3<numType> vec3<numType>::crossProduct(const vec3<numType>& v1, const vec3<numType>& v2) {
	return vec3<numType>(
		(v1.y*v2.z) - (v1.z*v2.y),
		(v1.z*v2.x) - (v1.x*v2.z),
		(v1.x*v2.y) - (v1.y*v2.x)
	);
}

template <class numType> HL_INLINE
void vec3<numType>::zero() {
	x = y = z = 0;
}

} //end math namespace
} //end hamlibs namespace
#endif /* __VECT3_H__*/
