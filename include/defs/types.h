
//templated variable and class declarations

//macros
#define HL_NULL 0

namespace hamLibs {
	typedef unsigned long int size_t;
	
	//utility classes
	class	logger;
	class	config;
	class	database;
	class	hamString;
	
namespace containers {
	//templated containers
	template <class type> class linkedList;
	template <class type> class stack;
	template <class type> class queue;
	template <class type> class dynArray;
	template <class type> class dictionary;
} //containers namespace

namespace math {
	//fixed point number type - EXPERIMENTAL!
	class fixed;

	//Multidimensional math classes
	template <class numType>	class mat2;
	template <class numType>	class mat3;
	template <class numType>	class mat4;
	template <class numType>	class quat;
	template <class numType>	class vec2;
	template <class numType>	class vec3;
	template <class numType>	class vec4;

	//[Hopefully] Useful Typedefs
	typedef quat	<int>		quati;		//Quaternions
	typedef quat	<long>		quatl;
	typedef quat	<float>		quatf;
	typedef quat	<double>	quatd;
	typedef quat	<fixed>		quatfix;
	typedef vec2	<int>		vec2i;		//2D vecors
	typedef vec2	<long>		vec2l;
	typedef vec2	<float>		vec2f;
	typedef vec2	<double>	vec2d;
	typedef quat	<fixed>		vec2fix;
	typedef vec3	<int>		vec3i;		//3D vecors
	typedef vec3	<long>		vec3l;
	typedef vec3	<float>		vec3f;
	typedef vec3	<double>	vec3d;
	typedef vec3	<fixed>		vec3fix;
	typedef vec4	<int>		vec4i;		//4D vecors
	typedef vec4	<long>		vec4l;
	typedef vec4	<float>		vec4f;
	typedef vec4	<double>	vec4d;
	typedef vec4	<fixed>		vec4fix;
	typedef mat2	<int>		mat2i;		//2D Matrices
	typedef mat2	<long>		mat2l;
	typedef mat2	<float>		mat2f;
	typedef mat2	<double>	mat2d;
	typedef mat2	<fixed>		mat2fix;
	typedef mat3	<int>		mat3i;		//3D Matrices
	typedef mat3	<long>		mat3l;
	typedef mat3	<float>		mat3f;
	typedef mat3	<double>	mat3d;
	typedef mat3	<fixed>		mat3fix;
	typedef mat4	<int>		mat4i;		//4D Matrices
	typedef mat4	<long>		mat4l;
	typedef mat4	<float>		mat4f;
	typedef mat4	<double>	mat4d;
	typedef mat4	<fixed>		mat4fix;

}//hamLibs::math
}//hamLibs