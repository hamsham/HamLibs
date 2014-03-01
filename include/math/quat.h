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

#include "../utils/assert.h"
#include "math/fixed.h"

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin quat structure
//---------------------------------------------------------------------
template <typename numType>
struct quat_t {
	union {
		numType q[4];
		struct {
			numType x, y, z, w;
		} index;
	};
    
    /*
     * Delegated Constructors
     * 
     * quat_t()
     * quat_t( numType n )
     * quat_t( numType x, numType y, numType z, numType w )
     * quat_t( const quat_t& )
     * quat_t( quat_t&& )
     */
	// Main Constructor
	constexpr quat_t(numType inX, numType inY, numType inZ, numType inW) :
    	q{ inX, inY, inZ, inW }
    {}
        
	constexpr quat_t() :
        quat_t(
            numType(0), numType(0), numType(0), numType(1)
        )
    {}
    
	constexpr quat_t( numType n ) :
        quat_t(
            n, n, n, numType(1)
        )
    {}
    
	constexpr quat_t(const quat_t<numType>& input) :
    	quat_t(
    		input.q[0], input.q[1], input.q[2], input.q[3]
    	)
    {}
    
	constexpr quat_t(quat_t<numType>&& input) :
    	quat_t(
    		input.q[0], input.q[1], input.q[2], input.q[3]
    	)
    {}
    
	~quat_t() = default;
    
	constexpr numType operator      []      (int i) const { return q[i]; }
	inline numType& operator        []      (int i) { return q[i]; }

	//quaternion-quaternion operators
	quat_t&			operator	++	(); //prefix operators
	quat_t&			operator	--	();
	quat_t			operator	++	(int); //postfix operators
	quat_t			operator	--	(int);
	quat_t			operator	+	(const quat_t<numType>& input) const;
	quat_t			operator	-	(const quat_t<numType>& input) const;
	quat_t			operator	*	(const quat_t<numType>& input) const;
	quat_t&			operator	=	(const quat_t<numType>& input);
	quat_t&			operator	=	(quat_t<numType>&& input);
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
};

/*
 * Quaternion Specializations
 */
HL_DECLARE_CLASS_TYPE(quatf, quat_t, float);
HL_DECLARE_CLASS_TYPE(quatd, quat_t, double);
HL_DECLARE_CLASS_TYPE(quati, quat_t, int);
HL_DECLARE_CLASS_TYPE(quatFixed, quat_t, medp_t);
HL_DECLARE_CLASS_TYPE(quat, quat_t, HL_FLOAT);

//---------------------------------------------------------------------
//  Non-Member Quaternion-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
quat_t<numType> operator + (numType n, const quat_t<numType>& q);

template <typename numType> inline
quat_t<numType> operator - (numType n, const quat_t<numType>& q);

template <typename numType> inline
quat_t<numType> operator * (numType n, const quat_t<numType>& q);

template <typename numType> inline
quat_t<numType> operator / (numType n, const quat_t<numType>& q);

//---------------------------------------------------------------------
//	Quaternion-Quaternion Operators
//---------------------------------------------------------------------
// prefix operators
template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator++ () {
	++q[0]; ++q[1]; ++q[2]; ++q[3];
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator-- () {
	--q[0]; --q[1]; --q[2]; --q[3];
	return *this;
}

//postfix operators
template <typename numType> inline
quat_t<numType> quat_t<numType>::operator++ (int) {
	return quat_t<numType>(
		++q[0], ++q[1], ++q[2], ++q[3]
	);
}

template <typename numType> inline
quat_t<numType> quat_t<numType>::operator-- (int) {
	return quat_t<numType>(
		--q[0], --q[1], --q[2], --q[3]
	);
}

template <typename numType> inline
quat_t<numType> quat_t<numType>::operator + (const quat_t<numType>& input) const {
	return quat_t<numType>(
		q[0] + input.q[0],
		q[1] + input.q[1],
		q[2] + input.q[2],
		q[3] + input.q[3]
	);
}

template <typename numType> inline
quat_t<numType> quat_t<numType>::operator - (const quat_t<numType>& input) const {
	return quat_t<numType>(
		q[0] - input.q[0],
		q[1] - input.q[1],
		q[2] - input.q[2],
		q[3] - input.q[3]
	);
}

template <typename numType> inline
quat_t<numType> quat_t<numType>::operator * (const quat_t<numType>& input) const {
	return quat_t<numType>(
		(input.q[3]*q[0]) + (input.q[0]*q[3]) + (input.q[1]*q[2]) - (input.q[2]*q[1]),
		(input.q[3]*q[1]) - (input.q[0]*q[2]) + (input.q[1]*q[3]) + (input.q[2]*q[0]),
		(input.q[3]*q[2]) + (input.q[0]*q[1]) - (input.q[1]*q[0]) + (input.q[2]*q[3]),
		(input.q[3]*q[3]) - (input.q[0]*q[0]) - (input.q[1]*q[1]) - (input.q[2]*q[2])
	);
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator = (const quat_t<numType>& input) {
	q[0] = input.q[0];
	q[1] = input.q[1];
	q[2] = input.q[2];
	q[3] = input.q[3];
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator = (quat_t<numType>&& input) {
	q[0] = input.q[0];
	q[1] = input.q[1];
	q[2] = input.q[2];
	q[3] = input.q[3];
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator += (const quat_t<numType>& input) {
	q[0] += input.q[0];
	q[1] += input.q[1];
	q[2] += input.q[2];
	q[3] += input.q[3];
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator -= (const quat_t<numType>& input) {
	q[0] -= input.q[0];
	q[1] -= input.q[1];
	q[2] -= input.q[2];
	q[3] -= input.q[3];
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator *= (const quat_t<numType>& input) {
	return *this = *this * input;
}

template <typename numType> inline
bool quat_t<numType>::operator == (const quat_t<numType>& compare) const {
	return	(
				q[0] == compare.q[0] &&
				q[1] == compare.q[1] &&
				q[2] == compare.q[2] &&
				q[3] == compare.q[3]
			);
}

template <typename numType> inline
bool quat_t<numType>::operator != (const quat_t<numType>& compare) const {
	return	(
				q[0] != compare.q[0] ||
				q[1] != compare.q[1] ||
				q[2] != compare.q[2] ||
				q[3] != compare.q[3]
			);
}

//---------------------------------------------------------------------
//					Quaternion-Scalar Operators
//---------------------------------------------------------------------
template <typename numType> inline
quat_t<numType> quat_t<numType>::operator + (numType input) const {
	return quat_t<numType>(
		q[0] + input,
		q[1] + input,
		q[2] + input,
		q[3] + input
	);
}

template <typename numType> inline
quat_t<numType> quat_t<numType>::operator - (numType input) const {
	return quat_t<numType>(
		q[0] - input,
		q[1] - input,
		q[2] - input,
		q[3] - input
	);
}

template <typename numType> inline
quat_t<numType> quat_t<numType>::operator * (numType input) const {
	return quat_t<numType>(
		q[0] * input,
		q[1] * input,
		q[2] * input,
		q[3] * input
	);
}

template <typename numType> inline
quat_t<numType> quat_t<numType>::operator / (numType input) const {
	return quat_t<numType>(
		q[0] / input,
		q[1] / input,
		q[2] / input,
		q[3] / input
	);
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator = (numType input) {
	q[0] = input;
	q[1] = input;
	q[2] = input;
	q[3] = input;
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator += (numType input) {
	q[0] += input;
	q[1] += input;
	q[2] += input;
	q[3] += input;
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator -= (numType input) {
	q[0] -= input;
	q[1] -= input;
	q[2] -= input;
	q[3] -= input;
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator *= (numType input) {
	q[0] *= input;
	q[1] *= input;
	q[2] *= input;
	q[3] *= input;
	return *this;
}

template <typename numType> inline
quat_t<numType>& quat_t<numType>::operator /= (numType input) {
	q[0] /= input;
	q[1] /= input;
	q[2] /= input;
	q[3] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Quaternion-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
quat_t<numType> operator + (numType n, const quat_t<numType>& q) {
	return q + n;
}

template <typename numType> inline
quat_t<numType> operator - (numType n, const quat_t<numType>& q) {
	return q - n;
}

template <typename numType> inline
quat_t<numType> operator * (numType n, const quat_t<numType>& q) {
	return q * n;
}

template <typename numType> inline
quat_t<numType> operator / (numType n, const quat_t<numType>& q) {
	return q / n;
}

} //end math namespace
} //end hamlibs namespace
#endif	/* QUAT_H */
