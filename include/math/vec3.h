/*
 * 3d vector structure
 * recommended for use with non-integral types

 * NOTES:
 * Orientation is as follows:
 * ----------
 *		X
 *		Y
 *		Z
 * ----------
*/

#ifndef __HL_MATH_VEC3_H__
#define __HL_MATH_VEC3_H__

#include "../utils/assert.h"

namespace hamLibs {
namespace math {

/* 3x3 Matrix forward declaration */
template <typename numType>
class mat3_t;

/******************************************************************************
 * 3D Vector Class
******************************************************************************/
template <typename numType>
struct vec3_t {
	union {
		numType v[3];
		struct {
			numType x, y, z;
		} index;
	};
    
    /*
     * Delegated Constructors
     * 
     * vec3_t()
     * vec3_t( numType n )
     * vec3_t( numType x, numType y, numType z )
     * vec3_t( const vec3_t& )
     * vec3_t( vec3_t&& )
     */
	// Main Constructor
	constexpr vec3_t(numType inX, numType inY, numType inZ) :
    	v{ inX, inY, inZ }
    {}
        
	constexpr vec3_t() :
        vec3_t(
            numType(0), numType(0), numType(0)
        )
    {}
    
	constexpr vec3_t( numType n ) :
        vec3_t(
            n, n, n
        )
    {}
    
	constexpr vec3_t(const vec3_t<numType>& input) :
    	vec3_t(
    		input.v[0], input.v[1], input.v[2]
    	)
    {}
    
	constexpr vec3_t(vec3_t<numType>&& input) :
    	vec3_t(
    		input.v[0], input.v[1], input.v[2]
    	)
    {}
    
	~vec3_t() = default;
    
	//array operators
#ifdef HL_DEBUG
	numType         operator        []      (int i) const {
                                                HL_ASSERT( (i>=0)&&(i<3) );
                                                return v[i];
                                            }
	numType&        operator        []      (int i) {
                                                HL_ASSERT( (i>=0)&&(i<3) );
                                                return v[i];
                                            }
#else
	constexpr numType operator      []      (int i) const { return v[i]; }
	inline numType& operator        []      (int i) { return v[i]; }
#endif

	//vector-vector operators
	vec3_t&			operator		= 		(const vec3_t<numType>&);
	vec3_t&			operator		= 		(vec3_t<numType>&&);
	vec3_t			operator 		+ 		(const vec3_t<numType>&) const;
	vec3_t			operator 		- 		(const vec3_t<numType>&) const;
	vec3_t			operator 		- 		() const;
	vec3_t			operator 		* 		(const vec3_t<numType>&) const;
	vec3_t			operator 		/ 		(const vec3_t<numType>&) const;
	vec3_t&			operator 		+= 		(const vec3_t<numType>&);
	vec3_t&			operator 		-= 		(const vec3_t<numType>&);
	vec3_t&			operator 		*= 		(const vec3_t<numType>&);
	vec3_t&			operator 		/= 		(const vec3_t<numType>&);
	vec3_t&			operator 		++		(); //prefix operators
	vec3_t&			operator 		--		();
	vec3_t			operator 		++		(int); //postfix operators
	vec3_t			operator 		--		(int);
	bool			operator		==		(const vec3_t<numType>& compare) const; //comparisons
	bool			operator		!=		(const vec3_t<numType>& compare) const;
	bool			operator		<		(const vec3_t<numType>& compare) const;
	bool			operator		>		(const vec3_t<numType>& compare) const;
	bool			operator		<=		(const vec3_t<numType>& compare) const;
	bool			operator		>=		(const vec3_t<numType>& compare) const;

	//vector-matrix operators (implementation in the matrix3 header)
	mat3_t<numType>	operator		+		(const mat3_t<numType>&) const;
	mat3_t<numType>	operator		-		(const mat3_t<numType>&) const;
	vec3_t<numType>	operator		*		(const mat3_t<numType>&) const;
	vec3_t&			operator		*=		(const mat3_t<numType>&);

	//vector-scalar operators
	vec3_t			operator 		= 		(numType);
	vec3_t			operator 		+ 		(numType) const;
	vec3_t			operator 		- 		(numType) const;
	vec3_t			operator 		* 		(numType) const;
	vec3_t			operator 		/ 		(numType) const;
	vec3_t&			operator 		+= 		(numType);
	vec3_t&			operator 		-= 		(numType);
	vec3_t&			operator 		*= 		(numType);
	vec3_t&			operator 		/= 		(numType);
};

//---------------------------------------------------------------------
//	Vector-Vector Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator = (const vec3_t<numType>& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator = (vec3_t<numType>&& input) {
	v[0] = input.v[0];
	v[1] = input.v[1];
	v[2] = input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator + (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] + input.v[0],
		v[1] + input.v[1],
		v[2] + input.v[2]
	);
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator - (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] - input.v[0],
		v[1] - input.v[1],
		v[2] - input.v[2]
	);
}

//for operations like "vectA = -vectB"
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator - () const {
	return vec3_t<numType>(-v[0], -v[1], -v[2]);
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator * (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] * input.v[0],
		v[1] * input.v[1],
		v[2] * input.v[2]
	);
}

template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator / (const vec3_t<numType>& input) const {
	return vec3_t<numType>(
		v[0] / input.v[0],
		v[1] / input.v[1],
		v[2] / input.v[2]
	);
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator += (const vec3_t<numType>& input) {
	v[0] += input.v[0];
	v[1] += input.v[1];
	v[2] += input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator -= (const vec3_t<numType>& input) {
	v[0] -= input.v[0];
	v[1] -= input.v[1];
	v[2] -= input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator *= (const vec3_t<numType>& input) {
	v[0] *= input.v[0];
	v[1] *= input.v[1];
	v[2] *= input.v[2];
	return *this;
}

template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator /= (const vec3_t<numType>& input) {
	v[0] /= input.v[0];
	v[1] /= input.v[1];
	v[2] /= input.v[2];
	return *this;
}

// prefix operations
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator++ () {
	++v[0];
	++v[1];
	++v[2];
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator-- () {
	--v[0];
	--v[1];
	--v[2];
	return *this;
}
//postfix operations
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator++ (int) {
	return vec3_t<numType>(
		++v[0],
		++v[1],
		++v[2]
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator-- (int) {
	return vec3_t<numType>(
		--v[0],
		--v[1],
		--v[2]
	);
}

//comparisons
template <typename numType> inline
bool vec3_t<numType>::operator== (const vec3_t<numType>& compare) const {
	return (	v[0] == compare.v[0] &&
				v[1] == compare.v[1] &&
				v[2] == compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator!= (const vec3_t<numType>& compare) const {
	return (	v[0] != compare.v[0] &&
				v[1] != compare.v[1] &&
				v[2] != compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator< (const vec3_t<numType>& compare) const {
	return (	v[0] < compare.v[0] &&
				v[1] < compare.v[1] &&
				v[2] < compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator> (const vec3_t<numType>& compare) const {
	return (	v[0] > compare.v[0] &&
				v[1] > compare.v[1] &&
				v[2] > compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator<= (const vec3_t<numType>& compare) const {
	return (	v[0] <= compare.v[0] &&
				v[1] <= compare.v[1] &&
				v[2] <= compare.v[2]
			);
}

template <typename numType> inline
bool vec3_t<numType>::operator>= (const vec3_t<numType>& compare) const {
	return (	v[0] >= compare.v[0] &&
				v[1] >= compare.v[1] &&
				v[2] >= compare.v[2]
			);
}

//---------------------------------------------------------------------
//	Vector-Scalar Math Operations
//---------------------------------------------------------------------
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator = (numType input) {
	v[0] = input;
	v[1] = input;
	v[2] = input;
	return *this;
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator + (numType input) const {
	return vec3_t<numType>(
		v[0] + input,
		v[1] + input,
		v[2] + input
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator - (numType input) const {
	return vec3_t<numType>(
		v[0] - input,
		v[1] - input,
		v[2] - input
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator * (numType input) const {
	return vec3_t<numType>(
		v[0] * input,
		v[1] * input,
		v[2] * input
	);
}
template <typename numType> inline
vec3_t<numType> vec3_t<numType>::operator / (numType input) const {
	return vec3_t<numType>(
		v[0] / input,
		v[1] / input,
		v[2] / input
	);
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator += (numType input) {
	v[0] += input;
	v[1] += input;
	v[2] += input;
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator -= (numType input) {
	v[0] -= input;
	v[1] -= input;
	v[2] -= input;
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator *= (numType input) {
	v[0] *= input;
	v[1] *= input;
	v[2] *= input;
	return *this;
}
template <typename numType> inline
vec3_t<numType>& vec3_t<numType>::operator /= (numType input) {
	v[0] /= input;
	v[1] /= input;
	v[2] /= input;
	return *this;
}

} //end math namespace
} //end hamlibs namespace

#endif /* __HL_MATH_VEC3_H__*/
