#include "jniopackage.hpp"

namespace jnio {

    java_package::java_package(const JNIOEnv& env, const char* location) {
        this->env = &env;
        this->location = std::string(location);
    }
    java_package::java_package(const JNIOEnv& env, const std::string& location) {
        this->env = &env;
        this->location = location;
    }
    
    java_package::java_package(const java_package& pack) {
        this->env = pack.env;
        this->location = pack.location;
    }

    java_package& java_package::operator = (const java_package& other) noexcept {
        this->env = other.env;
        this->location = other.location;        

        return *this;
    }
    bool java_package::operator == (const java_package& other) const noexcept {
        return this->location == other.location;
    }
    
    java_class java_package::get_class(const char* classname) const {
        if (classname == nullptr) {
            throw jnio_exception("Unable to find a Java Class from a nullptr.");
        }
        return java_class(this->env, *this, classname);
    }
}