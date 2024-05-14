#ifndef JNIO_METHODS
    #define JNIO_METHODS

    #include "jni.h"

    #include "jniosignatures.hpp"
    #include "jniovalue.hpp"

    namespace jnio {

        class java_class;
        class java_object;
        class java_object_array;

        class java_method {
            protected:
                const char* name;
                const java_class* clazz;
                method_signature sign;
                jmethodID method;

            public:
                java_method() = default;
                explicit java_method(const char* name, const java_class& clazz, const method_signature& sign);
                java_method(const java_method& meth);
                virtual ~java_method() = default;

                const jmethodID& get_jmethodID() const noexcept;        
                operator const jmethodID&() const noexcept;

                virtual java_method& operator = (const java_method& other) noexcept;
                virtual bool operator == (const java_method& other) const noexcept;

                const method_signature& getSignature() const noexcept;

                virtual java_value call_on(const java_object& obj, const jvalue* args = nullptr) const;
                virtual java_value call_on(jobject& obj, const jvalue* args = nullptr) const;
        };

        class java_static_method : public java_method {
            public:
                java_static_method() = default;
                explicit java_static_method(const char* name, const java_class& clazz, const method_signature& sign);
                java_static_method(const java_static_method& meth);
                virtual ~java_static_method() = default;

                virtual java_value call_on(const java_object& obj, const jvalue* args = nullptr) const override final;
                virtual java_value call_on(jobject& obj, const jvalue* args = nullptr) const override final;
                
                java_value call(const jvalue* args = nullptr) const;
        };

        class java_constructor : protected java_method {
            public:
                java_constructor() = default;
                explicit java_constructor(const java_class& clazz, const constructor_signature& cs);
                explicit java_constructor(const java_class& clazz);
                java_constructor(const java_constructor& con);
                ~java_constructor() = default;

                java_object new_instance(const jvalue* args = nullptr) const;
                java_object_array new_array(size_t length) const;
        };
    }

#endif