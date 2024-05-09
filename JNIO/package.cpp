#include "package.hpp"

namespace jnio {

    java_package::java_package(const char* location) {
        unsigned int len = strlen(location);
        this->location = new char[len+1]; this->location[len] = '\0';
        for (unsigned int i = 0; i < len; i++) {
            this->location[i] = location[i];
        }
    }
    java_package::java_package(const java_package& pack) {
        unsigned int len = strlen(pack.location);
        this->location = new char[len+1]; this->location[len] = '\0';
        for (unsigned int i = 0; i < len; i++) {
            this->location[i] = pack.location[i];
        }
    }

    java_package& java_package::operator = (const java_package& other) noexcept {
        if (this->location != nullptr) {
            delete[] this->location;
        }

        unsigned int len = strlen(other.location);
        this->location = new char[len+1]; this->location[len] = '\0';
        for (unsigned int i = 0; i < len; i++) {
            this->location[i] = other.location[i];
        }

        return *this;
    }
    bool java_package::operator == (const java_package& other) const noexcept {
        return (strcmp(this->location, other.location) == 0);
    }
    
    // java_class java_package::get_class(const char* classname) const {
    //     if (classname == nullptr) {
    //         throw jnio_exception("Unable to find a Java Class from a nullptr.");
    //     }
    //     return java_class(*this, classname);
    // }
}