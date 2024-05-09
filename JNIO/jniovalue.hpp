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

        class jnio_value {
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

                template <typename T> static const T castNumber(const jnio_value& val) {
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
                            throw jnio_value::badcast;
                        }
                    }
                }

            public:
                jnio_value(const JNIOEnv& env);
                jnio_value(const JNIOEnv& env, const jboolean& z);
                jnio_value(const JNIOEnv& env, const jbyte& b);
                jnio_value(const JNIOEnv& env, const jshort& s);
                jnio_value(const JNIOEnv& env, const jchar& c);
                jnio_value(const JNIOEnv& env, const jint& i);
                jnio_value(const JNIOEnv& env, const jlong& j);
                jnio_value(const JNIOEnv& env, const jfloat& f);
                jnio_value(const JNIOEnv& env, const jdouble& d);
                jnio_value(const JNIOEnv& env, const jobject& o);
                jnio_value(const JNIOEnv& env, const char* str);
                jnio_value(const jnio_value& val);
                ~jnio_value() = default;

                jnio_value& operator = (const jboolean& z) noexcept;
                jnio_value& operator = (const jbyte& b) noexcept;
                jnio_value& operator = (const jshort& s) noexcept;
                jnio_value& operator = (const jchar& c) noexcept;
                jnio_value& operator = (const jint& i) noexcept;
                jnio_value& operator = (const jlong& j) noexcept;
                jnio_value& operator = (const jfloat& f) noexcept;
                jnio_value& operator = (const jdouble& d) noexcept;
                jnio_value& operator = (const jobject& o) noexcept;
                jnio_value& operator = (const char* str) noexcept;

                jnio_value& operator = (const jnio_value& val) noexcept;

                bool operator == (const jnio_value& val) const noexcept;

                void setValue(const jboolean& z) noexcept;
                void setValue(const jbyte& b) noexcept;
                void setValue(const jshort& s) noexcept;
                void setValue(const jchar& c) noexcept;
                void setValue(const jint& i) noexcept;
                void setValue(const jlong& j) noexcept;
                void setValue(const jfloat& f) noexcept;
                void setValue(const jdouble& d) noexcept;
                void setValue(const jobject& o) noexcept;
                void setValue(const char* str) noexcept;

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

                friend std::ostream& operator << (std::ostream& os, const jnio_value& val) noexcept {
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
                            os << "Empty JValue";
                            break;
                        }
                    }
                    return os;
                }
        };
    }

#endif