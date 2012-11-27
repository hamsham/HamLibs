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

#ifndef __HAMLIBS_MATH_QUAT_H__
#define __HAMLIBS_MATH_QUAT_H__

#include "math.h"


namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin quat class
//---------------------------------------------------------------------
template <class numType>
class quat {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const quat<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, quat<type>& );
	
	public:
		numType q[4];
		numType &x, &y, &z, &w;
		
		enum {X, Y, Z, W};

		//construction
		quat			();
		quat			(const numType input[4]);
		quat			(const quat<numType>& input);
		quat			(numType inX=0, numType inY=0, numType inZ=0, numType inW=1);
		~quat(){}

		//array operators
		numType			operator	[]	(int) const;
		numType&		operator	[]	(int);

		//quaternion-quaternion operators
		quat&			operator	++	(); //prefix operators
		quat&			operator	--	();
		quat			operator	++	(int); //postfix operators
		quat			operator	--	(int);
		quat			operator	+	(const quat<numType>& input) const;
		quat			operator	-	(const quat<numType>& input) const;
		quat			operator	*	(const quat<numType>& input) const;
		quat			operator	/	(const quat<numType>& input) const;
		quat&			operator	=	(const quat<numType>& input);
		quat&			operator	+=	(const quat<numType>& input);
		quat&			operator	-=	(const quat<numType>& input);
		quat&			operator	*=	(const quat<numType>& input);
		quat&			operator	/=	(const quat<numType>& input);
		bool			operator	==	(const quat<numType>& input) const;
		bool			operator	!=	(const quat<numType>& input) const;

		//misc functions
		numType			getMagnitude	() const;
		void			setNormal		();
		quat			getNormal		() const;
		void			setConjugate	();
		quat			getConjugate	() const;
		void			makeIdentity	();
		void			setInverse		();
		quat			getInverse		() const;

		//orientation
		void			slerp			(const quat& slerpPos, const numType& alpha);
		void			rotate			(const numType& yaw, const numType& pitch, const numType& roll);

		//output conversions
		void			toVect			(numType& outX, numType& outY, numType& outZ);
		void			toVect			(vec3<numType>& outVect);
		void			toAxes			(numType& outX, numType& outY, numType& outZ, numType& outAngle);
		void			toAxes			(vec3<numType>& outVect, numType& outAngle);
		void			toEuler			(numType& yaw, numType& pitch, numType& roll) const;
		void			toEuler			(vec3<numType>& rotVector) const;
		void			toMatrix3		(mat3<numType>& m3x3, bool isUnitQuat = true) const;
		void			toMatrix4		(mat4<numType>& m4x4, bool isUnitQuat = true) const;

		//input conversions
		void			fromVect		(const numType& inX, const numType& inY, const numType& inZ);
		void			fromVect		(const vec3<numType>& inVect);
		void			fromAxes		(const numType& inX, const numType& inY, const numType& inZ, const numType& radians);
		void			fromAxes		(const vec3<numType>& inVector, const numType& radians);
		void			fromEuler		(const numType& yaw, const numType& pitch, const numType& roll);
		void			fromEuler		(const vec3<numType>& rotationVector);
		void			fromMatrix3		(const mat3<numType>& m3x3);
		void			fromMatrix4		(const mat4<numType>& m4x4);
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const quat<type>& qt ) {
	sout
		<< qt.x << " " << qt.y << " " << qt.z << " " << qt.w;
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, quat<type>& qt ) {
	stin
		>> qt.x >> qt.y >> qt.z >> qt.w;
	return stin;
}

//---------------------------------------------------------------------
//				Quaternion Constructors
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
quat<numType>::quat() :
	quat(
		0, 0, 0, 1
	)
{}

template <class numType> HL_IMPERATIVE
quat<numType>::quat(const numType input[4]) :
	quat(
		input[X], input[Y], input[Z], input[W]
	)
{}

template <class numType> HL_IMPERATIVE
quat<numType>::quat(const quat<numType>& input) :
	quat(
		input.x, input.y, input.z, input.w
	)
{}

template <class numType> HL_IMPERATIVE
quat<numType>::quat(numType inX, numType inY, numType inZ, numType inW) :
	q{ inX, inY, inZ, inW },
	x( q[0] ), y( q[1] ), z( q[2] ), w( q[3] )
{}

//---------------------------------------------------------------------
//					Array Operators
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType quat<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 4));
	return q[ index ];
}

template <class numType> HL_IMPERATIVE
numType& quat<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 4));
	return q[ index ];
}

//---------------------------------------------------------------------
//	Quaternion-Quaternion Operators
//---------------------------------------------------------------------
// prefix operators
template <class numType> HL_IMPERATIVE
quat<numType>& quat<numType>::operator++ () {
	++x; ++y; ++z; ++w;
	return *this;
}

template <class numType> HL_IMPERATIVE
quat<numType>& quat<numType>::operator-- () {
	--x; --y; --z; --w;
	return *this;
}

//postfix operators
template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::operator++ (int) {
	return quat<numType>(
		++x, ++y, ++z, ++w
	);
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::operator-- (int) {
	return quat<numType>(
		--x, --y, --z, --w
	);
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::operator + (const quat<numType>& input) const {
	return quat<numType>(
		x + input.x,
		y + input.y,
		z + input.z,
		w + input.w
	);
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::operator - (const quat<numType>& input) const {
	return quat<numType>(
		x - input.x,
		y - input.y,
		z - input.z,
		w - input.w
	);
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::operator * (const quat<numType>& input) const {
	return quat<numType>(
		(w*input.x) - (x*input.w) - (y*input.z) - (z*input.y),
		(w*input.y) - (x*input.z) - (y*input.w) - (z*input.x),
		(w*input.z) - (x*input.y) - (y*input.x) - (z*input.w),
		(w*input.w) - (x*input.x) - (y*input.y) - (z*input.z)
	);
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::operator / (const quat<numType>& input) const {
	numType magnitude((input.x*input.x)+(input.y*input.y)+(input.z*input.z)+(input.w*input.w));

	return quat<numType>(
		((input.w*x) - (input.x*w) - (input.y*z) + (input.z*y)) / magnitude,
		((input.w*y) - (input.x*z) - (input.y*w) + (input.z*x)) / magnitude,
		((input.w*z) - (input.x*y) - (input.y*x) + (input.z*z)) / magnitude,
		((input.w*w) - (input.x*x) - (input.y*y) + (input.z*w)) / magnitude
	);
}

template <class numType> HL_IMPERATIVE
quat<numType>& quat<numType>::operator = (const quat<numType>& input) {
	x = input.x;
	y = input.y;
	z = input.z;
	w = input.w;
	return *this;
}

template <class numType> HL_IMPERATIVE
quat<numType>& quat<numType>::operator += (const quat<numType>& input) {
	x += input.x;
	y += input.y;
	z += input.z;
	w += input.w;
	return *this;
}

template <class numType> HL_IMPERATIVE
quat<numType>& quat<numType>::operator -= (const quat<numType>& input) {
	x -= input.x;
	y -= input.y;
	z -= input.z;
	w -= input.w;
	return *this;
}

template <class numType> HL_IMPERATIVE
quat<numType>& quat<numType>::operator *= (const quat<numType>& input) {
	*this = *this * input;
	return *this;
}

template <class numType> HL_IMPERATIVE
quat<numType>& quat<numType>::operator /= (const quat<numType>& input) {
	*this = *this / input;
	return *this;
}

template <class numType> HL_IMPERATIVE
bool quat<numType>::operator == (const quat<numType>& compare) const {
	return	(
				x == compare.x &&
				y == compare.y &&
				z == compare.z &&
				w == compare.w
			);
}

template <class numType> HL_IMPERATIVE
bool quat<numType>::operator != (const quat<numType>& compare) const {
	return	(
				x != compare.x &&
				y != compare.y &&
				z != compare.z &&
				w != compare.w
			);
}

//---------------------------------------------------------------------
//					Miscellaneous Functions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType quat<numType>::getMagnitude() const {
	return hamLibs::math::fastSqrt(
		(x * x) +
		(y * y) +
		(z * z) +
		(w * w)
	);
}

template <class numType> HL_IMPERATIVE
void quat<numType>::setNormal() {
	//get the inverse square root
	numType length = fastInvSqrt(getMagnitude());
	x *= length;
	y *= length;
	z *= length;
	w *= length;
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::getNormal() const {
	//get the inverse square root
	numType length = fastInvSqrt(getMagnitude());
	return quat<numType>(
		x * length,
		y * length,
		z * length,
		w * length
	);
}

template <class numType> HL_IMPERATIVE
void quat<numType>::setConjugate() {
	x = -x;
	y = -y;
	z = -z;
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::getConjugate() const {
	return quat<numType>(
		-x,
		-y,
		-z,
		w
	);
}

//This piece of slerpage was blatantly plagiarized from:
//http://www.gamasutra.com/view/feature/131686/rotating_objects_using_quaternions.php?page=2
//some info was also found in the DOOM 3 source code
template <class numType> HL_IMPERATIVE
void quat<numType>::slerp(const quat<numType>& slerpTo, const numType& alpha) {
	numType temp[4] = {0, 0, 0, 0};
	numType omega, sinTheta, cosTheta, scale0, scale1;

	cosTheta = (x*slerpTo.x) + (y*slerpTo.y) + (z*slerpTo.z) + (w*slerpTo.w);

	//make adjustment if necessary
	if (cosTheta < 0) {
		cosTheta = -cosTheta;
		temp.x = -slerpTo.x;
		temp.y = -slerpTo.y;
		temp.z = -slerpTo.z;
		temp.w = -slerpTo.w;
	}
	else {
		temp.x = slerpTo.x;
		temp.y = slerpTo.y;
		temp.z = slerpTo.z;
		temp.w = slerpTo.w;
	}

	//check if regular LERP should be used instead
	if (1-cosTheta > HL_EPSILON) {
		//standard SLERP
		omega = acos(cosTheta);
		sinTheta = sin(omega);
		scale0 = sin((1 - alpha) * omega) / sinTheta;
		scale1 = sin(alpha * omega) / sinTheta;
	}
	else {
		//use LERP if the distance to travel is too small
		scale0 = 1 - alpha;
		scale1 = alpha;
	}

	//store the final values
	x = (scale0 * x) + (scale1 * slerpTo.x);
	y = (scale0 * y) + (scale1 * slerpTo.y);
	z = (scale0 * z) + (scale1 * slerpTo.z);
	w = (scale0 * w) + (scale1 * slerpTo.w);
	this->normalize();
}

template <class numType> HL_IMPERATIVE
void quat<numType>::rotate(const numType& yaw, const numType& pitch, const numType& roll) {
	fromEuler(yaw, pitch, roll);
	setNormal();
}

template <class numType> HL_IMPERATIVE
void quat<numType>::makeIdentity() {
	x = y = z = 0;
	w = 1;
}

template <class numType> HL_IMPERATIVE
void quat<numType>::setInverse() {
	numType length = -1 / ((x*x) + (y*y) + (z*z) + (w*w));
	//multiplication is faster than division
	x *= length;
	y *= length;
	z *= length;
	w *= -length;
}

template <class numType> HL_IMPERATIVE
quat<numType> quat<numType>::getInverse() const {
	numType length = -1 / ((x*x) + (y*y) + (z*z) + (w*w));
	
	return quat<numType>(
		x * length,
		y * length,
		z * length,
		w * -length
	);
}

//---------------------------------------------------------------------
//					Output Conversions
//---------------------------------------------------------------------
//Code for this conversion was found at:
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm
template <class numType> HL_IMPERATIVE
void quat<numType>::toVect(numType& outX, numType& outY, numType& outZ) {
	if (w > 1) setNormal();		// if w>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
	float s = sqrt(1-(w*w));	// assuming quaternion normalized then w is less than 1, so term always positive.

	if (s < 001) {				// test to avoid divide by zero, s is always positive due to sqrt
		outX = x;				// if s close to zero then direction of axis not important
		outY = y;				// if it is important that axis is normalized then replace with x=1; y=z=0;
		outZ = z;
	}
	else {
		outX = x / s;			// normalize axis
		outY = y / s;
		outZ = z / s;
	}
}

template <class numType> HL_IMPERATIVE
void quat<numType>::toVect(vec3<numType>& outVect) {
	toVect(outVect.x, outVect.y, outVect.z);
}

template <class numType> HL_IMPERATIVE
void quat<numType>::toAxes(numType& outX, numType& outY, numType& outZ, numType& outAngle) {
	outAngle = acos(w) * 2;
	toVect(outX, outY, outZ);
}

template <class numType> HL_IMPERATIVE
void quat<numType>::toAxes(vec3<numType>& outVect, numType& outAngle) {
	toAxes(outVect.x, outVect.y, outVect.z, outAngle);
}

//more code found on:
//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
template <class numType> HL_IMPERATIVE
void quat<numType>::toEuler(numType& yaw, numType& pitch, numType& roll) const {
	numType sqw = w*w;
	numType sqx = x*x;
	numType sqy = y*y;
	numType sqz = z*z;
	numType unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	numType test = x*y + z*w;
	
	if (test > 0.499*unit) { // singularity at north pole
		pitch = 2 * atan2(x,w);
		yaw = HL_PI_OVR2;
		roll = 0;
		return;
	}
	else if (test < -0.499*unit) { // singularity at south pole
		pitch = -2 * atan2(x,w);
		yaw = -HL_PI_OVR2;
		roll = 0;
		return;
	}
	else {
		pitch = atan2((2*(y*w))-(2*(x*z)), sqx - sqy - sqz + sqw);
		yaw = asin(2*test/unit);
		roll = atan2((2*(x*w))-(2*(w*z)), -sqx + sqy - sqz + sqw);
	}
}

//code found on:
//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
template <class numType> HL_IMPERATIVE
void quat<numType>::toMatrix3(mat3<numType>& m3x3, bool isUnitQuat) const {
	numType xx = x * x;	numType yy = y * y;	numType zz = z * z;	numType ww = w * w;
	numType xy = x * y;	numType xz = x * z;	numType xw = x * w;
	numType yz = y * z;	numType yw = y * w;
	numType zw = z * w;
	
	if (isUnitQuat) {
		//"multiply" the angles by 2 and optimize if the current quaternion is a unit quaternion
		xx += xx; yy += yy; zz += zz;
		m3x3[0] = 1-(yy+zz);	m3x3[1] = 2*(xy-zw);	m3x3[2] = 2*(xz+yw);
		m3x3[3] = 2*(xy+zw);	m3x3[4] = 1-(xx+zz);	m3x3[5] = 2*(yz+xw);
		m3x3[6] = 2*(xz+yw);	m3x3[7] = 2*(yz+xw);	m3x3[8] = 1-(xx+yy);
	}
	else {
		m3x3[0] = ww+xx-zz-yy;	m3x3[1] = -zw+xy-zw+xy;	m3x3[2] = yw+xz+xz+yw;
		m3x3[3] = xy+zw+zw+xy;	m3x3[4] = yy-zz+ww-xx;	m3x3[5] = yz+yz-xw-xw;
		m3x3[6] = xz-yw+xz-yw;	m3x3[7] = yz+yz+xw+xw;	m3x3[8] = zz-yy-xx+ww;
	}
}

template <class numType> HL_IMPERATIVE
void quat<numType>::toMatrix4(mat4<numType>& m4x4, bool isUnitQuat) const {
	numType xx = x * x;	numType yy = y * y;	numType zz = z * z;	numType ww = w * w;
	numType xy = x * y;	numType xz = x * z;	numType xw = x * w;
	numType yz = y * z;	numType yw = y * w;
	numType zw = z * w;
	
	if (isUnitQuat) {
		//"multiply" the angles by 2 and optimize if the current quaternion is a unit quaternion
		xx += xx; yy += yy; zz += zz;
		m4x4[0] = 1-(yy+zz);	m4x4[1] = 2*(xy-zw);	m4x4[2] = 2*(xz+yw);	m4x4[3] = 0;
		m4x4[4] = 2*(xy+zw);	m4x4[5] = 1-(xx+zz);	m4x4[6] = 2*(yz+xw);	m4x4[7] = 0;
		m4x4[8] = 2*(xz+yw);	m4x4[9] = 2*(yz+xw);	m4x4[10] = 1-(xx+yy);	m4x4[11] = 0;
		m4x4[12] = 0;			m4x4[13] = 0;			m4x4[14] = 0;			m4x4[15] = 1;
	}
	else {
		m4x4[0] = ww+xx-zz-yy;	m4x4[1] = -zw+xy-zw+xy;	m4x4[2] = yw+xz+xz+yw;	m4x4[3] = 0;
		m4x4[4] = xy+zw+zw+xy;	m4x4[5] = yy-zz+ww-xx;	m4x4[6] = yz+yz-xw-xw;	m4x4[7] = 0;
		m4x4[8] = xz-yw+xz-yw;	m4x4[9] = yz+yz+xw+xw;	m4x4[10] = zz-yy-xx+ww;	m4x4[11] = 0;
		m4x4[12] = 0;			m4x4[13] = 0;			m4x4[14] = 0;			m4x4[15] = 1;
	}
}


//---------------------------------------------------------------------
//					Input Conversions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
void quat<numType>::fromVect(const numType& inX, const numType& inY, const numType& inZ) {
	x = inX;
	y = inY;
	z = inZ;
	w = 0;
}

template <class numType> HL_IMPERATIVE
void quat<numType>::fromVect(const vec3<numType>& inVector) {
	fromVect(inVector.x, inVector.y, inVector.z);
}

template <class numType> HL_IMPERATIVE
void quat<numType>::fromAxes(const numType& inX, const numType& inY, const numType& inZ, const numType& radians) {
	numType angle = sin(radians * 0.5);
	x = inX * angle;
	y = inY * angle;
	z = inZ * angle;
	w = cos(radians * 0.5);
}

template <class numType> HL_IMPERATIVE
void quat<numType>::fromAxes(const vec3<numType>& inVector, const numType& radians) {
	fromAxes(inVector.x, inVector.y, inVector.z, radians);
}

template <class numType> HL_IMPERATIVE
void quat<numType>::fromEuler(const numType& yaw, const numType& pitch, const numType& roll) {
	//too many premature optimizations went into this
	numType sP	(sin(pitch*0.5));
	numType cP	(cos(pitch*0.5));
	numType sY	(sin(yaw*0.5));
	numType cY	(cos(yaw*0.5));
	numType sR	(sin(roll*0.5));
	numType cR	(cos(roll*0.5));
	
	numType sPsY(sP*sY);
	numType sPcY(sP*cY);
	numType cPsY(cP*sY);
	numType cPcY(cP*cY);
	
	x = sR * cPcY	-	cR * sPsY;
	y = cR * sPcY	+	sR * cPsY;
	z = cR * cPsY	-	sR * sPcY;
	w = cR * cPcY	+	sR * sPsY;
}

template <class numType> HL_IMPERATIVE
void quat<numType>::fromEuler(const vec3<numType>& rotationVector) {
	fromEuler(rotationVector.x, rotationVector.y, rotationVector.z);
}

// 	matrix-quaternion conversions found from
//	http://www.j3d.org/matrix_faq/matrfaq_latest.html
template <class numType> HL_IMPERATIVE
void quat<numType>::fromMatrix3(const mat3<numType>& m3x3) {
	//calculate the trace of the input matrix major diagonal
	numType trace = 4 * (1 - (m3x3[0]*m3x3[0]) - (m3x3[4]*m3x3[4]) - (m3x3[8]*m3x3[8]));
	numType temp = 0;

	//if the matrix trace value is too small, perform an immediate conversion
	if (trace > HL_EPSILON) {
		temp = fastInvSqrt(trace) * 0.5;
		x = (m3x3[7] - m3x3[5]) * temp;
		y = (m3x3[2] - m3x3[6]) * temp;
		z = (m3x3[3] - m3x3[1]) * temp;
		w = 0.25 / temp;
	}
	//if the trace of the matrix is equal to 0, then find out
	//which major diagonal has the greatest value.
	if (m3x3[0] > m3x3[5] && m3x3[0] > m3x3[8]) { //first column
		temp = fastInvSqrt(1 + m3x3[0] - m3x3[4] - m3x3[8]) * 0.5;
		x = 0.25 / temp;
		y = (m3x3[3] + m3x3[1]) * temp;
		z = (m3x3[2] + m3x3[6]) * temp;
		w = (m3x3[7] - m3x3[5]) * temp;
	}
	else if (m3x3[4] > m3x3[8]) {
		temp = fastInvSqrt(1 + m3x3[4] - m3x3[0] - m3x3[8]) * 0.5;
		x = (m3x3[3] + m3x3[1]) * temp;
		y = 0.25 / temp;
		z = (m3x3[7] + m3x3[5]) * temp;
		w = (m3x3[2] - m3x3[6]) * temp;
	}
	else {
		temp = fastInvSqrt(1 + m3x3[4] - m3x3[0] - m3x3[8]) * 0.5;
		x = (m3x3[2] + m3x3[6]) * temp;
		y = (m3x3[7] + m3x3[5]) * temp;
		z = 0.25 / temp;
		w = (m3x3[3] - m3x3[1]) * temp;
	}
}

template <class numType> HL_IMPERATIVE
void quat<numType>::fromMatrix4(const mat4<numType>& m4x4) {
	//calculate the trace of the input matrix major diagonal
	numType trace = 4 * (1 - (m4x4[0]*m4x4[0]) - (m4x4[5]*m4x4[5]) - (m4x4[10]*m4x4[10]));
	numType temp = 0;

	//if the matrix trace value is too small, perform an immediate conversion
	if (trace > HL_EPSILON) {
		temp = fastInvSqrt(trace) * 0.5;
		x = (m4x4[9] - m4x4[6]) * temp;
		y = (m4x4[2] - m4x4[8]) * temp;
		z = (m4x4[4] - m4x4[1]) * temp;
		w = 0.25 / temp;
	}
	//if the trace of the matrix is equal to 0, then find out
	//which major diagonal has the greatest value.
	if (m4x4[0] > m4x4[5] && m4x4[0] > m4x4[10]) { //first column
		temp = fastInvSqrt(1 + m4x4[0] - m4x4[5] - m4x4[10]) * 0.5;
		x = 0.25 / temp;
		y = (m4x4[4] + m4x4[1]) * temp;
		z = (m4x4[2] + m4x4[8]) * temp;
		w = (m4x4[9] - m4x4[6]) * temp;
	}
	else if (m4x4[5] > m4x4[10]) {
		temp = fastInvSqrt(1 + m4x4[5] - m4x4[0] - m4x4[10]) * 0.5;
		x = (m4x4[4] + m4x4[1]) * temp;
		y = 0.25 / temp;
		z = (m4x4[9] + m4x4[6]) * temp;
		w = (m4x4[2] - m4x4[8]) * temp;
	}
	else {
		temp = fastInvSqrt(1 + m4x4[5] - m4x4[0] - m4x4[10]) * 0.5;
		x = (m4x4[2] + m4x4[8]) * temp;
		y = (m4x4[9] + m4x4[6]) * temp;
		z = 0.25 / temp;
		w = (m4x4[4] - m4x4[1]) * temp;
	}
}

} //end math namespace
} //end hamlibs namespace
#endif	/* QUAT_H */
