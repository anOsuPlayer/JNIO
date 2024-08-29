#include "javafield.hpp"

namespace jnio {

    JavaField::JavaField(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Field& sign) {
        this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->field = env->GetFieldID(clazz.getJClass(), name.c_str(), sign);

        if (this->field == nullptr) {
            throw NoSuchFieldException();
        }
    }

    JavaField::operator const jfieldID&() const noexcept {
        return this->field;
    }

    const jfieldID& JavaField::getJField() const noexcept {
        return this->field;
    }

    const sign::Field& JavaField::getSignature() const noexcept {
        return this->sign;
    }

    JValue JavaField::accessOn(const JavaObject& obj) const {
        return obj.access(*this);
    }

    void JavaField::editOn(JavaObject& obj, const JValue& value) {
        obj.edit(*this, value);
    }

    JValue JavaField::accessOn(jobject obj) const {
        return JavaObject::_access(this->env, obj, *this);
    }

    void JavaField::editOn(jobject obj, const JValue& value) {
        JavaObject::_edit(this->env, obj, *this, value);
    }

    const std::string& JavaField::string() const noexcept {
        return this->name;
    }

	const char* JavaField::c_str() const noexcept {
		return this->name.c_str();
	}

    bool JavaField::operator == (const JavaField& other) const noexcept {
        return this->name == other.name && this->sign == other.sign && this->clazz == other.clazz;
    }

    JavaStaticField::JavaStaticField(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Field& sign) {
		this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->field = env->GetStaticFieldID(clazz.getJClass(), name.c_str(), sign);

        if (this->field == nullptr) {
            throw NoSuchFieldException();
        }
    }

    JValue JavaStaticField::accessOn(const JavaObject& obj) const {
        throw jnio_exception("Unable to access a JavaStaticField from a JavaObject.");
    }
	
    void JavaStaticField::editOn(JavaObject& obj, const JValue& value) {
        throw jnio_exception("Unable to edit a JavaStaticField from a JavaObject.");
    }

    JValue JavaStaticField::accessOn(jobject obj) const {
        throw jnio_exception("Unable to access a JavaStaticField from a JavaObject.");
    }
    void JavaStaticField::editOn(jobject obj, const JValue& value) {
        throw jnio_exception("Unable to edit a JavaStaticField from a JavaObject.");
    }

    JValue JavaStaticField::access() const {
        return this->clazz->access(*this);
    }

    void JavaStaticField::edit(const JValue& value) const {
        this->clazz->edit(*this, value);
    }

	bool JavaStaticField::operator == (const JavaStaticField& other) const noexcept {
        return this->name == other.name && this->field == other.field && this->clazz == other.clazz;
    }
}