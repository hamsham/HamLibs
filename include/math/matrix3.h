/*
 * 3d matrix class
 * recommended for use with non-integral types
 * 
 * NOTES:
 * Matrix is Row-Major
 * orientation is as follows:
 * ---------------------
 *		XX	XY	XZ
 *		YX	YY	YZ
 *		ZX	ZY	ZZ
 * ---------------------
*/

#ifndef __HAMLIBS_MATH_MATRIX3_H__
#define __HAMLIBS_MATH_MATRIX3_H__

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat3 class
//---------------------------------------------------------------------
template <class numType>
class mat3 {
	public:
		union {
			struct {
				numType	xx, xy, xz,
						yx, yy, yz,
						zx, zy, zz;
			};
			numType m3[9];
		};
		
		//enumeration for readability
		enum coords {	XX, XY, XZ,
						YX, YY, YZ,
						ZX, ZY, ZZ	};

		//hardhat construction
		mat3();
		mat3(numType input[9]);
		mat3(const mat3<numType>& input);
		mat3(	numType inXX, numType inXY, numType inXZ,
				numType inYX, numType inYY, numType inYZ,
				numType inZX, numType inZY, numType inZZ	);
		~mat3(){}

		//array operators
		numType			operator	[]		(int) const;
		numType&		operator	[]		(int);

		//matrix-matrix operators
		mat3&			operator	++		(); //prefix operators
		mat3&			operator	--		();
		mat3			operator	++		(int); //postfix operators
		mat3			operator	--		(int);
		mat3			operator	+		(const mat3<numType>& input) const;
		mat3			operator	-		(const mat3<numType>& input) const;
		mat3			operator	-		() const;
		mat3			operator	*		(const mat3<numType>& input) const;
		mat3&			operator	=		(const mat3<numType>& input);
		mat3&			operator	+=		(const mat3<numType>& input);
		mat3&			operator	-=		(const mat3<numType>& input);
		mat3&			operator	*=		(const mat3<numType>& input);
		bool			operator	==		(const mat3<numType>& input);
		bool			operator	!=		(const mat3<numType>& input);

		//matrix-vector operators
		mat3			operator	+		(const vec3<numType>&) const;
		mat3			operator	-		(const vec3<numType>&) const;
		vec3<numType>	operator	*		(const vec3<numType>&) const;
		mat3&			operator	=		(const vec3<numType>&);
		mat3&			operator	+=		(const vec3<numType>&);
		mat3&			operator	-=		(const vec3<numType>&);

		//matrix-scalar operators
		mat3			operator	+		(numType) const;
		mat3			operator	-		(numType) const;
		mat3			operator	*		(numType) const;
		mat3			operator	/		(numType) const;
		mat3&			operator	=		(numType);
		mat3&			operator	+=		(numType);
		mat3&			operator	-=		(numType);
		mat3&			operator	*=		(numType);
		mat3&			operator	/=		(numType);

		//movement & translation
		static mat3		rotMatrixX			(numType radians);
		static mat3		rotMatrixY			(numType radians);
		static mat3		rotMatrixZ			(numType radians);
		mat3			rotMatrixXYZ		(numType radians) const;
		mat3			rotMatrixXYZ		(numType radX, numType radY, numType radZ) const;
		void			rotateX				(numType radians);
		void			rotateY				(numType radians);
		void			rotateZ				(numType radians);
		void			rotateXYZ			(numType radians);
		void			rotateXYZ			(numType radX, numType radY, numType radZ);

		//miscellaneous functions
		static mat3		getIdentity			();
		void			setIdentity			();
		mat3			getNormal			() const;
		void			setNormal			();
		numType			getDeterminant		() const;
		mat3			getTransposed		() const;
		void			setTransposed		();
};

//---------------------------------------------------------------------
//	Matrix Constructors
//---------------------------------------------------------------------
//construct all matricies as identity matricies unless stated otherwise
//construction is done using initializer lists
template <class numType> HL_INLINE
mat3<numType>::mat3() :
	xx(1), xy(0), xz(0),
	yx(0), yy(1), yz(0),
	zx(0), zy(0), zz(1)
{}

template <class numType> HL_INLINE
mat3<numType>::mat3(numType input[9]) :
	xx(input[XX]), xy(input[XY]), xz(input[XZ]),
	yx(input[YX]), yy(input[YY]), yz(input[YZ]),
	zx(input[ZX]), zy(input[ZY]), zz(input[ZZ])
{}

template <class numType> HL_INLINE
mat3<numType>::mat3(const mat3<numType>& input) :
	xx(input.xx), xy(input.xy), xz(input.xz),
	yx(input.yx), yy(input.yy), yz(input.yz),
	zx(input.zx), zy(input.zy), zz(input.zz)
{}

template <class numType> HL_INLINE
mat3<numType>::mat3(	numType	inXX, numType inXY, numType inXZ,
						numType inYX, numType inYY, numType inYZ,
						numType inZX, numType inZY, numType inZZ) :

	xx(inXX), xy(inXY), xz(inXZ),
	yx(inYX), yy(inYY), yz(inYZ),
	zx(inZX), zy(inZY), zz(inZZ)
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <class numType> HL_INLINE
numType mat3<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 9));
	return m3[ index ];
}

template <class numType> HL_INLINE
numType& mat3<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 9));
	return m3[ index ];
}

//---------------------------------------------------------------------
//	Matrix-Matrix Operators
//---------------------------------------------------------------------
// prefix operators
template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator++ () {
	++xx; ++xy; ++xz;
	++yx; ++yy; ++yz;
	++zx; ++zy; ++zz;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator-- () {
	--xx; --xy; --xz;
	--yx; --yy; --yz;
	--zx; --zy; --zz;
	return *this;
}

//postfix operators
template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator++ (int) {
	return mat3<numType>(
		++xx, ++xy, ++xz,
		++yx, ++yy, ++yz,
		++zx, ++zy, ++zz
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator-- (int) {
	return mat3<numType>(
		--xx, --xy, --xz,
		--yx, --yy, --yz,
		--zx, --zy, --zz
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator + (const mat3<numType>& input) const {
	return mat3<numType>(
		xx + input.xx, xy + input.xy, xz + input.xz,
		yx + input.yx, yy + input.yy, yz + input.yz,
		zx + input.zx, zy + input.zy, zz + input.zz
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator - (const mat3<numType>& input) const {
	return mat3<numType>(
		xx - input.xx, xy - input.xy, xz - input.xz,
		yx - input.yx, yy - input.yy, yz - input.yz,
		zx - input.zx, zy - input.zy, zz - input.zz
	);
}

//for operations like "matrix3a = -matrix3b"
template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator - () const {
	return mat3<numType>(	-xx, -xy, -xz,
							-yx, -yy, -yz,
							-zx, -zy, -zz);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator * (const mat3<numType>& input) const {
	return mat3<numType>(
	//X
		(xx*input.xx) + (xy*input.yx) + (xz*input.zx),
		(xx*input.xy) + (xy*input.yy) + (xz*input.zy),
		(xx*input.xz) + (xy*input.yz) + (xz*input.zz),
		
	//Y
		(yx*input.xx) + (yy*input.yx) + (yz*input.zx),
		(yx*input.xy) + (yy*input.yy) + (yz*input.zy),
		(yx*input.xz) + (yy*input.yz) + (yz*input.zz),
		
	//Z
		(zx*input.xx) + (zy*input.yx) + (zz*input.zx),
		(zx*input.xy) + (zy*input.yy) + (zz*input.zy),
		(zx*input.xz) + (zy*input.yz) + (zz*input.zz)
	);
	//if this is wrong, fuck you
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator = (const mat3<numType>& input) {
	xx = input.xx; xy = input.xy; xz = input.xz;
	yx = input.yx; yy = input.yy; yz = input.yz;
	zx = input.zx; zy = input.zy; zz = input.zz;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator += (const mat3<numType>& input) {
	xx += input.xx; xy += input.xy; xz += input.xz;
	yx += input.yx; yy += input.yy; yz += input.yz;
	zx += input.zx; zy += input.zy; zz += input.zz;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator -= (const mat3<numType>& input) {
	xx -= input.xx; xy -= input.xy; xz -= input.xz;
	yx -= input.yx; yy -= input.yy; yz -= input.yz;
	zx -= input.zx; zy -= input.zy; zz -= input.zz;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator *= (const mat3<numType>& input) {
	numType temp[] = {
	//X
		(xx*input.xx) + (xy*input.yx) + (xz*input.zx),
		(xx*input.xy) + (xy*input.yy) + (xz*input.zy),
		(xx*input.xz) + (xy*input.yz) + (xz*input.zz),
		
	//Y
		(yx*input.xx) + (yy*input.yx) + (yz*input.zx),
		(yx*input.xy) + (yy*input.yy) + (yz*input.zy),
		(yx*input.xz) + (yy*input.yz) + (yz*input.zz),
		
	//Z
		(zx*input.xx) + (zy*input.yx) + (zz*input.zx),
		(zx*input.xy) + (zy*input.yy) + (zz*input.zy),
		(zx*input.xz) + (zy*input.yz) + (zz*input.zz)
	};
	xx = temp[XX]; xy = temp[XY]; xz = temp[XZ];
	yx = temp[YX]; yy = temp[YY]; yz = temp[YZ];
	zx = temp[ZX]; zy = temp[ZY]; zz = temp[ZZ];
	return *this;
}

template <class numType> HL_INLINE
bool mat3<numType>::operator == (const mat3<numType>& compare) {
	return	(
				xx == compare.xx && xy == compare.xy && xz == compare.xz &&
				yx == compare.yx && yy == compare.yy && yz == compare.yz &&
				zx == compare.zx && zy == compare.zy && zz == compare.zz
			);
}

template <class numType> HL_INLINE
bool mat3<numType>::operator != (const mat3<numType>& compare) {
	return	(
				xx != compare.xx && xy != compare.xy && xz != compare.xz &&
				yx != compare.yx && yy != compare.yy && yz != compare.yz &&
				zx != compare.zx && zy != compare.zy && zz != compare.zz
			);
}

//---------------------------------------------------------------------
//	Matrix-Vector Operators
//---------------------------------------------------------------------
template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator + (const vec3<numType>& input) const {
	return mat3(
		xx + input.x, xy + input.x, xz + input.x,
		yx + input.y, yy + input.y, yz + input.y,
		zx + input.z, zy + input.z, zz + input.z
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator - (const vec3<numType>& input) const {
	return mat3(
		xx - input.x, xy - input.x, xz - input.x,
		yx - input.y, yy - input.y, yz - input.y,
		zx - input.z, zy - input.z, zz - input.z
	);
}

template <class numType> HL_INLINE
vec3<numType> mat3<numType>::operator * (const vec3<numType>& inVect) const {
	return vec3<numType>(
		(xx * inVect.x) + (xy * inVect.y) + (xz * inVect.z),
		(yx * inVect.x) + (yy * inVect.y) + (yz * inVect.z),
		(zx * inVect.x) + (zy * inVect.y) + (zz * inVect.z)
	);
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator = (const vec3<numType>& input) {
	xx = input.x; xy = input.x; xz = input.x;
	yx = input.y; yy = input.y; yz = input.y;
	zx = input.z; zy = input.z; zz = input.z;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator += (const vec3<numType>& input) {
	xx += input.x; xy += input.x; xz += input.x;
	yx += input.y; yy += input.y; yz += input.y;
	zx += input.z; zy += input.z; zz += input.z;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator -= (const vec3<numType>& input) {
	xx -= input.x; xy -= input.x; xz -= input.x;
	yx -= input.y; yy -= input.y; yz -= input.y;
	zx -= input.z; zy -= input.z; zz -= input.z;
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Scalar Operators
//---------------------------------------------------------------------
template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator + (numType input) const {
	return mat3<numType>(
		xx + input, xy + input, xz + input,
		yx + input, yy + input, yz + input,
		zx + input, zy + input, zz + input
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator - (numType input) const {
	return mat3<numType>(
		xx - input, xy - input, xz - input,
		yx - input, yy - input, yz - input,
		zx - input, zy - input, zz - input
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator * (numType input) const {
	return mat3<numType>(
		xx * input, xy * input, xz * input,
		yx * input, yy * input, yz * input,
		zx * input, zy * input, zz * input
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::operator / (numType input) const {
	return mat3<numType>(
		xx / input, xy / input, xz / input,
		yx / input, yy / input, yz / input,
		zx / input, zy / input, zz / input
	);
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator = (numType input) {
	xx = input; xy = input; xz = input;
	yx = input; yy = input; yz = input;
	zx = input; zy = input; zz = input;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator += (numType input) {
	xx += input; xy += input; xz += input;
	yx += input; yy += input; yz += input;
	zx += input; zy += input; zz += input;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator -= (numType input) {
	xx -= input; xy -= input; xz -= input;
	yx -= input; yy -= input; yz -= input;
	zx -= input; zy -= input; zz -= input;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator *= (numType input) {
	xx *= input; xy *= input; xz *= input;
	yx *= input; yy *= input; yz *= input;
	zx *= input; zy *= input; zz *= input;
	return *this;
}

template <class numType> HL_INLINE
mat3<numType>& mat3<numType>::operator /= (numType input) {
	xx /= input; xy /= input; xz /= input;
	yx /= input; yy /= input; yz /= input;
	zx /= input; zy /= input; zz /= input;
	return *this;
}

//---------------------------------------------------------------------
//	Movement & Translation
//---------------------------------------------------------------------
//basic Identity Matrix rotations.
//these van be used independently of class objects by calling:
//	"matrix<numberType>::rotMatrixXYZ(radians)"
template <class numType> HL_INLINE
mat3<numType> mat3<numType>::rotMatrixX(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	return mat3<numType>(
		1,	0,		0,
		0,	ncos,	-nsin,
		0,	nsin,	ncos
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::rotMatrixY(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	return mat3<numType>(
		ncos,	0,	nsin,
		0,		1,	0,
		-nsin,	0,	ncos
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::rotMatrixZ(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	return mat3<numType>(
		ncos,	-nsin,	0,
		nsin,	ncos,	0,
		0,		0,		1
	);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::rotMatrixXYZ(numType radians) const {
	return rotMatrixX(radians) * rotMatrixY(radians) * rotMatrixZ(radians);
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::rotMatrixXYZ(numType radX, numType radY, numType radZ) const {
	return rotMatrixX(radX) * rotMatrixY(radY) * rotMatrixZ(radZ);
}

//these functions rotate whatever matrix object that is being called
//added only for extra functionality, but not recommended for regular
//use. Constant rotation of non-identity matricies will result in a
//loss of precision with each rotation (I.E. your matrix will shrink)
template <class numType> HL_INLINE
void mat3<numType>::rotateX(numType radians) {
	numType ncos = cos(radians);
	numType nsin = sin(radians);

	*this = mat3<numType>(
		xx, (xy*ncos) + (xz*nsin), (xz*ncos) - (xy*nsin),
		yx, (yy*ncos) + (yz*nsin), (yz*ncos) - (yy*nsin),
		zx, (zy*ncos) + (zz*nsin), (zz*ncos) - (zy*nsin)
	);
}

template <class numType> HL_INLINE
void mat3<numType>::rotateY(numType radians) {
	numType ncos = cos(radians);
	numType nsin = sin(radians);

	*this = mat3<numType>(
		(xx*ncos) - (xz*nsin), xy, (xx*nsin) + (xz*ncos),
		(yx*ncos) - (yz*nsin), yy, (yx*nsin) + (yz*ncos),
		(zx*ncos) - (zz*nsin), zy, (zx*nsin) + (zz*ncos)
	);
}

template <class numType> HL_INLINE
void mat3<numType>::rotateZ(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	*this = mat3<numType>(
		(xx*ncos) + (xy*nsin), (xy*ncos) - (xx*nsin), xz,
		(yx*ncos) + (yy*nsin), (yy*ncos) - (yx*nsin), yz,
		(zx*ncos) + (zy*nsin), (zy*ncos) - (zx*nsin), zz
	);
}

template <class numType> HL_INLINE
void mat3<numType>::rotateXYZ(numType radians) {
	rotateX(radians);
	rotateY(radians);
	rotateZ(radians);
}

template <class numType> HL_INLINE
void mat3<numType>::rotateXYZ(numType radX, numType radY, numType radZ) {
	rotateX(radX);
	rotateY(radY);
	rotateZ(radZ);
}

//---------------------------------------------------------------------
//	Miscellaneous Functions
//---------------------------------------------------------------------
template <class numType> HL_INLINE
mat3<numType> mat3<numType>::getIdentity() {
	return mat3<numType>(	1, 0, 0,
							0, 1, 0,
							0, 0, 1	);
}

template <class numType> HL_INLINE
void mat3<numType>::setIdentity() {
	xx = 1; xy = 0; xz = 0;
	yx = 0; yy = 1; yz = 0;
	zx = 0; zy = 0; zz = 1;
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::getNormal() const {
	mat3<numType> output(m3);
	output.setNormal();
	return output;
}

template <class numType> HL_INLINE
void mat3<numType>::setNormal() {
	numType mag = hamLibs::math::fastInvSqrt(
		(xx * xx)+
		(xy * xy)+
		(xz * xz)
	);
	xx *= mag; xy *= mag; xz *= mag;

	mag = hamLibs::math::fastInvSqrt(
		(yx * yx)+
		(yy * yy)+
		(yz * yz)
	);
	yx *= mag; yy *= mag; yz *= mag;

	mag = hamLibs::math::fastInvSqrt(
		(zx * zx)+
		(zy * zy)+
		(zz * zz)
	);
	zx *= mag; zy *= mag; zz *= mag;
}

template <class numType> HL_INLINE
numType mat3<numType>::getDeterminant() const {
	return numType(		(xx * yy * zz) +
						(xy * yz * zx) +
						(xz * yx * zy) -
						(xz * yy * zx) -
						(xy * yx * zz) -
						(xx * yz * zy) );
}

template <class numType> HL_INLINE
mat3<numType> mat3<numType>::getTransposed() const {
	return mat3<numType>(	xx, yx, zx,
							xy, yy, zy,
							xz, yz, zz	);
}

template <class numType> HL_INLINE
void mat3<numType>::setTransposed() {
	*this = mat3<numType>(	xx, yx, zx,
							xy, yy, zy,
							xz, yz, zz	);
}

} //end math namespace
} //end hamlibs namespace
#endif /*__MATRIX3_H__*/
