#include "javamethod.hpp"

namespace jnio {

    java_method::java_method(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::method& sign) {
        this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->method = env->GetMethodID(clazz.getJClass(), name.c_str(), sign);

        if (this->method == nullptr) {
            throw no_such_method();
        }
    }
    
    java_method::operator const jmethodID&() const noexcept {
        return this->method;
    }

    const jmethodID& java_method::getJMethod() const noexcept {
        return this->method;
    }

    const sign::method& java_method::get_signature() const noexcept {
        return this->sign;
    }

    value java_method::callOn(const java_object& obj, std::initializer_list<value> args) const {
        return obj.call(*this, args);
    }

    value java_method::callOn(jobject obj, std::initializer_list<value> args) const {
        return java_object::_call(this->env, obj, *this, args);
    }

	const std::string& java_method::string() const noexcept {
        return this->name;
    }

    const char* java_method::c_str() const noexcept {
        return this->name.c_str();
    }

    bool java_method::operator == (const java_method& other) const noexcept {
        return this->name == other.name && this->sign == other.sign && this->clazz == other.clazz;
    }

    java_static_method::java_static_method(JNIEnv* env, const std::string& name, const java_class& clazz, const sign::method& sign) {
        this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->method = env->GetStaticMethodID(clazz.getJClass(), name.c_str(), sign);

        if (this->method == nullptr) {
            throw no_such_method();
        }
    }

    value java_static_method::callOn(const java_object& obj, std::initializer_list<value> args) const {
        throw jnio_exception("Unable to call java_static_method on a java_object.");
    }

    value java_static_method::callOn(jobject obj, std::initializer_list<value> args) const {
        throw jnio_exception("Unable to call java_static_method on a java_object.");
    }

    value java_static_method::call(std::initializer_list<value> args) const {
        return this->clazz->call(*this, args);
    }

    java_constructor::java_constructor(JNIEnv* env, const java_class& clazz, const sign::constructor& cs) :
		java_method(env, "<init>", clazz, cs) {
    }

    java_constructor::java_constructor(JNIEnv* env, const java_class& clazz)
		: java_method(env, "<init>", clazz, sign::DEFAULT) {
	}

    java_object java_constructor::newInstance(std::initializer_list<value> args) const {
        java_object obj(this->env, (args.size() == 0) ? env->NewObject(this->clazz->getJClass(), this->method)
            : env->NewObjectA(this->clazz->getJClass(), this->method, (jvalue*) args.begin()));
        
        if (obj == nullptr) {
            throw jnio_exception("Object creation failed.");
        }
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("Object creation failed.");
        }

        return obj;
    }

    java_object_array java_constructor::newArray(size_t length) const {
        java_object_array arr(this->env, env->NewObjectArray(length, this->clazz->clazz, nullptr));

        if (arr == nullptr) {
            throw jnio_exception("Array creation failed.");
        }
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            jnio_exception("Array creation failed.");
        }

        return arr;
    }
}