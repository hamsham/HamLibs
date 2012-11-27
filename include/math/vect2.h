/*
 * 2d vector class
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 * ----------
 *	derp
*/

#ifndef __HAMLIBS_MATH_VECT2_H__
#define __HAMLIBS_MATH_VECT2_H__

namespace hamLibs {
namespace math {

template <class numType>
class vec2 {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const vec2<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, vec2<type>& );
	
	public:
		numType v2[2];
		numType	x, y;

		enum {X, Y};
		
		//constructors
		vec2			();
		vec2			(const numType inVect[2]);
		vec2			(const vec2<numType>& invect);
		vec2			(numType inX=0, numType inY=0);

		//array operators
		numType			operator		[]		(int) const;
		numType&		operator		[]		(int);

		//vector-vector operators
		vec2&			operator		= 		(const vec2<numType>&);
		vec2			operator 		+ 		(const vec2<numType>&) const;
		vec2			operator 		- 		(const vec2<numType>&) const;
		vec2			operator 		- 		() const;
		vec2			operator 		* 		(const vec2<numType>&) const;
		vec2			operator 		/ 		(const vec2<numType>&) const;
		vec2&			operator 		+= 		(const vec2<numType>&);
		vec2&			operator 		-= 		(const vec2<numType>&);
		vec2&			operator 		*= 		(const vec2<numType>&);
		vec2&			operator 		/= 		(const vec2<numType>&);
		vec2&			operator 		++		(); //prefix operators
		vec2&			operator 		--		();
		vec2			operator 		++		(int); //postfix operators
		vec2			operator 		--		(int);
		bool			operator		==		(const vec2<numType>& compare) const; //comparisons
		bool			operator		!=		(const vec2<numType>& compare) const;
		bool			operator		<		(const vec2<numType>& compare) const;
		bool			operator		>		(const vec2<numType>& compare) const;
		bool			operator		<=		(const vec2<numType>& compare) const;
		bool			operator		>=		(const vec2<numType>& compare) const;

		//vector-matrix operators
		mat2<numType>	operator		+		(const mat2<numType>&) const;
		mat2<numType>	operator		-		(const mat2<numType>&) const;
		vec2<numType>	operator		*		(const mat2<numType>&) const;
		vec2&			operator		*=		(const mat2<numType>&);

		//vector-scalar operators
		vec2			operator 		= 		(numType);
		vec2			operator 		+ 		(numType) const;
		vec2			operator 		- 		(numType) const;
		vec2			operator 		* 		(numType) const;
		vec2			operator 		/ 		(numType) const;
		vec2&			operator 		+= 		(numType);
		vec2&			operator 		-= 		(numType);
		vec2&			operator 		*= 		(numType);
		vec2&			operator 		/= 		(numType);

		//vector rotation functions
		void			rotate			(numType radians);
		vec2			rotVect			(numType radians);

		//misc functions
		numType			Magnitude		()		const;
		vec2			getNormal		()		const;
		void			normalize		();
		void			zero			();
		static numType	dotProduct		(const vec2<numType>& v1, const vec2<numType>& v2);
		static numType	angleBetween	(const vec2<numType>& v1, const vec2<numType>& v2, const vec2<numType>& origin = 0);
		static vec2		crossProduct	(const vec2<numType>& invect2);
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const vec2<type>& v2 ) {
	sout
		<< v2.x << " " << v2.y;
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, vec2<type>& v2 ) {
	stin
		>> v2.x >> v2.y;
	return stin;
}

//---------------------------------------------------------------------
//	Vector Constructors
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec2<numType>::vec2() :
	vec2(
		0, 0
	)
{}

template <class numType> HL_IMPERATIVE
vec2<numType>::vec2(const numType input[2]) :
	vec2(
		input[X], input[Y]
	)
{}

template <class numType> HL_IMPERATIVE
vec2<numType>::vec2(const vec2<numType>& input) :
	vec2(
		input.x, input.y
	)
{}

template <class numType> HL_IMPERATIVE
vec2<numType>::vec2(numType inX, numType inY) :
	v2{ inX, inY },
	x( v2[0] ), y( v2[1] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType vec2<numType>::operator[](const int index) const {
	HL_ASSERT((index == 0) || (index == 1));
	return v2[ index ];
}

template <class numType> HL_IMPERATIVE
numType& vec2<numType>::operator[](const int index) {
	HL_ASSERT((index == 0) || (index == 1));
	return v2[ index ];
}

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator = (const vec2<numType>& input) {
	x = input.x;
	y = input.y;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator + (const vec2<numType>& input) const {
	return vec2<numType>(
		x + input.x,
		y + input.y
	);
}

template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator - (const vec2<numType>& input) const {
	return vec2<numType>(
		x - input.x,
		y - input.y
	);
}

//for operations like "vectA = -vectB"
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator - () const {
	return vec2<numType>(-x, -y);
}

template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator * (const vec2<numType>& input) const {
	return vec2<numType>(
		x * input.x,
		y * input.y
	);
}

template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator / (const vec2<numType>& input) const {
	return vec2<numType>(
		x / input.x,
		y / input.y
	);
}

template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator += (const vec2<numType>& input) {
	x += input.x;
	y += input.y;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator -= (const vec2<numType>& input) {
	x -= input.x;
	y -= input.y;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator *= (const vec2<numType>& input) {
	x *= input.x;
	y *= input.y;
	return *this;
}

template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator /= (const vec2<numType>& input) {
	x /= input.x;
	y /= input.y;
	return *this;
}

// prefix operations
template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator++ () {
	++x;
	++y;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator-- () {
	--x;
	--y;
	return *this;
}
//postfix operations
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator++ (int) {
	return vec2<numType>(
		++x,
		++y
	);
}
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator-- (int) {
	return vec2<numType>(
		--x,
		--y
	);
}

//comparisons
template <class numType> HL_IMPERATIVE
bool vec2<numType>::operator== (const vec2<numType>& compare) const {
	return (	x == compare.x &&
				y == compare.y
			);
}

template <class numType> HL_IMPERATIVE
bool vec2<numType>::operator!= (const vec2<numType>& compare) const {
	return (	x != compare.x &&
				y != compare.y
			);
}

template <class numType> HL_IMPERATIVE
bool vec2<numType>::operator< (const vec2<numType>& compare) const {
	return (	x < compare.x &&
				y < compare.y
			);
}

template <class numType> HL_IMPERATIVE
bool vec2<numType>::operator> (const vec2<numType>& compare) const {
	return (	x > compare.x &&
				y > compare.y
			);
}

template <class numType> HL_IMPERATIVE
bool vec2<numType>::operator<= (const vec2<numType>& compare) const {
	return (	x <= compare.x &&
				y <= compare.y
			);
}

template <class numType> HL_IMPERATIVE
bool vec2<numType>::operator>= (const vec2<numType>& compare) const {
	return (	x >= compare.x &&
				y >= compare.y
			);
}

//---------------------------------------------------------------------
//	Vector-Matrix Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
mat2<numType> vec2<numType>::operator + (const mat2<numType>& m2x2) const {
	return mat2<numType>(
		x + m2x2.xx, x + m2x2.xy,
		y + m2x2.yx, y + m2x2.yy
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> vec2<numType>::operator - (const mat2<numType>& m2x2) const {
	return mat2<numType>(
		x - m2x2.xx, x - m2x2.xy,
		y - m2x2.yx, y - m2x2.yy
	);
}

template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator * (const mat2<numType>& m2x2) const {
	return vec2<numType>(
		(m2x2.xx * x) + (m2x2.xy * y),
		(m2x2.yx * x) + (m2x2.yy * y)
	);
}

template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator *= (const mat2<numType>& m2x2) {
	vec2<numType> temp(
		(m2x2.xx * x) + (m2x2.xy * y),
		(m2x2.yx * x) + (m2x2.yy * y)
	);
	x = temp.x;
	y = temp.y;
	return *this;
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator = (numType input) {
	x = input;
	y = input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator + (numType input) const {
	return vec2<numType>(
		x + input,
		y + input
	);
}
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator - (numType input) const {
	return vec2<numType>(
		x - input,
		y - input
	);
}
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator * (numType input) const {
	return vec2<numType>(
		x * input,
		y * input
	);
}
template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::operator / (numType input) const {
	return vec2<numType>(
		x / input,
		y / input
	);
}
template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator += (numType input) {
	x += input;
	y += input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator -= (numType input) {
	x -= input;
	y -= input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator *= (numType input) {
	x *= input;
	y *= input;
	return *this;
}
template <class numType> HL_IMPERATIVE
vec2<numType>& vec2<numType>::operator /= (numType input) {
	x /= input;
	y /= input;
	return *this;
}

//---------------------------------------------------------------------
//	Vector Rotation Functions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
void vec2<numType>::rotate (numType radians) {
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
vec2<numType> vec2<numType>::rotVect (numType radians) {
	numType sinTheta = sin(radians);
	numType cosTheta = cos(radians);

	return vec2<numType>(
		(x*cosTheta) + (y*sinTheta),
		(y*cosTheta) - (x*sinTheta)
	);
}

//---------------------------------------------------------------------
//	Miscellaneous Functions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType vec2<numType>::Magnitude() const {
	return hamLibs::math::fastSqrt(
		(x * x)+
		(y * y)
	);
}

template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::getNormal() const {
	numType mag = hamLibs::math::fastInvSqrt(
		(x * x)+
		(y * y)
	);
	return vec2<numType>(
		x*mag,
		y*mag
	);
}

template <class numType> HL_IMPERATIVE
void vec2<numType>::normalize() {
	numType mag = hamLibs::math::fastInvSqrt(
		(x * x)+
		(y * y)
	);
	x *= mag;
	y *= mag;
}

template <class numType> HL_IMPERATIVE
numType vec2<numType>::dotProduct(const vec2<numType>& v1, const vec2<numType>& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

template <class numType> HL_IMPERATIVE
numType vec2<numType>::angleBetween(const vec2<numType>& v1, const vec2<numType>& v2, const vec2<numType>& origin) {
	return	acos(
				((v1.x - origin.x) * (v2.x - origin.x)) +
				((v1.y - origin.y) * (v2.y - origin.y))
			);
}

template <class numType> HL_IMPERATIVE
vec2<numType> vec2<numType>::crossProduct(const vec2<numType>& inVect2) {
	return vec2<numType>(
			inVect2.y,
			-inVect2.x
	);
}

template <class numType> HL_IMPERATIVE
void vec2<numType>::zero() {
	x = y = 0;
}

} //end math namespace
} //end hamlibs namespace
#endif /* __vect2_H__*/
