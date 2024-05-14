#ifndef JNIO_SIGNATURES
    #define JNIO_SIGNATURES

    #include <string>
    #include "jni.h"

    #include "jnioexception.hpp"

    namespace jnio {

        class base_signature {
            protected:
                base_signature() = default;

                std::string signature;
                base_signature(const char*);
                base_signature(const std::string&);

            public:
                base_signature(const base_signature&) = default;
                ~base_signature() = default;

                const base_signature& operator = (const base_signature&) noexcept;

                static const base_signature VOID;
                static const base_signature BOOLEAN;
                static const base_signature BYTE;
                static const base_signature CHAR;
                static const base_signature SHORT;
                static const base_signature INT;
                static const base_signature LONG;
                static const base_signature FLOAT;
                static const base_signature DOUBLE;

                const std::string& get_signature() const noexcept;

            friend class array_signature;
        };

        class object_signature : public base_signature {
            public:
                object_signature(const char*);
                object_signature(const std::string&);
                ~object_signature() = default;

                static const object_signature OBJECT;
                static const object_signature STRING;
        };

        class array_signature : public base_signature {
            private:
                unsigned int height;
                array_signature(const std::string&);

            public:
                array_signature(const base_signature&, unsigned int height);
                ~array_signature() = default;

                base_signature component_type() const noexcept;
                base_signature base_type() const noexcept;
        };
    }

#endif