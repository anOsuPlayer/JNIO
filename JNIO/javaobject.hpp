#ifndef JNIO_OBJECT
	#define JNIO_OBJECT

	#include "jnioenv.hpp"
	#include "javamethod.hpp"
	#include "javafield.hpp"
	#include "javavalue.hpp"
	#include "javastring.hpp"
	#include "jnioexception.hpp"

	namespace jnio {

		class java_method;
		class java_static_method;
		class java_field;

		class java_object {
			protected:
				jobject obj;

				java_object() = default;

				static value _call(jobject obj, const java_method& jm, std::initializer_list<value> args = {});

				static value _access(jobject obj, const java_field& jf);
				static void _edit(jobject obj, const java_field& jf, const value& value);

			public:
				java_object(const jobject& obj);
				
				virtual ~java_object();

				java_object(const java_object& obj);
				java_object& operator = (const java_object& obj);
				java_object& operator = (const jobject& obj);

				operator const jobject&() const noexcept;
				jobject get_jobject() const noexcept;

				value call(const java_method& jm, std::initializer_list<value> args = {}) const;

				value access(const java_field& jf) const;
				void edit(const java_field& jf, const value& value);

				java_class get_class() const;
				
				bool same_type(const jobject& obj) const noexcept;
				bool is_instanceof(const jclass& clazz) const noexcept;

				std::string string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const jobject& obj) const noexcept;

			friend class java_method;
			friend class java_field;
		};

		class java_object_array;

		class java_object_array_element : public java_object {
			private:
				java_object_array* ref;
				size_t refIndex;

				bool hasChanged = false;

				java_object_array_element() = default;

				java_object_array_element(java_object_array* ref, size_t index);

			public:
				java_object_array_element(const jobject& obj) = delete;
				java_object_array_element(const java_object& obj) = delete;
				virtual ~java_object_array_element();

				java_object_array_element& operator = (const java_object& obj);
				java_object_array_element& operator = (const jobject& obj);
			
			friend class java_object_array;
		};

		class java_object_array {
			protected:
				jobjectArray arr;
				java_object_array_element* currentElement;

			public:
				java_object_array() = default;
				java_object_array(const jobjectArray& arr);

				virtual ~java_object_array();

				java_object_array(const java_object_array& arr);
				java_object_array& operator = (const java_object_array& arr);
				java_object_array& operator = (const jobjectArray& arr);

				operator const jobjectArray&() const noexcept;
				jobjectArray getJObjectArray() const noexcept;

				java_object as_object() const noexcept;

				java_object_array_element& operator [] (size_t index);

				size_t length() const noexcept;

				std::string string() const noexcept;
				const char* c_str() const noexcept;
				bool operator == (const jobjectArray& arr) const noexcept;
			
			friend class java_object_array_element;
			friend class Moona;
		};
	}

#endif