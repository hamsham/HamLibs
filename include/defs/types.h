
//templated variable and class declarations

namespace hamLibs {
	
	// Global Typedefs
	typedef long int hlSize_t;
	
	//utility classes
	namespace utils {
		
		class logger;
		
	} // utils namespace
	
	namespace containers {
		
		class string;
		
		//templated containers
		template <class type> class list;
		template <class type> class stack;
		template <class type> class queue;
		template <class type> class array;
		template <class type> class dictionary;
		
	} //containers namespace

	namespace math {
		
		//Multidimensional math classes
		template <class numType>	class mat2_t;
		template <class numType>	class mat3_t;
		template <class numType>	class mat4_t;
		template <class numType>	class quat_t;
		template <class numType>	class vec2_t;
		template <class numType>	class vec3_t;
		template <class numType>	class vec4_t;

	}//hamLibs::math
}//hamLibs