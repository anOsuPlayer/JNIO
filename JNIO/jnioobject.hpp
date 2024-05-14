#ifndef JNIO_OBJECT
    #define JNIO_OBJECT

    #include "jni.h"

    #include "jniovalue.hpp"

    namespace jnio {

        class java_class;
        class java_method;
        class java_static_method;
        class java_field;

        class java_object {
            protected:
                jobject obj;

                java_object() = default;

                static java_value _call(jobject obj, const java_method& jm, const jvalue* args = nullptr);

                static java_value _access(jobject obj, const java_field& jf);
                static void _edit(jobject obj, const java_field& jf, const jvalue& value);

            public:
                java_object(const jobject& obj);
                java_object(const java_object& obj);
                virtual ~java_object();

                operator const jobject&() const noexcept;
                jobject get_jobject() const noexcept;

                virtual java_object as_object() const noexcept final;

                virtual java_object& operator = (const jobject& obj) noexcept;
                bool operator == (const jobject& obj) const noexcept;

                java_value call(const java_method& jm, const jvalue* args = nullptr) const;

                java_value access(const java_field& jf) const;
                void edit(const java_field& jf, const jvalue& value);

                java_class getClass() const;

                bool equals(const java_object& obj) const noexcept;
                
                bool same_type(const java_object& obj) const noexcept;

                bool is_instanceof(const java_class& clazz) const noexcept;

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

                virtual java_object& operator = (const jobject& obj) noexcept override final;
            
            friend class java_object_array;
        };

        class java_object_array {
            protected:
                jobjectArray arr;
                java_object_array_element* currentElement;

                static java_static_method PRINT_ARRAY;
                static java_static_method ARRAY_EQUALS;

                java_object_array() = default;

                void pop_current() noexcept;

            public:
                java_object_array(const jobjectArray& arr);
                java_object_array(const java_object_array& arr);
                virtual ~java_object_array();

                operator const jobjectArray&() const noexcept;
                jobjectArray get_jobjectArray() const noexcept;

                virtual java_object as_object() const noexcept final;

                java_object_array_element& operator [] (size_t index);

                java_object_array& operator = (const jobjectArray& arr) noexcept;
                bool operator == (const jobjectArray& arr) const noexcept;

                size_t length() const noexcept;

                bool equals(const jobjectArray& obj) const noexcept;
            
            friend class java_object_array_element;
        };
    }

#endif