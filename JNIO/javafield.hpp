#ifndef JNIO_FIELD
	#define JNIO_FIELD

	#include "nofieldexception.hpp"
	#include "javaclass.hpp"
	#include "javasignature.hpp"
	#include "javavalue.hpp"
	#include "javaobject.hpp"

	namespace jnio {

		class JavaClass;
		class JavaObject;

		class JavaField {
			protected:
				JNIEnv* env;
				std::string name;
				const JavaClass* clazz;
				sign::Field sign;
				jfieldID field;

			public:
				JavaField() = default;
				explicit JavaField(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Field& sign);

				virtual ~JavaField() = default;

				JavaField(const JavaField& meth) = default;
				JavaField& operator = (const JavaField& other) = default;

				const jfieldID& getJField() const noexcept;
				operator const jfieldID&() const noexcept;

				const sign::Field& getSignature() const noexcept;

				virtual JValue accessOn(const JavaObject& obj) const;
				virtual void editOn(JavaObject& obj, const JValue& value);

				virtual JValue accessOn(jobject obj) const;
				virtual void editOn(jobject obj, const JValue& value);

				const std::string& string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const JavaField& other) const noexcept;
		};

		class JavaStaticField : public JavaField {
			public:
				JavaStaticField() = default;
				explicit JavaStaticField(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Field& sign);
				
				virtual ~JavaStaticField() = default;
				JavaStaticField& operator = (const JavaStaticField& other) = default;

				JavaStaticField(const JavaStaticField& meth);

				virtual JValue accessOn(const JavaObject& obj) const override final;
				virtual void editOn(JavaObject& obj, const JValue& value) override final;

				virtual JValue accessOn(jobject obj) const override final;
				virtual void editOn(jobject obj, const JValue& value) override final;

				JValue access() const;
				void edit(const JValue& value) const;

				bool operator == (const JavaStaticField& other) const noexcept;
		};
	}

#endif