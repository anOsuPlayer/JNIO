#include "jniovalue.hpp"

namespace jnio {

    java_value::java_value(const JNIOEnv& env) {
        this->env = &env;
        this->tag = value_tag::NONE;
    }
    java_value::java_value(const JNIOEnv& env, jboolean z) : z{z} {
        this->env = &env;
        this->tag = value_tag::BOOLEAN;
    }
    java_value::java_value(const JNIOEnv& env, jbyte b) : b{b} {
        this->env = &env;
        this->tag = value_tag::BYTE;
    }
    java_value::java_value(const JNIOEnv& env, jshort s) : s{s} {
        this->env = &env;
        this->tag = value_tag::SHORT;
    }
    java_value::java_value(const JNIOEnv& env, jchar c) : c{c} {
        this->env = &env;
        this->tag = value_tag::CHAR;
    }
    java_value::java_value(const JNIOEnv& env, jint i) : i{i} {
        this->env = &env;
        this->tag = value_tag::INT;
    }
    java_value::java_value(const JNIOEnv& env, jlong j) : j{j} {
        this->env = &env;
        this->tag = value_tag::LONG;
    }
    java_value::java_value(const JNIOEnv& env, jfloat f) : f{f} {
        this->env = &env;
        this->tag = value_tag::FLOAT;
    }
    java_value::java_value(const JNIOEnv& env, jdouble d) : d{d} {
        this->env = &env;
        this->tag = value_tag::DOUBLE;
    }
    java_value::java_value(const JNIOEnv& env, const jobject& o) : o{o} {
        this->env = &env;
        this->tag = value_tag::OBJECT;
    }
    java_value::java_value(const JNIOEnv& env, const char* str) {
        this->env = &env;
        this->o = env.get_JNIEnv()->NewStringUTF(str);
        this->tag = value_tag::STRING;
    }

    java_value::java_value(const java_value& val) {
        *this = val;
    }

    const jnio_exception java_value::badcast = jnio_exception("Illegal JValue cast.");

    java_value& java_value::operator = (jboolean z) noexcept {
        this->tag = value_tag::BOOLEAN;
        this->z = z;

        return *this;
    }
    java_value& java_value::operator = (jbyte b) noexcept {
        this->tag = value_tag::BYTE;
        this->b = b;

        return *this;
    }
    java_value& java_value::operator = (jshort s) noexcept {
        this->tag = value_tag::SHORT;
        this->s = s;

        return *this;
    }
    java_value& java_value::operator = (jchar c) noexcept {
        this->tag = value_tag::CHAR;
        this->c = c;

        return *this;
    }
    java_value& java_value::operator = (jint i) noexcept {
        this->tag = value_tag::INT;
        this->i = i;

        return *this;
    }
    java_value& java_value::operator = (jlong j) noexcept {
        this->tag = value_tag::LONG;
        this->j = j;

        return *this;
    }
    java_value& java_value::operator = (jfloat f) noexcept {
        this->tag = value_tag::FLOAT;
        this->f = f;

        return *this;
    }
    java_value& java_value::operator = (jdouble d) noexcept {
        this->tag = value_tag::DOUBLE;
        this->d = d;

        return *this;
    }
    java_value& java_value::operator = (const jobject& o) noexcept {
        this->tag = value_tag::OBJECT;
        this->o = o;

        return *this;
    }
    java_value& java_value::operator = (const char* str) noexcept {
        this->tag = value_tag::STRING;
        this->o = this->env->get_JNIEnv()->NewStringUTF(str);

        return *this;
    }

    java_value& java_value::operator = (const java_value& val) noexcept {
        this->env = val.env;
        this->tag = val.tag;

        switch (val.tag) {
            case value_tag::BOOLEAN : {
                this->z = val.z;
                break;
            }
            case value_tag::BYTE : {
                this->b = val.b;
                break;
            }
            case value_tag::SHORT : {
                this->s = val.s;
                break;
            }
            case value_tag::CHAR : {
                this->c = val.c;
                break;
            }
            case value_tag::INT : {
                this->i = val.i;
                break;
            }
            case value_tag::LONG : {
                this->j = val.j;
                break;
            }
            case value_tag::FLOAT : {
                this->f = val.f;
                break;
            }
            case value_tag::DOUBLE : {
                this->d = val.d;
                break;
            }
            case value_tag::STRING : 
            case value_tag::OBJECT : {
                this->o = val.o;
                break;
            }
        }

        return *this;
    }

    bool java_value::operator == (const java_value& val) const noexcept {
        if (this->tag <= 0 || val.tag <= 0) {
            switch (this->tag) {
                case value_tag::STRING : {
                    const char* chars1 = val.env->get_JNIEnv()->GetStringUTFChars((jstring) this->o, 0);
                    const char* chars2 = val.env->get_JNIEnv()->GetStringUTFChars((jstring) val.o, 0);
                    bool comp = (strcmp(chars1, chars2) == 1) ? true : false;

                    val.env->get_JNIEnv()->ReleaseStringUTFChars((jstring) this->o, chars1);
                    val.env->get_JNIEnv()->ReleaseStringUTFChars((jstring) val.o, chars2);
                    return comp;
                }
                case value_tag::OBJECT : {
                    return (val.tag == value_tag::OBJECT) && this->o == val.o;
                }
                case value_tag::BOOLEAN : {
                    return (val.tag == value_tag::BOOLEAN) && this->z == val.z;
                }
                case value_tag::NONE : {
                    return val.tag == value_tag::NONE;
                }
            }
        }
        else {
            double first, second;

            switch (this->tag) {
                case value_tag::BYTE : {
                    first = this->b;
                }
                case value_tag::CHAR : {
                    first = this->c;
                }
                case value_tag::SHORT : {
                    first = this->s;
                }
                case value_tag::INT : {
                    first = this->i;
                }
                case value_tag::LONG : {
                    first = this->j;
                }
                case value_tag::FLOAT : {
                    first = this->f;
                }
                case value_tag::DOUBLE : {
                    first = this->d;
                }
            }
            switch (val.tag) {
                case value_tag::BYTE : {
                    second = val.b;
                }
                case value_tag::CHAR : {
                    second = val.c;
                }
                case value_tag::SHORT : {
                    second = val.s;
                }
                case value_tag::INT : {
                    second = val.i;
                }
                case value_tag::LONG : {
                    second = val.j;
                }
                case value_tag::FLOAT : {
                    second = val.f;
                }
                case value_tag::DOUBLE : {
                    second = val.d;
                }
            }

            return first == second;
        }

        return false;
    }

    void java_value::set_value(jboolean z) noexcept {
        this->tag = value_tag::BOOLEAN;
        this->z = z;
    }
    void java_value::set_value(jbyte b) noexcept {
        this->tag = value_tag::BYTE;
        this->b = b;
    }
    void java_value::set_value(jshort s) noexcept {
        this->tag = value_tag::SHORT;
        this->s = s;
    }
    void java_value::set_value(jchar c) noexcept {
        this->tag = value_tag::CHAR;
        this->c = c;
    }
    void java_value::set_value(jint i) noexcept {
        this->tag = value_tag::INT;
        this->i = i;
    }
    void java_value::set_value(jlong j) noexcept {
        this->tag = value_tag::LONG;
        this->j = j;
    }
    void java_value::set_value(jfloat f) noexcept {
        this->tag = value_tag::FLOAT;
        this->f = f;
    }
    void java_value::set_value(jdouble d) noexcept {
        this->tag = value_tag::DOUBLE;
        this->d = d;
    }
    void java_value::set_value(const jobject& o) noexcept {
        this->tag = value_tag::OBJECT;
        this->o = o;
    }
    void java_value::set_value(const char* str) noexcept {
        this->tag = value_tag::STRING;
        this->o = this->env->get_JNIEnv()->NewStringUTF(str);
    }

    java_value::operator const jboolean() const {
        if (this->tag != value_tag::BOOLEAN) {
            throw java_value::badcast;
        }
        return this->z;
    }
    java_value::operator const jbyte() const {
        return java_value::cast_number<jbyte>(*this);
    }
    java_value::operator const jshort() const {
        return java_value::cast_number<jshort>(*this);
    }
    java_value::operator const jchar() const {
        return java_value::cast_number<jchar>(*this);
    }
    java_value::operator const jint() const {
        return java_value::cast_number<jint>(*this);
    }
    java_value::operator const jlong() const {
        return java_value::cast_number<jlong>(*this);
    }
    java_value::operator const jfloat() const {
        return java_value::cast_number<jfloat>(*this);
    }
    java_value::operator const jdouble() const {
        return java_value::cast_number<jdouble>(*this);
    }
    java_value::operator const jobject() const {
        if (this->tag == value_tag::OBJECT || this->tag == value_tag::STRING) {
            return this->o;
        }
        throw java_value::badcast;
    }
    java_value::operator const jstring() const {
        if (this->tag == value_tag::OBJECT || this->tag == value_tag::STRING) {
            return (jstring) this->o;
        }
        throw java_value::badcast;
    }

    java_value::operator const jvalue() const {
        jvalue val;

        switch (this->tag) {
            case value_tag::BOOLEAN : {
                val.z = this->z;
                break;
            }
            case value_tag::BYTE : {
                val.b = this->b;
                break;
            }
            case value_tag::CHAR : {
                val.c = this->c;
                break;
            }
            case value_tag::SHORT : {
                val.s = this->s;
                break;
            }
            case value_tag::INT : {
                val.i = this->i;
                break;
            }
            case value_tag::LONG : {
                val.j = this->j;
                break;
            }
            case value_tag::FLOAT : {
                val.f = this->f;
                break;
            }
            case value_tag::DOUBLE : {
                val.d = this->d;
                break;
            }
            case value_tag::STRING :
            case value_tag::OBJECT : {
                val.l = this->o;
                break;
            }
        }

        return val;
    }
}