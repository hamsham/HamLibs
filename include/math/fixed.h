/* 
 * File:   fixed.h
 * Author: hammy
 *
 * Created on June 14, 2012, 6:34 PM
 */

#ifndef __HL_FIXED_MATH_H__
#define	__HL_FIXED_MATH_H__
namespace hamLibs {
namespace math {
	
class fixed {
	friend std::ostream& operator << ( std::ostream&, const fixed& );
	friend std::istream& operator >> ( std::istream&, fixed& );
	
	public:
		al_fixed num;
		
		fixed		();
		fixed		(const fixed& x);
		fixed		(const int& x);
		fixed		(const double& x);
		~fixed		();
		
		//comparisons
		bool			operator	==		(const fixed& x) const;
		bool			operator	!=		(const fixed& x) const;
		bool			operator	<		(const fixed& x) const;
		bool			operator	>		(const fixed& x) const;
		bool			operator	<=		(const fixed& x) const;
		bool			operator	>=		(const fixed& x) const;

		//fixed-point operators
		fixed&		operator 	++		();						//prefix operators
		fixed&		operator 	--		();
		fixed		operator 	++		(int);					//postfix operators
		fixed		operator 	--		(int);
		fixed		operator 	+ 		(const fixed& x) const;
		fixed		operator 	- 		(const fixed& x) const;
		fixed		operator 	- 		() const;
		fixed		operator 	* 		(const fixed& x) const;
		fixed		operator 	/ 		(const fixed& x) const;
		fixed&		operator	= 		(const fixed& x);
		fixed&		operator 	+= 		(const fixed& x);
		fixed&		operator 	-= 		(const fixed& x);
		fixed&		operator 	*= 		(const fixed& x);
		fixed&		operator 	/= 		(const fixed& x);
		
		//fixed-integer operations
		fixed		operator 	+ 		(const int& x) const;
		fixed		operator 	- 		(const int& x) const;
		fixed		operator 	* 		(const int& x) const;
		fixed		operator 	/ 		(const int& x) const;
		fixed&		operator	= 		(const int& x);
		fixed&		operator 	+= 		(const int& x);
		fixed&		operator 	-= 		(const int& x);
		fixed&		operator 	*= 		(const int& x);
		fixed&		operator 	/= 		(const int& x);
		bool			operator	==		(const int& x) const;
		bool			operator	!=		(const int& x) const;
		bool			operator	<		(const int& x) const;
		bool			operator	>		(const int& x) const;
		bool			operator	<=		(const int& x) const;
		bool			operator	>=		(const int& x) const;
		
		//fixed-double operations
		fixed		operator 	+ 		(const double& x) const;
		fixed		operator 	- 		(const double& x) const;
		fixed		operator 	* 		(const double& x) const;
		fixed		operator 	/ 		(const double& x) const;
		fixed&		operator	= 		(const double& x);
		fixed&		operator 	+= 		(const double& x);
		fixed&		operator 	-= 		(const double& x);
		fixed&		operator 	*= 		(const double& x);
		fixed&		operator 	/= 		(const double& x);
		bool			operator	==		(const double& x) const;
		bool			operator	!=		(const double& x) const;
		bool			operator	<		(const double& x) const;
		bool			operator	>		(const double& x) const;
		bool			operator	<=		(const double& x) const;
		bool			operator	>=		(const double& x) const;
		
		//regular conversions
		operator		int		() const;
		operator		float	() const;
		
		//-------------------------------------------------------------
		//					Static Methods
		//-------------------------------------------------------------
		//misc
		static int	floor	(const fixed& x);
		static int	ceil		(const fixed& x);
		static fixed	sqrt		(const fixed& x);
		static fixed	hypot	(const fixed& x, const fixed& y);
		
		//trigonometry
		static fixed	sin		(const fixed& x);
		static fixed	cos		(const fixed& x);
		static fixed	tan		(const fixed& x);
		static fixed	asin		(const fixed& x);
		static fixed	acos		(const fixed& x);
		static fixed	atan		(const fixed& x);
		static fixed	atan2	(const fixed& x, const fixed& y);
		
		//trigonometry (integer conversions)
		static fixed	sin		(const int& x);
		static fixed	cos		(const int& x);
		static fixed	tan		(const int& x);
		static fixed	asin		(const int& x);
		static fixed	acos		(const int& x);
		static fixed	atan		(const int& x);
		static fixed	atan2	(const int& x, const int& y);
		
		//trigonometry (double conversions)
		static fixed	sin		(const double& x);
		static fixed	cos		(const double& x);
		static fixed	tan		(const double& x);
		static fixed	asin		(const double& x);
		static fixed	acos		(const double& x);
		static fixed	atan		(const double& x);
		static fixed	atan2	(const double& x, const double& y);
};

//---------------------------------------------------------------------
//						I/O Streams
//---------------------------------------------------------------------
HL_INLINE std::ostream& operator << ( std::ostream& sout, const fixed& fix ) {
	sout << (float)fix;
	return sout;
}

HL_INLINE std::istream& operator >> ( std::istream& stin, fixed& fix ) {
	float inNum( 0.f );
	stin >> inNum;
	fix.num = al_ftofix( inNum );
	return stin;
}

//---------------------------------------------------------------------
//						Construction
//---------------------------------------------------------------------
HL_INLINE fixed::fixed() : num(0) {
}

HL_INLINE fixed::fixed(const fixed& x) : num(x.num) {
}

HL_INLINE fixed::fixed(const int& x) : num(al_itofix(x)) {
}

HL_INLINE fixed::fixed(const double& x) : num(al_ftofix(x)) {
}

HL_INLINE fixed::~fixed() {
}

//---------------------------------------------------------------------
//						Fixed Point Operators
//---------------------------------------------------------------------
//comparisons
HL_INLINE bool fixed::operator == (const fixed& x) const {
	return (num == x.num) ? true : false;
}

HL_INLINE bool fixed::operator != (const fixed& x) const {
	return (num != x.num) ? true : false;
}

HL_INLINE bool fixed::operator < (const fixed& x) const {
	return (num < x.num) ? true : false;
}

HL_INLINE bool fixed::operator > (const fixed& x) const {
	return (num > x.num) ? true : false;
}

HL_INLINE bool fixed::operator <= (const fixed& x) const {
	return (num <= x.num) ? true : false;
}

HL_INLINE bool fixed::operator >= (const fixed& x) const {
	return (num >= x.num) ? true : false;
}

// prefix operations
HL_INLINE fixed& fixed::operator ++ () {
	num = al_fixadd(num, 1 << 16);
	return *this;
}

HL_INLINE fixed& fixed::operator -- () {
	num = al_fixsub(num, 1 << 16);
	return *this;
}

//postfix operations
HL_INLINE fixed fixed::operator ++ (int) {
	fixed temp;
	temp.num = al_fixadd(num, 1 << 16);
	return temp;
}

HL_INLINE fixed fixed::operator-- (int) {
	fixed temp;
	temp.num = al_fixsub(num, 1 << 16);
	return temp;
}

HL_INLINE fixed fixed::operator + (const fixed& x) const {
	fixed temp;
	temp.num = al_fixadd(num, x.num);
	return temp;
}
	
HL_INLINE fixed fixed::operator - (const fixed& x) const {
	fixed temp;
	temp.num = al_fixsub(0, num);
	return temp;
}
	
HL_INLINE fixed fixed::operator * (const fixed& x) const {
	fixed temp;
	temp.num = al_fixmul(num, x.num);
	return temp;
}
	
HL_INLINE fixed fixed::operator / (const fixed& x) const {
	fixed temp;
	temp.num = al_fixdiv(num, x.num);
	return temp;
}

HL_INLINE fixed& fixed::operator = (const fixed& x) {
	num = x.num;
	return *this;
}
	
HL_INLINE fixed& fixed::operator += (const fixed& x) {
	num = al_fixadd(num, x.num);
	return *this;
}
	
HL_INLINE fixed& fixed::operator -= (const fixed& x) {
	num = al_fixsub(num, x.num);
	return *this;
}
	
HL_INLINE fixed& fixed::operator *= (const fixed& x) {
	num = al_fixmul(num, x.num);
	return *this;
}
	
HL_INLINE fixed& fixed::operator /= (const fixed& x) {
	num = al_fixdiv(num, x.num);
	return *this;
}

//---------------------------------------------------------------------
//						Fixed-Integer Operators
//---------------------------------------------------------------------
HL_INLINE fixed fixed::operator + (const int& x) const {
	fixed temp;
	temp.num = al_fixadd(num, al_itofix(x));
	return temp;
}
	
HL_INLINE fixed fixed::operator - (const int& x) const {
	fixed temp;
	temp.num = al_fixsub(num, al_itofix(x));
	return temp;
}
	
HL_INLINE fixed fixed::operator * (const int& x) const {
	fixed temp;
	temp.num = al_fixmul(num, al_itofix(x));
	return temp;
}
	
HL_INLINE fixed fixed::operator / (const int& x) const {
	fixed temp;
	temp.num = al_fixdiv(num, al_itofix(x));
	return temp;
}

HL_INLINE fixed& fixed::operator = (const int& x) {
	num = al_itofix(x);
	return *this;
}
	
HL_INLINE fixed& fixed::operator += (const int& x) {
	num = al_fixadd(num, al_itofix(x));
	return *this;
}
	
HL_INLINE fixed& fixed::operator -= (const int& x) {
	num = al_fixsub(num, al_itofix(x));
	return *this;
}
	
HL_INLINE fixed& fixed::operator *= (const int& x) {
	num = al_fixmul(num, al_itofix(x));
	return *this;
}
	
HL_INLINE fixed& fixed::operator /= (const int& x) {
	num = al_fixdiv(num, al_itofix(x));
	return *this;
}

//comparisons
HL_INLINE bool fixed::operator == (const int& x) const {
	return (num == al_itofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator != (const int& x) const {
	return (num != al_itofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator < (const int& x) const {
	return (num < al_itofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator > (const int& x) const {
	return (num > al_itofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator <= (const int& x) const {
	return (num <= al_itofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator >= (const int& x) const {
	return (num >= al_itofix(x)) ? true : false;
}

//---------------------------------------------------------------------
//						Fixed-double Operators
//---------------------------------------------------------------------
HL_INLINE fixed fixed::operator + (const double& x) const {
	fixed temp;
	temp.num = al_fixadd(num, al_ftofix(x));
	return temp;
}
	
HL_INLINE fixed fixed::operator - (const double& x) const {
	fixed temp;
	temp.num = al_fixsub(num, al_ftofix(x));
	return temp;
}
	
HL_INLINE fixed fixed::operator * (const double& x) const {
	fixed temp;
	temp.num = al_fixmul(num, al_ftofix(x));
	return temp;
}
	
HL_INLINE fixed fixed::operator / (const double& x) const {
	fixed temp;
	temp.num = al_fixdiv(num, al_ftofix(x));
	return temp;
}

HL_INLINE fixed& fixed::operator = (const double& x) {
	num = al_ftofix(x);
	return *this;
}
	
HL_INLINE fixed& fixed::operator += (const double& x) {
	num = al_fixadd(num, al_ftofix(x));
	return *this;
}
	
HL_INLINE fixed& fixed::operator -= (const double& x) {
	num = al_fixsub(num, al_ftofix(x));
	return *this;
}
	
HL_INLINE fixed& fixed::operator *= (const double& x) {
	num = al_fixmul(num, al_ftofix(x));
	return *this;
}
	
HL_INLINE fixed& fixed::operator /= (const double& x) {
	num = al_fixdiv(num, al_ftofix(x));
	return *this;
}

//comparisons
HL_INLINE bool fixed::operator == (const double& x) const {
	return (num == al_ftofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator != (const double& x) const {
	return (num != al_ftofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator < (const double& x) const {
	return (num < al_ftofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator > (const double& x) const {
	return (num > al_ftofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator <= (const double& x) const {
	return (num <= al_ftofix(x)) ? true : false;
}

HL_INLINE bool fixed::operator >= (const double& x) const {
	return (num >= al_ftofix(x)) ? true : false;
}

//regular conversions
HL_INLINE fixed::operator int() const {
	return al_fixtoi(num);
}

//regular conversions
HL_INLINE fixed::operator float() const {
	return al_fixtof(num);
}

//---------------------------------------------------------------------
//						Static Methods
//---------------------------------------------------------------------
//misc
HL_INLINE int fixed::floor(const fixed& x) {
	return al_fixtoi(al_fixfloor(x.num));
}

HL_INLINE int fixed::ceil(const fixed& x) {
	return al_fixtoi(al_fixceil(x.num));
}

HL_INLINE fixed fixed::sqrt(const fixed& x) {
	return fixed(al_fixsqrt(x.num));
}

HL_INLINE fixed fixed::hypot(const fixed& x, const fixed& y) {
	fixed temp;
	temp = al_fixhypot(x.num, y.num);
	return temp;
}
		
//trigonometry
HL_INLINE fixed	fixed::sin (const fixed& x) {
	fixed temp;
	temp.num = al_fixsin(x.num);
	return temp;
}

HL_INLINE fixed	fixed::cos (const fixed& x) {
	fixed temp;
	temp.num = al_fixcos(x.num);
	return temp;
}

HL_INLINE fixed	fixed::tan (const fixed& x) {
	fixed temp;
	temp.num = al_fixtan(x.num);
	return temp;
}

HL_INLINE fixed	fixed::asin (const fixed& x) {
	fixed temp;
	temp.num = al_fixasin(x.num);
	return temp;
}

HL_INLINE fixed	fixed::acos (const fixed& x) {
	fixed temp;
	temp.num = al_fixacos(x.num);
	return temp;
}

HL_INLINE fixed	fixed::atan (const fixed& x) {
	fixed temp;
	temp.num = al_fixatan(x.num);
	return temp;
}

HL_INLINE fixed	fixed::atan2 (const fixed& x, const fixed& y) {
	fixed temp;
	temp.num = al_fixatan2(x.num, y.num);
	return temp;
}

//trigonometry (integer conversions)
HL_INLINE fixed	fixed::sin (const int& x) {
	fixed temp;
	temp.num = al_fixsin(al_itofix(x));
	return temp;
}

HL_INLINE fixed	fixed::cos (const int& x) {
	fixed temp;
	temp.num = al_fixcos(al_itofix(x));
	return temp;
}

HL_INLINE fixed	fixed::tan (const int& x) {
	fixed temp;
	temp.num = al_fixtan(al_itofix(x));
	return temp;
}

HL_INLINE fixed	fixed::asin (const int& x) {
	fixed temp;
	temp.num = al_fixasin(al_itofix(x));
	return temp;
}

HL_INLINE fixed	fixed::acos (const int& x) {
	fixed temp;
	temp.num = al_fixacos(al_itofix(x));
	return temp;
}

HL_INLINE fixed	fixed::atan (const int& x) {
	fixed temp;
	temp.num = al_fixatan(al_itofix(x));
	return temp;
}

HL_INLINE fixed	fixed::atan2 (const int& x, const int& y) {
	fixed temp;
	temp.num = al_fixatan2(al_itofix(x), al_itofix(y));
	return temp;
}

//trigonometry (double conversions)
HL_INLINE fixed	fixed::sin (const double& x) {
	fixed temp;
	temp.num = al_fixsin(al_ftofix(x));
	return temp;
}

HL_INLINE fixed	fixed::cos (const double& x) {
	fixed temp;
	temp.num = al_fixcos(al_ftofix(x));
	return temp;
}

HL_INLINE fixed	fixed::tan (const double& x) {
	fixed temp;
	temp.num = al_fixtan(al_ftofix(x));
	return temp;
}

HL_INLINE fixed	fixed::asin (const double& x) {
	fixed temp;
	temp.num = al_fixasin(al_ftofix(x));
	return temp;
}

HL_INLINE fixed	fixed::acos (const double& x) {
	fixed temp;
	temp.num = al_fixacos(al_ftofix(x));
	return temp;
}

HL_INLINE fixed	fixed::atan (const double& x) {
	fixed temp;
	temp.num = al_fixatan(al_ftofix(x));
	return temp;
}

HL_INLINE fixed	fixed::atan2 (const double& x, const double& y) {
	fixed temp;
	temp.num = al_fixatan2(al_ftofix(x), al_ftofix(y));
	return temp;
}
	
} //end math namespace
} //end hamlibs namespace
#endif	/* __HL_FIXED_MATH_H__ */

