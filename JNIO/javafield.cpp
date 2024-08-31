#include "javafield.hpp"

namespace jnio {

    java_field::java_field(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::field& sign) {
        this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->field = env->GetFieldID(clazz.getJClass(), name.c_str(), sign);

        if (this->field == nullptr) {
            throw no_such_field();
        }
    }

    java_field::operator const jfieldID&() const noexcept {
        return this->field;
    }

    const jfieldID& java_field::getJField() const noexcept {
        return this->field;
    }

    const sign::field& java_field::getSignature() const noexcept {
        return this->sign;
    }

    value java_field::accessOn(const java_object& obj) const {
        return obj.access(*this);
    }

    void java_field::editOn(java_object& obj, const value& value) {
        obj.edit(*this, value);
    }

    value java_field::accessOn(jobject obj) const {
        return java_object::_access(this->env, obj, *this);
    }

    void java_field::editOn(jobject obj, const value& value) {
        java_object::_edit(this->env, obj, *this, value);
    }

    const std::string& java_field::string() const noexcept {
        return this->name;
    }

	const char* java_field::c_str() const noexcept {
		return this->name.c_str();
	}

    bool java_field::operator == (const java_field& other) const noexcept {
        return this->name == other.name && this->sign == other.sign && this->clazz == other.clazz;
    }

    java_static_field::java_static_field(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::field& sign) {
		this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->field = env->GetStaticFieldID(clazz.getJClass(), name.c_str(), sign);

        if (this->field == nullptr) {
            throw no_such_field();
        }
    }

    value java_static_field::accessOn(const java_object& obj) const {
        throw jnio_exception("Unable to access a java_static_field from a java_object.");
    }
	
    void java_static_field::editOn(java_object& obj, const value& value) {
        throw jnio_exception("Unable to edit a java_static_field from a java_object.");
    }

    value java_static_field::accessOn(jobject obj) const {
        throw jnio_exception("Unable to access a java_static_field from a java_object.");
    }
    void java_static_field::editOn(jobject obj, const value& value) {
        throw jnio_exception("Unable to edit a java_static_field from a java_object.");
    }

    value java_static_field::access() const {
        return this->clazz->access(*this);
    }

    void java_static_field::edit(const value& value) const {
        this->clazz->edit(*this, value);
    }

	bool java_static_field::operator == (const java_static_field& other) const noexcept {
        return this->name == other.name && this->field == other.field && this->clazz == other.clazz;
    }
}