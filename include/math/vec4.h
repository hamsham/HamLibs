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

#include "../utils/assert.h"

namespace hamLibs {
namespace math {

/* 4x4 Matrix forward declaration */
template <typename numType>
class mat4_t;

/******************************************************************************
 * 4D Vector Class
******************************************************************************/
template <typename numType>
struct vec4_t {
	union {
		numType v[4];
		struct {
			numType x, y, z, w;
		} index;
	};
    
    /*
     * Delegated Constructors
     * 
     * vec4_t()
     * vec4_t( numType n )
     * vec4_t( numType x, numType y, numType z, numType w )
     * vec4_t( const vec4_t& )
     * vec4_t( vec4_t&& )
     */
	// Main Constructor
	constexpr vec4_t(numType inX, numType inY, numType inZ, numType inW) :
    	v{ inX, inY, inZ, inW }
    {}
        
	constexpr vec4_t() :
        vec4_t(
            numType(0), numType(0), numType(0), numType(1)
        )
    {}
    
	constexpr vec4_t( numType n ) :
        vec4_t(
            n, n, n, numType(1)
        )
    {}
    
	constexpr vec4_t(const vec4_t<numType>& input) :
    	vec4_t(
    		input.v[0], input.v[1], input.v[2], input.v[3]
    	)
    {}
    
	constexpr vec4_t(vec4_t<numType>&& input) :
    	vec4_t(
    		input.v[0], input.v[1], input.v[2], input.v[3]
    	)
    {}
    
	~vec4_t() = default;

	//array operators
#ifdef HL_DEBUG
	numType         operator        []      (int i) const {
                                                HL_ASSERT( (i>=0)&&(i<4) );
                                                return v[i];
                                            }
	numType&        operator        []      (int i) {
                                                HL_ASSERT( (i>=0)&&(i<4) );
                                                return v[i];
                                            }
#else
	constexpr numType operator      []      (int i) const { return v[i]; }
	inline numType& operator        []      (int i) { return v[i]; }
#endif

	//vector-vector operators
	vec4_t&			operator		= 		(const vec4_t<numType>&);
	vec4_t&			operator		= 		(vec4_t<numType>&&);
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

	//vector-matrix operators (implementation in the matrix4 header)
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
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType> operator + (numType n, const vec4_t<numType>& v);

template <typename numType> inline
vec4_t<numType> operator - (numType n, const vec4_t<numType>& v);

template <typename numType> inline
vec4_t<numType> operator * (numType n, const vec4_t<numType>& v);

template <typename numType> inline
vec4_t<numType> operator / (numType n, const vec4_t<numType>& v);

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator = (const vec4_t<numType>& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	v[3] = input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator = (vec4_t<numType>&& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	v[3] = input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator + (const vec4_t<numType>& input) const {
	return vec4_t(
		v[0] + input.v[0],
		v[1] + input.v[1],
		v[2] + input.v[2],
		v[3] + input.v[3]
	);
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator - (const vec4_t<numType>& input) const {
	return vec4_t(
		v[0] - input.v[0],
		v[1] - input.v[1],
		v[2] - input.v[2],
		v[3] - input.v[3]
	);
}

//for operations like "vectA = -vectB"
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator - () const {
	return vec4_t<numType>(-v[0], -v[1], -v[2], -v[3]);
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator * (const vec4_t<numType>& input) const {
	return vec4_t<numType>(
		v[0] * input.v[0],
		v[1] * input.v[1],
		v[2] * input.v[2],
		v[3] * input.v[3]
	);
}

template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator / (const vec4_t<numType>& input) const {
	return vec4_t<numType>(
		v[0] / input.v[0],
		v[1] / input.v[1],
		v[2] / input.v[2],
		v[3] / input.v[3]
	);
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator += (const vec4_t<numType>& input) {
    v[0] += input.v[0];
    v[1] += input.v[1];
    v[2] += input.v[2];
    v[3] += input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator -= (const vec4_t<numType>& input) {
    v[0] -= input.v[0];
    v[1] -= input.v[1];
    v[2] -= input.v[2];
    v[3] -= input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator *= (const vec4_t<numType>& input) {
    v[0] *= input.v[0];
    v[1] *= input.v[1];
    v[2] *= input.v[2];
    v[3] *= input.v[3];
	return *this;
}

template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator /= (const vec4_t<numType>& input) {
    v[0] /= input.v[0];
    v[1] /= input.v[1];
    v[2] /= input.v[2];
    v[3] /= input.v[3];
	return *this;
}

// prefix operations
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator++ () {
	++v[0];
	++v[1];
	++v[2];
	++v[3];
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator-- () {
	--v[0];
	--v[1];
	--v[2];
	--v[3];
	return *this;
}

//postfix operations
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator++ (int) {
	return vec4_t<numType>(
		++v[0],
		++v[1],
		++v[2],
		++v[3]
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator-- (int) {
	return vec4_t<numType>(
		--v[0],
		--v[1],
		--v[2],
		--v[3]
	);
}

//comparisons
template <typename numType> inline
bool vec4_t<numType>::operator== (const vec4_t<numType>& compare) const {
	return (	v[0] == compare.v[0] &&
				v[1] == compare.v[1] &&
				v[2] == compare.v[2] &&
				v[3] == compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator!= (const vec4_t<numType>& compare) const {
	return (	v[0] != compare.v[0] &&
				v[1] != compare.v[1] &&
				v[2] != compare.v[2] &&
				v[3] != compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator< (const vec4_t<numType>& compare) const {
	return (	v[0] < compare.v[0] &&
				v[1] < compare.v[1] &&
				v[2] < compare.v[2] &&
				v[3] < compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator> (const vec4_t<numType>& compare) const {
	return (	v[0] > compare.v[0] &&
				v[1] > compare.v[1] &&
				v[2] > compare.v[2] &&
				v[3] > compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator<= (const vec4_t<numType>& compare) const {
	return (	v[0] <= compare.v[0] &&
				v[1] <= compare.v[1] &&
				v[2] <= compare.v[2] &&
				v[3] <= compare.v[3]
			);
}

template <typename numType> inline
bool vec4_t<numType>::operator>= (const vec4_t<numType>& compare) const {
	return (	v[0] >= compare.v[0] &&
				v[1] >= compare.v[1] &&
				v[2] >= compare.v[2] &&
				v[3] >= compare.v[3]
			);
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator = (numType input) {
	v[0] = input;
	v[1] = input;
	v[2] = input;
	v[3] = input;
	return *this;
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator + (numType input) const {
	return vec4_t<numType>(
		v[0] + input,
		v[1] + input,
		v[2] + input,
		v[3] + input
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator - (numType input) const {
	return vec4_t<numType>(
		v[0] - input,
		v[1] - input,
		v[2] - input,
		v[3] - input
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator * (numType input) const {
	return vec4_t<numType>(
		v[0] * input,
		v[1] * input,
		v[2] * input,
		v[3] * input
	);
}
template <typename numType> inline
vec4_t<numType> vec4_t<numType>::operator / (numType input) const {
	return vec4_t<numType>(
		v[0] / input,
		v[1] / input,
		v[2] / input,
		v[3] / input
	);
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator += (numType input) {
    v[0] += input.v[0];
    v[1] += input.v[1];
    v[2] += input.v[2];
    v[3] += input.v[3];
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator -= (numType input) {
    v[0] -= input.v[0];
    v[1] -= input.v[1];
    v[2] -= input.v[2];
    v[3] -= input.v[3];
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator *= (numType input) {
    v[0] *= input.v[0];
    v[1] *= input.v[1];
    v[2] *= input.v[2];
    v[3] *= input.v[3];
	return *this;
}
template <typename numType> inline
vec4_t<numType>& vec4_t<numType>::operator /= (numType input) {
    v[0] /= input.v[0];
    v[1] /= input.v[1];
    v[2] /= input.v[2];
    v[3] /= input.v[3];
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec4_t<numType> operator + (numType n, const vec4_t<numType>& v) {
	return v + n;
}

template <typename numType> inline
vec4_t<numType> operator - (numType n, const vec4_t<numType>& v) {
	return v - n;
}

template <typename numType> inline
vec4_t<numType> operator * (numType n, const vec4_t<numType>& v) {
	return v * n;
}

template <typename numType> inline
vec4_t<numType> operator / (numType n, const vec4_t<numType>& v) {
	return v / n;
}

} //end math namespace
} //end hamlibs namespace
#endif /* __HL_MATH_VEC4_H__*/
