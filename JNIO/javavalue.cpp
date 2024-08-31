#include "javavalue.hpp"

namespace jnio {

    value::value(jboolean z) {
		this->val.z = z;
    }

    value::value(jbyte b) {
		this->val.b = b;
	}

    value::value(jshort s) {
		this->val.s = s;
    }

    value::value(jchar c) {
		this->val.c = c;
    }

    value::value(jint i) {
		this->val.i = i;
    }

    value::value(jlong j) {
		this->val.j = j;
    }

    value::value(jfloat f) {
		this->val.f = f;
    }

    value::value(jdouble d) {
		this->val.d = d;
    }

    value::value(jobject o) {
		this->val.l = o;
    }

    value& value::operator = (jboolean z) noexcept {
        this->val.z = z;
        return *this;
    }

    value& value::operator = (jbyte b) noexcept {
        this->val.b = b;
        return *this;
    }

    value& value::operator = (jshort s) noexcept {
        this->val.s = s;
        return *this;
    }
	
    value& value::operator = (jchar c) noexcept {
        this->val.c = c;
        return *this;
    }

    value& value::operator = (jint i) noexcept {
        this->val.i = i;
        return *this;
    }

    value& value::operator = (jlong j) noexcept {
        this->val.j = j;
        return *this;
    }
	
    value& value::operator = (jfloat f) noexcept {
        this->val.f = f;
        return *this;
    }

    value& value::operator = (jdouble d) noexcept {
        this->val.d = d;
        return *this;
    }

    value& value::operator = (jobject o) noexcept {
        this->val.l = o;
        return *this;
    }

    value::operator jboolean() const noexcept {
        return this->val.z;
    }

    value::operator jbyte() const noexcept {
        return this->val.b;
    }

    value::operator jshort() const noexcept {
        return this->val.s;
    }

    value::operator jchar() const noexcept {
        return this->val.c;
    }

    value::operator jint() const noexcept {
        return this->val.i;
    }

    value::operator jlong() const noexcept {
        return this->val.j;
    }

    value::operator jfloat() const noexcept {
        return this->val.f;
    }
	
    value::operator jdouble() const noexcept {
        return this->val.d;
    }

    value::operator jobject() const noexcept {
        return this->val.l;
    }
	
    value::operator jstring() const noexcept {
        return (jstring) this->val.l;
    }

    value::operator const jvalue() const noexcept {
        return this->val;
    }

	bool value::operator == (const value& val) const noexcept {
        return this->val.l == val.val.l;
    }
}