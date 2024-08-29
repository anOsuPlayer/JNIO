#ifndef JNIO_STRING
	#define JNIO_STRING

	#include <jni.h>

	#include "javaarray.hpp"
	#include "javaobject.hpp"

	namespace jnio {

		class JavaString {
			private:
				JNIEnv* env;
				std::string text;

			public:
				JavaString(JNIEnv* env);
				JavaString(JNIEnv* env, const std::string& str, size_t init = 0, size_t chars = std::string::npos);
				JavaString(JNIEnv* env, JavaCharArray& charr, size_t init = 0, size_t chars = std::string::npos);
				JavaString(JNIEnv* env, const jstring& str, size_t init = 0, size_t chars = std::string::npos);
				
				~JavaString() = default;

				JavaString(const JavaString& str, size_t init = 0, size_t chars = std::string::npos);
				JavaString& operator = (const JavaString& str) = default;
				JavaString& operator = (const jstring& str);

				char& operator [] (size_t index);

				size_t length() const noexcept;

				JavaObject asObject() const noexcept;

				operator jstring() const noexcept;
				JavaCharArray toCharArray() const noexcept;

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const JavaString& str) const noexcept;
				bool operator == (jstring str) const noexcept;
		};
	}

#endif