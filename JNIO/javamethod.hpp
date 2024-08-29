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

		class JavaClass;
		class JavaObject;
		class JavaObjectArray;

		class JavaMethod {
			protected:
				JNIEnv* env;
				std::string name;
				const JavaClass* clazz;
				sign::Method sign;
				jmethodID method;

			public:
				JavaMethod() = default;
				explicit JavaMethod(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Method& sign);
				
				~JavaMethod() = default;

				JavaMethod(const JavaMethod& meth) = default;
				JavaMethod& operator = (const JavaMethod& other) = default;

				const jmethodID& getJMethod() const noexcept;        
				operator const jmethodID&() const noexcept;

				const sign::Method& getSignature() const noexcept;

				virtual JValue callOn(const JavaObject& obj, std::initializer_list<JValue> args = {}) const;
				virtual JValue callOn(jobject obj, std::initializer_list<JValue> args = {}) const;

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const JavaMethod& other) const noexcept;
		};

		class JavaStaticMethod : public JavaMethod {
			public:
				JavaStaticMethod() = default;
				explicit JavaStaticMethod(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Method& sign);
				
				~JavaStaticMethod() = default;
				JavaStaticMethod& operator = (const JavaStaticMethod& other) = default;

				JavaStaticMethod(const JavaStaticMethod& meth);

				virtual JValue callOn(const JavaObject& obj, std::initializer_list<JValue> args = {}) const override final;
				virtual JValue callOn(jobject obj, std::initializer_list<JValue> args = {}) const override final;
				
				JValue call(std::initializer_list<JValue> args = {}) const;
		};

		class JavaConstructor : public JavaMethod {
			public:
				JavaConstructor() = default;
				explicit JavaConstructor(JNIEnv* env, const JavaClass& clazz, const sign::Constructor& cs);
				explicit JavaConstructor(JNIEnv* env, const JavaClass& clazz);
				
				~JavaConstructor() = default;

				JavaConstructor(const JavaConstructor& con);
				JavaConstructor& operator = (const JavaConstructor& other) = default;

				JavaObject newInstance(std::initializer_list<JValue> args = {}) const;
				JavaObjectArray newArray(size_t length) const;
		};
	}

#endif