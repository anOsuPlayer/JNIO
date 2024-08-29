#ifndef JNIO_ARRAY
	#define JNIO_ARRAY

	#include <jni.h>
	#include <concepts>

	#include "javavalue.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class JavaObject;

		template <typename A> concept JArray = requires { std::is_base_of<jarray, A>(); };

		template <JArray A, typename T> class JavaArray {
			protected:
				mutable T* elements;
				mutable size_t size;
				JNIEnv* env;

				JavaArray(JNIEnv* env, size_t size) {
					this->env = env;
					this->elements = new T[size];
					this->size = size;
				}

			public:
				virtual ~JavaArray() {
					delete[] this->elements;
				}

				virtual JavaArray<A, T>& operator = (const JavaArray<A, T>& arr) noexcept final {
					if (this->elements != nullptr) {
						delete[] this->elements;
					}
					this->size = arr.length();
					this->elements = new T[size];
					for (size_t i = 0; i < size; i++) {
						this->elements[i] = arr.elements[i];
					}

					return *this;
				}

				virtual JavaArray<A, T>& operator = (A& arr) noexcept = 0;

				T* get_elements() const noexcept {
					return this->elements;
				}

				T& operator [] (size_t index) {
					if (index >= this->length()) {
						throw std::out_of_range("The given index goes out of bounds for this JavaArray.");
					}
					return this->elements[index];
				}

				virtual A getJArray() const noexcept = 0;

				virtual operator A() const noexcept = 0;

				JValue getJValue() const noexcept {
					return JValue(*this);
				}

				operator JValue() const noexcept {
					return JValue(*this);
				}

				virtual JavaObject asObject() const noexcept = 0;
				
				size_t length() const noexcept {
					return this->size;
				}
		};

		class JavaBooleanArray : public JavaArray<jbooleanArray, jboolean> {
			protected:
				JavaBooleanArray() = default;

			public:
				JavaBooleanArray(JNIEnv* env, jbooleanArray arr);
				JavaBooleanArray(JNIEnv* env, size_t size, jboolean* elements = nullptr);
				
				virtual ~JavaBooleanArray() = default;

				JavaBooleanArray(const JavaBooleanArray& arr);
				virtual JavaBooleanArray& operator = (jbooleanArray& arr) noexcept override final;

				virtual JavaObject asObject() const noexcept override final;

				JavaBooleanArray region(size_t begin, size_t end) const;

				virtual jbooleanArray getJArray() const noexcept override final;
				virtual operator jbooleanArray() const noexcept override final;
		};

		class JavaByteArray : public JavaArray<jbyteArray, jbyte> {
			protected:
				JavaByteArray() = default;

			public:
				JavaByteArray(JNIEnv* env, jbyteArray arr);
				JavaByteArray(JNIEnv* env, size_t size, jbyte* elements = nullptr);
				
				virtual ~JavaByteArray() = default;

				JavaByteArray(const JavaByteArray& arr);
				virtual JavaByteArray& operator = (jbyteArray& arr) noexcept override final;

				virtual JavaObject asObject() const noexcept override final;

				JavaByteArray region(size_t begin, size_t end) const;

				virtual jbyteArray getJArray() const noexcept override final;
				virtual operator jbyteArray() const noexcept override final;
		};

		class JavaCharArray : public JavaArray<jcharArray, jchar> {
			protected:
				JavaCharArray() = default;

			public:
				JavaCharArray(JNIEnv* env, jcharArray arr);
				JavaCharArray(JNIEnv* env, size_t size, jchar* elements = nullptr);
				JavaCharArray(JNIEnv* env, size_t size, const char* elements);
				
				virtual ~JavaCharArray() = default;

				JavaCharArray(const JavaCharArray& arr);
				virtual JavaCharArray& operator = (jcharArray& arr) noexcept override final;

				virtual JavaObject asObject() const noexcept override final;

				JavaCharArray region(size_t begin, size_t end) const;

				virtual jcharArray getJArray() const noexcept override final;
				virtual operator jcharArray() const noexcept override final;
		};

		class JavaIntArray : public JavaArray<jintArray, jint> {
			protected:
				JavaIntArray() = default;

			public:
				JavaIntArray(JNIEnv* env, jintArray arr);
				JavaIntArray(JNIEnv* env, size_t size, jint* elements = nullptr);
				
				virtual ~JavaIntArray() = default;

				JavaIntArray(const JavaIntArray& arr);
				virtual JavaIntArray& operator = (jintArray& arr) noexcept override final;

				virtual JavaObject asObject() const noexcept override final;

				JavaIntArray region(size_t begin, size_t end) const;

				virtual jintArray getJArray() const noexcept override final;
				virtual operator jintArray() const noexcept override final;
		};
		
		class JavaLongArray : public JavaArray<jlongArray, jlong> {
			protected:
				JavaLongArray() = default;

			public:
				JavaLongArray(JNIEnv* env, jlongArray arr);
				JavaLongArray(JNIEnv* env, size_t size, jlong* elements = nullptr);
				
				virtual ~JavaLongArray() = default;

				JavaLongArray(const JavaLongArray& arr);
				virtual JavaLongArray& operator = (jlongArray& arr) noexcept override final;

				virtual JavaObject asObject() const noexcept override final;

				JavaLongArray region(size_t begin, size_t end) const;

				virtual jlongArray getJArray() const noexcept override final;
				virtual operator jlongArray() const noexcept override final;
		};

		class JavaFloatArray : public JavaArray<jfloatArray, jfloat> {
			protected:
				JavaFloatArray() = default;

			public:
				JavaFloatArray(JNIEnv* env, jfloatArray arr);
				JavaFloatArray(JNIEnv* env, size_t size, jfloat* elements = nullptr);
				
				virtual ~JavaFloatArray() = default;

				JavaFloatArray(const JavaFloatArray& arr);
				virtual JavaFloatArray& operator = (jfloatArray& arr) noexcept override final;

				virtual JavaObject asObject() const noexcept override final;

				JavaFloatArray region(size_t begin, size_t end) const;

				virtual jfloatArray getJArray() const noexcept override final;
				virtual operator jfloatArray() const noexcept override final;
		};

		class JavaDoubleArray : public JavaArray<jdoubleArray, jdouble> {
			protected:
				JavaDoubleArray() = default;

			public:
				JavaDoubleArray(JNIEnv* env, jdoubleArray arr);
				JavaDoubleArray(JNIEnv* env, size_t size, jdouble* elements = nullptr);
				
				virtual ~JavaDoubleArray() = default;

				JavaDoubleArray(const JavaDoubleArray& arr);
				virtual JavaDoubleArray& operator = (jdoubleArray& arr) noexcept override final;

				virtual JavaObject asObject() const noexcept override final;

				JavaDoubleArray region(size_t begin, size_t end) const;

				virtual jdoubleArray getJArray() const noexcept override final;
				virtual operator jdoubleArray() const noexcept override final;
		};
	}

#endif