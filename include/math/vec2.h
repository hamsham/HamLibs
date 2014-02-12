/*
 * 2d vector structure
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 * ----------
*/

#ifndef __HL_MATH_VEC2_H__
#define __HL_MATH_VEC2_H__

#include "../utils/assert.h"

namespace hamLibs {
namespace math {

/* 2x2 Matrix forward declaration */
template <typename numType>
class mat2_t;

/******************************************************************************
 * 2D Vector Class
******************************************************************************/
template <typename numType>
struct vec2_t {
	union {
		numType v[2];
		struct {
			numType	x, y;
		} index;
	};
    
    /*
     * Delegated Constructors
     * 
     * vec2_t()
     * vec2_t( numType n )
     * vec2_t( numType x, numType y )
     * vec2_t( const vec2_t& )
     * vec2_t( vec2_t&& )
     */
	// Main Constructor
	constexpr vec2_t(numType inX, numType inY) :
    	v{ inX, inY }
    {}
        
	constexpr vec2_t() :
        vec2_t(
            numType(0), numType(0)
        )
    {}
    
	constexpr vec2_t( numType n ) :
        vec2_t(
            n, n
        )
    {}
    
	constexpr vec2_t(const vec2_t<numType>& input) :
    	vec2_t(
    		input.v[0], input.v[1]
    	)
    {}
    
	constexpr vec2_t(vec2_t<numType>&& input) :
    	vec2_t(
    		input.v[0], input.v[1]
    	)
    {}
    
	~vec2_t() = default;

	//array operators
#ifdef HL_DEBUG
	numType         operator        []      (int i) const {
                                                HL_ASSERT( (i==0)||(i==1) );
                                                return v[i];
                                            }
	numType&        operator        []      (int i) {
                                                HL_ASSERT( (i==0)||(i==1) );
                                                return v[i];
                                            }
#else
	constexpr numType operator      []      (int i) const { return v[i]; }
	inline numType& operator        []      (int i) { return v[i]; }
#endif
    
	//vector-vector operators
	vec2_t&			operator		= 		(const vec2_t<numType>&);
	vec2_t&			operator		= 		(vec2_t<numType>&&);
	vec2_t			operator 		+ 		(const vec2_t<numType>&) const;
	vec2_t			operator 		- 		(const vec2_t<numType>&) const;
	vec2_t			operator 		- 		() const;
	vec2_t			operator 		* 		(const vec2_t<numType>&) const;
	vec2_t			operator 		/ 		(const vec2_t<numType>&) const;
	vec2_t&			operator 		+= 		(const vec2_t<numType>&);
	vec2_t&			operator 		-= 		(const vec2_t<numType>&);
	vec2_t&			operator 		*= 		(const vec2_t<numType>&);
	vec2_t&			operator 		/= 		(const vec2_t<numType>&);
	vec2_t&			operator 		++		(); //prefix operators
	vec2_t&			operator 		--		();
	vec2_t			operator 		++		(int); //postfix operators
	vec2_t			operator 		--		(int);
	bool			operator		==		(const vec2_t<numType>& compare) const; //comparisons
	bool			operator		!=		(const vec2_t<numType>& compare) const;
	bool			operator		<		(const vec2_t<numType>& compare) const;
	bool			operator		>		(const vec2_t<numType>& compare) const;
	bool			operator		<=		(const vec2_t<numType>& compare) const;
	bool			operator		>=		(const vec2_t<numType>& compare) const;

	//vector-matrix operators (implementation in the matrix2 header)
	mat2_t<numType>	operator		+		(const mat2_t<numType>&) const;
	mat2_t<numType>	operator		-		(const mat2_t<numType>&) const;
	vec2_t<numType>	operator		*		(const mat2_t<numType>&) const;
	vec2_t&			operator		*=		(const mat2_t<numType>&);

	//vector-scalar operators
	vec2_t			operator 		= 		(numType);
	vec2_t			operator 		+ 		(numType) const;
	vec2_t			operator 		- 		(numType) const;
	vec2_t			operator 		* 		(numType) const;
	vec2_t			operator 		/ 		(numType) const;
	vec2_t&			operator 		+= 		(numType);
	vec2_t&			operator 		-= 		(numType);
	vec2_t&			operator 		*= 		(numType);
	vec2_t&			operator 		/= 		(numType);
};

//---------------------------------------------------------------------
//  Non-Member Matrix-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType> operator + (numType n, const vec2_t<numType>& v);

template <typename numType> inline
vec2_t<numType> operator - (numType n, const vec2_t<numType>& v);

template <typename numType> inline
vec2_t<numType> operator * (numType n, const vec2_t<numType>& v);

template <typename numType> inline
vec2_t<numType> operator / (numType n, const vec2_t<numType>& v);

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator = (const vec2_t<numType>& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator = (vec2_t<numType>&& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator + (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] + input.v[0],
		v[1] + input.v[1]
	);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator - (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] - input.v[0],
		v[1] - input.v[1]
	);
}

//for operations like "vectA = -vectB"
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator - () const {
	return vec2_t<numType>(-v[0], -v[1]);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator * (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] * input.v[0],
		v[1] * input.v[1]
	);
}

template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator / (const vec2_t<numType>& input) const {
	return vec2_t<numType>(
		v[0] / input.v[0],
		v[1] / input.v[1]
	);
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator += (const vec2_t<numType>& input) {
	v[0] += input.v[0];
	v[1] += input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator -= (const vec2_t<numType>& input) {
	v[0] -= input.v[0];
	v[1] -= input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator *= (const vec2_t<numType>& input) {
	v[0] *= input.v[0];
	v[1] *= input.v[1];
	return *this;
}

template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator /= (const vec2_t<numType>& input) {
	v[0] /= input.v[0];
	v[1] /= input.v[1];
	return *this;
}

// prefix operations
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator++ () {
	++v[0];
	++v[1];
	return *this;
}
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator-- () {
	--v[0];
	--v[1];
	return *this;
}
//postfix operations
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator++ (int) {
	return vec2_t<numType>(
		++v[0],
		++v[1]
	);
}
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator-- (int) {
	return vec2_t<numType>(
		--v[0],
		--v[1]
	);
}

//comparisons
template <typename numType> inline
bool vec2_t<numType>::operator== (const vec2_t<numType>& compare) const {
	return (	v[0] == compare.v[0] &&
				v[1] == compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator!= (const vec2_t<numType>& compare) const {
	return (	v[0] != compare.v[0] &&
				v[1] != compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator< (const vec2_t<numType>& compare) const {
	return (	v[0] < compare.v[0] &&
				v[1] < compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator> (const vec2_t<numType>& compare) const {
	return (	v[0] > compare.v[0] &&
				v[1] > compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator<= (const vec2_t<numType>& compare) const {
	return (	v[0] <= compare.v[0] &&
				v[1] <= compare.v[1]
			);
}

template <typename numType> inline
bool vec2_t<numType>::operator>= (const vec2_t<numType>& compare) const {
	return (	v[0] >= compare.v[0] &&
				v[1] >= compare.v[1]
			);
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator = (numType input) {
	v[0] = input;
	v[1] = input;
	return *this;
}
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator + (numType input) const {
	return vec2_t<numType>(
		v[0] + input,
		v[1] + input
	);
}
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator - (numType input) const {
	return vec2_t<numType>(
		v[0] - input,
		v[1] - input
	);
}
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator * (numType input) const {
	return vec2_t<numType>(
		v[0] * input,
		v[1] * input
	);
}
template <typename numType> inline
vec2_t<numType> vec2_t<numType>::operator / (numType input) const {
	return vec2_t<numType>(
		v[0] / input,
		v[1] / input
	);
}
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator += (numType input) {
    v[0] += input;
    v[1] += input;
	return *this;
}
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator -= (numType input) {
    v[0] -= input;
    v[1] -= input;
	return *this;
}
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator *= (numType input) {
    v[0] *= input;
    v[1] *= input;
	return *this;
}
template <typename numType> inline
vec2_t<numType>& vec2_t<numType>::operator /= (numType input) {
    v[0] /= input;
    v[1] /= input;
	return *this;
}

//---------------------------------------------------------------------
//  Non-Member Vector-Scalar operations
//---------------------------------------------------------------------
template <typename numType> inline
vec2_t<numType> operator + (numType n, const vec2_t<numType>& v) {
	return v + n;
}

template <typename numType> inline
vec2_t<numType> operator - (numType n, const vec2_t<numType>& v) {
	return v - n;
}

template <typename numType> inline
vec2_t<numType> operator * (numType n, const vec2_t<numType>& v) {
	return v * n;
}

template <typename numType> inline
vec2_t<numType> operator / (numType n, const vec2_t<numType>& v) {
	return v / n;
}

} //end math namespace
} //end hamlibs namespace

#endif /* __HL_MATH_VEC2_H__*/
