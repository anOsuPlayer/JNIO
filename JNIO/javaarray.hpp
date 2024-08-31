#ifndef JNIO_ARRAY
	#define JNIO_ARRAY

	#include <jni.h>
	#include <concepts>

	#include "javavalue.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class java_object;

		template <typename A> concept base_array = requires { std::is_base_of<jarray, A>(); };

		template <base_array A, typename T> class java_array {
			protected:
				A arr;
				mutable T* elements = nullptr;
				JNIEnv* env;

				java_array(JNIEnv* env) {
					this->env = env;
				}

				virtual void release_elements() const noexcept = 0;

			public:
				virtual ~java_array() {
					if (this->elements != nullptr) {
						free(this->elements);
					}
				}

				const T* get_elements() const noexcept {
					return this->elements;
				}

				T& operator [] (size_t index) {
					if (index >= this->length()) {
						throw std::out_of_range("The given index goes out of bounds for this java_array.");
					}
					return this->elements[index];
				}

				virtual operator java_object() const noexcept = 0;

				explicit operator A() const noexcept {
					release_elements();
					return this->arr;
				}

				operator value() const noexcept {
					release_elements();
					return value(*this);
				}
				
				size_t length() const noexcept {
					release_elements();
					return env->GetArrayLength(arr);
				}
		};

		class java_boolean_array : public java_array<jbooleanArray, jboolean> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_boolean_array(JNIEnv* env);
				java_boolean_array(JNIEnv* env, const jbooleanArray& arr);
				java_boolean_array(JNIEnv* env, size_t size, const jboolean* args = nullptr);
				java_boolean_array(JNIEnv* env, std::initializer_list<jboolean> args);

				virtual ~java_boolean_array() = default;

				java_boolean_array(const java_boolean_array& arr);
				java_boolean_array& operator = (const jbooleanArray& arr);
				java_boolean_array& operator = (const java_boolean_array& arr);

				virtual operator java_object() const noexcept override final;
		};

		class java_byte_array : public java_array<jbyteArray, jbyte> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_byte_array(JNIEnv* env);
				java_byte_array(JNIEnv* env, const jbyteArray& arr);
				java_byte_array(JNIEnv* env, size_t size, const jbyte* args = nullptr);
				java_byte_array(JNIEnv* env, std::initializer_list<jbyte> args);

				virtual ~java_byte_array() = default;

				java_byte_array(const java_byte_array& arr);
				java_byte_array& operator = (const jbyteArray& arr);
				java_byte_array& operator = (const java_byte_array& arr);

				virtual operator java_object() const noexcept override final;
		};

		class java_short_array : public java_array<jshortArray, jshort> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_short_array(JNIEnv* env);
				java_short_array(JNIEnv* env, const jshortArray& arr);
				java_short_array(JNIEnv* env, size_t size, const jshort* args = nullptr);
				java_short_array(JNIEnv* env, std::initializer_list<jshort> args);

				virtual ~java_short_array() = default;

				java_short_array(const java_short_array& arr);
				java_short_array& operator = (const jshortArray& arr);
				java_short_array& operator = (const java_short_array& arr);

				virtual operator java_object() const noexcept override final;
		};

		class java_char_array : public java_array<jcharArray, jchar> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_char_array(JNIEnv* env);
				java_char_array(JNIEnv* env, const jcharArray& arr);
				java_char_array(JNIEnv* env, size_t size, const jchar* args = nullptr);
				java_char_array(JNIEnv* env, size_t size, const wchar_t* args = nullptr);
				java_char_array(JNIEnv* env, std::initializer_list<jchar> args);

				virtual ~java_char_array() = default;

				java_char_array(const java_char_array& arr);
				java_char_array& operator = (const jcharArray& arr);
				java_char_array& operator = (const java_char_array& arr);

				virtual operator java_object() const noexcept override final;
		};

		class java_int_array : public java_array<jintArray, jint> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_int_array(JNIEnv* env);
				java_int_array(JNIEnv* env, const jintArray& arr);
				java_int_array(JNIEnv* env, size_t size, const jint* args = nullptr);
				java_int_array(JNIEnv* env, std::initializer_list<jint> args);

				virtual ~java_int_array() = default;

				java_int_array(const java_int_array& arr);
				java_int_array& operator = (const jintArray& arr);
				java_int_array& operator = (const java_int_array& arr);

				virtual operator java_object() const noexcept override final;
		};
		
		class java_long_array : public java_array<jlongArray, jlong> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_long_array(JNIEnv* env);
				java_long_array(JNIEnv* env, const jlongArray& arr);
				java_long_array(JNIEnv* env, size_t size, const jlong* args = nullptr);
				java_long_array(JNIEnv* env, std::initializer_list<jlong> args);

				virtual ~java_long_array() = default;

				java_long_array(const java_long_array& arr);
				java_long_array& operator = (const jlongArray& arr);
				java_long_array& operator = (const java_long_array& arr);

				virtual operator java_object() const noexcept override final;
		};

		class java_float_array : public java_array<jfloatArray, jfloat> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_float_array(JNIEnv* env);
				java_float_array(JNIEnv* env, const jfloatArray& arr);
				java_float_array(JNIEnv* env, size_t size, const jfloat* args = nullptr);
				java_float_array(JNIEnv* env, std::initializer_list<jfloat> args);

				virtual ~java_float_array() = default;

				java_float_array(const java_float_array& arr);
				java_float_array& operator = (const jfloatArray& arr);
				java_float_array& operator = (const java_float_array& arr);

				virtual operator java_object() const noexcept override final;
		};

		class java_double_array : public java_array<jdoubleArray, jdouble> {
			protected:
				virtual void release_elements() const noexcept override final;
			
			public:
				java_double_array(JNIEnv* env);
				java_double_array(JNIEnv* env, const jdoubleArray& arr);
				java_double_array(JNIEnv* env, size_t size, const jdouble* args = nullptr);
				java_double_array(JNIEnv* env, std::initializer_list<jdouble> args);

				virtual ~java_double_array() = default;

				java_double_array(const java_double_array& arr);
				java_double_array& operator = (const jdoubleArray& arr);
				java_double_array& operator = (const java_double_array& arr);

				virtual operator java_object() const noexcept override final;
		};
	}

#endif