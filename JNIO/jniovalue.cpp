#include "jniovalue.hpp"

namespace jnio {

    jnio_value::jnio_value(const JNIOEnv& env) {
        this->env = &env;
        this->tag = value_tag::NONE;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jboolean& z) : z{z} {
        this->env = &env;
        this->tag = value_tag::BOOLEAN;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jbyte& b) : b{b} {
        this->env = &env;
        this->tag = value_tag::BYTE;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jshort& s) : s{s} {
        this->env = &env;
        this->tag = value_tag::SHORT;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jchar& c) : c{c} {
        this->env = &env;
        this->tag = value_tag::CHAR;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jint& i) : i{i} {
        this->env = &env;
        this->tag = value_tag::INT;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jlong& j) : j{j} {
        this->env = &env;
        this->tag = value_tag::LONG;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jfloat& f) : f{f} {
        this->env = &env;
        this->tag = value_tag::FLOAT;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jdouble& d) : d{d} {
        this->env = &env;
        this->tag = value_tag::DOUBLE;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const jobject& o) : o{o} {
        this->env = &env;
        this->tag = value_tag::OBJECT;
    }
    jnio_value::jnio_value(const JNIOEnv& env, const char* str) {
        this->env = &env;
        this->o = env.get_JNIEnv()->NewStringUTF(str);
        this->tag = value_tag::STRING;
    }

    jnio_value::jnio_value(const jnio_value& val) {
        *this = val;
    }

    const jnio_exception jnio_value::badcast = jnio_exception("Illegal JValue cast.");

    jnio_value& jnio_value::operator = (const jboolean& z) noexcept {
        this->tag = value_tag::BOOLEAN;
        this->z = z;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jbyte& b) noexcept {
        this->tag = value_tag::BYTE;
        this->b = b;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jshort& s) noexcept {
        this->tag = value_tag::SHORT;
        this->s = s;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jchar& c) noexcept {
        this->tag = value_tag::CHAR;
        this->c = c;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jint& i) noexcept {
        this->tag = value_tag::INT;
        this->i = i;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jlong& j) noexcept {
        this->tag = value_tag::LONG;
        this->j = j;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jfloat& f) noexcept {
        this->tag = value_tag::FLOAT;
        this->f = f;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jdouble& d) noexcept {
        this->tag = value_tag::DOUBLE;
        this->d = d;

        return *this;
    }
    jnio_value& jnio_value::operator = (const jobject& o) noexcept {
        this->tag = value_tag::OBJECT;
        this->o = o;

        return *this;
    }
    jnio_value& jnio_value::operator = (const char* str) noexcept {
        this->tag = value_tag::STRING;
        this->o = this->env->get_JNIEnv()->NewStringUTF(str);

        return *this;
    }

    jnio_value& jnio_value::operator = (const jnio_value& val) noexcept {
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

    bool jnio_value::operator == (const jnio_value& val) const noexcept {
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

    void jnio_value::setValue(const jboolean& z) noexcept {
        this->tag = value_tag::BOOLEAN;
        this->z = z;
    }
    void jnio_value::setValue(const jbyte& b) noexcept {
        this->tag = value_tag::BYTE;
        this->b = b;
    }
    void jnio_value::setValue(const jshort& s) noexcept {
        this->tag = value_tag::SHORT;
        this->s = s;
    }
    void jnio_value::setValue(const jchar& c) noexcept {
        this->tag = value_tag::CHAR;
        this->c = c;
    }
    void jnio_value::setValue(const jint& i) noexcept {
        this->tag = value_tag::INT;
        this->i = i;
    }
    void jnio_value::setValue(const jlong& j) noexcept {
        this->tag = value_tag::LONG;
        this->j = j;
    }
    void jnio_value::setValue(const jfloat& f) noexcept {
        this->tag = value_tag::FLOAT;
        this->f = f;
    }
    void jnio_value::setValue(const jdouble& d) noexcept {
        this->tag = value_tag::DOUBLE;
        this->d = d;
    }
    void jnio_value::setValue(const jobject& o) noexcept {
        this->tag = value_tag::OBJECT;
        this->o = o;
    }
    void jnio_value::setValue(const char* str) noexcept {
        this->tag = value_tag::STRING;
        this->o = this->env->get_JNIEnv()->NewStringUTF(str);
    }

    jnio_value::operator const jboolean() const {
        if (this->tag != value_tag::BOOLEAN) {
            throw jnio_value::badcast;
        }
        return this->z;
    }
    jnio_value::operator const jbyte() const {
        return jnio_value::castNumber<jbyte>(*this);
    }
    jnio_value::operator const jshort() const {
        return jnio_value::castNumber<jshort>(*this);
    }
    jnio_value::operator const jchar() const {
        return jnio_value::castNumber<jchar>(*this);
    }
    jnio_value::operator const jint() const {
        return jnio_value::castNumber<jint>(*this);
    }
    jnio_value::operator const jlong() const {
        return jnio_value::castNumber<jlong>(*this);
    }
    jnio_value::operator const jfloat() const {
        return jnio_value::castNumber<jfloat>(*this);
    }
    jnio_value::operator const jdouble() const {
        return jnio_value::castNumber<jdouble>(*this);
    }
    jnio_value::operator const jobject() const {
        if (this->tag == value_tag::OBJECT || this->tag == value_tag::STRING) {
            return this->o;
        }
        throw jnio_value::badcast;
    }
    jnio_value::operator const jstring() const {
        if (this->tag == value_tag::OBJECT || this->tag == value_tag::STRING) {
            return (jstring) this->o;
        }
        throw jnio_value::badcast;
    }

    jnio_value::operator const jvalue() const {
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