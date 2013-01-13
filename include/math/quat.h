//---------------------------------------------------------------------
//					Quaternion Class
//---------------------------------------------------------------------

/*
NOTES:
 * Since the actual quaternion, Q is set up as an array,the vector
 * components (X, Y, & Z) are the first three elements in the array.
 * The angle component, W, is the fourth element in the array
 * i.e. Q = <X,Y,Z,W>
 */

#ifndef __HL_MATH_QUAT_H__
#define __HL_MATH_QUAT_H__

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin quat structure
//---------------------------------------------------------------------
template <typename numType>
struct quat_t {
	numType q[4];
	numType &x, &y, &z, &w;

	//construction (all delegated)
	quat_t			();
	quat_t			(const quat_t<numType>& input);
	quat_t			(	numType inX, numType inY, numType inZ, numType inW );
	~quat_t()		{}

	//array operators
	numType			operator	[]	(int) const;
	numType&		operator	[]	(int);

	//quaternion-quaternion operators
	quat_t&			operator	++	(); //prefix operators
	quat_t&			operator	--	();
	quat_t			operator	++	(int); //postfix operators
	quat_t			operator	--	(int);
	quat_t			operator	+	(const quat_t<numType>& input) const;
	quat_t			operator	-	(const quat_t<numType>& input) const;
	quat_t			operator	*	(const quat_t<numType>& input) const;
	quat_t&			operator	=	(const quat_t<numType>& input);
	quat_t&			operator	+=	(const quat_t<numType>& input);
	quat_t&			operator	-=	(const quat_t<numType>& input);
	quat_t&			operator	*=	(const quat_t<numType>& input);
	bool			operator	==	(const quat_t<numType>& input) const;
	bool			operator	!=	(const quat_t<numType>& input) const;

	//quaternion-scalar operators
	quat_t			operator	+	(numType) const;
	quat_t			operator	-	(numType) const;
	quat_t			operator	*	(numType) const;
	quat_t			operator	/	(numType) const;
	quat_t&			operator	=	(numType);
	quat_t&			operator	+=	(numType);
	quat_t&			operator	-=	(numType);
	quat_t&			operator	*=	(numType);
	quat_t&			operator	/=	(numType);
/*
	void			toEuler			(numType& yaw, numType& pitch, numType& roll) const;
	void			toEuler			(vec3_t<numType>& rotVector) const;
*/
};

//---------------------------------------------------------------------
//				Quaternion Constructors
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
quat_t<numType>::quat_t() :
	quat_t(
		numType(0), numType(0), numType(0), numType(1)
	)
{}

template <typename numType> HL_IMPERATIVE
quat_t<numType>::quat_t(const quat_t<numType>& input) :
	quat_t(
		input.x, input.y, input.z, input.w
	)
{}

template <typename numType> HL_IMPERATIVE
quat_t<numType>::quat_t(numType inX, numType inY, numType inZ, numType inW) :
	// all constructors are delegated to use this.
	// make the references equal a value in the array
	q{ inX, inY, inZ, inW },
	x( q[0] ), y( q[1] ), z( q[2] ), w( q[3] )
{}

//---------------------------------------------------------------------
//					Array Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
numType quat_t<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 4));
	return q[ index ];
}

template <typename numType> HL_IMPERATIVE
numType& quat_t<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 4));
	return q[ index ];
}

//---------------------------------------------------------------------
//	Quaternion-Quaternion Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator++ () {
	++x; ++y; ++z; ++w;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator-- () {
	--x; --y; --z; --w;
	return *this;
}

//postfix operators
template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator++ (int) {
	return quat_t<numType>(
		++x, ++y, ++z, ++w
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator-- (int) {
	return quat_t<numType>(
		--x, --y, --z, --w
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator + (const quat_t<numType>& input) const {
	return quat_t<numType>(
		x + input.x,
		y + input.y,
		z + input.z,
		w + input.w
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator - (const quat_t<numType>& input) const {
	return quat_t<numType>(
		x - input.x,
		y - input.y,
		z - input.z,
		w - input.w
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator * (const quat_t<numType>& input) const {
	return quat_t<numType>(
		(input.w*x) + (input.x*w) + (input.y*z) - (input.z*y),
		(input.w*y) - (input.x*z) + (input.y*w) + (input.z*x),
		(input.w*z) + (input.x*y) - (input.y*x) + (input.z*w),
		(input.w*w) - (input.x*x) - (input.y*y) - (input.z*z)
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator = (const quat_t<numType>& input) {
	x = input.x;
	y = input.y;
	z = input.z;
	w = input.w;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator += (const quat_t<numType>& input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator -= (const quat_t<numType>& input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator *= (const quat_t<numType>& input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
bool quat_t<numType>::operator == (const quat_t<numType>& compare) const {
	return	(
				x == compare.x &&
				y == compare.y &&
				z == compare.z &&
				w == compare.w
			);
}

template <typename numType> HL_IMPERATIVE
bool quat_t<numType>::operator != (const quat_t<numType>& compare) const {
	return	(
				x != compare.x &&
				y != compare.y &&
				z != compare.z &&
				w != compare.w
			);
}

//---------------------------------------------------------------------
//					Quaternion-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator + (numType input) const {
	return quat_t<numType>(
		x + input,
		y + input,
		z + input,
		w + input
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator - (numType input) const {
	return quat_t<numType>(
		x - input,
		y - input,
		z - input,
		w - input
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator * (numType input) const {
	return quat_t<numType>(
		x * input,
		y * input,
		z * input,
		w * input
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType> quat_t<numType>::operator / (numType input) const {
	return quat_t<numType>(
		x / input,
		y / input,
		z / input,
		w / input
	);
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator = (numType input) {
	x = input;
	y = input;
	z = input;
	w = input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator += (numType input) {
	*this = *this + input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator -= (numType input) {
	*this = *this - input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator *= (numType input) {
	*this = *this * input;
	return *this;
}

template <typename numType> HL_IMPERATIVE
quat_t<numType>& quat_t<numType>::operator /= (numType input) {
	*this = *this / input;
	return *this;
}

/*
//more code found on:
//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
template <typename numType> HL_IMPERATIVE
void quat_t<numType>::toEuler(numType& yaw, numType& pitch, numType& roll) const {
	numType sqw = w*w;
	numType sqx = x*x;
	numType sqy = y*y;
	numType sqz = z*z;
	numType unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	numType test = x*y + z*w;
	
	if (test > HL_EPSILON*unit) { // singularity at north pole
		pitch = numType(2) * atan2(x,w);
		yaw = HL_PI_OVR2;
		roll = 0;
		return;
	}
	else if (test < -HL_EPSILON*unit) { // singularity at south pole
		pitch = numType(-2) * atan2(x,w);
		yaw = -HL_PI_OVR2;
		roll = numType(0);
		return;
	}
	else {
		pitch = atan2((numType(2)*(y*w))-(numType(2)*(x*z)), sqx - sqy - sqz + sqw);
		yaw = asin(numType(2)*test/unit);
		roll = atan2((numType(2)*(x*w))-(numType(2)*(w*z)), -sqx + sqy - sqz + sqw);
	}
}
*/

} //end math namespace
} //end hamlibs namespace
#endif	/* QUAT_H */
