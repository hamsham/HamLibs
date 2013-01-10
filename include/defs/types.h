
//templated variable and class declarations

namespace hamLibs {
	
	// Global Typedefs
	typedef long int hlSize_t;
	
	//utility classes
	class	logger;
	class	string;
	
	namespace containers {
		//templated containers
		template <class type> class list;
		template <class type> class stack;
		template <class type> class queue;
		template <class type> class array;
		template <class type> class dictionary;
	} //containers namespace

	namespace math {
		//Multidimensional math classes
		template <class numType>	class mat2;
		template <class numType>	class mat3;
		template <class numType>	class mat4;
		template <class numType>	class quat;
		template <class numType>	class vec2;
		template <class numType>	class vec3;
		template <class numType>	class vec4;

		//[Hopefully] Useful Typedefs
		typedef quat	<float>		quatf;		//Quaternions
		typedef quat	<double>	quatd;
		typedef vec2	<float>		vec2f;		//2D vectors
		typedef vec2	<double>	vec2d;
		typedef vec3	<float>		vec3f;		//3D vectors
		typedef vec3	<double>	vec3d;
		typedef vec4	<float>		vec4f;		//4D vectors
		typedef vec4	<double>	vec4d;
		typedef mat2	<float>		mat2f;		//2x2 matrices
		typedef mat2	<double>	mat2d;
		typedef mat3	<float>		mat3f;		//3x3 matrices
		typedef mat3	<double>	mat3d;
		typedef mat4	<float>		mat4f;		//4x4 matrices
		typedef mat4	<double>	mat4d;
		
		typedef quat	<HL_FLOAT>	quat_t;
		typedef quat	<HL_FLOAT>	vec2_t;
		typedef quat	<HL_FLOAT>	vec3_t;
		typedef quat	<HL_FLOAT>	vec4_t;
		typedef quat	<HL_FLOAT>	mat2_t;
		typedef quat	<HL_FLOAT>	mat3_t;
		typedef quat	<HL_FLOAT>	mat4_t;

	}//hamLibs::math
}//hamLibs