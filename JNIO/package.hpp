#ifndef JNIO_PACKAGE
    #define JNIO_PACKAGE

    #include <string.h>

    #include "jnioexception.hpp"

    namespace jnio {

        class java_class;

        class java_package {
            private:
                char* location;

            public:
                java_package() = delete;
                explicit java_package(const char* location);
                java_package(const java_package& pack);
                ~java_package() = default;

                virtual java_package& operator = (const java_package& other) noexcept;
                virtual bool operator == (const java_package& other) const noexcept;

                java_class get_class(const char* classname) const;
        };
    }

#endif