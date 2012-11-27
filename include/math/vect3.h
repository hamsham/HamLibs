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
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const vec3<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, vec3<type>& );
	
	public:
		numType v3[3];
		numType &x, &y, &z;

		enum {X, Y, Z};
		
		//constructors
		vec3			();
		vec3			(const numType inVect[3]);
		vec3			(const vec3<numType>& invect);
		vec3			(numType inX=0, numType inY=0, numType inZ=0);
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
		bool			operator		==		(const vec3<numType>& compare) const; //comparisons
		bool			operator		!=		(const vec3<numType>& compare) const;
		bool			operator		<		(const vec3<numType>& compare) const;
		bool			operator		>		(const vec3<numType>& compare) const;
		bool			operator		<=		(const vec3<numType>& compare) const;
		bool			operator		>=		(const vec3<numType>& compare) const;

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
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const vec3<type>& v3 ) {
	sout
		<< v3.x << " " << v3.y << " " << v3.z;
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, vec3<type>& v3 ) {
	stin
		>> v3.x >> v3.y >> v3.z;
	return stin;
}

//---------------------------------------------------------------------
//	Vector Constructors
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec3<numType>::vec3() :
	vec3(
		0, 0, 0
	)
{}

template <class numType> HL_IMPERATIVE
vec3<numType>::vec3(const numType input[3]) :
	vec3(
		input[X], input[Y], input[Z]
	)
{}

template <class numType> HL_IMPERATIVE
vec3<numType>::vec3(const vec3<numType>& input) :
	vec3(
		input.x, input.y, input.z
	)
{}

template <class numType> HL_IMPERATIVE
vec3<numType>::vec3(numType inX, numType inY, numType inZ) :
	v3{ inX, inY, inZ },
	x( v3[0] ), y( v3[1] ), z( v3[2] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType vec3<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 3));
	return v3[ index ];
}

template <class numType> HL_IMPERATIVE
numType& vec3<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 3));
	return v3[ index ];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator = (const vec3<numType>& input) {
	x = input.x;
	y = input.y;
	z = input.z;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator + (const vec3<numType>& input) const {
	return vec3<numType>(
		x + input.x,
		y + input.y,
		z + input.z
	);
}

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator - (const vec3<numType>& input) const {
	return vec3<numType>(
		x - input.x,
		y - input.y,
		z - input.z
	);
}

//for operations like "vectA = -vectB"
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator - () const {
	return vec3<numType>(-x, -y, -z);
}

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator * (const vec3<numType>& input) const {
	return vec3<numType>(
		x * input.x,
		y * input.y,
		z * input.z
	);
}

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator / (const vec3<numType>& input) const {
	return vec3<numType>(
		x / input.x,
		y / input.y,
		z / input.z
	);
}

template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator += (const vec3<numType>& input) {
	x += input.x;
	y += input.y;
	z += input.z;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator -= (const vec3<numType>& input) {
	x -= input.x;
	y -= input.y;
	z -= input.z;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator *= (const vec3<numType>& input) {
	x *= input.x;
	y *= input.y;
	z *= input.z;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator /= (const vec3<numType>& input) {
	x /= input.x;
	y /= input.y;
	z /= input.z;
	return *this;
}

// prefix operations
template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator++ () {
	++x;
	++y;
	++z;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator-- () {
	--x;
	--y;
	--z;
	return *this;
}
//postfix operations
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator++ (int) {
	return vec3<numType>(
		++x,
		++y,
		++z
	);
}
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator-- (int) {
	return vec3<numType>(
		--x,
		--y,
		--z
	);
}

//comparisons
template <class numType> HL_IMPERATIVE
bool vec3<numType>::operator== (const vec3<numType>& compare) const {
	return (	x == compare.x &&
				y == compare.y &&
				z == compare.z
			);
}

template <class numType> HL_IMPERATIVE
bool vec3<numType>::operator!= (const vec3<numType>& compare) const {
	return (	x != compare.x &&
				y != compare.y &&
				z != compare.z
			);
}

template <class numType> HL_IMPERATIVE
bool vec3<numType>::operator< (const vec3<numType>& compare) const {
	return (	x < compare.x &&
				y < compare.y &&
				z < compare.z
			);
}

template <class numType> HL_IMPERATIVE
bool vec3<numType>::operator> (const vec3<numType>& compare) const {
	return (	x > compare.x &&
				y > compare.y &&
				z > compare.z
			);
}

template <class numType> HL_IMPERATIVE
bool vec3<numType>::operator<= (const vec3<numType>& compare) const {
	return (	x <= compare.x &&
				y <= compare.y &&
				z <= compare.z
			);
}

template <class numType> HL_IMPERATIVE
bool vec3<numType>::operator>= (const vec3<numType>& compare) const {
	return (	x >= compare.x &&
				y >= compare.y &&
				z >= compare.z
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
mat3<numType> vec3<numType>::operator + (const mat3<numType>& m3x3) const {
	return mat3<numType>(
		x + m3x3.xx, x + m3x3.xy, x + m3x3.xz,
		y + m3x3.yx, y + m3x3.yy, y + m3x3.yz,
		z + m3x3.zx, z + m3x3.zy, z + m3x3.zz
	);
}

template <class numType> HL_IMPERATIVE
mat3<numType> vec3<numType>::operator - (const mat3<numType>& m3x3) const {
	return mat3<numType>(
		x - m3x3.xx, x - m3x3.xy, x - m3x3.xz,
		y - m3x3.yx, y - m3x3.yy, y - m3x3.yz,
		z - m3x3.zx, z - m3x3.zy, z - m3x3.zz
	);
}

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator * (const mat3<numType>& m3x3) const {
	return vec3<numType>(
		(m3x3.xx * x) + (m3x3.xy * y) + (m3x3.xz * z),
		(m3x3.yx * x) + (m3x3.yy * y) + (m3x3.yz * z),
		(m3x3.zx * x) + (m3x3.zy * y) + (m3x3.zz * z)
	);
}

template <class numType> HL_IMPERATIVE
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
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator = (numType input) {
	x = input;
	y = input;
	z = input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator + (numType input) const {
	return vec3<numType>(
		x + input,
		y + input,
		z + input
	);
}
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator - (numType input) const {
	return vec3<numType>(
		x - input,
		y - input,
		z - input
	);
}
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator * (numType input) const {
	return vec3<numType>(
		x * input,
		y * input,
		z * input
	);
}
template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::operator / (numType input) const {
	return vec3<numType>(
		x / input,
		y / input,
		z / input
	);
}
template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator += (numType input) {
	x += input;
	y += input;
	z += input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator -= (numType input) {
	x -= input;
	y -= input;
	z -= input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator *= (numType input) {
	x *= input;
	y *= input;
	z *= input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec3<numType>& vec3<numType>::operator /= (numType input) {
	x /= input;
	y /= input;
	z /= input;
	return *this;
}

//---------------------------------------------------------------------
//	Vector Rotation Functions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
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

template <class numType> HL_IMPERATIVE
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

template <class numType> HL_IMPERATIVE
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

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::rotVectX (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec3<numType>(
		x,
		(y*cosTheta) + (z*sinTheta),
		(z*cosTheta) - (y*sinTheta)
	);
}

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::rotVectY (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec3<numType>(
		(x*cosTheta) - (z*sinTheta),
		y,
		(x*sinTheta) + (z*cosTheta)
	);

}

template <class numType> HL_IMPERATIVE
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
template <class numType> HL_IMPERATIVE
numType vec3<numType>::Magnitude() const {
	return hamLibs::math::fastSqrt(
		(x * x)+
		(y * y)+
		(z * z)
	);
}

template <class numType> HL_IMPERATIVE
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

template <class numType> HL_IMPERATIVE
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

template <class numType> HL_IMPERATIVE
numType vec3<numType>::dotProduct(const vec3<numType>& v1, const vec3<numType>& v2) {
	return	(v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

template <class numType> HL_IMPERATIVE
numType vec3<numType>::angleBetween(const vec3<numType>& v1, const vec3<numType>& v2, const vec3<numType>& origin) {
	return	acos(
				((v1.x - origin.x) * (v2.x - origin.x)) +
				((v1.y - origin.y) * (v2.y - origin.y)) +
				((v1.z - origin.z) * (v2.z - origin.z))
			);
}

template <class numType> HL_IMPERATIVE
vec3<numType> vec3<numType>::crossProduct(const vec3<numType>& v1, const vec3<numType>& v2) {
	return vec3<numType>(
		(v1.y*v2.z) - (v1.z*v2.y),
		(v1.z*v2.x) - (v1.x*v2.z),
		(v1.x*v2.y) - (v1.y*v2.x)
	);
}

template <class numType> HL_IMPERATIVE
void vec3<numType>::zero() {
	x = y = z = 0;
}

} //end math namespace
} //end hamlibs namespace
#endif /* __VECT3_H__*/
