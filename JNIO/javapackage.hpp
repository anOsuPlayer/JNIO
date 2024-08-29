#ifndef JNIO_PACKAGE
	#define JNIO_PACKAGE

	#include <jni.h>
	#include <string>

	#include "javaclass.hpp"

	namespace jnio {
		
		class JavaClass;

		class JavaPackage {
			private:
				std::string location;
				JNIEnv* env;

			public:
				JavaPackage() = delete;
				explicit JavaPackage(JNIEnv* env, const std::string& location);
				
				~JavaPackage() = default;

				JavaPackage(const JavaPackage& pack) = default;
				JavaPackage& operator = (const JavaPackage& other) = default;
				

				JavaClass getClass(const char* classname) const;

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const JavaPackage& other) const noexcept;
		};
	}

#endif