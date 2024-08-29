#ifndef JNIO_CLASS
	#define JNIO_CLASS

	#include <jni.h>
	#include <string>

	#include "javapackage.hpp"
	#include "javaobject.hpp"
	#include "javamethod.hpp"
	#include "javafield.hpp"
	#include "noclassexception.hpp"
	#include "javasignature.hpp"
	#include "javavalue.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class JavaPackage;
		class JavaMethod;
		class JavaConstructor;
		class JavaStaticMethod;
		class JavaField;
		class JavaStaticField;
		class JavaObject;

		class JavaClass {
			protected:
				std::string classname;
				jclass clazz;
				JNIEnv* env;

			public:
				JavaClass() = default;
				JavaClass(JNIEnv* env, jclass clazz);
				explicit JavaClass(JNIEnv* env, const std::string& fullname);
				explicit JavaClass(JNIEnv* env, const JavaPackage& pack, const std::string& classname);
				
				virtual ~JavaClass();

				JavaClass(const JavaClass& clazz);
				virtual JavaClass& operator = (const JavaClass& other);

				operator const jclass&() const noexcept;
				jclass getJClass() const noexcept;

				virtual JavaObject asObject() const noexcept final;

				JValue call(const JavaStaticMethod& jsm, std::initializer_list<JValue> args = {}) const;

				JValue access(const JavaStaticField& jsf) const;
				void edit(const JavaStaticField& jsf, const JValue& value) const;

				JavaMethod getMethod(const char* name, const sign::Method& ms) const;
				JavaStaticMethod getStaticMethod(const char* name, const sign::Method& ms) const;

				JavaConstructor getConstructor(const sign::Constructor& cs = sign::DEFAULT) const;

				JavaField getField(const char* name, const sign::Field& ms);
				JavaStaticField getStaticField(const char* name, const sign::Field& ms);

				bool isArray() const noexcept;

				bool extends(const jclass& clazz) const noexcept;

				JavaClass arrayType(size_t level = 1) const;

				JavaClass componentType() const noexcept;
				JavaClass baseType() const noexcept;

				const std::string& string() const noexcept;
				bool operator == (const JavaClass& other) const noexcept;
			
			friend class JavaConstructor;
		};
	}
	
#endif