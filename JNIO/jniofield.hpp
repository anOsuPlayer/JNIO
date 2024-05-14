#ifndef JNIO_FIELDS
    #define JNIO_FIELDS

    #include "jni.h"

    #include "jniosignatures.hpp"
    #include "jniovalue.hpp"

    namespace jnio {

        class java_class;
        class java_object;

        class java_field {
            protected:
                const char* name;
                java_class* clazz;
                field_signature sign;
                jfieldID field;

            public:
                java_field() = default;
                explicit java_field(const char* name, java_class& clazz, const field_signature& sign);
                java_field(const java_field& meth);
                virtual ~java_field() = default;
                
                const jfieldID& get_jfieldID() const noexcept;
                operator const jfieldID&() const noexcept;

                virtual java_field& operator = (const java_field& other) noexcept;
                virtual bool operator == (const java_field& other) const noexcept;

                const field_signature& getSignature() const noexcept;

                virtual java_value access_on(const java_object& obj) const;
                virtual void edit_on(java_object& obj, const jvalue& value);

                virtual java_value access_on(jobject obj) const;
                virtual void edit_on(jobject obj, const jvalue& value);
        };

        class java_static_field : public java_field {
            public:
                java_static_field() = default;
                explicit java_static_field(const char* name, java_class& clazz, const field_signature& sign);
                java_static_field(const java_static_field& meth);
                virtual ~java_static_field() = default;

                virtual java_value access_on(const java_object& obj) const override final;
                virtual void edit_on(java_object& obj, const jvalue& value) override final;

                virtual java_value access_on(jobject obj) const override final;
                virtual void edit_on(jobject obj, const jvalue& value) override final;

                java_value access() const;
                void edit(const jvalue& value) const;
        };
    }

#endif