#ifndef JNIO_FIELD
	#define JNIO_FIELD

	#include "nofieldexception.hpp"
	#include "javaclass.hpp"
	#include "javasignature.hpp"
	#include "javavalue.hpp"
	#include "javaobject.hpp"

	namespace jnio {

		class java_class;
		class java_object;

		class java_field {
			protected:
				JNIEnv* env;
				std::string name;
				const java_class* clazz;
				sign::field sign;
				jfieldID field;

			public:
				java_field() = default;
				explicit java_field(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::field& sign);

				virtual ~java_field() = default;

				java_field(const java_field& field) = default;
				java_field& operator = (const java_field& other) = default;

				const jfieldID& get_jfield() const noexcept;
				operator const jfieldID&() const noexcept;

				const sign::field& get_signature() const noexcept;

				virtual value access_on(const java_object& obj) const;
				virtual void edit_on(java_object& obj, const value& value);

				virtual value access_on(jobject obj) const;
				virtual void edit_on(jobject obj, const value& value);

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const java_field& other) const noexcept;
		};

		class java_static_field : public java_field {
			public:
				java_static_field() = default;
				explicit java_static_field(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::field& sign);
				
				virtual ~java_static_field() = default;
				java_static_field& operator = (const java_static_field& other) = default;

				java_static_field(const java_static_field& meth);

				virtual value access_on(const java_object& obj) const override final;
				virtual void edit_on(java_object& obj, const value& value) override final;

				virtual value access_on(jobject obj) const override final;
				virtual void edit_on(jobject obj, const value& value) override final;

				value access() const;
				void edit(const value& value) const;

				bool operator == (const java_static_field& other) const noexcept;
		};
	}

#endif