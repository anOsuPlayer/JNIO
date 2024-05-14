#ifndef JNIO_VALUE
    #define JNIO_VALUE

    #include <iostream>
    #include <string.h>
    #include <jni.h>

    #include "jnioexception.hpp"
    #include "jnioenv.hpp"

    namespace jnio {

        enum value_tag {
            NONE = -1,
            BOOLEAN = 0,
            BYTE = 1,
            SHORT = 2,
            CHAR = 3,
            INT = 4,
            LONG = 5,
            FLOAT = 6,
            DOUBLE = 7,
            OBJECT = -2,
            STRING = -3
        };

        class java_value {
            private:
                union {
                    jboolean z;
                    jbyte b;
                    jshort s;
                    jchar c;
                    jint i;
                    jlong j;
                    jfloat f;
                    jdouble d;
                    jobject o;
                };
                value_tag tag;
                const JNIOEnv* env;

                static const jnio_exception badcast;

                template <typename T> static const T cast_number(const java_value& val) {
                    switch(val.tag) {
                        case value_tag::BYTE : {
                            return static_cast<T>(val.b);
                        }
                        case value_tag::SHORT : {
                            return static_cast<T>(val.s);
                        }
                        case value_tag::CHAR : {
                            return static_cast<T>(val.c);
                        }
                        case value_tag::INT : {
                            return static_cast<T>(val.i);
                        }
                        case value_tag::LONG : {
                            return static_cast<T>(val.j);
                        }
                        case value_tag::FLOAT : {
                            return static_cast<T>(val.f);
                        }
                        case value_tag::DOUBLE : {
                            return static_cast<T>(val.d);
                        }
                        default : {
                            throw java_value::badcast;
                        }
                    }
                }

            public:
                java_value(const JNIOEnv& env);
                java_value(const JNIOEnv& env, jboolean z);
                java_value(const JNIOEnv& env, jbyte b);
                java_value(const JNIOEnv& env, jshort s);
                java_value(const JNIOEnv& env, jchar c);
                java_value(const JNIOEnv& env, jint i);
                java_value(const JNIOEnv& env, jlong j);
                java_value(const JNIOEnv& env, jfloat f);
                java_value(const JNIOEnv& env, jdouble d);
                java_value(const JNIOEnv& env, const jobject& o);
                java_value(const JNIOEnv& env, const char* str);
                java_value(const java_value& val);
                ~java_value() = default;

                java_value& operator = (jboolean z) noexcept;
                java_value& operator = (jbyte b) noexcept;
                java_value& operator = (jshort s) noexcept;
                java_value& operator = (jchar c) noexcept;
                java_value& operator = (jint i) noexcept;
                java_value& operator = (jlong j) noexcept;
                java_value& operator = (jfloat f) noexcept;
                java_value& operator = (jdouble d) noexcept;
                java_value& operator = (const jobject& o) noexcept;
                java_value& operator = (const char* str) noexcept;

                java_value& operator = (const java_value& val) noexcept;

                bool operator == (const java_value& val) const noexcept;

                void set_value(jboolean z) noexcept;
                void set_value(jbyte b) noexcept;
                void set_value(jshort s) noexcept;
                void set_value(jchar c) noexcept;
                void set_value(jint i) noexcept;
                void set_value(jlong j) noexcept;
                void set_value(jfloat f) noexcept;
                void set_value(jdouble d) noexcept;
                void set_value(const jobject& o) noexcept;
                void set_value(const char* str) noexcept;

                operator const jboolean() const;
                operator const jbyte() const;
                operator const jshort() const;
                operator const jchar() const;
                operator const jint() const;
                operator const jlong() const;
                operator const jfloat() const;
                operator const jdouble() const;
                operator const jobject() const;
                operator const jstring() const;

                operator const jvalue() const;

                friend std::ostream& operator << (std::ostream& os, const java_value& val) noexcept {
                    switch (val.tag) {
                        case value_tag::BOOLEAN : {
                            os << std::boolalpha << ((val.z == 0) ? false : true) << std::noboolalpha;
                            break;
                        }
                        case value_tag::BYTE : {
                            os << val.b;
                            break;
                        }
                        case value_tag::SHORT : {
                            os << val.s;
                            break;
                        }
                        case value_tag::CHAR : {
                            os << val.c;
                            break;
                        }
                        case value_tag::INT : {
                            os << val.i;
                            break;
                        }
                        case value_tag::LONG : {
                            os << val.j;
                            break;
                        }
                        case value_tag::FLOAT : {
                            os << val.f;
                            break;
                        }
                        case value_tag::DOUBLE : {
                            os << val.d;
                            break;
                        }
                        case value_tag::OBJECT : {
                            os << val.o;
                            break;
                        }
                        case value_tag::STRING : {
                            const char* str = val.env->get_JNIEnv()->GetStringUTFChars((jstring) val.o, 0);
                            os << str;
                            val.env->get_JNIEnv()->ReleaseStringUTFChars((jstring) val.o, str);
                            break;
                        }
                        case value_tag::NONE : {
                            os << "empty value";
                            break;
                        }
                    }
                    return os;
                }
        };
    }

#endif