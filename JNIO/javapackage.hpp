#ifndef JNIO_PACKAGE
	#define JNIO_PACKAGE

	#include <jni.h>
	#include <string>

	#include "javaclass.hpp"

	namespace jnio {
		
		class java_class;

		class java_package {
			private:
				std::string location;
				JNIEnv* env;

			public:
				java_package() = delete;
				explicit java_package(JNIEnv* env, const std::string& location);
				
				~java_package() = default;

				java_package(const java_package& pack) = default;
				java_package& operator = (const java_package& other) = default;
				

				java_class getClass(const char* classname) const;

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const java_package& other) const noexcept;
		};
	}

#endif