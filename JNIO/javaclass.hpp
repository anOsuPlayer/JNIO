#ifndef JNIO_CLASS
	#define JNIO_CLASS

	#include <jni.h>
	#include <string>

	#include "jnioenv.hpp"
	#include "javapackage.hpp"
	#include "javaobject.hpp"
	#include "javamethod.hpp"
	#include "javafield.hpp"
	#include "noclassexception.hpp"
	#include "javasignature.hpp"
	#include "javavalue.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class java_package;
		class java_method;
		class java_constructor;
		class java_static_method;
		class java_field;
		class java_static_field;
		class java_object;

		class java_class {
			protected:
				std::string classname;
				jclass clazz;

			public:
				java_class() = default;
				java_class(jclass clazz);
				explicit java_class(const std::string& fullname);
				explicit java_class(const java_package& pack, const std::string& classname);
				
				virtual ~java_class();

				java_class(const java_class& clazz);
				virtual java_class& operator = (const java_class& other);

				operator const jclass&() const noexcept;
				jclass getJClass() const noexcept;

				virtual java_object as_object() const noexcept final;

				value call(const java_static_method& jsm, std::initializer_list<value> args = {}) const;

				value access(const java_static_field& jsf) const;
				void edit(const java_static_field& jsf, const value& value) const;

				java_method getMethod(const char* name, const sign::method& ms) const;
				java_static_method getStaticMethod(const char* name, const sign::method& ms) const;

				java_constructor getConstructor(const sign::constructor& cs = sign::DEFAULT) const;

				java_field getField(const char* name, const sign::field& ms);
				java_static_field getStaticField(const char* name, const sign::field& ms);

				bool isArray() const noexcept;

				bool extends(const jclass& clazz) const noexcept;

				java_class arrayType(size_t level = 1) const;

				java_class componentType() const noexcept;
				java_class baseType() const noexcept;

				const std::string& string() const noexcept;
				bool operator == (const java_class& other) const noexcept;
			
			friend class java_constructor;
		};
	}
	
#endif