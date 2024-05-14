#ifndef JNIO_STRING
    #define JNIO_STRING

    #include <iostream>

    #include "jni.h"

    #include "jnioarray.hpp"
    #include "jnioobject.hpp"

    namespace jnio {

        class java_string {
            private:
                char* text;

            public:
                java_string();
                java_string(const char* str, size_t init = 0, size_t end = 0);
                java_string(java_char_array& charr, size_t init = 0, size_t end = 0);
                java_string(jstring str, size_t init = 0, size_t end = 0);
                java_string(const java_string& str, size_t init = 0, size_t end = 0);
                virtual ~java_string();

                java_string& operator = (const java_string& str) noexcept;
                java_string& operator = (jstring str) noexcept;

                bool operator == (const java_string& str) const noexcept;
                bool operator == (jstring str) const noexcept;

                char& operator [] (size_t index);

                friend std::ostream& operator << (std::ostream& os, const java_string& str) noexcept {
                    os << str.text;
                    return os;
                }

                size_t length() const noexcept;

                java_char_array to_char_array() const noexcept;

                operator jstring() const noexcept;
                jstring get_jstring() const noexcept;

                virtual java_object as_object() const noexcept final;

                operator const char*() const noexcept;
        };
    }

#endif