/*
 * 3d mat class
 * recommended for use with non-integral types

 * NOTES:
 * mat is Row-Major
 * orientation is as follows:
 * ----------------
 *		XX	XY
 *		YX	YY
 * ----------------
*/

#ifndef __HAMLIBS_MATH_MATRIX2_H__
#define __HAMLIBS_MATH_MATRIX2_H__

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat2 class
//---------------------------------------------------------------------
template <class numType>
class mat2 {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const mat2<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, mat2<type>& );
	
	public:
		numType	m2[4];
		numType	&xx, &xy,
				&yx, &yy; // these references are attached to the array above during construction

		enum coords {	XX, XY,
						YX, YY	};

		//hardhat construction
		//mat2();
		mat2(const numType input[4]);
		mat2(const mat2<numType>& input);
		mat2(	numType inXX = 1, numType inXY = 0,
				numType inYX = 0, numType inYY = 1);
		~mat2() {};

		//array operators
		numType			operator	[]		(int) const;
		numType&		operator	[]		(int);

		//mat-mat operators
		mat2&			operator	++		();			//prefix operators
		mat2&			operator	--		();
		mat2			operator	++		(int);	//postfix operators
		mat2			operator	--		(int);
		mat2			operator	+		(const mat2<numType>& input) const;
		mat2			operator	-		(const mat2<numType>& input) const;
		mat2			operator	-		() const;
		mat2			operator	*		(const mat2<numType>& input) const;
		mat2&			operator	=		(const mat2<numType>& input);
		mat2&			operator	+=		(const mat2<numType>& input);
		mat2&			operator	-=		(const mat2<numType>& input);
		mat2&			operator	*=		(const mat2<numType>& input);
		bool			operator	==		(const mat2<numType>& input) const;
		bool			operator	!=		(const mat2<numType>& input) const;

		//mat-vector operators
		mat2			operator	+		(const vec2<numType>&) const;
		mat2			operator	-		(const vec2<numType>&) const;
		vec2<numType>	operator	*		(const vec2<numType>&) const;
		mat2&			operator	=		(const vec2<numType>&);
		mat2&			operator	+=		(const vec2<numType>&);
		mat2&			operator	-=		(const vec2<numType>&);

		//mat-scalar operators
		mat2			operator	+		(numType) const;
		mat2			operator	-		(numType) const;
		mat2			operator	*		(numType) const;
		mat2			operator	/		(numType) const;
		mat2&			operator	=		(numType);
		mat2&			operator	+=		(numType);
		mat2&			operator	-=		(numType);
		mat2&			operator	*=		(numType);
		mat2&			operator	/=		(numType);

		//movement & translation
		static mat2		rotmat				(numType radians);
		void			rotate				(numType radians);

		//miscellaneous functions
		static mat2		getIdentity			();
		void			setIdentity			();
		mat2			getNormal			() const;
		void			setNormal			();
		numType			getDeterminant		() const;
		mat2			getTransposed		() const;
		void			setTransposed		();
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_IMPERATIVE
std::ostream& operator << ( std::ostream& sout, const mat2<type>& mat ) {
	sout
		<< mat.xx << " " << mat.xy << " "
		<< mat.yx << " " << mat.yy;
	return sout;
}

template <typename type> HL_IMPERATIVE
std::istream& operator >> ( std::istream& stin, mat2<type>& mat ) {
	stin
		>> mat.xx >> mat.xy
		>> mat.yx >> mat.yy;
	return stin;
}

//---------------------------------------------------------------------
//	2x2 Matrix Constructors (mostly delegated)
//---------------------------------------------------------------------
//construct all matricies as identity matricies unless stated otherwise
//all constructions use list-initializations
/*
template <class numType> HL_IMPERATIVE
mat2<numType>::mat2() :
	mat2(
		1, 0,
		1, 0
	)
{}
*/
template <class numType> HL_IMPERATIVE
mat2<numType>::mat2(const numType input[4]) :
	mat2(
		input[ 0 ], input[ 1 ],
		input[ 2 ], input[ 3 ]
	)
{}

template <class numType> HL_IMPERATIVE
mat2<numType>::mat2(const mat2<numType>& input) :
	mat2(
		input.xx, input.xy,
		input.yx, input.yy
	)
{}

template <class numType> HL_IMPERATIVE
mat2<numType>::mat2(	numType inXX, numType inXY,
						numType inYX, numType inYY) :
	m2{
		inXX, inXY,
		inYX, inYY
	},
	xx( m2[0] ), xy( m2[1] ),
	yx( m2[2] ), yy( m2[3] )
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
numType mat2<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 2));
	return m2[ index ];
}

template <class numType> HL_IMPERATIVE
numType& mat2<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 4));
	return m2[ index ];
}

//---------------------------------------------------------------------
//	mat-mat Operators
//---------------------------------------------------------------------
// prefix operators
template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator++ () {
	++xx; ++xy;
	++yx; ++yy;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator-- () {
	--xx; --xy;
	--yx; --yy;
	return *this;
}

//postfix operators
template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator++ (int) {
	return mat2<numType>(
		++xx, ++xy,
		++yx, ++yy
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator-- (int) {
	return mat2<numType>(
		--xx, --xy,
		--yx, --yy
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator + (const mat2<numType>& input) const {
	return mat2<numType>(
		xx + input.xx, xy + input.xy,
		yx + input.yx, yy + input.yy
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - (const mat2<numType>& input) const {
	return mat2<numType>(
		xx - input.xx, xy - input.xy,
		yx - input.yx, yy - input.yy
	);
}

//for operations like "mat2a = -mat2b"
template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - () const {
	return mat2<numType>(	-xx, -xy,
							-yx, -yy);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator * (const mat2<numType>& input) const {
	return mat2<numType>(
	//X
		(xx*input.xx) + (xy*input.yx),
		(xx*input.xy) + (xy*input.yy),
		
	//Y
		(yx*input.xx) + (yy*input.yx),
		(yx*input.xy) + (yy*input.yy)
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator = (const mat2<numType>& input) {
	xx = input.xx; xy = input.xy;
	yx = input.yx; yy = input.yy;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator += (const mat2<numType>& input) {
	xx += input.xx; xy += input.xy;
	yx += input.yx; yy += input.yy;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator -= (const mat2<numType>& input) {
	xx -= input.xx; xy -= input.xy;
	yx -= input.yx; yy -= input.yy;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator *= (const mat2<numType>& input) {
	numType temp[] = {
	//X
		(xx*input.xx) + (xy*input.yx),
		(xx*input.xy) + (xy*input.yy),
		
	//Y
		(yx*input.xx) + (yy*input.yx),
		(yx*input.xy) + (yy*input.yy)
	};
	xx = temp[XX]; xy = temp[XY];
	yx = temp[YX]; yy = temp[YY];
	return *this;
}

template <class numType> HL_IMPERATIVE
bool mat2<numType>::operator == (const mat2<numType>& compare) const {
	return	(
				xx == compare.xx && xy == compare.xy &&
				yx == compare.yx && yy == compare.yy
			);
}

template <class numType> HL_IMPERATIVE
bool mat2<numType>::operator != (const mat2<numType>& compare) const {
	return	(
				xx != compare.xx && xy != compare.xy &&
				yx != compare.yx && yy != compare.yy
			);
}

//---------------------------------------------------------------------
//	mat-vector Operators
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator + (const vec2<numType>& input) const {
	return mat2(
		xx + input.x, xy + input.x,
		yx + input.y, yy + input.y
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - (const vec2<numType>& input) const {
	return mat2(
		xx - input.x, xy - input.x,
		yx - input.y, yy - input.y
	);
}

template <class numType> HL_IMPERATIVE
vec2<numType> mat2<numType>::operator * (const vec2<numType>& inVec) const {
	return vec2<numType>(
		(xx * inVec.x) + (xy * inVec.y),
		(yx * inVec.x) + (yy * inVec.y)
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator = (const vec2<numType>& input) {
	xx = input.x; xy = input.x;
	yx = input.y; yy = input.y;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator += (const vec2<numType>& input) {
	xx += input.x; xy += input.x;
	yx += input.y; yy += input.y;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator -= (const vec2<numType>& input) {
	xx -= input.x; xy -= input.x;
	yx -= input.y; yy -= input.y;
	return *this;
}

//---------------------------------------------------------------------
//	mat-Scalar Operators
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator + (numType input) const {
	return mat2<numType>(
		xx + input, xy + input,
		yx + input, yy + input
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator - (numType input) const {
	return mat2<numType>(
		xx - input, xy - input,
		yx - input, yy - input
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator * (numType input) const {
	return mat2<numType>(
		xx * input, xy * input,
		yx * input, yy * input
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::operator / (numType input) const {
	return mat2<numType>(
		xx / input, xy / input,
		yx / input, yy / input
	);
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator = (numType input) {
	xx = input; xy = input;
	yx = input; yy = input;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator += (numType input) {
	xx += input; xy += input;
	yx += input; yy += input;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator -= (numType input) {
	xx -= input; xy -= input;
	yx -= input; yy -= input;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator *= (numType input) {
	xx *= input; xy *= input;
	yx *= input; yy *= input;
	return *this;
}

template <class numType> HL_IMPERATIVE
mat2<numType>& mat2<numType>::operator /= (numType input) {
	xx /= input; xy /= input;
	yx /= input; yy /= input;
	return *this;
}

//---------------------------------------------------------------------
//	Movement & Translation
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::rotmat(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	return mat2<numType>(
		ncos,	-nsin,
		nsin,	ncos
	);
}

template <class numType> HL_IMPERATIVE
void mat2<numType>::rotate(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);
	numType temp[] = {
	//X
		(xx*ncos) + (xy*nsin),
		(xy*ncos) - (xx*nsin),
		
	//Y
		(yx*ncos) + (yy*nsin),
		(yy*ncos) - (yx*nsin)
	};
	xx = temp[XX]; xy = temp[XY];
	yx = temp[YX]; yy = temp[YY];
}

//---------------------------------------------------------------------
//	Miscellaneous Functions
//---------------------------------------------------------------------
template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::getIdentity() {
	return mat2<numType>(	1, 0,
							0, 1	);
}

template <class numType> HL_IMPERATIVE
void mat2<numType>::setIdentity() {
	xx = 1; xy = 0;
	yx = 0; yy = 1;
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::getNormal() const {
	mat2<numType> output(*this);
	output.setNormal();
	return output;
}

template <class numType> HL_IMPERATIVE
void mat2<numType>::setNormal() {
	numType mag = hamLibs::math::fastInvSqrt(
		(xx * xx)+
		(xy * xy)
	);
	xx *= mag; xy *= mag;

	mag = hamLibs::math::fastInvSqrt(
		(yx * yx)+
		(yy * yy)
	);
	yx *= mag; yy *= mag;
}

template <class numType> HL_IMPERATIVE
numType mat2<numType>::getDeterminant() const {
	return numType(	(xx * yy) -
					(xy * yx)	);
}

template <class numType> HL_IMPERATIVE
mat2<numType> mat2<numType>::getTransposed() const {
	return mat2<numType>(	xx, yx,
							xy, yy	);
}

template <class numType> HL_IMPERATIVE
void mat2<numType>::setTransposed() {
	*this = mat2<numType>(	xx, yx,
							xy, yy	);
}

} //end math namespace
} //end hamlibs namespace
#endif /*__mat2_H__*/
