#include "javavalue.hpp"

namespace jnio {

    JValue::JValue(jboolean z) {
		this->val.z = z;
    }

    JValue::JValue(jbyte b) {
		this->val.b = b;
	}

    JValue::JValue(jshort s) {
		this->val.s = s;
    }

    JValue::JValue(jchar c) {
		this->val.c = c;
    }

    JValue::JValue(jint i) {
		this->val.i = i;
    }

    JValue::JValue(jlong j) {
		this->val.j = j;
    }

    JValue::JValue(jfloat f) {
		this->val.f = f;
    }

    JValue::JValue(jdouble d) {
		this->val.d = d;
    }

    JValue::JValue(jobject o) {
		this->val.l = o;
    }

    JValue& JValue::operator = (jboolean z) noexcept {
        this->val.z = z;
        return *this;
    }

    JValue& JValue::operator = (jbyte b) noexcept {
        this->val.b = b;
        return *this;
    }

    JValue& JValue::operator = (jshort s) noexcept {
        this->val.s = s;
        return *this;
    }
	
    JValue& JValue::operator = (jchar c) noexcept {
        this->val.c = c;
        return *this;
    }

    JValue& JValue::operator = (jint i) noexcept {
        this->val.i = i;
        return *this;
    }

    JValue& JValue::operator = (jlong j) noexcept {
        this->val.j = j;
        return *this;
    }
	
    JValue& JValue::operator = (jfloat f) noexcept {
        this->val.f = f;
        return *this;
    }

    JValue& JValue::operator = (jdouble d) noexcept {
        this->val.d = d;
        return *this;
    }

    JValue& JValue::operator = (jobject o) noexcept {
        this->val.l = o;
        return *this;
    }

    JValue::operator jboolean() const noexcept {
        return this->val.z;
    }

    JValue::operator jbyte() const noexcept {
        return this->val.b;
    }

    JValue::operator jshort() const noexcept {
        return this->val.s;
    }

    JValue::operator jchar() const noexcept {
        return this->val.c;
    }

    JValue::operator jint() const noexcept {
        return this->val.i;
    }

    JValue::operator jlong() const noexcept {
        return this->val.j;
    }

    JValue::operator jfloat() const noexcept {
        return this->val.f;
    }
	
    JValue::operator jdouble() const noexcept {
        return this->val.d;
    }

    JValue::operator jobject() const noexcept {
        return this->val.l;
    }
	
    JValue::operator jstring() const noexcept {
        return (jstring) this->val.l;
    }

    JValue::operator const jvalue() const noexcept {
        return this->val;
    }

	bool JValue::operator == (const JValue& val) const noexcept {
        return this->val.l == val.val.l;
    }
}