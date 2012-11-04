/*
 * 4d matrix class
 * recommended for use with non-integral types
 * 
 * NOTES:
 * Matrix is Row-Major
 * orientation is as follows:
 * ---------------------
 *		XX	XY	XZ	XW
 *		YX	YY	YZ	YW
 *		ZX	ZY	ZZ	ZW
 *		WX	WY	WZ	WW
 * ---------------------
*/
#ifndef __HAMLIBS_MATH_MATRIX4_H__
#define __HAMLIBS_MATH_MATRIX4_H__

namespace hamLibs {
namespace math {

//---------------------------------------------------------------------
//				Begin mat4 class
//---------------------------------------------------------------------
template <class numType>
class mat4 {
	template <typename type>
	friend std::ostream& operator << ( std::ostream&, const mat4<type>& );
	template <typename type>
	friend std::istream& operator >> ( std::istream&, mat4<type>& );
	
	public:
		union {
			struct {
				numType	xx, xy, xz, xw,
						yx, yy, yz, yw,
						zx, zy, zz, zw,
						wx, wy, wz, ww;
			};
			numType m4[16];
		};

		//enumeration for readability
		enum coords {	XX, XY, XZ, XW,
						YX, YY, YZ, YW,
						ZX, ZY, ZZ, ZW,
						WX, WY, WZ, WW };

		//hardhat construction
		mat4();
		mat4(numType input[16]);
		mat4(const mat4<numType>& input);
		mat4(	numType inXX, numType inXY, numType inXZ, numType inXW,
				numType inYX, numType inYY, numType inYZ, numType inYW,
				numType inZX, numType inZY, numType inZZ, numType inZW,
				numType inWX, numType inWY, numType inWZ, numType inWW);
		~mat4(){}

		//array operators
		numType			operator	[]		(int) const;
		numType&		operator	[]		(int);

		//matrix-matrix operators
		mat4&			operator	++		(); //prefix operators
		mat4&			operator	--		();
		mat4			operator	++		(int); //postfix operators
		mat4			operator	--		(int);
		mat4			operator	+		(const mat4<numType>& input) const;
		mat4			operator	-		(const mat4<numType>& input) const;
		mat4			operator	-		() const;
		mat4			operator	*		(const mat4<numType>& input) const;
		mat4&			operator	=		(const mat4<numType>& input);
		mat4&			operator	+=		(const mat4<numType>& input);
		mat4&			operator	-=		(const mat4<numType>& input);
		mat4&			operator	*=		(const mat4<numType>& input);
		bool			operator	==		(const mat4<numType>& input) const;
		bool			operator	!=		(const mat4<numType>& input) const;

		//matrix-vector operators
		mat4			operator	+		(const vec4<numType>&) const;
		mat4			operator	-		(const vec4<numType>&) const;
		vec4<numType>	operator	*		(const vec4<numType>&) const;
		mat4&			operator	=		(const vec4<numType>&);
		mat4&			operator	+=		(const vec4<numType>&);
		mat4&			operator	-=		(const vec4<numType>&);

		//matrix-scalar operators
		mat4			operator	+		(numType) const;
		mat4			operator	-		(numType) const;
		mat4			operator	*		(numType) const;
		mat4			operator	/		(numType) const;
		mat4&			operator	=		(numType);
		mat4&			operator	+=		(numType);
		mat4&			operator	-=		(numType);
		mat4&			operator	*=		(numType);
		mat4&			operator	/=		(numType);

		//movement & translation
		static mat4		rotMatrixX			(numType radians);
		static mat4		rotMatrixY			(numType radians);
		static mat4		rotMatrixZ			(numType radians);
		mat4			rotmatrixXYZW		(numType radians) const;
		mat4			rotmatrixXYZW		(numType radX, numType radY, numType radZ) const;
		void			rotateX				(numType radians);
		void			rotateY				(numType radians);
		void			rotateZ				(numType radians);
		void			rotateXYZ			(numType radians);
		void			rotateXYZ			(numType radX, numType radY, numType radZ);

		//miscellaneous functions
		static mat4		getIdentity			();
		void			setIdentity			();
		mat4			getNormal			() const;
		void			setNormal			();
		numType			getDeterminant		() const;
		mat4			getTransposed		() const;
		void			setTransposed		();
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
template <typename type> HL_INLINE
std::ostream& operator << ( std::ostream& sout, const mat4<type>& mat ) {
	sout
		<< mat.xx << " " << mat.xy << " " << mat.xz << " " << mat.xw << " "
		<< mat.yx << " " << mat.yy << " " << mat.yz << " " << mat.yw << " "
		<< mat.zx << " " << mat.zy << " " << mat.zz << " " << mat.zw << " "
		<< mat.wx << " " << mat.wy << " " << mat.wz << " " << mat.ww;
	return sout;
}

template <typename type> HL_INLINE
std::istream& operator >> ( std::istream& stin, mat4<type>& mat ) {
	stin
		>> mat.xx >> mat.xy >> mat.xz >> mat.xw
		>> mat.yx >> mat.yy >> mat.yz >> mat.yw
		>> mat.zx >> mat.zy >> mat.zz >> mat.zw
		>> mat.wx >> mat.wy >> mat.wz >> mat.ww;
	return stin;
}

//---------------------------------------------------------------------
//	Matrix Constructors
//---------------------------------------------------------------------
//construct all matricies as identity matricies unless stated otherwise
template <class numType> HL_INLINE
mat4<numType>::mat4() :
	xx(1),	xy(0),	xz(0),	xw(0),
	yx(0),	yy(1),	yz(0),	yw(0),
	zx(0),	zy(0),	zz(1),	zw(0),
	wx(0),	wy(0),	wz(0),	ww(1)
{}

template <class numType> HL_INLINE
mat4<numType>::mat4(numType input[16]) :
	xx(input[XX]), xy(input[XY]), xz(input[XZ]), xw(input[XW]),
	yx(input[YX]), yy(input[YY]), yz(input[YZ]), yw(input[YW]),
	zx(input[ZX]), zy(input[ZY]), zz(input[ZZ]), zw(input[ZW]),
	wx(input[WX]), wy(input[WY]), wz(input[WZ]), ww(input[WW])
{}

template <class numType> HL_INLINE
mat4<numType>::mat4(const mat4<numType>& input) :
	xx(input.xx), xy(input.xy), xz(input.xz), xw(input.xw),
	yx(input.yx), yy(input.yy), yz(input.yz), yw(input.yw),
	zx(input.zx), zy(input.zy), zz(input.zz), zw(input.zw),
	wx(input.wx), wy(input.wy), wz(input.wz), ww(input.ww)
{}

template <class numType> HL_INLINE
mat4<numType>::mat4(numType inXX, numType inXY, numType inXZ, numType inXW,
					numType inYX, numType inYY, numType inYZ, numType inYW,
					numType inZX, numType inZY, numType inZZ, numType inZW,
					numType inWX, numType inWY, numType inWZ, numType inWW) :
	xx(inXX), xy(inXY), xz(inXZ), xw(inXW),
	yx(inYX), yy(inYY), yz(inYZ), yw(inYW),
	zx(inZX), zy(inZY), zz(inZZ), zw(inZW),
	wx(inWX), wy(inWY), wz(inWZ), ww(inWW)
{}

//---------------------------------------------------------------------
//	Array Operators
//---------------------------------------------------------------------
template <class numType> HL_INLINE
numType mat4<numType>::operator[](const int index) const {
	HL_ASSERT((index >= 0) && (index < 16));
	return m4[ index ];
}

template <class numType> HL_INLINE
numType& mat4<numType>::operator[](const int index) {
	HL_ASSERT((index >= 0) && (index < 16));
	return m4[ index ];
}

//---------------------------------------------------------------------
//	Matrix-Matrix Operators
//---------------------------------------------------------------------
// prefix operators
template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator++ () {
	++xx; ++xy; ++xz; ++xw;
	++yx; ++yy; ++yz; ++yw;
	++zx; ++zy; ++zz; ++zw;
	++wx; ++wy; ++wz; ++ww;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator-- () {
	--xx; --xy; --xz; --xw;
	--yx; --yy; --yz; --yw;
	--zx; --zy; --zz; --zw;
	--wx; --wy; --wz; --ww;
	return *this;
}

//postfix operators
template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator++ (int) {
	return mat4<numType>(
		++xx, ++xy, ++xz, ++xw,
		++yx, ++yy, ++yz, ++yw,
		++zx, ++zy, ++zz, ++zw,
		++wx, ++wy, ++wz, ++ww
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator-- (int) {
	return mat4<numType>(
		--xx, --xy, --xz, --xw,
		--yx, --yy, --yz, --yw,
		--zx, --zy, --zz, --zw,
		--wx, --wy, --wz, --ww
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator + (const mat4<numType>& input) const {
	return mat4<numType>(
		xx + input.xx, xy + input.xy, xz + input.xz, xw + input.xw,
		yx + input.yx, yy + input.yy, yz + input.yz, yw + input.yw,
		zx + input.zx, zy + input.zy, zz + input.zz, zw + input.zw,
		wx + input.wx, wy + input.wy, wz + input.wz, ww + input.ww
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator - (const mat4<numType>& input) const {
	return mat4<numType>(
		xx - input.xx, xy - input.xy, xz - input.xz, xw - input.xw,
		yx - input.yx, yy - input.yy, yz - input.yz, yw - input.yw,
		zx - input.zx, zy - input.zy, zz - input.zz, zw - input.zw,
		wx - input.wx, wy - input.wy, wz - input.wz, ww - input.ww
	);
}

//for operations like "matrix4a = -matrix4b"
template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator - () const {
	return mat4<numType>(	-xx, -xy, -xz, -xw,
							-yx, -yy, -yz, -yw,
							-zx, -zy, -zz, -zw,
							-wx, -wy, -wz, -ww);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator * (const mat4<numType>& input) const {
	return mat4<numType>(
	//X
		(xx*input.xx) + (xy*input.yx) + (xz*input.zx) + (xw*input.wx),
		(xx*input.xy) + (xy*input.yy) + (xz*input.zy) + (xw*input.wy),
		(xx*input.xz) + (xy*input.yz) + (xz*input.zz) + (xw*input.wz),
		(xx*input.xw) + (xy*input.yw) + (xz*input.zw) + (xw*input.ww),
		
	//Y
		(yx*input.xx) + (yy*input.yx) + (yz*input.zx) + (yw*input.wx),
		(yx*input.xy) + (yy*input.yy) + (yz*input.zy) + (yw*input.wy),
		(yx*input.xz) + (yy*input.yz) + (yz*input.zz) + (yw*input.wz),
		(yx*input.xw) + (yy*input.yw) + (yz*input.zw) + (yw*input.ww),
		
	//Z
		(zx*input.xx) + (zy*input.yx) + (zz*input.zx) + (zw*input.wx),
		(zx*input.xy) + (zy*input.yy) + (zz*input.zy) + (zw*input.wy),
		(zx*input.xz) + (zy*input.yz) + (zz*input.zz) + (zw*input.wz),
		(zx*input.xw) + (zy*input.yw) + (zz*input.zw) + (zw*input.ww),
		
	//W
		(wx*input.xx) + (wy*input.yx) + (wz*input.zx) + (ww*input.wx),
		(wx*input.xy) + (wy*input.yy) + (wz*input.zy) + (ww*input.wy),
		(wx*input.xz) + (wy*input.yz) + (wz*input.zz) + (ww*input.wz),
		(wx*input.xw) + (wy*input.yw) + (wz*input.zw) + (ww*input.ww)
	);
	//if this is wrong, fuck you
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator = (const mat4<numType>& input) {
	xx = input.xx; xy = input.xy; xz = input.xz; xw = input.xw;
	yx = input.yx; yy = input.yy; yz = input.yz; yw = input.yw;
	zx = input.zx; zy = input.zy; zz = input.zz; zw = input.zw;
	wx = input.wx; wy = input.wy; wz = input.wz; ww = input.ww;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator += (const mat4<numType>& input) {
	xx += input.xx; xy += input.xy; xz += input.xz; xw += input.xw;
	yx += input.yx; yy += input.yy; yz += input.yz; yw += input.yw;
	zx += input.zx; zy += input.zy; zz += input.zz; zw += input.zw;
	wx += input.wx; wy += input.wy; wz += input.wz; ww += input.ww;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator -= (const mat4<numType>& input) {
	xx -= input.xx; xy -= input.xy; xz -= input.xz; xw -= input.xw;
	yx -= input.yx; yy -= input.yy; yz -= input.yz; yw -= input.yw;
	zx -= input.zx; zy -= input.zy; zz -= input.zz; zw -= input.zw;
	wx -= input.wx; wy -= input.wy; wz -= input.wz; ww -= input.ww;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator *= (const mat4<numType>& input) {
	numType temp[] = {
	//X
		(xx*input.xx) + (xy*input.yx) + (xz*input.zx) + (xw*input.wx),
		(xx*input.xy) + (xy*input.yy) + (xz*input.zy) + (xw*input.wy),
		(xx*input.xz) + (xy*input.yz) + (xz*input.zz) + (xw*input.wz),
		(xx*input.xw) + (xy*input.yw) + (xz*input.zw) + (xw*input.ww),
		
	//Y
		(yx*input.xx) + (yy*input.yx) + (yz*input.zx) + (yw*input.wx),
		(yx*input.xy) + (yy*input.yy) + (yz*input.zy) + (yw*input.wy),
		(yx*input.xz) + (yy*input.yz) + (yz*input.zz) + (yw*input.wz),
		(yx*input.xw) + (yy*input.yw) + (yz*input.zw) + (yw*input.ww),
		
	//Z
		(zx*input.xx) + (zy*input.yx) + (zz*input.zx) + (zw*input.wx),
		(zx*input.xy) + (zy*input.yy) + (zz*input.zy) + (zw*input.wy),
		(zx*input.xz) + (zy*input.yz) + (zz*input.zz) + (zw*input.wz),
		(zx*input.xw) + (zy*input.yw) + (zz*input.zw) + (zw*input.ww),
		
	//W
		(wx*input.xx) + (wy*input.yx) + (wz*input.zx) + (ww*input.wx),
		(wx*input.xy) + (wy*input.yy) + (wz*input.zy) + (ww*input.wy),
		(wx*input.xz) + (wy*input.yz) + (wz*input.zz) + (ww*input.wz),
		(wx*input.xw) + (wy*input.yw) + (wz*input.zw) + (ww*input.ww)
	};
	xx = temp[XX]; xy = temp[XY]; xz = temp[XZ]; xw = temp[XW];
	yx = temp[YX]; yy = temp[YY]; yz = temp[YZ]; yw = temp[YW];
	zx = temp[ZX]; zy = temp[ZY]; zz = temp[ZZ]; zw = temp[ZW];
	wx = temp[WX]; wy = temp[WY]; wz = temp[WZ]; ww = temp[WW];
	return *this;
}

template <class numType> HL_INLINE
bool mat4<numType>::operator == (const mat4<numType>& compare) const {
	return	(
				xx == compare.xx && xy == compare.xy && xz == compare.xz && xw == compare.xw &&
				yx == compare.yx && yy == compare.yy && yz == compare.yz && yw == compare.yw &&
				zx == compare.zx && zy == compare.zy && zz == compare.zz && zw == compare.zw &&
				wx == compare.wx && wy == compare.wy && wz == compare.wz && ww == compare.ww
			);
}

template <class numType> HL_INLINE
bool mat4<numType>::operator != (const mat4<numType>& compare) const {
	return	(
				xx != compare.xx && xy != compare.xy && xz != compare.xz && xw != compare.xw &&
				yx != compare.yx && yy != compare.yy && yz != compare.yz && yw != compare.yw &&
				zx != compare.zx && zy != compare.zy && zz != compare.zz && zw != compare.zw &&
				wx != compare.wx && wy != compare.wy && wz != compare.wz && ww != compare.ww
			);
}

//---------------------------------------------------------------------
//	Matrix-Vector Operators
//---------------------------------------------------------------------
template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator + (const vec4<numType>& input) const {
	return mat4(
		xx + input.x, xy + input.x, xz + input.x, xw + input.x,
		yx + input.y, yy + input.y, yz + input.y, yw + input.y,
		zx + input.z, zy + input.z, zz + input.z, zw + input.z,
		wx + input.w, wy + input.w, wz + input.w, ww + input.w
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator - (const vec4<numType>& input) const {
	return mat4(
		xx - input.x, xy - input.x, xz - input.x, xw - input.x,
		yx - input.y, yy - input.y, yz - input.y, yw - input.y,
		zx - input.z, zy - input.z, zz - input.z, zw - input.z,
		wx - input.w, wy - input.w, wz - input.w, ww - input.w
	);
}

template <class numType> HL_INLINE
vec4<numType> mat4<numType>::operator * (const vec4<numType>& inVect) const {
	return vec4<numType>(
		(xx * inVect.x) + (xy * inVect.y) + (xz * inVect.z) + (xw * inVect.w),
		(yx * inVect.x) + (yy * inVect.y) + (yz * inVect.z) + (yw * inVect.w),
		(zx * inVect.x) + (zy * inVect.y) + (zz * inVect.z) + (zw * inVect.w),
		(wx * inVect.x) + (wy * inVect.y) + (wz * inVect.z) + (ww * inVect.w)
	);
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator = (const vec4<numType>& input) {
	xx = input.x; xy = input.x; xz = input.x; xw = input.x;
	yx = input.y; yy = input.y; yz = input.y; yw = input.y;
	zx = input.z; zy = input.z; zz = input.z; zw = input.z;
	wx = input.w; wy = input.w; wz = input.w; ww = input.w;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator += (const vec4<numType>& input) {
	xx += input.x; xy += input.x; xz += input.x; xw += input.x;
	yx += input.y; yy += input.y; yz += input.y; yw += input.y;
	zx += input.z; zy += input.z; zz += input.z; zw += input.z;
	wx += input.w; wy += input.w; wz += input.w; ww += input.w;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator -= (const vec4<numType>& input) {
	xx -= input.x; xy -= input.x; xz -= input.x; xw -= input.x;
	yx -= input.y; yy -= input.y; yz -= input.y; yw -= input.y;
	zx -= input.z; zy -= input.z; zz -= input.z; zw -= input.z;
	wx -= input.w; wy -= input.w; wz -= input.w; ww -= input.w;
	return *this;
}

//---------------------------------------------------------------------
//	Matrix-Scalar Operators
//---------------------------------------------------------------------
template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator + (numType input) const {
	return mat4<numType>(
		xx + input, xy + input, xz + input, xw + input,
		yx + input, yy + input, yz + input, yw + input,
		zx + input, zy + input, zz + input, zw + input,
		wx + input, wy + input, wz + input, ww + input
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator - (numType input) const {
	return mat4<numType>(
		xx - input, xy - input, xz - input, xw - input,
		yx - input, yy - input, yz - input, yw - input,
		zx - input, zy - input, zz - input, zw - input,
		wx - input, wy - input, wz - input, ww - input
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator * (numType input) const {
	return mat4<numType>(
		xx * input, xy * input, xz * input, xw * input,
		yx * input, yy * input, yz * input, yw * input,
		zx * input, zy * input, zz * input, zw * input,
		wx * input, wy * input, wz * input, ww * input
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::operator / (numType input) const {
	return mat4<numType>(
		xx / input, xy / input, xz / input, xw / input,
		yx / input, yy / input, yz / input, yw / input,
		zx / input, zy / input, zz / input, zw / input,
		wx / input, wy / input, wz / input, ww / input
	);
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator = (numType input) {
	xx = input; xy = input; xz = input; xw = input;
	yx = input; yy = input; yz = input; yw = input;
	zx = input; zy = input; zz = input; zw = input;
	wx = input; wy = input; wz = input; ww = input;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator += (numType input) {
	xx += input; xy += input; xz += input; xw += input;
	yx += input; yy += input; yz += input; yw += input;
	zx += input; zy += input; zz += input; zw += input;
	wx += input; wy += input; wz += input; ww += input;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator -= (numType input) {
	xx -= input; xy -= input; xz -= input; xw -= input;
	yx -= input; yy -= input; yz -= input; yw -= input;
	zx -= input; zy -= input; zz -= input; zw -= input;
	wx -= input; wy -= input; wz -= input; ww -= input;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator *= (numType input) {
	xx *= input; xy *= input; xz *= input; xw *= input;
	yx *= input; yy *= input; yz *= input; yw *= input;
	zx *= input; zy *= input; zz *= input; zw *= input;
	wx *= input; wy *= input; wz *= input; ww *= input;
	return *this;
}

template <class numType> HL_INLINE
mat4<numType>& mat4<numType>::operator /= (numType input) {
	xx /= input; xy /= input; xz /= input; xw /= input;
	yx /= input; yy /= input; yz /= input; yw /= input;
	zx /= input; zy /= input; zz /= input; zw /= input;
	wx /= input; wy /= input; wz /= input; ww /= input;
	return *this;
}

//---------------------------------------------------------------------
//	Movement & Translation
//---------------------------------------------------------------------
//basic Identity Matrix rotations.
//these van be used independently of class objects by calling:
//	"matrix<numberType>::rotmatrixXYZW(radians)"
template <class numType> HL_INLINE
mat4<numType> mat4<numType>::rotMatrixX(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	return mat4<numType>(
		1,	0,		0,		0,
		0,	ncos,	-nsin,	0,
		0,	nsin,	ncos,	0,
		0,	0,		0,		1
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::rotMatrixY(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	return mat4<numType>(
		ncos,	0,	nsin,	0,
		0,		1,	0,		0,
		-nsin,	0,	ncos,	0,
		0,		0,	0,		1
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::rotMatrixZ(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	return mat4<numType>(
		ncos,	-nsin,	0,	0,
		nsin,	ncos,	0,	0,
		0,		0,		1,	0,
		0,		0,		0,	1
	);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::rotmatrixXYZW(numType radians) const {
	return rotMatrixX(radians) * rotMatrixY(radians) * rotMatrixZ(radians);
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::rotmatrixXYZW(numType radX, numType radY, numType radZ) const {
	return rotMatrixX(radX) * rotMatrixY(radY) * rotMatrixZ(radZ);
}

//these functions rotate whatever matrix object that is being called
//added only for extra functionality, but not recommended for regular
//use. Constant rotation of non-identity matricies will result in a
//loss of precision with each rotation (I.E. your matrix will shrink)
template <class numType> HL_INLINE
void mat4<numType>::rotateX(numType radians) {
	numType ncos = cos(radians);
	numType nsin = sin(radians);

	*this = mat4<numType>(
		xx, (xy*ncos) + (xz*nsin), (xz*ncos) - (xy*nsin), xw,
		yx, (yy*ncos) + (yz*nsin), (yz*ncos) - (yy*nsin), yw,
		zx, (zy*ncos) + (zz*nsin), (zz*ncos) - (zy*nsin), zw,
		wx, (wy*ncos) + (wz*nsin), (wz*ncos) - (ww*nsin), ww
	);
}

template <class numType> HL_INLINE
void mat4<numType>::rotateY(numType radians) {
	numType ncos = cos(radians);
	numType nsin = sin(radians);

	*this = mat4<numType>(
		(xx*ncos) - (xz*nsin), xy, (xx*nsin) + (xz*ncos), xw,
		(yx*ncos) - (yz*nsin), yy, (yx*nsin) + (yz*ncos), yw,
		(zx*ncos) - (zz*nsin), zy, (zx*nsin) + (zz*ncos), zw,
		(wx*ncos) - (wz*nsin), wy, (wx*nsin) + (wz*ncos), ww
	);
}

template <class numType> HL_INLINE
void mat4<numType>::rotateZ(numType radians) {
	numType nsin = (numType)sin(radians);
	numType ncos = (numType)cos(radians);

	*this = mat4<numType>(
		(xx*ncos) + (xy*nsin), (xy*ncos) - (xx*nsin), xz, xw,
		(yx*ncos) + (yy*nsin), (yy*ncos) - (yx*nsin), yz, yw,
		(zx*ncos) + (zy*nsin), (zy*ncos) - (zx*nsin), zz, zw,
		(wx*ncos) + (wy*nsin), (wy*ncos) - (wx*nsin), wz, zw
	);
}

template <class numType> HL_INLINE
void mat4<numType>::rotateXYZ(numType radians) {
	rotateX(radians); rotateY(radians); rotateZ(radians);
}

template <class numType> HL_INLINE
void mat4<numType>::rotateXYZ(numType radX, numType radY, numType radZ) {
	rotateX(radX); rotateY(radY); rotateZ(radZ);
}

//---------------------------------------------------------------------
//	Miscellaneous Functions
//---------------------------------------------------------------------
template <class numType> HL_INLINE
mat4<numType> mat4<numType>::getIdentity() {
	return mat4<numType>(	1,	0,	0,	0,
							0,	1,	0,	0,
							0,	0,	1,	0,
							0,	0,	0,	1	);
}

template <class numType> HL_INLINE
void mat4<numType>::setIdentity() {
	xx = 1; xy = 0; xz = 0; xw = 0;
	yx = 0; yy = 1; yz = 0; yw = 0;
	zx = 0; zy = 0; zz = 1; zw = 0;
	wx = 0; wy = 0; wz = 0; ww = 1;
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::getNormal() const {
	mat4<numType> output(*this);
	output.setNormal();
	return output;
}

template <class numType> HL_INLINE
void mat4<numType>::setNormal() {
	numType mag = hamLibs::math::fastInvSqrt(
		(xx * xx)+
		(xy * xy)+
		(xz * xz)+
		(xw * xw)
	);
	xx *= mag; xy *= mag; xz *= mag; xw *= mag;

	mag = hamLibs::math::fastInvSqrt(
		(yx * yx)+
		(yy * yy)+
		(yz * yz)+
		(yw * yw)
	);
	yx *= mag; yy *= mag; yz *= mag; yw *= mag;

	mag = hamLibs::math::fastInvSqrt(
		(zx * zx)+
		(zy * zy)+
		(zz * zz)+
		(zw * zw)
	);
	zx *= mag; zy *= mag; zz *= mag; zw *= mag;

	mag = hamLibs::math::fastInvSqrt(
		(wx * wx)+
		(wy * wy)+
		(wz * wz)+
		(ww * ww)
	);
	wx *= mag; wy *= mag; wz *= mag; ww *= mag;
}

template <class numType> HL_INLINE
numType mat4<numType>::getDeterminant() const {
	return numType(
		(xw * yz * zy * wx) - (xz * yw * zy * wx) - (xw * yy * zz * wx) + (xy * yw * zz * wx) +
		(xz * yy * zw * wx) - (xy * yz * zw * wx) - (xw * yz * zx * wy) + (xz * yw * zx * wy) +
		(xw * yx * zz * wy) - (xx * yw * zz * wy) - (xz * yx * zw * wy) + (xx * yz * zw * wy) +
		(xw * yy * zx * wz) - (xy * yw * zx * wz) - (xw * yx * zy * wz) + (xx * yw * zy * wz) +
		(xy * yx * zw * wz) - (xx * yy * zw * wz) - (xz * yy * zx * ww) + (xy * yz * zx * ww) +
		(xz * yx * zy * ww) - (xx * yz * zy * ww) - (xy * yx * zz * ww) + (xx * yy * zz * ww) );
	//umm... wow
}

template <class numType> HL_INLINE
mat4<numType> mat4<numType>::getTransposed() const {
	return mat4<numType>(	xx, yx, zx, wx,
							xy, yy, zy, wy,
							xz, yz, zz, wz,
							xw, yw, zw, ww	);
}

template <class numType> HL_INLINE
void mat4<numType>::setTransposed() {
	*this = mat4<numType>(	xx, yx, zx, wx,
							xy, yy, zy, wy,
							xz, yz, zz, wz,
							xw, yw, zw, ww	);
}

} //end math namespace
} //end hamlibs namespace
#endif /*__MATRIX4_H__*/
