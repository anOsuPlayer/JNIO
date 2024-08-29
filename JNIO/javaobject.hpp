#ifndef JNIO_OBJECT
	#define JNIO_OBJECT

	#include "javamethod.hpp"
	#include "javafield.hpp"
	#include "javavalue.hpp"
	#include "javastring.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class JavaMethod;
		class JavaStaticMethod;
		class JavaField;

		class JavaObject {
			protected:
				JNIEnv* env;
				jobject obj;

				JavaObject() = default;

				static JValue _call(JNIEnv* env, jobject obj, const JavaMethod& jm, std::initializer_list<JValue> args = {});

				static JValue _access(JNIEnv* env, jobject obj, const JavaField& jf);
				static void _edit(JNIEnv* env, jobject obj, const JavaField& jf, const JValue& value);



			public:
				JavaObject(JNIEnv* env, const jobject& obj);
				
				virtual ~JavaObject();

				JavaObject(const JavaObject& obj);
				JavaObject& operator = (const JavaObject& obj);
				JavaObject& operator = (const jobject& obj);

				operator const jobject&() const noexcept;
				jobject getJObject() const noexcept;

				JValue call(const JavaMethod& jm, std::initializer_list<JValue> args = {}) const;

				JValue access(const JavaField& jf) const;
				void edit(const JavaField& jf, const JValue& value);

				JavaClass getClass() const;
				
				bool sameType(const jobject& obj) const noexcept;
				bool isInstanceof(const jclass& clazz) const noexcept;

				std::string string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const jobject& obj) const noexcept;

			friend class JavaMethod;
			friend class JavaField;
		};

		class JavaObjectArray;

		class JavaObjectArrayElement : public JavaObject {
			private:
				JavaObjectArray* ref;
				size_t refIndex;

				bool hasChanged = false;

				JavaObjectArrayElement() = default;

				JavaObjectArrayElement(JavaObjectArray* ref, size_t index);

			public:
				JavaObjectArrayElement(const jobject& obj) = delete;
				JavaObjectArrayElement(const JavaObject& obj) = delete;
				virtual ~JavaObjectArrayElement();

				JavaObjectArrayElement& operator = (const JavaObject& obj);
				JavaObjectArrayElement& operator = (const jobject& obj);
			
			friend class JavaObjectArray;
		};

		class JavaObjectArray {
			protected:
				JNIEnv* env;
				jobjectArray arr;
				JavaObjectArrayElement* currentElement;

			public:
				JavaObjectArray() = default;
				JavaObjectArray(JNIEnv* env, const jobjectArray& arr);

				virtual ~JavaObjectArray();

				JavaObjectArray(const JavaObjectArray& arr);
				JavaObjectArray& operator = (const JavaObjectArray& arr);
				JavaObjectArray& operator = (const jobjectArray& arr);

				operator const jobjectArray&() const noexcept;
				jobjectArray getJObjectArray() const noexcept;

				JavaObject asObject() const noexcept;

				JavaObjectArrayElement& operator [] (size_t index);

				size_t length() const noexcept;

				std::string string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const jobjectArray& arr) const noexcept;
			
			friend class JavaObjectArrayElement;
			friend class Moona;
		};
	}

#endif