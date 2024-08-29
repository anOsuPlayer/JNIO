#include "javamethod.hpp"

namespace jnio {

    JavaMethod::JavaMethod(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Method& sign) {
        this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->method = env->GetMethodID(clazz.getJClass(), name.c_str(), sign);

        if (this->method == nullptr) {
            throw NoSuchMethodException();
        }
    }
    
    JavaMethod::operator const jmethodID&() const noexcept {
        return this->method;
    }

    const jmethodID& JavaMethod::getJMethod() const noexcept {
        return this->method;
    }

    const sign::Method& JavaMethod::getSignature() const noexcept {
        return this->sign;
    }

    JValue JavaMethod::callOn(const JavaObject& obj, std::initializer_list<JValue> args) const {
        return obj.call(*this, args);
    }

    JValue JavaMethod::callOn(jobject obj, std::initializer_list<JValue> args) const {
        return JavaObject::_call(this->env, obj, *this, args);
    }

	const std::string& JavaMethod::string() const noexcept {
        return this->name;
    }

    const char* JavaMethod::c_str() const noexcept {
        return this->name.c_str();
    }

    bool JavaMethod::operator == (const JavaMethod& other) const noexcept {
        return this->name == other.name && this->sign == other.sign && this->clazz == other.clazz;
    }

    JavaStaticMethod::JavaStaticMethod(JNIEnv* env, const std::string& name, const JavaClass& clazz, const sign::Method& sign) {
        this->env = env;
        this->clazz = &clazz;
        this->name = name;
        this->sign = sign;
        this->method = env->GetStaticMethodID(clazz.getJClass(), name.c_str(), sign);

        if (this->method == nullptr) {
            throw NoSuchMethodException();
        }
    }

    JValue JavaStaticMethod::callOn(const JavaObject& obj, std::initializer_list<JValue> args) const {
        throw jnio_exception("Unable to call JavaStaticMethod on a JavaObject.");
    }

    JValue JavaStaticMethod::callOn(jobject obj, std::initializer_list<JValue> args) const {
        throw jnio_exception("Unable to call JavaStaticMethod on a JavaObject.");
    }

    JValue JavaStaticMethod::call(std::initializer_list<JValue> args) const {
        return this->clazz->call(*this, args);
    }

    JavaConstructor::JavaConstructor(JNIEnv* env, const JavaClass& clazz, const sign::Constructor& cs) :
		JavaMethod(env, "<init>", clazz, cs) {
    }

    JavaConstructor::JavaConstructor(JNIEnv* env, const JavaClass& clazz)
		: JavaMethod(env, "<init>", clazz, sign::DEFAULT) {
	}

    JavaObject JavaConstructor::newInstance(std::initializer_list<JValue> args) const {
        JavaObject obj(this->env, (args.size() == 0) ? env->NewObject(this->clazz->getJClass(), this->method)
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

    JavaObjectArray JavaConstructor::newArray(size_t length) const {
        JavaObjectArray arr(this->env, env->NewObjectArray(length, this->clazz->clazz, nullptr));

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