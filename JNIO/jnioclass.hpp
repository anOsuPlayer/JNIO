#ifndef JNIO_CLASS
    #define JNIO_CLASS

    #include "jni.h"

    #include "jnioenv.hpp"
    #include "jniopackage.hpp"
    #include "jniovalue.hpp"
    #include "jniosignatures.hpp"

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
                char* classname;
                jclass clazz;
                const JNIOEnv* env;

            public:
                java_class(const JNIOEnv* env);
                java_class(const JNIOEnv* env, jclass clazz);
                explicit java_class(const JNIOEnv* env, const char* fullname);
                explicit java_class(const JNIOEnv* env, const java_package& pack, const char* classname);
                java_class(const JNIOEnv* env, const java_class& clazz);
                virtual ~java_class();

                operator const jclass&() const noexcept;
                jclass get_jclass() const noexcept;

                virtual java_object as_object() const noexcept final;

                virtual java_class& operator = (const java_class& other);
                bool operator == (const java_class& other);

                java_value call(const java_static_method& jsm, const jvalue* args = nullptr) const;

                java_value access(const java_static_field& jsf) const;
                void edit(const java_static_method& jsf, const jvalue& value);

                java_method get_method(const char* name, const method_signature& ms) const;
                java_static_method get_static_method(const char* name, const method_signature& ms) const;

                java_constructor get_constructor(const constructor_signature& cs = constructor_signature::DEFAULT) const;

                java_field get_field(const char* name, const field_signature& ms);
                java_static_field get_static_field(const char* name, const field_signature& ms);

                constexpr bool is_array() const noexcept;

                bool extends(const jclass& clazz) const noexcept;

                java_class array_type(size_t level = 1) const;
                java_class component_type() const noexcept;
            
            friend class java_constructor;
        };
    }

#endif