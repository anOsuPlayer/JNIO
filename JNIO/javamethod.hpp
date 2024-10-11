#ifndef JNIO_METHOD
	#define JNIO_METHOD

	#include <jni.h>

	#include "nomethodexception.hpp"
	#include "javaclass.hpp"
	#include "javasignature.hpp"
	#include "javavalue.hpp"
	#include "javaobject.hpp"
	#include "javaarray.hpp"

	namespace jnio {

		class java_class;
		class java_object;
		class java_object_array;

		class java_method {
			protected:
				JNIEnv* env;
				std::string name;
				const java_class* clazz;
				sign::method sign;
				jmethodID method;

			public:
				java_method() = default;
				explicit java_method(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::method& sign);
				
				~java_method() = default;

				java_method(const java_method& meth) = default;
				java_method& operator = (const java_method& other) = default;

				const jmethodID& getJMethod() const noexcept;        
				operator const jmethodID&() const noexcept;

				const sign::method& get_signature() const noexcept;

				virtual value callOn(const java_object& obj, std::initializer_list<value> args = {}) const;
				virtual value callOn(jobject obj, std::initializer_list<value> args = {}) const;

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const java_method& other) const noexcept;
		};

		class java_static_method : public java_method {
			public:
				java_static_method() = default;
				explicit java_static_method(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::method& sign);
				
				~java_static_method() = default;
				java_static_method& operator = (const java_static_method& other) = default;

				java_static_method(const java_static_method& meth);

				virtual value callOn(const java_object& obj, std::initializer_list<value> args = {}) const override final;
				virtual value callOn(jobject obj, std::initializer_list<value> args = {}) const override final;
				
				value call(std::initializer_list<value> args = {}) const;
		};

		class java_constructor : public java_method {
			public:
				java_constructor() = default;
				explicit java_constructor(JNIEnv* env, const java_class& clazz, const sign::constructor& cs);
				explicit java_constructor(JNIEnv* env, const java_class& clazz);
				
				~java_constructor() = default;

				java_constructor(const java_constructor& con);
				java_constructor& operator = (const java_constructor& other) = default;

				java_object newInstance(std::initializer_list<value> args = {}) const;
				java_object_array newArray(size_t length) const;
		};
	}

#endif