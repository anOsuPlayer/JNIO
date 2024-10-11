#ifndef JNIO_STRING
	#define JNIO_STRING

	#include <jni.h>

	#include "javaarray.hpp"
	#include "javaobject.hpp"

	namespace jnio {

		class java_string {
			private:
				JNIEnv* env;
				std::string text;

			public:
				java_string(JNIEnv* env);
				java_string(JNIEnv* env, const std::string& str, size_t init = 0, size_t chars = std::string::npos);
				java_string(JNIEnv* env, java_char_array& charr, size_t init = 0, size_t chars = std::string::npos);
				java_string(JNIEnv* env, const jstring& str, size_t init = 0, size_t chars = std::string::npos);
				
				~java_string() = default;

				java_string(const java_string& str, size_t init = 0, size_t chars = std::string::npos);
				java_string& operator = (const java_string& str) = default;
				java_string& operator = (const jstring& str);

				char& operator [] (size_t index);

				size_t length() const noexcept;

				java_object as_object() const noexcept;

				operator jstring() const noexcept;
				java_char_array to_char_array() const noexcept;

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const java_string& str) const noexcept;
				bool operator == (jstring str) const noexcept;
		};
	}

#endif