#ifndef JNIO_SIGNATURES
    #define JNIO_SIGNATURES

    #include <string.h>

    #include "jnioexception.hpp"

    namespace jnio {

        class pure_signature {
            protected:
                char* signature;
                pure_signature() = default;
            
            public:
                explicit pure_signature(const char* signature);
                pure_signature(const pure_signature& ps);
                virtual ~pure_signature();

                virtual pure_signature& operator = (const pure_signature& ps2) noexcept;
                virtual bool operator == (const pure_signature& ps2) const noexcept;

                operator const char*() const noexcept;
                const char* get_signature() const noexcept;

            friend class array_signature;
        };

        class composed_signature : public pure_signature {
            public:
                explicit composed_signature(const char* signature);
                composed_signature(const pure_signature& ps);
                virtual ~composed_signature() = default;

                composed_signature& concat(const pure_signature& ps);
                composed_signature& operator + (const pure_signature& ps);
                composed_signature& operator += (const pure_signature& ps);
        };

        class signature : public pure_signature {
            public:
                signature() = delete;
                explicit signature(const char* signature);
                signature(const signature& s);
                virtual ~signature() = default;

                static const signature BOOLEAN;
                static const signature BYTE;
                static const signature CHAR;
                static const signature SHORT;
                static const signature INT;
                static const signature LONG;
                static const signature FLOAT;
                static const signature DOUBLE;

                static const signature VOID;
        };

        class object_signature : public pure_signature {
            public:
                object_signature() = delete;
                object_signature(const char* obj);
                object_signature(const object_signature& os);
                virtual ~object_signature() = default;

                static const object_signature STRING;
                static const object_signature OBJECT;
        };

        class array_signature : public pure_signature {
            public:
                array_signature() = delete;
                array_signature(const char* obj, unsigned int order = 1);
                array_signature(const pure_signature& base, unsigned int order = 1);
                virtual ~array_signature() = default;

                static const array_signature BOOLEAN_ARRAY;
                static const array_signature BYTE_ARRAY;
                static const array_signature CHAR_ARRAY;
                static const array_signature SHORT_ARRAY;
                static const array_signature INT_ARRAY;
                static const array_signature LONG_ARRAY;
                static const array_signature FLOAT_ARRAY;
                static const array_signature DOUBLE_ARRAY;

                static const array_signature STRING_ARRAY;
                static const array_signature OBJECT_ARRAY;

                pure_signature getBaseSignature() const noexcept;
        };

        class method_signature {
            private:
                char* signature;

            public:
                method_signature() = default;
                explicit method_signature(const char* signature);
                method_signature(const pure_signature& returntype);
                method_signature(const pure_signature& returntype, const composed_signature& args);
                method_signature(const method_signature& ms);
                ~method_signature();

                static const method_signature BOOLEAN_METHOD;
                static const method_signature BYTE_METHOD;
                static const method_signature SHORT_METHOD;
                static const method_signature CHAR_METHOD;
                static const method_signature INT_METHOD;
                static const method_signature LONG_METHOD;
                static const method_signature FLOAT_METHOD;
                static const method_signature DOUBLE_METHOD;
                
                static const method_signature VOID_METHOD;

                static const method_signature STRING_METHOD;

                static const method_signature MAIN;

                static const method_signature TO_STRING;
                static const method_signature EQUALS;
                static const method_signature HASH_CODE;
                static const method_signature WAIT;
                static const method_signature NOTIFY;

                virtual method_signature& operator = (const method_signature& ms) noexcept;
                virtual bool operator == (const method_signature& ms) const noexcept;

                operator const char*() const noexcept;
                const char* get_signature() const noexcept;

                const pure_signature returnType() const noexcept;
            
            friend class constructor_signature;
        };

        class constructor_signature : public method_signature {
            public:
                constructor_signature();
                explicit constructor_signature(const char* signature);
                constructor_signature(const composed_signature& args);
                constructor_signature(const constructor_signature& cs);
                ~constructor_signature() = default;

                static const constructor_signature DEFAULT;
        };

        class field_signature {
            private:
                char* signature;

            public:
                field_signature() = default;
                explicit field_signature(const char* signature);
                field_signature(const pure_signature& type);
                field_signature(const field_signature& fs);
                ~field_signature();

                static const field_signature BOOLEAN_FIELD;
                static const field_signature BYTE_FIELD;
                static const field_signature SHORT_FIELD;
                static const field_signature CHAR_FIELD;
                static const field_signature INT_FIELD;
                static const field_signature LONG_FIELD;
                static const field_signature FLOAT_FIELD;
                static const field_signature DOUBLE_FIELD;

                static const field_signature STRING_FIELD;

                virtual field_signature& operator = (const field_signature& ms) noexcept;
                virtual bool operator == (const field_signature& ms) const noexcept;

                operator const char*() const noexcept;
                const char* get_signature() const noexcept;
        };
    }

#endif