#ifndef JNIO_JVALUE
	#define JNIO_JVALUE

	#include <jni.h>
	#include <iostream>

	#include "jnioutils.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class value {
			private:
				jvalue val;

			public:
				value() = default;
				value(jboolean z);
				value(jbyte b);
				value(jshort s);
				value(jchar c);
				value(jint i);
				value(jlong j);
				value(jfloat f);
				value(jdouble d);
				value(jobject o);
				
				~value() = default;

				value(const value& val) = default;
				value& operator = (const value& val) = default;

				value& operator = (jboolean z) noexcept;
				value& operator = (jbyte b) noexcept;
				value& operator = (jshort s) noexcept;
				value& operator = (jchar c) noexcept;
				value& operator = (jint i) noexcept;
				value& operator = (jlong j) noexcept;
				value& operator = (jfloat f) noexcept;
				value& operator = (jdouble d) noexcept;
				value& operator = (jobject o) noexcept;

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

				bool operator == (const value& val) const noexcept;
		};
	}

#endif