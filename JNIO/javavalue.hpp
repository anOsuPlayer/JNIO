#ifndef JNIO_JVALUE
	#define JNIO_JVALUE

	#include <jni.h>
	#include <iostream>

	#include "jnioutils.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class JValue {
			private:
				jvalue val;

			public:
				JValue() = default;
				JValue(jboolean z);
				JValue(jbyte b);
				JValue(jshort s);
				JValue(jchar c);
				JValue(jint i);
				JValue(jlong j);
				JValue(jfloat f);
				JValue(jdouble d);
				JValue(jobject o);
				
				~JValue() = default;

				JValue(const JValue& val) = default;
				JValue& operator = (const JValue& val) = default;

				JValue& operator = (jboolean z) noexcept;
				JValue& operator = (jbyte b) noexcept;
				JValue& operator = (jshort s) noexcept;
				JValue& operator = (jchar c) noexcept;
				JValue& operator = (jint i) noexcept;
				JValue& operator = (jlong j) noexcept;
				JValue& operator = (jfloat f) noexcept;
				JValue& operator = (jdouble d) noexcept;
				JValue& operator = (jobject o) noexcept;

				operator jboolean() const noexcept;
				operator jbyte() const noexcept;
				operator jshort() const noexcept;
				operator jchar() const noexcept;
				operator jint() const noexcept;
				operator jlong() const noexcept;
				operator jfloat() const noexcept;
				operator jdouble() const noexcept;
				operator jobject() const noexcept;
				operator jstring() const noexcept;

				operator const jvalue() const noexcept;

				bool operator == (const JValue& val) const noexcept;
		};
	}

#endif